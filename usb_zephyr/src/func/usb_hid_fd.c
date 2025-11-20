/*==================================================================*/
/**
  @file usb_hid_fd.c

  HID function driver implementation

  @file         usb_hid_fd.c
 
  @brief       Skeleton documentation example
 
  @details    
 
               Copyright (c) 2017 Qualcomm Technologies Inc.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*/
/*==================================================================*/

/*------------------------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------------------------*/
#include <stringl/stringl.h>
#include "usb_util.h"
#include "usb_log.h"
#include "usb_common.h"
#include "usb_hid_fd.h"
#include "usb_fd.h"

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/

#define HID_REQ_GET_DESCRIPTOR                     (0x06)

#define HID_DESCRIPTOR_LENGTH                      (0x09)
#define B_DESCRIPTOR_TYPE_HID                      (0x21)
#define B_DESCRIPTOR_TYPE_HID_REPORT               (0x22)
 
//Types of Requests for HID class, bRequest field in any request sent by Host
#define USB_HID_GET_REPORT                         (0x01)
#define USB_HID_SET_REPORT                         (0x09)
#define USB_HID_GET_IDLE                           (0x02)
#define USB_HID_SET_IDLE                           (0x0A)
 
//Report Types
#define USB_REPORT_TYPE_INPUT                      (0x01)
#define USB_REPORT_TYPE_OUTPUT                     (0x02)
#define USB_REPORT_TYPE_FEATURE                    (0x03)
 

#define USB_INTERFACE_CLASS_HID                    (0x03)
#define USB_INTERFACE_HID_SUBCLASS_NONE            (0x00)

//Macros for HID EP
#define USB_HID_EP_MAX_PKT_SIZE                    (0x10)
#define USB_HID_EP_BINTERVAL_HS                    (0x06)
#define USB_HID_EP_BINTERVAL_FS                    (0x03)


/* HID Report Descriptor - Consumer Transport Control Device */
static const uint8 report_descriptor_hid_consumer_transport[] = 
{
    0x05, 0x0C,                  /* USAGE_PAGE (Consumer Devices) */
    0x09, 0x01,                  /* USAGE (Consumer Control) */
    0xa1, 0x01,                  /* COLLECTION (Application) */
    
    0x85, 0x01,                  /*   REPORT_ID (1) */
    
    0x15, 0x00,                  /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                  /*   LOGICAL_MAXIMUM (1) */
    0x09, 0xcd,                  /*   USAGE (Play/Pause - OSC) */
    0x09, 0xb5,                  /*   USAGE (Next Track - OSC) */
    0x09, 0xb6,                  /*   USAGE (Previous Track - OSC) */
    0x09, 0xb7,                  /*   USAGE (Stop - OSC) */
    0x75, 0x01,                  /*   REPORT_SIZE (1) */
    0x95, 0x04,                  /*   REPORT_COUNT (4) */
    0x81, 0x02,                  /*   INPUT (Data,Var,Abs) */
    
    0x15, 0x00,                  /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                  /*   LOGICAL_MAXIMUM (1) */
    0x09, 0xb0,                  /*   USAGE (Play - OOC) */
    0x09, 0xb1,                  /*   USAGE (Pause - OOC) */
    0x09, 0xb3,                  /*   USAGE (Fast Forward -OOC) */
    0x09, 0xb4,                  /*   USAGE (Rewind - OOC) */
    0x75, 0x01,                  /*   REPORT_SIZE (1) */
    0x95, 0x04,                  /*   REPORT_COUNT (4) */
    0x81, 0x22,                  /*   INPUT (Data,Var,Abs,NoPref) */
    
    0x15, 0x00,                  /*   LOGICAL_MINIMUM (0) */
    0x25, 0x01,                  /*   LOGICAL_MAXIMUM (1) */
    0x09, 0xe9,                  /*   USAGE (Volume Increment - RTC) */
    0x09, 0xea,                  /*   USAGE (Volume Decrement - RTC) */
    0x75, 0x01,                  /*   REPORT_SIZE (1) */
    0x95, 0x02,                  /*   REPORT_COUNT (2) */    
    0x81, 0x02,                  /*   INPUT (Data,Var,Abs,Bit Field) */
    0x09, 0xe2,                  /*   USAGE (Mute - OOC) */
    
    0x95, 0x01,                  /*   REPORT_COUNT (1) */    
    0x81, 0x06,                  /*   INPUT (Data,Var,Rel,Bit Field) */
    
    0x95, 0x05,                  /*   REPORT_COUNT (5) */
    0x81, 0x01,                  /*   INPUT (Const) */
    
    0xc0                         /* END_COLLECTION */
};

