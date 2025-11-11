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
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/common/usb_fn_tbl.c#2 $ 
// $DateTime: 2018/05/03 14:04:39 $ $Author: pwbldsvc $
// 
// when         who        what, where, why
// --------   ---        ----------------------------------------------------------
//
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "usb_fn_tbl.h"

/*----------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* -------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
// API Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// AL Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// BULK Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// DFU Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// HID Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Audio FD Layer Function Declarations
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// FD Function Declarations
//------------------------------------------------------------------------------
void usb_fd_alloc_ep_comp_desc(uint8** dsc, uint16* len, uint16 dsc_size, uint8 burst_size, uint8 attr, uint8 bpi);
usb_dcd_dsc_endpoint_t* usb_fd_alloc_ep_desc(uint8** dsc, uint16* len, uint16 dsc_size, uint8 ep_num, uint8 ep_mask, uint8 ep_attr, uint8 ep_interval, uint16 max_packet_size);
usb_dcd_dsc_interface_t* usb_fd_alloc_ifc_desc(uint8** dsc, uint16* len, uint16 dsc_size, uint8 ifc_index, uint8 alt_setting, uint8 n_ep, uint8 ifc_class, uint8 subclass, uint8 protocol, uint8 str_index);
usb_dcd_dsc_configuration_t * usb_fd_create_cfg_desc(uint8** dsc, uint16* len, uint16 dsc_size, uint8 id, uint8 n_ifc);
int usb_fd_set_cfg(usb_dcd_dsc_configuration_t* cfg, usb_setup_packet_t* req);
usb_bos_desc_t* usb_fd_alloc_bos_desc(usb_fd_ctx_t* fd_ctx);
usb_dcd_dsc_configuration_t* usb_fd_alloc_audio_cfg(usb_fd_ctx_t* fd_ctx, usb_ifc_id* usb_comp, uint8 n_ifc, usb_device_connect_speed_t speed, usb_audio_class_rev_t audio_rev, uint8 config_num);
void usb_fd_set_transfer_status(usb_fd_ctx_t* fd_ctx, uint32 transfer_status);
void usb_fd_init_urb(usb_fd_ctx_t* fd_ctx);
void usb_fd_notify(void* fd_ctx_ptr, usb_notify_events_t event);
boolean usb_fd_init(usb_fd_ctx_t** fd_ctx_ptr, usb_api_callback_t api_cb, usb_audio_dev_config_t* dev_cfg, usb_max_speed_required_t speed_required);
void usb_fd_shutdown(usb_fd_ctx_t** fd_ctx_ptr);
uint32 usb_fd_tx_pkt(usb_fd_ctx_t* fd_ctx, unsigned char *pkt, uint32 len, uint32 req_id, uint32 client_id, void* cb_data);
uint32 usb_fd_hid_report(usb_fd_ctx_t* fd_ctx, usb_hid_bitmask_cmd_t report_mask, uint32 client_id);
uint32 usb_fd_rx_pkt(usb_fd_ctx_t* fd_ctx, void *buff_ptr, uint32 len, uint32 req_id, uint32 client_id, void* cb_data);
uint32 usb_fd_cancel_transfer(usb_fd_ctx_t* fd_ctx, uint32 client_id);
uint32 usb_fd_cancel_transfer_dir(usb_fd_ctx_t* fd_ctx, uint32 client_id, uint8 dir);
void usb_fd_poll(usb_fd_ctx_t* fd_ctx);
void usb_fd_reset(usb_fd_ctx_t* fd_ctx);
uint32 usb_fd_get_max_packet_size(usb_fd_ctx_t* fd_ctx);
usb_device_connect_speed_t usb_fd_get_speed(usb_fd_ctx_t* fd_ctx);
void* usb_fd_get_dci_ctx(usb_fd_ctx_t* fd_ctx);
void usb_fd_set_core(usb_fd_ctx_t* fd_ctx, usb_core_type core_id);
boolean usb_fd_is_usb_configured(usb_fd_ctx_t* fd_ctx);

//------------------------------------------------------------------------------
// DCD Function Declarations
//------------------------------------------------------------------------------
uint32 usb_dcd_desc_max_packet_size(usb_device_connect_speed_t speed);
void usb_dcd_create_dev_desc(usb_desc_device_t** dev_desc, uint16 vendor_id, uint16 product_id, usb_device_connect_speed_t speed, usb_max_speed_required_t speed_required, uint8 n_cfg);
void usb_dcd_create_dev_qual_desc(usb_desc_dev_qual_t** dev_qual_desc);
void usb_dcd_allocate_dev_qual(usb_dcd_dsc_qual_t** dev_qual);
void usb_dcd_allocate_strings(usb_dcd_ctx_t* dcd_ctx, uint16 lang_id, uint8* manuf_str, uint8* product_str);
void usb_dcd_create_ep_comp_desc(usb_ep_comp_desc_t** ep_comp_ptr, uint8 burst_size, uint8 attr, uint8 bpi);
void usb_dcd_create_ep_desc(usb_dcd_dsc_endpoint_t** endpoint, uint8 ep_num, uint8 ep_mask, uint8 ep_attr, uint8 ep_interval, uint16 max_packet_size);
void usb_dcd_create_ifc_desc(usb_dcd_dsc_interface_t** interface, uint8 ifc_index, uint8 alt_setting, uint8 n_ep, uint8 ifc_class, uint8 subclass, uint8 protocol, uint8 str_index);
usb_dcd_dsc_configuration_t* dcd_get_config_tree(const usb_dcd_ctx_t* dcd_ctx);
int dcd_get_config_value(const usb_dcd_ctx_t* dcd_ctx);
usb_dcd_dsc_configuration_t* find_config_by_value(const usb_dcd_ctx_t* dcd_ctx, uint8 value);
usb_dcd_dsc_interface_t* get_curr_ifc_alt_set(const usb_dcd_ctx_t* dcd_ctx, uint8 ifc_num);
usb_dcd_dsc_endpoint_t* usb_dcd_find_ep(const usb_dcd_ctx_t* dcd_ctx, uint16 ep_address);
usb_desc_header_t* get_string_desc(const usb_dcd_ctx_t* dcd_ctx, uint16 lang_id, uint8 index);
void usb_dcd_fd_notify(usb_dcd_ctx_t* dcd_ctx, usb_notify_events_t event);
int usb_dcd_set_interface(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_interface_t* ifc, uint8 ifc_num, uint8 alt);
int usb_dcd_set_config(usb_dcd_ctx_t* dcd_ctx, uint8 new_config);
int usb_dcd_control_transfer(usb_dcd_ctx_t* dcd_ctx, int is_tx, void* buff, uint32 len);
int usb_dcd_control_reply(usb_dcd_ctx_t* dcd_ctx, uint32 len);
int handle_get_descriptor(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
int handle_setup_dev(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
int handle_setup_ifc(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
int handle_ep_halt(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_endpoint_t* ep, int halt);
int handle_setup_ep(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
int handle_setup_std(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);
void usb_dcd_handle_reset(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_handle_disconnect(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_handle_suspend(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_handle_setup(usb_dcd_ctx_t* dcd_ctx, void* buffer_ptr);
void usb_dcd_port_status_changed(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_notify(void* dev_ptr, usb_notify_events_t  event, void* buffer_ptr);
void usb_dcd_set_bos(usb_dcd_ctx_t* dcd_ctx, usb_bos_desc_t* bos_desc);
boolean usb_dcd_set_cfg_tree(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_configuration_t* cfg_tree);
void usb_dcd_create_desc(usb_dcd_ctx_t* dcd_ctx_ptr, uint16 vendor_id, uint16 product_id, uint8 n_cfg);
void usb_dcd_ctrl_start_xfer(usb_dcd_ctx_t *dcd_ctx);
boolean usb_dcd_init(usb_max_speed_required_t speed_required, usb_dcd_ctx_t** dcd_ctx_ptr, void* fd_ctx, usb_fd_callback_t fd_cb, uint16 lang_id, uint8* manuf_str, uint8* product_str);
boolean usb_dcd_free_desc(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_shutdown(usb_dcd_ctx_t** dcd_ptr);
int usb_dcd_submit_urb(usb_dcd_ctx_t* dcd_ctx, usb_urb_t* urb);
void usb_dcd_set_core(usb_dcd_ctx_t* dcd_ctx, usb_core_type core_id);
void* usb_dcd_get_dci_ctx(usb_dcd_ctx_t* dcd_ctx);
usb_device_connect_speed_t usb_dcd_get_speed(usb_dcd_ctx_t* dcd_ctx);
boolean usb_dcd_is_usb_configured(usb_dcd_ctx_t* dcd_ctx);
uint32 usb_dcd_get_ctrl_urb_tx_transfer_status(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_poll(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_reset(usb_dcd_ctx_t* dcd_ctx);
uint32 usb_dcd_cancel_transfer(usb_dcd_ctx_t* dcd_ctx, usb_urb_t* urb_ptr);
uint32 usb_dcd_get_max_packet_size(usb_dcd_ctx_t* dcd_ctx);
boolean usb_dcd_wakeup(usb_dcd_ctx_t* dcd_ctx);
void usb_dcd_handle_class_status3_req_ifc(struct usb_urb* urb_ptr);
void usb_dcd_handle_class_status3_req_ep(struct usb_urb* urb_ptr);
boolean usb_dcd_handle_setup_class_ifc(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
boolean usb_dcd_handle_setup_class_ep(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
boolean usb_dcd_handle_setup_class(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);
void usb_dcd_vendor_out_cb(struct usb_urb* urb_ptr);
int usb_dcd_handle_setup_vendor(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);

//------------------------------------------------------------------------------
// DCI Function Declarations
//------------------------------------------------------------------------------
void usb_dci_handle_u1_u2_enable(usb_dci_u1_u2_event_type event, boolean enable);
void usb_dci_update_packet_size(usb_dci_ctx_t* dci_ctx);
void usb_dci_test_mode_enable(usb_dci_ctx_t* dci_ctx, boolean enable, uint32 test_mode);
void usb_dci_handle_test_mode(usb_dci_ctx_t* dci_ctx);
void usb_dci_configure_device_mode(boolean is_l1_enable, usb_max_speed_required_t speed_required);
void usb_dci_hw_init(usb_dci_ctx_t* dci_ctx, usb_max_speed_required_t* max_speed);
uint32 usb_dci_init(usb_core_type core_id, void** dci_ctx_ptr, void* dcd_ctx, usb_dcd_callback_t* cb_table_ptr);
void usb_dci_core_init(usb_dci_ctx_t* dci_ctx);
uint32 usb_dci_write_ep_cmd(usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, usb_ep_cmd_t *ep_cmd);
uint32 usb_dci_write_dev_cmd(usb_dci_ctx_t* dci_ctx, usb_dev_cmd_t *dev_cmd);
void usb_dci_event_buffer_init(usb_dci_ctx_t* dci_ctx);
void usb_dci_set_run_stop(usb_dci_ctx_t* dci_ctx, boolean set);
void usb_dci_handle_ep_event(usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt);
void usb_dci_handle_dev_event(usb_dci_ctx_t* dci_ctx, usb_event_devt_t  *devevt);
void usb_dci_poll_events(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_ctrl_transfers(usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt);
void usb_dci_inc_trb_idx(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, uint8 *idx);
void usb_dci_handle_transfer_complete(usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt);
void usb_dci_handle_usb_reset(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_connect_done(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_usb_disconnect(usb_dci_ctx_t* dci_ctx);
usb_link_state_t usb_dci_get_link_state(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_link_status_change(usb_dci_ctx_t* dci_ctx, uint32 state);
void usb_dci_drive_remote_wakeup(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_suspend_entry(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_wakeup(usb_dci_ctx_t* dci_ctx);
uint8 usb_dci_get_address(void);
void usb_dci_set_address(uint8 address);
uint32 usb_dci_get_event_cnt(void);
uint32 usb_dci_stall_endpoint(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
uint32 usb_dci_unstall_endpoint(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
void usb_dci_config_endpoint(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, uint8 ep_type, uint8 ep_interval, uint16 max_packet_length, boolean zero_length_transfer);
uint32 usb_dci_unconfig_endpoint( uint8 ep, uint8 dir);
uint32 usb_dci_submit_trb_data(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
void usb_dci_init_trb_ring(usb_dci_ctx_t* dci_ctx);
uint32 usb_dci_prepare_trbs(usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, usb_urb_t* urb_ptr, uint8 trb_ctl);
uint32 usb_dci_transfer_data_request(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, usb_urb_t* urb_ptr, trb_ctl_type_t trb_ctrl);
void usb_dci_ctrl_error_recover(usb_dci_ctx_t* dci_ctx);
void usb_dci_ctrl_xfer_state_machine(usb_dci_ctx_t* dci_ctx, usb_urb_t *urb_ptr, trb_ctl_type_t *trb_ctl);
uint32 usb_dci_ctrl_submit_request(usb_dci_ctx_t* dci_ctx, uint8 dir);
uint32 usb_dci_transfer_request(usb_dci_ctx_t* dci_ctx, usb_urb_t* urb_ptr);
uint32 usb_dci_cancel_transfer(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
uint32 usb_dci_shutdown(usb_dci_ctx_t** dci_ptr);
uint32 usb_dci_get_speed(usb_dci_ctx_t* dci_ctx);
void usb_dci_set_max_packet_size(usb_dci_ctx_t* dci_ctx, uint32 max_packet_size);
uint32 usb_dci_get_max_packet_size(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_set_select(usb_dci_ctx_t* dci_ctx);
uint32 usb_dci_buffer_is_empty(usb_dci_ctx_t* dci_ctx);
void usb_dci_enter_lpm(usb_dci_ctx_t* dci_ctx, pwr_evnt_t event);
uint32 usb_dci_poll_pwr_event(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_event(usb_dci_ctx_t* dci_ctx, uint32 pwr_event);
uint32 usb_dci_remote_wakeup(usb_dci_ctx_t* dci_ctx);
void usb_dci_handle_remote_wakeup_enabled(usb_dci_ctx_t* dci_ctx, boolean enabled);
boolean usb_dci_is_remote_wakeup_enabled(usb_dci_ctx_t* dci_ctx);

//------------------------------------------------------------------------------
// DCI Target Layer Function Declarations
//------------------------------------------------------------------------------
void usb_dci_reset_hw(void);
void usb_dci_select_utmi_clk(void);
void usb_dci_enable_vbus_valid(usb_max_speed_required_t speed_required);
void usb_dci_select_phy_mode(usb_phy_mode phy_mode);
void usb_dci_update_override(void);
void usb_dci_hs_phy_init(void);
void usb_dci_deinit_hs_phy(void);

//------------------------------------------------------------------------------
// Utility Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Memory Utility Layer Function Declarations
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Log Function Declarations
//------------------------------------------------------------------------------

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

// NOTE: The unified function table usb_fn_tbl_g is not used in this architecture.
// Each layer (FD, DCD, DCI) maintains its own function table:
// - fn_tbl_fd in usb_fd.c
// - fn_tbl_dcd in usb_dcd.c  
// - fn_tbl_dci in usb_dci.c
// Access them via: usb_fn_fd(), usb_fn_dcd(), usb_fn_dci()

#if 0  // Disabled - use individual layer function tables instead
 usb_fn_tbl_t usb_fn_tbl_g = 
{

  //----------------------------------------------------------------------------
  // FD Layer Function Table
  //----------------------------------------------------------------------------
  {
    usb_fd_alloc_ep_comp_desc,
    usb_fd_alloc_ep_desc,
    usb_fd_alloc_ifc_desc,
    usb_fd_create_cfg_desc,
    usb_fd_set_cfg,
    NULL, // usb_fd_set_req_status_comp_cb - not implemented
    NULL, // usb_fd_handle_set_req - not implemented
    NULL, // usb_fd_handle_get_req - not implemented
    usb_fd_alloc_bos_desc,
    usb_fd_alloc_audio_cfg,
    usb_fd_set_transfer_status,
    usb_fd_init_urb,
    usb_fd_notify,
    usb_fd_init,
    usb_fd_shutdown,
    usb_fd_tx_pkt,
    usb_fd_hid_report,
    usb_fd_rx_pkt,
    usb_fd_cancel_transfer,
    usb_fd_cancel_transfer_dir,
    usb_fd_poll,
    usb_fd_reset,
    usb_fd_get_max_packet_size,
    usb_fd_get_speed,
    usb_fd_get_dci_ctx,
    usb_fd_set_core,
    usb_fd_is_usb_configured,
  },

  //----------------------------------------------------------------------------
  // DCD Layer Function Table
  //----------------------------------------------------------------------------
  {
    usb_dcd_desc_max_packet_size,
    usb_dcd_create_dev_desc,
    usb_dcd_create_dev_qual_desc,
    usb_dcd_allocate_dev_qual,
    usb_dcd_allocate_strings,
    usb_dcd_create_ep_comp_desc,
    usb_dcd_create_ep_desc,
    usb_dcd_create_ifc_desc,
    dcd_get_config_tree,
    dcd_get_config_value,
    find_config_by_value,
    get_curr_ifc_alt_set,
    usb_dcd_find_ep,
    get_string_desc,
    usb_dcd_fd_notify,
    usb_dcd_set_interface,
    usb_dcd_set_config,
    usb_dcd_control_transfer,
    usb_dcd_control_reply,
    handle_get_descriptor,
    handle_setup_dev,
    handle_setup_ifc,
    handle_ep_halt,
    handle_setup_ep,
    handle_setup_std,
    usb_dcd_handle_reset,
    usb_dcd_handle_disconnect,
    usb_dcd_handle_suspend,
    usb_dcd_handle_setup,
    usb_dcd_port_status_changed,
    usb_dcd_notify,
    usb_dcd_set_bos,
    usb_dcd_set_cfg_tree,
    usb_dcd_create_desc,
    usb_dcd_ctrl_start_xfer,
    usb_dcd_init,
    usb_dcd_free_desc,
    usb_dcd_shutdown,
    usb_dcd_submit_urb,
    usb_dcd_set_core,
    usb_dcd_get_dci_ctx,
    usb_dcd_get_speed,
    usb_dcd_is_usb_configured,
    usb_dcd_get_ctrl_urb_tx_transfer_status,
    usb_dcd_poll,
    usb_dcd_reset,
    usb_dcd_cancel_transfer,
    usb_dcd_get_max_packet_size,
    usb_dcd_wakeup,
    usb_dcd_handle_class_status3_req_ifc,
    usb_dcd_handle_class_status3_req_ep,
    usb_dcd_handle_setup_class_ifc,
    usb_dcd_handle_setup_class_ep,
    usb_dcd_handle_setup_class,
    usb_dcd_vendor_out_cb,
    usb_dcd_handle_setup_vendor,
  },

  //----------------------------------------------------------------------------
  // DCI Layer Function Table
  //----------------------------------------------------------------------------
  {
    usb_dci_handle_u1_u2_enable,
    usb_dci_update_packet_size,
    usb_dci_test_mode_enable,
    usb_dci_handle_test_mode,
    usb_dci_configure_device_mode,
    usb_dci_hw_init,
    usb_dci_init,
    usb_dci_core_init,
    usb_dci_write_ep_cmd,
    usb_dci_write_dev_cmd,
    usb_dci_event_buffer_init,
    usb_dci_set_run_stop,
    usb_dci_handle_ep_event,
    usb_dci_handle_dev_event,
    usb_dci_poll_events,
    usb_dci_handle_ctrl_transfers,
    usb_dci_inc_trb_idx,
    usb_dci_handle_transfer_complete,
    usb_dci_handle_usb_reset,
    usb_dci_handle_connect_done,
    usb_dci_handle_usb_disconnect,
    usb_dci_get_link_state,
    usb_dci_handle_link_status_change,
    usb_dci_drive_remote_wakeup,
    usb_dci_handle_suspend_entry,
    usb_dci_handle_wakeup,
    usb_dci_get_address,
    usb_dci_set_address,
    usb_dci_get_event_cnt,
    usb_dci_stall_endpoint,
    usb_dci_unstall_endpoint,
    usb_dci_config_endpoint,
    usb_dci_unconfig_endpoint,
    usb_dci_submit_trb_data,
    usb_dci_init_trb_ring,
    usb_dci_prepare_trbs,
    usb_dci_transfer_data_request,
    usb_dci_ctrl_error_recover,
    usb_dci_ctrl_xfer_state_machine,
    usb_dci_ctrl_submit_request,
    usb_dci_transfer_request,
    usb_dci_cancel_transfer,
    usb_dci_shutdown,
    usb_dci_get_speed,
    usb_dci_set_max_packet_size,
    usb_dci_get_max_packet_size,
    usb_dci_handle_set_select,
    usb_dci_buffer_is_empty,
    usb_dci_enter_lpm,
    usb_dci_poll_pwr_event,
    usb_dci_handle_event,
    usb_dci_remote_wakeup,
    usb_dci_handle_remote_wakeup_enabled,
    usb_dci_is_remote_wakeup_enabled, 
  },
  
//----------------------------------------------------------------------------
// Target specific DCI Layer Function Table
//----------------------------------------------------------------------------
  {
    usb_dci_reset_hw,
    usb_dci_select_utmi_clk,
    usb_dci_enable_vbus_valid,
    usb_dci_select_phy_mode,
    usb_dci_update_override,
    usb_dci_hs_phy_init,
    usb_dci_deinit_hs_phy,
  },
};
#endif // Disabled unified function table
