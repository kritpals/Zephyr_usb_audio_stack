/*=======================================================================*//**
 * @file        usb_log.h
 * @author:     shreyasr
 * @date        13-Mar-2012
 *
 * @brief       USB (Qualcomm High-Speed USB) Logging implementation.
 *
 * @details     This file contains the implementation of the APIs to be used by
 *              the boot Sahara downloader.
 *
 * @note        
 *
 *              Copyright 2012 QUALCOMM Incorporated.
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
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/common/usb_log.h#1 $ 
// $DateTime: 2018/02/12 17:09:34 $ $Author: pwbldsvc $
// 
// when         who        what, where, why
// --------     ---        ----------------------------------------------------------
// 06/13/12   shreyasr 		Initial revision
//
// ===========================================================================
#ifndef USB_LOG__H_
#define USB_LOG__H_

#include "comdef.h" 
#include "log_enum_usb.h"

/*----------------------------------------------------------------------------
 * Constants definitions
 * -------------------------------------------------------------------------*/

#define USB_HLOS_GENERIC_LOG_SIZE       16 //32  //256
#define USB_HLOS_BUS_LOG_SIZE           16 //48  //256
#define USB_HLOS_ERROR_LOG_SIZE         32 // 32  //64

/*----------------------------------------------------------------------------
 * Type declarations
 * -------------------------------------------------------------------------*/

typedef enum
{
  usb_mips__usb_al_hlos_handle = 0,
  usb_mips__usb_intr_isr,
  usb_mips__usb_intr_dsr,
  usb_mips__usb_handle_events, 
  usb_mips__usb_read,
  usb_mips__usb_write,
  usb_mips__rx_complete,
  usb_mips__tx_complete,
  usb_mips__rx_cb,
  usb_mips__tx_cb,  
  usb_mips__max,
}
usb_mips_log_t;

typedef struct 
{
  uint16 idx;
  usb_dbg_log_t id_0;
  uint32 param;
} usb_generic_log_entry;

typedef struct 
{
  uint16 idx;
  usb_gen_log_t id_0;
  uint32 param;
} usb_bus_log_entry;

typedef struct 
{
  uint16 idx;
  usb_err_log_t id_0;
  uint32 param;
} usb_error_log_entry;

typedef struct 
{
  uint16 idx;
  usb_eng_log_t id_0;
  uint32 param;
} usb_eng_log_entry;


typedef enum
{
  USB_LOG_NULL,
  USB_LOG_SBL_MODE_ERR,  
  USB_LOG_HLOS_MODE_ERR,
  
  USB_LOG_SBL_MODE_ALL,
  USB_LOG_HLOS_MODE_ALL,
  USB_LOG_HLOS_MODE_UALL,
  USB_LOG_USB_LOG_MAX_TYPE
} usb_log_mode;

typedef struct
{
  usb_log_mode log_mode;
  uint32 seq_num; 
#ifdef USB_ENABLE_ERR_LOG
  uint16 error_buffer_index;
  uint32 usb_error_log_buf_size;
  usb_error_log_entry*   error_log;
  #ifdef USB_ENABLE_DBG_LOG
  uint16 generic_buffer_index; 
  uint32 usb_generic_log_buf_size;
  usb_generic_log_entry* generic_log;
  #endif
  #ifdef USB_ENABLE_GEN_LOG
  uint16 bus_buffer_index;
  uint32 usb_bus_log_buf_size;
  usb_bus_log_entry*     bus_log;
  #endif
  #ifdef USB_ENABLE_ENG_LOG
  uint16 eng_buffer_index; 
  uint32 usb_eng_log_buf_size;
  usb_eng_log_entry*     eng_log;
  #endif
#endif
}usb_log_type;

/*----------------------------------------------------------------------------
 * API declarations and definitions
 * -------------------------------------------------------------------------*/

