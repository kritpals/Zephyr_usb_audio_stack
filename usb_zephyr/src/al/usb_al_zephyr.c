/*=======================================================================*//**
 * @file        usb_al_zephyr.c
 * @author:     Ported to Zephyr OS
 * @date        16-Oct-2025
 *
 * @brief       USB Adaptation Layer for Zephyr OS
 *
 * @details     This file contains the Zephyr OS implementation of the USB
 *              adaptation layer, replacing QuRT RTOS dependencies.
 *
 * @note        Ported from usb_al_hlos.c
 * 
*//*========================================================================*/

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <string.h>

#include "comdef.h"
#include "usb_log.h"
#include "usb_util.h"
#include "usb_mem_util.h"
#include "usb_api.h"
#include "usb_log_api.h"
#include "usb_fd.h"
#include "usb_dcd_ch9.h"
#include "usb_isr.h"


LOG_MODULE_REGISTER(usb_al, LOG_LEVEL_DBG);
int usb_zephyr_init(void);

SYS_INIT(usb_zephyr_init, APPLICATION, CONFIG_QC_CHGFW_USB_DRIVERS);
//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------
#define USB_PRODUCT_ID      (USB_PID_UAC2_HEADSET)

#define USB_DISABLE_HID     (1 << 0)
#define USB_DISABLE_DFU     (1 << 1)
#define USB_DISABLE_BULK    (1 << 2)

#define USB_THREAD_STACK_SIZE (2048)
#define USB_THREAD_PRIORITY   (5)

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------
typedef struct
{
  boolean is_enumerated;
  boolean vbus_high;
  boolean is_suspend;
  void (*notify) (uint32 event, uint32 client_id, void* data);
  usb_audio_dev_config_t dev_cfg;
  ctrl_client_ctx_t* ctrl_ctx;
  client_ctx_t* client_ctx[USB_COMP_SIZE_MAX];
  usb_fd_ctx_t* fd_ctx;
  usb_isr_ctx_t isr_ctx;
  //usb_log_type* log_ptr;
} usb0_ctx_t;

typedef struct usb_fn_tbl_al
{
  //uint8* (*usb_get_str_dsc_from_acdb_str)(uint8 len, uint16* acdb_str);
  //void (*usb_set_comp_profile)(usb_audio_dev_config_t* dev_cfg, uint32 pid, uint8 op_mode, uint8 disable_flags);
  //void (*usb_set_audio_rev)(usb_audio_dev_config_t* dev_cfg, uint32 pid);
  //void (*usb_set_audio_profile)(usb_audio_dev_config_t* dev_cfg, usb_audio_profile_t audio_profile);
  void* (*usb_client_get_config)(uint8 client_id);
  void (*usb_client_notification)(uint32 event, uint32 client_id, void* data);
  boolean (*usb_ctrl_out_cb)(uint8* setup_ptr, uint8* payload, uint32 payload_size);
  boolean (*usb_ctrl_in_cb)(uint8* setup_ptr, uint8* payload, uint32* payload_size);
  void (*usb_register_ctrl_client)(ctrl_client_ctx_t* ctrl_ctx);
  void (*usb_al_hlos_isr_vbus_event)(uint32 vbus_high);
  void (*usb_al_hlos_isr_pwr_event)(uint32 event_id);
  void (*usb_al_hlos_log_timer_cb)(uint32 event_id);
  void (*usb_al_hlos_enum_complete)(boolean enum_flag);
  void (*usb_al_hlos_disconnect_handler)(void);
  void (*usb_al_disconnect_cb)(void);
  void (*usb_al_notify_suspend)(boolean is_suspend);
  void (*usb_ctx_init)(void);
  void (*usb_ctx_free)(void);
  void (*usb_tx_complete)(usb_urb_t* urb);
  void (*usb_rx_complete)(usb_urb_t* urb);
  void (*usb_handle_reset)(void);
  void (*usb_al_hlos_bulk_init)(usb_max_speed_required_t speed_required);
  uint32 (*usb_client_cnt)(void);
  void (*usb_deregister_client)(client_ctx_t* client_ctx);
  boolean (*usb_register_client)(client_ctx_t* client_ctx);
  void* (*usb_copy_client_data)(void* data_in, uint32 size);
  uint32 (*usb_send_tx)(unsigned char *pkt, uint32 len, uint32 req_id, uint32 client_id, void* cb_data);
  uint32 (*usb_send_hid_report)(uint32 client_id, usb_hid_bitmask_cmd_t report_mask);
  uint32 (*usb_send_rx)(unsigned char *pkt, uint32 len, uint32 req_id, uint32 client_id, void* cb_data);
  boolean (*usb_check_enum)(void);
  uint32 (*usb_get_max_packet_size)(void);
  void (*usb_remove_thread)(void);
  client_ctx_t* (*usb_alloc_register_client_ctx)(usb_ifc_id ifc_id, usb_event_func_t event_cb, usb_func_cb_t rx_cb, usb_func_cb_t tx_cb, void* data, uint32 data_size);
  void (*usb_shutdown)(void);
  void (*usb_return_buffer)(client_ctx_t* client_ctx);
  boolean (*usb_internal_close)(client_ctx_t* client_ctx);
  void (*usb_thread_entry)(void *p1, void *p2, void *p3);
  boolean (*usb_create_thread)(void);
  void (*usb_log_read_send_ulog)(void);
} usb_fn_tbl_al_t;

