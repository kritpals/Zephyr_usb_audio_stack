#ifndef USB_DCI_API_H
#define USB_DCI_API_H

/*=======================================================================*//**
 * @file        usb_dci_api.h
 * @author:     amirs
 * @date        14-July-2008
 *
 * @brief       USB (Qualcomm High-Speed USB) DCI (Device-Controller-Interface) exported API.
 *
 * @details     The USB (Qualcomm High-Speed USB) DCI (Device-Controller-Interface) 
 *              acts like a HAL (Hardware Abtraction Layer) for Chip-Idea USB Hardware.
 *              The DCI should supply generic API that hides USB Hardware registers access from the upper layers.
 *              It should not be aware of Chapter-9 or specific function drivers (Mass-Storage , CDC , HID etc).
 *              It should be simple without any management algorithms.
 *              
 *              The USB Device Core Driver (DCD) shall use the DCI to implement
 *              the USB protocol chapter 9 enumeration,
 *              and handling of special BUS signaling : Reset / Suspend / Resume.
 * 
 * @note        This DCI is implementing the ChipIdea hardware core.
 *              The DCI depends on the USB Core (a.k.a LINK) connection to the PHY:
 *              When a 3-wired PHY is connected (Full-Speed only) then the LINK
 *              can not control the VBUS D+ wire via the Run/Stop bit.
 * 
 * @ref         ChipIdea spec "CI13612a HighSpeed USB OnTheGo Controller Core".
 *
 *              Copyright (c) 2008-2010 QUALCOMM Incorporated.
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
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dci/usb_dci.h#3 $$DateTime: 2018/05/30 12:19:59 $$Author: pwbldsvc $
// 
// when       who      what, where, why
// --------   ---      ----------------------------------------------------------
// 09/17/13   shreyasr Added support for SNPS controller 
// 04/27/11   dpatnaik Added support for 8960 FLCB
// 04/27/11   dpatnaik Merged important FLCB related changes from 2.2 branch
// 08/30/10   dpatnaik Port USB to RPM, add ULPI based charger detection
// 07/14/08   amirs    First Draft
// 08/08/08   amirs    First working DLOAD process
// 08/11/08   amirs    Add files and functions headers according to coding standard.
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h"           // basic types as byte word uint32 etc
#include "usb_dci_private.h"

//Type define
#include "usb_dcd_ch9.h"
#include "usb_common.h"
#include "usb_urb.h"

#include "usb_util.h"         // for mutex
#include "usb_dci_ulpi.h"     // ulpi debug ctx
#include "usb_log.h"

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

#define DCI_LNK_TRB_SIZE            (1)
#define DCI_TRBS                    (((USB_URB_MAX)*(DCI_MAX_TRBS+DCI_ZLP_TRB))+ DCI_LNK_TRB_SIZE)

typedef struct usb_dcd_callback
{                      
  void (*notify)(void* dcd_ctx_ptr, usb_notify_events_t event, void *buffer_ptr);
} usb_dcd_callback_t;

typedef struct usb_isoc_reconfig_sess
{
  uint8 ep;
  uint8 dir;
  uint8 bm1;
} usb_isoc_reconfig_sess_t;

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------

typedef enum
{
  USB_DCI_U1_INIT_ENABLE,
  USB_DCI_U2_INIT_ENABLE,
  USB_DCI_U1_U2_ACCPET_ENABLE,
} usb_dci_u1_u2_event_type;

typedef enum
{
  // Link Power Events
  PWR_EVNT_SW,
  PWR_EVNT_PHY_L2,
  PWR_EVNT_PHY_P3,

  // QMP PHY Events
  QMP_PHY_LFPS_IRQ,

  // USB2 PHY Events
  USB2_PHY_IRQ,

  // Generic wakeup event
  GENERIC_WAKEUP_EVNT,

  PWR_EVNT_MAX = 0x7FFFFFFF,
} pwr_evnt_t;

// There is only one trb_ring per endpoint.
typedef struct usb_trb_ring_info {
  usb_urb_t                *urb_ptr[USB_URB_MAX];
  uint32                    ep_state;
  uint8                     xfer_res_idx;
  uint8                     trb_idx;           // Keeps track of TRB to be queued by SW next.
  uint8                     trb_submit_idx;    // Keeps track of TRB submitted to HW in start / update transfer
  uint8                     urb_idx;           // Keeps track of URB to be queued by SW next.
  uint8                     urb_comp_idx;      // Keeps track of URB waiting to be completed by HW.
  uint8                     trb_comp_idx;      // Keeps track of TRB waiting to be completed by HW.
  uint8                     swo[DCI_TRBS];     // Keeps track of pending software processing for a TRB.
  trb_ctl_type_t            trb_ctl;

  // Isoc parameters
  uint8                     b_interval;
  uint16                    xfer_nrdy_uf;
  uint16                    xfer_nrdy_uf_prev;
  uint16                    xfer_nrdy_uf_diff;
  uint8                     xfer_nrdy_uf_diff_cnt;
  uint8                     missed_isoc;
} usb_trb_ring_t;


struct usb_dci_ctx;
typedef struct usb_dci_ctx usb_dci_ctx_t;

typedef struct usb_fn_tbl_dci
{
  void (*usb_dci_handle_u1_u2_enable) (usb_dci_u1_u2_event_type event, boolean enable);
  void (*usb_dci_update_packet_size) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_test_mode_enable) (usb_dci_ctx_t* dci_ctx, boolean enable, uint32 test_mode);
  void (*usb_dci_handle_test_mode)(usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_configure_device_mode)(boolean is_l1_enable, usb_max_speed_required_t speed_required);
  void (*usb_dci_hw_init) (usb_dci_ctx_t* dci_ctx, usb_max_speed_required_t* max_speed);
  uint32 (*usb_dci_init) (usb_core_type core_id, void** dci_ctx_ptr, void* dcd_ctx, usb_dcd_callback_t* cb_table_ptr, uint32 feature_flags);
  void (*usb_dci_core_init) (usb_dci_ctx_t* dci_ctx);
  uint32 (*usb_dci_write_ep_cmd)(usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, usb_ep_cmd_t *ep_cmd);
  uint32 (*usb_dci_write_dev_cmd) (usb_dci_ctx_t* dci_ctx, usb_dev_cmd_t *dev_cmd);
  void (*usb_dci_event_buffer_init) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_set_run_stop) (usb_dci_ctx_t* dci_ctx, boolean set);
  uint8 (*usb_dci_get_bm1_from_uf) (uint16 uf);
  void (*usb_dci_handle_ep_event) (usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt);
  void (*usb_dci_handle_dev_event) (usb_dci_ctx_t* dci_ctx, usb_event_devt_t  *devevt);
  void (*usb_dci_poll_events) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_ctrl_transfers) (usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt);
  void (*usb_dci_inc_trb_idx) (usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, uint8 *idx);
  void (*usb_dci_handle_transfer_complete) (usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt);
  void (*usb_dci_handle_usb_reset) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_connect_done) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_usb_disconnect) (usb_dci_ctx_t* dci_ctx);
  usb_link_state_t (*usb_dci_get_link_state) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_link_status_change) (usb_dci_ctx_t* dci_ctx, uint32 state);
  void (*usb_dci_drive_remote_wakeup) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_suspend_entry)(usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_wakeup) (usb_dci_ctx_t* dci_ctx);
  uint8 (*usb_dci_get_address) (void);
  void (*usb_dci_set_address) (uint8 address);
  uint32 (*usb_dci_get_event_cnt) (void);
  uint32 (*usb_dci_stall_endpoint) (usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
  uint32 (*usb_dci_unstall_endpoint) (usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
  void (*usb_dci_config_endpoint) (usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, uint8 ep_type, 
    uint8 ep_interval, uint16 max_packet_length, boolean zero_length_transfer);
  uint32 (*usb_dci_unconfig_endpoint) ( uint8 ep, uint8 dir);
  uint32 (*usb_dci_submit_trb_data) (usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
  void (*usb_dci_init_trb_ring)(usb_dci_ctx_t* dci_ctx);
  uint32 (*usb_dci_prepare_trbs) (usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, 
    usb_urb_t* urb_ptr, uint8 trb_ctl);
  uint32 (*usb_dci_transfer_data_request) (usb_dci_ctx_t* dci_ctx, 
    uint8 ep, uint8 dir, usb_urb_t* urb_ptr, trb_ctl_type_t trb_ctrl);
  void (*usb_dci_ctrl_error_recover) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_ctrl_xfer_state_machine) (usb_dci_ctx_t* dci_ctx, usb_urb_t *urb_ptr, 
    trb_ctl_type_t *trb_ctl);
  uint32 (*usb_dci_ctrl_submit_request) (usb_dci_ctx_t* dci_ctx, uint8 dir);
  uint32 (*usb_dci_transfer_request) (usb_dci_ctx_t* dci_ctx, usb_urb_t* urb_ptr);
  uint32 (*usb_dci_cancel_transfer) (usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
  uint32 (*usb_dci_shutdown) (usb_dci_ctx_t** dci_ptr);
  uint32 (*usb_dci_get_speed) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_set_max_packet_size) (usb_dci_ctx_t* dci_ctx, uint32 max_packet_size);
  uint32 (*usb_dci_get_max_packet_size) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_set_select) (usb_dci_ctx_t* dci_ctx);
  uint32 (*usb_dci_buffer_is_empty) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_enter_lpm) (usb_dci_ctx_t* dci_ctx, pwr_evnt_t event);
  uint32 (*usb_dci_poll_pwr_event) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_event)(usb_dci_ctx_t* dci_ctx, uint32 pwr_event);
  uint32 (*usb_dci_remote_wakeup) (usb_dci_ctx_t* dci_ctx);
  void (*usb_dci_handle_remote_wakeup_enabled) (usb_dci_ctx_t* dci_ctx, boolean enabled);
  boolean (*usb_dci_is_remote_wakeup_enabled) (usb_dci_ctx_t* dci_ctx);
} usb_fn_tbl_dci_t; 

struct usb_dci_ctx
{
  // Important Note: do not add new variables on top that causes TRB alignment issues.
  usb_trb_t usb_trb_list[DCI_MAX_ENDPOINTS][DCI_MAX_DIRECTION][DCI_TRBS];
  usb_trb_ring_t usb_trb_ring[DCI_MAX_ENDPOINTS][DCI_MAX_DIRECTION];
  uint8 usb_event_buffer[EVENT_BUFFER_SIZE];
  usb_event_buffer_info_t usb_evt_buf_info;
  uint8* usb_control_tx_buffer;
  uint32 usb_dci_max_packet_size;
  uint32 usb_dci_ep0_max_packet_size;
  usb_dci_ctrl_trb_state_t ctrl_state;
  usb_ep_dir_t ctrl_data_dir;
  usb_device_connect_speed_t speed;
  //usb_max_speed_required_t max_speed;
  usb_link_state_t  link_state;

  usb_dcd_callback_t dcd_cb;
  void* dcd_ctx;

  usb_core_type core_id;
  boolean is_attached;
  boolean is_suspended;
  boolean is_disconnected;
  boolean is_usb_clk_on;
  boolean is_l1_feature_enabled;
  boolean is_l2_feature_enabled;
  boolean test_mode_enabled;
  uint32 test_mode;

  boolean usb_set_stall_on_xfer_nrdy_wrong_dir;
  boolean usb_dci_soft_rst_enabled;
  boolean remote_wakeup_enabled;
  boolean phy_in_l2;

  #if defined(TARGET_FPGA)
  usb_ulpi_debug_ctx_t* ulpi_debug;
  #endif
};


//----------------------------------------------------------------------------
// Function Declarations and Documentation
//----------------------------------------------------------------------------
extern usb_fn_tbl_dci_t fn_tbl_dci;
#define usb_fn_dci()    (&fn_tbl_dci)

#endif // USB_DCI_API_H


