#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/irq.h>
#include "usb_isr.h"
#include "usb_dci.h"
 #include "usb_common.h"
#include "usb_util.h"
//#include "led.h" 
#include "usb_log.h"
#include "usb_hwio_9410.h"
#include "usb_dci_9410.h"


/* Get device tree node */
//TODO: Add DT support
//#define USB_DWC3_NODE DT_NODELABEL(usb_dwc3)
//#define VBUS_GPIO_NODE DT_PATH(vbus_detect, vbus_gpio)

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
void usb_isr_poll_events(usb_isr_ctx_t* isr_ctx)
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

/*===========================================================================
FUNCTION usb_isr_init

DESCRIPTION
Initializes a USB core's interrupt. Inital the event buffer for usb_dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
  uint32 return 0 Success
         return 1 Fail

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_isr_init(usb_isr_ctx_t* isr_ctx)
{
  USB_ASSERT(isr_ctx);

#ifdef USB_KW_CONST_RESULT
    //condition always yield the same result and causes an unreachable code 
  if (FALSE == usb_fn_isr()->usb_isr_ee_init(isr_ctx))
  {
    return USB_ERR_UNKNOWN;
  }
  if (FALSE == usb_fn_isr()->usb_isr_pwr_init(isr_ctx))
  {
    return USB_ERR_UNKNOWN;
  }
#else
  usb_fn_isr()->usb_isr_ee_init(isr_ctx);
  usb_fn_isr()->usb_isr_pwr_init(isr_ctx);
#endif
  return USB_SUCCESS;//eRes;//HSU_JSUCCESS;
}  /* hsu_os_bus_interrupt_init */

/*===========================================================================
FUNCTION usb_isr_uninit

DESCRIPTION
Deregister all usb ISR (EE1+ pwr_isr)

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_isr_uninit(usb_isr_ctx_t* isr_ctx)
{
  uint32 error_value=USB_SUCCESS ;
  USB_ASSERT(isr_ctx);
#ifdef USB_KW_CONST_RESULT
    //condition always yield the same result and causes an unreachable code   
  error_value = usb_fn_isr()->usb_isr_ee_uninit(isr_ctx);
  if (error_value)
  {
    return error_value;
  }  
  
  error_value = usb_fn_isr()->usb_isr_pwr_uninit(isr_ctx);
  if (error_value)
  {
    return error_value;
  }  
#else
  usb_fn_isr()->usb_isr_ee_uninit(isr_ctx);
  usb_fn_isr()->usb_isr_pwr_uninit(isr_ctx);
#endif
  return error_value;
}

/*===========================================================================
FUNCTION usb_event_queue_init

DESCRIPTION
Create usb dsr event buffer.

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer
  uint32 size: number of event

RETURN VALUE
 none
 
SIDE EFFECTS
None.
===========================================================================*/
void usb_event_queue_init(usb_event_queue_t* q_ctx, uint32 size)
{
  USB_ASSERT(q_ctx && (size != 0));

  USB_ASSERT(q_ctx->dsr_save_event = 
    (usb_event_t*) usb_fn_mem_util()->usb_malloc((size + 1) * USB_EVT_BUFFER_UNIT_SIZE));

  q_ctx->dsr_event_read_idx  = size;
  q_ctx->dsr_event_write_idx = 0;
  q_ctx->size = size + 1;
  q_ctx->cnt = 0;
}

/*===========================================================================
FUNCTION usb_event_queue_uninit

DESCRIPTION
Destory the usb_dsr buffer

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer

RETURN VALUE
 none

SIDE EFFECTS
None.
===========================================================================*/
void usb_event_queue_uninit(usb_event_queue_t* q_ctx)
{
  USB_ASSERT(q_ctx);
  usb_fn_mem_util()->usb_free((void**)&q_ctx->dsr_save_event);
}