/* HID Report in response to GET_REPORT */
static uint8 hid_input_report[] =
{
	0x01,                        /* REPORT_ID (1) */
	0x00,                        /* Usage per bit 0- Play/Pause
												  1- Next Track
												  2- Previous Track
												  3- Stop
												  4- Play
												  5- Pause
												  6- Fast Forward
												  7- Rewind */
	0x00                         /* Usage per bit 0- Volume Increment
												  1- Volume Decrement
												  2- Mute
												  3..7- Not Assigned */
};

/*------------------------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
 * Function Declarations and Definitions
 * ----------------------------------------------------------------------------------------*/

void usb_hid_notify_speed(usb_device_connect_speed_t speed, void* data)
{
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t*)data;

  USB_ASSERT(hid_ctx);

  USB_ULOG_1(ENG_QLOG, "speed %d", speed);
  USB_LOG_DBG_1(log_usb_hid_notify_speed__spd_D, speed);

  switch(speed)
  {
    case USB_SUPER_SPEED:
    case USB_HIGH_SPEED:
    {
      hid_ctx->bInterval_ep = USB_HID_EP_BINTERVAL_HS;
    }
    break;
    case USB_FULL_SPEED:
    {
      hid_ctx->bInterval_ep = USB_HID_EP_BINTERVAL_FS;
    }
    default:
    {
      USB_LOG_ERR_1(log_usb_hid_notify_speed__bad_spd_D, speed);
    }
  }
}

void usb_hid_set_cfg(void* ctx, usb_dcd_dsc_interface_t* ifc)
{
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t*) ctx;
  USB_ASSERT(hid_ctx && ifc);
  hid_ctx->ifc = ifc;
}

uint16 usb_hid_cs_ifc_desc(uint8** dsc, uint16* len, uint16 dsc_size)
{
  usb_hid_desc_t* hid_ifc;
  uint16 cs_offset = (*len);
  uint8* hid_dsc = (*dsc);

  (*len) += sizeof(usb_hid_desc_t);
  USB_ASSERT ((*len) < dsc_size);
  hid_ifc = (usb_hid_desc_t*)hid_dsc;
  hid_ifc->bLength           = HID_DESCRIPTOR_LENGTH;
  hid_ifc->bDescriptorType   = B_DESCRIPTOR_TYPE_HID;
  hid_ifc->bcdHID            = 0x0111; //HID specs 1.11
  hid_ifc->bCountryCode      = 0;
  hid_ifc->bNumDescriptors   = 1;
  hid_ifc->bDescriptorType1  = B_DESCRIPTOR_TYPE_HID_REPORT;
  hid_ifc->wDescriptorLength = sizeof(report_descriptor_hid_consumer_transport);
  hid_dsc += sizeof(usb_hid_desc_t);

  (*dsc) = hid_dsc;
  return ((*len) - cs_offset);
}

usb_dcd_dsc_interface_t* usb_hid_alloc_desc(uint8 ** dsc, uint16 * len,
  uint16 dsc_size, void * data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, 
  uint32 rev_not_used)
{
  uint8 n_ep = 1;
  uint8 alt_set =0;
  usb_dcd_dsc_interface_t* ifc_itr;
  usb_dcd_dsc_endpoint_t*  ep_itr;
  uint8 ep_num = 0;
  uint8 ep_mask = 0;
  uint8 ep_attr = 0;
  uint16 max_packet_size;
  uint8 bInterval;
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t*) data;

  USB_ASSERT (hid_ctx && (hid_ctx->ifc_id == USB_IFC_ID_HID));

  ep_num = ++(*ep_in_num);
  ep_mask = USB_EP_ADDR_IN;
  ep_attr = USB_EP_ATTR_INTR;

  ifc_itr = usb_fn_fd()->usb_fd_alloc_ifc_desc (dsc, len, dsc_size, ifc_num, alt_set, n_ep, USB_INTERFACE_CLASS_HID,
    USB_INTERFACE_HID_SUBCLASS_NONE, USB_INTERFACE_PROTOCOL_NONE, USB_INTERFACE_STR_INDEX_NONE);

  ifc_itr->id = hid_ctx->ifc_id;
  ifc_itr->cs_dsc = (*dsc);
  ifc_itr->cs_dsc_size = usb_fn_hid()->usb_hid_cs_ifc_desc(dsc, len, dsc_size);

  max_packet_size = USB_HID_EP_MAX_PKT_SIZE;
  bInterval = hid_ctx->bInterval_ep;

  ep_itr = usb_fn_fd()->usb_fd_alloc_ep_desc(dsc, len, dsc_size, ep_num, ep_mask, ep_attr, bInterval, max_packet_size);

  INSERT_TAIL(usb_dcd_dsc_endpoint, ifc_itr->endpoints, ep_itr);
  ep_itr->ifc = ifc_itr;

  return ifc_itr;
}

