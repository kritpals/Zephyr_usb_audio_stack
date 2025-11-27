#ifndef USB_FD_H
#define USB_FD_H
/*=======================================================================*//**
  @file usb_fd.h

  Functional driver for download function

  @file         usb_fd.h
 
  @brief        Skeleton documentation example
 
  @details      There is no standard class for download. 
                Instead, vendor-specific interface with 
                2 bulk EP (1-IN, 1-OUT) get used.
 
               Copyright (c) 2008-2009 QUALCOMM Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*//*========================================================================*/
/*  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/func/usb_fd.h#10 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_urb.h"
#include "usb_common.h"

#include "usb_audio_fd.h"
#include "usb_hid_fd.h"
#include "usb_dfu_fd.h"
#include "usb_bulk_fd.h"


//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------
#define USB_CFG_DESC_SIZE   (1024)
#define USB_BOS_DESC_SIZE   (128)

#define USB_COMP_SIZE_MAX   (0x8) // max number of interfaces in USB composition.
#define USB_AUDIO_REV_MAX   (0x3) // max number of audio revisions supported in USB composition.

#define USB_STR_LEN_MAX     (64)

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------
#define USB_CONFIG_1                  (0x1)
#define USB_INTERFACE_ALT_SETTING_0   (0x0)
#define USB_INTERFACE_STR_INDEX_NONE  (0x0)
#define USB_INTERFACE_PROTOCOL_NONE   (0x0)

#define USB_INTERFACE_CLASS_VENDOR_SP                 (0xFF)
#define USB_INTERFACE_VENDOR_SP_SUBCLASS_VENDOR_SP    (0xFF)
#define USB_INTERFACE_VENDOR_SP_PROTOCOL_VENDOR_SP    (0xFF)

#define USB_ENDPOINT_BINTERVAL_NONE         (0x0)

typedef struct usb_api_callback
{
  void (*tx_complete)(usb_urb_t* urb);
  void (*rx_complete)(usb_urb_t* urb);
  boolean (*ctrl_in_cb) (uint8* setup_ptr, uint8* payload, uint32* payload_size);
  boolean (*ctrl_out_cb) (uint8* setup_ptr, uint8* payload, uint32 payload_size);
  void (*notify) (uint32 event, uint32 client_id, void* data);
  void (*enum_complete)(boolean enum_flag);
  void* (*get_client_config) (uint8 client_id);
  void (*error)(void);
  void (*notify_suspend)(boolean is_suspend);
} usb_api_callback_t;

typedef struct usb_audio_dev_config 
{
  uint16 lang_id;
  uint16 vendor_id;
  uint8* manuf_str;
  uint16 product_id;
  uint8* product_str;
  usb_audio_profile_t audio_profile;
  usb_audio_class_rev_t audio_rev_arr[USB_AUDIO_REV_MAX];
  uint8 audio_rev_arr_size;
  usb_ifc_id usb_comp[USB_COMP_SIZE_MAX];
  uint8 usb_comp_num_ifc; // number of interfaces in USB composition.
  usb_op_mode_t op_mode;
  usb_audio_class_rev_t top_aud_rev;
  uint8 mic_type;
  uint32 feature_flags;
} usb_audio_dev_config_t;

/* Forward declaration */

#define usb_dcd usb_dcd_ctx_t

typedef struct
{
  uint8 idx;
  usb_urb_t urb[USB_URB_MAX];
} usb_urb_list_t;

typedef struct usb_class
{
  void* ctx;
  void* (*init)(usb_ifc_id ifc_id, uint8 ifc_num, void* data);
  usb_dcd_dsc_interface_t* (*alloc_desc)(uint8 ** dsc, uint16 * len, uint16 dsc_size, void* data,
    uint8 ifc_num, uint8* ep_in_num, uint8* ep_out_num, uint32 rev);
  void (*set_cfg) (void* ctx, usb_dcd_dsc_interface_t* ifc);
  void (*notify_speed)  (usb_device_connect_speed_t speed, void* data);
  void (*enum_comp)(void* fd_ctx, uint8 ifc_num);
  boolean (*handle_set_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* buff, uint32 len);
  void (*set_req_status_comp_cb)(void* fd_ptr, usb_setup_packet_t* req);
  uint8* (*handle_get_req)(void* fd_ptr, usb_setup_packet_t* req, uint32* len);
  void (*deinit)(void* class_ctx);
} usb_class_t;

typedef struct
{
  usb_ifc_id ifc_id;
  uint8 ifc_num;
  usb_class_t fn_class;
  usb_urb_list_t* rx;
  usb_urb_list_t* tx;
} ifc_ctx_t;

