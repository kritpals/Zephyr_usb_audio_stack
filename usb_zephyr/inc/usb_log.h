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

#include "stdlib.h"
#include "comdef.h" 
#include "framework/log/battman_log.h"
#include "framework/log/battmngr_debug_str.h"
//#include "framework/osservice/battman_osa.h"
#include "zephyr/sys/util.h"
#include "log_enum_usb.h"

#define USB_ENABLE_ERR_LOG 1
#define USB_ENABLE_DBG_LOG 1

typedef struct usb_fn_tbl_log
{
  void (*usb_log_0)(uint32 enm);
  void (*usb_log_1)(uint32 enm, uint32 p1);
  void (*usb_log_2)(uint32 enm, uint32 p1, uint32 p2);
  void (*usb_log_3)(uint32 enm, uint32 p1, uint32 p2, uint32 p3);
} usb_fn_tbl_log_t;

extern usb_fn_tbl_log_t fn_tbl_log;
#define usb_fn_log(ctx)  (&fn_tbl_log)

//Backward compatability with default ULOG implementation.
#define USB_ULOG(log_type, fmt)
#define USB_ULOG_1(log_type, fmt, value1)
#define USB_ULOG_2(log_type, fmt, value1, value2)
#define USB_ULOG_3(log_type, fmt, value1, value2, value3)
#define USB_ULOG_4(log_type, fmt, value1, value2, value3, value4)
#define USB_ULOG_STR(log_type, fmt, str_msg)

#ifdef USB_FEATURE_ULOG

#define usb_log_buffer_init(p)
#define usb_log_buffer_free(p)

#else

#ifdef USB_ENABLE_ERR_LOG

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
