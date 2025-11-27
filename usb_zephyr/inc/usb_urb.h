#ifndef USB_URB_H
#define USB_URB_H
/*=======================================================================*//**
  @file         usb_urb.h
 
  @brief        URB
 
  @details      
                Theory of operation 
                 
                URB stands for USB Request Buffer; it facilitate data 
                exchange between application and DCI. 
                 
                URB is allocated by application. Application provides also 
                transmit buffer. Application fills: 
                 - signature 
                 - transfer_buffer_ptr
                 - transfer_length
                 - ep
                 - is_tx
                 - complete_callback
                 - app_priv_ptr
                 
                Then, application calls usb_dcd_submit_urb. This function 
                returns error code. If error occurs (returned is negative 
                value), submission failed and URB was not passed to DCI. If 
                success (0) is returned, from this moment, ownership over URB 
                passed to DCI and application can't access URB. 
                 
                Eventually, when DCI finished with this URB, it call URB's 
                complete() callback. At this moment, ownership over URB 
                returns to application. Application analyse transfer_status 
                to decide on next actions. DCI fills: 
                - transfer_status 
                - actual_length 
                - in case of Rx, buffer filled with data 
 
               Copyright (c) 2008 QUALCOMM Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
*//*========================================================================*/
/* $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dcd/usb_urb.h#1 $ */

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "comdef.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define USB_URB_MAX                             (0x5)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
//struct usb_dcd_ctx;

//typedef void (*urb_complete_callback)((struct usb_urb)* urb_ptr);
typedef enum
{
  DIR_RX, // OUT Token
  DIR_TX, // IN Token
  DIR_NONE = 0xFF
} usb_ep_dir_t;

/**
 * USB Request buffer
 */
typedef struct usb_urb{
  uint32 signature;     //should match \a USB_URB_SIGNATURE 
#define USB_URB_SIGNATURE (0x42525551) // 'QURB'
  /********************* control *********************/
  //usb_urb_t* next; /**< link URB's for the EP */
  /**
  * Transaction status.
  *  - DCD set to 0 prior to submission;
  *  - DCI modifies to ACTIVE when submited, and to
  *    COMPLETE/ERROR on completeion.
  *  - in complete(), DCD check status.
  */
  uint32 transfer_status;
#define USB_URB_STATUS_QUEUED          (1)   /**< Request queued       */
#define USB_URB_STATUS_ACTIVE          (2)   /**< Transfer in progress */
#define USB_URB_STATUS_COMPLETE_OK     (3)   /**< Completed, success   */
#define USB_URB_STATUS_COMPLETE_ERROR  (4)   /**< completed, error     */
#define USB_URB_STATUS_TRANSFER_CANCEL (5)   /**< cancel_transfer      */

  //struct usb_dcd_ctx* usb_device;    /**< DCD context */
  void* fd_ctx;

  /**
  * queued for this EP, 
  *  - bits 3:0 - EP number, 
  *  - bit 7 - IN(1)/OUT(0)
  */
  uint8 endpoint_address;
  uint8 reserved0[3]; // align to 32 bits
  /*************** data *****************/
  /**
  * Data buffer
  */
  void* transfer_buffer_ptr;
  /**
  * Length, bytes, of buffer
  */
  uint32 transfer_length;
  /**
  * Bytes user in buffer. Filled by DCI upon Rx
  */
  uint32 actual_length;
  /**
  * Flag to let FD layer to specify whether we want to transmit a ZLP 
  */
  uint8 send_zlp;

  uint8 reserved1[2]; // align to 32 bits
  /******************** application use ********************/
  /**
  * callback to be executed upon transmission completion.
  */
  void (*complete_callback)(struct usb_urb* urb_ptr);
  //urb_complete_callback complete_callback;

  /**
  * private data to be used by application / driver
  */
  void* app_priv_ptr; // high level
  void* dcd_priv_ptr;
  void* dci_priv_ptr; // low level 
  //client_ctx_t* client_ctx;
  uint32 client_id;
  uint32 req_id;
  void* cb_data;
} usb_urb_t;




#endif /*USB_URB_H*/