extern usb_fn_tbl_al_t fn_tbl_al;
#define usb_fn_al() (&fn_tbl_al)

static usb0_ctx_t* usb0_ctx;

// Zephyr thread and synchronization objects
K_THREAD_STACK_DEFINE(usb_thread_stack, USB_THREAD_STACK_SIZE);
static struct k_thread usb_thread_data;
static k_tid_t usb_thread_id;
static struct k_event usb_events;

// Event flags matching original signal definitions
#define USB_EVENT_QUEUE_FLAG        BIT(0)
#define USB_ENUM_DONE_FLAG          BIT(1)
#define USB_PWR_EVENT_QUEUE_FLAG    BIT(2)
#define USB_VBUS_EVENT_FLAG         BIT(3)
#define USB_LOG_TIMER_EXP_FLAG      BIT(4)

//----------------------------------------------------------------------------
// Forward Declarations
//----------------------------------------------------------------------------
static void usb_thread_entry(void *p1, void *p2, void *p3);

//----------------------------------------------------------------------------
// Function Implementations
//----------------------------------------------------------------------------
#if 0 //Audio related code. 

uint8* usb_get_str_dsc_from_acdb_str(uint8 len, uint16* acdb_str)
{
  uint8 str_len;
  uint8 str_size_in_bytes;
  uint8* str_ptr = NULL;
  str_len = MIN(len, USB_STR_LEN_MAX);

  if(str_len)
  {
    str_size_in_bytes = 2 + (str_len * sizeof(uint16));
    USB_ASSERT(str_ptr = (uint8*)usb_fn_mem_util()->usb_malloc(str_size_in_bytes));
    str_ptr[0] = str_size_in_bytes;
    str_ptr[1] = USB_DESCTYPE_STRING;
    memscpy(&str_ptr[2], (str_size_in_bytes - 2), acdb_str, str_len * sizeof(uint16));
  }
  return str_ptr;
}

static void usb_set_comp_profile(usb_audio_dev_config_t* dev_cfg, uint32 pid, uint8 op_mode, 
  uint8 disable_flags)
{
  uint8 idx = 0;

  if(op_mode == USB_OP_MODE_DFU) 
  {
    dev_cfg->usb_comp[idx++] = USB_IFC_ID_DFU;
    dev_cfg->usb_comp_num_ifc = idx;
    return;
  }

  switch(pid)
  {
    case USB_PID_UAC1_HEADSET:
    case USB_PID_UAC2_HEADSET:
    case USB_PID_UAC1_BADD3_HEADSET:
    case USB_PID_UAC2_BADD3_HEADSET:
    case USB_PID_UAC1_BADD3_UAC3_HEADSET:
    case USB_PID_UAC2_BADD3_UAC3_HEADSET:
    {

      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_CONTROL;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_STREAMING_SPEAKER;
      dev_cfg->audio_profile   = USB_AUDIO_HEADSET;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_STREAMING_MIC;
    }
    break;

    case USB_PID_UAC1_HEADPHONE:
    case USB_PID_UAC2_HEADPHONE:
    case USB_PID_UAC1_BADD3_HEADPHONE:
    case USB_PID_UAC2_BADD3_HEADPHONE:
    case USB_PID_UAC1_BADD3_UAC3_HEADPHONE:
    case USB_PID_UAC2_BADD3_UAC3_HEADPHONE:
    {
      dev_cfg->audio_profile = USB_AUDIO_HEADPHONE;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_CONTROL;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_STREAMING_SPEAKER;
    }
    break;

    case USB_PID_UAC1_MICROPHONE:             // 0x9610,
    case USB_PID_UAC2_MICROPHONE:             // 0x9611,
    case USB_PID_UAC1_BADD3_MICROPHONE:       // 0x9612,
    case USB_PID_UAC2_BADD3_MICROPHONE:       // 0x9613,
    case USB_PID_UAC1_BADD3_UAC3_MICROPHONE:  // 0x9614,
    case USB_PID_UAC2_BADD3_UAC3_MICROPHONE:  // 0x9615,
    {
      dev_cfg->audio_profile   = USB_AUDIO_MICROPHONE;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_CONTROL;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_STREAMING_MIC;
    }
    break;

    default:
      dev_cfg->audio_profile = USB_AUDIO_HEADSET;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_CONTROL;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_STREAMING_SPEAKER;
      dev_cfg->usb_comp[idx++] = USB_IFC_ID_AUDIO_STREAMING_MIC;
  }

  if(FALSE == (disable_flags & USB_DISABLE_HID))
  {
    dev_cfg->usb_comp[idx++] = USB_IFC_ID_HID;
  }

  if(FALSE == (disable_flags & USB_DISABLE_DFU))
  {
    dev_cfg->usb_comp[idx++] = USB_IFC_ID_DFU;
  }

  if(FALSE == (disable_flags & USB_DISABLE_BULK))
  {
    dev_cfg->usb_comp[idx++] = USB_IFC_ID_BULK;
  }

  USB_ASSERT(idx < USB_COMP_SIZE_MAX);
  dev_cfg->usb_comp_num_ifc = idx;
}

