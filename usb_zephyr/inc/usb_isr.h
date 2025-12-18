#ifndef USB_ISR_H
#define USB_ISR_H

#include "comdef.h"
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "usb_dci.h"

/* IRQ numbers - should come from device tree */
#define USB_CTRL_EE1_IRQ          5
#define USB_CTRL_POWER_EVENT_IRQ  10
#define USB_CTRL_HSPHY_IRQ        11

/* Event flags for polling */
#define USB_EVENT_FLAG_NONE       0x00
#define USB_EVENT_FLAG_DEVICE     0x01
#define USB_EVENT_FLAG_POWER      0x02
#define USB_EVENT_FLAG_VBUS       0x04
#define USB_EVENT_FLAG_PHY        0x08

#define USB_EVENT_AGGR_CNT        (8)
#define USB_PWR_DSR_QUEUE_SIZE    (8)

#define USB_PHY_DPSE_IRQ          (13)  // EDGE trigger, edge fall  //Enable after IN_L2, handle VOTE_PWR_USB
#define USB_SOF_IRQ               (14)  // Not use
#define USB_RECOVERED_SOF_IRQ     (15)  // Not use 


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
  
  /* Zephyr IRQ context */
  const struct device *usb_dev;
  struct gpio_callback vbus_cb_data;
  struct gpio_dt_spec vbus_gpio;
  uint32 irq_ee1;
  uint32 irq_pwr;
  uint32 irq_phy;
  
  /* Polling flags (volatile for ISR access) */
  volatile uint32 pending_events;
  volatile uint32 vbus_state;
} usb_isr_ctx_t;

/* Polling function to be called from main loop */
void usb_poll_events(usb_isr_ctx_t* isr_ctx);

/* ... rest of existing declarations ... */

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
  void (*usb_isr_poll_events)(usb_isr_ctx_t* isr_ctx);
} usb_fn_tbl_isr_t;

extern usb_fn_tbl_isr_t fn_tbl_isr;

#define usb_get_fn_isr()  (&fn_tbl_isr)
#define usb_fn_isr()      (&fn_tbl_isr) 

#endif /*USB_ISR_H*/