/*===========================================================================
FUNCTION usb_event_enqueue

DESCRIPTION
Enqueue usb_buffer

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer
  uint32 usb_event

RETURN VALUE
  TRUE for success.
  FLASE for FAIL.

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_event_enqueue(usb_event_queue_t* q_ctx, uint32 new_data)
{
  USB_ASSERT(q_ctx);

  if (q_ctx->dsr_event_write_idx == q_ctx->dsr_event_read_idx)
  {
    //USB_LOG_ERR_1(log_usb_event_enqueue__queue_full_D, (uint32)queue_ctx->cnt);
    return FALSE;
  }
  q_ctx->dsr_save_event[q_ctx->dsr_event_write_idx].generic= new_data;
  q_ctx->dsr_event_write_idx = (q_ctx->dsr_event_write_idx + 1) % q_ctx->size;
  q_ctx->cnt++;
  return TRUE;
}

/*===========================================================================
FUNCTION usb_event_dequeue

DESCRIPTION
Dequeue usb_buffer. It disable usb_isr

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer
  uint32* usb_event

RETURN VALUE
  TRUE for success.
  FLASE for FAIL.

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_event_dequeue( usb_event_queue_t* q_ctx, uint32* old_data)
{
  uint32 local_rd_idx;
  USB_ASSERT(q_ctx && old_data);

  local_rd_idx = (q_ctx->dsr_event_read_idx + 1) % q_ctx->size;

  if (local_rd_idx == q_ctx->dsr_event_write_idx)
  {
    USB_LOG_ERR_1(log_usb_event_dequeue__queue_empty_D, (uint32)q_ctx);
    return FALSE;
  }

  *old_data = q_ctx->dsr_save_event[local_rd_idx].generic;
  q_ctx->dsr_event_read_idx = local_rd_idx;
  q_ctx->cnt--;

  return TRUE;
}

/*===========================================================================
FUNCTION usb_event_queue_cnt

DESCRIPTION
  return the number of event in queue
  Disable when reading cnt
  
DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer

RETURN VALUE
  uint32 Number of events in the queue

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_event_queue_cnt(usb_event_queue_t* q_ctx)
{
  USB_ASSERT(q_ctx);
  return q_ctx->cnt;
}

/*===========================================================================
FUNCTION usb_isr_enable

DESCRIPTION
Enable/disable the all usb_isr (only usb isr)

INPUT
  boolean enable; to enable to disable usb isr
DEPENDENCIES
None.

RETURN VALUE
None.

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_enable(usb_isr_ctx_t* isr_ctx, boolean enable)
{
  usb_fn_isr()->usb_isr_ee_enable(enable);
  usb_fn_isr()->usb_isr_pwr_enable(enable);
}

/*===========================================================================
FUNCTION usb_isr_enqueue_ee_event

DESCRIPTION
This is call from usb_isr_ee1_handle. To enqueue usb event to dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
 TRUE for success.
 FLASE for FAIL.

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_isr_enqueue_ee_event(usb_isr_ctx_t* isr_ctx)
{
  uint32 evt_byte_count;
  uint32 cur_buf_pos;
  usb_dci_ctx_t* dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  USB_ASSERT(dci_ctx);

  /* Get the event count  ( number of valid bytes ) from the event buffer - SNPS 6.2.7.3 */
  evt_byte_count = HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INMI(0,
     HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK);

  if (!evt_byte_count)
  {
    //USB_ULOG(DBG_E_QLOG, "interrupt WITHOUT event!");
    //USB_LOG_ERR(log_usb_isr_enqueue_ee_event__no_event);
    return FALSE;
  }

  while (evt_byte_count > 0) 
  {
    usb_event_t event;
    /* position of the event to be handled in the current event buffer */
    cur_buf_pos = dci_ctx->usb_evt_buf_info.cur_pos;
  
        /* Move the event buffer to the new location */
    event.generic = *(volatile uint32 *)((uint8 *)(dci_ctx->usb_evt_buf_info.buf) + cur_buf_pos );

    if (FALSE == usb_fn_isr()->usb_event_enqueue(&isr_ctx->ee_dsr_queue, event.generic))
    {
      //USB_ULOG_1(DBG_E_QLOG, "enqueue_fail, queue_ptr 0x%X", (uint32)&isr_ctx->ee_dsr_queue);    
      return FALSE;
    }
    *(volatile uint32 *)((uint8 *)dci_ctx->usb_evt_buf_info.buf + cur_buf_pos) = event.generic | 0xFF000000;
    //USB_LOG_DBG_2(log_usb_isr_enqueue_ee_event__event_cnt_D__event_D, usb_event_queue_cnt(&isr_ctx->ee_dsr_queue), event.generic);
    //USB_ULOG_3(ENG_QLOG, "Save Events - 0x%x, write_idx %u, cnt %u", event.generic, isr_ctx->ee_dsr_queue.dsr_event_write_idx, isr_ctx->ee_dsr_queue.cnt);

      /* Move to the next Event in the current buffer */
      /* Event buffer is 1K in size and each Event entry is 4 bytes long. We wrap at 1K. */
      /* Wrap the circular buffer at EVENT_BUFFER_SIZE to ensure there is no overflow */
    dci_ctx->usb_evt_buf_info.cur_pos = (cur_buf_pos + USB_EVT_BUFFER_UNIT_SIZE ) % EVENT_BUFFER_SIZE ;
    evt_byte_count -= USB_EVT_BUFFER_UNIT_SIZE;

    /* SW indicates to HW how many events it processed by writing the byte count (we process 4 at a time ) */
    HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OUTMI(0,
            HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK,
            USB_EVT_BUFFER_UNIT_SIZE << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_SHFT );

  }
  return TRUE;
}


