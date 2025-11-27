#ifndef USB_DCD_CH9_H
#define USB_DCD_CH9_H
/*=======================================================================*/
/*
  @file         usb_dcd_ch9.h
 
  @brief        USB Chapter 9 structures
 
  @details      
 
               Copyright (c) 2008-2018 Qualcomm Technologies, Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary
========================================================================*/ 
// $Header: //source/qcom/qct/core/wiredconnectivity/usb/rel/2.2/src/dcd/usb_dcd_ch9.h#1
//
//  when        who       what, where, why
//  ----------  -------- -------------------------------------------------------
//  2010-08-30  dpatnaik  Port USB to RPM, add ULPI based charger detection
//
//========================================================================
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/

#include "comdef.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define USB_VENDOR_BUFF_SIZE   (64)
/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------
  Define Macro PACKED
---------------------------------------------------------------------------*/
/**
*  Enumeration for Port Test Mode. USB2.0 Table 9-2
**/
typedef enum {
  USB_PORT_TEST_DISABLE,
  USB_PORT_TEST_J_STATE,
  USB_PORT_TEST_K_STATE,
  USB_PORT_TEST_SE0_NAK,
  USB_PORT_TEST_PACKET,
  USB_PORT_TEST_FORCE_ENABLE,
} QCOM_USB_PORT_TEST_MODE;


/**
 * Setup packet
 */
typedef PACKED struct usb_setup_packet {
   uint8  bmRequestType;
   uint8  bRequest;
   uint16 wValue;
   uint16 wIndex;
   uint16 wLength;
} PACKED_POST usb_setup_packet_t ;

/** @defgroup usb_setup_rt Request type sub-fields
 *  Bit fields for bmRequestType
 */
/*@{*/

/** @defgroup usb_setup_rt_dir Data transfer direction
 *  Bit 7
 */
/*@{*/
#define USB_SETUP_RT_DIR_POS  (7)     // Position
#define USB_SETUP_RT_DIR_SEED (0x01)  // Seed
#define USB_SETUP_RT_DIR_MASK (USB_SETUP_RT_DIR_SEED << USB_SETUP_RT_DIR_POS) //Mask 
#define USB_SETUP_RT_DIR_H2D  (0)     //Host to Device 
#define USB_SETUP_RT_DIR_D2H  (1)     //Device to Host 
/* @} usb_setup_rt_dir */

/** @defgroup usb_setup_rt_type Type
 *  Bits 6:5
 */
/*@{*/
#define USB_SETUP_RT_TYPE_POS  (5)    // Position 
#define USB_SETUP_RT_TYPE_SEED (0x03) // Seed 
#define USB_SETUP_RT_TYPE_MASK (USB_SETUP_RT_TYPE_SEED << USB_SETUP_RT_TYPE_POS) // Mask 
#define USB_SETUP_RT_TYPE_STD  (0)    // Standard 
#define USB_SETUP_RT_TYPE_CLS  (1)    // Class 
#define USB_SETUP_RT_TYPE_VND  (2)    // Vendor 
#define USB_SETUP_RT_TYPE_RSVD (3)    //Reserved 
/* @} usb_setup_rt_type */

/** @defgroup usb_setup_rt_rcp Recipient
 *  Bits 4:0
 */
/*@{*/
#define USB_SETUP_RT_RCP_POS  (0)     // Position 
#define USB_SETUP_RT_RCP_SEED (0x1f)  // Seed 
#define USB_SETUP_RT_RCP_MASK (USB_SETUP_RT_RCP_SEED << USB_SETUP_RT_RCP_POS) // Mask 
#define USB_SETUP_RT_RCP_DEV  (0)     // Device 
#define USB_SETUP_RT_RCP_IFC  (1)     // Interface 
#define USB_SETUP_RT_RCP_EP   (2)     // Endpoint 
#define USB_SETUP_RT_RCP_OTH  (3)     // Other 
/* @} usb_setup_rt_rcp */

/* @} usb_setup_rt */

/** @defgroup usb_setup_req Requests
 *  values for bRequest
 */
/*@{*/
#define USB_SETUP_REQ_GET_STATUS         (0)
#define USB_SETUP_REQ_CLEAR_FEATURE      (1)
#define USB_SETUP_REQ_SET_FEATURE        (3)
#define USB_SETUP_REQ_SET_ADDRESS        (5)
#define USB_SETUP_REQ_GET_DESCRIPTOR     (6)
#define USB_SETUP_REQ_SET_DESCRIPTOR     (7)
#define USB_SETUP_REQ_GET_CONFIGURATION  (8)
#define USB_SETUP_REQ_SET_CONFIGURATION  (9)
#define USB_SETUP_REQ_GET_INTERFACE     (10)
#define USB_SETUP_REQ_SET_INTERFACE     (11)
#define USB_SETUP_REQ_SYNCH_FRAME       (12)
#define USB_SETUP_REQ_SET_SEL           (48)
#define USB_SETUP_REQ_SET_ISOCH_DELAY   (49)