void usb_hid_deinit(void* data)
{
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t*) data;
  USB_ASSERT(hid_ctx);
  usb_fn_mem_util()->usb_free((void** )&hid_ctx->report_buffer);
  usb_fn_mem_util()->usb_free((void** )&hid_ctx);
}

void* usb_hid_init(usb_ifc_id ifc_id, uint8 ifc_num, void* data)
{
  usb_hid_ctx_t* hid_ctx;
  
  USB_ASSERT(hid_ctx = (usb_hid_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_hid_ctx_t)));
  USB_ASSERT(hid_ctx->report_buffer = (usb_hid_buff_t*)usb_fn_mem_util()->usb_malloc_uncached(sizeof(usb_hid_buff_t)));

  hid_ctx->ifc_num = ifc_num;
  hid_ctx->ifc_id  = ifc_id;
  hid_ctx->idle_rate = 0x00;
  hid_ctx->drop_cnt = 0;
  hid_ctx->cb_cnt = 0;
  hid_ctx->req_idx = 0;
  hid_ctx->is_report_in_progress = FALSE;
  hid_ctx->is_last_report_pending = FALSE;

  return (void*)hid_ctx;
}

uint8* usb_hid_handle_get_req(void* ctx, usb_setup_packet_t* req, uint32* len)
{
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t* )ctx;
  uint8* buff = NULL;

  USB_ASSERT(hid_ctx);
  switch(req->bRequest)
  {
    case USB_HID_GET_REPORT:
    {
      uint8 report_type = (uint8)((req->wValue >> 8) & 0xff);
      if (report_type == USB_REPORT_TYPE_INPUT)
      {
        (*len) = sizeof(hid_input_report);
        buff = hid_input_report;
        USB_LOG_DBG_1(log_usb_hid_handle_get_req__report_D, report_type);
      }
      else
      {
        USB_LOG_ERR_1(log_usb_hid_handle_get_req__wrong_report_D, report_type);
      }
    }
    break;

    case USB_HID_GET_IDLE:
    {
      (*len) = sizeof(hid_ctx->idle_rate);
      buff = &(hid_ctx->idle_rate);
      USB_LOG_DBG_1(log_usb_hid_handle_get_req__idle_D, hid_ctx->idle_rate);
    }
    break;

    case HID_REQ_GET_DESCRIPTOR:
    {
      uint8 desc_type = (uint8)((req->wValue >> 8) & 0xff);
      USB_LOG_DBG_1(log_usb_hid_handle_get_req__desc_D, desc_type);;
      if (desc_type == B_DESCRIPTOR_TYPE_HID_REPORT)
      {
        (*len) = sizeof(report_descriptor_hid_consumer_transport);
        buff = (uint8*)report_descriptor_hid_consumer_transport;
      }
      else if (desc_type == B_DESCRIPTOR_TYPE_HID)
      {
        (*len) = hid_ctx->ifc->cs_dsc_size;
        buff = (uint8*)(hid_ctx->ifc->cs_dsc);
      }
      else
      {
        USB_LOG_ERR_1(log_usb_hid_handle_get_req__unknown_desc_D, desc_type);
      }
    }
    break;

    default:
      USB_ULOG (HID_LOG, "Unknown Request");
      USB_LOG_ERR_1(log_usb_hid_handle_get_req__unknown_req_D, req->bRequest);      
  }

  return buff;
}

boolean usb_hid_handle_set_req(void* ctx, usb_setup_packet_t* req, uint32* buff, uint32 len)
{
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t* )ctx;
  uint8* data = (uint8*)buff;

  USB_ASSERT(hid_ctx);
  USB_LOG_DBG_1(log_usb_hid_handle_set_req__D, req->bRequest);

  switch(req->bRequest)
  {
    case USB_HID_SET_REPORT:
    {
      if (data)
      {
        memscpy((void*)hid_input_report, sizeof(hid_input_report), (void*)data, len);
        return TRUE;
      }
      return FALSE;
    }
    break;

    case USB_HID_SET_IDLE:
    {
      uint8 duration = (uint8)((req->wValue >> 8) & 0xff);
      hid_ctx->idle_rate = duration;
      if (hid_ctx->idle_rate != 0)
      {
        // TODO: Need to implement a timer in case the duration is not 0 (ie. infinite)
      }
      return TRUE;
    }
    break;

    default:
      USB_ULOG (AUDIO_LOG, "Unknown Request");
  }
  return FALSE;
}

