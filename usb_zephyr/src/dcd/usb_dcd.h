#ifndef USB_DCD_H
#define USB_DCD_H
/*=======================================================================*//**
  @file         usb_dcd.h
 
  @brief        DCD API
 
  @details      Defines structures and functions required to initialize DCD

                In order to function, DCD should be provided with device
                definition. This includes definitions for device,
                its configurations, interfaces, endpoints, strings etc.

                For every element, there are 2 structures representing it:
                hardware (USB descriptor) and software one. Software structure 
                holds all relevant data, including internal states;
                it also holds pointer to USB descriptor.

                It is responsibility of upper layer to initialize device
                definition structures prior to DCD initialization.

                USB descriptors should be allocated in such way that
                all descriptors related to particular configuration follows
                its configuration descriptor, in order specified in 
                USB 2.0 spec, clause 9.4.3.
 
                For class specific requests, 'setup' callbacks may be defined
                at device, interface, endpoint levels. If callback is defined,
                it is called with any non-standard SETUP.
 
               Copyright (c) 2008 QUALCOMM Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*//*========================================================================*/
/* $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dcd/usb_dcd.h#9 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_dcd_ch9.h"
#include "usb_urb.h"
#include "usb_common.h"
#include "usb_dci.h"
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

typedef struct usb_dcd_dsc_endpoint usb_dcd_dsc_endpoint_t;
typedef struct usb_dcd_dsc_interface usb_dcd_dsc_interface_t;
typedef struct usb_dcd_dsc_configuration usb_dcd_dsc_configuration_t;
typedef struct usb_dcd_dsc_qual usb_dcd_dsc_qual_t;

typedef struct 
{
  usb_urb_t rx;
  usb_urb_t tx;
} usb_ctrl_urb;

typedef enum
{
  USB_STR_IDX_LANG_ID = 0,
  USB_STR_IDX_MANUF,
  USB_STR_IDX_PRODUCT,
  USB_STR_IDX_SERIAL_NUM,
  USB_STR_IDX_MAX,
} usb_dcd_string_index;

typedef struct usb_dcd_dsc_string 
{
  usb_desc_header_t* descriptor;
  uint16 langid;
} usb_dcd_dsc_string_t;

/* Forward declaration */
struct usb_dcd_ctx;
typedef struct usb_dcd_ctx usb_dcd_ctx_t;

//struct usb_dci_ctx;
//typedef struct usb_dci_ctx usb_dci_ctx_t;

#define usb_dci usb_dci_ctx_t

typedef struct usb_fd_callback
{
  boolean (*ctrl_in_cb) (uint8* setup_ptr, uint8* payload, uint32* payload_size);
  boolean (*ctrl_out_cb) (uint8* setup_ptr, uint8* payload, uint32 payload_size);
  boolean (*handle_set_req)(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req, uint32* buff, uint32 len);
  void (*set_req_status_comp_cb)(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req);
  uint8* (*handle_get_req)(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req, uint32* len);
  void (*notify)(void* fd_ctx, usb_notify_events_t event);   
}
usb_fd_callback_t;

typedef void (*urb_complete_callback_t)(usb_urb_t* urb);

typedef struct usb_dcd_isoc_info
{
  uint8 dir;
  uint8 ep;
} usb_dcd_isoc_info_t;


typedef enum
{
  NORMAL_SPEED_CFG,
  OTHER_SPEED_CFG,
  MAX_CONFIURATIONS   //this is last entires, not real configurations
} usb_dcd_cfg_type;

