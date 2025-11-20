/*=======================================================================*//**
  @file         usb_fd.c

  @brief        Function Driver for  USB custom function

  @details      
                This FD implements HDLC streaming protocol.
                It can use one of the following USB interfaces, depending on
                value of global variable usb_hdlc_use_cdcacm:

                - 0 : use vendor specific class with 2 bulk EP's
                - 1 : use CDC/ACM class with 2 bulk and 1 interrupt EP's

                HDLC implementation: For H->D direction, double buffers used
                to maximize throughput. Upon packet receive, the user supplied
                callback executed. This callback should handle the data arrived.
                For D->H direction, byte oriented interface provided. Data
                accumulated in internal buffer till it is full or 
                HDLC terminator (0x7e) submitted. In this case, packet get 
                transmitted to the USB bus.

                CDC/ACM implementation: FD supports ACM class specific commands:

                - SET_LINE_CODING
                - GET_LINE_CODING
                - SET_CONTROL_LINE_STATE

                Immediately after configuration (SET_CONFIG), FD sends 
                SERIAL_STATE notification indicating DCD and DSR

                CDC/ACM uses 2 interfaces, thus it requires 
                USB_HAVE_MULTI_FUNCTIONS to be defined.

                To use CDC/ACM, set usb_hdlc_use_cdcacm to 1 prior to
                USB stack initialization

                When the USB_SINGLE_BOOT_ENUM_MAGIC is passed via the 
                HS-USB scratch register HDLC will not issue a USB enumeration.
                Instead, it will rely on the existing USB enumeration. This is
                done for having a single USB enumeration during SW download.
 
                Copyright (c) 2008-2009 QUALCOMM Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
*//*========================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/func/usb_fd.c#17 $$DateTime: 2018/10/22 13:23:50 $$Author: pwbldsvc $

  when        who       what, where, why
  ----------  ---       ------------------------------------------------------
  2013-09-17  shreyasr	Removed the CDC ACM support and changes for SNPS controller
  2011-07-22  dpatnaik  For EMMCBLD/EHOSTDL dont update serial number string
  2011-06-10  dpatnaik  Added support for reading PID, Serial string from IMEM
  2011-05-18  kimd      Added support for unframed RAM-dump (tx packet feature)
  2009-04-17  dhaval    Fixed vid/pid read for cdc/acm device.
  2009-04-16  dhaval    Implemented API for retrieving vid/pid
  2009-04-09  dhaval    Corrected iSerialNumber
  2009-04-06  dhaval    Added API usb_fd_rx_completed to fix defect
                        when usb transfer > 4K.
  2009-03-17  dhaval    Added API for updating vid/pid if vid/pid fuses blown 
  2009-03-17  dhaval    Removed compiler warnings.
  2008-12-17  vkondrat  CDC/ACM support
  2008-08-14  vkondrat  redesign - use simple 1 buffer mode, Rx callback
  2008-08-10  vkondrat  initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_fd.h"
#include "usb_dcd.h"
#include <stringl/stringl.h>
#include "usb_common.h"
#include "usb_log.h"
#include "usb_util.h"
//#include "usb_audio_class_30.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define CUSTOMIZE NULL

// STRING DESCRIPTOR - USB 2.0 specification Table 9-16
// 1 byte:  bLength         - size of this desc in bytes
// 1 byte:  bDescriptorType - STRING Descriptor Type
// N bytes: bString         - UNICODE encoded string
// UNICODE string scriptor is not NULL-terminated.  The string length is
// substracting two from the value of the first type of the descriptor

// bLength's max value is 255.  2 bytes are used for bLength and 
// bDescriptorType fields
// This leaves 255-2 = 253 for UNICODE string size in bytes.
// Since UNICODE byte size has to be even number, max UNICODE ARRAY byte size 
// is 252 bytes.
#define USB_STRING_DESC_UNICODE_SIZE_MAX         (252)

// Size of bLength and bDescriptor field in STRING DESCRIPTOR in bytes
#define USB_STRING_DESC_LEN_AND_DESC_FIELD_SIZE  (2)

// Maximum size for the STRING DESCRIPTOR, must be even number
#define USB_STRING_DESC_SIZE_MAX    \
  (USB_STRING_DESC_UNICODE_SIZE_MAX \
  + USB_STRING_DESC_LEN_AND_DESC_FIELD_SIZE)

#define USB_DLOAD_SIZE                             (35)

#define USB_CONFIG_PRIORITY_SIZE                    (5)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
 //uint32 usb_dload_info[USB_DLOAD_SIZE];  //This is the static dload structure 

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

void usb_fd_notify(void* fd_ctx, usb_notify_events_t event);

void usb_fd_alloc_ep_comp_desc(uint8** dsc, uint16* len, uint16 dsc_size, 
  uint8 burst_size, uint8 attr, uint8 bpi)
{
  usb_ep_comp_desc_t* ep_comp = (usb_ep_comp_desc_t*) (*dsc);
  USB_ASSERT(ep_comp);
  (*len) += sizeof(usb_ep_comp_desc_t);
  USB_ASSERT((*len) < dsc_size);  
  ep_comp->bLength           = sizeof(usb_ep_comp_desc_t);
  ep_comp->bDescriptorType   = USB_DESCTYPE_EP_COMP;
  ep_comp->bMaxBurst         = burst_size;
  ep_comp->bmAttributes      = attr;
  ep_comp->wBytesPerInterval = bpi;
  (*dsc) += sizeof(usb_ep_comp_desc_t);  
}

usb_dcd_dsc_endpoint_t* usb_fd_alloc_ep_desc(uint8** dsc, uint16* len, uint16 dsc_size, 
uint8 ep_num, uint8 ep_mask, uint8 ep_attr, uint8 ep_interval, uint16 max_packet_size)
{
  usb_dcd_dsc_endpoint_t* ep_ptr;
  usb_desc_endpoint_t* ep = (usb_desc_endpoint_t*) (*dsc);

  USB_ASSERT(ep);
  USB_ASSERT(ep_ptr = (usb_dcd_dsc_endpoint_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_dsc_endpoint_t)));

  (*len) += sizeof(usb_desc_endpoint_t);
  USB_ASSERT((*len) < dsc_size);
  ep->bLength            = sizeof(usb_desc_endpoint_t);
  ep->bDescriptorType    = USB_DESCTYPE_ENDPOINT;
  ep->wMaxPacketSize     = max_packet_size;
  ep->bEndpointAddress   = ep_num | ep_mask;
  ep->bmAttributes       = ep_attr;
  ep->bInterval          = ep_interval;
  ep_ptr->descriptor = ep;
  (*dsc) += sizeof(usb_desc_endpoint_t);
  return ep_ptr;
}

usb_dcd_dsc_interface_t* usb_fd_alloc_ifc_desc(uint8** dsc, uint16* len, uint16 dsc_size, 
uint8 ifc_index, uint8 alt_setting, uint8 n_ep, uint8 ifc_class, uint8 subclass, uint8 protocol, 
uint8 str_index)
{
  usb_dcd_dsc_interface_t* ifc_ptr;
  usb_desc_interface_t* ifc = (usb_desc_interface_t*) (*dsc);

  USB_ASSERT(ifc);
  USB_ASSERT(ifc_ptr = (usb_dcd_dsc_interface_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_dsc_interface_t)));

  (*len) += sizeof(usb_desc_interface_t);
  USB_ASSERT((*len) < dsc_size);
  ifc->bLength                = sizeof(usb_desc_interface_t);
  ifc->bDescriptorType        = USB_DESCTYPE_INTERFACE;
  ifc->bInterfaceNumber       = ifc_index;
  ifc->bAlternateSetting      = alt_setting;
  ifc->bNumEndpoints          = n_ep;
  ifc->bInterfaceClass        = ifc_class;
  ifc->bInterfaceSubClass     = subclass;
  ifc->bInterfaceProtocol     = protocol;
  ifc->iInterface             = str_index;
  ifc_ptr->descriptor = ifc;
  (*dsc) += sizeof(usb_desc_interface_t);
  return ifc_ptr;
}

usb_dcd_dsc_configuration_t * usb_fd_create_cfg_desc (uint8** dsc, uint16* len, 
  uint16 dsc_size, uint8 id, uint8 n_ifc)
{
  usb_dcd_dsc_configuration_t* cfg_ptr;
  usb_desc_configuration_t* cfg = (usb_desc_configuration_t*) (*dsc);

  USB_ASSERT(cfg);
  USB_ASSERT(cfg_ptr = (usb_dcd_dsc_configuration_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_dsc_configuration_t)));

  (*len) += sizeof(usb_desc_configuration_t);
  USB_ASSERT((*len) < dsc_size);
  cfg->bLength               = sizeof(usb_desc_configuration_t);
  cfg->bDescriptorType       = USB_DESCTYPE_CONFIGURATION;
  cfg->wTotalLength          = 0; // Update at end.
  cfg->bNumInterfaces        = n_ifc;
  cfg->bConfigurationValue   = id;
  cfg->iConfiguration        = 0;
  cfg->bmAttributes          = 0xA0;
  cfg->bMaxPower             = 0x32;
  cfg_ptr->descriptor = cfg;
  (*dsc) += sizeof(usb_desc_configuration_t);

  return cfg_ptr;
}

int usb_fd_set_cfg(usb_dcd_dsc_configuration_t* cfg, usb_setup_packet_t* req)
{
  uint8 ifc_index;
  usb_dcd_dsc_interface_t* ifc_itr;
  usb_fd_ctx_t* fd_ctx = cfg->dcd_ctx->fd_ctx;

  for(ifc_index = 0, ifc_itr = cfg->interfaces; ifc_itr; ifc_itr = ifc_itr->next)
  {
    if(ifc_index == ifc_itr->descriptor->bInterfaceNumber)
    {
      if(fd_ctx->ifc_ctx[ifc_index].fn_class.set_cfg)
      {
        fd_ctx->ifc_ctx[ifc_index].fn_class.set_cfg(fd_ctx->ifc_ctx[ifc_index].fn_class.ctx, 
          ifc_itr);
      }
      ifc_index++; // skip alternate settings for same interface
    }
  }
  return 0;
}

// Provide a callback for deferred processing of SET_REQ control command.
void usb_fd_set_req_status_comp_cb(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req)
{
  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)fd_ptr;
  ifc_ctx_t* ifc_ctx = NULL;

  if(ifc_num < fd_ctx->dev_cfg->usb_comp_num_ifc)
  {
    ifc_ctx = &fd_ctx->ifc_ctx[ifc_num];
    if(ifc_ctx->fn_class.set_req_status_comp_cb) 
    {
      ifc_ctx->fn_class.set_req_status_comp_cb(ifc_ctx->fn_class.ctx, req);
    }
  }
}

boolean usb_fd_handle_set_req(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req, uint32* buff, uint32 len)
{
  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)fd_ptr;
  ifc_ctx_t* ifc_ctx = NULL;
  if(ifc_num < fd_ctx->dev_cfg->usb_comp_num_ifc)
  {
    ifc_ctx = &fd_ctx->ifc_ctx[ifc_num];
    if(ifc_ctx->fn_class.handle_set_req) 
    {
      return ifc_ctx->fn_class.handle_set_req(ifc_ctx->fn_class.ctx, req, buff, len);
    }
  }
  return FALSE;
}

uint8* usb_fd_handle_get_req(void* fd_ptr, uint8 ifc_num, usb_setup_packet_t* req, uint32* len)
{
  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)fd_ptr;
  ifc_ctx_t* ifc_ctx = NULL;
  if(ifc_num < fd_ctx->dev_cfg->usb_comp_num_ifc)
  {
    ifc_ctx = &fd_ctx->ifc_ctx[ifc_num];
    if(ifc_ctx->fn_class.handle_get_req) 
    {
      return ifc_ctx->fn_class.handle_get_req(ifc_ctx->fn_class.ctx, req, len);
    }  
  }
  return NULL;
}

usb_bos_desc_t* usb_fd_alloc_bos_desc(usb_fd_ctx_t* fd_ctx)
{
  uint8* dsc;
  uint16 len = 0;
  uint8 i;
  usb_bos_desc_t* bos;
  usb_bos_dev_cap_usb20_extn_t* bos_usb20_extn;
  usb_bos_dev_cap_config_summary_t* bos_cfg_sum;
  usb_dcd_dsc_configuration_t* cfg_itr;
  usb_dcd_dsc_configuration_t* cfg_priority[USB_CONFIG_PRIORITY_SIZE] = {NULL, NULL, NULL, NULL, NULL};
  usb_dcd_dsc_interface_t* ifc_itr;
  uint8 n_cfg;
  usb_audio_class_rev_t rev;
  USB_ASSERT(fd_ctx && fd_ctx->dev_cfg && fd_ctx->dcd_ctx);
  USB_ASSERT(dsc = (uint8*)usb_fn_mem_util()->usb_malloc(USB_BOS_DESC_SIZE));

  // Allocate BOS Descriptor
  bos = (usb_bos_desc_t*) dsc;
  len += sizeof(usb_bos_desc_t);
  USB_ASSERT(len < USB_BOS_DESC_SIZE);
  bos->bLength          = sizeof(usb_bos_desc_t);
  bos->bDescriptorType  = USB_DESCTYPE_BOS;
  bos->wTotalLength     = 0; // populate at end.
  bos->bNumDeviceCaps   = 0;
  dsc += sizeof(usb_bos_desc_t);

  // Allocate Misc. device capability registers.
  // Advertise USB 2.0 extension capability.
  bos->bNumDeviceCaps++;
  bos_usb20_extn = (usb_bos_dev_cap_usb20_extn_t*) dsc;
  len += sizeof(usb_bos_dev_cap_usb20_extn_t);
  USB_ASSERT(len < USB_BOS_DESC_SIZE);
  bos_usb20_extn->bLength            = sizeof(usb_bos_dev_cap_usb20_extn_t);
  bos_usb20_extn->bDescriptorType    = USB_DESCTYPE_DEV_CAP;
  bos_usb20_extn->bDevCapabilityType = USB_BOS_DEV_CAP_TYPE__USB2_EXTN;
  bos_usb20_extn->bmAttributes       =(USB_LPM_BESL_150_US << USB_BOS_DEV_CAP_USB2_EXTN_RECOM_BASELINE_BESL_VALUE_SHFT)|
     USB_BOS_DEV_CAP_USB2_EXTN_BESL_ALT_HIRD_SUPPORT |USB_BOS_DEV_CAP_USB2_EXTN_ATTR_LPM; // LPM capable.
  dsc += sizeof(usb_bos_dev_cap_usb20_extn_t);

  n_cfg = 1;// TODO: for audio, fd_ctx->dev_cfg->audio_rev_arr_size;

  if(n_cfg <= 1)
  {
    bos->wTotalLength = len;
    return bos;
  }

  // Advertise config summary descriptor only when multi-config.
  // Priority order for config summary is UAC3.0 --> UAC2.0 --> BADD3 --> UAC1.0
  cfg_itr = usb_fn_dcd()->dcd_get_config_tree(fd_ctx->dcd_ctx);
  for(i=0; i < n_cfg; i++, cfg_itr = cfg_itr->next)
  {
    rev = fd_ctx->dev_cfg->audio_rev_arr[i];
    if (fd_ctx->dev_cfg->top_aud_rev == rev)
    {
      USB_LOG_1(log_usb_fd_alloc_bos_des__top_aud_rev_D_sel, rev);
      cfg_priority[0] = cfg_itr;
    }
    else
    {
      switch(rev)
      {
#ifdef USB_ENABLE_UAC30_FLAG
        case USB_AUDIO_CLASS_REV_3:
        {
          cfg_priority[1] = cfg_itr;
        }
        break;
#endif
        case USB_AUDIO_CLASS_REV_2:
        {
          cfg_priority[2] = cfg_itr;
        }
        break;

        case USB_AUDIO_CLASS_BADD3:
        {
          cfg_priority[3] = cfg_itr;
        }
        break;

        case USB_AUDIO_CLASS_REV_1:
        {
          cfg_priority[4] = cfg_itr;
        }
        break;

        default:
          USB_LOG_ERR_1(log_usb_fd_alloc_bos_des__unknown_rev_D, rev);
      }
    }
  }

  // Append separate BOS Config Summary Descriptor per function (USB3.2 spec)
  for(i = 0; i < USB_CONFIG_PRIORITY_SIZE; i++)
  {
    cfg_itr = cfg_priority[i];
    if(cfg_itr)
    {
      // Advertise class, subclass and protocol for each interface alongwith configuration indices it is present in.
      for(ifc_itr = cfg_itr->interfaces; ifc_itr; ifc_itr = ifc_itr->next)
      {
        // Omitt class functions (e.g. HID, DFU, BULK) common to all configurations from config summary descriptor.
        // Advertise only one BOS config summary descriptor per Audio Interface Association.
        if((ifc_itr->descriptor->bAlternateSetting == 0) && (ifc_itr->id == USB_IFC_ID_AUDIO_CONTROL))
        {
          bos->bNumDeviceCaps++;
          bos_cfg_sum = (usb_bos_dev_cap_config_summary_t*) dsc;
          len += sizeof(usb_bos_dev_cap_config_summary_t);
          USB_ASSERT(len < USB_BOS_DESC_SIZE);
          bos_cfg_sum->bLength              = sizeof(usb_bos_dev_cap_config_summary_t);
          bos_cfg_sum->bDescriptorType      = USB_DESCTYPE_DEV_CAP;
          bos_cfg_sum->bDevCapabilityType   = USB_BOS_DEV_CAP_TYPE__CONFIG_SUMMARY;
          bos_cfg_sum->bcdVersion           = 0x100;
          bos_cfg_sum->bClass               = ifc_itr->descriptor->bInterfaceClass;
          bos_cfg_sum->bProtocol            = ifc_itr->descriptor->bInterfaceProtocol;            

          // Reference: UAC3.0 Spec
          // The Audio Function portion of the Configuration Summary descriptor shall contain the 
          // bFunctionClass, bFunctionSubClass, and bFunctionProtocol fields of each AIA contained in 
          // the Configuration being summarized.
          if (ifc_itr->descriptor->bInterfaceProtocol == UAC_IFC_PROTOCOL_VERSION_03_00) 
          {
            // bFunctionSubClass for UAC3.0/BADD3.0 is set to Profile ID.
            //TODO: bos_cfg_sum->bSubClass = (ifc_itr->cs_dsc) ? UAC30_PROFILE_ID_FULL_ADC_3_0 : usb_fn_uac3()->badd3_get_profile_id(fd_ctx->dev_cfg->audio_profile);           
          }
          else
          {
            // bFunctionSubClass for UAC1.0/UAC2.0 is set to zero i.e. Undefined.
            bos_cfg_sum->bSubClass = 0; 
          }

          bos_cfg_sum->bConfigurationCount  = 1;
          bos_cfg_sum->bConfigurationIndex  = cfg_itr->descriptor->bConfigurationValue;
          dsc += sizeof(usb_bos_dev_cap_config_summary_t);
        }
      }
    }
  }

  bos->wTotalLength = len;
  return bos;
}

usb_dcd_dsc_configuration_t* usb_fd_alloc_audio_cfg(usb_fd_ctx_t* fd_ctx, 
  usb_ifc_id* usb_comp, uint8 n_ifc, usb_device_connect_speed_t speed, 
  usb_audio_class_rev_t audio_rev, uint8 config_num)
{
#if 0 //Audio related code.
  usb_dcd_dsc_configuration_t* cfg_ptr = NULL;
  usb_dcd_dsc_interface_t* ifc_itr = NULL; // Keeps track of alternate indexes of an interface
  usb_dcd_dsc_interface_t* ifc_ptr = NULL; // Keep track of interfaces
  usb_ifc_id ifc_id;
  uint8 ep_in_num = 0;
  uint8 ep_out_num = 0;
  uint8 ifc_index;
  uint8* dsc;
  uint16 len = 0;

  USB_ASSERT(usb_comp);
  USB_ASSERT(dsc = (uint8*)usb_fn_mem_util()->usb_malloc(USB_CFG_DESC_SIZE));

  // Allocate configuration descriptor
  cfg_ptr = usb_fn_fd()->usb_fd_create_cfg_desc(&dsc, &len, USB_CFG_DESC_SIZE, config_num, n_ifc);
  cfg_ptr->dcd_ctx = fd_ctx->dcd_ctx;

  // Use set config setup only when operating in mission mode.
  if(fd_ctx->dev_cfg->op_mode == USB_OP_MODE_MISSION)
  {
    cfg_ptr->setup = usb_fn_fd()->usb_fd_set_cfg;
  }

  // For all interfaces within a configuration allocate interfaces and ep descriptors 
  for(ifc_index = 0; ifc_index < n_ifc; ifc_index++)
  {
    ifc_id = usb_comp[ifc_index];

    switch(ifc_id)
    {
      case USB_IFC_ID_BULK:

      case USB_IFC_ID_AUDIO_CONTROL:
      case USB_IFC_ID_AUDIO_STREAMING_MIC:
      case USB_IFC_ID_AUDIO_STREAMING_SPEAKER:

      case USB_IFC_ID_HID:
      case USB_IFC_ID_DFU:
      {
        // allocate interface struct using class API
        void* class_ctx = fd_ctx->ifc_ctx[ifc_index].fn_class.ctx;
        ifc_ptr = fd_ctx->ifc_ctx[ifc_index].fn_class.alloc_desc(&dsc, &len, USB_CFG_DESC_SIZE, 
          class_ctx, ifc_index, &ep_in_num, &ep_out_num, audio_rev);
      }
      break;


      default:
        USB_ULOG(ENG_QLOG, "Unsupported interface type.");
        USB_ASSERT(FALSE);
    }

    // For all alternate settings of the interface populate config ptr and id.
    for(ifc_itr = ifc_ptr; ifc_itr; ifc_itr = ifc_itr->next)
    {
      ifc_itr->configuration = cfg_ptr;
      ifc_itr->id = ifc_id;
    }
    INSERT_TAIL(usb_dcd_dsc_interface, cfg_ptr->interfaces, ifc_ptr);
  }

  cfg_ptr->desc_size = len;
  cfg_ptr->descriptor->wTotalLength = len;
  return cfg_ptr;
#endif
  return NULL;
}

//============================================================================
/**
 * @function    usb_dcd_set_all_transfer_status
 * 
 * @brief   Go through every urb and set the transfer status
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx,
 * @param   (INPUT) uint32 transfer_status: new status
 *
 */
