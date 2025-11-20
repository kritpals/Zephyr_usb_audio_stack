/*==================================================================*/
/**
  @file usb_dfu_fd.c

  DFU function driver implementation

  @file         usb_dfu_fd.c
 
  @brief       Implements device firmware upgrade class.
                  Reference : USB Device Firmware Upgrade Specification, Revision 1.1.
 
  @details    DFU allows flashing binary over control channel interface. In order to enter DFU mode, 
                  host explicitly sends DFU_DETACH request. Device responds to DFU_DETACH request by 
                  performing spoof dis-connect - connect and re-enumerates in DFU only mode.
                  In DFU only mode, device downloads / uploads binary image and resets.
 
               Copyright (c) 2017 Qualcomm Technologies Inc.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*/
/*==================================================================*/

/*------------------------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------------------------*/
#include <stringl/stringl.h>

#include "usb_api.h"
#include "usb_log.h"
#include "usb_common.h"
#include "usb_dfu.h"
#include "usb_dfu_fd.h"
#include "usb_dcd.h"
#include "usb_util.h"
#include "usb_fd.h"

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/

#define HID_REQ_GET_DESCRIPTOR                     (0x06)

#define DFU_DESCRIPTOR_LENGTH                      (0x09)
#define B_DESCRIPTOR_TYPE_DFU                      (0x21)
#define B_DESCRIPTOR_TYPE_HID_REPORT               (0x22)

#define USB_INTERFACE_CLASS_VENDOR                 (0xFF)
#define USB_INTERFACE_CLASS_DFU                    (0xFE)
#define USB_INTERFACE_DFU_SUBCLASS                 (0x01)
#define USB_INTERFACE_DFU_PROTOCOL_NORMAL          (0x01)
#define USB_INTERFACE_DFU_PROTOCOL_DFU             (0x02)

#define USB_DFU_MAX_TRANSFER_SIZE                  (64)
#define USB_DFU_HS_MAX_PKT                         (64)
#define USB_DFU_FS_MAX_PKT                         (16)


// TODO: Need to discuss the value for this, FFFF is a random number
#define USB_DFU_DETACH_TIMEOUT                     (0xFFFF)

// Section: Table 4.2 DFU Functional Descriptor (bmAttributes)
// DFU attributes
#define DFU_ATTR_WILL_DETACH                      (1 << 3)
#define DFU_ATTR_MANIFEST_TOLERANT                (1 << 2)
#define DFU_ATTR_UPLOAD_CAPABLE                   (1 << 1)
#define DFU_ATTR_DNLOAD_CAPABLE                   (1 << 0)

#define USB_REQ_CLASS_DFU_DETACH                  (0x00)
#define USB_REQ_CLASS_DFU_DNLOAD                  (0x01)
#define USB_REQ_CLASS_DFU_UPLOAD                  (0x02)
#define USB_REQ_CLASS_DFU_GETSTATUS               (0x03)
#define USB_REQ_CLASS_DFU_CLRSTATUS               (0x04)
#define USB_REQ_CLASS_DFU_GETSTATE                (0x05)
#define USB_REQ_CLASS_DFU_ABORT                   (0x06)
#define USB_REQ_CLASS_DFU_THESYCON_DETACH         (0xF2)
#define USB_REQ_CLASS_DFU_THESYCON_START          (0xF4)
#define USB_REQ_CLASS_DFU_THESYCON_END            (0xF3)

/*------------------------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------
 * Function Declarations and Definitions
 * ----------------------------------------------------------------------------------------*/

void usb_dfu_get_status(dfu_get_status_resp_t* resp, uint8 status, uint8 state)
{
  resp->bStatus = status;
  resp->bwPollTimeout = 0;
  resp->bState = state;
  resp->iString = 0;
}

// Implements DFU state machine assuming DFU Attr below.
// DFU Attr -  bitCanDnload = 1, bitCanUpload = 1, bitWillDetach = 1 and bitManifestTolerant = 1
// Reference: USB Device Firmware Upgrade Specification, Revision 1.1.
// Section - A.1 - Interface state transition diagram
// Section - A.2 - Interface state transition summary

