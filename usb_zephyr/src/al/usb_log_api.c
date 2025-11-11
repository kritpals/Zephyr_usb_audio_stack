/*==================================================================*/
/**
  @file usb_log_api.c

  USB log client implementation

  @file         usb_log_api.c
 
  @brief      Implementation of micro-log over USB COM port interface.
 
  @details    A micrologging mechanism is provided to send debug logs over USB. 
 
               Copyright (c) 2017 Qualcomm Technologies Inc.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*/
/*==================================================================*/

/*------------------------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------------------------*/
#include "comdef.h"
#include <stringl/stringl.h>
//#include "timetick.h" TODO: Replace with zephyr.
#include "qurt.h"
#include "timer.h"
//#include "micro_ULog.h"
//#include "log_handler.h"

#include "usb_api.h"
#include "usb_util.h"
//#include "usb_al_hlos.h"
#include "log.h"

/*------------------------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------------------------*/

#define USB_LOG_RX_BUFF_SIZE  (512)
#define USB_LOG_TX_BUFF_SIZE  (512)
#define USB_LOG_TIMER_MS (10)

/*------------------------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------------------------*/

typedef enum
{
  USB_LOG_CMD__DISABLE  = 0,
  USB_LOG_CMD__ENABLE   = 1,
} usb_log_cmd_t;

typedef struct usb_log_ctx
{
  client_ctx_t* usb_ctx;
  uint8* rx_buff;
  uint8* tx_buff;
  uint16 tx_bytes_acc;    // Bytes accumulated on TX.

  timer_type timer;

  uint8 is_logging_enabled;
  boolean tx_in_progress;

  // Debug variables.
  uint32 bytes_queued;
  uint32 bytes_complete;
} usb_log_ctx_t;

/*------------------------------------------------------------------------------------------
 * Function Declarations and Definitions
 * ----------------------------------------------------------------------------------------*/
usb_log_ctx_t* log_ctx = NULL;

// Forward declaration
void usb_al_hlos_log_timer_cb(uint32 event_id);

void usb_log_read_send_ulog(void) 
{
  boolean overrun = FALSE;
  unsigned long int num_bytes_read = 0;
  //micro_ULogResult ulog_result = MICRO_ULOG_SUCCESS;
  unsigned char *tx_buff_ptr;

  if((NULL == log_ctx) || (FALSE == log_ctx->is_logging_enabled))
  {
    return;
  }

  // Accumulate data read from ulog API.
  if(log_ctx->tx_bytes_acc < USB_LOG_TX_BUFF_SIZE) 
  {
    tx_buff_ptr = log_ctx->tx_buff + log_ctx->tx_bytes_acc;
    //ulog_result  = micro_ULog_ReadDataItem(ulog_h, (USB_LOG_TX_BUFF_SIZE - log_ctx->tx_bytes_acc),
    //  tx_buff_ptr, &num_bytes_read, &overrun);

   // if(ulog_result == MICRO_ULOG_SUCCESS)
   // {
   //   log_ctx->tx_bytes_acc += num_bytes_read;
   // }
  }

  // If ulog has more data but buffer is insufficient or TX buffer is full then send data out.
  /*if((FALSE == log_ctx->tx_in_progress) && 
    (ulog_result == MICRO_ULOG_ERR_INSUFFICIENT_BUFFER || log_ctx->tx_bytes_acc == USB_LOG_TX_BUFF_SIZE))
  {
    if(USB_SUCCESS == usb_api()->usb_write(log_ctx->usb_ctx, log_ctx->tx_buff, log_ctx->tx_bytes_acc, log_ctx))
    {
      log_ctx->bytes_queued += log_ctx->tx_bytes_acc;
      log_ctx->tx_bytes_acc = 0;
      log_ctx->tx_in_progress = TRUE;
    }
  }
  else
  {
    // Timer is only set if not enough ulog data bytes are accumulated.
    timer_set_64(&log_ctx->timer, USB_LOG_TIMER_MS,  0, T_MSEC);
  }*/
}

void usb_log_process_cmd(uint8* buf_ptr, uint32 size)
{ 
  uint8 cmd;
  USB_ASSERT(log_ctx);

  cmd = buf_ptr[0];
  switch(cmd)
  {
    case USB_LOG_CMD__DISABLE:
    {      
      log_ctx->is_logging_enabled = FALSE;
      timer_stop(&log_ctx->timer, T_MSEC, NULL);
      //log_handler_set_transport_mode(LOG_HANDLER_TRANSPORT_MODE__UART);
    }
    break;
  
    case USB_LOG_CMD__ENABLE:
    { 
      //log_handler_set_transport_mode(LOG_HANDLER_TRANSPORT_MODE__USB);
      log_ctx->is_logging_enabled = TRUE;
      timer_set_64(&log_ctx->timer, USB_LOG_TIMER_MS,  0, T_MSEC);
    }
    break;

  }
}

void usb_log_event_cb(uint32 event, void* data)
{
  USB_ASSERT(log_ctx);
  switch(event)
  {
    case USB_EVENT_ENABLED:
    {
      usb_api()->usb_read(log_ctx->usb_ctx, log_ctx->rx_buff, USB_LOG_RX_BUFF_SIZE, log_ctx);
    }
    break;
  }
}

void usb_log_tx_cb(uint8* buf_ptr, uint32 size, uint32 status, void* cb_data)
{
  USB_ASSERT(log_ctx);
  log_ctx->tx_in_progress = FALSE;
  log_ctx->bytes_complete += size;
  memset(log_ctx->tx_buff, 0, USB_LOG_TX_BUFF_SIZE);
  usb_log_read_send_ulog();
}

void usb_log_rx_cb(uint8* buf_ptr, uint32 size, uint32 status, void* cb_data)
{
  USB_ASSERT(log_ctx);
  if(buf_ptr && size)
  {
    usb_log_process_cmd(buf_ptr, size);
  }
  usb_api()->usb_read(log_ctx->usb_ctx, log_ctx->rx_buff, USB_LOG_RX_BUFF_SIZE, log_ctx);
}

void usb_log_close(void)
{
  if(log_ctx)
  {
    usb_api()->usb_close(log_ctx->usb_ctx);
    timer_undef(&log_ctx->timer);
    usb_fn_mem_util()->usb_free((void**)&log_ctx->tx_buff);
    usb_fn_mem_util()->usb_free((void**)&log_ctx->rx_buff);
    usb_fn_mem_util()->usb_free((void**)&log_ctx);
  }
}

void usb_log_open(void)
{
  USB_ASSERT(log_ctx == NULL);
  USB_ASSERT(log_ctx = (usb_log_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_log_ctx_t)));
  log_ctx->is_logging_enabled  = FALSE;
  log_ctx->tx_in_progress      = FALSE;

  usb_api()->usb_open(&log_ctx->usb_ctx, USB_IFC_ID_BULK, NULL, &usb_log_event_cb, usb_log_rx_cb, usb_log_tx_cb, 1, 1);

  USB_ASSERT(log_ctx->rx_buff = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_LOG_RX_BUFF_SIZE));
  USB_ASSERT(log_ctx->tx_buff = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_LOG_TX_BUFF_SIZE));

  timer_def_osal(&log_ctx->timer, NULL, TIMER_FUNC1_CB_TYPE, usb_al_hlos_log_timer_cb, NULL);
}