// ===========================================================================
void usb_fd_set_transfer_status(usb_fd_ctx_t* fd_ctx, uint32 transfer_status)
{
  usb_dcd_dsc_configuration_t* config_tree;
  usb_dcd_dsc_interface_t* ifc_ptr;
  uint32 ifc_num;
  uint32 urb_num;

  USB_ASSERT(fd_ctx && fd_ctx->dcd_ctx);
  config_tree = usb_fn_dcd()->dcd_get_config_tree(fd_ctx->dcd_ctx);
  USB_ASSERT(config_tree && config_tree->interfaces);
  
  for(ifc_ptr=config_tree->interfaces; ifc_ptr && ifc_ptr->descriptor; ifc_ptr=ifc_ptr->next)
  {
    ifc_num = ifc_ptr->descriptor->bInterfaceNumber;
    for (urb_num =0; urb_num<USB_URB_MAX; urb_num++)
    {
      fd_ctx->ifc_ctx[ifc_num].rx->urb[urb_num].transfer_status = transfer_status;
    }
  }
}

void usb_fd_init_urb(usb_fd_ctx_t* fd_ctx)
{
  uint8 urb_num;
  uint8 ifc_num;
  usb_dcd_dsc_endpoint_t* ep_ptr;
  usb_dcd_dsc_interface_t* ifc_ptr;
  usb_dcd_dsc_configuration_t* config_tree;
  static usb_urb_t* urb;
  boolean is_tx;

  USB_ASSERT(fd_ctx && fd_ctx->dcd_ctx);
  config_tree = usb_fn_dcd()->dcd_get_config_tree(fd_ctx->dcd_ctx);
  USB_ASSERT(config_tree && config_tree->interfaces);

  for(ifc_ptr = config_tree->interfaces; ifc_ptr && ifc_ptr->descriptor; ifc_ptr = ifc_ptr->next)
  {
    ifc_num = ifc_ptr->descriptor->bInterfaceNumber;
    for(ep_ptr = ifc_ptr->endpoints; ep_ptr && ep_ptr->descriptor; ep_ptr = ep_ptr->next)
    {
      is_tx = ep_ptr->descriptor->bEndpointAddress & 0x80;
      if(is_tx)
      {
        // skip repeat endpoints due to multiple alt settings of an interface.
        if(fd_ctx->ifc_ctx[ifc_num].tx)
        {
          continue;
        }

        USB_ASSERT(fd_ctx->ifc_ctx[ifc_num].tx = (usb_urb_list_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_urb_list_t)));
        fd_ctx->ifc_ctx[ifc_num].tx->idx = 0;
        for(urb_num=0; urb_num < USB_URB_MAX; urb_num++)
        {
          urb                      = &fd_ctx->ifc_ctx[ifc_num].tx->urb[urb_num];
          urb->fd_ctx              = fd_ctx;
          urb->endpoint_address    = ep_ptr->descriptor->bEndpointAddress;
          urb->transfer_buffer_ptr = NULL;
          urb->transfer_length     = 0;
          urb->transfer_status     = 0;
          urb->send_zlp            = TRUE;
          urb->complete_callback   = fd_ctx->api_cb.tx_complete;
        }
      }
      else
      {
        // skip repeat endpoints due to multiple alt settings of an interface.
        if(fd_ctx->ifc_ctx[ifc_num].rx) 
        {
          continue;
        }

        USB_ASSERT(fd_ctx->ifc_ctx[ifc_num].rx = (usb_urb_list_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_urb_list_t)));
        fd_ctx->ifc_ctx[ifc_num].rx->idx = 0;
        for(urb_num=0; urb_num < USB_URB_MAX; urb_num++)
        {        
          /* rx */
          urb                      = &fd_ctx->ifc_ctx[ifc_num].rx->urb[urb_num];
          urb->fd_ctx              = fd_ctx;
          urb->endpoint_address    = ep_ptr->descriptor->bEndpointAddress;
          urb->transfer_buffer_ptr = NULL;
          urb->transfer_length     = 0;
          urb->send_zlp            = FALSE;
          urb->complete_callback   = fd_ctx->api_cb.rx_complete;
          urb->actual_length       = 0;
        }
      }
    }
  }
}

