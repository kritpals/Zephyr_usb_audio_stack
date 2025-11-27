#ifndef USB_HID_FD_H
#define USB_HID_FD_H
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
/*  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/func/usb_hid_fd.h#9 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_urb.h"
#include "usb_hid_api.h"
#include "usb_dcd.h"
#include "usb_api.h"

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

// bRequest values for HID Class Specific Requests
#define USB_REQ_CLASS_HID_GET_REPORT (0x01)
#define USB_REQ_CLASS_HID_SET_REPORT (0x09)
#define USB_REQ_CLASS_HID_GET_IDLE   (0x02)
#define USB_REQ_CLASS_HID_SET_IDLE   (0x0A)


//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------

//struct usb_dcd_dsc_interface;
//typedef struct usb_dcd_dsc_interface usb_dcd_dsc_interface_t;

//struct usb_hid_ctx;
//typedef struct usb_hid_ctx usb_hid_ctx_t;

//struct usb_fd_ctx;
//typedef struct usb_fd_ctx usb_fd_ctx_t;


typedef struct usb_hid_ctx
{
  usb_dcd_dsc_interface_t* ifc;
  usb_ifc_id  ifc_id;
  uint8  ifc_num;
  uint8  idle_rate;
  uint8  bInterval_ep;

  usb_hid_buff_t* report_buffer;
  usb_hid_bitmask_cmd_t last_report;
  boolean is_report_in_progress;
  boolean is_last_report_pending;

  //debug variable
  uint32 req_idx;
  uint32 drop_cnt;
  uint32 cb_cnt;
} usb_hid_ctx_t;

typedef PACKED struct usb_hid_desc
{
  uint8   bLength;              // length of descriptor
  uint8   bDescriptorType;      // HID_DESCRIPTOR
  uint16  bcdHID ;              // HID class specification release
  uint8   bCountryCode;         // Country code of localized hardware
  uint8   bNumDescriptors;      // Number of class descriptors
  uint8   bDescriptorType1;      // Type of class descriptor
  uint16  wDescriptorLength;    // Total size of report descriptor
} PACKED_POST usb_hid_desc_t;

typedef struct usb_fn_tbl_hid
{
  void (*usb_hid_notify_speed)(usb_device_connect_speed_t speed, void* data);
  void (*usb_hid_set_cfg)(void* ctx, usb_dcd_dsc_interface_t* ifc);
  uint16 (*usb_hid_cs_ifc_desc)(uint8** dsc, uint16* len, uint16 dsc_size);
  usb_dcd_dsc_interface_t* (*usb_hid_alloc_desc)(uint8 ** dsc, uint16 * len, uint16 dsc_size, void * data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, uint32 rev_not_used);
  void (*usb_hid_deinit)(void* data);
  void* (*usb_hid_init)(usb_ifc_id ifc_id, uint8 ifc_num, void* data);
  uint8* (*usb_hid_handle_get_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* len);
  boolean (*usb_hid_handle_set_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* buff, uint32 len);
  void (*usb_hid_tx_cb)(usb_urb_t* urb_ptr);
  void (*usb_hid_tx)(void* fd_ptr, usb_ifc_id ifc_id, usb_hid_bitmask_cmd_t input);
  void (*usb_hid_enum_complete)(void* fd_ptr, uint8 ifc_num);
} usb_fn_tbl_hid_t;

extern usb_fn_tbl_hid_t fn_tbl_hid;
#define usb_fn_hid()  (&fn_tbl_hid)

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#endif /* #ifndef USB_AUDIO_CLASS_H */

