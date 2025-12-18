# Zephyr IRQ Integration Guide for USB Stack (Single-Threaded)

## Executive Summary

This guide explains how to integrate Zephyr's IRQ subsystem into the current USB stack using a **single-threaded, polling-based architecture**. The current implementation has placeholder IRQ handlers with TODO comments for `CPEInterruptController` functions that need to be replaced with Zephyr's IRQ APIs. This design avoids threads and uses ISR + polling model suitable for single-core systems.

## Current State Analysis

### What's Present

1. **ISR Structure** (`usb_isr.c`):
   - Event queue management (enqueue/dequeue)
   - ISR handler functions (placeholders)
   - Power event handling
   - USB PHY event handling
   - Device event (EE1) handling
   - DSR (Deferred Service Routine) handlers for processing events

2. **IRQ Types Identified**:
   - `USB_CTRL_EE1_IRQ` (5) - Device event
   - `USB_CTRL_POWER_EVENT_IRQ` (10) - Power event (VBUS, L2 suspend/resume)
   - `USB_CTRL_HSPHY_IRQ` (11) - High-speed PHY event
   - `USB_PHY_DPSE_IRQ` (13) - DP/DM line state event
   - `USB_SOF_IRQ` (14) - Start of Frame (not used)
   - `USB_RECOVERED_SOF_IRQ` (15) - Recovered SOF (not used)

3. **Polling Architecture**:
   - `usb_dci_poll_events()` - Main polling function for device events
   - Event queues for buffering ISR events
   - DSR handlers process queued events in main loop context

### What's Missing

1. **Zephyr IRQ Registration**: No `IRQ_CONNECT()` or `irq_connect_dynamic()` calls
2. **Device Tree Integration**: No DT bindings for IRQ numbers and priorities
3. **IRQ Enable/Disable**: Placeholder functions need Zephyr `irq_enable()`/`irq_disable()`
4. **VBUS Detection**: No GPIO IRQ for VBUS detection
5. **Proper ISR Context**: Missing Zephyr ISR-safe operations

## Integration Architecture (Single-Threaded)

```
┌─────────────────────────────────────────────────────────────┐
│                    Device Tree (DTS)                         │
│  - USB controller node with interrupts property              │
│  - VBUS GPIO with interrupt configuration                    │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│              Zephyr IRQ Subsystem                            │
│  - IRQ_CONNECT() / irq_connect_dynamic()                    │
│  - irq_enable() / irq_disable()                              │
│  - ISR execution context                                     │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│              USB ISR Handlers (usb_isr.c)                    │
│  - usb_isr_ee1_handle()      - Device events                 │
│  - usb_isr_pwr_handle()      - Power events (L2)            │
│  - usb_isr_hsphy_handle()    - PHY events                    │
│  - usb_isr_vbus_handle()     - VBUS detection (NEW)         │
│                                                               │
│  ISR Actions:                                                │
│  1. Read hardware registers                                  │
│  2. Clear interrupt status                                   │
│  3. Enqueue event to queue                                   │
│  4. Set flag for main loop                                   │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│              Event Queue (ISR → Main Loop)                   │
│  - usb_event_enqueue() - Add events from ISR                │
│  - Volatile flags indicate pending events                    │
└─────────────────────────────────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│              Main Loop Polling (Application)                 │
│  - usb_poll_events() - Check flags & process events         │
│  - usb_dsr_handle_ee_event() - Process device events         │
│  - usb_dsr_handle_pwr_event() - Process power events         │
│  - usb_handle_vbus_event() - Process VBUS events            │
│                                                               │
│  Called periodically from main application loop              │
└─────────────────────────────────────────────────────────────┘
```

## Key Design Principles

1. **No Threads**: All processing happens in main loop context
2. **ISR Minimal Work**: ISRs only queue events and set flags
3. **Polling-Based**: Application calls `usb_poll_events()` periodically
4. **Event Queues**: Buffer multiple events between polls
5. **Volatile Flags**: Signal pending work to main loop

## Step-by-Step Integration

### Step 1: Device Tree Configuration

Create or update the USB device tree binding:

```dts
/* In your board's .dts or .dtsi file */

usb_dwc3: usb@<base_address> {
    compatible = "snps,dwc3";
    reg = <0x<base_address> 0x10000>;
    interrupts = <USB_CTRL_EE1_IRQ 2>,        /* Device event, priority 2 */
                 <USB_CTRL_POWER_EVENT_IRQ 2>, /* Power event, priority 2 */
                 <USB_CTRL_HSPHY_IRQ 2>;       /* PHY event, priority 2 */
    interrupt-names = "dwc3_ee1", "dwc3_pwr", "dwc3_phy";
    status = "okay";
};

/* VBUS detection GPIO */
vbus_detect: vbus-detect {
    compatible = "gpio-keys";
    vbus_gpio: vbus-gpio {
        gpios = <&gpio0 <pin_number> (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)>;
        label = "VBUS Detect";
    };
};
```

### Step 2: Update usb_isr.h

Add Zephyr IRQ context and polling flags:

```c
#ifndef USB_ISR_H
#define USB_ISR_H

#include "comdef.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "usb_dci.h"

/* IRQ numbers - should come from device tree */
#define USB_CTRL_EE1_IRQ          5
#define USB_CTRL_POWER_EVENT_IRQ  10
#define USB_CTRL_HSPHY_IRQ        11
#define USB_PHY_DPSE_IRQ          12

/* Event flags for polling */
#define USB_EVENT_FLAG_NONE       0x00
#define USB_EVENT_FLAG_DEVICE     0x01
#define USB_EVENT_FLAG_POWER      0x02
#define USB_EVENT_FLAG_VBUS       0x04
#define USB_EVENT_FLAG_PHY        0x08

typedef struct usb_isr_ctx
{
  usb_event_queue_t ee_dsr_queue;
  usb_event_queue_t pwr_dsr_queue;
  void* dci_ctx;
  void (*pwr_handle)(uint32 event_id);
  void (*vbus_handle)(uint32 vbus_high);
  
  /* Zephyr IRQ context */
  const struct device *usb_dev;
  struct gpio_callback vbus_cb_data;
  struct gpio_dt_spec vbus_gpio;
  uint32 irq_ee1;
  uint32 irq_pwr;
  uint32 irq_phy;
  
  /* Polling flags (volatile for ISR access) */
  volatile uint32 pending_events;
  volatile uint32 vbus_state;
} usb_isr_ctx_t;

/* Polling function to be called from main loop */
void usb_poll_events(usb_isr_ctx_t* isr_ctx);

/* ... rest of existing declarations ... */

#endif /*USB_ISR_H*/
```

### Step 3: Implement Zephyr IRQ Registration (usb_isr_zephyr.c)

Create a new file with single-threaded ISR handlers:

```c
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/irq.h>
#include "usb_isr.h"
#include "usb_dci.h"
#include "usb_log.h"

/* Get device tree node */
#define USB_DWC3_NODE DT_NODELABEL(usb_dwc3)
#define VBUS_GPIO_NODE DT_PATH(vbus_detect, vbus_gpio)

/* Static ISR context pointer for ISR callbacks */
static usb_isr_ctx_t *g_isr_ctx = NULL;

/*===========================================================================
FUNCTION usb_isr_ee1_zephyr_handler

DESCRIPTION
  Zephyr ISR wrapper for device event interrupt.
  Minimal work: enqueue event and set flag for polling.

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  Sets pending_events flag
===========================================================================*/
static void usb_isr_ee1_zephyr_handler(const void *arg)
{
    usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)arg;
    
    if (isr_ctx)
    {
        /* Enqueue event for later processing */
        if(usb_fn_isr()->usb_isr_enqueue_ee_event(isr_ctx))
        {
            /* Set flag for main loop to process */
            isr_ctx->pending_events |= USB_EVENT_FLAG_DEVICE;
        }
    }
}

/*===========================================================================
FUNCTION usb_isr_pwr_zephyr_handler

DESCRIPTION
  Zephyr ISR wrapper for power event interrupt.
  Minimal work: read status, enqueue, and set flag.

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  Sets pending_events flag
===========================================================================*/
static void usb_isr_pwr_zephyr_handler(const void *arg)
{
    usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)arg;
    uint32 pwr_isr_event;
    
    if (!isr_ctx)
        return;
    
    /* Read and clear interrupt status */
    pwr_isr_event = HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN;
    
    if (pwr_isr_event)
    {
        HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OUT(pwr_isr_event);
        
        /* Enqueue for later processing */
        if (usb_fn_isr()->usb_event_enqueue(&isr_ctx->pwr_dsr_queue, pwr_isr_event))
        {
            /* Set flag for main loop */
            isr_ctx->pending_events |= USB_EVENT_FLAG_POWER;
        }
        
        /* Call immediate handler if registered */
        if (isr_ctx->pwr_handle)
        {
            isr_ctx->pwr_handle(pwr_isr_event);
        }
    }
}

/*===========================================================================
FUNCTION usb_isr_hsphy_zephyr_handler

DESCRIPTION
  Zephyr ISR wrapper for high-speed PHY interrupt.
  Minimal work: disable PHY IRQ and enable clocks.

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  Sets pending_events flag
===========================================================================*/
static void usb_isr_hsphy_zephyr_handler(const void *arg)
{
    usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)arg;
    
    if (!isr_ctx)
        return;
    
    /* Disable PHY interrupt */
    usb_fn_isr()->usb_isr_usbphy_enable(FALSE);
    
    /* Enable clocks in ISR context */
    usb_fn_util()->usb_enable_clocks_in_isr();
    
    /* Set flag for main loop processing */
    isr_ctx->pending_events |= USB_EVENT_FLAG_PHY;
}

/*===========================================================================
FUNCTION usb_isr_vbus_gpio_callback

DESCRIPTION
  GPIO callback for VBUS detection.
  Minimal work: read state and set flag.

DEPENDENCIES
  None.

RETURN VALUE
  None

SIDE EFFECTS
  Sets pending_events flag and vbus_state
===========================================================================*/
static void usb_isr_vbus_gpio_callback(const struct device *dev,
                                        struct gpio_callback *cb,
                                        uint32_t pins)
{
    usb_isr_ctx_t* isr_ctx = CONTAINER_OF(cb, usb_isr_ctx_t, vbus_cb_data);
    int vbus_state;
    
    /* Read VBUS state */
    vbus_state = gpio_pin_get_dt(&isr_ctx->vbus_gpio);
    
    /* Store state for polling */
    isr_ctx->vbus_state = vbus_state;
    
    /* Set flag for main loop */
    isr_ctx->pending_events |= USB_EVENT_FLAG_VBUS;
}

/*===========================================================================
FUNCTION usb_isr_ee_enable

DESCRIPTION
  Enable/disable device event IRQ using Zephyr API

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.
===========================================================================*/
void usb_isr_ee_enable(boolean enable)
{
    if (g_isr_ctx == NULL)
        return;
        
    if (enable)
    {
        irq_enable(g_isr_ctx->irq_ee1);
    }
    else
    {
        irq_disable(g_isr_ctx->irq_ee1);
    }
}

/*===========================================================================
FUNCTION usb_isr_pwr_enable

DESCRIPTION
  Enable/disable power event IRQ using Zephyr API

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.
===========================================================================*/
void usb_isr_pwr_enable(boolean enable)
{
    if (g_isr_ctx == NULL)
        return;
        
    if (enable)
    {
        irq_enable(g_isr_ctx->irq_pwr);
    }
    else
    {
        irq_disable(g_isr_ctx->irq_pwr);
    }
}

/*===========================================================================
FUNCTION usb_isr_usbphy_enable

DESCRIPTION
  Enable/disable USB PHY IRQ using Zephyr API

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.
===========================================================================*/
void usb_isr_usbphy_enable(boolean enable)
{
    if (g_isr_ctx == NULL)
        return;
        
    if (enable)
    {
        irq_enable(g_isr_ctx->irq_phy);
    }
    else
    {
        irq_disable(g_isr_ctx->irq_phy);
    }
}

/*===========================================================================
FUNCTION usb_isr_ee_init

DESCRIPTION
  Initialize device event IRQ with Zephyr

DEPENDENCIES
  None.

RETURN VALUE
  TRUE for success, FALSE for failure

SIDE EFFECTS
  None.
===========================================================================*/
boolean usb_isr_ee_init(usb_isr_ctx_t* isr_ctx)
{
    int ret;
    
    USB_ASSERT(isr_ctx);
    g_isr_ctx = isr_ctx;
    
    /* Initialize event queue */
    usb_fn_isr()->usb_event_queue_init(&isr_ctx->ee_dsr_queue, 
                                       EVENT_BUFFER_SIZE/sizeof(usb_event_t));
    
    /* Initialize polling flags */
    isr_ctx->pending_events = USB_EVENT_FLAG_NONE;
    
    /* Get IRQ number from device tree or use hardcoded value */
#if DT_NODE_EXISTS(USB_DWC3_NODE)
    isr_ctx->irq_ee1 = DT_IRQN_BY_NAME(USB_DWC3_NODE, dwc3_ee1);
#else
    isr_ctx->irq_ee1 = USB_CTRL_EE1_IRQ;
#endif
    
    /* Connect IRQ using Zephyr API */
    ret = irq_connect_dynamic(isr_ctx->irq_ee1,
                              2,  /* Priority */
                              usb_isr_ee1_zephyr_handler,
                              isr_ctx,
                              0);  /* Flags */
    
    if (ret < 0)
    {
        USB_LOG_ERR_1(log_usb_ee_pwr_init__failed_to_reg_interrupt_D, isr_ctx->irq_ee1);
        return FALSE;
    }
    
    return TRUE;
}

/*===========================================================================
FUNCTION usb_isr_pwr_init

DESCRIPTION
  Initialize power event IRQ with Zephyr

DEPENDENCIES
  None.

RETURN VALUE
  TRUE for success, FALSE for failure

SIDE EFFECTS
  None.
===========================================================================*/
boolean usb_isr_pwr_init(usb_isr_ctx_t* isr_ctx)
{
    int ret;
    
    USB_ASSERT(isr_ctx);
    
    /* Initialize event queue */
    usb_fn_isr()->usb_event_queue_init(&isr_ctx->pwr_dsr_queue, USB_PWR_DSR_QUEUE_SIZE);
    
    /* Get IRQ numbers from device tree or use hardcoded values */
#if DT_NODE_EXISTS(USB_DWC3_NODE)
    isr_ctx->irq_pwr = DT_IRQN_BY_NAME(USB_DWC3_NODE, dwc3_pwr);
    isr_ctx->irq_phy = DT_IRQN_BY_NAME(USB_DWC3_NODE, dwc3_phy);
#else
    isr_ctx->irq_pwr = USB_CTRL_POWER_EVENT_IRQ;
    isr_ctx->irq_phy = USB_CTRL_HSPHY_IRQ;
#endif
    
    /* Connect power event IRQ */
    ret = irq_connect_dynamic(isr_ctx->irq_pwr,
                              2,  /* Priority */
                              usb_isr_pwr_zephyr_handler,
                              isr_ctx,
                              0);  /* Flags */
    
    if (ret < 0)
    {
        USB_LOG_ERR_1(log_usb_isr_pwr_init__failed_to_reg_interrupt_D, isr_ctx->irq_pwr);
        return FALSE;
    }
    
    /* Connect PHY event IRQ */
    ret = irq_connect_dynamic(isr_ctx->irq_phy,
                              2,  /* Priority */
                              usb_isr_hsphy_zephyr_handler,
                              isr_ctx,
                              0);  /* Flags */
    
    if (ret < 0)
    {
        USB_LOG_ERR_1(log_usb_isr_pwr_init__failed_to_reg_interrupt_D, isr_ctx->irq_phy);
        return FALSE;
    }
    
    /* Initialize VBUS GPIO if available */
#if DT_NODE_EXISTS(VBUS_GPIO_NODE)
    isr_ctx->vbus_gpio = GPIO_DT_SPEC_GET(VBUS_GPIO_NODE, gpios);
    
    if (device_is_ready(isr_ctx->vbus_gpio.port))
    {
        ret = gpio_pin_configure_dt(&isr_ctx->vbus_gpio, GPIO_INPUT);
        if (ret == 0)
        {
            ret = gpio_pin_interrupt_configure_dt(&isr_ctx->vbus_gpio,
                                                   GPIO_INT_EDGE_BOTH);
            if (ret == 0)
            {
                gpio_init_callback(&isr_ctx->vbus_cb_data,
                                   usb_isr_vbus_gpio_callback,
                                   BIT(isr_ctx->vbus_gpio.pin));
                gpio_add_callback(isr_ctx->vbus_gpio.port, &isr_ctx->vbus_cb_data);
            }
        }
    }
#endif
    
    return TRUE;
}

/*===========================================================================
FUNCTION usb_isr_ee_uninit

DESCRIPTION
  Deinitialize device event IRQ

DEPENDENCIES
  None.

RETURN VALUE
  0 for success, error code otherwise

SIDE EFFECTS
  None.
===========================================================================*/
uint32 usb_isr_ee_uninit(usb_isr_ctx_t* isr_ctx)
{
    USB_ASSERT(isr_ctx);
    
    /* Disable IRQ */
    irq_disable(isr_ctx->irq_ee1);
    
    /* Free event queue */
    if (NULL != (isr_ctx->ee_dsr_queue).dsr_save_event)
    {
        usb_fn_isr()->usb_event_queue_uninit(&(isr_ctx->ee_dsr_queue));
    }
    
    g_isr_ctx = NULL;
    return USB_SUCCESS;
}

/*===========================================================================
FUNCTION usb_isr_pwr_uninit

DESCRIPTION
  Deinitialize power event IRQ

DEPENDENCIES
  None.

RETURN VALUE
  0 for success, error code otherwise

SIDE EFFECTS
  None.
===========================================================================*/
uint32 usb_isr_pwr_uninit(usb_isr_ctx_t* isr_ctx)
{
    USB_ASSERT(isr_ctx);
    
    /* Disable IRQs */
    irq_disable(isr_ctx->irq_pwr);
    irq_disable(isr_ctx->irq_phy);
    
    /* Remove VBUS GPIO callback if configured */
#if DT_NODE_EXISTS(VBUS_GPIO_NODE)
    if (device_is_ready(isr_ctx->vbus_gpio.port))
    {
        gpio_remove_callback(isr_ctx->vbus_gpio.port, &isr_ctx->vbus_cb_data);
    }
#endif
    
    /* Free event queue */
    if (NULL != (isr_ctx->pwr_dsr_queue).dsr_save_event)
    {
        usb_fn_isr()->usb_event_queue_uninit(&isr_ctx->pwr_dsr_queue);
    }
    
    return USB_SUCCESS;
}

/*===========================================================================
FUNCTION usb_poll_events

DESCRIPTION
  Main polling function to be called from application main loop.
  Processes all pending USB events queued by ISRs.

DEPENDENCIES
  Must be called periodically from main loop.

RETURN VALUE
  None

SIDE EFFECTS
  Clears pending_events flags as events are processed.
===========================================================================*/
void usb_poll_events(usb_isr_ctx_t* isr_ctx)
{
    uint32 events;
    
    if (!isr_ctx)
        return;
    
    /* Read and clear pending events atomically */
    unsigned int key = irq_lock();
    events = isr_ctx->pending_events;
    isr_ctx->pending_events = USB_EVENT_FLAG_NONE;
    irq_unlock(key);
    
    /* Process device events */
    if (events & USB_EVENT_FLAG_DEVICE)
    {
        usb_fn_isr()->usb_dsr_handle_ee_event(isr_ctx);
    }
    
    /* Process power events */
    if (events & USB_EVENT_FLAG_POWER)
    {
        usb_fn_isr()->usb_dsr_handle_pwr_event(isr_ctx);
    }
    
    /* Process VBUS events */
    if (events & USB_EVENT_FLAG_VBUS)
    {
        if (isr_ctx->vbus_handle)
        {
            isr_ctx->vbus_handle(isr_ctx->vbus_state);
        }
    }
    
    /* Process PHY events */
    if (events & USB_EVENT_FLAG_PHY)
    {
        /* PHY event processing if needed */
    }
}
```