boolean usb_dfu_update_state(usb_dfu_ctx_t * dfu_ctx, usb_dfu_event_t event)
{
  boolean event_valid = FALSE;

  if(NULL == dfu_ctx)
  {
    return FALSE;
  }
  
  switch(dfu_ctx->state)
  {
    case DFU_APP_IDLE: // DFU Spec. Section - A.2.1 : State 0 appIDLE
    {
      switch(event)
      {
        case DFU_EVENT_DETACH:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_APP_DETACH;
          dfu_ctx->notify(USB_EVENT_DFU_ENTRY, dfu_ctx->ifc_num, (void*)NULL);
        }
        break;

        case DFU_EVENT_GET_STATE:
        case DFU_EVENT_GET_STATUS:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_APP_IDLE;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_APP_IDLE;
      }
    }
    break;

    case DFU_APP_DETACH: // DFU Spec. Section - A.2.2 : State 1 appDETACH
    {
      switch(event)
      {
        case DFU_EVENT_GET_STATUS:
        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_APP_DETACH;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_APP_IDLE;
      }    
    }
    break;

    case DFU_IDLE: // DFU Spec. Section - A.2.3 : State 2 dfuIDLE
    {
      switch(event)
      {
        case DFU_EVENT_DNLOAD:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_DNLOAD_SYNC;
        }
        break;

        case DFU_EVENT_DNLOAD_END:
        {
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
        }
        break;

        case DFU_EVENT_UPLOAD:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_UPLOAD_IDLE;
        }
        break;

        case DFU_EVENT_ABORT:
        case DFU_EVENT_GET_STATUS:
        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_IDLE;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
      }
    }
    break;
    
    case DFU_DNLOAD_SYNC: // DFU Spec. Section - A.2.4 : State 3 dfuIDLE
    {
      switch(event)
      {
        case DFU_EVENT_GET_STATUS:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_DNLOAD_IDLE;
        }
        break;

        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_DNLOAD_SYNC;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
      }
    }
    break;

    case DFU_DNLOAD_BUSY: // DFU Spec. Section - A.2.5 : State 4 dfuDNBUSY
    {
      event_valid = FALSE;
      dfu_ctx->state = DFU_ERROR;    
    }
    break;
    
    case DFU_DNLOAD_IDLE: // DFU Spec. Section - A.2.6 : State 5 dfuDNLOAD-IDLE
    {
      switch(event)
      {
        case DFU_EVENT_DNLOAD:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_DNLOAD_SYNC;
        }
        break;

        case DFU_EVENT_DNLOAD_END:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_MANIFEST_SYNC;
        }
        break;

        case DFU_EVENT_ABORT:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_IDLE;
        }
        break;

        case DFU_EVENT_GET_STATUS:
        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_DNLOAD_IDLE;        
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
      }
    }
    break;
    
    case DFU_MANIFEST_SYNC: // DFU Spec. Section - A.2.7 : State 6 dfuMANIFEST-SYNC
    {
      switch(event)
      {
        case DFU_EVENT_GET_STATUS:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_IDLE;
          if(FALSE == dfu_ctx->use_rsvd) 
          {
            dfu_ctx->notify(USB_EVENT_DFU_EXIT, dfu_ctx->ifc_num, (void*)NULL);
          }
        }
        break;

        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_MANIFEST_SYNC;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
      }
    }
    break;
    
    case DFU_MANIFEST: // DFU Spec. Section - A.2.8 : State 7 dfuMANIFEST
    {
      event_valid = FALSE;
      dfu_ctx->state = DFU_ERROR;
    }
    break;
    
    case DFU_MANIFEST_WAIT_RESET: // DFU Spec. Section - A.2.9 : State 8 dfuMANIFEST-WAIT-RESET
    {
      event_valid = TRUE;
      dfu_ctx->state = DFU_MANIFEST_WAIT_RESET;
    }
    break;
    
    case DFU_UPLOAD_IDLE: // DFU Spec. Section - A.2.10 : State 9 dfuUPLOAD-IDLE
    {
      switch(event)
      {
        case DFU_EVENT_UPLOAD:
        case DFU_EVENT_GET_STATUS:
        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_UPLOAD_IDLE;
        }
        break;

        case DFU_EVENT_UPLOAD_END:
        case DFU_EVENT_ABORT:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_IDLE;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
      }
    }
    break;
    
    case DFU_ERROR: // DFU Spec. Section - A.2.11 : State 11 dfuERROR
    {
      switch(event)
      {
        case DFU_EVENT_GET_STATUS:
        case DFU_EVENT_GET_STATE:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_ERROR;
        }
        break;

        case DFU_EVENT_CLEAR_STATUS:
        {
          event_valid = TRUE;
          dfu_ctx->state = DFU_IDLE;
        }
        break;

        default:
          event_valid = FALSE;
          dfu_ctx->state = DFU_ERROR;
      }
    }
    break;

    default:
      USB_LOG_ERR_1(log_usb_dfu_update_state__unknown_state_D, dfu_ctx->state);
  }
  return event_valid;
}