typedef struct usb_fn_tbl_dcd
{
  uint32 (*usb_dcd_desc_max_packet_size)(usb_device_connect_speed_t speed);
  void (*usb_dcd_create_dev_desc)(usb_desc_device_t** dev_desc, uint16 vendor_id, uint16 product_id, usb_device_connect_speed_t speed, usb_max_speed_required_t speed_required, uint8 n_cfg);
  void (*usb_dcd_create_dev_qual_desc)(usb_desc_dev_qual_t** dev_qual_desc);
  void (*usb_dcd_allocate_dev_qual)(usb_dcd_dsc_qual_t** dev_qual);
  void (*usb_dcd_allocate_strings)(usb_dcd_ctx_t* dcd_ctx, uint16 lang_id, uint8* manuf_str, uint8* product_str);
  void (*usb_dcd_create_ep_comp_desc)(usb_ep_comp_desc_t** ep_comp_ptr, uint8 burst_size, uint8 attr, uint8 bpi);
  void (*usb_dcd_create_ep_desc)(usb_dcd_dsc_endpoint_t** endpoint, uint8 ep_num, uint8 ep_mask, uint8 ep_attr, uint8 ep_interval, uint16 max_packet_size);
  void (*usb_dcd_create_ifc_desc)(usb_dcd_dsc_interface_t** interface, uint8 ifc_index, uint8 alt_setting, uint8 n_ep, uint8 ifc_class, uint8 subclass, uint8 protocol, uint8 str_index);
  usb_dcd_dsc_configuration_t* (*dcd_get_config_tree)(const usb_dcd_ctx_t* dcd_ctx);
  int (*dcd_get_config_value)(const usb_dcd_ctx_t* dcd_ctx);
  usb_dcd_dsc_configuration_t* (*find_config_by_value)(const usb_dcd_ctx_t* dcd_ctx, uint8 value);
  usb_dcd_dsc_interface_t* (*get_curr_ifc_alt_set)(const usb_dcd_ctx_t* dcd_ctx, uint8 ifc_num);
  usb_dcd_dsc_endpoint_t* (*usb_dcd_find_ep)(const usb_dcd_ctx_t* dcd_ctx, uint16 ep_address);
  usb_desc_header_t* (*get_string_desc)(const usb_dcd_ctx_t* dcd_ctx, uint16 lang_id, uint8 index);
  void (*usb_dcd_fd_notify)(usb_dcd_ctx_t* dcd_ctx, usb_notify_events_t event);
  int (*usb_dcd_set_interface)(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_interface_t* ifc, uint8 ifc_num, uint8 alt);
  int (*usb_dcd_set_config)(usb_dcd_ctx_t* dcd_ctx, uint8 new_config);
  int (*usb_dcd_control_transfer)(usb_dcd_ctx_t* dcd_ctx, int is_tx, void* buff, uint32 len);
  int (*usb_dcd_control_reply)(usb_dcd_ctx_t* dcd_ctx, uint32 len);
  int (*handle_get_descriptor)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
  int (*handle_setup_dev)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
  int (*handle_setup_ifc)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
  int (*handle_ep_halt)(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_endpoint_t* ep, int halt);
  int (*handle_setup_ep)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
  int (*handle_setup_std)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);
  void (*usb_dcd_handle_reset)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_handle_disconnect)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_handle_suspend)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_handle_setup)(usb_dcd_ctx_t* dcd_ctx, void* buffer_ptr);
  void (*usb_dcd_port_status_changed)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_notify)(void* dev_ptr, usb_notify_events_t  event, void* buffer_ptr);
  void (*usb_dcd_set_bos)(usb_dcd_ctx_t* dcd_ctx, usb_bos_desc_t* bos_desc);
  boolean (*usb_dcd_set_cfg_tree)(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_configuration_t* cfg_tree);
  void (*usb_dcd_create_desc)(usb_dcd_ctx_t* dcd_ctx_ptr, uint16 vendor_id, uint16 product_id, uint8 n_cfg);
  void (*usb_dcd_ctrl_start_xfer)(usb_dcd_ctx_t *dcd_ctx);
  boolean (*usb_dcd_init)(usb_max_speed_required_t speed_required, usb_dcd_ctx_t** dcd_ctx_ptr, void* fd_ctx, usb_fd_callback_t fd_cb, uint16 lang_id, uint8* manuf_str, uint8* product_str, uint32 feature_flags);
  boolean (*usb_dcd_free_desc)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_shutdown)(usb_dcd_ctx_t** dcd_ptr);
  int (*usb_dcd_submit_urb)(usb_dcd_ctx_t* dcd_ctx, usb_urb_t* urb);
  void (*usb_dcd_set_core)(usb_dcd_ctx_t* dcd_ctx, usb_core_type core_id);
  void* (*usb_dcd_get_dci_ctx)(usb_dcd_ctx_t* dcd_ctx);
  usb_device_connect_speed_t (*usb_dcd_get_speed)(usb_dcd_ctx_t* dcd_ctx);
  boolean (*usb_dcd_is_usb_configured)(usb_dcd_ctx_t* dcd_ctx);
  uint32 (*usb_dcd_get_ctrl_urb_tx_transfer_status)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_poll)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_reset)(usb_dcd_ctx_t* dcd_ctx);
  uint32 (*usb_dcd_cancel_transfer)(usb_dcd_ctx_t* dcd_ctx, usb_urb_t* urb_ptr);
  uint32 (*usb_dcd_get_max_packet_size)(usb_dcd_ctx_t* dcd_ctx);
  boolean (*usb_dcd_wakeup)(usb_dcd_ctx_t* dcd_ctx);
  void (*usb_dcd_class_status2_ack_cb)(struct usb_urb* urb_ptr);
  void (*usb_dcd_class_data_cb)(struct usb_urb* urb_ptr);
  void (*usb_dcd_handle_class_status3_req_ifc)(struct usb_urb* urb_ptr);
  void (*usb_dcd_handle_class_status3_req_ep)(struct usb_urb* urb_ptr);
  boolean (*usb_dcd_handle_setup_class_ifc)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
  boolean (*usb_dcd_handle_setup_class_ep)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir);
  boolean (*usb_dcd_handle_setup_class)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);
  void (*usb_dcd_vendor_out_cb)(struct usb_urb* urb_ptr);
  int (*usb_dcd_handle_setup_vendor)(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req);
} usb_fn_tbl_dcd_t;