static void usb_set_audio_rev(usb_audio_dev_config_t* dev_cfg, uint32 pid)
{
  USB_ASSERT(dev_cfg);

  dev_cfg->audio_rev_arr_size = 0;
  
  switch(pid)
  {
    case USB_PID_UAC1_BADD3_UAC3_HEADSET:     // 0x9608
    case USB_PID_UAC1_BADD3_UAC3_HEADPHONE:   // 0x960E
    case USB_PID_UAC1_BADD3_UAC3_MICROPHONE:  // 0x9614
    {
      dev_cfg->audio_rev_arr[2] = USB_AUDIO_CLASS_REV_3;
      dev_cfg->audio_rev_arr_size++;
    }
    case USB_PID_UAC1_BADD3_HEADSET:          // 0x9606
    case USB_PID_UAC1_BADD3_HEADPHONE:        // 0x960C
    case USB_PID_UAC1_BADD3_MICROPHONE:       // 0x9612
    {
      dev_cfg->audio_rev_arr[1] = USB_AUDIO_CLASS_BADD3;
      dev_cfg->audio_rev_arr_size++;
    }
    case USB_PID_UAC1_HEADSET:                // 0x9604
    case USB_PID_UAC1_HEADPHONE:              // 0x960A
    case USB_PID_UAC1_MICROPHONE:             // 0x9610
    {
      dev_cfg->audio_rev_arr[0] = USB_AUDIO_CLASS_REV_1;
      dev_cfg->audio_rev_arr_size++;
    }
    break;

    case USB_PID_UAC2_BADD3_UAC3_HEADPHONE:   // 0x960F
    case USB_PID_UAC2_BADD3_UAC3_HEADSET:     // 0x9609
    case USB_PID_UAC2_BADD3_UAC3_MICROPHONE:  // 0x9615
    {
      dev_cfg->audio_rev_arr[2] = USB_AUDIO_CLASS_REV_3;
      dev_cfg->audio_rev_arr_size++;
    }
    case USB_PID_UAC2_BADD3_HEADSET:          // 0x9607
    case USB_PID_UAC2_BADD3_HEADPHONE:        // 0x960D
    case USB_PID_UAC2_BADD3_MICROPHONE:       // 0x9613
    {
      dev_cfg->audio_rev_arr[1] = USB_AUDIO_CLASS_BADD3;
      dev_cfg->audio_rev_arr_size++;
    }
    case USB_PID_UAC2_HEADSET:                // 0x9605
    case USB_PID_UAC2_HEADPHONE:              // 0x960B
    case USB_PID_UAC2_MICROPHONE:             // 0x9611
    default:
    {
      dev_cfg->audio_rev_arr[0] = USB_AUDIO_CLASS_REV_2;
      dev_cfg->audio_rev_arr_size++;
    }
    break;
  }
}

void usb_set_audio_profile(usb_audio_dev_config_t* dev_cfg, usb_audio_profile_t audio_profile)
{
  switch(dev_cfg->audio_profile)
  {
    case USB_AUDIO_HEADSET:
    {
      if(audio_profile == USB_AUDIO_HEADSET_ADAPTOR || (audio_profile == USB_AUDIO_SPEAKERPHONE)) 
      {
        dev_cfg->audio_profile = audio_profile;
      }
    }
    break;

    case USB_AUDIO_HEADPHONE:
    {
      if(audio_profile == USB_AUDIO_SPEAKER) 
      {
        dev_cfg->audio_profile = audio_profile;
      }
    }
    break;

    case USB_AUDIO_MICROPHONE:
    default:
    {
      // Do nothing
    }
  }
}
#endif

void* usb_client_get_config(uint8 client_id)
{
  return usb0_ctx->client_ctx[client_id]->data;
}