//============================================================================
/**
 * @function    usb_fd_notify
 * 
 * @brief   API fuction pass to dcd for hardware event callback
 * 
 * @note    This API pass to dcd layer, it will trigger when dcd cb for hw event
 *  
 * @param   (INPUT) void* fd_ctx_ptr: 
 *          (INPUT) usb_notify_events_t  event: hw notify event
 *
 * @return None
 */
// ===========================================================================
void usb_fd_notify(void* fd_ctx_ptr, usb_notify_events_t event)
{
  usb_fd_ctx_t* fd_ctx = (usb_fd_ctx_t*)fd_ctx_ptr;

  USB_ASSERT(fd_ctx);
  USB_LOG_DBG_1(log_usb_fd_notify__evt_D, event);

  switch(event)
  {
    case USB_DCD_EVT_CONFIG:
    {
      ifc_ctx_t* ifc_ctx;
      uint8 ifc_index;

      USB_LOG(log_usb_fd_notify__evt_config);

      usb_fn_fd()->usb_fd_init_urb(fd_ctx);

      for(ifc_index = 0; ifc_index < fd_ctx->dev_cfg->usb_comp_num_ifc; ifc_index++)
      {
        ifc_ctx = &fd_ctx->ifc_ctx[ifc_index];
        if (ifc_ctx->fn_class.enum_comp)
        {
          ifc_ctx->fn_class.enum_comp((void*)fd_ctx, ifc_index);
        }
      }


      if (fd_ctx->api_cb.enum_complete != NULL)
      {
        fd_ctx->api_cb.enum_complete(TRUE);
      }
    }
    break;

    case USB_DCD_EVT_UNCONFIG:
    {
      USB_LOG(log_usb_fd_notify__evt_unconfig);
      if (fd_ctx->api_cb.enum_complete != NULL)
      {
        fd_ctx->api_cb.enum_complete(FALSE);
      }
    }
    break;

    case USB_DCD_EVT_SPEED:
    {
      USB_LOG_DBG_1(log_usb_fd_notify__evt_speed_D, usb_fn_dcd()->usb_dcd_get_speed(fd_ctx->dcd_ctx));

      usb_fn_dcd()->usb_dcd_create_desc(fd_ctx->dcd_ctx, fd_ctx->dev_cfg->vendor_id, 
        fd_ctx->dev_cfg->product_id, fd_ctx->dev_cfg->audio_rev_arr_size);
    }
    break;

    case USB_DCD_EVT_ADDRESS:
    {
      usb_dcd_dsc_configuration_t* cfg_tree = NULL;
      usb_dcd_dsc_configuration_t* configurations = NULL;
      usb_device_connect_speed_t speed = usb_fn_dcd()->usb_dcd_get_speed(fd_ctx->dcd_ctx);    
      ifc_ctx_t* ifc_ctx;
      void* class_ctx;
      uint8 ifc_index;
      uint8 i;
      USB_LOG_DBG_1(log_usb_fd_notify__evt_addr_speed_D, speed);

      for(ifc_index = 0; ifc_index < fd_ctx->dev_cfg->usb_comp_num_ifc; ifc_index++)
      {
        ifc_ctx = &fd_ctx->ifc_ctx[ifc_index];
        class_ctx = ifc_ctx->fn_class.ctx;
        if (ifc_ctx->fn_class.notify_speed)
        {
          ifc_ctx->fn_class.notify_speed(speed, class_ctx);
        }
      }
#if 0 //Audio related code.
      if (FALSE == fd_ctx->dsc_init)
      {
        for(i = 0; i < fd_ctx->dev_cfg->audio_rev_arr_size; i++)
        {
          configurations = usb_fn_fd()->usb_fd_alloc_audio_cfg(fd_ctx, fd_ctx->dev_cfg->usb_comp, 
            fd_ctx->dev_cfg->usb_comp_num_ifc, speed, fd_ctx->dev_cfg->audio_rev_arr[i], (i+1));
          INSERT_TAIL(usb_dcd_dsc_configuration, cfg_tree, configurations);
        }
        usb_fn_dcd()->usb_dcd_set_cfg_tree(fd_ctx->dcd_ctx, cfg_tree);
        usb_fn_dcd()->usb_dcd_set_bos(fd_ctx->dcd_ctx, usb_fn_fd()->usb_fd_alloc_bos_desc(fd_ctx));
        fd_ctx->dsc_init= TRUE;
      }
#endif
    }
    break;

    case USB_DCD_EVT_DISCONNECT: 
    {
      USB_LOG(log_usb_fd_notify__evt_disconnect);
      /*Now a disconnect event has occured during the transfer*/ //NOT USE
      if(NULL != fd_ctx->api_cb.error)
      {
        usb_fn_fd()->usb_fd_set_transfer_status(fd_ctx, USB_URB_STATUS_COMPLETE_ERROR);
        fd_ctx->api_cb.error();
      }
    }
    break;
    case USB_DCD_EVT_SUSPEND:
    {
      //FixMe: Sequence to be followed on Suspend
      USB_LOG(log_usb_fd_notify__evt_suspend);      
      fd_ctx->api_cb.notify_suspend(TRUE);
    }
    break;

    default:
    {
      USB_LOG_ERR_1(log_usb_fd_notify__evt_unknown_evt_D, event);
    }
    break;
  }
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
//============================================================================
/**
 * @function    usb_fd_init
 * 
 * @brief   Initialize fd, Should be called prior to any other functions
 * 
 * @note    Need to call after usb_dcd_ctx_alloc,
 *          Should be called prior to any other USB activity
 * @param   
 *          (INPUT/OUTPUT) usb_fd_ctx_t** pass_fd_ctx: pointer to fd_ctx
 *          (INPUT) (*rx_callback): callback for RX_complete
 *          (INPUT) uint8* str_product: Product string name
 *          (INPUT) (*tx_callback): URB completion callback,
 *                   will be called for every successfully transmitted URB
 *          (INPUT) (*enum_complete): Enumeration completion callback, will be
 *                   called after enumeration is complete
 *          (INPUT) (*error_handler): cb for error handle
 *          (INPUT) uint16 product_id: product id
 *          (INPUT) usb_max_speed_required_t speed_required: highest speed require
 *          (INPUT) usb_transfer_mode buffer_mode: which OS mode is usb running
 *                                         (PBL, SBL, MissionMode)
 *          (INPUT) uint32 number_client: number of client support
 *
 * @return  boolean FALSE whne fail, TRUE when success
 */
// ===========================================================================

boolean usb_fd_init(usb_fd_ctx_t** fd_ctx_ptr, usb_api_callback_t api_cb,
  usb_audio_dev_config_t* dev_cfg, usb_max_speed_required_t speed_required)
{
  usb_fd_ctx_t* fd_ctx;
  usb_fd_callback_t fd_cb;
  uint8 ifc_index;
  void* audio_ctrl_ctx = NULL;

  USB_ASSERT(fd_ctx_ptr);
  USB_LOG(log_usb_fd_init);

  if(NULL == dev_cfg)
  {
    USB_ULOG(ENG_QLOG, "unknown device config");
    return FALSE;
  }

  USB_ASSERT(fd_ctx = (usb_fd_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_fd_ctx_t)));
  *fd_ctx_ptr = fd_ctx;

  fd_ctx->api_cb    = api_cb;
  fd_ctx->dev_cfg   = dev_cfg;
  fd_ctx->dsc_init  = FALSE;
  fd_cb.notify      = usb_fn_fd()->usb_fd_notify;
  fd_cb.ctrl_in_cb  = api_cb.ctrl_in_cb;
  fd_cb.ctrl_out_cb = api_cb.ctrl_out_cb;
  fd_cb.set_req_status_comp_cb = usb_fd_set_req_status_comp_cb;
  fd_cb.handle_set_req = usb_fd_handle_set_req;
  fd_cb.handle_get_req = usb_fd_handle_get_req;

  USB_ASSERT(fd_ctx->ifc_ctx = (ifc_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(ifc_ctx_t)* dev_cfg->usb_comp_num_ifc));

  for(ifc_index = 0; ifc_index < fd_ctx->dev_cfg->usb_comp_num_ifc; ifc_index++)
  {
    usb_ifc_id ifc_id = fd_ctx->dev_cfg->usb_comp[ifc_index];
    ifc_ctx_t* ifc_ctx = &fd_ctx->ifc_ctx[ifc_index];
    ifc_ctx->ifc_id = ifc_id;
    ifc_ctx->ifc_num = ifc_index;

    switch(ifc_id)
    {
      case USB_IFC_ID_BULK:
      {
        ifc_ctx->fn_class.init = usb_fn_bulk()->usb_bulk_init;
        ifc_ctx->fn_class.alloc_desc = usb_fn_bulk()->usb_bulk_alloc_desc;
        ifc_ctx->fn_class.set_cfg = usb_fn_bulk()->usb_bulk_set_cfg;
        ifc_ctx->fn_class.notify_speed = usb_fn_bulk()->usb_bulk_notify_speed;
        ifc_ctx->fn_class.deinit = usb_fn_bulk()->usb_bulk_deinit;
        ifc_ctx->fn_class.ctx =  ifc_ctx->fn_class.init(ifc_id, ifc_index, NULL);
      }
      break;

      case USB_IFC_ID_AUDIO_CONTROL:
      {
        usb_audio_ctrl_open_cfg_t* ctrl_open_cfg = 
          (usb_audio_ctrl_open_cfg_t*) fd_ctx->api_cb.get_client_config(ifc_index);
        usb_audio_ctrl_init_cfg_t ctrl_init_cfg;

        ctrl_init_cfg.notify_client = fd_ctx->api_cb.notify;
        ctrl_init_cfg.audio_profile = fd_ctx->dev_cfg->audio_profile;
        ctrl_init_cfg.clock_mode = ctrl_open_cfg->clock_mode;
        ctrl_init_cfg.set_req = ctrl_open_cfg->set_req;
        ctrl_init_cfg.get_req = ctrl_open_cfg->get_req;
        ctrl_init_cfg.mic_type = fd_ctx->dev_cfg->mic_type;

        ifc_ctx->fn_class.init = NULL; //TODO usb_fn_fd_audio()->usb_audio_ctrl_init;
        ifc_ctx->fn_class.alloc_desc = NULL; //TODO usb_fn_fd_audio()->usb_audio_alloc_ac_desc;
        ifc_ctx->fn_class.set_cfg = NULL; //TODO usb_fn_fd_audio()->usb_audio_ctrl_set_cfg;
        ifc_ctx->fn_class.handle_set_req = NULL; //TODO usb_fn_fd_audio()->usb_audio_ctrl_handle_set_req;
        ifc_ctx->fn_class.handle_get_req = NULL; //TODO usb_fn_fd_audio()->usb_audio_ctrl_handle_get_req;
        ifc_ctx->fn_class.deinit = NULL; //TODO usb_fn_fd_audio()->usb_audio_ctrl_deinit;

        audio_ctrl_ctx = ifc_ctx->fn_class.ctx =  ifc_ctx->fn_class.init(ifc_id, ifc_index, 
          &ctrl_init_cfg);
      }
      break;

#if 0
      case USB_IFC_ID_AUDIO_STREAMING_SPEAKER:
      case USB_IFC_ID_AUDIO_STREAMING_MIC:
      {
        usb_audio_stream_open_cfg_t* stream_open_cfg = 
          (usb_audio_stream_open_cfg_t*) fd_ctx->api_cb.get_client_config(ifc_index);
        usb_audio_stream_init_cfg_t init_cfg;
        init_cfg.audio_ctx = audio_ctrl_ctx;

        if(stream_open_cfg)
        {
          init_cfg.as_freq = stream_open_cfg->as_freq;
          init_cfg.as_bus_cfg = &stream_open_cfg->as_bus_cfg[0];
          init_cfg.mic_type = fd_ctx->dev_cfg->mic_type;
          init_cfg.get_expl_fb_freq = stream_open_cfg->get_expl_fb_freq;
        }

        ifc_ctx->fn_class.init = usb_fn_fd_audio()->usb_audio_stream_init;
        ifc_ctx->fn_class.alloc_desc = usb_fn_fd_audio()->usb_audio_alloc_as_desc;
        ifc_ctx->fn_class.notify_speed = usb_fn_fd_audio()->usb_audio_notify_speed;
        ifc_ctx->fn_class.set_cfg = usb_fn_fd_audio()->usb_audio_stream_set_cfg;
        ifc_ctx->fn_class.handle_set_req = usb_fn_fd_audio()->usb_audio_stream_handle_set_req;
        ifc_ctx->fn_class.handle_get_req = usb_fn_fd_audio()->usb_audio_stream_handle_get_req;
        ifc_ctx->fn_class.deinit = usb_fn_fd_audio()->usb_audio_stream_deinit;
        ifc_ctx->fn_class.ctx = ifc_ctx->fn_class.init(ifc_id, ifc_index, &init_cfg);
      }
      break;
  #endif    
      case USB_IFC_ID_HID:
      {
        ifc_ctx->fn_class.init = usb_fn_hid()->usb_hid_init;
        ifc_ctx->fn_class.alloc_desc = usb_fn_hid()->usb_hid_alloc_desc;
        ifc_ctx->fn_class.notify_speed = usb_fn_hid()->usb_hid_notify_speed;
        ifc_ctx->fn_class.set_cfg = usb_fn_hid()->usb_hid_set_cfg;
        ifc_ctx->fn_class.deinit = usb_fn_hid()->usb_hid_deinit;
        ifc_ctx->fn_class.enum_comp = usb_fn_hid()->usb_hid_enum_complete;
        ifc_ctx->fn_class.handle_set_req = usb_fn_hid()->usb_hid_handle_set_req;
        ifc_ctx->fn_class.handle_get_req = usb_fn_hid()->usb_hid_handle_get_req;
        ifc_ctx->fn_class.ctx =  ifc_ctx->fn_class.init(ifc_id, ifc_index, 0);
      }
      break;

      case USB_IFC_ID_DFU:
      {
        usb_dfu_open_cfg_t* dfu_open_cfg = 
          (usb_dfu_open_cfg_t*) fd_ctx->api_cb.get_client_config(ifc_index);
        usb_dfu_init_cfg_t dfu_init_cfg;
        dfu_init_cfg.op_mode = fd_ctx->dev_cfg->op_mode;
        dfu_init_cfg.dn_cb = dfu_open_cfg->dn_cb;
        dfu_init_cfg.up_cb = dfu_open_cfg->up_cb;
        dfu_init_cfg.notify = fd_ctx->api_cb.notify;

        ifc_ctx->fn_class.init = usb_fn_dfu()->usb_dfu_init;
        ifc_ctx->fn_class.alloc_desc = usb_fn_dfu()->usb_dfu_alloc_desc;
        ifc_ctx->fn_class.notify_speed = usb_fn_dfu()->usb_dfu_notify_speed;
        ifc_ctx->fn_class.set_cfg = usb_fn_dfu()->usb_dfu_set_cfg;
        ifc_ctx->fn_class.deinit = usb_fn_dfu()->usb_dfu_deinit;
        ifc_ctx->fn_class.handle_set_req = usb_fn_dfu()->usb_dfu_handle_set_req;
        ifc_ctx->fn_class.set_req_status_comp_cb = usb_fn_dfu()->usb_dfu_set_req_status_comp_cb;
        ifc_ctx->fn_class.handle_get_req = usb_fn_dfu()->usb_dfu_handle_get_req;
        ifc_ctx->fn_class.ctx =  ifc_ctx->fn_class.init(ifc_id, ifc_index, (void*) &dfu_init_cfg);
      }
      break;

      default:
        USB_LOG_ERR_1(log_usb_fd_init__unknown_ifc_id_D, ifc_id);
    }
  }

  if(FALSE == usb_fn_dcd()->usb_dcd_init(speed_required, &fd_ctx->dcd_ctx, fd_ctx, fd_cb,  
    fd_ctx->dev_cfg->lang_id, fd_ctx->dev_cfg->manuf_str, fd_ctx->dev_cfg->product_str, fd_ctx->dev_cfg->feature_flags))
  {
    return NULL;
  }

  usb_fn_dcd()->usb_dcd_set_core(fd_ctx->dcd_ctx, USB_CORE_SNPS);

  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_fd_shutdown
 * 
 * @brief   This function performs a shutdown for all ctx of usb.
 *
 * @note: need to shutdown hardware (i.e. usb_snps_shutdown) 
 *        before trigger this function. 
 *        This function will clean up all the memory for usb.
 *        USB can still monitor vbus event after this
 * 
 * @param   (INPUT) usb_fd_ctx_t* fd_ctx: pointer to fd_ctx.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_fd_shutdown(usb_fd_ctx_t** fd_ctx_ptr)
{
  usb_fd_ctx_t* fd_ctx = *fd_ctx_ptr;
  uint8 ifc_index;
  ifc_ctx_t* ifc_ctx;
  void* class_ctx;

  USB_ASSERT(fd_ctx);

  usb_fn_dcd()->usb_dcd_shutdown(&fd_ctx->dcd_ctx);

  for(ifc_index = 0; ifc_index < fd_ctx->dev_cfg->usb_comp_num_ifc; ifc_index++)
  {
    ifc_ctx = &fd_ctx->ifc_ctx[ifc_index];
    class_ctx = ifc_ctx->fn_class.ctx;
    if (ifc_ctx->fn_class.deinit)
    {
      ifc_ctx->fn_class.deinit(class_ctx);
    }

    if (ifc_ctx->rx)
    {
      usb_fn_mem_util()->usb_free((void**)&ifc_ctx->rx);
    }

    if (ifc_ctx->tx)
    {
      usb_fn_mem_util()->usb_free((void**)&ifc_ctx->tx);
    }
  }

  if (fd_ctx->ifc_ctx)
  {
    usb_fn_mem_util()->usb_free((void**)&fd_ctx->ifc_ctx);
  }

  usb_fn_mem_util()->usb_free((void**)fd_ctx_ptr);
}

// ===========================================================================
/**
 * @function    usb_fd_tx_pkt
 * 
 * @brief   Pass through function to dcd layer
 *
 * @details convert the data pkt to urb and sumbit to hardware
 *
 * @param   (INPUT) usb_fd_ctx_t* fd_ctx: pointer to fd_ctx.
 *          (INPUT) unsigned char *pkt: package to transmite pointer 
 *          (INPUT) uint32 len: length of the package 
 *          (INPUT) uint32 req_id: Debug purpose, the index of buffer to be send
 *          (INPUT) uint32 client_id: Client unique ID
 *          (INPUT) void* cb_data: client private data pointer
 *
 * @return  error_msg
 */
// ===========================================================================
uint32 usb_fd_tx_pkt(usb_fd_ctx_t* fd_ctx, unsigned char *pkt, uint32 len, uint32 req_id, 
  uint32 client_id, void* cb_data)
{
  usb_urb_list_t* tx;
  usb_urb_t* urb;

  if ((NULL == fd_ctx) || (NULL == fd_ctx->ifc_ctx))
  {
    USB_LOG_ERR_1(log_usb_fd_tx_pkt__null_ptr_client_id_D, client_id);
    return USB_ERR_BAD_PARAM;
  }

  tx = fd_ctx->ifc_ctx[client_id].tx;
  USB_ASSERT(tx);

  urb = &tx->urb[tx->idx];
  USB_ASSERT(urb);

  USB_LOG_DBG_1(log_usb_fd_tx_pkt__len_D, len);  
  if ( USB_URB_STATUS_ACTIVE == urb->transfer_status ) 
  {
    USB_ULOG_3(DBG_E_QLOG, "overflow, client_id %u, urb %u, req_id %u", 
      (uint32) client_id, (uint32) urb, (uint32) req_id);
    USB_LOG_ERR_1(log_usb_fd_tx_pkt__urb_active__client_D, client_id);
    return USB_ERR_OVERFLOW;
  }

  // In most case, we should be able avoid memcpy 
  urb->transfer_buffer_ptr = pkt;
  urb->transfer_length = len;
  urb->req_id = req_id;
  urb->client_id = client_id;
  urb->cb_data = cb_data;

  USB_ULOG_3(ENG_QLOG, "URB_FD client_id %u, urb %u, urb_idx %u", 
    (uint32) client_id, (uint32) urb, (uint32) tx->idx);

  // Send URB
  if (USB_SUCCESS == usb_fn_dcd()->usb_dcd_submit_urb(fd_ctx->dcd_ctx, urb))
  {   
    tx->idx = ((tx->idx)+1)%USB_URB_MAX;
    return USB_SUCCESS;
  }

  USB_ULOG_3(DBG_E_QLOG, "write_error, client_id %u, urb %u, req_id %u", 
    (uint32) client_id, (uint32) urb, (uint32) req_id);
  USB_LOG_ERR_1(log_usb_fd_tx_pkt__trans_error_client_D, client_id);  
  return USB_ERR_WRITE;
}


uint32 usb_fd_hid_report(usb_fd_ctx_t* fd_ctx, usb_hid_bitmask_cmd_t report_mask, uint32 client_id)
{
   usb_fn_hid()->usb_hid_tx((void*) fd_ctx, client_id, report_mask); 
   return 0;
}

// ===========================================================================
/**
 * @function    usb_fd_rx_pkt
 * 
 * @brief   submit rx buffer to hardware
 *
 * @details convert the data pkt to urb and sumbit to hardware
 *
 * @param   (INPUT) usb_fd_ctx_t* fd_ctx: pointer to fd_ctx.
 *          (INPUT) void *buff_ptr: package buffer pointer to recieve
 *          (INPUT) uint32 len: length of the max package to recieve 
 *          (INPUT) uint32 req_id: Debug purpose, the index of buffer to be send
 *          (INPUT) uint32 client_id: Client unique ID
 *          (INPUT) void* cb_data: client private data pointer
 *
 * @return  error_msg
 */
// ===========================================================================
uint32 usb_fd_rx_pkt(usb_fd_ctx_t* fd_ctx, void *buff_ptr, uint32 len, uint32 req_id, 
  uint32 client_id, void* cb_data)
{
  usb_urb_list_t* rx;
  usb_urb_t* urb;

  if ((NULL == fd_ctx) || (NULL == fd_ctx->dcd_ctx) || (NULL == fd_ctx->ifc_ctx))
  {
    USB_LOG_ERR_1(log_usb_fd_rx_pkt__null_ptr_client_id_D, client_id);
    return USB_ERR_BAD_PARAM;
  }

  rx = fd_ctx->ifc_ctx[client_id].rx;
  USB_ASSERT(rx);

  urb = &rx->urb[rx->idx];
  USB_ASSERT(urb);

  // handle previously active RX transfers 
  if (USB_URB_STATUS_ACTIVE == urb->transfer_status)
  {
    USB_ULOG_3(DBG_E_QLOG, "overflow, client_id %u, urb 0x%X, req_id %u", 
      (uint32) client_id, (uint32) (urb), (uint32) req_id);
    USB_LOG_ERR_1(log_usb_fd_rx_pkt__urb_active__client_id_D, client_id);    
    return USB_ERR_OVERFLOW;
  }

  urb->req_id = req_id;
  urb->client_id = client_id;
  urb->cb_data = cb_data;
  urb->transfer_buffer_ptr = buff_ptr;
  urb->transfer_length = len;

  USB_LOG_DBG_1(log_usb_fd_rx_pkt__len_D,len);
  USB_ULOG_3(ENG_QLOG, "fd_urb client_id %u, urb %u, urb_idx %u", 
        (uint32) client_id, (uint32) urb, (uint32) rx->idx);


  // Send URB
  if (USB_SUCCESS == usb_fn_dcd()->usb_dcd_submit_urb(fd_ctx->dcd_ctx, urb))
  {
    rx->idx = ((rx->idx)+1)%USB_URB_MAX;
    return USB_SUCCESS;
  }

  USB_ULOG_3(DBG_E_QLOG, "read_error, client_id %u, urb %u, req_id %u", 
    (uint32) client_id, (uint32) urb, (uint32) req_id);
  USB_LOG_ERR_1(log_usb_fd_rx_pkt__tran_error_client_D, client_id);
  return USB_ERR_READ;
}

uint32 usb_fd_cancel_transfer(usb_fd_ctx_t* fd_ctx, uint32 client_id)
{
  uint32 err_tx = 0;

  err_tx = usb_fn_fd()->usb_fd_cancel_transfer_dir(fd_ctx, client_id, DIR_TX);
  if(err_tx)
  {
    USB_ULOG_1(BUS_QLOG, "err_tx %u", (uint32)err_tx);
    return USB_ERR_DEFAULT;
  }

  //the only way this function will fail is null_ptr, which already check in TX
  // so no need to check in RX again
  usb_fn_fd()->usb_fd_cancel_transfer_dir(fd_ctx, client_id, DIR_RX);

  return USB_SUCCESS;
}

uint32 usb_fd_cancel_transfer_dir(usb_fd_ctx_t* fd_ctx, uint32 client_id, uint8 dir)
{
  uint8 urb_idx;
  usb_urb_list_t* urb_list_ptr;
  usb_urb_t* urb_ptr;
  uint32 err = USB_SUCCESS;

  if ((NULL == fd_ctx->dcd_ctx) || (NULL == fd_ctx->ifc_ctx))
  {
    USB_LOG_ERR_1(log_usb_fd_cancel_transfer_dir__client_D_not_open, client_id);
    return USB_ERR_NULL_PTR;
  }

  if (dir == DIR_TX)
  {
    urb_list_ptr = fd_ctx->ifc_ctx[client_id].tx;
  }
  else
  {
    urb_list_ptr = fd_ctx->ifc_ctx[client_id].rx;
  }

  if(urb_list_ptr)
  {
    urb_list_ptr->idx = 0;
    for(urb_idx = 0; urb_idx < USB_URB_MAX; urb_idx++)
    {
      urb_ptr = &urb_list_ptr->urb[urb_idx];
      if (urb_ptr->transfer_status == USB_URB_STATUS_ACTIVE)
      {
        USB_ULOG_2(BUS_QLOG, "client id %u, tx_urb 0x%X",(uint32)client_id, (uint32) urb_ptr);
        err = usb_fn_dcd()->usb_dcd_cancel_transfer(fd_ctx->dcd_ctx, urb_ptr);
        USB_ERR_HALT_LOG((0 == err), log_usb_fd_cancel_transfer_dir__cancel_failed);
        break;
      }
    }
  }

  return err;
}


//============================================================================
/**
  PASS THROUGH FUNCTION TO DCI
*/
// ===========================================================================

//============================================================================
/**
 * @function    usb_fd_poll
 * 
 * @brief   Pass through function to dcd layer
 * @param   (INPUT) usb_fd_ctx_t* fd_ctx
 *
 * @return  None
 */
// ===========================================================================
void usb_fd_poll(usb_fd_ctx_t* fd_ctx)
{
  if (NULL != fd_ctx) 
  {
    usb_fn_dcd()->usb_dcd_poll(fd_ctx->dcd_ctx);
  }
}

//============================================================================
/**
 * @function    usb_fd_reset
 * 
 * @brief   Pass through function to dcd layer
 * @param   (INPUT) usb_fd_ctx_t* fd_ctx
 *
 * @return  None
 */
// ===========================================================================
void usb_fd_reset(usb_fd_ctx_t* fd_ctx)
{
  if (NULL != fd_ctx) 
  {
    usb_fn_dcd()->usb_dcd_reset(fd_ctx->dcd_ctx);;
  }
}

// ===========================================================================
/**
 * @function    usb_fd_get_max_packet_size
 * 
 * @brief    Pass through function to dcd layer
 * 
 * @param  (INPUT) usb_fd_ctx_t* fd_ctx
 * @return  uint32 max packet_size.
 * 
 */
// ===========================================================================
uint32 usb_fd_get_max_packet_size(usb_fd_ctx_t* fd_ctx)
{
  if (NULL != fd_ctx) 
  {
    return usb_fn_dcd()->usb_dcd_get_max_packet_size(fd_ctx->dcd_ctx);
  }
  return 0;
}

// ===========================================================================
/**
 * @function    usb_fd_get_speed
 * 
 * @brief   Pass through function to dcd layer.
 *
 * @details This function return current speed
 * 
 * @param   (input) usb_fd_ctx_t* fd_ctx.
 * 
 * @return   usb_device_connect_speed_t current_speed.
 * 
 */
// ===========================================================================
usb_device_connect_speed_t usb_fd_get_speed(usb_fd_ctx_t* fd_ctx)
{
  if (NULL != fd_ctx) 
  {
    return usb_fn_dcd()->usb_dcd_get_speed(fd_ctx->dcd_ctx);
  }
  return USB_UNKNOWN_SPEED;
}

// ===========================================================================
/**
 * @function    usb_fd_get_dci_ctx
 * 
 * @brief    Pass through function to dcd layer
 * 
 * @param  (INPUT) usb_fd_ctx_t* fd_ctx
 * @return  pointer to dci_ctx
 * 
 */
// ===========================================================================
void* usb_fd_get_dci_ctx(usb_fd_ctx_t* fd_ctx)
{
  if (NULL != fd_ctx) 
  {
    return usb_fn_dcd()->usb_dcd_get_dci_ctx(fd_ctx->dcd_ctx);
  }
  return NULL;
}

// ===========================================================================
/**
 * @function    usb_fd_set_core
 * 
 * @brief   Pass through function to dcd layer.
 * 
 * @details This function set usb core.
 * 
 * @param   (INPUT) usb_fd_ctx_t* fd_ctx
 *          (INPUT) usb_core_type core_id: core_id
 * 
 * @return  none
 * 
 */
// ===========================================================================
void usb_fd_set_core(usb_fd_ctx_t* fd_ctx, usb_core_type core_id)
{
  USB_LOG_DBG_1(log_usb_fd_set_core__id_D, core_id);
  //for synopsys controller, make sure that the correct core_id is set
  if (core_id >= USB_CORE_MAXX)
  {
    USB_LOG_ERR_1(log_usb_fd_set_core__wrong_id_D, core_id);
  }
  else
  {
    USB_ASSERT(fd_ctx);
    usb_fn_dcd()->usb_dcd_set_core(fd_ctx->dcd_ctx, core_id);
  }
}

// ===========================================================================
/**
 * @function    usb_fd_is_usb_configured
 * 
 * @brief   Pass through function to dcd layer.
 *
 * @details This function return boolean if usb is configured
 * 
 * @param   (input) usb_fd_ctx_t* fd_ctx.
 * 
 * @return  boolean TRUE if usb is configured.
 * 
 */
// ===========================================================================
boolean usb_fd_is_usb_configured(usb_fd_ctx_t* fd_ctx)
{
  if (NULL != fd_ctx)
  {
    return usb_fn_dcd()->usb_dcd_is_usb_configured(fd_ctx->dcd_ctx);
  }
  return FALSE;
}

/*----------------------------------------------------------------------------
 * Function table definitions - FD layer
 * -------------------------------------------------------------------------*/

usb_fn_tbl_fd_t fn_tbl_fd = 
{
  usb_fd_alloc_ep_comp_desc,
  usb_fd_alloc_ep_desc,
  usb_fd_alloc_ifc_desc,
  usb_fd_create_cfg_desc,
  usb_fd_set_cfg,
  usb_fd_set_req_status_comp_cb,
  usb_fd_handle_set_req,
  usb_fd_handle_get_req,
  usb_fd_alloc_bos_desc,
  usb_fd_alloc_audio_cfg,
  usb_fd_set_transfer_status,
  usb_fd_init_urb,
  usb_fd_notify,
  usb_fd_init,
  usb_fd_shutdown,
  usb_fd_tx_pkt,
  usb_fd_hid_report,
  usb_fd_rx_pkt,
  usb_fd_cancel_transfer,
  usb_fd_cancel_transfer_dir,
  usb_fd_poll,
  usb_fd_reset,
  usb_fd_get_max_packet_size,
  usb_fd_get_speed,
  usb_fd_get_dci_ctx,
  usb_fd_set_core,
  usb_fd_is_usb_configured,
};
