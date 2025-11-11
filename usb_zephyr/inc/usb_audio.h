#ifndef USB__AUDIO_H
#define USB__AUDIO_H
/*=======================================================================*//**
 * @file        usb_audio.h
 * @author:  kameya
 * @date      04/06/2017
 *
 * @brief      USB Audio Class Specific header
 *
 * @details   This file contains the implementation of the APIs to be used by
 *                Audio Service Layer.
 *
 * @note        
 *
 *              Copyright 2017 Qualcomm Technologies Inc.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h" // common defines - basic types as uint32 etc
#include "usb_common.h"

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/
#define AS_BUS_CFG_SIZE     (8)

/*------------------------------------------------------------------------------------------     
* Type Declarations
* ----------------------------------------------------------------------------------------*/

// USB topology IDs
typedef enum
{
  USB_TOP_ID_MAIN_RX_IT         = 1,
  USB_TOP_ID_ST_RX_FU           = 2,
  USB_TOP_ID_HPH_OT             = 3,
  USB_TOP_ID_VOICE_MIC_IT       = 4,
  USB_TOP_ID_VOICE_MIC_FU       = 5,
  USB_TOP_ID_VOICE_TX_OT        = 6,
  USB_TOP_ID_ST_FU              = 7,
  USB_TOP_ID_ST_MIXER           = 8,
  USB_TOP_ID_MAIN_RX_CLOCK      = 9,
  USB_TOP_ID_POWER_DOMAIN_A     = 10,
  USB_TOP_ID_POWER_DOMAIN_B     = 11,
  USB_TOP_ID_MAIN_RX_FU         = 12,
  USB_TOP_ID_MIX_RX_IT          = 13,
  USB_TOP_ID_MIX_RX_FU          = 14,
  USB_TOP_ID_RX_MIXER           = 15,
  USB_TOP_ID_DSD_MIXER          = 16,
  USB_TOP_ID_ANC_SELECTOR       = 17,
  USB_TOP_ID_ANC_PROCESSING     = 18,
  USB_TOP_ID_EC_REF_OT          = 19,
  USB_TOP_ID_STEREO_MIC_IT      = 20,
  USB_TOP_ID_STEREO_MIC_FU      = 21,
  USB_TOP_ID_STEREO_MIC_OT      = 22,
  USB_TOP_ID_VOICE_MIC_CLOCK    = 23,
  USB_TOP_ID_STEREO_MIC_CLOCK   = 24,
  USB_TOP_ID_MIX_RX_CLOCK       = 25,
  USB_TOP_ID_EC_REF_CLOCK       = 26,
} usb_audio_unit_id_t;

typedef enum usb_audio_clock_mode
{
  USB_AUDIO_CLOCK_MODE_MULTI  = 0,
  USB_AUDIO_CLOCK_MODE_SINGLE = 1,
} usb_audio_clock_mode_t;

typedef enum usb_audio_profile
{
  USB_AUDIO_HEADSET   = 0,
  USB_AUDIO_HEADSET_ADAPTOR = 1,
  USB_AUDIO_SPEAKERPHONE    = 2,
  USB_AUDIO_HEADPHONE       = 3,
  USB_AUDIO_SPEAKER         = 4,
  USB_AUDIO_MICROPHONE      = 5,
} usb_audio_profile_t;

typedef enum usb_audio_mic
{
  USB_MIC_MONO    = 0,
  USB_MIC_STEREO  = 1,
  USB_MIC_QUAD    = 2,
} usb_audio_mic_t;

typedef enum usb_audio_class_rev
{
  USB_AUDIO_CLASS_REV_NONE = 0x0000,
  USB_AUDIO_CLASS_REV_1    = 0x0100,
  USB_AUDIO_CLASS_REV_2    = 0x0200,
  USB_AUDIO_CLASS_BADD3    = 0x02FF,
  USB_AUDIO_CLASS_REV_3    = 0x0300,
  USB_AUDIO_CLASS_REV_MAX  = 0xFFFF,
} usb_audio_class_rev_t;

typedef enum audio_ctrl
{
  AUDIO_CTRL_CS_FREQ   = 0x1,
  AUDIO_CTRL_CS_VALID  = 0x2,
  AUDIO_CTRL_FU_MUTE   = 0x4,
  AUDIO_CTRL_FU_VOLUME = 0x8,
} audio_ctrl_t;

typedef enum audio_req
{
  AUDIO_REQ_CURR,
  AUDIO_REQ_MIN,
  AUDIO_REQ_MAX,
  AUDIO_REQ_RES,
  AUDIO_REQ_RANGE,
} audio_req_t;

