#ifndef USB_API_H
#define USB_API_H
/*=======================================================================*//**
 * @file        usb_al_bulk.c
 * @author:     dpatnaik
 * @date        12-Feb-2011
 *
 * @brief       USB (Qualcomm High-Speed USB) AL (Adaptation-Layer) implementation.
 *
 * @details     This file contains the implementation of the APIs to be used by
 *              the boot Sahara downloader.
 *
 * @note        
 *
 *              Copyright 2011 QUALCOMM Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*==================================================================================================================*/


// =====================================================================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/api/wiredconnectivity/usb_api.h#10 $ 
// $DateTime: 2018/02/12 17:09:34 $ $Author: pwbldsvc $
// 
// when       who     what, where, why
// --------   ---     ----------------------------------------------------------
// 02/12/11   dpatnaik  Initial revision
//
// =====================================================================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h"                 // common defines - basic types as uint32 etc
#include "usb_common.h"
#include "usb_audio.h"
#include "usb_dfu.h"
#include "usb_hid_api.h"


/*------------------------------------------------------------------------------------------     
* Type Declarations
* ----------------------------------------------------------------------------------------*/

typedef struct usb_fn_tbl_api
{
  boolean (*usb_set_params)(usb_dev_params_t* svc_params, usb_ifc_id** usb_comp, uint8* usb_comp_num_ifc);
  uint32 (*usb_write)(client_ctx_t* client_ctx, uint8* buf_ptr, uint32 xfer_size, void* cb_data);
  uint32 (*usb_read)(client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buf_size, void* cb_data);
  uint32 (*usb_isoc_in)(client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buf_size, void* cb_data);
  uint32 (*usb_isoc_out) (client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buf_size, void* cb_data);
  uint32 (*usb_open_ctrl) (ctrl_client_ctx_t** client_ctx, usb_ifc_id ifc_id, boolean (*ctrl_out_cb)(usb_setup_t* cmd_ptr, uint8* payload, uint32 payload_size), boolean (*ctrl_in_cb)(usb_setup_t* cmd_ptr, uint8* payload, uint32* payload_size));
//  uint32 (*usb_open_audio_stream)(client_ctx_t** client_ctx, usb_ifc_id ifc_id, usb_audio_stream_open_cfg_t* cfg, usb_event_func_t event_cb, usb_func_cb_t data_cb);
//  uint32 (*usb_open_audio_ctrl)(client_ctx_t** client_ctx, usb_ifc_id ifc_id, usb_audio_ctrl_open_cfg_t* cfg,  usb_event_func_t event_cb);
  uint32 (*usb_open_dfu)(client_ctx_t** client_ctx, usb_ifc_id ifc_id, usb_dfu_open_cfg_t* cfg, usb_event_func_t event_cb);
  uint32 (*usb_hid_open)(client_ctx_t** client_ctx, usb_ifc_id ifc_id);
  uint32 (*usb_hid_report)(client_ctx_t* client_ctx, usb_hid_bitmask_cmd_t report);
  uint32 (*usb_open)(client_ctx_t** client_ctx, usb_ifc_id ifc_id, void* data, usb_event_func_t event_cb, usb_func_cb_t rx_cb, usb_func_cb_t tx_cb, uint32 rx_buf_num, uint32 tx_buf_num);
  uint32 (*usb_close)(client_ctx_t* client_ctx);
  void (*usb_handle_signal)(uint32 client_sig);
  void (*usb_thread_init)(void* sig_ptr);
  void (*usb_log_open)(void); 
  void (*usb_log_close)(void);
} usb_fn_tbl_api_t;

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/
extern usb_fn_tbl_api_t fn_tbl_api;
#define usb_api()  (&fn_tbl_api)

// ==========================================================================================================
/**
 * @function  usb_set_params
 * 
 * @brief   Application or service layer can call this API to pass important ACDB information.
 *
 * @details Application or service layer can call this API to pass important ACDB information like qc_pid, 
 *              vid_override, pid_override. A unique composition will be returned corresponding to qc_pid
 * 
 * @param   usb_dev_params_t - [IN] - Pointer to ACDB info like qc_pid, vid_override, pid_override etc. 
 *          usb_comp - [OUT] - Pointer to usb_composition is returned.
 *          usb_comp_num_ifc  - [OUT]  - number of interfaces in USB composition.
 * 
 * @return  none.
 */
// ==========================================================================================================
boolean usb_set_params(usb_dev_params_t* params, usb_ifc_id** usb_comp, uint8* usb_comp_num_ifc);

// ==========================================================================================================
/**
 * @function  usb_open
 * 
 * @brief   Client call this function to register usb.
 *
 * @details All client need to call this function to recieve callback from USB
 * 
 * @param   usb_ctx     - [OUT] client will keep the usb_ctx
 *          iface_id    - [IN]  client interface ID, ALL ID is fix value
 *          iface_type  - [IN]  client interface type
 *          event_cb    - [IN]  pointer to client event cb function 
 *                              (eg enum, disconncet, close)
 *          rx_cb       - [IN]  pointer to client rx cb function
 *          tx_cb       - [IN]  pointer to client tx cb function
 *          rx_buf_num - [IN]  max size of rx buffer queue a the same time
 *          tx_buf_num - [IN]  max size of tx buffer queue a the same time
 * 
 * @return  boolean if client success register
 */
// ==========================================================================================================
uint32 usb_open(client_ctx_t** usb_ctx, usb_ifc_id ifc_id, void* data,
  usb_event_func_t event_cb, usb_func_cb_t rx_cb, usb_func_cb_t tx_cb, uint32 rx_buf_num, 
  uint32 tx_buf_num);

