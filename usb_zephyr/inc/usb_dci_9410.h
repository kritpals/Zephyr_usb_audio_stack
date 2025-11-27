#ifndef USB_DCI_9410_H
#define USB_DCI_9410_H

/*=======================================================================================*/
/**
 * @file        usb_dci_9410.h
 * @author:     kameya
 * @date        12-December-2017
 *
 * @brief       USB DCI (Device-Controller-Interface) target specific defines, 
 *              types and API.
 *
 * @details     Declaration of target specific USB clock enable APIs.
 *              Declaration of target specific USB PHY initialization APIs.
 *              Declaration of target specific USB PHY configuration APIs.
 *              
 * @ref         Target specigic hardware programming guide.
 *              
 *
 *              Copyright (c) 2017 Qualcomm Technologies, Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*/
/*=======================================================================================*/

//=========================================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dci/usb_dci_9410.h#1 $ $DateTime: 2018/02/12 17:09:34 $ $Author: pwbldsvc $
// 
// when         who       what, where, why
// ----------   ---       -----------------------------------------------------------------
// 12/13/2017   kameya    First Draft
// ========================================================================================

//-----------------------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------------------
#include "comdef.h"       // common defines and types
#include "usb_common.h"
#include "usb_dci.h"

//-----------------------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Type Declarations
//-----------------------------------------------------------------------------------------

typedef enum 
{
  USB_PHY_MODE_UTMI = 0,
  USB_PHY_MODE_ULPI,
  USB_PHY_MODE_MAX
} usb_phy_mode;

typedef struct usb_fn_tbl_dci_target
{
  void (*usb_dci_reset_hw)(void);
  void (*usb_dci_select_utmi_clk)(void);
  void (*usb_dci_enable_vbus_valid)(usb_max_speed_required_t speed_required);
  void (*usb_dci_select_phy_mode)(usb_phy_mode phy_mode);
  void (*usb_dci_update_override)(void);
  void (*usb_dci_hs_phy_init)(void);
  void (*usb_dci_deinit_hs_phy)(void);
} usb_fn_tbl_dci_target_t;

//-----------------------------------------------------------------------------------------
// Function Declarations and Documentation
//-----------------------------------------------------------------------------------------

extern usb_fn_tbl_dci_target_t fn_tbl_dci_target;
#define usb_fn_dci_target()   (&fn_tbl_dci_target)


#endif /* USB_DCI_9410_H */