typedef struct usb_fd_ctx
{
  usb_dcd* dcd_ctx;
  usb_api_callback_t api_cb;
  boolean dsc_init;
  usb_audio_dev_config_t* dev_cfg;
  ifc_ctx_t* ifc_ctx;
  void (*notify) (uint32 event, void* data);
} usb_fd_ctx_t;

typedef struct usb_fn_tbl_fd
{
  void (*usb_fd_alloc_ep_comp_desc)(uint8** dsc, uint16* len, uint16 dsc_size, uint8 burst_size, uint8 attr, uint8 bpi);
  usb_dcd_dsc_endpoint_t* (*usb_fd_alloc_ep_desc)(uint8** dsc, uint16* len, uint16 dsc_size, uint8 ep_num, uint8 ep_mask, uint8 ep_attr, uint8 ep_interval, uint16 max_packet_size);
  usb_dcd_dsc_interface_t* (*usb_fd_alloc_ifc_desc)(uint8** dsc, uint16* len, uint16 dsc_size, uint8 ifc_index, uint8 alt_setting, uint8 n_ep, uint8 ifc_class, uint8 subclass, uint8 protocol, uint8 str_index);
  usb_dcd_dsc_configuration_t * (*usb_fd_create_cfg_desc)(uint8** dsc, uint16* len, uint16 dsc_size, uint8 id, uint8 n_ifc);
  int (*usb_fd_set_cfg)(usb_dcd_dsc_configuration_t* cfg, usb_setup_packet_t* req);
  void (*usb_fd_set_req_status_comp_cb) (void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req);
  boolean (*usb_fd_handle_set_req)(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req, uint32* buff, uint32 len);
  uint8* (*usb_fd_handle_get_req)(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req, uint32* len);
  usb_bos_desc_t* (*usb_fd_alloc_bos_desc)(usb_fd_ctx_t* fd_ctx);
  usb_dcd_dsc_configuration_t* (*usb_fd_alloc_audio_cfg)(usb_fd_ctx_t* fd_ctx, usb_ifc_id* usb_comp, uint8 n_ifc, usb_device_connect_speed_t speed, usb_audio_class_rev_t audio_rev, uint8 config_num);
  void (*usb_fd_set_transfer_status)(usb_fd_ctx_t* fd_ctx, uint32 transfer_status);
  void (*usb_fd_init_urb)(usb_fd_ctx_t* fd_ctx);
  void (*usb_fd_notify)(void* fd_ctx_ptr, usb_notify_events_t event);
  boolean (*usb_fd_init)(usb_fd_ctx_t** fd_ctx_ptr, usb_api_callback_t api_cb, usb_audio_dev_config_t* dev_cfg, usb_max_speed_required_t speed_required);
  void (*usb_fd_shutdown)(usb_fd_ctx_t** fd_ctx_ptr);
  uint32 (*usb_fd_tx_pkt)(usb_fd_ctx_t* fd_ctx, unsigned char *pkt, uint32 len, uint32 req_id, uint32 client_id, void* cb_data);
  uint32 (*usb_fd_hid_report)(usb_fd_ctx_t* fd_ctx, usb_hid_bitmask_cmd_t report_mask, uint32 client_id);
  uint32 (*usb_fd_rx_pkt)(usb_fd_ctx_t* fd_ctx, void *buff_ptr, uint32 len, uint32 req_id, uint32 client_id, void* cb_data);
  uint32 (*usb_fd_cancel_transfer)(usb_fd_ctx_t* fd_ctx, uint32 client_id);
  uint32 (*usb_fd_cancel_transfer_dir)(usb_fd_ctx_t* fd_ctx, uint32 client_id, uint8 dir);
  void (*usb_fd_poll)(usb_fd_ctx_t* fd_ctx);
  void (*usb_fd_reset)(usb_fd_ctx_t* fd_ctx);
  uint32 (*usb_fd_get_max_packet_size)(usb_fd_ctx_t* fd_ctx);
  usb_device_connect_speed_t (*usb_fd_get_speed)(usb_fd_ctx_t* fd_ctx);
  void* (*usb_fd_get_dci_ctx)(usb_fd_ctx_t* fd_ctx);
  void (*usb_fd_set_core)(usb_fd_ctx_t* fd_ctx, usb_core_type core_id);
  boolean (*usb_fd_is_usb_configured)(usb_fd_ctx_t* fd_ctx);
} usb_fn_tbl_fd_t;

extern usb_fn_tbl_fd_t fn_tbl_fd;
#define usb_fn_fd()   (&fn_tbl_fd)


#endif /* #ifndef USB_FD_H */

