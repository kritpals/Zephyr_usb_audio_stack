#ifndef USB_AUDIO_DCD_H
#define USB_AUDIO_DCD_H
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
/*  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dcd/usb_class_dcd.h#6 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_urb.h"
#include "usb_dcd_ch9.h" /* for USB descriptor types */
#include "usb_common.h"
#include "usb_dcd.h"

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------
void usb_dcd_class_status2_ack_cb(struct usb_urb* urb_ptr);
void usb_dcd_class_data_cb(struct usb_urb* urb_ptr);
void usb_dcd_handle_class_status3_req_ifc(struct usb_urb* urb_ptr);
void usb_dcd_handle_class_status3_req_ep(struct usb_urb* urb_ptr);
boolean usb_dcd_handle_setup_class_ifc(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
boolean usb_dcd_handle_setup_class_ep(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
boolean usb_dcd_handle_setup_class(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);
void usb_dcd_vendor_out_cb(struct usb_urb* urb_ptr);
int usb_dcd_handle_setup_vendor(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/




#endif /* #ifndef USB_AUDIO_DCD_H */