struct usb_dcd_ctx{
  /*===========supplied by application==============*/
  usb_desc_device_t* descriptor;
  usb_dcd_dsc_configuration_t* configurations;
  usb_dcd_dsc_string_t strings[USB_STR_IDX_MAX];
  usb_bos_desc_t* bos_descriptor;
  usb_dcd_dsc_configuration_t* other_speed_configuration;
  usb_dcd_dsc_qual_t* dev_qual;
  usb_core_type core_id;
  /**
   * Custom SETUP handler.
   *
   * Called for all device level SETUP not understood by DCD
   *
   * Return number of bytes transmitted;
   * for "set" type commands return 0.
   * In case of error, or if SETUP was not handled, return
   * negative error.
   */
  int (*setup)(struct usb_dcd_ctx* dcd_ctx, usb_setup_packet_t* req);

  /*==============private===============*/
  /* current state */
  usb_desc_configuration_t* other_speed_config_desc;
  //boolean is_attached;                    //is Vbus connected? 
  usb_device_connect_speed_t speed;  //High=0,Full=1,Low=2,FullSpeed_48=3,SuperSpeed=4,Unknown = 5
  int max_current;                    // in ma
  uint8 address;
  uint8 config_value;
  usb_dcd_dsc_configuration_t* active_configuration;
  //for setup transfers
  uint8 *setup_status;
  uint8 *setup_data;
  usb_ctrl_urb ctrl_urb;
  usb_setup_packet_t cached_req;
  uint32      max_packet_size;
  boolean u1_enabled;
  boolean u2_enabled;
  boolean usb_is_configured;
  uint32  test_mode;
  usb_max_speed_required_t speed_required;
  uint8* vendor_buff;

  // FD layer info
  usb_fd_callback_t fd_cb;  
  void* fd_ctx;
  usb_dci* dci_ctx;
};

struct usb_dcd_dsc_qual
{
  struct usb_dcd_dsc_qual* next;
  usb_desc_dev_qual_t* descriptor;
};

struct usb_dcd_dsc_configuration {
  /**
  * list of all configurations for device
  */
  usb_dcd_dsc_configuration_t* next;
  usb_desc_configuration_t* descriptor;
  usb_dcd_ctx_t* dcd_ctx;
  usb_dcd_dsc_interface_t* interfaces;
  uint16 desc_size;  
  int (*setup)(usb_dcd_dsc_configuration_t* cfg, usb_setup_packet_t* req);  
};

struct usb_dcd_dsc_interface {
  /**
  * list of all interfaces/altsettings for config
  */
  usb_dcd_dsc_interface_t* next;
  usb_desc_interface_t* descriptor;
  usb_dcd_dsc_configuration_t* configuration;
  usb_dcd_dsc_endpoint_t* endpoints;

  uint8* cs_dsc;         // pointer to class specific descriptor
  uint16 cs_dsc_size;    // size of the class specific descriptor
  usb_ifc_id id;

  /**
  * Custom SETUP handler.
  * 
  * Called for all interface level SETUP not understood by DCD
  * 
  * Return number of bytes transmitted;
  * for "set" type commands return 0.
  * In case of error, or if SETUP was not handled, return
  * negative error.
  */
  int (*setup)(usb_dcd_dsc_interface_t* ifc, usb_setup_packet_t* req);

  /**
  * currently selected alt setting for this interface.
  * 
  * set simultaneously for all altsettings for interface
  */
  uint8 current_altsetting;
};

struct usb_dcd_dsc_endpoint {
  /**
  * list of endpoints for interface
  */
  usb_dcd_dsc_endpoint_t* next;
  usb_desc_endpoint_t* descriptor;
  usb_dcd_dsc_interface_t* ifc;
  uint8* cs_dsc;
  uint16 cs_dsc_size;
  /**
  * Custom SETUP handler.
  * 
  * Called for all endpoint level SETUP not understood by DCD
  * 
  * Return number of bytes transmitted;
  * for "set" type commands return 0.
  * In case of error, or if SETUP was not handled, return
  * negative error.
  */
  int (*setup)(usb_dcd_dsc_endpoint_t* ep, usb_setup_packet_t* req);
  /* private data */
  uint32 is_halt:1;
};

typedef PACKED struct usb_config_struct_obex {
  usb_desc_configuration_t conf1;
  usb_desc_interface_t ifc_data;
  usb_desc_endpoint_t ep_in;
  usb_desc_endpoint_t ep_out;
} PACKED_POST usb_config_struct_obex_t;


typedef PACKED struct usb_config_struct_obex_ss {
  usb_desc_configuration_t conf1;
  usb_desc_interface_t ifc_data;
  usb_desc_endpoint_t ep_in;
  usb_ep_comp_desc_t  ep_in_comp;
  usb_desc_endpoint_t ep_out;
  usb_ep_comp_desc_t  ep_out_comp;
} PACKED_POST usb_config_struct_obex_ss_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
* -------------------------------------------------------------------------*/

extern usb_fn_tbl_dcd_t fn_tbl_dcd;
#define usb_fn_dcd()  (&fn_tbl_dcd)

#endif /*USB_DCD_H*/