### Step 4: Update CMakeLists.txt

Add the new Zephyr IRQ implementation file:

```cmake
zephyr_library_sources(
    # ... existing files ...
    src/dci/usb_isr.c
    src/dci/usb_isr_zephyr.c  # Add this line
    # ... rest of files ...
)
```

### Step 5: Application Main Loop Integration

Update your main application loop to call the polling function:

```c
/* In your main application file */

#include "usb_isr.h"

extern usb_isr_ctx_t* g_usb_isr_ctx;  /* Defined in usb_al_zephyr.c */

int main(void)
{
    /* Initialize USB stack */
    usb_zephyr_init();
    
    /* Main application loop */
    while (1)
    {
        /* Poll USB events - call this frequently */
        usb_poll_events(g_usb_isr_ctx);
        
        /* Your other application tasks */
        /* ... */
        
        /* Optional: small delay to prevent busy-waiting */
        k_msleep(1);  /* Or k_yield() */
    }
    
    return 0;
}
```

### Alternative: Integrate with Existing Polling

If you already have `usb_dci_poll_events()` being called:

```c
/* In usb_dci.c or usb_al_zephyr.c */

void usb_dci_poll_events(usb_dci_ctx_t* dci_ctx)
{
    /* First, process any ISR-queued events */
    if (dci_ctx && dci_ctx->isr_ctx)
    {
        usb_poll_events((usb_isr_ctx_t*)dci_ctx->isr_ctx);
    }
    
    /* Then continue with existing hardware polling */
    /* ... existing code ... */
}
```

