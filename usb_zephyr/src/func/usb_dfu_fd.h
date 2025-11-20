#ifndef USB_DFU_FD_H
#define USB_DFU_FD_H
/*=======================================================================*//**
  @file usb_dfu_fd.h

  Audio class driver implementation

  @file         usb_dfu_fd.h
 
  @brief        Skeleton documentation example
 
  @details      Audio class has two types of interfaces. 
				Audio control and streaming type interfaces.
				This module supports both.
 
               Copyright (c) 2017 Qualcomm Technologies Inc.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*/
/*========================================================================*/
/*  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/func/usb_dfu_fd.h#7 $ */

/*------------------------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------------------------*/
#include "usb_fd.h"
#include "usb_dfu.h"

//------------------------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// Type Declarations
//------------------------------------------------------------------------------------------

typedef PACKED struct usb_dfu_desc
{
  uint8   bLength;              // length of descriptor
  uint8   bDescriptorType;      // DFU_DESCRIPTOR
  uint8   bmAttributes;         // Contains capabilities of device
  uint16  wDetachTimeOut;       // No. of milliseconds device will wait for USB reset
  uint16  wTransferSize;        // No. of bytes device can accept per control write transaction
  uint16  bcdDFUVersion;        // Vesion of DFU specs release
}
PACKED_POST usb_dfu_desc_t;

typedef PACKED struct
{
  uint8 bStatus;
  uint32 bwPollTimeout:24;
  uint8 bState;
  uint8 iString;
} PACKED_POST dfu_get_status_resp_t;

typedef PACKED struct
{
  uint8 bState;
} PACKED_POST dfu_get_state_resp_t;

//DFU device state
typedef enum
{
  DFU_APP_IDLE = 0,        // Device running its normal application
  DFU_APP_DETACH,          // Received DFU_DETACH, waiting for USb reset
  DFU_IDLE,                // In DFU mode and waiting for requests
  DFU_DNLOAD_SYNC,         // Received a block and waiting for DFU_GETSTATUS
  DFU_DNLOAD_BUSY,         // Device is programming a control-write block into its non-volatile memory
  DFU_DNLOAD_IDLE,         // Processing download requests, expecting DFU_DNLOAD
  DFU_MANIFEST_SYNC,       // Received final block of firmware or completed manifestation phase and waiting for DFU_GETSTATUS
  DFU_MANIFEST,            // Device is in the manifestation phase
  DFU_MANIFEST_WAIT_RESET, // Device has programmed its memory and waiting for USB reset or power on reset
  DFU_UPLOAD_IDLE,         // Processing an upload operation. Expecting DFU_UPLOAD
  DFU_ERROR,               // Error has occured, awaiting for DFU_CLRSTATUS request
} usb_dfu_state;

typedef enum
{
  DFU_EVENT_GET_STATE = 0,
  DFU_EVENT_GET_STATUS,
  DFU_EVENT_DETACH,
  DFU_EVENT_DNLOAD,
  DFU_EVENT_DNLOAD_END,
  DFU_EVENT_UPLOAD,
  DFU_EVENT_UPLOAD_END,
  DFU_EVENT_ABORT,
  DFU_EVENT_CLEAR_STATUS,
  DFU_EVENT_DNLOAD_INVALID,
} usb_dfu_event_t;

typedef struct usb_dfu_init_cfg
{
  usb_op_mode_t op_mode;
  dfu_dnload_cb dn_cb;
  dfu_upload_cb up_cb;
  void (*notify) (uint32 event, uint32 client_id, void* data);
} usb_dfu_init_cfg_t;

typedef struct usb_dfu_ctx
{
  usb_dcd_dsc_interface_t* ifc;
  usb_ifc_id  ifc_id;
  uint8  ifc_num;
  usb_op_mode_t op_mode;
  dfu_dnload_cb dn_cb;
  dfu_upload_cb up_cb;
  void (*notify) (uint32 event, uint32 client_id, void* data);

  boolean use_rsvd;
  usb_dfu_status status;
  usb_dfu_state state;
  dfu_get_status_resp_t* resp;
  uint8* payload_buff;
  usb_device_connect_speed_t speed;
} usb_dfu_ctx_t;

typedef struct usb_fn_tbl_dfu
{
  void (*usb_dfu_get_status)(dfu_get_status_resp_t* resp, uint8 status, uint8 state);
  boolean (*usb_dfu_update_state)(usb_dfu_ctx_t * dfu_ctx, usb_dfu_event_t event);
  uint8* (*usb_dfu_handle_get_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* len);
  void (*usb_dfu_set_req_status_comp_cb)(void* ctx, usb_setup_packet_t* req);
  boolean (*usb_dfu_handle_set_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* buff, uint32 len);
  void (*usb_dfu_notify_speed)(usb_device_connect_speed_t speed, void* data);
  void (*usb_dfu_set_cfg)(void* ctx, usb_dcd_dsc_interface_t* ifc);
  uint16 (*usb_dfu_alloc_cs_desc)(uint8** dsc, uint16* len, uint16 dsc_size);
  usb_dcd_dsc_interface_t* (*usb_dfu_alloc_desc)(uint8 ** dsc, uint16 * len, uint16 dsc_size, void * data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, uint32 rev_not_used);
  void (*usb_dfu_deinit)(void* data);
  void* (*usb_dfu_init)(usb_ifc_id ifc_id, uint8 ifc_num, void* data);
} usb_fn_tbl_dfu_t;

extern usb_fn_tbl_dfu_t fn_tbl_dfu;
#define usb_fn_dfu()  (&fn_tbl_dfu)

#endif /* #ifndef USB_DFU_FD_H */

