/*=======================================================================*//**
  @file usb_audio_class.h

  Audio class driver implementation

  @file         usb_audio_class.h
 
  @brief        Skeleton documentation example
 
  @details      Audio class has two types of interfaces. 
				Audio control and streaming type interfaces.
				This module supports both.
 
               Copyright (c) 2017 Qualcomm Technologies Inc.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*/
/*========================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "stringl/stringl.h"

#include "usb_log.h"
#include "usb_class_dcd.h"
#include "usb_util.h"
#include "usb_dcd.h"
#include "usb_dci.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

// Receive callback for 2 stage SET_REQ ack completion.
// This allows deferred handling of SET_REQ for requests like DFU entry and DFU exit.
void usb_dcd_class_status2_ack_cb(struct usb_urb* urb_ptr)
{
  usb_dcd_ctx_t* dcd_ctx; 
  usb_setup_packet_t* req;
  uint8 ifc_num;
  USB_ASSERT(urb_ptr && urb_ptr->dcd_priv_ptr);
  dcd_ctx = (usb_dcd_ctx_t*)urb_ptr->dcd_priv_ptr;
  req = &dcd_ctx->cached_req;
  ifc_num = (uint8)(req->wIndex & 0xff);
  dcd_ctx->ctrl_urb.tx.complete_callback = NULL;
  dcd_ctx->fd_cb.set_req_status_comp_cb(dcd_ctx->fd_ctx, ifc_num, req);
}

// Queue ack for GET_REQ only after data phase completion.
void usb_dcd_class_data_cb(struct usb_urb* urb_ptr)
{
  usb_dcd_ctx_t* dcd_ctx;
  USB_ASSERT(urb_ptr && urb_ptr->dcd_priv_ptr);
  dcd_ctx = (usb_dcd_ctx_t*)urb_ptr->dcd_priv_ptr;
  dcd_ctx->ctrl_urb.tx.complete_callback = NULL;
  usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_RX, dcd_ctx->setup_status, 0);
}

void usb_dcd_handle_class_status3_req_ifc(struct usb_urb* urb_ptr)
{
  usb_dcd_ctx_t* dcd_ctx;
  usb_setup_packet_t* req;
  uint8 ifc_num;
  uint32* buff_ptr = NULL;

  USB_ASSERT(urb_ptr && urb_ptr->dcd_priv_ptr);

  dcd_ctx = (usb_dcd_ctx_t*)urb_ptr->dcd_priv_ptr;
  req = &dcd_ctx->cached_req;
  ifc_num = (uint8)(req->wIndex & 0xff);
  
  buff_ptr = (uint32*)urb_ptr->transfer_buffer_ptr;
  dcd_ctx->ctrl_urb.rx.complete_callback = NULL;

  if(req->wLength != urb_ptr->actual_length)
  {
    USB_LOG_ERR_2(log_usb_dcd_handle_class_status3_req_ifc__req_len_D_act_len_D, req->wLength, 
      urb_ptr->actual_length);
    return;
  }

  if(FALSE == dcd_ctx->fd_cb.handle_set_req(dcd_ctx->fd_ctx, ifc_num, req, buff_ptr, req->wLength))
  {
    /* error, stall EP0 */
    USB_LOG_ERR_1(log_usb_dcd_handle_setup__stall_ep_req_D, 
       ((req->bmRequestType >> USB_SETUP_RT_RCP_POS) & USB_SETUP_RT_RCP_SEED ));      
    usb_fn_dci()->usb_dci_ctrl_error_recover(dcd_ctx->dci_ctx);
  }
  else
  {
    usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_TX, dcd_ctx->setup_status, 0);
  }
}

void usb_dcd_handle_class_status3_req_ep(struct usb_urb* urb_ptr)
{
  usb_dcd_ctx_t* dcd_ctx; 
  usb_setup_packet_t* req;
  usb_dcd_dsc_interface_t* ifc_ptr = NULL;
  usb_dcd_dsc_endpoint_t* ep_ptr;
  uint32* buff_ptr = NULL;
  uint8 ep_num;
  uint8 ifc_num;

  USB_ASSERT(urb_ptr && urb_ptr->dcd_priv_ptr);

  dcd_ctx = (usb_dcd_ctx_t*)urb_ptr->dcd_priv_ptr;
  req = &dcd_ctx->cached_req;
  ep_num = (uint8)(req->wIndex & 0xff);
  buff_ptr = (uint32*)urb_ptr->transfer_buffer_ptr;
  dcd_ctx->ctrl_urb.rx.complete_callback = NULL;

  // check if host has sent exact amount of data it specified in setup request.
  if(req->wLength != urb_ptr->actual_length)
  {
    USB_ULOG(DBG_E_QLOG, "setup request length does not match actual data length");
    USB_LOG_ERR_2(log_usb_dcd_handle_class_status3_req_ep__req_len_D_act_len_D, req->wLength, 
      urb_ptr->actual_length);
    return;
  }

  ep_ptr = usb_fn_dcd()->usb_dcd_find_ep(dcd_ctx, ep_num);
  USB_ASSERT(ep_ptr && ep_ptr->ifc);

  ifc_ptr = ep_ptr->ifc;
  ifc_num = ifc_ptr->descriptor->bInterfaceNumber;

  if(FALSE == dcd_ctx->fd_cb.handle_set_req(dcd_ctx->fd_ctx, ifc_num, req, buff_ptr, req->wLength))
  {
      /* error, stall EP0 */
    USB_LOG_ERR_1(log_usb_dcd_handle_setup__stall_ep_req_D, 
       ((req->bmRequestType >> USB_SETUP_RT_RCP_POS) & USB_SETUP_RT_RCP_SEED ));      
    usb_fn_dci()->usb_dci_ctrl_error_recover(dcd_ctx->dci_ctx);
  }
  else
  {
    usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_TX, dcd_ctx->setup_status, 0);
  }
}