## Testing Strategy

### Phase 1: Basic IRQ Registration
1. Verify IRQ numbers from device tree
2. Test IRQ connect/disconnect
3. Verify IRQ enable/disable
4. Confirm ISRs are called

### Phase 2: Event Queueing
1. Test event enqueue from ISR
2. Verify flags are set correctly
3. Test atomic flag operations
4. Verify queue doesn't overflow

### Phase 3: Polling Integration
1. Test `usb_poll_events()` processes queued events
2. Verify DSR handlers are called
3. Test with multiple pending events
4. Verify no events are lost

### Phase 4: VBUS Detection
1. Test VBUS GPIO interrupt
2. Verify attach/detach detection
3. Test polling processes VBUS events
4. Test power management integration

### Phase 5: Integration Testing
1. Full enumeration test
2. Data transfer test
3. Suspend/resume test
4. Stress test with rapid interrupts

## Key Considerations

### 1. ISR Context Safety
- ISRs only enqueue events and set flags
- Minimal work in ISR context
- Use `irq_lock()`/`irq_unlock()` for atomic flag access
- All heavy processing in main loop context

### 2. Polling Frequency
- Call `usb_poll_events()` frequently (every 1-10ms)
- Balance between responsiveness and CPU usage
- Consider USB timing requirements (e.g., control transfer timeouts)

