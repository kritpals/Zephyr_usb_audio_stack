#ifndef USB_COMMON_H
#define USB_COMMON_H
//============================================================================
/**
 * @file        usb_common.h
 * @author      shreyasr
 * @date        23-April-2014
 *
 * @brief       Common USB defines.
 *
 *
 *              Copyright (c) 2014 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
 */
//============================================================================

// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: 
// 
// when          who        what, where, why
// ----------   --------    --------------------------------------------------
// 2012-04-23   shreyasr    First Draft
// 
// ===========================================================================
#include "comdef.h"

#ifdef DDR_DEBUG_MODE_ENABLED
#define __USB_DMA_ZI__  // Allow USB ZI to be placed differently or DDR debug tool
#else
#define __USB_DMA_ZI__ __attribute__((section("BOOT_UNCACHED_DDR_ZI_ZONE"), zero_init))
//#define __USB_DMA_ZI__ __attribute__((section("RAM_FOM_BSP_ZI_SECTION"), zero_init))
#endif

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------

typedef PACKED struct usb_setup 
{
   uint8  requestType;
   uint8  request;
   uint16 value;
   uint16 index;
   uint16 length;
} PACKED_POST usb_setup_t;


#define USB_MAX_CTRL_PKT_SIZE (64)
#define USB_CTRL_SETUP_PKT_SIZE (8)

#define USB_HLOS_HANDLE_SIG       (0x00FF0000)
#define USB_CLI_HANDLE_SIG        (0x00F00000)


// Endpoint Direction
#define USB_EP_DIR_RX            (0)  // OUT Token
#define USB_EP_DIR_TX            (1)  // IN Token

typedef enum
{  
  USB_CORE_SNPS = 0,
  USB_CORE_MAXX
} usb_core_type;

//SBL driver needs to make a cognitive decision about the maximum speed for USB
//SBL can operate a maximum in High Speed Mode or in Super Speed. 
//If they need to operate in HS, they need to pass this in usb_al_bulk_init()
typedef enum
{
  USB_MAX_SPEED_HIGH = 0x0, 
  USB_MAX_SPEED_SUPER
} usb_max_speed_required_t;

typedef enum usb_device_connect_speed
{
  USB_HIGH_SPEED    = 0,
  USB_FULL_SPEED    = 1,
  USB_LOW_SPEED     = 2,
  USB_FULL_SPEED_48 = 3,
  USB_SUPER_SPEED   = 4,
  USB_UNKNOWN_SPEED = 0xF
} usb_device_connect_speed_t;

typedef enum usb_err
{
  USB_SUCCESS                = 0,       // success
  USB_ERR_DEFAULT            = 1,       // generic error
  USB_ERR_PERM               = 2,       // operation not permitted
  USB_ERR_NO_MEM             = 3,       // out of heap memory
  USB_ERR_CANCEL             = 4,       // transfer cancelled
  USB_ERR_SUSPENDED          = 5,       // device is suspended
  USB_ERR_ENUMERATION        = 6,       // enumeration failed
  USB_ERR_TIMEOUT            = 7,       // operation timed out
  USB_ERR_BAD_PARAM          = 8,       // bad parameter
  USB_ERR_UNKNOWN            = 9,       // general error
  USB_ERR_READ               = 10,      // read error
  USB_ERR_WRITE              = 11,      // write error
  USB_ERR_CABLE_DISCONNECT   = 12,      // usb cable disconnect error
  USB_ERR_OVERFLOW           = 13,      // insufficient resources
  USB_ERR_MEM_OVERFLOW       = 14,      // not allocate enough memory
  USB_ERR_BUF_OVERFLOW       = 15,      // queue more requestion then init
  USB_ERR_CLIENT_NOT_OPEN    = 16,      // client calling api before calling open
  USB_ERR_NULL_PTR           = 17,      // unexpected null pointer error
  USB_ERR_MAX                = 0xFFFF   // max range of error code
} usb_err_t;

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------
typedef enum 
{
  USB_READ_REQ,
  USB_WRITE_REQ,
  USB_CLOSE_REQ,
  USB_REQ_TYPE_MAX,
} usb_request_type;

typedef enum
{
  USB_REQ_QUEUED =1,           /**< Request queued */
  USB_REQ_ACTIVE,           /**< Transfer in progress */
  USB_REQ_COMPLETE_OK,      /**< Completed, success */
  USB_REQ_COMPLETE_ERROR,   /**< completed, error */
  USB_REQ_CANCEL,
  USB_REQ_MAX_STATUS
} usb_req_status;

typedef struct 
{
  uint32 req_id;  //debug only, msg_id, can be 0 all the time
  uint32 type;    //usb_request_type, read, write, closed. this will be fill by usb_api
  void* buf_ptr;  //pointer to the buffer
  uint32 size;    //when submit request(usb_read: size of buffer, usb_write: number of byte to send)
                  //when callback (rx_cb: number of byte is read, tx_cb: random)
  uint32 status;  //usb request status
  void* cb_data;
} client_request_t;

typedef enum
{
  USB_EVENT_ENABLED, //ENUM_DONE_EVENT,
  USB_EVENT_DISCONNECT,
  USB_EVENT_CLOSE_COMPLETE,
  USB_EVENT_AUDIO_CTRL_CFG,
  USB_EVENT_STREAM_ENABLE,
  USB_EVENT_STREAM_DISABLE,
  USB_EVENT_DFU_ENTRY,
  USB_EVENT_DFU_EXIT,
  USB_EVENT_TYPE_MAX
} usb_event_type;