void usb_hid_tx_cb(usb_urb_t* urb_ptr)
{
  usb_urb_t* urb = (usb_urb_t*)urb_ptr;

  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)urb->fd_ctx;
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t*)fd_ctx->ifc_ctx[urb->client_id].fn_class.ctx;
  USB_LOG_DBG_1(log_usb_hid_tx_cb__req_id_D, urb_ptr->req_id);
  hid_ctx->cb_cnt++;
  hid_ctx->is_report_in_progress  =FALSE;
  if (urb->transfer_status == USB_URB_STATUS_TRANSFER_CANCEL)
  {
    hid_ctx->is_last_report_pending = FALSE;
    return;
  }

  if (hid_ctx->is_last_report_pending)
  {
    hid_ctx->is_last_report_pending =FALSE;
    usb_fn_hid()->usb_hid_tx(fd_ctx, urb->client_id, hid_ctx->last_report);
  }
  return;
}

void usb_hid_tx(void* fd_ptr, usb_ifc_id ifc_id, usb_hid_bitmask_cmd_t input)
{
  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)fd_ptr;
  usb_hid_ctx_t* hid_ctx = (usb_hid_ctx_t* )fd_ctx->ifc_ctx[ifc_id].fn_class.ctx;

  if (hid_ctx->is_report_in_progress == TRUE)
  {
    if (hid_ctx->is_last_report_pending)
    {
      USB_LOG_ERR_1(log_usb_hid_tx__drop_pending_report_D,hid_ctx->last_report);
      hid_ctx->drop_cnt++;
    }
    hid_ctx->last_report = input;
    hid_ctx->is_last_report_pending = TRUE;
  }
  else
  {
    if (hid_ctx->is_last_report_pending)
    {
      USB_LOG_ERR_1(log_usb_hid_tx__drop_pending_report_D, hid_ctx->last_report);
      hid_ctx->is_last_report_pending =FALSE;
    }
    hid_ctx->report_buffer->report_id = USB_HID_REPORT_ID;
    hid_ctx->report_buffer->cmd1 = input & 0x00ff;
    hid_ctx->report_buffer->cmd2 = (input & 0xff00)>>8;

    if (usb_fn_fd()->usb_fd_tx_pkt(fd_ctx, (unsigned char*)hid_ctx->report_buffer, sizeof(usb_hid_buff_t), hid_ctx->req_idx, ifc_id, 0))
    {
      USB_LOG_ERR_1(log_usb_hid_tx__fail_report_D, input);
      hid_ctx->is_report_in_progress = FALSE;
    }
    else
    {
      USB_LOG_DBG_1(log_usb_hid_tx__report_D, input);
      hid_ctx->req_idx++;
      //hid_ctx->is_report_in_progress = TRUE;
    }
  }
  return;
}

void usb_hid_enum_complete(void* fd_ptr, uint8 ifc_num)
{
#ifndef USB_HID_TEST_TX_CB
  uint32 urb_num= 0;
  usb_urb_t* urb;
  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)fd_ptr;
  USB_LOG_1(log_usb_hid_enum_complete__ifc_D, ifc_num);
  // setup URBs for handling HID cb
  fd_ctx->ifc_ctx[ifc_num].tx->idx = 0;
  for(urb_num=0; urb_num < USB_URB_MAX; urb_num++)
  {
    urb = &fd_ctx->ifc_ctx[ifc_num].tx->urb[urb_num];
    urb->complete_callback = usb_fn_hid()->usb_hid_tx_cb;
  }
#endif
}

/*----------------------------------------------------------------------------
 * Function table definitions - HID layer
 * -------------------------------------------------------------------------*/

usb_fn_tbl_hid_t fn_tbl_hid = 
{
  usb_hid_notify_speed,
  usb_hid_set_cfg,
  usb_hid_cs_ifc_desc,
  usb_hid_alloc_desc,
  usb_hid_deinit,
  usb_hid_init,
  usb_hid_handle_get_req,
  usb_hid_handle_set_req,
  usb_hid_tx_cb,
  usb_hid_tx,
  usb_hid_enum_complete,
};