### 3. Priority Configuration
- Device events: Priority 2 (high)
- Power events: Priority 2 (high)
- PHY events: Priority 2 (high)
- VBUS GPIO: Priority 3 (medium)

### 4. Event Queue Sizing
- Size queues to handle burst interrupts
- Monitor queue usage during testing
- Adjust `EVENT_BUFFER_SIZE` if needed

### 5. Power Management
- Disable IRQs during suspend
- Re-enable IRQs on resume
- Handle VBUS removal gracefully
- Consider wake-up sources

## Migration Checklist

- [ ] Create device tree bindings for USB controller
- [ ] Add VBUS GPIO configuration to device tree
- [ ] Implement Zephyr IRQ registration functions
- [ ] Replace all `CPEInterruptController_*` calls
- [ ] Update enable/disable functions with `irq_enable()`/`irq_disable()`
- [ ] Add VBUS GPIO interrupt handler
- [ ] Implement `usb_poll_events()` function
- [ ] Integrate polling into main loop or existing poll function
- [ ] Test basic IRQ functionality
- [ ] Test event queueing and polling
- [ ] Test VBUS detection
- [ ] Perform integration testing
- [ ] Optimize polling frequency
- [ ] Update documentation

## Performance Optimization

### Polling Frequency Guidelines

```c
/* High-performance mode - frequent polling */
while (1) {
    usb_poll_events(isr_ctx);
    /* Other tasks */
    k_yield();  /* Yield to other threads if any */
}

/* Balanced mode - periodic polling */
while (1) {
    usb_poll_events(isr_ctx);
    /* Other tasks */
    k_msleep(1);  /* 1ms polling interval */
}

/* Low-power mode - less frequent polling */
while (1) {
    usb_poll_events(isr_ctx);
    /* Other tasks */
    k_msleep(5);  /* 5ms polling interval */
}
```

### Event Queue Monitoring

```c
/* Add to usb_poll_events() for debugging */
void usb_poll_events(usb_isr_ctx_t* isr_ctx)
{
    uint32 ee_queue_cnt = usb_fn_isr()->usb_event_queue_cnt(&isr_ctx->ee_dsr_queue);
    uint32 pwr_queue_cnt = usb_fn_isr()->usb_event_queue_cnt(&isr_ctx->pwr_dsr_queue);
    
    /* Log if queues are getting full */
    if (ee_queue_cnt > (EVENT_BUFFER_SIZE * 3 / 4))
    {
        USB_LOG_WARN("Device event queue nearly full");
    }
    
    /* ... rest of function ... */
}
```

## Conclusion

This single-threaded integration guide provides a complete roadmap for adding Zephyr IRQ support without using threads. The key principles are:

1. **ISRs do minimal work**: Only queue events and set flags
2. **Main loop processes events**: Call `usb_poll_events()` periodically
3. **Event queues buffer bursts**: Handle multiple interrupts between polls
4. **Atomic flag operations**: Use `irq_lock()`/`irq_unlock()` for safety
5. **Device tree configuration**: Hardware-independent IRQ setup
6. **Flexible polling frequency**: Adjust based on performance needs

This architecture is ideal for:
- Single-core systems
- Applications with existing main loops
- Systems where thread overhead is undesirable
- Real-time systems with deterministic behavior

The implementation preserves the existing event queue architecture while adding proper Zephyr IRQ support for all USB-related interrupts including VBUS, device events, power events, and PHY events.
