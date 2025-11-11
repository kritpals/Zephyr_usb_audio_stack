/*=======================================================================*//**
 * @file        usb_log.c
 * @author:     shreyasr
 * @date        13-Mar-2012
 *
 * @brief       USB (Qualcomm High-Speed USB) Logging implementation.
 *
 * @details     This file contains the debug log APIs which can be used for
 *              getting log information
 * @note        
 *
 *              Copyright 2017 Qualcomm Technologies, Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/


// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/common/usb_log.c#7 $ 
// $DateTime: 2018/02/12 17:09:34 $ $Author: pwbldsvc $
// 
// when         who        what, where, why
// --------   ---        ----------------------------------------------------------
// 06/13/12   shreyasr   Initial revision
//
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------

#include "usb_log.h"
#include "usb_util.h"
#include <zephyr/kernel.h>

/*----------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* -------------------------------------------------------------------------*/

#define USB_LOG_MASK(sub_log_type)    (1 << (sub_log_type))
#define USB_SUB_LOG(enum_id)          (((enum_id) &  0x0f000000) >> 24)
#define USB_LOG_MASK_ENABLED(enum_id) (0 != (usb_log_mask & USB_LOG_MASK(USB_SUB_LOG(enum_id))))

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

typedef enum usb_sub_log
{
  USB_SUB_LOG_ERR = 0x0,
  USB_SUB_LOG_GEN = 0x1,
  USB_SUB_LOG_DBG = 0x2,
  USB_SUB_LOG_ENG = 0x3,
  USB_SUB_LOG_MAX
} usb_sub_log_t;

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
 
// Log mask for individual sub_log type. To enable all log put 0xF;
uint16 usb_log_mask = USB_LOG_MASK(USB_SUB_LOG_ERR); 
// | USB_LOG_MASK(USB_LOG_MASK_GEN) | USB_LOG_MASK(USB_LOG_MASK_DBG) | USB_LOG_MASK(USB_LOG_MASK_ENG);

#ifdef USB_FEATURE_ULOG

void usb_log_0(uint32 enm)
{
  if(USB_LOG_MASK_ENABLED(enm))
  {
    MSG_1(enm);
  }
}

void usb_log_1(uint32 enm, uint32 p1)
{
  if(USB_LOG_MASK_ENABLED(enm))
  {
    MSG_2(enm, p1);
  }
}

void usb_log_2(uint32 enm, uint32 p1, uint32 p2)
{
  if(USB_LOG_MASK_ENABLED(enm))
  {
    MSG_3(enm, p1, p2);
  }
}

void usb_log_3(uint32 enm, uint32 p1, uint32 p2, uint32 p3)
{
  if(USB_LOG_MASK_ENABLED(enm))
  {
    MSG_4(enm, p1, p2, p3);
  }  
}

#else 

#ifdef USB_ENABLE_ERR_LOG
static usb_log_type* usb_log_buffer = NULL;

// ===========================================================================
/**
 * @function    usb_log_buffer_init
 * 
 * @brief   This function use the allocate usb_log_buffer
 *
 * @details This function will stored the allocate pointer to global variable
 *          So all the function can call the log without access to the pointer
 *          The last thread to call this function will take over the log
 *          buffer. This allow SBL,deviceprogrammer,MISSION_Mode share same api
 *          This function overwrite the global pointer, which can cause memory
 *          leak, if previous thread does not clean the memory properly.
 * 
 * @param   
 *          (INPUT/OUTPUT) usb_log_type** log_ptr: pointer to new_log_buffer
 * 
 * @return  if allocate the buffer properly.
 * 
 */