boolean usb_dcd_handle_setup_class_ifc(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, 
  usb_ep_dir_t ctrl_data_dir)
{
  boolean result = FALSE;
  uint8 ifc_num = (uint8)(req->wIndex & 0xff);
  usb_dcd_dsc_interface_t* ifc = usb_fn_dcd()->get_curr_ifc_alt_set(dcd_ctx, ifc_num);  

  uint8* buff = NULL;
  uint32 wLength = 0;

  USB_ASSERT(ifc);

  if (ctrl_data_dir == DIR_RX) // SET_REQ
  {
    USB_LOG_1(log_handle_steup_class_ifc__length_D, req->wLength);

    // cache existing request and process after receiving data from host.
    memscpy(&dcd_ctx->cached_req, sizeof(usb_setup_packet_t), req, sizeof(usb_setup_packet_t));
    
    if (req->wLength > 0) // with data phase (3 stage control request).
    {
      dcd_ctx->ctrl_urb.rx.complete_callback = usb_fn_dcd()->usb_dcd_handle_class_status3_req_ifc;
      usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, req->wLength);
      result = TRUE;
    }
    else // without data phase (2 stage control request).
    {
      if(TRUE == dcd_ctx->fd_cb.handle_set_req(dcd_ctx->fd_ctx, ifc_num, req, NULL, wLength))
      {
        dcd_ctx->ctrl_urb.tx.complete_callback = usb_fn_dcd()->usb_dcd_class_status2_ack_cb;
        usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_TX, dcd_ctx->setup_status, 0);
        result = TRUE;
      }
    }
  }
  else // GET_REQ with data phase.
  {
    USB_LOG_1(log_handle_get_class_ifc__ifc_D, ifc->id);
    buff = dcd_ctx->fd_cb.handle_get_req(dcd_ctx->fd_ctx, ifc_num, req, &wLength);
    if (buff)
    {
      dcd_ctx->ctrl_urb.tx.complete_callback = usb_fn_dcd()->usb_dcd_class_data_cb;
      usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, buff, MIN(wLength, req->wLength));
      result = TRUE;
    }
  }
  return result;
}

boolean usb_dcd_handle_setup_class_ep(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, 
  usb_ep_dir_t ctrl_data_dir)
{
  usb_dcd_dsc_endpoint_t* ep;
  usb_dcd_dsc_interface_t* ifc_ptr = NULL;
  boolean result = FALSE;
  uint8 ep_num = (uint8)(req->wIndex & 0xff);
  uint32 len;
  uint8* buff = NULL;
  uint8 ifc_num;
  
  ep = usb_fn_dcd()->usb_dcd_find_ep(dcd_ctx, ep_num);

  if(ep && ep->ifc)
  {
    ifc_ptr = ep->ifc;
    ifc_num = ifc_ptr->descriptor->bInterfaceNumber;
    if (ctrl_data_dir == DIR_TX)   // GET_REQ with data phase
    {
      USB_LOG_1(log_handle_get_class_ep__ifc_id_D, ifc_ptr->id);
      buff = dcd_ctx->fd_cb.handle_get_req(dcd_ctx->fd_ctx, ifc_num, req, &len);
      if(buff)
      {
        dcd_ctx->ctrl_urb.tx.complete_callback = usb_fn_dcd()->usb_dcd_class_data_cb;
        usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, buff, MIN(req->wLength, len));
        result = TRUE;
      }
      else
      {
        USB_LOG_ERR_1(log_usb_dcd_handle_get_class_ep__bad_ifc_id_D, ifc_ptr->id);
      }
    }
    else // SET_REQ with data from host
    {
      USB_LOG_1(log_handle_setup_class_ep__ifc_id_D, ifc_ptr->id);
      // cache existing request to process after receiving data fron host
      memscpy(&dcd_ctx->cached_req, sizeof(usb_setup_packet_t), req, sizeof(usb_setup_packet_t));
      dcd_ctx->ctrl_urb.rx.complete_callback = usb_fn_dcd()->usb_dcd_handle_class_status3_req_ep;
      usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, req->wLength);
      result = TRUE;
    }
  }
  return result;
}