void usb_client_notification(uint32 event, uint32 client_id, void* data)
{
  if(NULL == usb0_ctx->client_ctx[client_id])
  {
    LOG_ERR("Empty client_id: %d", client_id);
    return;
  }

  LOG_DBG("Event %d, data 0x%x", event, (uint32)data);

  switch(event)
  {
    case USB_EVENT_DFU_ENTRY:
    case USB_EVENT_DFU_EXIT:
    case USB_EVENT_AUDIO_CTRL_CFG:
    case USB_EVENT_STREAM_ENABLE:
    {
      usb0_ctx->client_ctx[client_id]->app_event_cb_func(event, data);
    }
    break;

    case USB_EVENT_STREAM_DISABLE:
    {
      usb_fn_fd()->usb_fd_cancel_transfer(usb0_ctx->fd_ctx, client_id);
      usb0_ctx->client_ctx[client_id]->app_event_cb_func(event, data);
    }
    break;

    case USB_EVENT_ENABLED:
    case USB_EVENT_DISCONNECT:
    case USB_EVENT_CLOSE_COMPLETE:
    case USB_EVENT_TYPE_MAX:
    default:
      LOG_WRN("Unknown client layer event");
  }
}

boolean usb_ctrl_out_cb(uint8* setup_ptr, uint8* payload, uint32 payload_size)
{
  USB_ASSERT(usb0_ctx->ctrl_ctx);
  return usb0_ctx->ctrl_ctx->ctrl_out_cb((usb_setup_t*)setup_ptr, payload, payload_size);
}

boolean usb_ctrl_in_cb(uint8* setup_ptr, uint8* payload, uint32* payload_size)
{
  USB_ASSERT(usb0_ctx->ctrl_ctx);
  return usb0_ctx->ctrl_ctx->ctrl_in_cb((usb_setup_t*)setup_ptr, payload, payload_size);
}

void usb_register_ctrl_client(ctrl_client_ctx_t* ctrl_ctx)
{
  usb0_ctx->ctrl_ctx = ctrl_ctx;
}

void usb_al_hlos_isr_vbus_event(uint32 vbus_high)
{
  USB_ASSERT(usb0_ctx);
  
  LOG_DBG("VBUS event: %u", vbus_high);
  usb0_ctx->vbus_high = vbus_high;
  usb_api()->usb_handle_signal(USB_VBUS_EVENT_FLAG);
}

void usb_al_hlos_isr_pwr_event(uint32 event_id)
{
  USB_ASSERT(usb0_ctx);
  
  LOG_DBG("Power event: %u", event_id);
  usb_api()->usb_handle_signal(USB_PWR_EVENT_QUEUE_FLAG);
}

void usb_al_hlos_log_timer_cb(uint32 event_id)
{
  USB_ASSERT(usb0_ctx);
  usb_api()->usb_handle_signal(USB_LOG_TIMER_EXP_FLAG);
}

void usb_al_hlos_isr_ee_event(void)
{
  usb_api()->usb_handle_signal(USB_EVENT_QUEUE_FLAG);
}

static void usb_al_hlos_enum_complete(boolean enum_flag)
{
  USB_ASSERT(usb0_ctx);
  LOG_INF("Enumeration complete: %d", enum_flag);
  usb0_ctx->is_enumerated = enum_flag;
  usb_api()->usb_handle_signal(USB_ENUM_DONE_FLAG);
}

void usb_al_hlos_disconnect_handler(void)
{
  uint32 idx;
  USB_ASSERT(usb0_ctx);

  LOG_INF("Disconnect handler");

  if(usb0_ctx->is_enumerated == TRUE)
  {
    for (idx=0; idx < usb0_ctx->dev_cfg.usb_comp_num_ifc; idx++)
    {
      if ((NULL != usb0_ctx->client_ctx[idx]))
      {
        usb_fn_al()->usb_return_buffer(usb0_ctx->client_ctx[idx]);
      }
    }
  }

  usb_fn_al()->usb_shutdown();
}

void usb_al_disconnect_cb(void)
{
  LOG_ERR("Disconnect on wrong path");
}

void usb_al_notify_suspend(boolean is_suspend)
{
  LOG_DBG("Suspend notification: %d", is_suspend);
}

void usb_ctx_init(void)
{
  usb_drv_params_t* usb_params;

  if (NULL != usb0_ctx)
  {
    return;
  }

  USB_ASSERT(usb0_ctx = (usb0_ctx_t*) usb_fn_mem_util()->usb_malloc(sizeof(usb0_ctx_t)));
  memset(usb0_ctx, 0, sizeof(usb0_ctx_t));
  
  usb0_ctx->is_enumerated         = FALSE;
  usb0_ctx->vbus_high             = TRUE;
  usb0_ctx->fd_ctx                = NULL;  
  usb0_ctx->isr_ctx.usb_events  = &usb_events;
  usb0_ctx->isr_ctx.pwr_handle    = usb_fn_al()->usb_al_hlos_isr_pwr_event;  
  usb0_ctx->isr_ctx.vbus_handle   = usb_fn_al()->usb_al_hlos_isr_vbus_event;
  usb0_ctx->notify                = usb_fn_al()->usb_client_notification;
  //usb0_ctx->log_ptr               = NULL;

  USB_ASSERT(usb_params = (usb_drv_params_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_drv_params_t)));

  usb_fn_util()->usb_get_acdb_params(usb_params);

  //usb0_ctx->dev_cfg.product_str = usb_fn_al()->usb_get_str_dsc_from_acdb_str(usb_params->product_str_len, usb_params->product_str);
  //usb0_ctx->dev_cfg.manuf_str   = usb_fn_al()->usb_get_str_dsc_from_acdb_str(usb_params->manuf_str_len, usb_params->manuf_str);
  usb0_ctx->dev_cfg.feature_flags = usb_params->feature_flags;

  usb_fn_util()->usb_set_halt_on_err(usb_params->feature_flags);

  if(usb_params->lang_id && usb0_ctx->dev_cfg.product_str && usb0_ctx->dev_cfg.manuf_str)
  {
    usb0_ctx->dev_cfg.lang_id = usb_params->lang_id;
  }

  usb_fn_mem_util()->usb_free((void**)&usb_params);
}