// ==========================================================================================================
/**
 * @function  usb_isoc_out / usb_read
 * 
 * @brief   Client call this function to submit buffer to receive data from USB host
 *
 * @details Client call this function to submit read buffer. This function only,
 *          submit the buffer into queue, client still need call usb_signal.
 *          So USB thtead can submit to hardware.
 * 
 * @param   client_ctx  - [IN]  usb_ctx relate to the client
 *          req           - [IN]  pointer to the buffer
 *          buffer_size   - [IN]  max size of the buffer to recieve. 
 *                        -       need be at least max buffer size of speed.
 * 
 * @return  err_msg,  0,        queue successful
 *                    non-zero, queue fail

 */
// ==========================================================================================================
uint32 usb_read (client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buffer_size, void* cb_data);

// ==========================================================================================================
/**
 * @function  usb_isoc_in / usb_write
 * 
 * @brief   Client call this function to submit buffer to send data to USB host.
 *
 * @details Client call this function to submit write buffer. This function only,
 *          submit the buffer into queue, client still need call usb_signal.
 *          So USB thtead can submit to hardware.
 * 
 * @param   client_ctx    - [IN]  usb_ctx relate to the client
 *          req           - [IN]  pointer to the buffer
 *          transfer_size - [IN]  number byte to transfer in the buffer.
 * 
 * @return  err_msg,  0 queue successful
 *                    non-zero queue fail
 */
// ===========================================================================
uint32 usb_write (client_ctx_t* client_ctx, uint8* buf_ptr, uint32 transfer_size, void* cb_data);

// ==========================================================================================================
/**
 * @function    usb_close
 * 
 * @brief   close usb with that client
 *
 *
 * @details close usb with that client, when all client is close, usb will shutdown
 *          
 * 
 * @param   client_ctx_t   -  [IN] Client_ctx
 * 
 *
 * @return  err_msg,  0 close successful
 *                    non-zero close fail
 */
// ==========================================================================================================
uint32 usb_close(client_ctx_t* client_ctx);

// ==========================================================================================================
/**
 * @function    usb_create_thread
 * 
 * @brief   This function will create USB driver thread.
 *
 * @details This function will create and register USB driver thread and signals
 *          with OS. Essential when using independent USB thread.
 * 
 * @param   None.
 * 
 * @return  TRUE: when thread create successful.
 *          FALSE: when thread create fail.
 * 
 */
// ==========================================================================================================
boolean usb_create_thread(void);

// ==========================================================================================================
/**
 * @function    usb_thread_init
 * 
 * @brief   enable usb memory and global variable + enable usb hardware
 *
 *
 * @details call to allocate all the usb stack before calling usb_open
 *          
 * 
 * @param   client_sig   -  [IN] thread signal pointer for usb. 
                          USB usb signal bit 0x000F0000
 * 
 *
 * @return  None.
 * 
 */
// ==========================================================================================================
void usb_thread_init(void* client_sig);

// ==========================================================================================================
/**
 * @function  usb_handle_signal
 * 
 * @brief   Handles various events signaled to USB thread.
 *
 * @details Handles various events signaled to USB thread from other threads 
 *          and interrupt contexts. List of signals handled is below -
 *          1) USB0_TASK_EVENT_QUEUE_SIG - events generated from USB controller
 *          2) USB0_TASK_PWR_EVENT_QUEUE_SIG - events generated by power event interrupt
 *          3) USB0_TASK_VBUS_EVENT_SIG - event generated by Vbus interrupt.
 * 
 * @param   client_sig - [IN] - Current state of USB thread signals.
 *
 * @return  None
 *
 */
// ==========================================================================================================
void usb_handle_signal(uint32 client_sig);

// ==========================================================================================================
/**
 * @function  usb_open_ctrl
 * 
 * @brief   API for USB bus control channel clients to register in/out data callbacks.
 *
 * @details This API provide means to register callbacks for clients communicating over control 
 *          channel of USB bus. Potential clients may include vendor specific requests that needs 
 *          to be serviced outside USB driver. e.g. audio tune service. 
 * 
 * @param   client_ctx - [IN] - context of the audio ctrl client
 *          ifc_id - [IN] - identifier for interface type.
 *          ctrl_out_cb - [IN] - callback to receive data from host.
 *          ctrl_in_cb - [IN] - callback to send host data to host.
 *          cmd_ptr - [IN] - callbacks provides USB setup packet to client via cmd_ptr.
 *          payload -[IN / OUT] - data to be sent to or received from USB host.
 *          payload_size - [IN / OUT] - size of data to be sent to or received from USB host.
 *          ctrl_out_cb and  ctrl_in_cb returns success / failure for command execution and parsing. 
 *
 * @return  TRUE,  if buffer was queued to hardware successfully
 *          FALSE, if buffer failed to be queued to hardware
 */
// ==========================================================================================================
uint32 usb_open_ctrl (ctrl_client_ctx_t** client_ctx, usb_ifc_id ifc_id,
  ctrl_out_cb_t ctrl_out_cb, ctrl_in_cb_t ctrl_in_cb);

// ==========================================================================================================
/**
 * @function    usb_lb_task_init
 * 
 * @brief   USB dummy loopback client initialization API.
 *
 *
 * @details Can only be used for verifying USB layer functionality through a 
 *          simple loopback application that exercises Audio and HID functionality.
 *          
 * 
 * @param   None.
 * 
 *
 * @return  Success or Failure.
 * 
 */
// ==========================================================================================================
boolean usb_lb_task_init(void);

#endif /* USB_API_H */