//Backward compatability with default ULOG implementation.
#define USB_ULOG(log_type, fmt)
#define USB_ULOG_1(log_type, fmt, value1)
#define USB_ULOG_2(log_type, fmt, value1, value2)
#define USB_ULOG_3(log_type, fmt, value1, value2, value3)
#define USB_ULOG_4(log_type, fmt, value1, value2, value3, value4)
#define USB_ULOG_STR(log_type, fmt, str_msg)

typedef struct usb_fn_tbl_log
{
  void (*usb_log_0)(uint32 enm);
  void (*usb_log_1)(uint32 enm, uint32 p1);
  void (*usb_log_2)(uint32 enm, uint32 p1, uint32 p2);
  void (*usb_log_3)(uint32 enm, uint32 p1, uint32 p2, uint32 p3);
} usb_fn_tbl_log_t;

extern usb_fn_tbl_log_t fn_tbl_log;
#define usb_fn_log(ctx)  (&fn_tbl_log)

#ifdef USB_FEATURE_ULOG

#define usb_log_buffer_init(p)
#define usb_log_buffer_free(p)

#else

#ifdef USB_ENABLE_ERR_LOG

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
boolean usb_log_buffer_init(usb_log_type** log_ptr);

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
boolean usb_log_buffer_free(usb_log_type** log_ptr);

#else

#define usb_log_buffer_init(p)
#define usb_log_buffer_free(p)

#endif

#endif

#ifdef USB_ENABLE_ERR_LOG
#define USB_LOG_ERR(enm)                usb_fn_log()->usb_log_0(enm)
#define USB_LOG_ERR_1(enm, p1)          usb_fn_log()->usb_log_1(enm, p1)
#define USB_LOG_ERR_2(enm, p1, p2)      usb_fn_log()->usb_log_2(enm, p1, p2)
#define USB_LOG_ERR_3(enm, p1, p2, p3)  usb_fn_log()->usb_log_3(enm, p1, p2, p3)
#else
#define USB_LOG_ERR(enm)
#define USB_LOG_ERR_1(enm, p1)
#define USB_LOG_ERR_2(enm, p1, p2)
#define USB_LOG_ERR_3(enm, p1, p2, p3)
#endif

#ifdef USB_ENABLE_GEN_LOG
#define USB_LOG(enm)                    usb_fn_log()->usb_log_0(enm)
#define USB_LOG_1(enm, p1)              usb_fn_log()->usb_log_1(enm, p1)
#define USB_LOG_2(enm, p1, p2)          usb_fn_log()->usb_log_2(enm, p1, p2)
#define USB_LOG_3(enm, p1, p2, p3)      usb_fn_log()->usb_log_3(enm, p1, p2, p3)
#else
#define USB_LOG(enm)
#define USB_LOG_1(enm, p1)
#define USB_LOG_2(enm, p1, p2)
#define USB_LOG_3(enm, p1, p2, p3)
#endif

#ifdef USB_ENABLE_DBG_LOG
#define USB_LOG_DBG(enm)                usb_fn_log()->usb_log_0( enm)
#define USB_LOG_DBG_1(enm, p1)          usb_fn_log()->usb_log_1( enm, p1)
#define USB_LOG_DBG_2(enm, p1, p2)      usb_fn_log()->usb_log_2( enm, p1, p2)
#define USB_LOG_DBG_3(enm, p1, p2, p3)  usb_fn_log()->usb_log_3( enm, p1, p2, p3)
#else
#define USB_LOG_DBG(enm)          
#define USB_LOG_DBG_1(enm, p1)      
#define USB_LOG_DBG_2(enm, p1, p2)  
#define USB_LOG_DBG_3(enm, p1, p2, p3)
#endif

#ifdef USB_FEATURE_ENABLE_MIPS_LOG
void usb_mips_start(usb_mips_log_t type);
void usb_mips_stop(usb_mips_log_t type);
#else
#define usb_mips_start(type) 
#define usb_mips_stop(type) 
#endif

#endif /*USB_LOG__H_*/
