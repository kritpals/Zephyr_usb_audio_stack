/*==================================================================*/
/**
  @file usb_bulk_fd.c

  BULK function driver implementation

  @file         usb_bulk_fd.c
 
  @brief       Implements USB bulk class.
 
  @details    Implements USB bulk or obex type of class.
 
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
#include "usb_util.h"
#include "usb_fd.h"

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/
#define USB_BULK_MAX_PACKET_SIZE_HS  (512)
#define USB_BULK_MAX_PACKET_SIZE_FS  (64)

/*------------------------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------------------------*/
typedef struct usb_bulk_ctx
{
  usb_dcd_dsc_interface_t* ifc;
  usb_ifc_id  ifc_id;
  uint8  ifc_num;
  usb_device_connect_speed_t speed;
  uint16 max_packet_size;
} usb_bulk_ctx_t;

/*------------------------------------------------------------------------------------------
 * Function Declarations and Definitions
 * ----------------------------------------------------------------------------------------*/
void usb_bulk_notify_speed(usb_device_connect_speed_t speed, void* data)
{
  usb_bulk_ctx_t* bulk_ctx = (usb_bulk_ctx_t*)data;
  USB_ASSERT(bulk_ctx);
  bulk_ctx->speed = speed;

  switch(speed)
  {
    case USB_SUPER_SPEED:
    case USB_HIGH_SPEED:
    {
      bulk_ctx->max_packet_size = USB_BULK_MAX_PACKET_SIZE_HS;
    }
    break;

    case USB_FULL_SPEED:
    default:
    {
      bulk_ctx->max_packet_size = USB_BULK_MAX_PACKET_SIZE_FS;
    }
  }
}

void usb_bulk_set_cfg(void* ctx, usb_dcd_dsc_interface_t* ifc)
{
  usb_bulk_ctx_t* bulk_ctx = (usb_bulk_ctx_t*) ctx;
  USB_ASSERT(bulk_ctx && ifc);
  bulk_ctx->ifc = ifc;
}

usb_dcd_dsc_interface_t* usb_bulk_alloc_desc(uint8 ** dsc, uint16 * len,
  uint16 dsc_size, void * data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, 
  uint32 rev_not_used)
{
  uint8 n_ep = 2;
  uint8 alt_set =0;
  usb_dcd_dsc_interface_t* ifc_itr;
  usb_dcd_dsc_endpoint_t* ep_itr;  
  usb_bulk_ctx_t* bulk_ctx = (usb_bulk_ctx_t* )data;

  USB_ASSERT(bulk_ctx);

  ifc_itr = usb_fn_fd()->usb_fd_alloc_ifc_desc (dsc, len, dsc_size, ifc_num, alt_set, n_ep, 
    USB_INTERFACE_CLASS_VENDOR_SP, USB_INTERFACE_VENDOR_SP_SUBCLASS_VENDOR_SP, 
    USB_INTERFACE_VENDOR_SP_PROTOCOL_VENDOR_SP, USB_INTERFACE_STR_INDEX_NONE);

  ifc_itr->id = USB_IFC_ID_BULK;
  ifc_itr->cs_dsc = NULL;
  ifc_itr->cs_dsc_size = 0;

  // Allocate IN and OUT endpoint each
  ep_itr = usb_fn_fd()->usb_fd_alloc_ep_desc(dsc, len, dsc_size, ++(*ep_in_num), USB_EP_ADDR_IN, 
    USB_EP_ATTR_BULK, USB_ENDPOINT_BINTERVAL_NONE, bulk_ctx->max_packet_size);

  INSERT_TAIL(usb_dcd_dsc_endpoint, ifc_itr->endpoints, ep_itr);
  ep_itr->ifc = ifc_itr;
  ep_itr->cs_dsc = NULL;
  ep_itr->cs_dsc_size = NULL;

  ep_itr = usb_fn_fd()->usb_fd_alloc_ep_desc(dsc, len, dsc_size, ++(*ep_out_num), USB_EP_ADDR_OUT, 
     USB_EP_ATTR_BULK, USB_ENDPOINT_BINTERVAL_NONE, bulk_ctx->max_packet_size);
  
   INSERT_TAIL(usb_dcd_dsc_endpoint, ifc_itr->endpoints, ep_itr);
   ep_itr->ifc = ifc_itr;
   ep_itr->cs_dsc = NULL;
   ep_itr->cs_dsc_size = NULL;
 
  return ifc_itr;
}

void usb_bulk_deinit(void* data)
{
  usb_bulk_ctx_t* bulk_ctx = (usb_bulk_ctx_t*) data;
  USB_ASSERT(bulk_ctx);
  usb_fn_mem_util()->usb_free((void**)&bulk_ctx);
}

void* usb_bulk_init(usb_ifc_id ifc_id, uint8 ifc_num, void* data)
{
  usb_bulk_ctx_t* bulk_ctx;
  USB_ASSERT(bulk_ctx = (usb_bulk_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_bulk_ctx_t)));
  bulk_ctx->ifc_id = ifc_id;
  bulk_ctx->ifc_num = ifc_num;
  return bulk_ctx;
}

/*----------------------------------------------------------------------------
 * Function table definitions - Bulk layer
 * -------------------------------------------------------------------------*/

usb_fn_tbl_bulk_t fn_tbl_bulk = 
{
  usb_bulk_notify_speed,
  usb_bulk_set_cfg,
  usb_bulk_alloc_desc,
  usb_bulk_deinit,
  usb_bulk_init,
};