void usb_ctx_free(void)
{
  usb0_ctx->is_enumerated = FALSE;
  usb0_ctx->vbus_high = FALSE;

  if(usb0_ctx->dev_cfg.product_str)
  {
    usb_fn_mem_util()->usb_free((void**)&usb0_ctx->dev_cfg.product_str);
  }

  if (usb0_ctx->dev_cfg.manuf_str)
  {
    usb_fn_mem_util()->usb_free((void**)&usb0_ctx->dev_cfg.manuf_str);
  }

  usb_fn_mem_util()->usb_free((void**)&usb0_ctx);
}

void usb_tx_complete(usb_urb_t* urb)
{
  USB_ASSERT(urb && (urb->client_id < usb0_ctx->dev_cfg.usb_comp_num_ifc));

  if (NULL == usb0_ctx->client_ctx[urb->client_id])
  {
    LOG_ERR("TX complete: killed client %d", urb->client_id);
    return;
  }

  if (urb->transfer_status != USB_URB_STATUS_COMPLETE_OK)
  {
    LOG_ERR("TX fail: client %d, status %d, len %d",
      urb->client_id, urb->transfer_status, urb->actual_length);
  }
  else
  {
    if (urb->actual_length != urb->transfer_length)
    {
      LOG_ERR("TX length error: client %d, expected %d, actual %d", 
        urb->client_id, urb->transfer_length, urb->actual_length);
      urb->transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
    }
  }

  if (usb0_ctx->client_ctx[urb->client_id]->app_tx_cb_func)
  {
    usb0_ctx->client_ctx[urb->client_id]->app_tx_cb_func(urb->transfer_buffer_ptr, urb->actual_length, 
      urb->transfer_status, urb->cb_data);
  }
}

void usb_rx_complete(usb_urb_t* urb)
{
  USB_ASSERT(urb && (urb->client_id < USB_COMP_SIZE_MAX) && usb0_ctx->client_ctx[urb->client_id]);

  if(USB_URB_STATUS_TRANSFER_CANCEL == urb->transfer_status)
  {
    LOG_DBG("RX cancelled: client %d, len %d", urb->client_id, urb->actual_length);
  }
  else if (urb->transfer_status != USB_URB_STATUS_COMPLETE_OK)
  {
    LOG_ERR("RX fail: client %d, status %d, len %d",
      urb->client_id, urb->transfer_status, urb->actual_length);
  }
  else
  {
    if (urb->actual_length == 0)
    {
      urb->transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
      LOG_ERR("RX ZLP: client %d", urb->client_id);
    }
  }

  if (usb0_ctx->client_ctx[urb->client_id]->app_rx_cb_func)
  {
    usb0_ctx->client_ctx[urb->client_id]->app_rx_cb_func(urb->transfer_buffer_ptr, urb->actual_length, 
      urb->transfer_status, urb->cb_data);
  }
}

void usb_handle_reset(void)
{
  USB_ASSERT(usb0_ctx);
  usb0_ctx->is_enumerated = FALSE;
  usb_fn_fd()->usb_fd_reset(usb0_ctx->fd_ctx);
}

