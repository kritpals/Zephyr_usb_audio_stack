/*=======================================================================*//**
 * @file        usb_api_fn_tbl.c
 * @author:     USB Team
 * @date        20-Nov-2025
 *
 * @brief       USB API function table implementation.
 *
 * @details     This file contains the API function table definition that
 *              provides the main USB API functions to clients.
 * 
*//*========================================================================*/

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "usb_api.h"
#include "usb_common.h"

//----------------------------------------------------------------------------
// Forward Declarations - API Functions
//----------------------------------------------------------------------------
boolean usb_set_params(usb_dev_params_t* params, usb_ifc_id** usb_comp, uint8* usb_comp_num_ifc);
uint32 usb_write(client_ctx_t* client_ctx, uint8* buf_ptr, uint32 xfer_size, void* cb_data);
uint32 usb_read(client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buf_size, void* cb_data);
uint32 usb_open_ctrl(ctrl_client_ctx_t** client_ctx, usb_ifc_id ifc_id, boolean (*ctrl_out_cb)(usb_setup_t* cmd_ptr, uint8* payload, uint32 payload_size), boolean (*ctrl_in_cb)(usb_setup_t* cmd_ptr, uint8* payload, uint32* payload_size));
uint32 usb_open_dfu(client_ctx_t** client_ctx, usb_ifc_id ifc_id, usb_dfu_open_cfg_t* cfg, usb_event_func_t event_cb);
uint32 usb_hid_open(client_ctx_t** client_ctx, usb_ifc_id ifc_id);
uint32 usb_hid_report(client_ctx_t* client_ctx, usb_hid_bitmask_cmd_t report);
uint32 usb_open(client_ctx_t** client_ctx, usb_ifc_id ifc_id, void* data, usb_event_func_t event_cb, usb_func_cb_t rx_cb, usb_func_cb_t tx_cb, uint32 rx_buf_num, uint32 tx_buf_num);
uint32 usb_close(client_ctx_t* client_ctx);
void usb_handle_signal(uint32 client_sig);
void usb_thread_init(void* sig_ptr);
void usb_log_open(void);
void usb_log_close(void);

//----------------------------------------------------------------------------
// API Function Table Definition
//----------------------------------------------------------------------------
usb_fn_tbl_api_t fn_tbl_api = 
{
  NULL, // usb_set_params,
  NULL, // usb_write,
  NULL, // usb_read,
  NULL, // usb_isoc_in - not implemented yet
  NULL, // usb_isoc_out - not implemented yet
  NULL, // usb_open_ctrl,
  NULL, // usb_open_dfu,
  NULL, // usb_hid_open,
  NULL, // usb_hid_report,
  NULL, // usb_open,
  NULL, //usb_close,
  usb_handle_signal,
  usb_thread_init,
  NULL, //usb_log_open,
  NULL, //usb_log_close,
};
