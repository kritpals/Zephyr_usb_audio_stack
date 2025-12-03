/*=======================================================================*//**
  @file         usb_cdc_acm_example.c

  @brief        Example application for USB CDC-ACM serial communication

  @details      This file demonstrates how to integrate and use the CDC-ACM
                driver for USB serial communication.
 
                Copyright (c)  Qualcomm Technologies, Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
*//*========================================================================*/

#include "usb_api.h"
#include "usb_common.h"
#include "usb_log.h"
#include <string.h>
#include "usb_cdc_acm_fd.h"
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define CDC_RX_BUFFER_SIZE  512
#define CDC_TX_BUFFER_SIZE  512
#define CDC_NUM_BUFFERS     4

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct {
    uint8_t rx_buffers[CDC_NUM_BUFFERS][CDC_RX_BUFFER_SIZE];
    uint8_t tx_buffer[CDC_TX_BUFFER_SIZE];
    uint32_t rx_buffer_idx;
    boolean connected;
} cdc_app_ctx_t;

/*----------------------------------------------------------------------------
 * Static Variables
 * -------------------------------------------------------------------------*/
static cdc_app_ctx_t cdc_app_ctx;

/*----------------------------------------------------------------------------
 * Function Declarations
 * -------------------------------------------------------------------------*/

/**
 * @brief CDC-ACM RX completion callback
 * 
 * Called when data is received from the host
 */
static void cdc_rx_callback(uint8_t* buffer, uint32_t length, uint32_t status, void* cb_data)
{
    client_ctx_t* client_ctx = (client_ctx_t*)cb_data;
    
    USB_LOG_DBG_1(log_cdc_rx_callback__len, length);
    
    if (status == USB_REQ_COMPLETE_OK && length > 0) {
        /* Process received data */
        USB_LOG_DBG(log_cdc_rx_callback__data_received);
        
        /* Echo back the received data */
        if (client_ctx) {
            usb_api()->usb_write(client_ctx, buffer, length, NULL);
        }
        
        /* Queue next RX buffer */
        uint32_t next_idx = (cdc_app_ctx.rx_buffer_idx + 1) % CDC_NUM_BUFFERS;
        if (client_ctx) {
            usb_api()->usb_read(client_ctx, cdc_app_ctx.rx_buffers[next_idx], CDC_RX_BUFFER_SIZE, NULL);
        }
        cdc_app_ctx.rx_buffer_idx = next_idx;
    } else {
        USB_LOG_ERR_2(log_cdc_rx_callback__error, status, length);
    }
}

/**
 * @brief CDC-ACM TX completion callback
 * 
 * Called when data transmission to host is complete
 */
static void cdc_tx_callback(uint8_t* buffer, uint32_t length, uint32_t status, void* cb_data)
{
    USB_LOG_DBG_1(log_cdc_tx_callback__len, length);
    
    if (status == USB_REQ_COMPLETE_OK) {
        USB_LOG_DBG(log_cdc_tx_callback__success);
    } else {
        USB_LOG_ERR_1(log_cdc_tx_callback__error, status);
    }
}

/**
 * @brief CDC-ACM event callback
 * 
 * Called for USB events like enumeration, disconnection, etc.
 */
static void cdc_event_callback(uint32_t event, void* data)
{
    client_ctx_t* client_ctx = (client_ctx_t*)data;
    
    USB_LOG_DBG_1(log_cdc_event_callback__event, event);
    
    switch(event) {
        case USB_EVENT_ENABLED:
            USB_LOG(log_cdc_event__enumeration_complete);
            cdc_app_ctx.connected = TRUE;
            
            /* Start receiving data */
            if (client_ctx) {
                usb_api()->usb_read(client_ctx, cdc_app_ctx.rx_buffers[0], CDC_RX_BUFFER_SIZE, NULL);
            }
            break;
            
        case USB_EVENT_DISCONNECT:
            USB_LOG(log_cdc_event__disconnected);
            cdc_app_ctx.connected = FALSE;
            break;
            
        default:
            USB_LOG_DBG_1(log_cdc_event__unknown_event, event);
            break;
    }
}

/**
 * @brief Initialize CDC-ACM application
 * 
 * @return USB_SUCCESS on success, error code otherwise
 */