boolean usb_dcd_handle_setup_class(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req)
{
  boolean result = FALSE;
  uint8 bm_req_recp = ((req->bmRequestType & USB_SETUP_RT_RCP_MASK) >> USB_SETUP_RT_RCP_POS);
  uint8 bm_req_dir = ((req->bmRequestType & USB_SETUP_RT_DIR_MASK) >> USB_SETUP_RT_DIR_POS);
  USB_LOG_2(log_handle_setup_class__dir_D_recp_D, bm_req_dir, bm_req_recp);

  switch( bm_req_recp )
  { 
    case USB_SETUP_RT_RCP_IFC:
    {
      result = usb_fn_dcd()->usb_dcd_handle_setup_class_ifc(dcd_ctx, req, (usb_ep_dir_t)bm_req_dir);
    }
    break;

    case USB_SETUP_RT_RCP_EP:
    {
      result = usb_fn_dcd()->usb_dcd_handle_setup_class_ep(dcd_ctx, req, (usb_ep_dir_t)bm_req_dir);
    }
    break;

    case USB_SETUP_RT_RCP_DEV:
    {
      uint8 desc_type = (req->wValue >> 8);
      if (desc_type == USB_DESCTYPE_HID || desc_type == USB_DESCTYPE_HID_REPORT)
      {
        // Only in case of HID report descriptor, send it as ifc command
        result = usb_fn_dcd()->usb_dcd_handle_setup_class_ifc(dcd_ctx, req, (usb_ep_dir_t)bm_req_dir);
      }
    }
    break;

    default:
      USB_LOG_ERR_1(log_usb_dcd_handle_setup_class__bad_recp_D, bm_req_recp);
  }

  if(FALSE == result)
  {
    USB_LOG_ERR(log_usb_dcd_handle_setup_class__failed);
  }

  return result;
}

void usb_dcd_vendor_out_cb(struct usb_urb* urb_ptr)
{
  usb_dcd_ctx_t* dcd_ctx; 
  usb_setup_packet_t* req;

  USB_ASSERT(urb_ptr && urb_ptr->dcd_priv_ptr);
  USB_ULOG(ENG_QLOG, "++");

  dcd_ctx = (usb_dcd_ctx_t*)urb_ptr->dcd_priv_ptr;
  req = &dcd_ctx->cached_req;
  dcd_ctx->ctrl_urb.rx.complete_callback = NULL;

  if(req->wLength != urb_ptr->actual_length)
  {
    USB_ULOG_2(DBG_E_QLOG, "invalid transfer length, expected %d, actual %d", req->wLength, 
      urb_ptr->actual_length);
    USB_LOG_ERR_2(log_usb_dcd_vendor_out_cb__length_D_act_length_D, req->wLength, urb_ptr->actual_length);
    usb_fn_dci()->usb_dci_ctrl_error_recover(dcd_ctx->dci_ctx);
    return;
  }

  if(TRUE == dcd_ctx->fd_cb.ctrl_out_cb((uint8*)req, (uint8*)urb_ptr->transfer_buffer_ptr, 
    urb_ptr->actual_length))
  {
    // Ack only when data phase was successfully processed.
    usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_TX, dcd_ctx->setup_status, 0);
  }
  else
  {
    usb_fn_dci()->usb_dci_ctrl_error_recover(dcd_ctx->dci_ctx);
  }
}

int usb_dcd_handle_setup_vendor(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req)
{
  int data_out_len = -1;
  uint8 bm_req_dir = ((req->bmRequestType & USB_SETUP_RT_DIR_MASK) >> USB_SETUP_RT_DIR_POS);
  uint32 payload_len = req->wLength;

  USB_LOG_2(log_handle_setup_vendor__dir_D_len_D, bm_req_dir, payload_len);
  USB_ULOG(ENG_QLOG, "++");

  if (bm_req_dir == DIR_TX)
  {
    if (TRUE == dcd_ctx->fd_cb.ctrl_in_cb((uint8*)req, dcd_ctx->vendor_buff, &payload_len))
    {
      data_out_len = MIN(USB_VENDOR_BUFF_SIZE, payload_len);
      usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, bm_req_dir, dcd_ctx->vendor_buff, payload_len);
    }
  }
  else
  {
    if (req->wLength == 0)
    {
      data_out_len = 0;
      if(TRUE == dcd_ctx->fd_cb.ctrl_out_cb((uint8*)req, NULL, 0))
      {
        // Ack only when data phase was successfully processed.
        usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_TX, dcd_ctx->setup_status, 0);
      }
    }
    else if (req->wLength <= USB_VENDOR_BUFF_SIZE) // Requeue buffer on RX to receive more data from host
    {
      data_out_len = 0;
      dcd_ctx->ctrl_urb.rx.complete_callback = usb_fn_dcd()->usb_dcd_vendor_out_cb;
      memscpy(&dcd_ctx->cached_req, sizeof(usb_setup_packet_t), req, sizeof(usb_setup_packet_t));      
      usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_RX, dcd_ctx->setup_data, req->wLength);      
    }
  }
  return data_out_len;
}

