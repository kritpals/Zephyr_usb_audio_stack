#ifndef USB_MEM_UTIL_H
#define USB_MEM_UTIL_H

#include "comdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Memory utility function table */
typedef struct usb_fn_tbl_mem_util
{
  void (*usb_mem_barrier)(void);
  void* (*usb_mem_attr_uncached)(void* ptr);
  void* (*usb_mem_attr_writethrough)(void* ptr);
  void* (*usb_mem_attr_uncached_inv)(void* ptr, uint32 size);
  void (*usb_mem_init)(void);
  void (*usb_mem_deinit)(void);
  void* (*usb_malloc)(uint32 size);
  void* (*usb_malloc_uncached)(uint32 size);
  void (*usb_free)(void** addr);
  uint32 (*usb_print_meminfo)(void);
} usb_fn_tbl_mem_util_t;

extern usb_fn_tbl_mem_util_t fn_tbl_mem_util;

/* Accessor macro used across the codebase */
#define usb_fn_mem_util() (&fn_tbl_mem_util)

#ifdef __cplusplus
}
#endif

#endif /* USB_MEM_UTIL_H */