typedef enum audio_ch
{
  AUDIO_CH_MASTER = 0,
  AUDIO_CH_1      = 1,
  AUDIO_CH_2      = 2,
} audio_ch_t;

typedef struct audio_controls_cs
{
  uint8 valid;
  uint32 freq;
  uint8* range;
  uint16 range_size;
} audio_controls_cs_t;

typedef enum audio_unit
{
  AUDIO_CLOCK_SOURCE,
  AUDIO_CLOCK_SELECTOR,
  AUDIO_INPUT_TERMINAL,
  AUDIO_FEATURE_UNIT,
  AUDIO_MIXER_UNIT,
  AUDIO_OUTPUT_TERMINAL,
  AUDIO_CONNECTOR,
  AUDIO_POWER_DOMAIN,
} audio_unit_t;

typedef enum audio_terminal
{
  AUDIO_TERMINAL_MIC,
  AUDIO_TERMINAL_SPEAKER,
  AUDIO_TERMINAL_ENDPOINT,
} audio_terminal_t;

typedef struct audio_cs
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  uint8 controls;
  audio_controls_cs_t* controls_ptr;
} audio_cs_t;

typedef struct audio_it
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  usb_audio_unit_id_t clock_id;
  uint8 n_ch;
  uint8 term_type;
} audio_it_t;

typedef struct audio_fu
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  usb_audio_unit_id_t source_id;
  uint8 controls;
  uint8 n_ch;
} audio_fu_t;

typedef struct audio_mu
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  uint8 n_sources;
  usb_audio_unit_id_t source_id[2];
  uint8 n_op_ch;
} audio_mu_t;

typedef struct audio_ot
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  usb_audio_unit_id_t clock_id;
  usb_audio_unit_id_t source_id;
  uint8 term_type;
} audio_ot_t;

typedef struct audio_conn
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  usb_audio_unit_id_t conn_id;
  uint8 n_ch;
} audio_conn_t;

typedef struct audio_pd
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
  uint8 n_entity;
  usb_audio_unit_id_t entity_id[2];
} audio_pd_t;

typedef struct audio_node_val
{
  audio_unit_t type;
  usb_audio_unit_id_t id;
} audio_node_val_t;

typedef union audio_node
{
  audio_node_val_t val;
  audio_cs_t cs;
  audio_it_t it;
  audio_fu_t fu;
  audio_mu_t mu;
  audio_ot_t ot;
  audio_conn_t conn;
  audio_pd_t pd;
} audio_node_t;

typedef struct audio_slot_size
{
  uint8 bit_res;
  uint8 slot_size;
  uint16 bint_us; // service interval in micro-seconds
} audio_slot_size_t;

typedef struct 
{
  uint32 client_id;
  usb_ifc_id ifc_id;
  uint8 n_ch;
  uint32 freq;
  uint8  bytes_per_sample;
  uint16 interval; // service interval in terms of USB micro-frames (125us). e.g. @ 500us, interval = 4. 
  uint16 max_buff_size;
} usb_audio_stream_cfg;

typedef struct 
{
  uint32 client_id;
  uint8 n_nodes;
  audio_node_t* topology;
} usb_audio_ctrl_cfg;

typedef struct usb_audio_stream_open_cfg
{
  uint16 as_freq;
  uint8  as_bus_cfg[AS_BUS_CFG_SIZE];
  uint32 (*get_expl_fb_freq) (uint32 client_id);
} usb_audio_stream_open_cfg_t;

typedef boolean (*usb_audio_ctrl_set_req_t) (uint32 client_id, audio_node_t* node, 
  audio_ctrl_t ctrl, audio_req_t req, audio_ch_t ch, uint32* buff, uint32 len);

typedef boolean (*usb_audio_ctrl_get_req_t) (uint32 client_id, audio_node_t* node, 
  audio_ctrl_t ctrl, audio_req_t req, audio_ch_t ch, uint32* buff, uint32* len);

typedef struct usb_audio_ctrl_open_cfg
{
  usb_audio_clock_mode_t clock_mode;
  usb_audio_ctrl_get_req_t get_req;
  usb_audio_ctrl_set_req_t set_req;
} usb_audio_ctrl_open_cfg_t;

typedef enum
{
  AS_FREQ_NONE    = 0x0000,
  AS_FREQ_8_k     = 0x0001,
  AS_FREQ_16_k    = 0x0002,
  AS_FREQ_32_k    = 0x0004,
  AS_FREQ_44p1_k  = 0x0008,
  AS_FREQ_48_k    = 0x0010,
  AS_FREQ_88p2_k  = 0x0020,
  AS_FREQ_96_k    = 0x0040,
  AS_FREQ_176p4_k = 0x0080,
  AS_FREQ_192_k   = 0x0100,
  AS_FREQ_352p8_k = 0x0200,
  AS_FREQ_384_k   = 0x0400,
  AS_FREQ_MAX     = 0xFFFF,
} usb_as_freq_bmsk;