uint32_t cdc_app_init(void)
{
    uint32_t ret;
    client_ctx_t* cdc_ctrl_client = NULL;
    client_ctx_t* cdc_data_client = NULL;
    usb_ifc_id* usb_composition;
    uint8 usb_comp_num_ifc;
    usb_dev_params_t dev_params;
    
    USB_LOG(log_cdc_app_init__start);
    
    /* Initialize application context */
    memset(&cdc_app_ctx, 0, sizeof(cdc_app_ctx_t));
    cdc_app_ctx.rx_buffer_idx = 0;
    cdc_app_ctx.connected = FALSE;
    
    /* Configure device parameters */
    memset(&dev_params, 0, sizeof(usb_dev_params_t));
    dev_params.qc_pid = USB_PID_UAC2_HEADSET;  /* Use existing PID or define new one */
    dev_params.vid_override = 0x05C6;  /* Qualcomm vendor ID */
    dev_params.pid_override = 0x9091; /* CDC-ACM product ID */
    dev_params.op_mode = USB_OP_MODE_MISSION;
    dev_params.audio_profile = 0;  /* Not used for CDC */
    dev_params.top_aud_rev = 0;    /* Not used for CDC */
    dev_params.disable_flags = 0;
    dev_params.mic_type = 0;       /* Not used for CDC */
    
    /* Set USB parameters - returns composition */
    ret = usb_api()->usb_set_params(&dev_params, &usb_composition, &usb_comp_num_ifc);
    if (ret != TRUE) {
        USB_LOG_ERR_1(log_cdc_app_init__set_params_failed, ret);
        return USB_ERR_DEFAULT;
    }
    
    /* Open CDC Control interface */
    ret = usb_api()->usb_open(&cdc_ctrl_client, USB_IFC_ID_CDC_CONTROL, NULL,
                   cdc_event_callback, cdc_rx_callback, cdc_tx_callback, 
                   CDC_NUM_BUFFERS, CDC_NUM_BUFFERS);
    if (ret != USB_SUCCESS) {
        USB_LOG_ERR_1(log_cdc_app_init__open_ctrl_failed, ret);
        return ret;
    }
    
    /* Open CDC Data interface */
    ret = usb_api()->usb_open(&cdc_data_client, USB_IFC_ID_CDC_DATA, NULL,
                   NULL, cdc_rx_callback, cdc_tx_callback,
                   CDC_NUM_BUFFERS, CDC_NUM_BUFFERS);
    if (ret != USB_SUCCESS) {
        USB_LOG_ERR_1(log_cdc_app_init__open_data_failed, ret);
        usb_api()->usb_close(cdc_ctrl_client);
        return ret;
    }
    
    USB_LOG(log_cdc_app_init__success);
    return USB_SUCCESS;
}

/**
 * @brief Send data over CDC-ACM
 * 
 * @param data Pointer to data buffer
 * @param length Length of data to send
 * 
 * @return USB_SUCCESS on success, error code otherwise
 */
uint32_t cdc_app_send_data(client_ctx_t* client_ctx, const uint8_t* data, uint32_t length)
{
    if (!cdc_app_ctx.connected) {
        USB_LOG_ERR(log_cdc_app_send__not_connected);
        return USB_ERR_CABLE_DISCONNECT;
    }
    
    if (length > CDC_TX_BUFFER_SIZE) {
        USB_LOG_ERR_1(log_cdc_app_send__buffer_too_large, length);
        return USB_ERR_BAD_PARAM;
    }
    
    if (!client_ctx) {
        USB_LOG_ERR(log_cdc_app_send__null_ctx);
        return USB_ERR_BAD_PARAM;
    }
    
    /* Copy data to TX buffer */
    memcpy(cdc_app_ctx.tx_buffer, data, length);
    
    /* Send data */
    return usb_api()->usb_write(client_ctx, cdc_app_ctx.tx_buffer, length, NULL);
}

/**
 * @brief Example main function
 */
/* Example usage - not a real main function, just for reference */
void cdc_app_example_usage(client_ctx_t* cdc_data_client)
{
    uint32_t ret;
    const char* test_msg = "Hello from CDC-ACM!\r\n";
    
    /* Initialize CDC-ACM application */
    ret = cdc_app_init();
    if (ret != USB_SUCCESS) {
        //USB_LOG_ERR_1(log_main__cdc_init_failed, ret);
        return;
    }
    
    /* Wait for enumeration */
    while (!cdc_app_ctx.connected) {
        /* Poll USB events */
        usb_handle_signal(0);
        /* Add delay or yield to other tasks */
    }
    
    /* Send test message */
    ret = cdc_app_send_data(cdc_data_client, (const uint8_t*)test_msg, strlen(test_msg));
    if (ret != USB_SUCCESS) {
        //USB_LOG_ERR_1(log_main__send_failed, ret);
    }
    
    /* Main loop - handle USB events */
    while (1) {
        usb_handle_signal(0);
        /* Add your application logic here */
    }
}

/*----------------------------------------------------------------------------
 * Additional Helper Functions
 * -------------------------------------------------------------------------*/

/**
 * @brief Check if CDC-ACM is connected
 * 
 * @return TRUE if connected, FALSE otherwise
 */
boolean cdc_app_is_connected(void)
{
    return cdc_app_ctx.connected;
}

/**
 * @brief Get CDC-ACM connection status
 * 
 * @param rx_count Pointer to store RX byte count (optional)
 * @param tx_count Pointer to store TX byte count (optional)
 */
void cdc_app_get_stats(uint32_t* rx_count, uint32_t* tx_count)
{
    /* Implement statistics tracking if needed */
    if (rx_count) {
        *rx_count = 0;  /* TODO: Track RX bytes */
    }
    if (tx_count) {
        *tx_count = 0;  /* TODO: Track TX bytes */
    }
}
