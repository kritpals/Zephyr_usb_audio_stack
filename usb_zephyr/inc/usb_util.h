#ifndef USB_UTIL_H
#define USB_UTIL_H

#include "assert.h"
#include <zephyr/kernel.h>
#include "usb_mem_util.h"
#include "usb_svc_data.h"
//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

#define usblock_t  uint32
  
#define usblock_init(x)
#define usblock_uninit(x)
#define usblock_lock(x)
#define usblock_unlock(x)

#define USB_ASSERT_W_LOG(msg) \
  USB_ULOG(DBG_E_QLOG, msg); \
  USB_ASSERT(0)

void usb_error_fatal(void);
void usb_error_halt(uint32 log_enum);

#define USB_ASSERT( condition ) \
  if( !(condition) ) \
    usb_error_fatal()

// This is not assert, code may continue to run after USB_ERR_HALT
#define USB_ERR_HALT(condition) \
  if( !(condition) ) \
    usb_error_halt(0)

#define USB_ERR_HALT_LOG(condition, enum) \
  if( !(condition) ) \
    usb_error_halt(enum)

#define USB_ERR_FATAL( condition, p1, p2, p3 )

// Finds last node in a linked list and assigns ptr as next.
// In case linked list is empty populate head.
#define INSERT_TAIL(type, head, ptr) \
{ \
  if(head) \
  { \
    struct type* itr; \
    for( itr = head; (itr->next); itr = itr->next); \
    itr->next = ptr;  \
  } \
  else  \
  { \
    head = ptr;  \
  } \
}

#define CIRINC(val, max_val) (val) = ((val+1)%(max_val))

//----------------------------------------------------------------------------
// Type declarations
//----------------------------------------------------------------------------

typedef struct usb_fn_tbl_util
{
  void (*usb_delay_us)(uint32 usecs);
  void (*usb_delay_ms)(uint32 msecs);
  void (*usb_enable_clocks)(boolean* status_flag_ptr, boolean enable);
  void (*usb_enable_clocks_in_isr)(void);
  void (*usb_get_acdb_params)(usb_drv_params_t* params);
  void (*usb_error_fatal)(void);
  void (*usb_set_halt_on_err)(boolean val);
  void (*usb_error_halt)(uint32 log_enum);
  void (*usb_os_spinlock_init)(void);
  void (*usb_os_spinlock_lock)(void);
  void (*usb_os_spinlock_unlock)(void);
  void (*usb_os_safe_enter_d)(void);
  void (*usb_os_safe_leave_d)(void);
} usb_fn_tbl_util_t;


extern usb_fn_tbl_util_t fn_tbl_util;
#define usb_fn_util()  (&fn_tbl_util)

// Macro for adding debug capabilities to os_safe_enter.

#define USB_OS_SAFE_ENTER() \
  usb_fn_util()->usb_os_safe_enter_d()
  //USB_ULOG(SNPS_QLOG, "enter_ctrical");

/** Macro for adding debug capabilities to os_safe_leave.
*/
#define USB_OS_SAFE_LEAVE() \
  usb_fn_util()->usb_os_safe_leave_d()
  //USB_ULOG(SNPS_QLOG, "leave_ctrical");
  
#endif /* USB_UTIL_H */
