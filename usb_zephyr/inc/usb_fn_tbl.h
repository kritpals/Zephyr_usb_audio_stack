/*=======================================================================*//**
 * @file        usb_fn_tbl.c
 * @author:     kameya
 * @date        01-Jan-2018
 *
 * @brief       USB driver function table implementation.
 *
 * @details     This file contains function tables which can be used for
 *              calling USB APIs.
 * @note        
 *
 *              Copyright 2017-2018 Qualcomm Technologies, Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/


// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/common/usb_fn_tbl.h#1 $ 
// $DateTime: 2018/02/12 17:09:34 $ $Author: pwbldsvc $
// 
// when         who        what, where, why
// --------   ---        ----------------------------------------------------------
//
// ===========================================================================
#ifndef USB_FN_TBL__H_
#define USB_FN_TBL__H_

/*----------------------------------------------------------------------------
* Include Files
* -------------------------------------------------------------------------*/
#include "comdef.h" 
#include "log_enum_usb.h"
#include "usb_common.h"
#include "usb_dci_9410.h"
#include "usb_dci.h"
#include "usb_dcd.h"
#include "usb_dcd_ch9.h"
#include "usb_fd.h"

/*----------------------------------------------------------------------------
 * Constants definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

// usb_fn_tbl_dci_t is defined in usb_dci.h - do not redefine here
// usb_fn_tbl_dci_target_t is defined in usb_dci_9410.h - do not redefine here

struct usb_fn_tbl_fd;
typedef struct usb_fn_tbl_fd usb_fn_tbl_fd_t;

typedef struct usb_fn_tbl
{ 
  usb_fn_tbl_fd_t fd;
  usb_fn_tbl_dcd_t dcd;
  usb_fn_tbl_dci_t dci;
  usb_fn_tbl_dci_target_t dci_target;
} usb_fn_tbl_t;

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

extern usb_fn_tbl_t usb_fn_tbl_g;

/*----------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* -------------------------------------------------------------------------*/
// Macros usb_fn_fd(), usb_fn_dcd(), usb_fn_dci(), usb_fn_dci_target() 
// are defined in their respective header files (usb_fd.h, usb_dcd.h, usb_dci.h, usb_dci_9410.h)

#endif /*USB_FN_TBL__H_*/
