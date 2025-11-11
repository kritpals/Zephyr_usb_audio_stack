#ifndef USB_ISR_H
#define USB_ISR_H

#include "comdef.h"     // common defines and types
#include <zephyr/kernel.h>
#include "usb_dci.h"

typedef struct
{
  usb_event_t* dsr_save_event;
  uint32 dsr_event_read_idx;
  uint32 dsr_event_write_idx;
  uint32 size;
  uint32 cnt;
} usb_event_queue_t;


typedef struct usb_isr_ctx
{
  usb_event_queue_t ee_dsr_queue;
  usb_event_queue_t pwr_dsr_queue;
  void* dci_ctx;
  struct k_event* usb_events;
  void (*pwr_handle)(uint32 event_id);
  void (*vbus_handle)(uint32 vbus_high);
} usb_isr_ctx_t;

typedef struct usb_fn_tbl_isr
{
  void (*usb_event_queue_init)(usb_event_queue_t* queue_ctx, uint32 size);
  void (*usb_event_queue_uninit)(usb_event_queue_t* queue_ctx);
  boolean (*usb_event_enqueue)(usb_event_queue_t* queue_ctx, uint32 new_data);
  boolean (*usb_event_dequeue)(usb_event_queue_t* queue_ctx, uint32* old_data);
  uint32 (*usb_event_queue_cnt)(usb_event_queue_t* queue_ctx);
  void (*usb_isr_ee_enable)(boolean enable);
  void (*usb_isr_usbphy_enable)(boolean enable);
  void (*usb_isr_pwr_enable)(boolean enable);
  void (*usb_isr_enable)(usb_isr_ctx_t* isr_ctx, boolean enable);
  void (*usb_isr_ee1_handle)(void* ctx);
  void (*usb_isr_pwr_handle)(void* ctx);
  void (*usb_isr_hsphy_handle)(void* ctx);
  void (*usb_isr_dpse_handle)(void* ctx);
  boolean (*usb_isr_lpm_init)(boolean is_l1_enable);
  boolean (*usb_isr_ee_init)(usb_isr_ctx_t* isr_ctx);
  boolean (*usb_isr_pwr_init)(usb_isr_ctx_t* isr_ctx);
  uint32 (*usb_isr_ee_uninit)(usb_isr_ctx_t* isr_ctx);
  uint32 (*usb_isr_pwr_uninit)(usb_isr_ctx_t* isr_ctx);
   uint32 (*usb_isr_init)(usb_isr_ctx_t* isr_ctx);
  uint32 (*usb_isr_uninit)(usb_isr_ctx_t* isr_ctx);
  boolean (*usb_isr_enqueue_ee_event)(usb_isr_ctx_t* isr_ctx);
  uint32 (*usb_dsr_handle_ee_event)(usb_isr_ctx_t* isr_ctx);
  uint32 (*usb_dsr_handle_pwr_event)(usb_isr_ctx_t* isr_ctx);
} usb_fn_tbl_isr_t;

extern usb_fn_tbl_isr_t fn_tbl_isr;

#define usb_get_fn_isr()  (&fn_tbl_isr)
#define usb_fn_isr()      (&fn_tbl_isr) 

#endif /*USB_ISR_H*/