typedef enum
{
  AS_BW_SLOT_CFG_NONE = 0,
  AS_BW_SLOT_CFG_16_2 = 1,
  AS_BW_SLOT_CFG_24_3 = 2,
  AS_BW_SLOT_CFG_24_4 = 3,
  AS_BW_SLOT_CFG_32_4 = 4,
  AS_BW_SLOT_CFG_MAX  = 5,
} usb_as_bw_slot_cfg;

typedef enum
{
  AS_SVC_INT_US_NONE = 0,
  AS_SVC_INT_US_125  = 1,
  AS_SVC_INT_US_250  = 2,
  AS_SVC_INT_US_500  = 3,
  AS_SVC_INT_US_1000 = 4,
  AS_SVC_INT_US_2000 = 5,
  AS_SVC_INT_US_4000 = 6,
  AS_SVC_INT_US_MAX  = 7,
} usb_as_svc_int_us;

// ===================================================================
/**
 * @function  usb_open_audio_ctrl
 * 
 * @brief   API to register audio control clients.
 *
 * @details Allocates context for audio control clients, and registers set_req and get_req APIs with USB driver.
 * 
 * @param   client_ctx - [IN]  usb_ctx of the audio control client
 *                cfg - [IN]  pointer to usb_open_audio_ctrl
 *                event_cb - [IN] callback to listen to Audio Control interface events. 
 * 
 * @return  0,  Success
 *              Non-zero, error code for failure.
 */
// ===================================================================
uint32 usb_open_audio_ctrl(client_ctx_t** client_ctx, usb_ifc_id ifc_id, 
usb_audio_ctrl_open_cfg_t* cfg,  usb_event_func_t event_cb);

// ===================================================================
/**
 * @function  usb_open_audio_stream
 * 
 * @brief   API to register audio streaming clients.
 *
 * @details Registers audio streaming clients, optionally a API callback to request explicit feedback frequency.
 * 
 * @param   client_ctx - [IN]  usb_ctx of the audio streaming client
 *                ifc_id - [IN]  interface id for audio streaming interface. (MIC_MONO, MIC_STEREO, SPEAKER, etc.)
 *                cfg - [IN] pointer to usb_audio_stream_open_cfg
 *                event_cb - [IN] callback to listen to audio streaming interface events. (STREAM_ENABLE/DISABLE)
 *                data_cb - [IN] data buffer completion callback.
 * 
 * @return  TRUE,  if buffer was queued to hardware successfully
 *              FALSE, if buffer failed to be queued to hardware
 */
// ===================================================================
uint32 usb_open_audio_stream(client_ctx_t** client_ctx, usb_ifc_id ifc_id, 
  usb_audio_stream_open_cfg_t* cfg, usb_event_func_t event_cb, usb_func_cb_t data_cb);

// ===================================================================
/**
 * @function  usb_isoc_out
 * 
 * @brief   API for audio streaming clients to receive data from USB host.
 *
 * @details API for audio streaming clients to receive data from USB host.
 * 
 * @param   client_ctx - [IN]  usb_ctx of the audio streaming client
 *                buf_ptr - [IN]  pointer to the buffer to which data needs to be received
 *                transfer_size - [IN] size of the buffer to be sent
 *                cb_data - [IN] pointer to client data structure needed on callback completion.
 * 
 * @return  TRUE,  if buffer was queued to hardware successfully
 *              FALSE, if buffer failed to be queued to hardware
 */
// ===================================================================
uint32 usb_isoc_out (client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buf_size, void* cb_data);

// ===================================================================
/**
 * @function  usb_isoc_in
 * 
 * @brief   API for audio streaming clients to submit buffer to send to USB host.
 *
 * @details API for audio streaming clients to submit buffer to send to USB host.
 * 
 * @param   client_ctx - [IN]  usb_ctx of the audio streaming client
 *                buf_ptr - [IN]  pointer to the buffer needs to be sent
 *                transfer_size - [IN] size of the buffer to be sent
 *                cb_data - [IN] pointer to client data structure needed on callback completion.
 * 
 * @return  TRUE,  if buffer was queued to hardware successfully
 *              FALSE, if buffer failed to be queued to hardware
 */
// ===================================================================
uint32 usb_isoc_in (client_ctx_t* client_ctx, uint8* buf_ptr, uint32 buf_size, void* cb_data);


#endif /* USB__AUDIO_H */