void usb_al_hlos_bulk_init(usb_max_speed_required_t speed_required)
{
  usb_api_callback_t api_cb;

  if (NULL == usb0_ctx)
  {
    LOG_ERR("USB context empty");
    USB_ASSERT(0);
  }

  //usb_log_buffer_init(&(usb0_ctx->log_ptr));

  usb_fn_util()->usb_os_spinlock_lock();

  if (NULL != usb0_ctx->fd_ctx)
  {
    LOG_WRN("USB HW already initialized");
    usb_fn_util()->usb_os_spinlock_unlock();
    return;
  }
  
  LOG_INF("USB init, vbus: %u, clients: %u", usb0_ctx->vbus_high, usb_fn_al()->usb_client_cnt());

  api_cb.tx_complete        = usb_fn_al()->usb_tx_complete;
  api_cb.rx_complete        = usb_fn_al()->usb_rx_complete;
  api_cb.ctrl_in_cb         = usb_fn_al()->usb_ctrl_in_cb;
  api_cb.ctrl_out_cb        = usb_fn_al()->usb_ctrl_out_cb;
  api_cb.notify             = usb_fn_al()->usb_client_notification;
  api_cb.enum_complete      = usb_fn_al()->usb_al_hlos_enum_complete;
  api_cb.get_client_config  = usb_fn_al()->usb_client_get_config;
  api_cb.error              = usb_fn_al()->usb_al_disconnect_cb;
  api_cb.notify_suspend     = usb_fn_al()->usb_al_notify_suspend;

  usb_fn_fd()->usb_fd_init(&usb0_ctx->fd_ctx, api_cb, &usb0_ctx->dev_cfg, speed_required);

  usb_fn_mem_util()->usb_print_meminfo();

  usb0_ctx->isr_ctx.dci_ctx = usb_fn_fd()->usb_fd_get_dci_ctx(usb0_ctx->fd_ctx);

  usb_fn_isr()->usb_isr_init(&usb0_ctx->isr_ctx);

  LOG_INF("USB init complete");

  usb_fn_util()->usb_os_spinlock_unlock();
}

uint32 usb_client_cnt(void)
{
  uint32 i;
  uint32 cnt = 0;
  for (i=0; i < usb0_ctx->dev_cfg.usb_comp_num_ifc; i++)
  {
     if (usb0_ctx->client_ctx[i])
     {
        LOG_DBG("Client exists: 0x%X, idx %u", (uint32)usb0_ctx->client_ctx[i], i);
        cnt++;
     }
  }
  return cnt;
}

void usb_deregister_client(client_ctx_t* client_ctx)
{
  if (NULL == client_ctx)
  {
    LOG_ERR("Null client context");
  }
  else if (client_ctx->client_id < usb0_ctx->dev_cfg.usb_comp_num_ifc)
  {
    usb0_ctx->client_ctx[client_ctx->client_id] = NULL;
  }
  else
  {
    LOG_ERR("Client ID overflow: %d", client_ctx->client_id);
  }
}

boolean usb_register_client(client_ctx_t* client_ctx)
{
  uint8 i;
  boolean result = FALSE;
  uint32 num_clients;

  if (NULL == client_ctx)
  {
    return result;
  }

  for (i=0; i < usb0_ctx->dev_cfg.usb_comp_num_ifc; i++)
  {
    if ((NULL == usb0_ctx->client_ctx[i]) && (usb0_ctx->dev_cfg.usb_comp[i] == client_ctx->ifc_id))
    {
      client_ctx->client_id = i;
      usb0_ctx->client_ctx[i] = client_ctx;
      result = TRUE;
    }
  }

  if (FALSE == result)
  {
    LOG_ERR("Client registration overflow: %d", client_ctx->client_id);
  }

  num_clients = usb_fn_al()->usb_client_cnt();
  LOG_INF("Clients registered: %d", num_clients);

  if ((result == TRUE) && (usb0_ctx->dev_cfg.usb_comp_num_ifc == num_clients))
  {
    usb_fn_al()->usb_al_hlos_bulk_init((usb_max_speed_required_t)0x0);
  }

  return result;
}

void* usb_copy_client_data(void* data_in, uint32 size)
{
  void* data_out = NULL;

  if(data_in && (size > 0))
  {
    USB_ASSERT(data_out = usb_fn_mem_util()->usb_malloc(size));
    memcpy((void*)data_out, data_in, size);
  }

  return data_out;
}

client_ctx_t* usb_alloc_register_client_ctx(usb_ifc_id ifc_id, usb_event_func_t event_cb, 
  usb_func_cb_t rx_cb, usb_func_cb_t tx_cb, void* data, uint32 data_size)
{
  client_ctx_t* client_ctx_ptr;

  USB_ASSERT(client_ctx_ptr = (client_ctx_t*) usb_fn_mem_util()->usb_malloc(sizeof(client_ctx_t)));

  client_ctx_ptr->ifc_id            = ifc_id;
  client_ctx_ptr->app_event_cb_func = event_cb;
  client_ctx_ptr->app_rx_cb_func    = rx_cb;
  client_ctx_ptr->app_tx_cb_func    = tx_cb;
  client_ctx_ptr->data_size         = data_size;
  client_ctx_ptr->data              = usb_fn_al()->usb_copy_client_data(data, data_size);

  // Check if client is present in USB composition and allocates unique client ID.
  if(FALSE == usb_fn_al()->usb_register_client(client_ctx_ptr))
  {
    usb_fn_mem_util()->usb_free((void**)&client_ctx_ptr);
    return NULL;
  }

  return client_ctx_ptr;
}