/* @} usb_setup_req */

/** @defgroup usb_desctype Descriptor Types
 *  values for bDescriptorType
 */
/*@{*/
#define USB_DESCTYPE_DEVICE         (1)
#define USB_DESCTYPE_CONFIGURATION  (2)
#define USB_DESCTYPE_STRING         (3)
#define USB_DESCTYPE_INTERFACE      (4)
#define USB_DESCTYPE_ENDPOINT       (5)
#define USB_DESCTYPE_DEV_QUAL       (6)
#define USB_DESCTYPE_OTH_SPEED      (7)
#define USB_DESCTYPE_IFC_POWER      (8)
#define USB_DESCTYPE_EP_COMP        (0x30)
#define USB_DESCTYPE_BOS            (0xf)
#define USB_DESCTYPE_DEV_CAP        (0x10) // device capability 

/**
 * @ref HID 1.11 clause 7.1
 */
#define USB_DESCTYPE_HID           (33)
#define USB_DESCTYPE_HID_REPORT    (34)
#define USB_DESCTYPE_HID_PHYS      (35)
/* @} usb_desctype */

/** @defgroup usb_fsel Feature Selectors
 *  values for wValue in {SET|CLEAR}_FEATURE requests
 */
/*@{*/
#define USB_FSEL_EP_HALT            (0)
#define USB_FSEL_DEV_REMOTE_WAKEUP  (1)
#define USB_FSEL_DEV_TEST_MODE      (2)

#define USB_FSEL_IFACE_FUNC_SUSP    (0)

#define USB_FSEL_U1_ENABLE          (48)
#define USB_FSEL_U2_ENABLE          (49)
#define USB_FSEL_LTM_ENABLE         (50)

/* USB Feature Status bits */
#define DEV_BUS_PWRD            (0)
#define DEV_SELF_PWRD           (1)
#define DEV_REMOTE_WAKEUP       (1 << 1)
#define U1_ENABLE               (1 << 2)
#define U2_ENABLE               (1 << 3)

#define FUNC_REMOTE_WAKEUP_CAP  (1)
#define FUNC_REMOTE_WAKEUP      (1 << 1)



/* @} usb_desctype */

/**
 * Any descriptor begins with this header
 */
typedef PACKED struct usb_desc_header {
  uint8  bLength;
  uint8  bDescriptorType;
} PACKED_POST usb_desc_header_t;

/**
 * Standard Device descriptor
 */
typedef PACKED struct usb_desc_device {
  uint8  bLength;
  uint8  bDescriptorType;              //USB_DESCTYPE_DEVICE 
  uint16 bcdUSB;
  uint8  bDeviceClass;
  uint8  bDeviceSubClass;
  uint8  bDeviceProtocol;
  uint8  bMaxPacketSize0;
  uint16 idVendor;
  #define USB_VENDOR_ID_QUALCOMM      (0x05C6)
  uint16 idProduct;
  uint16 bcdDevice;
  uint8  iManufacturer;
  uint8  iProduct;
  uint8  iSerialNumber;
  uint8  bNumConfigurations;
} PACKED_POST usb_desc_device_t;

/**
 * Standard Configuration descriptor 
 * Same structure used for USB_DESCTYPE_OTH_SPEED 
 */
typedef PACKED struct usb_desc_configuration {
  uint8  bLength;
  uint8  bDescriptorType;              // USB_DESCTYPE_CONFIGURATION 
  uint16 wTotalLength;
  uint8  bNumInterfaces;
  uint8  bConfigurationValue;
  uint8  iConfiguration;
  uint8  bmAttributes;
  uint8  bMaxPower;
} PACKED_POST usb_desc_configuration_t;

/**
 * Standard Interface descriptor
 */
typedef PACKED struct usb_desc_interface {
  uint8  bLength;
  uint8  bDescriptorType;              // USB_DESCTYPE_INTERFACE 
  uint8  bInterfaceNumber;
  uint8  bAlternateSetting;
  uint8  bNumEndpoints;
  uint8  bInterfaceClass;
  uint8  bInterfaceSubClass;
  uint8  bInterfaceProtocol;
  uint8  iInterface;
} PACKED_POST usb_desc_interface_t;

/**
 * Standard Endpoint descriptor
 */
