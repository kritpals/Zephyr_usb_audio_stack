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


void usb_log_0(uint32 enm)
{
  TraceErr(BattMngr_INIT, "Error: ");
}

void usb_log_1(uint32 enm, uint32 p1)
{
  TraceErr(BattMngr_INIT, "Error: %u", p1);
}

void usb_log_2(uint32 enm, uint32 p1, uint32 p2)
{
  TraceErr(BattMngr_INIT, "Error: %u , %u", p1, p2);
}

void usb_log_3(uint32 enm, uint32 p1, uint32 p2, uint32 p3)
{
  TraceErr(BattMngr_INIT, "Error: %u , %u, %u", p1, p2, p3);
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
