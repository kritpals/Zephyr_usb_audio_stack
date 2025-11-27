#ifndef USB_AUDIO_FD_H
#define USB_AUDIO_FD_H
/*=======================================================================*//**
  @file usb_audio_class.h

  Audio class driver implementation

  @file         usb_audio_class.h
 
  @brief        Skeleton documentation example
 
  @details      Audio class has two types of interfaces. 
				Audio control and streaming type interfaces.
				This module supports both.
 
               Copyright (c) 2017 Qualcomm Technologies Inc.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*/
/*========================================================================*/
/*  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/func/usb_audio_fd.h#14 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_urb.h"
#include "usb_common.h"
#include "usb_dcd.h"
#include "usb_api.h"
#include "usb_audio.h"

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------
#define USB_AUDIO_MAX_TRANSFER_SIZE                   (1023)
#define USB_AUDIO_FB_FREQ_SIZE_FS                     (3)
#define USB_AUDIO_FB_FREQ_SIZE_HS                     (4)
#define UAC_FN_PROTOCOL_VERSION_03_00                 (0x30)
#define UAC_IFC_PROTOCOL_VERSION_03_00                (0x30)
#define UAC_FN_PROTOCOL_VERSION_02_00                 (0x20)
#define UAC_IFC_PROTOCOL_VERSION_02_00                (0x20)

#define USB_AUDIO_FN_CATEGORY_UNDEF                   (0x00)
#define USB_AUDIO_FN_CATEGORY_DESKTOP_SPEAKER         (0x01)
#define USB_AUDIO_FN_CATEGORY_HOME_THEATER            (0x02)
#define USB_AUDIO_FN_CATEGORY_MICROPHONE              (0x03)
#define USB_AUDIO_FN_CATEGORY_HEADSET                 (0x04)
#define USB_AUDIO_FN_CATEGORY_TELEPHONE               (0x05)
#define USB_AUDIO_FN_CATEGORY_CONVERTER               (0x06)
#define USB_AUDIO_FN_CATEGORY_RECORDER                (0x07)
#define USB_AUDIO_FN_CATEGORY_IO_BOX                  (0x08)
#define USB_AUDIO_FN_CATEGORY_MUSIC_INSTR             (0x09)
#define USB_AUDIO_FN_CATEGORY_PRO_AUDIO               (0x0A)
#define USB_AUDIO_FN_CATEGORY_AUDIO_VIDEO             (0x0B)
#define USB_AUDIO_FN_CATEGORY_CONTROL_PANEL           (0x0C)
#define USB_AUDIO_FN_CATEGORY_HEADPHONE               (0x0D)
#define USB_AUDIO_FN_CATEGORY_GENERIC_SPEAKER         (0x0E)
#define USB_AUDIO_FN_CATEGORY_HEADSET_ADAPTOR         (0x0F)
#define USB_AUDIO_FN_CATEGORY_SPEAKER_PHONE           (0x10)
#define USB_AUDIO_FN_CATEGORY_OTHER                   (0xFF)

#define USB_INTERFACE_CLASS_AUDIO                     (0x1)
#define USB_INTERFACE_AUDIO_SUBCLASS_UNDEFINED        (0x0)
#define USB_INTERFACE_AUDIO_SUBCLASS_CONTROL          (0x1)
#define USB_INTERFACE_AUDIO_SUBCLASS_STREAMING        (0x2)

#define USB_AUDIO_STD_IFC_ASOC_DESC_TYPE              (0x0B)
#define USB_AUDIO_CS_DESC_TYPE                        (0x24)
#define USB_AUDIO_CS_DESC_SUBTYPE_UNDEF               (0x00)
#define USB_AUDIO_CS_DESC_SUBTYPE_HEADER              (0x01)
#define USB_AUDIO_CS_DESC_SUBTYPE_IT                  (0x02)
#define USB_AUDIO_CS_DESC_SUBTYPE_OT                  (0x03)
#define USB_AUDIO_CS_DESC_SUBTYPE_MU                  (0x04)
#define USB_AUDIO_CS_DESC_SUBTYPE_FU                  (0x06)
#define USB_AUDIO_CS_DESC_SUBTYPE_CSRC                (0x0A)
#define USB_AUDIO_CS_DESC_SUBTYPE_CONN                (0x0F)
#define USB_AUDIO_CS_DESC_SUBTYPE_POWER_DOMAIN        (0x10)

#define USB_AUDIO_CS_EP_DESC_TYPE                     (0x25)
#define USB_AUDIO_CS_EP_DESC_SUBTYPE_GENERAL          (0x01)

#define USB_AUDIO_CS_CLUSTER_DESC_TYPE                (0x26)

// USB class specific descriptor types
#define USB_AUDIO_CS_IFC_DESC_SUBTYPE_GENERAL         (0x01)
#define USB_AUDIO_CS_IFC_DESC_SUBTYPE_FORMAT          (0x02)
#define USB_AUDIO_CS_IFC_DESC_FORMAT_TYPE_1           (0x01)

// USB terminal types
#define USB_AUDIO_TERM_TYPE_UNDEF                     (0x0100)
#define USB_AUDIO_TERM_TYPE_STREAMING                 (0x0101)
#define USB_AUDIO_TERM_TYPE_VENDOR_SPEC               (0x01FF)
#define USB_AUDIO_TERM_TYPE_IT_UNDEF                  (0x0200)
#define USB_AUDIO_TERM_TYPE_IT_MIC                    (0x0201)
#define USB_AUDIO_TERM_TYPE_IT_MIC_DESKTOP            (0x0202)
#define USB_AUDIO_TERM_TYPE_IT_MIC_PERSONAL           (0x0203)
#define USB_AUDIO_TERM_TYPE_IT_MIC_OMNIDIR            (0x0204)
#define USB_AUDIO_TERM_TYPE_IT_MIC_ARRAY              (0x0205)
#define USB_AUDIO_TERM_TYPE_OT_UNDEF                  (0x0300)
#define USB_AUDIO_TERM_TYPE_OT_SPEAKER                (0x0301)
#define USB_AUDIO_TERM_TYPE_OT_HEADPHONES             (0x0302)
#define USB_AUDIO_TERM_TYPE_OT_HM_DISPLAY_AUD         (0x0303)
#define USB_AUDIO_TERM_TYPE_OT_SPEAKER_DESKTOP        (0x0304)
#define USB_AUDIO_TERM_TYPE_OT_SPEAKER_ROOM           (0x0305)
#define USB_AUDIO_TERM_TYPE_OT_SPEAKER_COMM           (0x0306)
#define USB_AUDIO_TERM_TYPE_OT_SPEAKER_LF             (0x0307)

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------

// Standard Interface Association Descriptor
typedef PACKED struct uac_std_ifc_asoc_desc
{
  uint8   bLength;              // 8 bytes
  uint8   bDescriptorType;      // IFC_ISOC type
  uint8   bFirstInterface;
  uint8   bInterfaceCount;
  uint8   bFunctionClass;       // USB_INTERFACE_CLASS_AUDIO
  uint8   bFunctionSubClass;    // USB_INTERFACE_AUDIO_SUBCLASS_UNDEFINED
  uint8   bFunctionProtocol;    // USB_AUDIO_FN_PROTOCOL
  uint8   iFunction;
}
PACKED_POST uac_std_ifc_asoc_desc_t;


struct usb_audio_stream;
typedef struct usb_audio_stream usb_audio_stream_t;

struct usb_audio_ctx;
typedef struct usb_audio_ctx usb_audio_ctx_t;

struct usb_audio_stream
{
  usb_audio_stream_t*  next;
  usb_audio_ctx_t* audio_ctx;

  // stream descriptors
  usb_audio_class_rev_t rev;
  usb_dcd_dsc_interface_t* ifc;
  uint8* ifc_asoc_desc;
  uint8 ifc_num;
  usb_ifc_id ifc_id;  

  // stream configuration.
  usb_audio_stream_cfg cfg;
  uint32 (*get_expl_fb_freq) (uint32 client_id);
  uint32 expl_fb_req_id;
  uint32 expl_fb_freq;     // Feedback frequency reported by client in 8.24 format.
  uint32* expl_fb_freq_bin; // Feedback frequency in binary format
  uint16 expl_fb_len;
  uint8 n_ch;
  audio_node_t* term;
  audio_cs_t* cs;
  uint32* freq_arr;
  uint16 freq_arr_size;
  audio_slot_size_t* slot_arr;
  uint16 slot_arr_size;

  // bus parameters
  uint8 bm1;     // This is bInterval minus 1. For constructing a descriptor add 1 to this value.
  uint32 usb_frame_us;  // length of each USB frame in us.
  usb_device_connect_speed_t speed;

  // revision specific function pointers 
  uint8 (*get_bps)(usb_dcd_dsc_interface_t* ifc);
  
  uint8* (*handle_get_req)(usb_audio_stream_t* stream, uint8 ifc_num, uint8 recp, 
    uint8 req, uint8 control, uint32* len);

  boolean (*handle_set_req)(usb_audio_stream_t* stream, uint8 ifc_num, uint8 unit_id, 
    uint8 req, uint8 control, uint32* buff, uint32 len);
};

struct usb_audio_ctx
{
  usb_audio_class_rev_t rev;
  usb_dcd_dsc_interface_t* ifc;

  void (*notify_client)(uint32 event, uint32 client_id, void* data);

  usb_ifc_id id;
  uint8 ifc_num;
  usb_audio_stream_t* stream_q;

  // configuration
  usb_audio_ctrl_cfg ctrl_cfg;
  uint8 n_ifc;
  uint8 n_nodes;
  usb_audio_clock_mode_t clock_mode;
  audio_node_t* topology;
  usb_audio_profile_t profile;
  uint8* dsc_buff;

  boolean (*get_req) (uint32 client_id, audio_node_t* node, audio_ctrl_t ctrl, audio_req_t req, 
    audio_ch_t ch, uint32* buff, uint32* len);

  boolean (*set_req) (uint32 client_id, audio_node_t* node, audio_ctrl_t ctrl, audio_req_t req, 
    audio_ch_t ch, uint32* buff, uint32 len);

  // USB audio class revision specific function pointers
  uint8* (*handle_get_req)(usb_audio_ctx_t* audio_ctx, uint8 ifc_num, uint8 unit_id, 
    uint8 ch, uint8 control, uint8 req, uint32* len);

  boolean (*handle_set_req)(usb_audio_ctx_t* audio_ctx, uint8 ifc_num, uint8 unit_id, 
    uint8 ch, uint8 control, uint8 req, uint32* buff, uint32 len);

};

typedef struct usb_audio_ctrl_init_cfg
{
  usb_audio_profile_t audio_profile;
  usb_audio_clock_mode_t clock_mode;
  usb_audio_mic_t mic_type;
  void (*notify_client)(uint32 event, uint32 client_id, void* data);
  boolean (*get_req) (uint32 client_id, audio_node_t* node, audio_ctrl_t ctrl, audio_req_t req, 
    audio_ch_t ch, uint32* buff, uint32* len);
  boolean (*set_req) (uint32 client_id, audio_node_t* node, audio_ctrl_t ctrl, audio_req_t req, 
    audio_ch_t ch, uint32* buff, uint32 len);
} usb_audio_ctrl_init_cfg_t;

typedef struct usb_audio_stream_init_cfg
{
  usb_audio_ctx_t* audio_ctx;
  uint16 as_freq;
  uint8* as_bus_cfg;
  usb_audio_mic_t mic_type;
  uint32 (*get_expl_fb_freq) (uint32 client_id);
} usb_audio_stream_init_cfg_t;

typedef struct usb_fn_tbl_fd_audio
{
  uint64 (*usb_audio_power_of_two)(uint64 exponent);
  uint8 (*usb_num_bit_set)(uint32 input);
  uint8 (*usb_audio_get_bm1_from_us)(uint16 bint_us, uint32 usb_frame_us);
  uint32 (*usb_audio_calc_transfer_size)(uint32 freq, uint8 n_ch, uint8 bps, uint8 bm1, uint32 usb_frame_us);
  uint16 (*usb_audio_conv_ff_to_bin)(usb_audio_stream_t* stream, uint32 ff_bin_8_24, uint32* dsc);
  void (*usb_audio_notify_speed)(usb_device_connect_speed_t speed, void* data);
  audio_node_t* (*usb_audio_get_node)(usb_audio_ctx_t* audio_ctx, uint8 unit_id);
  audio_node_t* (*usb_audio_get_term_id)(usb_audio_ctx_t* audio_ctx, usb_ifc_id ifc_id, uint8 stream_ifc_num);
  uint8 (*usb_audio_get_mic_n_ch)(usb_audio_mic_t mic_type);
  uint16 (*usb_audio_get_ot_type)(usb_audio_profile_t audio_profile);
  void (*usb_audio_ctrl_set_cs)(audio_cs_t* cs, usb_audio_unit_id_t id, uint8 controls, audio_controls_cs_t* controls_ptr);
  void (*usb_audio_ctrl_set_it)(audio_it_t* it, usb_audio_unit_id_t id, usb_audio_unit_id_t clock_id, uint8 n_ch, uint8 term_type);
  void (*usb_audio_ctrl_set_fu)(audio_fu_t* fu, usb_audio_unit_id_t id, usb_audio_unit_id_t source_id, uint8 controls, uint8 n_ch);
  void (*usb_audio_ctrl_set_ot)(audio_ot_t* ot, usb_audio_unit_id_t id, usb_audio_unit_id_t clock_id, usb_audio_unit_id_t source_id, uint8 term_type);
  void (*usb_audio_ctrl_set_mu)(audio_mu_t* mu, usb_audio_unit_id_t id, usb_audio_unit_id_t src1_id, usb_audio_unit_id_t src2_id, uint8 n_op_ch);
  audio_node_t* (*usb_audio_ctrl_alloc_badd_mic_topology)(uint8* n_nodes, uint8 n_ch_mic);
  audio_node_t* (*usb_audio_ctrl_alloc_hph_topology)(uint8* n_nodes);
  audio_node_t* (*usb_audio_ctrl_alloc_hset_topology)(uint8* n_nodes);
  audio_node_t* (*usb_audio_ctrl_alloc_badd_hset_topology)(uint8* n_nodes);
  audio_node_t* (*usb_audio_ctrl_alloc_hset_topology_mic_n_ch)(usb_audio_clock_mode_t clock_mode, uint8 mic_n_ch, uint8* n_nodes);
  void (*usb_audio_ctrl_set_topology)(usb_audio_ctx_t* audio_ctx);
  void (*usb_audio_ctrl_set_cfg)(void* ctx, usb_dcd_dsc_interface_t* ifc);
  void (*usb_audio_stream_set_cfg)(void* ctx, usb_dcd_dsc_interface_t* ifc);
  int (*usb_audio_stream_set_ifc)(usb_dcd_dsc_interface_t* ifc, usb_setup_packet_t* req);
  void (*usb_audio_expl_fb_cb)(usb_urb_t* urb);
  int (*usb_audio_start_expl_fb)(usb_dcd_dsc_endpoint_t* ep, usb_setup_packet_t* req);
  int (*usb_audio_start_session)(usb_dcd_dsc_endpoint_t* ep, usb_setup_packet_t* req);
  usb_dcd_dsc_interface_t* (*usb_audio_alloc_as_desc)(uint8 ** dsc, uint16 * len, uint16 dsc_size, void* data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, uint32 rev);
  usb_dcd_dsc_interface_t* (*usb_audio_alloc_ac_desc)(uint8 ** dsc, uint16 * len, uint16 dsc_size, void* data, uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, uint32 rev);
  void (*usb_audio_ctrl_deinit)(void* data);
  void* (*usb_audio_ctrl_init)(usb_ifc_id ifc_id, uint8 ifc_num, void* data);
  uint32 (*usb_audio_get_freq_from_mask)(uint16 as_freq_mask);
  void (*usb_audio_get_freq_arr)(uint16 as_freq, uint32* freq_arr, uint16 freq_arr_size);
  boolean (*usb_audio_is_bus_cfg_valid)(uint8 as_bus_cfg);
  uint8 (*usb_audio_get_slot_arr_size)(uint8* as_bus_cfg);
  audio_slot_size_t (*usb_audio_get_slot_cfg)(uint8 as_bus_cfg);
  void (*usb_audio_get_slot_arr)(uint8* as_bus_cfg, audio_slot_size_t* slot_arr, uint16 slot_arr_size);
  uint8* (*usb_audio_alloc_freq_range_desc)(uint32* freq_arr, uint16 freq_arr_size, uint16* freq_range_size);
  void (*usb_audio_stream_deinit)(void* data);
  void* (*usb_audio_stream_init)(usb_ifc_id ifc_id, uint8 ifc_num, void* data);
  boolean (*usb_audio_ctrl_handle_set_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* buff, uint32 len);
  uint8* (*usb_audio_ctrl_handle_get_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* len);
  boolean (*usb_audio_stream_handle_set_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* buff, uint32 len);
  uint8* (*usb_audio_stream_handle_get_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* len);  
} usb_fn_tbl_fd_audio_t;

//extern usb_fn_tbl_fd_audio_t fn_tbl_fd_audio; 
//TODO: #define usb_fn_fd_audio() (&fn_tbl_fd_audio)

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

#endif /* #ifndef USB_AUDIO_CLASS_H */