typedef PACKED struct usb_desc_endpoint {
  uint8  bLength;
  uint8  bDescriptorType;              // USB_DESCTYPE_ENDPOINT 
  uint8  bEndpointAddress;
#define USB_EP_ADDR_OUT                (0)
#define USB_EP_ADDR_IN              (0x80)
  uint8  bmAttributes;
#define USB_EP_ATTR_CNTRL              (0)
#define USB_EP_ATTR_ISOCH              (1)
#define USB_EP_ATTR_BULK               (2)
#define USB_EP_ATTR_INTR               (3)
#define USB_EP_ATTR_SYNC_NONE          (0 << 2)
#define USB_EP_ATTR_SYNC_ASYNC         (1 << 2)
#define USB_EP_ATTR_SYNC_ADAPTIVE      (2 << 2)
#define USB_EP_ATTR_SYNC_SYNC          (3 << 2)
#define USB_EP_ATTR_USAGE_DATA         (0 << 4)
#define USB_EP_ATTR_USAGE_FEEDBACK     (1 << 4)
#define USB_EP_ATTR_USAGE_EXPL_FB_DATA (2 << 4)
#define USB_EP_ATTR_USAGE_RSVD         (3 << 4)
  uint16 wMaxPacketSize;
  uint8  bInterval;
} PACKED_POST usb_desc_endpoint_t;

/**
 * Standard Device Qualifier descriptor
 */
typedef PACKED struct usb_desc_dev_qual {
  uint8  bLength;
  uint8  bDescriptorType;              //USB_DESCTYPE_DEV_QUAL
  uint16 bcdUSB;
  uint8  bDeviceClass;
  uint8  bDeviceSubClass;
  uint8  bDeviceProtocol;
  uint8  bMaxPacketSize0;
  uint8  bNumConfigurations;
  uint8  bReserved;
} PACKED_POST usb_desc_dev_qual_t;

/**
 * HID class descriptor 
 */
typedef PACKED struct usb_desc_hid {
 uint8  bLength;
 uint8  bDescriptorType;              // USB_DESCTYPE_HID
 uint16 bcdHID;
 uint8  bCountryCode;
 uint8  bNumDescriptor;
 uint8  bDescriptorType1;             //1 to avoid name clash
 uint16 wDescriptorLen;
} PACKED_POST usb_desc_hid_t;

/* *
 * SuperSpeed Endpoint Companion descriptor
 */
typedef PACKED struct usb_ep_comp_desc {
  uint8  bLength;
  uint8  bDescriptorType;
  uint8  bMaxBurst;
  uint8  bmAttributes;
  uint16 wBytesPerInterval;
} PACKED_POST usb_ep_comp_desc_t;

// BOS Descriptors 
#define USB_BOS_DEV_CAP_TYPE__WIRELESS_USB        (0x01)
#define USB_BOS_DEV_CAP_TYPE__USB2_EXTN           (0x02)
#define USB_BOS_DEV_CAP_TYPE__SUPERSPEED          (0x03)
#define USB_BOS_DEV_CAP_TYPE__CONFIG_SUMMARY      (0x10)

#define USB_BOS_DEV_CAP_USB2_EXTN_ATTR_LPM                   (1 << 1)
#define USB_BOS_DEV_CAP_USB2_EXTN_BESL_ALT_HIRD_SUPPORT      (1 << 2)
#define USB_BOS_DEV_CAP_USB2_EXTN_RECOM_BASELINE_BESL_VALID  (1 << 3)
#define USB_BOS_DEV_CAP_USB2_EXTN_RECOM_DEEP_BESL_VALID      (1 << 4)
#define USB_BOS_DEV_CAP_USB2_EXTN_RECOM_BASELINE_BESL_VALUE_SHFT  (8)
#define USB_BOS_DEV_CAP_USB2_EXTN_RECOM_DEEP_BESL_VALUE_SHFT      (12)

//BESL (Best Effor Service Latency). The vaue indicate the amount of time from the start of a resume
// to when the host will attempt to begin issuing transaction to the device. 
typedef enum 
{
  USB_LPM_BESL_125_US = 0,
  USB_LPM_BESL_150_US,    
  USB_LPM_BESL_200_US,    
  USB_LPM_BESL_300_US,
  USB_LPM_BESL_400_US,
  USB_LPM_BESL_500_US,    
  USB_LPM_BESL_1000_US,    
  USB_LPM_BESL_2000_US,
  USB_LPM_BESL_3000_US,
  USB_LPM_BESL_4000_US,    
  USB_LPM_BESL_5000_US,    
  USB_LPM_BESL_6000_US,
  USB_LPM_BESL_7000_US,
  USB_LPM_BESL_8000_US,    
  USB_LPM_BESL_9000_US,    
  USB_LPM_BESL_10000_US
} USB_LPM_BESL_US_TYPE;