uint32 usb_send_tx(unsigned char *pkt, uint32 len, uint32 req_id, uint32 client_id, void* cb_data)
{
  if (usb0_ctx && (TRUE == usb0_ctx->is_enumerated) && usb0_ctx->vbus_high)
  {
    return usb_fn_fd()->usb_fd_tx_pkt(usb0_ctx->fd_ctx, (void *)pkt, len, req_id, client_id, cb_data);    
  }
  return USB_ERR_CABLE_DISCONNECT;
}

uint32 usb_send_hid_report(uint32 client_id, usb_hid_bitmask_cmd_t report_mask)
{
  if (usb0_ctx && (TRUE == usb0_ctx->is_enumerated) && usb0_ctx->vbus_high)
  {
    return usb_fn_fd()->usb_fd_hid_report(usb0_ctx->fd_ctx, report_mask, client_id);    
  }
  return USB_ERR_CABLE_DISCONNECT;
}

uint32 usb_send_rx(unsigned char *pkt, uint32 len, uint32 req_id, uint32 client_id, void* cb_data)
{
  if (usb0_ctx && (TRUE == usb0_ctx->is_enumerated) && usb0_ctx->vbus_high)
  {
    return usb_fn_fd()->usb_fd_rx_pkt(usb0_ctx->fd_ctx, pkt, len, req_id, client_id, cb_data);
  }
  return USB_ERR_CABLE_DISCONNECT;
}

boolean usb_check_enum(void)
{
  USB_ASSERT(usb0_ctx);
  return usb0_ctx->is_enumerated;
}

uint32 usb_get_max_packet_size(void)
{
  USB_ASSERT(usb0_ctx && usb0_ctx->fd_ctx);
  return usb_fn_fd()->usb_fd_get_max_packet_size(usb0_ctx->fd_ctx);
}

void usb_remove_thread(void)
{
  usb_fn_al()->usb_shutdown();
  usb_fn_mem_util()->usb_mem_deinit();
  usb_fn_al()->usb_ctx_free();
}

void usb_shutdown(void)
{
  LOG_INF("USB shutdown");
  usb_fn_isr()->usb_isr_uninit(&(usb0_ctx->isr_ctx));
  usb_fn_fd()->usb_fd_shutdown(&usb0_ctx->fd_ctx); 
  usb0_ctx->is_enumerated = FALSE;
  usb_fn_mem_util()->usb_print_meminfo();
}

void usb_return_buffer(client_ctx_t* client_ctx)
{
  uint32 err = 0;
  USB_ASSERT(client_ctx);
  err = usb_fn_fd()->usb_fd_cancel_transfer(usb0_ctx->fd_ctx, client_ctx->client_id);
  if (err)
  {
    LOG_ERR("Failed to dequeue: id %u", client_ctx->client_id);
  }
  LOG_DBG("Interface close: %u", err);  
}

boolean usb_internal_close(client_ctx_t* client_ctx)
{
  uint32 num_clients;
  USB_ASSERT(client_ctx);

  usb_fn_al()->usb_return_buffer(client_ctx);
  
  if(client_ctx->app_event_cb_func)
  {
    client_ctx->app_event_cb_func(USB_EVENT_CLOSE_COMPLETE, NULL);
  }

  usb_fn_al()->usb_deregister_client(client_ctx);

  if(client_ctx->data) 
  {
    usb_fn_mem_util()->usb_free((void**)&client_ctx->data);
  }

  usb_fn_mem_util()->usb_free((void**)&client_ctx);

  num_clients = usb_fn_al()->usb_client_cnt();

  if (0 == num_clients)
  {
    LOG_INF("All clients closed");
    usb_fn_al()->usb_shutdown();
  }
  else
  {
    LOG_INF("Clients remaining: %u", num_clients);
  }
  
  return TRUE;
}