uint8* usb_dfu_handle_get_req(void* ctx, usb_setup_packet_t* req, uint32* len)
{
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t* )ctx;
  uint8* buff = NULL;
  usb_dfu_event_t event;

  USB_ASSERT(dfu_ctx);
  USB_LOG_DBG_1(log_usb_dfu_handle_get_req__D, req->bRequest);

  switch(req->bRequest)
  {
    case USB_REQ_CLASS_DFU_GETSTATE:
    {
      if(usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_GET_STATE))
      {
        usb_fn_dfu()->usb_dfu_get_status(dfu_ctx->resp, dfu_ctx->status, dfu_ctx->state);
        (*len) = sizeof(dfu_get_state_resp_t);
        buff = (uint8*) &dfu_ctx->resp->bState;
      }
    }
    break;

    case USB_REQ_CLASS_DFU_GETSTATUS:
    {
      if(usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_GET_STATUS))
      {
        usb_fn_dfu()->usb_dfu_get_status(dfu_ctx->resp, dfu_ctx->status, dfu_ctx->state);
        (*len) = sizeof(dfu_get_status_resp_t);
        buff = (uint8*) dfu_ctx->resp;
      }
    }
    break;

    case USB_REQ_CLASS_DFU_UPLOAD:
    {
      event = ((*len) == USB_DFU_MAX_TRANSFER_SIZE) ? DFU_EVENT_UPLOAD : DFU_EVENT_UPLOAD_END;
      if(usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, event))
      {
        dfu_ctx->status = dfu_ctx->up_cb(req->wValue, dfu_ctx->payload_buff, len);
        if(dfu_ctx->status == DCI_OK)
        {
          buff = dfu_ctx->payload_buff;
        }
      }
    }
    break;

    default:
      USB_ULOG (HID_QLOG, "Unknown Request");
  }

  if(buff == NULL)
  {
    dfu_ctx->state = DFU_ERROR;
  }

  return buff;
}

void usb_dfu_set_req_status_comp_cb(void* ctx, usb_setup_packet_t* req)
{
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t*) ctx;
  boolean status = FALSE;

  USB_ASSERT(dfu_ctx);
  USB_LOG_DBG_1(log_usb_dfu_handle_set_req__D, req->bRequest);

  switch(req->bRequest)
  {
    case USB_REQ_CLASS_DFU_THESYCON_DETACH:
    case USB_REQ_CLASS_DFU_DETACH:
    {
      USB_LOG_ERR(log_usb_dfu_timer_cb__signal_dfu_entry);
      status = usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_DETACH);
    }
    break;

    case USB_REQ_CLASS_DFU_THESYCON_END:
    {
      USB_LOG_ERR(log_usb_dfu_timer_cb__signal_dfu_exit);
      status = usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_GET_STATE);
      dfu_ctx->notify(USB_EVENT_DFU_EXIT, dfu_ctx->ifc_num, (void*)NULL);
    }
    break;

    default:
    {
    }
  }
  
}