// Device level capability desc.
typedef PACKED struct usb_bos_desc 
{
  uint8  bLength;
  uint8  bDescriptorType;
  uint16 wTotalLength;
  uint8  bNumDeviceCaps;
} PACKED_POST usb_bos_desc_t;

// Device capability header desc.
typedef PACKED struct usb_bos_dev_cap_header 
{
  uint8   bLength;
  uint8   bDescriptorType;
  uint8   bDevCapabilityType;
} PACKED_POST usb_bos_dev_cap_header_t;

// USB 2.0 Extension capability descriptor.
typedef PACKED struct usb_bos_dev_cap_usb20_extn 
{
  uint8   bLength;
  uint8   bDescriptorType;
  uint8   bDevCapabilityType;
  uint32  bmAttributes;  
} PACKED_POST usb_bos_dev_cap_usb20_extn_t;

// Speed capabilities
#define USB_LOW_SPEED_SUPPORT       (1)
#define USB_FULL_SPEED_SUPPORT      (1 << 1)
#define USB_HIGH_SPEED_SUPPORT      (1 << 2)
#define USB_SUPER_SPEED_SUPPORT     (1 << 3)

// SuperSpeed capability descriptor
typedef PACKED struct usb_bos_dev_cap_ss {
  uint8  bLength;
  uint8  bDescriptorType;
  uint8  bDevCapabilityType;
  uint8  bmAttributes;
  uint16 wSpeedSupported;
  uint8  bFunctionalitySupport;
  uint8  bU1devExitLat;
  uint16 bU2DevExitLat;
} PACKED_POST usb_bos_dev_cap_ss_t;

// USB configuration summery descriptor
typedef PACKED struct usb_bos_dev_cap_config_summary 
{
  uint8   bLength;
  uint8   bDescriptorType;
  uint8   bDevCapabilityType;
  uint16  bcdVersion;
  uint8   bClass;
  uint8   bSubClass;
  uint8   bProtocol;
  uint8   bConfigurationCount;
  uint8   bConfigurationIndex;
} PACKED_POST usb_bos_dev_cap_config_summary_t;

//
// Tracking the control transfer stage
//
typedef enum usb_link_state{
  LS_U0 = 0,  // HS on state 
  LS_U1,
  LS_U2,      // HS L1 state (sleep)  
  LS_U3,      // HS L2 state (suspend) 
  LS_SS_DIS,  // HS Disconnect state
  LS_RX_DET,
  LS_SS_INACT,
  LS_POLL,
  LS_RECOV,   // Remote Wakeup for HS
  LS_HRESET,
  LS_CMPLY,
  LS_LPBK,
  LS_RESUME_RESET = 0xF
} usb_link_state_t;

typedef enum usb_device_bcd_USB{
  USB_BCD_USB2       = 0x200,
  USB_BCD_USB2_EXT   = 0x201,
  USB_BCD_USB3       = 0x300,    
} usb_device_bcd_USB_t; 

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
typedef enum usb_notify_events {
  USB_DCD_EVT_ATTACH = 0x0,    // is_attached changed 
  USB_DCD_EVT_SPEED,           // speed changed 
  USB_DCD_EVT_ADDRESS,         // address changed 
  USB_DCD_EVT_CONFIG,          // config_value changed 
  USB_DCD_EVT_CURRENT,         // max_current changed 
  USB_DCD_EVT_SUSPEND,         // is_suspended changed (suspend/resume)
  //
  // Custom Event Notification
  // This is called to inform about a disconnect event or a Reset
  // Event to the Application layer.
  //
  USB_DCD_EVT_DISCONNECT,      // device disconnected
  USB_DCD_EVT_UNCONFIG,        // config_value changed
  USB_DCD_EVT_RESET,           // bus reset received
  USB_DCD_EVT_OTHER,           // any other event 
  
  // Contol events
  USB_DCD_EVT_CTRL_SETUP_COMPLETE,
  USB_DCD_EVT_CTRL_INIT,
  USB_DCD_EVT_CTRL_STATUS_COMPLETE,
  USB_DCD_EVT_CTRL_ERROR,

  // Isoc events
  USB_DCD_EVT_START_SESSION,
  USB_DCD_EVT_RECONFIG_SESSION,
  USB_DCD_EVT_STOP_SESSION,
}usb_notify_events_t;

#endif /*USB_DCD_CH9_H*/

