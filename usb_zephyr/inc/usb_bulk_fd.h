#ifndef USB_BULK_FD_H
#define USB_BULK_FD_H
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
/*  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/func/usb_bulk_fd.h#4 $ */

/*------------------------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------------------------*/
#include "usb_fd.h"

//------------------------------------------------------------------------------------------
// Type Declarations
//------------------------------------------------------------------------------------------

typedef struct usb_fn_tbl_bulk
{
  void (*usb_bulk_notify_speed)(usb_device_connect_speed_t speed, void* data);
  void (*usb_bulk_set_cfg)(void* ctx, usb_dcd_dsc_interface_t* ifc);
  usb_dcd_dsc_interface_t* (*usb_bulk_alloc_desc)(uint8 ** dsc, uint16 * len, uint16 dsc_size, void * data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, uint32 rev_not_used);
  void (*usb_bulk_deinit)(void* data);
  void* (*usb_bulk_init)(usb_ifc_id ifc_id, uint8 ifc_num, void* data);
} usb_fn_tbl_bulk_t;

//------------------------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//------------------------------------------------------------------------------------------
extern usb_fn_tbl_bulk_t fn_tbl_bulk;
#define usb_fn_bulk() (&fn_tbl_bulk)

//------------------------------------------------------------------------------------------
// Function Declarations
//------------------------------------------------------------------------------------------

#endif /* #ifndef USB_BULK_FD_H */