boolean usb_dfu_handle_set_req(void* ctx, usb_setup_packet_t* req, uint32* buff, uint32 len)
{
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t*) ctx;
  boolean status = FALSE;

  USB_ASSERT(dfu_ctx);
  USB_LOG_DBG_1(log_usb_dfu_handle_set_req__D, req->bRequest);

  switch(req->bRequest)
  {
    case USB_REQ_CLASS_DFU_THESYCON_DETACH:
    case USB_REQ_CLASS_DFU_DETACH:
    {
      // Defer processing DFU DETACH event until SET_REQ ack completion.
      status = TRUE;
    }
    break;

    case USB_REQ_CLASS_DFU_DNLOAD:
    {
      if(len)
      {
        if(usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_DNLOAD))
        {
          dfu_ctx->status = dfu_ctx->dn_cb(req->wValue, (uint8*)buff, len);
          status = (dfu_ctx->status == DCI_OK);
        }
      }
      else
      {
        status = usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_DNLOAD_END);
      }
    }
    break;

    case USB_REQ_CLASS_DFU_THESYCON_START:
    {
      dfu_ctx->use_rsvd = TRUE;
      status = usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_GET_STATE);
    }
    break;
    
    case USB_REQ_CLASS_DFU_THESYCON_END:
    {
      // Defer processing DFU DNLOAD END event until SET_REQ ack completion.
      status = TRUE;
    }
    break;

    case USB_REQ_CLASS_DFU_CLRSTATUS:
    {
      status = usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_CLEAR_STATUS);
    }
    break;

    case USB_REQ_CLASS_DFU_ABORT:
    {
      status = usb_fn_dfu()->usb_dfu_update_state(dfu_ctx, DFU_EVENT_ABORT);
    }
    break;

    default:
    {
      USB_ULOG (HID_QLOG, "Unknown Request");
      USB_LOG_ERR_1(log_usb_dfu_handle_set_req__unknown_req_D, req->bRequest);
    }
  }

  if (FALSE == status)
  {
    dfu_ctx->state = DFU_ERROR;
  }

  return status;
}

void usb_dfu_notify_speed(usb_device_connect_speed_t speed, void* data)
{
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t*)data;
  USB_ASSERT(dfu_ctx);
  dfu_ctx->speed = speed;
  USB_ULOG_1(ENG_QLOG, "speed %d", speed);
}

void usb_dfu_set_cfg(void* ctx, usb_dcd_dsc_interface_t* ifc)
{
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t*) ctx;
  USB_ASSERT(dfu_ctx && ifc);
  dfu_ctx->ifc = ifc;
}

uint16 usb_dfu_alloc_cs_desc(uint8** dsc, uint16* len, uint16 dsc_size)
{
  usb_dfu_desc_t* dfu_ifc;
  uint16 cs_offset = (*len);
  uint8* dfu_dsc = (*dsc);
  USB_ASSERT(dfu_dsc);

  (*len) += sizeof(usb_dfu_desc_t);
  USB_ASSERT ((*len) < dsc_size);
  dfu_ifc = (usb_dfu_desc_t*)dfu_dsc;
  dfu_ifc->bLength           = DFU_DESCRIPTOR_LENGTH;
  dfu_ifc->bDescriptorType   = B_DESCRIPTOR_TYPE_DFU;
  dfu_ifc->bmAttributes      = DFU_ATTR_DNLOAD_CAPABLE | DFU_ATTR_UPLOAD_CAPABLE 
                                | DFU_ATTR_WILL_DETACH | DFU_ATTR_MANIFEST_TOLERANT;
  dfu_ifc->wDetachTimeOut    = USB_DFU_DETACH_TIMEOUT;
  dfu_ifc->wTransferSize     = USB_DFU_MAX_TRANSFER_SIZE;
  dfu_ifc->bcdDFUVersion     = 0x0110; //DFU specs 1.1
  (*dsc) += sizeof(usb_dfu_desc_t);

  return ((*len) - cs_offset);
}

