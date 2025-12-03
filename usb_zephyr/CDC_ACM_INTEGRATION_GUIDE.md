# USB CDC-ACM Serial Driver Integration Guide

## Overview

This document provides a complete guide for integrating and using the USB CDC-ACM (Communications Device Class - Abstract Control Model) serial driver in your custom USB stack.

## Table of Contents

1. [Architecture Overview](#architecture-overview)
2. [Files Added](#files-added)
3. [Integration Steps](#integration-steps)
4. [Usage Example](#usage-example)
5. [Testing](#testing)
6. [Troubleshooting](#troubleshooting)

---

## Architecture Overview

### CDC-ACM Class Structure

CDC-ACM uses **two interfaces**:

1. **Control Interface (Communication Class)**
   - Interface Class: 0x02 (CDC)
   - Interface SubClass: 0x02 (ACM)
   - Contains:
     - 1 Interrupt IN endpoint (for notifications)
     - CDC functional descriptors (Header, ACM, Union, Call Management)

2. **Data Interface (Data Class)**
   - Interface Class: 0x0A (CDC-Data)
   - Contains:
     - 1 Bulk IN endpoint (device to host)
     - 1 Bulk OUT endpoint (host to device)

### Integration with Custom Stack

```
Application Layer
    ↓
USB API Layer (usb_api.h)
    ↓
Function Driver Layer (usb_fd.c)
    ↓
CDC-ACM Function Driver (usb_cdc_acm_fd.c)
    ↓
Device Class Driver (usb_dcd.c)
    ↓
Device Controller Interface (usb_dci.c)
    ↓
Hardware (DWC3 Controller)
```

---

## Files Added

### 1. Header File
**Location:** `battman/usb/usb_zephyr/inc/usb_cdc_acm_fd.h`

Defines:
- CDC-ACM context structure
- Function table for CDC-ACM operations
- CDC class codes and endpoint configurations

### 2. Implementation File
**Location:** `battman/usb/usb_zephyr/src/func/usb_cdc_acm_fd.c`

Implements:
- Descriptor allocation (control + data interfaces)
- CDC functional descriptors (Header, ACM, Union, Call Management)
- Class-specific request handling (SET_LINE_CODING, GET_LINE_CODING, SET_CONTROL_LINE_STATE)
- Speed notification handling
- Configuration callbacks

### 3. Example Application
**Location:** `battman/usb/usb_zephyr/examples/usb_cdc_acm_example.c`

Demonstrates:
- CDC-ACM initialization
- Client registration
- Data transmission and reception
- Event handling

---

## Integration Steps

### Step 1: Update Common Header

**File:** `battman/usb/usb_zephyr/inc/usb_common.h`

Add CDC interface IDs to the `usb_ifc_id` enum:

```c
typedef enum
{
  USB_IFC_ID_BULK,
  USB_IFC_ID_CDC_CONTROL,    // Added
  USB_IFC_ID_CDC_DATA,        // Added
  USB_IFC_ID_AUDIO_CONTROL,
  // ... rest of interfaces
} usb_ifc_id;
```

### Step 2: Register CDC-ACM in Function Driver

**File:** `battman/usb/usb_zephyr/src/func/usb_fd.c`

The CDC-ACM handler is already integrated in `usb_fd_init()`:

```c
case USB_IFC_ID_CDC_CONTROL:
{
  ifc_ctx->fn_class.init = usb_fn_cdc()->usb_cdc_acm_init;
  ifc_ctx->fn_class.alloc_desc = usb_fn_cdc()->usb_cdc_acm_alloc_desc;
  ifc_ctx->fn_class.set_cfg = usb_fn_cdc()->usb_cdc_acm_set_cfg;
  ifc_ctx->fn_class.handle_set_req = usb_fn_cdc()->usb_cdc_acm_handle_class_req;
  ifc_ctx->fn_class.handle_get_req = usb_fn_cdc()->usb_cdc_acm_handle_class_req;
  ifc_ctx->fn_class.deinit = usb_fn_cdc()->usb_cdc_acm_deinit; 
  ifc_ctx->fn_class.notify_speed = usb_fn_cdc()->usb_cdc_acm_notify_speed;
  ifc_ctx->fn_class.ctx = ifc_ctx->fn_class.init(ifc_id, ifc_index, NULL);
}
break;

case USB_IFC_ID_CDC_DATA:
{
  /* CDC Data interface shares context with Control interface */
  if (ifc_index > 0 && fd_ctx->ifc_ctx[ifc_index - 1].ifc_id == USB_IFC_ID_CDC_CONTROL) {
    ifc_ctx->fn_class.ctx = fd_ctx->ifc_ctx[ifc_index - 1].fn_class.ctx;
    ifc_ctx->fn_class.set_cfg = usb_fn_cdc()->usb_cdc_acm_set_cfg;
    ifc_ctx->fn_class.notify_speed = usb_fn_cdc()->usb_cdc_acm_notify_speed;
  }
}
break;
```

### Step 3: Build Configuration

**File:** `battman/usb/usb_zephyr/CMakeLists.txt`

Ensure CDC-ACM source files are included:

```cmake
target_sources(usb_zephyr PRIVATE
    src/func/usb_fd.c
    src/func/usb_cdc_acm_fd.c  # Add this line
    # ... other sources
)
```

---

## Usage Example

### Basic CDC-ACM Application

```c
#include "usb_api.h"
#include "usb_common.h"

/* Define USB composition with CDC-ACM */
usb_ifc_id usb_composition[2] = {
    USB_IFC_ID_CDC_CONTROL,
    USB_IFC_ID_CDC_DATA
};

/* Configure device */
usb_audio_dev_config_t dev_cfg = {
    .vendor_id = 0x05C6,           /* Qualcomm VID */
    .product_id = 0x9091,          /* CDC-ACM PID */
    .usb_comp = usb_composition,
    .usb_comp_num_ifc = 2,
    .op_mode = USB_OP_MODE_MISSION,
    .lang_id = 0x0409,             /* English (US) */
    .manuf_str = (uint8_t*)"Qualcomm",
    .product_str = (uint8_t*)"CDC-ACM Serial"
};

/* RX callback - called when data received from host */
void cdc_rx_callback(uint8_t* buffer, uint32_t length, 
                     uint32_t status, void* cb_data)
{
    if (status == USB_REQ_COMPLETE_OK) {
        /* Process received data */
        process_data(buffer, length);
        
        /* Queue next RX buffer */
        usb_send_rx(next_buffer, buffer_size, req_id, client_id, NULL);
    }
}

/* TX callback - called when data sent to host */
void cdc_tx_callback(uint8_t* buffer, uint32_t length,
                     uint32_t status, void* cb_data)
{
    if (status == USB_REQ_COMPLETE_OK) {
        /* TX complete - buffer can be reused */
    }
}

/* Event callback - called for USB events */
void cdc_event_callback(uint32_t event, void* data)
{
    switch(event) {
        case USB_EVENT_ENABLED:
            /* USB enumeration complete */
            /* Start receiving data */
            usb_send_rx(rx_buffer, RX_SIZE, 0, 0, NULL);
            break;
            
        case USB_EVENT_DISCONNECT:
            /* USB disconnected */
            break;
    }
}

/* Initialize CDC-ACM */
int init_cdc_acm(void)
{
    client_ctx_t cdc_client;
    
    /* Set USB parameters */
    usb_set_params(&dev_cfg);
    
    /* Register CDC Control interface client */
    cdc_client.ifc_id = USB_IFC_ID_CDC_CONTROL;
    cdc_client.client_id = 0;
    cdc_client.app_rx_cb_func = cdc_rx_callback;
    cdc_client.app_tx_cb_func = cdc_tx_callback;
    cdc_client.app_event_cb_func = cdc_event_callback;
    usb_alloc_register_client_ctx(&cdc_client);
    
    /* Register CDC Data interface client */
    cdc_client.ifc_id = USB_IFC_ID_CDC_DATA;
    cdc_client.client_id = 1;
    cdc_client.app_event_cb_func = NULL;  /* Events on control interface */
    usb_alloc_register_client_ctx(&cdc_client);
    
    return 0;
}

/* Send data to host */
int send_data(const uint8_t* data, uint32_t length)
{
    return usb_send_tx((uint8_t*)data, length, 0, 1, NULL);
}
```

---

## Testing

### 1. Windows Testing

1. **Connect Device**
   - Windows will automatically install CDC-ACM driver
   - Device appears as "USB Serial Device" in Device Manager

2. **Open Serial Port**
   ```
   - Use PuTTY, TeraTerm, or any serial terminal
   - Baud rate: 115200 (or as configured)
   - Data bits: 8
   - Parity: None
   - Stop bits: 1
   ```

3. **Test Communication**
   - Type characters in terminal
   - Should see echo if echo is implemented
   - Check for data transmission/reception

### 2. Linux Testing

1. **Check Device**
   ```bash
   # Device should appear as /dev/ttyACM0
   dmesg | grep tty
   ls -l /dev/ttyACM*
   ```

2. **Open Serial Port**
   ```bash
   # Using screen
   screen /dev/ttyACM0 115200
   
   # Using minicom
   minicom -D /dev/ttyACM0 -b 115200
   
   # Using cat/echo
   cat /dev/ttyACM0 &
   echo "Hello" > /dev/ttyACM0
   ```

3. **Check USB Descriptors**
   ```bash
   lsusb -v -d 05c6:9091
   ```

### 3. macOS Testing

1. **Check Device**
   ```bash
   ls -l /dev/cu.usbmodem*
   ```

2. **Open Serial Port**
   ```bash
   screen /dev/cu.usbmodem14101 115200
   ```

---

## Troubleshooting

### Issue 1: Device Not Enumerated

**Symptoms:**
- Device not recognized by host
- No COM port appears

**Solutions:**
1. Check USB cable connection
2. Verify VID/PID configuration
3. Check descriptor generation:
   ```c
   /* Enable USB logging */
   USB_LOG_LEVEL = LOG_LEVEL_DBG;
   ```
4. Verify both interfaces are registered

### Issue 2: Data Not Received

**Symptoms:**
- Device enumerates but no data received
- RX callback not called

**Solutions:**
1. Ensure RX buffers are queued:
   ```c
   usb_send_rx(buffer, size, req_id, client_id, NULL);
   ```
2. Check endpoint configuration
3. Verify bulk OUT endpoint is enabled
4. Check for USB errors in logs

### Issue 3: Data Not Transmitted

**Symptoms:**
- TX callback not called
- Data not appearing on host

**Solutions:**
1. Check USB connection status
2. Verify TX buffer is valid
3. Check bulk IN endpoint configuration
4. Ensure device is configured (enumeration complete)

### Issue 4: Class Requests Failing

**Symptoms:**
- SET_LINE_CODING fails
- GET_LINE_CODING returns wrong data

**Solutions:**
1. Check `usb_cdc_acm_handle_class_req()` implementation
2. Verify buffer sizes for line coding structure
3. Check request direction (IN vs OUT)
4. Enable class request logging

### Issue 5: Multiple Interfaces Not Working

**Symptoms:**
- Only one interface appears
- Data interface missing

**Solutions:**
1. Verify both interfaces are in composition:
   ```c
   usb_composition[0] = USB_IFC_ID_CDC_CONTROL;
   usb_composition[1] = USB_IFC_ID_CDC_DATA;
   ```
2. Check interface association descriptor (IAD)
3. Verify `usb_comp_num_ifc = 2`

---

## CDC-ACM Class Requests

The driver handles these standard CDC-ACM requests:

### SET_LINE_CODING (0x20)
Sets serial line parameters (baud rate, stop bits, parity, data bits)

```c
struct cdc_acm_line_coding {
    uint32_t dwDTERate;      /* Baud rate */
    uint8_t  bCharFormat;    /* Stop bits: 0=1, 1=1.5, 2=2 */
    uint8_t  bParityType;    /* Parity: 0=None, 1=Odd, 2=Even */
    uint8_t  bDataBits;      /* Data bits: 5, 6, 7, 8, 16 */
};
```

### GET_LINE_CODING (0x21)
Returns current serial line parameters

### SET_CONTROL_LINE_STATE (0x22)
Sets DTR and RTS signals
- Bit 0: DTR (Data Terminal Ready)
- Bit 1: RTS (Request To Send)

---

## Descriptor Structure

### Configuration Descriptor Hierarchy

```
Configuration Descriptor
├── Interface Association Descriptor (IAD)
├── Control Interface (Interface 0)
│   ├── Interface Descriptor
│   ├── CDC Header Functional Descriptor
│   ├── CDC Call Management Functional Descriptor
│   ├── CDC ACM Functional Descriptor
│   ├── CDC Union Functional Descriptor
│   └── Interrupt IN Endpoint Descriptor
└── Data Interface (Interface 1)
    ├── Interface Descriptor
    ├── Bulk IN Endpoint Descriptor
    └── Bulk OUT Endpoint Descriptor
```

---

## Performance Considerations

### Throughput Optimization

1. **Use Multiple RX Buffers**
   ```c
   #define CDC_NUM_BUFFERS 4  /* Increase for higher throughput */
   ```

2. **Optimize Buffer Sizes**
   - Full Speed: 64 bytes max packet size
   - High Speed: 512 bytes max packet size
   - Use buffer sizes that are multiples of max packet size

3. **Minimize Callback Processing**
   - Keep RX/TX callbacks fast
   - Queue data for processing in separate task
   - Re-queue RX buffers immediately

### Latency Optimization

1. **Reduce Polling Interval**
   ```c
   /* For interrupt endpoint */
   ep->bInterval = 1;  /* 1ms for high-speed */
   ```

2. **Use Interrupt-Driven I/O**
   - Enable USB interrupts
   - Process data in ISR or deferred work

---

## Advanced Features

### Flow Control

Implement software flow control using DTR/RTS:

```c
void cdc_event_callback(uint32_t event, void* data)
{
    if (event == USB_EVENT_LINE_STATE_CHANGED) {
        usb_cdc_acm_ctx_t* ctx = (usb_cdc_acm_ctx_t*)data;
        
        if (ctx->line_state & 0x01) {
            /* DTR asserted - host ready */
            start_transmission();
        } else {
            /* DTR de-asserted - host not ready */
            stop_transmission();
        }
    }
}
```

### Serial State Notifications

Send serial state changes to host:

```c
/* Notify host of break condition */
usb_cdc_send_notification(USB_CDC_SERIAL_STATE_BREAK);

/* Notify host of overrun error */
usb_cdc_send_notification(USB_CDC_SERIAL_STATE_OVERRUN);
```

---

## References

1. **USB CDC Specification 1.2**
   - https://www.usb.org/document-library/class-definitions-communication-devices-12

2. **USB CDC PSTN Subclass 1.2**
   - Defines ACM model and class-specific requests

3. **USB 2.0 Specification**
   - Chapter 9: USB Device Framework

---

## Support

For issues or questions:
1. Check logs with `USB_LOG_LEVEL = LOG_LEVEL_DBG`
2. Verify descriptor generation with USB analyzer
3. Test with known-good USB host
4. Review example application in `examples/usb_cdc_acm_example.c`

---

## Revision History

| Version | Date | Description |
|---------|------|-------------|
| 1.0 | 2025-12-03 | Initial CDC-ACM integration |
