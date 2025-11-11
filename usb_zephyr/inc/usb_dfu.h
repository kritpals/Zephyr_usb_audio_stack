#ifndef USB__DFU_H
#define USB__DFU_H
/*=======================================================================*//**
 * @file      usb_dfu.h
 * @author:   kameya
 * @date      04/06/2017
 *
 * @brief     USB DFU Class Specific header
 *
 * @details   This file contains the implementation of DFU APIs to be used by
 *            Audio Service Layer.
 *
 * @note
 *
 *            Copyright 2017 Qualcomm Technologies Inc.
 *            All Rights Reserved.
 *            Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h" // common defines - basic types as uint32 etc
#include "usb_common.h"

typedef enum
{
  DFU_OK = 0x00,           // No error
  DFU_ERR_TARGET,          // File is not targeted for use by this device
  DFU_ERR_FILE,            // File is per device but failed some vendor specific test
  DFU_ERR_WRITE,           // Device unable to write to memory
  DFU_ERR_ERASE,           // Memory erase function failed
  DFU_ERR_CHECK_ERASED,    // Memory erase check failed
  DFU_ERR_PROG,            // Program memory function failed
  DFU_ERR_VERIFY,          // Programmed memory failed verification
  DFU_ERR_ADDRESS,         // Cannot program memory, received address out of range
  DFU_ERR_NOTDONE,         // Received DFU_DNLOAD with wLength=0, but device think its not done
  DFU_ERR_FIRMWARE,        // Device's firmware is corrupt. Cannot return to non-DFU operations
  DFU_ERR_VENDOR,          // iString indicates a vendor specific error
  DFU_ERR_USBR,            // Device detected unexpected USB reset signalling
  DFU_ERR_POR,             // Device detected unexpected power on reset
  DFU_ERR_UNKNOWN,         // Unknown error
  DFU_ERR_STALLED_PKT,     // Device stalled an unexpected request
} usb_dfu_status;

typedef usb_dfu_status (*dfu_dnload_cb)(uint16 block_num, uint8* payload, uint32 payload_size);
typedef usb_dfu_status (*dfu_upload_cb)(uint16 block_num, uint8* payload, uint32* payload_size);

typedef struct usb_dfu_open_cfg
{
  dfu_dnload_cb dn_cb;
  dfu_upload_cb up_cb;
} usb_dfu_open_cfg_t;

// ===================================================================
/**
 * @function  usb_open_dfu
 * 
 * @brief   API to register DFU client.
 *
 * @details API to register DFU client.
 * 
 * @param   client_ctx - [IN] - usb_ctx of the DFU client
 *          ifc_id - [IN]  - DFU identifier -- USB_IFC_ID_DFU
 *          cfg - [IN] DFU - download and upload callback APIs.
 *          event_cb - [IN] - handler for DFU_ENTRY and DFU_EXIT events.
 * 
 * @return  SUCCESS,  zero value.
 *              FAILURE, non-zero value.
 */
// ===================================================================
uint32 usb_open_dfu (client_ctx_t** client_ctx, usb_ifc_id ifc_id, usb_dfu_open_cfg_t* cfg,
  usb_event_func_t event_cb);

#endif /* USB__DFU_H */