usb_dcd_dsc_interface_t* usb_dfu_alloc_desc(uint8 ** dsc, uint16 * len,
  uint16 dsc_size, void * data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, 
  uint32 rev_not_used)
{
  uint8 n_ep = 0;
  uint8 alt_set =0;
  usb_dcd_dsc_interface_t* ifc_ptr;
  uint8 ifc_protocol = 0;
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t*) data;

  USB_ASSERT (dfu_ctx);

    ifc_protocol = (dfu_ctx->op_mode == USB_OP_MODE_MISSION) ? USB_INTERFACE_DFU_PROTOCOL_NORMAL : 
      USB_INTERFACE_DFU_PROTOCOL_DFU;
  
  ifc_ptr = usb_fn_fd()->usb_fd_alloc_ifc_desc (dsc, len, dsc_size, ifc_num, alt_set, n_ep, 
      USB_INTERFACE_CLASS_DFU, USB_INTERFACE_DFU_SUBCLASS, ifc_protocol, 
      USB_INTERFACE_STR_INDEX_NONE);

  ifc_ptr->id = dfu_ctx->ifc_id;
  ifc_ptr->cs_dsc = (*dsc);
  ifc_ptr->cs_dsc_size = usb_fn_dfu()->usb_dfu_alloc_cs_desc(dsc, len, dsc_size);

  return ifc_ptr;
}

void usb_dfu_deinit(void* data)
{
  usb_dfu_ctx_t* dfu_ctx = (usb_dfu_ctx_t*) data;
  USB_ASSERT(dfu_ctx);

  if(dfu_ctx->op_mode == USB_OP_MODE_DFU)
  {
    usb_fn_mem_util()->usb_free((void**)&dfu_ctx->payload_buff);
  }

  usb_fn_mem_util()->usb_free((void**)&dfu_ctx->resp);
  usb_fn_mem_util()->usb_free((void**)&dfu_ctx);
}

void* usb_dfu_init(usb_ifc_id ifc_id, uint8 ifc_num, void* data)
{
  usb_dfu_ctx_t* dfu_ctx;
  usb_dfu_init_cfg_t* dfu_init_cfg = (usb_dfu_init_cfg_t*) data;

  USB_ASSERT(dfu_init_cfg);
  USB_ASSERT(dfu_ctx = (usb_dfu_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dfu_ctx_t)));
  USB_ASSERT(dfu_ctx->resp = (dfu_get_status_resp_t*)usb_fn_mem_util()->usb_malloc(sizeof(dfu_get_status_resp_t)));

  dfu_ctx->ifc_num  = ifc_num;
  dfu_ctx->ifc_id   = ifc_id;
  dfu_ctx->op_mode  = dfu_init_cfg->op_mode;
  dfu_ctx->up_cb    = dfu_init_cfg->up_cb;
  dfu_ctx->dn_cb    = dfu_init_cfg->dn_cb;
  dfu_ctx->notify   = dfu_init_cfg->notify;
  dfu_ctx->use_rsvd = FALSE;
  dfu_ctx->status   = DFU_OK;
  dfu_ctx->state    = (dfu_ctx->op_mode == USB_OP_MODE_MISSION) ? DFU_APP_IDLE : DFU_IDLE;
  usb_fn_dfu()->usb_dfu_get_status(dfu_ctx->resp, dfu_ctx->status, dfu_ctx->state);

  // Allocate DFU payload buffer only when operating in DFU only mode.
  if(dfu_ctx->op_mode == USB_OP_MODE_DFU)
  {
    USB_ASSERT(dfu_ctx->payload_buff = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_DFU_MAX_TRANSFER_SIZE));
  }

  return (void*)dfu_ctx;
}

/*----------------------------------------------------------------------------
 * Function table definitions - DFU layer
 * -------------------------------------------------------------------------*/

usb_fn_tbl_dfu_t fn_tbl_dfu = 
{
  usb_dfu_get_status,
  usb_dfu_update_state,
  usb_dfu_handle_get_req,
  usb_dfu_set_req_status_comp_cb,
  usb_dfu_handle_set_req,
  usb_dfu_notify_speed,
  usb_dfu_set_cfg,
  usb_dfu_alloc_cs_desc,
  usb_dfu_alloc_desc,
  usb_dfu_deinit,
  usb_dfu_init,
};