typedef enum
{
  USB_IFC_ID_BULK,
  USB_IFC_ID_AUDIO_TUNING,
  USB_IFC_ID_AUDIO_CONTROL,
  USB_IFC_ID_AUDIO_STREAMING_MIC,
  USB_IFC_ID_AUDIO_STREAMING_SPEAKER,
  USB_IFC_ID_HID,
  USB_IFC_ID_DFU,
  USB_IFC_ID_CDC_CONTROL, //Serial control
  USB_IFC_ID_CDC_DATA, //Serial data
  // Add new interface IDs here
  USB_IFC_ID_MAX
} usb_ifc_id;

typedef enum
{
  USB_GENE_LOG_TYPE,
  USB_BUS_LOG_TYPE,
  USB_ERROR_LOG_TYPE,
  USB_MAX_LOG_TYPE
} usb_enum_log_type;

typedef enum
{
  CLIENT_EVENT_CB_CLOG = 1,
  CLIENT_CLOSE_EVENT_CB_CLOG,
  CLIENT_TX_CB_CLOG,
  CLIENT_RX_CB_CLOG,
  CLIENT_ALLOC_BUFF_CLOG,
  CLIENT_THREAD_ENTER_WHILE_CLOG,
  CLIENT_GET_SIG_CLOG,
  CLIENT_GET_CMD_CLOG,
  CLIENT_READ_CLOG,
  CLIENT_READ_BUF_TOO_SMALL_CLOG,
  CLIENT_WRITE_CLOG,
  CLIENT_REQ_QUEUE_INIT_FAIL_CLOG,
  CLIENT_REQ_QUEUE_ENQ_FAIL_CLOG,
  CLIENT_REQ_QUEUE_DEQ_FAIL_CLOG,
  CLIENT_RX_COMPLETE_HANDLE_CLOG,
  CLIENT_FREE_TX_ENQ_CLOG,
  CLIENT_FREE_RX_ENQ_CLOG,
  CLIENT_UNKNOWN_CMD_CLOG,
  CLIENT_MAX_CLOG
}usb_client_log_enum;

typedef void (*usb_event_func_t)(uint32 event, void* data);
typedef void (*usb_func_cb_t)(uint8* buf_ptr, uint32 size, uint32 status, void* cb_data);
typedef boolean (*ctrl_out_cb_t)(usb_setup_t* cmd_ptr, uint8* payload, uint32 payload_size);
typedef boolean (*ctrl_in_cb_t)(usb_setup_t* cmd_ptr, uint8* payload, uint32* payload_size);

typedef struct
{
  usb_ifc_id ifc_id;
  uint8 client_id; // populated as index in USB composition, unique per client
  void* data;       // configuration of the iterface type
  uint32 data_size; // size of interface configuration
  usb_func_cb_t app_rx_cb_func; // RX completion callback of the interface
  usb_func_cb_t app_tx_cb_func; // TX completion callback of the interface
  usb_event_func_t app_event_cb_func; // Event indication callback
} client_ctx_t;

typedef struct
{
  usb_ifc_id ifc_id;
  ctrl_out_cb_t ctrl_out_cb;
  ctrl_in_cb_t ctrl_in_cb;
} ctrl_client_ctx_t;

typedef enum
{
  USB_OP_MODE_MISSION = 0,
  USB_OP_MODE_DFU,
} usb_op_mode_t;

typedef enum
{
  USB_PID_UAC1_HEADSET                = 0x9604,
  USB_PID_UAC2_HEADSET                = 0x9605,
  USB_PID_UAC1_BADD3_HEADSET          = 0x9606,
  USB_PID_UAC2_BADD3_HEADSET          = 0x9607,
  USB_PID_UAC1_BADD3_UAC3_HEADSET     = 0x9608,
  USB_PID_UAC2_BADD3_UAC3_HEADSET     = 0x9609,
  USB_PID_UAC1_HEADPHONE              = 0x960A,
  USB_PID_UAC2_HEADPHONE              = 0x960B,
  USB_PID_UAC1_BADD3_HEADPHONE        = 0x960C,
  USB_PID_UAC2_BADD3_HEADPHONE        = 0x960D,
  USB_PID_UAC1_BADD3_UAC3_HEADPHONE   = 0x960E,
  USB_PID_UAC2_BADD3_UAC3_HEADPHONE   = 0x960F,
  USB_PID_UAC1_MICROPHONE             = 0x9610,
  USB_PID_UAC2_MICROPHONE             = 0x9611,
  USB_PID_UAC1_BADD3_MICROPHONE       = 0x9612,
  USB_PID_UAC2_BADD3_MICROPHONE       = 0x9613,
  USB_PID_UAC1_BADD3_UAC3_MICROPHONE  = 0x9614,
  USB_PID_UAC2_BADD3_UAC3_MICROPHONE  = 0x9615,
} usb_pid_t;

typedef struct usb_dev_params
{
  uint16 qc_pid;
  uint16 vid_override;
  uint16 pid_override;
  uint8  audio_profile;
  uint8  op_mode;
  uint16 top_aud_rev; 
  uint8  disable_flags;
  uint8  mic_type;
} usb_dev_params_t;

#endif /*USB_COMMON_H*/