// ===========================================================================
boolean usb_log_buffer_init(usb_log_type** log_ptr)
{
  USB_ASSERT(log_ptr);

  if (*log_ptr)
  {
    usb_log_buffer = *log_ptr;
    return TRUE;
  }

  *log_ptr = usb_log_buffer;
  USB_ASSERT(usb_log_buffer = (usb_log_type*)usb_fn_mem_util()->usb_malloc(sizeof(usb_log_type)));

  usb_log_buffer->seq_num                   = 1;
  usb_log_buffer->error_buffer_index        = 0;
  usb_log_buffer->usb_error_log_buf_size    = USB_HLOS_ERROR_LOG_SIZE;
  usb_log_buffer->log_mode                  = USB_LOG_HLOS_MODE_ERR;
  USB_ASSERT(usb_log_buffer->error_log = (usb_error_log_entry*)
    usb_fn_mem_util()->usb_malloc(sizeof(usb_error_log_entry) * (usb_log_buffer->usb_error_log_buf_size)));
  usb_log_buffer->error_log->idx =0;


  #ifdef USB_ENABLE_DBG_LOG
  usb_log_buffer->generic_buffer_index      = 0;
  usb_log_buffer->usb_generic_log_buf_size  = USB_HLOS_GENERIC_LOG_SIZE;
  usb_log_buffer->log_mode                  = USB_LOG_HLOS_MODE_ALL;
  USB_ASSERT(usb_log_buffer->generic_log = (usb_generic_log_entry*)
    usb_fn_mem_util()->usb_malloc(sizeof(usb_generic_log_entry) * (usb_log_buffer->usb_generic_log_buf_size)));
  usb_log_buffer->generic_log->idx =0;
  #endif

  #ifdef USB_ENABLE_GEN_LOG
  usb_log_buffer->bus_buffer_index          = 0;
  usb_log_buffer->usb_bus_log_buf_size      = USB_HLOS_BUS_LOG_SIZE;
  usb_log_buffer->log_mode                  = USB_LOG_HLOS_MODE_ALL;
  USB_ASSERT(usb_log_buffer->bus_log = (usb_bus_log_entry*)
    usb_fn_mem_util()->usb_malloc(sizeof(usb_bus_log_entry) * (usb_log_buffer->usb_bus_log_buf_size)));
  usb_log_buffer->bus_log->idx =0;
  
  #endif

  #ifdef USB_ENABLE_ENG_LOG
  usb_log_buffer->eng_buffer_index          = 0;
  usb_log_buffer->usb_eng_log_buf_size      = USB_HLOS_BUS_LOG_SIZE;
  usb_log_buffer->log_mode                  = USB_LOG_HLOS_MODE_ALL;
  USB_ASSERT(usb_log_buffer->eng_log = (usb_eng_log_entry*)
    usb_fn_mem_util()->usb_malloc(sizeof(usb_bus_log_entry) * (usb_log_buffer->usb_eng_log_buf_size)));
  usb_log_buffer->eng_log->idx =0;
  #endif
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_log_buffer_free
 * 
 * @brief   This function free all the buffer and clean the global pointer
 *
 * @details the api require to pass the free_memory api
 * 
 * @param   
 *          (INPUT) usb_log_type** log_ptr: log ptr to buffer
 * 
 * @return  if free memory properly
 * 
 */
// ===========================================================================
boolean usb_log_buffer_free(usb_log_type** log_ptr)
{
  USB_ASSERT(log_ptr);
  if (NULL == *log_ptr)
  {
    usb_log_buffer = NULL;
    return FALSE;
  }
  if ((*log_ptr != usb_log_buffer)) //If the log does not match global variable
  {
    //DONT crash, in case the global variable is corroupt
    usb_log_buffer = *log_ptr;
  }
  if (usb_log_buffer->error_log)
  {
    usb_fn_mem_util()->usb_free((void**)&(*log_ptr)->error_log);
    (*log_ptr)->error_log = NULL;
  }
  #ifdef USB_ENABLE_DBG_LOG
  if ((*log_ptr)->generic_log)
  {
    usb_fn_mem_util()->usb_free((void**)&(*log_ptr)->generic_log);
    (*log_ptr)->generic_log = NULL;
  }
  #endif
  #ifdef USB_ENABLE_GEN_LOG
  if ((*log_ptr)->bus_log)
  {
    usb_fn_mem_util()->usb_free((void**)&(*log_ptr)->bus_log);
    (*log_ptr)->bus_log = NULL;
  }
  #endif
  #ifdef USB_ENABLE_ENG_LOG
  if ((*log_ptr)->eng_log)
  {
    usb_fn_mem_util()->usb_free((void**)&(*log_ptr)->eng_log);
    (*log_ptr)->eng_log = NULL;
  }
  #endif
  usb_fn_mem_util()->usb_free((void**)log_ptr);
  usb_log_buffer = NULL;
  *log_ptr = NULL;
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_log
 * 
 * @brief   print the log in generic log (if it exist)
 *
 * @details This api use the global log buffer and print to generic_log.
 *          if ulog is enable it will print to USB_ULOG.
 *          This take 1 uint32 varible
 * 
 * @param   
 *          (INPUT) usb_dbg_log_t id_0: enum for log_id
 *          (INPUT) uint8 offset: offset to the enum_log_id
 *          (INPUT) uint32 param: variable to print
 * 
 * @return  None
 * 
 */
// ===========================================================================
void usb_log(usb_dbg_log_t id_0, uint8 offset, uint32 param)
{
#ifdef USB_ENABLE_DBG_LOG
if ((NULL == usb_log_buffer) || (NULL == usb_log_buffer->generic_log))
  {
    return;
  }

  usb_log_buffer->generic_log[usb_log_buffer->generic_buffer_index].idx =  usb_log_buffer->seq_num;
  usb_log_buffer->seq_num = (usb_log_buffer->seq_num + 1);
  usb_log_buffer->generic_log[usb_log_buffer->generic_buffer_index].id_0 = (usb_dbg_log_t)(id_0 + offset);
  usb_log_buffer->generic_log[usb_log_buffer->generic_buffer_index].param = param;
  usb_log_buffer->generic_buffer_index = (usb_log_buffer->generic_buffer_index + 1) % (usb_log_buffer->usb_generic_log_buf_size);
#endif
}

// ===========================================================================
/**
 * @function    usb_bus_log
 * 
 * @brief   print the log in bus_log (if it exist)
 *
 * @details This api use the global log buffer and print to bus_log.
 *          if ulog is enable it will print to USB_ULOG.
 *          This take 1 uint32 varible
 * 
 * @param   
 *          (INPUT) usb_eng_log_t id_0: enum for log_id
 *          (INPUT) uint8 offset: offset to the enum_log_id
 *          (INPUT) uint32 param: variable to print
 * 
 * @return  None
 * 
 */
// ===========================================================================
void usb_eng_log(usb_eng_log_t id_0, uint8 offset, uint32 param)
{
#ifdef USB_ENABLE_ENG_LOG
  if ((NULL == usb_log_buffer) || (NULL == usb_log_buffer->eng_log))
  {
    return;
  }
  usb_log_buffer->eng_log[usb_log_buffer->eng_buffer_index].idx =  usb_log_buffer->seq_num;
  usb_log_buffer->seq_num = (usb_log_buffer->seq_num + 1);
  usb_log_buffer->eng_log[usb_log_buffer->eng_buffer_index].id_0 = (usb_eng_log_t)(id_0 + offset);
  usb_log_buffer->eng_log[usb_log_buffer->eng_buffer_index].param = param;
  usb_log_buffer->eng_buffer_index = (usb_log_buffer->eng_buffer_index + 1) % (usb_log_buffer->usb_eng_log_buf_size);
#endif
}

void usb_bus_log(usb_gen_log_t id_0, uint8 offset, uint32 param)
{
#ifdef USB_ENABLE_GEN_LOG
  if ((NULL == usb_log_buffer) || (NULL == usb_log_buffer->bus_log))
  {
    return;
  }
  usb_log_buffer->bus_log[usb_log_buffer->bus_buffer_index].idx =  usb_log_buffer->seq_num;
  usb_log_buffer->seq_num = (usb_log_buffer->seq_num + 1);
  usb_log_buffer->bus_log[usb_log_buffer->bus_buffer_index].id_0 = (usb_gen_log_t)(id_0 + offset);
  usb_log_buffer->bus_log[usb_log_buffer->bus_buffer_index].param = param;
  usb_log_buffer->bus_buffer_index = (usb_log_buffer->bus_buffer_index + 1) % (usb_log_buffer->usb_bus_log_buf_size);
#endif
}

// ===========================================================================
/**
 * @function    usb_error_log
 * 
 * @brief   print the log in error_log (if it exist)
 *
 * @details This api use the global log buffer and print to error_log.
 *          if ulog is enable it will print to USB_ULOG.
 *          This take 1 uint32 varible
 * 
 * @param   
 *          (INPUT) usb_err_log_t id_0: enum for log_id
 *          (INPUT) uint8 offset: offset to the enum_log_id
 *          (INPUT) uint32 param: variable to print
 * 
 * @return  None
 * 
 */
// ===========================================================================
void usb_error_log(usb_err_log_t id_0, uint8 offset, uint32 param)
{
#ifdef USB_ENABLE_ERR_LOG
  if ((NULL == usb_log_buffer) || (NULL == usb_log_buffer->error_log))
  {
    return;
  }
  usb_log_buffer->error_log[usb_log_buffer->error_buffer_index].idx =  usb_log_buffer->seq_num;
  usb_log_buffer->seq_num = (usb_log_buffer->seq_num + 1);
  usb_log_buffer->error_log[usb_log_buffer->error_buffer_index].id_0 = (usb_err_log_t)(id_0 + offset);
  usb_log_buffer->error_log[usb_log_buffer->error_buffer_index].param = param;
  usb_log_buffer->error_buffer_index = (usb_log_buffer->error_buffer_index + 1) % (usb_log_buffer->usb_error_log_buf_size);
#endif
}

void usb_log_b(uint32 enm, uint32 p1)
{
  switch(USB_SUB_LOG(enm))
  {
    case USB_SUB_LOG_ERR:
      usb_error_log(enm, 0, p1);
      break;
      
    case USB_SUB_LOG_GEN:
      usb_bus_log(enm, 0, p1);
      break;
      
    case USB_SUB_LOG_DBG:
      usb_log(enm, 0, p1);
      break;
      
    case USB_SUB_LOG_ENG:
      usb_eng_log(enm, 0, p1);
      break;

    default:
      usb_log(enm, 0, p1);
  }
}

void usb_log_0(uint32 enm)
{
  usb_log_b(enm, 0);
}

void usb_log_1(uint32 enm, uint32 p1)
{
  usb_log_b(enm, p1);
}

void usb_log_2(uint32 enm, uint32 p1, uint32 p2)
{
  usb_log_b(enm, p1);
}

void usb_log_3(uint32 enm, uint32 p1, uint32 p2, uint32 p3)
{
  usb_log_b(enm, p1);
}

#else

void usb_log_0(uint32 enm)
{
}

void usb_log_1(uint32 enm, uint32 p1)
{
}

void usb_log_2(uint32 enm, uint32 p1, uint32 p2)
{
}

void usb_log_3(uint32 enm, uint32 p1, uint32 p2, uint32 p3)
{
}

#endif // ifdef USB_ENABLE_ERR_LOG

#endif // ifdef USB_FEATURE_ULOG

#ifdef USB_FEATURE_ENABLE_MIPS_LOG

#define USB_MIPS_MAX  (120000000)

typedef struct usb_mips_stats
{
  usb_mips_log_t log_type;
  uint32 start;
  uint32 stop;
  uint32 diff;
} usb_mips_stats_t;

typedef struct usb_mips_ctx
{
  uint32 cycle_start;
  usb_mips_stats_t stats[usb_mips__max];
} usb_mips_ctx_t;

usb_mips_ctx_t usb_mips = 
{
  0,
  {
    {usb_mips__usb_al_hlos_handle,    0, 0, 0},
    {usb_mips__usb_intr_isr,          0, 0, 0},
    {usb_mips__usb_intr_dsr,          0, 0, 0},
    {usb_mips__usb_handle_events,     0, 0, 0},
    {usb_mips__usb_read,              0, 0, 0},
    {usb_mips__usb_write,             0, 0, 0},
    {usb_mips__rx_complete,           0, 0, 0},
    {usb_mips__tx_complete,           0, 0, 0},
    {usb_mips__rx_cb,                 0, 0, 0},
    {usb_mips__tx_cb,                 0, 0, 0},
  }
};

void usb_mips_calc_print_stats(uint32 cycle_stop)
{
  USB_LOG_ERR_1(usb_mips_calc_stats_err_usb_read_D_usb_write_D, 
    usb_mips.stats[usb_mips__usb_al_hlos_handle].diff);
}

void usb_mips_start(usb_mips_log_t type)
{
  usb_mips.stats[type].start = k_cycle_get_32();
}

void usb_mips_stop(usb_mips_log_t type)
{
  uint8 i;
  usb_mips.stats[type].stop = k_cycle_get_32();
  usb_mips.stats[type].diff += usb_mips.stats[type].stop - usb_mips.stats[type].start;
  if((usb_mips.stats[type].stop - usb_mips.cycle_start) > USB_MIPS_MAX)
  {
    usb_mips_calc_print_stats(usb_mips.stats[type].stop);
    usb_mips.cycle_start = usb_mips.stats[type].stop;
    for(i=0; i < usb_mips__max; i++)
    {
      usb_mips.stats[i].diff = 0;
    }
  }
}

#endif

//----------------------------------------------------------------------------
// Function table definition
//----------------------------------------------------------------------------

usb_fn_tbl_log_t fn_tbl_log = 
{
  usb_log_0,
  usb_log_1,
  usb_log_2,
  usb_log_3,
};