void usb_handle_signal(uint32 client_sig)
{
  if (NULL == usb0_ctx)
  {
    LOG_ERR("USB context not initialized");
    return;
  }

  if (usb0_ctx->fd_ctx && (client_sig & USB_EVENT_QUEUE_FLAG))
  {
    USB_OS_SAFE_ENTER();    
    usb_fn_isr()->usb_dsr_handle_ee_event(&(usb0_ctx->isr_ctx));
    USB_OS_SAFE_LEAVE();
  }

  if (usb0_ctx->fd_ctx && (client_sig & USB_PWR_EVENT_QUEUE_FLAG))
  {
    USB_OS_SAFE_ENTER();    
    usb_fn_isr()->usb_dsr_handle_pwr_event(&(usb0_ctx->isr_ctx));
    USB_OS_SAFE_LEAVE();
  }

  if (client_sig & USB_VBUS_EVENT_FLAG)
  {
    uint8 idx=0;
    USB_OS_SAFE_ENTER();
    LOG_DBG("VBUS event signal");
    
    if (usb0_ctx->vbus_high == 0)
    {
      LOG_DBG("VBUS low: %u", usb0_ctx->vbus_high); 
      if (usb0_ctx->is_enumerated)
      {
        usb_fn_al()->usb_al_hlos_disconnect_handler();
        for (idx=0; idx < usb0_ctx->dev_cfg.usb_comp_num_ifc; idx++)
        {
          if ((NULL != usb0_ctx->client_ctx[idx]) &&
              (NULL != usb0_ctx->client_ctx[idx]->app_event_cb_func))
          {
            usb0_ctx->client_ctx[idx]->app_event_cb_func(USB_EVENT_DISCONNECT, NULL);
          }
        }
      }
    }
    else if (usb0_ctx->vbus_high == 1)
    {
      if (FALSE == usb0_ctx->is_enumerated)
      {
        LOG_DBG("VBUS high: %u", usb0_ctx->vbus_high);
        if(usb0_ctx->dev_cfg.usb_comp_num_ifc == usb_fn_al()->usb_client_cnt())
        {
          usb_fn_al()->usb_al_hlos_bulk_init((usb_max_speed_required_t)0x0);
        }
      }
    }
    USB_OS_SAFE_LEAVE();
  } 

  if (usb0_ctx->fd_ctx && (client_sig & USB_ENUM_DONE_FLAG))
  {
    uint8 idx=0;
    USB_OS_SAFE_ENTER();
    LOG_DBG("Enumeration done signal");
     
    for (idx=0; idx < usb0_ctx->dev_cfg.usb_comp_num_ifc; idx++)
    {
      if ((NULL != usb0_ctx->client_ctx[idx]) &&
          (NULL != usb0_ctx->client_ctx[idx]->app_event_cb_func))
      {
        usb0_ctx->client_ctx[idx]->app_event_cb_func(USB_EVENT_ENABLED, NULL);
      }
    }
    USB_OS_SAFE_LEAVE();
  }

  if (usb0_ctx->fd_ctx && (client_sig & USB_LOG_TIMER_EXP_FLAG))
  {
    USB_OS_SAFE_ENTER();
    //usb_log_read_send_ulog();
    USB_OS_SAFE_LEAVE();
  }
}

static void usb_thread_entry(void *p1, void *p2, void *p3)
{
  uint32 events;

  LOG_INF("USB thread started");

  usb_fn_util()->usb_os_spinlock_init();

  while (1)
  {
    events = k_event_wait(&usb_events, 
      USB_EVENT_QUEUE_FLAG | 
      USB_PWR_EVENT_QUEUE_FLAG | 
      USB_VBUS_EVENT_FLAG | 
      USB_ENUM_DONE_FLAG |
      USB_LOG_TIMER_EXP_FLAG,
      false, K_FOREVER);

    k_event_clear(&usb_events, events);

    usb_api()->usb_handle_signal(events);
  }
}

void usb_thread_init(void* sig_ptr)
{
  // Initialize event object
  k_event_init(&usb_events);

  usb_fn_util()->usb_os_spinlock_init();

  usb_fn_mem_util()->usb_mem_init();
  usb_fn_al()->usb_ctx_init();
  //usb_log_buffer_init(&usb0_ctx->log_ptr);
}

int usb_zephyr_init(void)
{
  /* Single-threaded: do not create a dedicated USB thread */
  k_event_init(&usb_events);
  usb_api()->usb_thread_init(&usb_events);
  return TRUE;
}

boolean usb_create_thread(void)
{
  /* Single-threaded: do not create a dedicated USB thread */
  k_event_init(&usb_events);
  usb_api()->usb_thread_init(&usb_events);
  return TRUE;
}

// Function table definitions
usb_fn_tbl_al_t fn_tbl_al = 
{
  //usb_get_str_dsc_from_acdb_str,
  //usb_set_comp_profile,
  //usb_set_audio_rev,
  //usb_set_audio_profile,
  usb_client_get_config,
  usb_client_notification,
  usb_ctrl_out_cb,
  usb_ctrl_in_cb,
  usb_register_ctrl_client,
  usb_al_hlos_isr_vbus_event,
  usb_al_hlos_isr_pwr_event,
  usb_al_hlos_log_timer_cb,
  usb_al_hlos_enum_complete,
  usb_al_hlos_disconnect_handler,
  usb_al_disconnect_cb,
  usb_al_notify_suspend,
  usb_ctx_init,
  usb_ctx_free,
  usb_tx_complete,
  usb_rx_complete,
  usb_handle_reset,
  usb_al_hlos_bulk_init,
  usb_client_cnt,
  usb_deregister_client,
  usb_register_client,
  usb_copy_client_data,
  usb_send_tx,
  usb_send_hid_report,
  usb_send_rx,
  usb_check_enum,
  usb_get_max_packet_size,
  usb_remove_thread,
  usb_alloc_register_client_ctx,
  usb_shutdown,
  usb_return_buffer,
  usb_internal_close,
  usb_thread_entry,
  usb_create_thread,
  NULL, //usb_log_read_send_ulog,
};