/*===========================================================================
FUNCTION usb_dsr_handle_ee_event

DESCRIPTION
this function is called in usb_thread to get the usb event from dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
  uint32 return 0 for successful
         return 1 for Fail
  

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_dsr_handle_ee_event(usb_isr_ctx_t* isr_ctx)
{
  /* EP specific Event */
  usb_event_t event_arr[USB_EVENT_AGGR_CNT];
  uint8 event_arr_size;
  uint8 i;
  uint32 event_cnt;
  usb_dci_ctx_t* dci_ctx;

  USB_ASSERT(isr_ctx && isr_ctx->dci_ctx);
  dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  event_cnt = usb_fn_isr()->usb_event_queue_cnt(&isr_ctx->ee_dsr_queue);
  while (event_cnt != 0)
  {
    usb_fn_isr()->usb_isr_ee_enable(FALSE);
    event_arr_size = MIN(event_cnt, USB_EVENT_AGGR_CNT);
    for(i=0; i < event_arr_size; i++)
    {
      if(FALSE == usb_fn_isr()->usb_event_dequeue(&isr_ctx->ee_dsr_queue, (uint32*)&event_arr[i]))
    {
        event_arr_size = i+1;
        break;
      }
    }

    usb_fn_isr()->usb_isr_ee_enable(TRUE);

    usb_mips_start(usb_mips__usb_handle_events);

    for(i=0; i < event_arr_size; i++)
    {
      if(event_arr[i].depevt.event_type == USB_EVT_TYPE_EP)
      {
        usb_fn_dci()->usb_dci_handle_ep_event(dci_ctx, &event_arr[i].depevt);
      }
      else if(event_arr[i].devt.event_type == USB_EVT_TYPE_NON_EP && !(event_arr[i].devt.dev_spec_event) )
      {
      /* Dev specific Event  */
      /* Event type should be "Non Ep'' and bits-7:1  should be Zero ( SNPS pg. 478, Table-649 ) */
        usb_fn_dci()->usb_dci_handle_dev_event(dci_ctx, &event_arr[i].devt);
      }
      else
      {
        USB_LOG_ERR_1(log_usb_dsr_handle_ee_event__unknown_event_D, event_arr[i].devt.dev_spec_event);
      }
      event_cnt--;
    }
    usb_mips_stop(usb_mips__usb_handle_events);
  }

  return 0;
}


/*===========================================================================
FUNCTION usb_dsr_handle_pwr_event

DESCRIPTION
this function is called in usb_thread to get the usb event from dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
  uint32 return 0 for successful
         return 1 for Fail
  

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_dsr_handle_pwr_event(usb_isr_ctx_t* isr_ctx)
{
  uint32 event_cnt;
  usb_dci_ctx_t* dci_ctx;
  uint32 pwr_event;
  USB_ASSERT(isr_ctx && isr_ctx->dci_ctx);
  dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  event_cnt = usb_fn_isr()->usb_event_queue_cnt(&isr_ctx->pwr_dsr_queue);
  while (event_cnt != 0)
  {
    usb_fn_isr()->usb_isr_pwr_enable(FALSE);
    if(FALSE == usb_fn_isr()->usb_event_dequeue(&isr_ctx->pwr_dsr_queue, (uint32*)&pwr_event))
    {
      usb_fn_isr()->usb_isr_pwr_enable(TRUE);
      return 1;
    }
    usb_fn_isr()->usb_isr_pwr_enable(TRUE);
    //USB_LOG_1(log_usb_dsr_handle_pwr_event__pwr_event_D, pwr_event);
    event_cnt--;
    usb_fn_dci()->usb_dci_handle_event(dci_ctx, pwr_event);
  }
  return 0;
}

//----------------------------------------------------------------------------
// Function table definition
//----------------------------------------------------------------------------

usb_fn_tbl_isr_t fn_tbl_isr = 
{
  usb_event_queue_init,
  usb_event_queue_uninit,
  usb_event_enqueue,
  usb_event_dequeue,
  usb_event_queue_cnt,
  usb_isr_ee_enable,
  usb_isr_usbphy_enable,
  usb_isr_pwr_enable,
  usb_isr_enable,
  NULL, //usb_isr_ee1_handle,
  NULL, //usb_isr_pwr_handle,
  NULL, //usb_isr_hsphy_handle,
  NULL, //usb_isr_dpse_handle,
  NULL, //usb_isr_lpm_init,
  usb_isr_ee_init,
  usb_isr_pwr_init,
  usb_isr_ee_uninit,
  usb_isr_pwr_uninit,
  usb_isr_init,
  usb_isr_uninit,
  usb_isr_enqueue_ee_event,
  usb_dsr_handle_ee_event,
  usb_dsr_handle_pwr_event,
  usb_isr_poll_events,
};
