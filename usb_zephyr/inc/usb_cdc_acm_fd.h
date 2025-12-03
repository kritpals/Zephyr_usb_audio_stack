/*=======================================================================*//**
  @file         usb_cdc_acm_fd.h

  @brief        Serial commnunication CDC driver header

  @details      
 
                Copyright (c)  Qualcomm Technologies, Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
*//*========================================================================*/
#ifndef USB_CDC_ACM_FD_H
#define USB_CDC_ACM_FD_H

#include "usb_api.h"
#include "usb_log.h"
#include "usb_common.h"
#include "usb_util.h"
#include "usb_fd.h"
#include <zephyr/usb/class/usb_cdc.h>

/* CDC-ACM Class Codes */
#define USB_CDC_ACM_CLASS           0x02
#define USB_CDC_ACM_SUBCLASS        0x02
#define USB_CDC_ACM_PROTOCOL        0x00
#define USB_CDC_DATA_CLASS          0x0A

/* CDC-ACM Endpoints */
#define CDC_ACM_INT_EP_MPS          16
#define CDC_ACM_BULK_EP_MPS_HS      512
#define CDC_ACM_BULK_EP_MPS_FS      64

/* CDC-ACM Class Requests */
#define USB_CDC_SET_LINE_CODING             0x20
#define USB_CDC_GET_LINE_CODING             0x21
#define USB_CDC_SET_CONTROL_LINE_STATE      0x22

/* CDC-ACM Serial State bits 
#define USB_CDC_SERIAL_STATE_DCD            (1 << 0)
#define USB_CDC_SERIAL_STATE_DSR            (1 << 1)
#define USB_CDC_SERIAL_STATE_BREAK          (1 << 2)
#define USB_CDC_SERIAL_STATE_RING_SIGNAL    (1 << 3)
#define USB_CDC_SERIAL_STATE_FRAMING        (1 << 4)
#define USB_CDC_SERIAL_STATE_PARITY         (1 << 5)
#define USB_CDC_SERIAL_STATE_OVERRUN        (1 << 6)
*/
typedef struct usb_cdc_acm_ctx {
    usb_dcd_dsc_interface_t* ctrl_ifc;   /* Control interface */
    usb_dcd_dsc_interface_t* data_ifc;   /* Data interface */
    usb_ifc_id ifc_id;
    uint8_t ctrl_ifc_num;
    uint8_t data_ifc_num;
    usb_device_connect_speed_t speed;
    uint16_t bulk_max_packet_size;
    struct cdc_acm_line_coding line_coding;
    uint16_t line_state;
} usb_cdc_acm_ctx_t;

typedef struct usb_fn_tbl_cdc_acm
{
  usb_dcd_dsc_interface_t* (*usb_cdc_acm_alloc_desc)(uint8_t **dsc, uint16_t *len, uint16_t dsc_size, void *data, uint8_t ifc_num, 
            uint8_t *ep_in_num, uint8_t *ep_out_num, uint32_t rev_not_used);
  boolean (*usb_cdc_acm_handle_set_req)(void* ctx, usb_setup_packet_t* setup, uint32* buff, uint32 len);
  uint8_t* (*usb_cdc_acm_handle_get_req)(void* ctx, usb_setup_packet_t* setup, uint32* len);
  void* (*usb_cdc_acm_init)(usb_ifc_id ifc_id, uint8_t ifc_num, void* data);
  void (*usb_cdc_acm_deinit)(void* data);
  void (*usb_cdc_acm_notify_speed)(usb_device_connect_speed_t speed, void* data);
  void (*usb_cdc_acm_set_cfg)(void* ctx, usb_dcd_dsc_interface_t* ifc);
}usb_fn_tbl_cdc_acm_t;

extern usb_fn_tbl_cdc_acm_t fn_tbl_cdc_acm;
#define usb_fn_cdc()  (&fn_tbl_cdc_acm)

uint32_t cdc_app_init(void); 

#endif /* #ifndef USB_CDC_ACM_FD_H */
