/*==================================================================*/
/**
  @file usb_mem_util_zephyr.c

  USB memory utility implementation for Zephyr OS.

  @brief      Implements USB memory management APIs for Zephyr.
 
  @details    Zephyr OS port of USB memory management.
 
               Copyright (c) 2025 Ported to Zephyr OS.
*/
/*==================================================================*/

/*------------------------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------------------------*/
#include <zephyr/kernel.h>
#include <zephyr/cache.h>
#include <zephyr/logging/log.h>
#include <string.h>

#include "usb_log.h"
#include "usb_util.h"
 
LOG_MODULE_REGISTER(usb_mem, LOG_LEVEL_DBG);

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/
#define USB_HLOS_MEM_HANDLE_MAX     (128)
#define USB_MEM_CACHE_ALIGN_BYTES   (CONFIG_DCACHE_LINE_SIZE)
#define USB_MEM_ATTR_CACHED         (0)
#define USB_MEM_ATTR_UNCACHED       (1)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

struct usb_mem_handle
{
  uint8* vaddr;
  uint8  pad_offset;
  uint8  seq_num;
  uint16 size;
};

typedef union 
{
  uint64 value;
  struct usb_mem_handle handle;
}
usb_mem_handle_t;

typedef struct usb_mem_ctx
{
  uint16 alloc_index;
  uint16 seq_num;           // sequence number counter
  uint16 alloc_size;        // size of currently allocated memory by USB driver.
  uint16 h_arr_size;        // size of the h_arr.
  usb_mem_handle_t* h_arr;  // array of handles to memory 
}
usb_mem_ctx_t;

static usb_mem_ctx_t usb_mem;

/*----------------------------------------------------------------------------
 *  Function definitions
 * -------------------------------------------------------------------------*/

void usb_mem_barrier(void)
{
  //TODO: barrier_dmem_fence_full();
}

void* usb_mem_attr_uncached(void* ptr)
{
  // In Zephyr, we use cache operations instead of address manipulation
  return ptr;
}

void* usb_mem_attr_writethrough(void* ptr)
{
  // In Zephyr, cache attributes are managed differently
  return ptr;
}

void* usb_mem_attr_uncached_inv(void* ptr, uint32 size)
{
  sys_cache_data_invd_range(ptr, size);
  return ptr;
}

void usb_mem_init(void)
{
  uint32 i;
  usb_mem.alloc_index = 0;
  usb_mem.alloc_size  = 0;
  usb_mem.seq_num     = 0;
  usb_mem.h_arr_size  = USB_HLOS_MEM_HANDLE_MAX;
  usb_mem.h_arr       = (usb_mem_handle_t*) k_malloc(usb_mem.h_arr_size * sizeof(usb_mem_handle_t));

  USB_ASSERT(usb_mem.h_arr);
  for(i=0; i < usb_mem.h_arr_size; i++)
  {
    usb_mem.h_arr[i].value = 0;
  }
  
  LOG_INF("USB memory initialized");
}

void usb_mem_deinit(void)
{
  uint32 i;
  usb_mem.alloc_index = 0;
  usb_mem.alloc_size  = 0;
  usb_mem.seq_num     = 0;
  for(i=0; i < usb_mem.h_arr_size; i++)
  {
    if(usb_mem.h_arr[i].handle.vaddr)
    {
      k_free(usb_mem.h_arr[i].handle.vaddr);
    }
    usb_mem.h_arr[i].value = 0;
  }
  usb_mem.h_arr_size  = 0;
  k_free(usb_mem.h_arr);
  
  LOG_INF("USB memory deinitialized");
}

void* usb_malloc_internal(uint32 size, uint8 mem_attr)
{
  uint32 num_try = 0;
  uint8  mem_offset;
  void*  mem_addr;
  uint16 mem_size;

  usb_fn_util()->usb_os_spinlock_lock();

  while((NULL != usb_mem.h_arr[usb_mem.alloc_index].handle.vaddr) && (num_try < usb_mem.h_arr_size))
  {
    CIRINC(usb_mem.alloc_index, usb_mem.h_arr_size);
    num_try++;
  }

  if (NULL != usb_mem.h_arr[usb_mem.alloc_index].handle.vaddr)
  {
    LOG_ERR("Malloc failed, size: %u", size);
    usb_fn_util()->usb_os_spinlock_unlock();
    USB_ASSERT(FALSE);
    return NULL;
  }

  mem_offset = 0;
  mem_size = (mem_attr == USB_MEM_ATTR_UNCACHED) ? size + USB_MEM_CACHE_ALIGN_BYTES : size;
  mem_addr = (uint8*) k_malloc(mem_size);
  USB_ASSERT(mem_addr);
  memset(mem_addr, 0, mem_size);

  if(mem_attr == USB_MEM_ATTR_UNCACHED)
  {
#if USB_MEM_CACHE_ALIGN_BYTES > 0
    mem_offset = USB_MEM_CACHE_ALIGN_BYTES - (((uint32) mem_addr) % USB_MEM_CACHE_ALIGN_BYTES);
    sys_cache_data_flush_and_invd_range(mem_addr, mem_size);
#else
    mem_offset = 0;
#endif
  }

  usb_mem.h_arr[usb_mem.alloc_index].handle.vaddr      = mem_addr;
  usb_mem.h_arr[usb_mem.alloc_index].handle.pad_offset = mem_offset;
  usb_mem.h_arr[usb_mem.alloc_index].handle.seq_num    = usb_mem.seq_num++;
  usb_mem.h_arr[usb_mem.alloc_index].handle.size       = mem_size;
  usb_mem.alloc_size += mem_size;

  LOG_DBG("Malloc: addr 0x%X, idx %u, size %u", (uint32) mem_addr, usb_mem.alloc_index, (uint32) size);
  CIRINC(usb_mem.alloc_index, usb_mem.h_arr_size);

  usb_fn_util()->usb_os_spinlock_unlock();
  return (mem_addr + mem_offset);
}

void* usb_malloc(uint32 size)
{
  return usb_malloc_internal(size, USB_MEM_ATTR_CACHED);
}

void* usb_malloc_uncached(uint32 size)
{
  return usb_malloc_internal(size, USB_MEM_ATTR_UNCACHED);
}

void usb_free(void** addr)
{
  uint32 i;
  usb_fn_util()->usb_os_spinlock_lock();

  if((NULL == addr) || (NULL == *addr))
  {
    USB_ASSERT(FALSE);
    return;
  }

  for(i=0; i < usb_mem.h_arr_size; i++)
  {
    if((*addr) == (usb_mem.h_arr[i].handle.vaddr + usb_mem.h_arr[i].handle.pad_offset))
    {
      k_free(usb_mem.h_arr[i].handle.vaddr);
      usb_mem.alloc_size -= usb_mem.h_arr[i].handle.size;
      (*addr) = NULL;
      usb_mem.h_arr[i].value = 0;
      usb_fn_util()->usb_os_spinlock_unlock();
      return;
    }
  }

  LOG_ERR("Free failed, addr: 0x%X", (uint32)(*addr));
  USB_ASSERT(FALSE);
  usb_fn_util()->usb_os_spinlock_unlock();
}

uint32 usb_print_meminfo(void)
{
  usb_fn_util()->usb_os_spinlock_lock();
  LOG_INF("USB memory allocated: %u bytes", usb_mem.alloc_size);
  usb_fn_util()->usb_os_spinlock_unlock();
  return usb_mem.alloc_size;
}


//----------------------------------------------------------------------------
// Function table definition for memory utility layer
//----------------------------------------------------------------------------

usb_fn_tbl_mem_util_t fn_tbl_mem_util = 
{
  usb_mem_barrier,
  usb_mem_attr_uncached,
  usb_mem_attr_writethrough,
  usb_mem_attr_uncached_inv,
  usb_mem_init,
  usb_mem_deinit,
  usb_malloc,
  usb_malloc_uncached,
  usb_free,
  usb_print_meminfo,
};
