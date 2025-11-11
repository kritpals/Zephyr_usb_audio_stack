/*=======================================================================*//**
  @file         usb_dcd.c

  @brief        Device controller driver functionality

  @details      
 
                Copyright (c) 2008-2018 Qualcomm Technologies, Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
*//*========================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dcd/usb_dcd.c#5 $$DateTime: 2018/07/17 15:45:47 $$Author: pwbldsvc $

  when        who       what, where, why
  ----------  ---       ------------------------------------------------------
  2009-04-17  dhaval    Ported from VU_CORE_WIREDCONNECTIVITY_USB.00.00.08 
                        Disable ZLT for Rx endpoints. This way, long transfer 
                        will be split into several dTD's by hardware.	
  2009-03-17  dhaval    Removed compiler warnings.
  2007-08-14  vkondrat  check device state prior to transfer
  2007-08-10  vkondrat  Initial revision.

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "usb_dcd.h"
#include "usb_class_dcd.h"
#include "usb_dci.h"

#include "usb_log.h"
#include "usb_dcd_ch9.h"
#include "usb_util.h"

// Xtensa header removed for Zephyr port
// #include <xtensa/core-macros.h>
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

#define USB_LANG_ID_EN_US   (0x0409)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
static uint8 str0[4] = {
  sizeof(str0),USB_DESCTYPE_STRING,
  0x09,0x04,                            // langid : US_EN
};
  
static const uint8 usb_product_str[34] = { // iProduct
  sizeof(usb_product_str),
  USB_DESCTYPE_STRING,
  'U',0,
  'S',0,
  'B',0,
  ' ',0,
  'A',0,
  'u',0,
  'd',0,
  'i',0,
  'o',0,
  ' ',0,
  'D',0,
  'e',0,
  'v',0,
  'i',0,
  'c',0,
  'e',0,
};
  
static uint8 usb_manuf_str[54] = { // iManufacturer
  sizeof(usb_manuf_str),USB_DESCTYPE_STRING,
  'Q',0,
  'u',0,
  'a',0,
  'l',0,
  'c',0,
  'o',0,
  'm',0,
  'm',0,
  ' ',0,
  'T',0,
  'e',0,
  'c',0,
  'h',0,
  'n',0,
  'o',0,
  'l',0,
  'o',0,
  'g',0,
  'i',0,
  'e',0,
  's',0,
  ' ',0,
  'I',0,
  'n',0,
  'c',0,
  '.',0,
};

static const uint8 str_serial[34] = { // iSerialNumber
  sizeof(str_serial),USB_DESCTYPE_STRING,
  '1',0,
  '2',0,
  '3',0,
  '4',0,
  '5',0,
  '6',0,
  '7',0,
  '8',0,
  '9',0,
  '0',0,
  'A',0,
  'B',0,
  'C',0,
  'D',0,
  'E',0,
  'F',0,
};

//============================================================================
/**
 * @function    usb_dcd_desc_max_packet_size
 * 
 * @brief   API is used to max packet size for descriptor base on speed
 * 
 * @note    Quartz create dynamic descriptor when host request descriptor.
 *  
 * @param   (INPUT) usb_device_connect_speed_t speed: max desc_speed
 *
 * @return  uint32 max_packet_size
 */
// ===========================================================================
uint32 usb_dcd_desc_max_packet_size(usb_device_connect_speed_t speed)
{
  return (speed == USB_SUPER_SPEED) ? 1024: 512;
}
  
//============================================================================
/**
 * @function    usb_dcd_create_dev_desc
 * 
 * @brief   API is used to allocate and init dev descriptor
 * 
 * @note    Quartz create dynamic descriptor when host request descriptor.
 * 
 * @param   (OUTPUT) usb_desc_device_t** dev_desc: output of create_dev_descriptor
 *          (INPUT) uint16 product_id
 *
 * @return  None
 */
// ===========================================================================  
void usb_dcd_create_dev_desc(usb_desc_device_t** dev_desc, uint16 vendor_id,
  uint16 product_id, usb_device_connect_speed_t speed, usb_max_speed_required_t speed_required,
  uint8 n_cfg)
{
  usb_desc_device_t* dev_desc_ptr;
  USB_ASSERT(dev_desc_ptr = (usb_desc_device_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_desc_device_t)));
  
  // Initialize device descriptor
  dev_desc_ptr->bLength             = sizeof(usb_desc_device_t);
  dev_desc_ptr->bDescriptorType     = USB_DESCTYPE_DEVICE;
  
  if(speed == USB_SUPER_SPEED)
  {
    dev_desc_ptr->bcdUSB = USB_BCD_USB3;
    dev_desc_ptr->bMaxPacketSize0 = USB_EP0_MAX_PACKET_SIZE_SUPER_BMAX0;
  } 
  else if (speed == USB_HIGH_SPEED)
  {
    //For Bolt target we always support LPM which require USB2_EXT
    dev_desc_ptr->bcdUSB = USB_BCD_USB2_EXT;
    dev_desc_ptr->bMaxPacketSize0 = USB_EP0_MAX_PACKET_SIZE_HIGH;    
  }
  else
  {
    //For Bolt target we always support LPM which require USB2_EXT
    dev_desc_ptr->bcdUSB = USB_BCD_USB2_EXT;
    dev_desc_ptr->bMaxPacketSize0 = USB_EP0_MAX_PACKET_SIZE_FULL;    
  }

  dev_desc_ptr->bDeviceClass        = 0;
  dev_desc_ptr->bDeviceSubClass     = 0;
  dev_desc_ptr->bDeviceProtocol     = 0;
  dev_desc_ptr->idVendor            = vendor_id;
  dev_desc_ptr->idProduct           = product_id;
  dev_desc_ptr->bcdDevice           = 0x0;
  dev_desc_ptr->iManufacturer       = 1;
  dev_desc_ptr->iProduct            = 2;
  dev_desc_ptr->iSerialNumber       = 0;
  dev_desc_ptr->bNumConfigurations  = n_cfg;

  *dev_desc = dev_desc_ptr;
}

//============================================================================
/**
 * @function    usb_dcd_create_dev_qual_desc
 * 
 * @brief   API is used to allocate and init dev qual descriptor
 * 
 * @note    Quartz create dynamic descriptor when host request descriptor.
 * 
 * @param   (OUTPUT) usb_desc_device_t** dev_qual_desc: output of create_dev_descriptor
 * 
 * @return  None
 */
// ===========================================================================    
void usb_dcd_create_dev_qual_desc(usb_desc_dev_qual_t** dev_qual_desc)
{
  usb_desc_dev_qual_t* dev_qual_desc_ptr;
  USB_ASSERT(dev_qual_desc_ptr = (usb_desc_dev_qual_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_desc_dev_qual_t)));

  dev_qual_desc_ptr->bLength             = sizeof(usb_desc_dev_qual_t);
  dev_qual_desc_ptr->bDescriptorType     = USB_DESCTYPE_DEV_QUAL;
  dev_qual_desc_ptr->bcdUSB              = USB_BCD_USB2_EXT;
  dev_qual_desc_ptr->bDeviceClass        = 0;
  dev_qual_desc_ptr->bDeviceSubClass     = 0;
  dev_qual_desc_ptr->bDeviceProtocol     = 0;
  dev_qual_desc_ptr->bMaxPacketSize0     = 64;
  dev_qual_desc_ptr->bNumConfigurations  = 1;

  *dev_qual_desc = dev_qual_desc_ptr;
}

//============================================================================
/**
 * @function    usb_dcd_allocate_dev_qual
 * 
 * @brief   API is used to allocate dev qual descriptor
 * 
 * @note    
 * 
 * @param   (OUTPUT) usb_desc_device_t** dev_qual_desc: output of create_dev_descriptor
 * 
 * @return  None
 */
// ===========================================================================    
void usb_dcd_allocate_dev_qual(usb_dcd_dsc_qual_t** dev_qual)
{
  usb_dcd_dsc_qual_t* dev_qual_ptr;
  USB_ASSERT(dev_qual_ptr = (usb_dcd_dsc_qual_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_dsc_qual_t)));

  dev_qual_ptr->next = NULL;
  usb_fn_dcd()->usb_dcd_create_dev_qual_desc(&dev_qual_ptr->descriptor);

  *dev_qual = dev_qual_ptr;
}

//============================================================================
/**
 * @function    usb_dcd_allocate_strings
 * 
 * @brief   API is used to alloc string desc pts
 * 
 * @note    
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *          (OUTPUT) usb_dcd_dsc_string_t** strings: output of create_dev_descriptor
 *          (INPUT)  uint8* str_product: pointer to string array
 *
 * @return  None
 */
// ===========================================================================  
void usb_dcd_allocate_strings(usb_dcd_ctx_t* dcd_ctx, uint16 lang_id, 
  uint8* manuf_str, uint8* product_str)
{
  uint16 langid = (lang_id) ? lang_id : USB_LANG_ID_EN_US;

  *((uint16*)&str0[2]) = langid;

  dcd_ctx->strings[USB_STR_IDX_LANG_ID].descriptor = (usb_desc_header_t*) &str0;
  dcd_ctx->strings[USB_STR_IDX_LANG_ID].langid = 0;

  if(manuf_str)
  {
    dcd_ctx->strings[USB_STR_IDX_MANUF].descriptor = (usb_desc_header_t*) manuf_str;
  }
  else
  {
    dcd_ctx->strings[USB_STR_IDX_MANUF].descriptor = (usb_desc_header_t*) &usb_manuf_str;
  }
  dcd_ctx->strings[USB_STR_IDX_MANUF].langid = langid;

  if(product_str)
  {
    dcd_ctx->strings[USB_STR_IDX_PRODUCT].descriptor = (usb_desc_header_t*) product_str;
  }
  else
  {
    dcd_ctx->strings[USB_STR_IDX_PRODUCT].descriptor = (usb_desc_header_t*) &usb_product_str;
  }
  dcd_ctx->strings[USB_STR_IDX_PRODUCT].langid = langid;

  dcd_ctx->strings[USB_STR_IDX_SERIAL_NUM].descriptor = (usb_desc_header_t*) &str_serial;
  dcd_ctx->strings[USB_STR_IDX_SERIAL_NUM].langid = langid;
}

//============================================================================
/**
 * @function    usb_dcd_create_ep_comp_desc
 * 
 * @brief   API is used to create ep comp desc
 * 
 * @note    
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *          (OUTPUT)usb_ep_comp_desc_t** ep_comp_ptr: output of create_dev_descriptor
 *          (INPUT)  uint8 burst_size: burst size
 *          (INPUT)  uint8 attr: bmAttributes
 *          (INPUT)  uint8 bpi: byte per interval
 *
 * @return  None
 */
// ===========================================================================
void usb_dcd_create_ep_comp_desc(usb_ep_comp_desc_t** ep_comp_ptr, uint8 burst_size, 
  uint8 attr, uint8 bpi)
{
  usb_ep_comp_desc_t* ep_comp; 
  USB_ASSERT(ep_comp = (usb_ep_comp_desc_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_ep_comp_desc_t)));
  ep_comp->bLength           = sizeof(usb_ep_comp_desc_t);
  ep_comp->bDescriptorType   = USB_DESCTYPE_EP_COMP;
  ep_comp->bMaxBurst         = burst_size;
  ep_comp->bmAttributes      = attr;
  ep_comp->wBytesPerInterval = bpi;
  *ep_comp_ptr = ep_comp;
}

//============================================================================
/**
 * @function    usb_dcd_create_ep_desc
 * 
 * @brief   API is used to create ep comp desc
 * 
 * @note    
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *          (OUTPUT)usb_dcd_dsc_endpoint_t** endpoint: output of endpoint desc pointer
 *          (INPUT)  uint8 ep_num: ep_num
 *          (INPUT)  uint8 ep_mask: mask to go with ep_num
 *          (INPUT)  uint8 ep_attr: byte per interval
 *          (INPUT)  uint8 ep_interval:
 *          (INPUT)  uint16 max_packet_size
 * @return  None
 */
// ===========================================================================
void usb_dcd_create_ep_desc(usb_dcd_dsc_endpoint_t** endpoint, uint8 ep_num, uint8 ep_mask,
  uint8 ep_attr, uint8 ep_interval, uint16 max_packet_size)
{
  usb_dcd_dsc_endpoint_t* ep_ptr;
  usb_desc_endpoint_t* ep;

  USB_ASSERT(ep_ptr = (usb_dcd_dsc_endpoint_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_dsc_endpoint_t)));
  USB_ASSERT(ep = (usb_desc_endpoint_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_desc_endpoint_t)));

  ep->bLength            = sizeof(usb_desc_endpoint_t);
  ep->bDescriptorType    = USB_DESCTYPE_ENDPOINT;
  ep->wMaxPacketSize     = max_packet_size;
  ep->bEndpointAddress   = ep_num | ep_mask;
  ep->bmAttributes       = ep_attr;
  ep->bInterval          = ep_interval;

  // Assign descriptor ptr
  ep_ptr->descriptor = ep;
  *endpoint = ep_ptr;
}

//============================================================================
/**
 * @function    usb_dcd_create_ifc_desc
 * 
 * @brief   API is used to create interface desc
 * 
 * @note    
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *          (OUTPUT)usb_dcd_dsc_interface_t** interface: output of interface desc pointer
 *          (INPUT)  uint8 ifc_index: interface number
 *          (INPUT)  uint8 alt_setting: alt setting for interface
 *          (INPUT)  uint8 n_ep: number of ep in the interface
 *          (INPUT)  uint8 ifc_class: 
 *          (INPUT)  uint8 subclass:
 *          (INPUT)  uint8 protocol
 *          (INPUT)  uint8 str_index
 * @return  None
 */
// ===========================================================================
void usb_dcd_create_ifc_desc(usb_dcd_dsc_interface_t** interface, uint8 ifc_index, 
  uint8 alt_setting, uint8 n_ep, uint8 ifc_class, uint8 subclass, uint8 protocol, uint8 str_index)
{
  usb_dcd_dsc_interface_t* ifc_ptr;
  usb_desc_interface_t* ifc;
  USB_ASSERT(ifc_ptr = (usb_dcd_dsc_interface_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_dsc_interface_t)));
  USB_ASSERT(ifc = (usb_desc_interface_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_desc_interface_t)));

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
  *interface = ifc_ptr;
}

//============================================================================
/**
 * @function    dcd_get_config_tree
 * 
 * @brief   API is used to to get configuration tree togther.
 * 
 * @note    Quartz create dynamic descriptor when host request descriptor.
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx : dcd layer context
 *
 * @return  pointer to configurations tree
 *
 */
// ===========================================================================
usb_dcd_dsc_configuration_t* dcd_get_config_tree(const usb_dcd_ctx_t* dcd_ctx) 
{
  return dcd_ctx->configurations;
}

//============================================================================
/**
 * @function    dcd_get_config_value
 * 
 * @brief   API is used to to get value of current configuration.
 * 
 * @note    create dynamic descriptor when host request descriptor.
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx : dcd layer context
 *
 * @return  pointer to configurations tree
 *
 */
// ===========================================================================
int dcd_get_config_value(const usb_dcd_ctx_t* dcd_ctx)
{
  return dcd_ctx->config_value;
}


//============================================================================
 /**
 * @function    find_config_by_value
 * 
 * @brief   Find config by configuration value
 * 
 * @note    
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx               : pointer to all config
 *          (INPUT) uint8 value: configure value
 *
 * @return  usb_dcd_dsc_configuration_t
 */
// ===========================================================================
usb_dcd_dsc_configuration_t* find_config_by_value(const usb_dcd_ctx_t* dcd_ctx, uint8 value)
{
  usb_dcd_dsc_configuration_t* config_itr = dcd_ctx->configurations;
  for(config_itr = dcd_ctx->configurations; config_itr; config_itr = config_itr->next)
  {
    if (config_itr->descriptor->bConfigurationValue == value)
    {
      return config_itr;
    }
  }
  return NULL;
}

//============================================================================
 /**
 * @function    get_curr_ifc_alt_set
 * 
 * @brief   Find interface configuration with current alt setting 
 *          by interface number
 * 
 * @note    
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx               : pointer to all config
 *          (INPUT) uint8 ifc_num: interface number
 *
 * @return  usb_dcd_dsc_interface_t
 */
// ===========================================================================
usb_dcd_dsc_interface_t* get_curr_ifc_alt_set(const usb_dcd_ctx_t* dcd_ctx, uint8 ifc_num)
{
  usb_dcd_dsc_interface_t* ifc_ptr;
  if (dcd_ctx->active_configuration != NULL)
  {
    for(ifc_ptr=dcd_ctx->active_configuration->interfaces; (ifc_ptr); ifc_ptr=ifc_ptr->next)
    {
      if(ifc_ptr->descriptor->bInterfaceNumber == ifc_num)
      {
        if(ifc_ptr->current_altsetting == ifc_ptr->descriptor->bAlternateSetting)
        {
          return ifc_ptr;
        }
      }
    }
  }
  USB_LOG_ERR_1(log_get_curr_ifc_alt_set__ifc_D, ifc_num);
  return NULL;
}


//============================================================================
 /**
 * @function    usb_dcd_find_ep
 * 
 * @brief   Find ep configuration by ep_addr
 * 
 * @note   * search strategy: 
 *          - go to current configuration 
 *          - iterate over interfaces 
 *          - look fo current altsetting
 *          - iterate over endpoints
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: pointer to all config
 *          (INPUT) uint8 ep_address: ep_addr
 *
 * @return EP software descriptor,
 *         NULL if not found
 */
// ===========================================================================
usb_dcd_dsc_endpoint_t* usb_dcd_find_ep(const usb_dcd_ctx_t* dcd_ctx, uint16 ep_address)
{
  usb_dcd_dsc_interface_t*ifc_ptr;
  usb_dcd_dsc_endpoint_t* ep_ptr;

  if((dcd_ctx->active_configuration == NULL) || (dcd_ctx->active_configuration->interfaces == NULL))
  {
    USB_LOG_ERR(log_usb_dcd_find_ep__null_active_config);
    return NULL;
  }

  for(ifc_ptr=dcd_ctx->active_configuration->interfaces ;(ifc_ptr); ifc_ptr=ifc_ptr->next)
  {
    for(ep_ptr=ifc_ptr->endpoints; ep_ptr && ep_ptr->descriptor; ep_ptr=ep_ptr->next)
    {
      if(ep_address == ep_ptr->descriptor->bEndpointAddress)
      {
        return ep_ptr;
      }
    }
  }

  return NULL;
}

//============================================================================
 /**
 * @function    find_string
 * 
 * @brief   Find des string pointer
 * 
 * @note   
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: pointer to all config
 *          (INPUT) uint16 lang: lang_id
 *          (INPUT) uint8 index: config_idx 
 *
 * @return device string pointer,
 *         NULL if not found
 */
// ===========================================================================
usb_desc_header_t* get_string_desc(const usb_dcd_ctx_t* dcd_ctx, uint16 lang_id, uint8 index)
{
  if(index == USB_STR_IDX_LANG_ID)
  {
    return dcd_ctx->strings[index].descriptor;
  }

  if((index > USB_STR_IDX_LANG_ID) && (index < USB_STR_IDX_MAX) && (lang_id == dcd_ctx->strings[index].langid))
  {
    return dcd_ctx->strings[index].descriptor;
  }

  return NULL;
}

//============================================================================
 /**
  * @function    usb_dcd_fd_notify
  * 
  * @brief   Trigger fd_notify_Cb
  * 
  * @note   
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: pointer for fd_cb
  *          (INPUT) usb_notify_events_t event: notify_event
  *
  * @return None
  *
  */
// ===========================================================================
void usb_dcd_fd_notify(usb_dcd_ctx_t* dcd_ctx, usb_notify_events_t event)
{
  USB_LOG_DBG_1(log_usb_dcd_fd_notify__event_D, event);
  if ( NULL != dcd_ctx->fd_cb.notify )
  {
    dcd_ctx->fd_cb.notify(dcd_ctx->fd_ctx, event);
  }
  else
  {
    USB_LOG_ERR(log_usb_dcd_fd_notify__null_fd_cb_notify);
  }
}

//============================================================================
 /**
  * @function    usb_dcd_set_interface
  * 
  * @brief   Set alternate setting for given interface
  * 
  * @note    
  *          2 path:
  *          - 1-st to make sure correct ifc/alt exist;
  *          - 2-nd to set correct alt for all ifc's with given index
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: pointer for fd_cb
  *          (INPUT) uint8 ifc_num: Interface number
  *          (INPUT) uint8 alt: alt number
  *
  * @return error code:
  *         - 0 if OK
  *         - negative if error
  */
// ===========================================================================
int usb_dcd_set_interface(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_interface_t* ifc, uint8 ifc_num, uint8 alt)
{
  usb_dcd_dsc_interface_t* new_ifc = NULL;
  USB_ASSERT(ifc  && ifc->descriptor);

  while(ifc)
  {
    if (ifc->descriptor->bInterfaceNumber == ifc_num )
    {
      if (ifc->descriptor->bAlternateSetting == alt)
      {
        new_ifc = ifc;
      }
      ifc->current_altsetting = alt;
    }
    ifc= ifc->next;
  }
  
  if (NULL == new_ifc)
  {
    USB_LOG_ERR_2(log_usb_dcd_set_interface__failed_to_set_ifc_D_alt_set_D, ifc_num, alt);
    return -1;
  }
  
  USB_LOG_2(log_usb_dcd_set_interface__ifc_num_D_alt_set_D, ifc_num, alt);

  if ( ( new_ifc->descriptor->bInterfaceNumber == ifc_num ) && 
      ( new_ifc->descriptor->bAlternateSetting == alt ) ) 
  {
    usb_dcd_dsc_endpoint_t* ep;
    
    for ( ep = new_ifc->endpoints; ep != NULL; ep = ep->next ) 
    {
      usb_dcd_ctx_t* dcd_ctx = new_ifc->configuration->dcd_ctx;
      usb_desc_endpoint_t* dsc = ep->descriptor;

      if(dsc != NULL)
      {
        uint8 is_ep_in = (uint8)(!!(dsc->bEndpointAddress & 0x80));
        uint8 ep_int = 0;

        if ((dcd_ctx->speed == USB_HIGH_SPEED) || (dcd_ctx->speed == USB_SUPER_SPEED))
        {
          ep_int = dsc->bInterval - 1;
        }

        // Special case for UAC1.0 
        // Use bRefresh instead of bInterval as service interval
        if (ep->cs_dsc && (dsc->bmAttributes & 0xF) == (USB_EP_ATTR_SYNC_NONE | USB_EP_ATTR_ISOCH))
        {        
          uint8 b_refresh;
          uint16 usb_frame_us;
          usb_frame_us = (dcd_ctx->speed == USB_HIGH_SPEED) ? 125 : 1000;
          b_refresh = *ep->cs_dsc;
          for(ep_int = 0; (usb_frame_us << ep_int) != ( (1 << b_refresh) * 1000); ep_int++);
        }

        usb_fn_dci()->usb_dci_config_endpoint(dcd_ctx->dci_ctx, (uint8)(dsc->bEndpointAddress & 0xf), is_ep_in,
          (uint8)(dsc->bmAttributes & 0x3), ep_int, dsc->wMaxPacketSize, 0); 
      }
      // Ifc has EP's but no desc, we should STALL 
      else
      {
        USB_LOG_ERR(log_usb_dcd_set_interface__null_ep_dsc);
        return -1;
      }
    }
      return 0;
  }
  return -1;
}

//============================================================================
 /**
  * @function    usb_dcd_set_config
  * 
  * @brief   Set new configuration value, as if SET_CONFIG was received.
  * 
  * @note    
  *          Use to configure device to run with 
  *          already defined configuration value.
  *          It assumes enumeration has already been done and
  *          host issued SET_CONFIG before USB stack initialized.
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) uint8 new_config: new config
  *
  * @return error code:
  *         - 0 if OK
  *         - negative if error
  */
// ===========================================================================
int usb_dcd_set_config(usb_dcd_ctx_t* dcd_ctx, uint8 new_config)
{
  //It is illegal to change configuration from one non-0 to
  //another
  usb_dcd_dsc_interface_t* ifc_ptr;
  USB_LOG_1( log_usb_dcd_set_config__new_config_D, new_config);
  if ( ( 0 != dcd_ctx->config_value ) && 
        ( 0 != new_config ) && 
        ( new_config != dcd_ctx->config_value )  ) 
  {
    return -1;
  }
  if ( new_config != dcd_ctx->config_value ) 
  {
    if ( new_config != 0 ) 
    {
      usb_dcd_dsc_configuration_t* conf = usb_fn_dcd()->find_config_by_value(dcd_ctx, new_config);
      if ( NULL == conf ) 
      { 
        /* requested configuration do not exist */
        return -1;
      }

      // Do not perform set interface operation for single enumeration use case.
      for(ifc_ptr=conf->interfaces; (ifc_ptr); ifc_ptr=ifc_ptr->next)
      {
        if(ifc_ptr->descriptor->bAlternateSetting == 0) 
        {
          if ( usb_fn_dcd()->usb_dcd_set_interface(dcd_ctx, ifc_ptr, ifc_ptr->descriptor->bInterfaceNumber, 0) < 0 ) 
          {
            return -1;
          }
        }
      }

      /* apply changes */
      if(conf->setup) 
      {
        conf->setup(conf, NULL);
      }
      dcd_ctx->config_value = new_config;
      dcd_ctx->active_configuration = conf;
      dcd_ctx->usb_is_configured = TRUE;
      usb_fn_dcd()->usb_dcd_fd_notify(dcd_ctx, USB_DCD_EVT_CONFIG);

    }
    else 
    {
      dcd_ctx->config_value = 0;
      dcd_ctx->active_configuration = NULL;
      //  unconfigure all EP's
      //  
      //  Accordingly to USB standard, device may contain up to 16
      //  EP's in each direction. EP0 is control EP and is handled
      //  separately (by DCI) , thus not mentioned here
      {
        uint8 ep;

        for(ep = 1; ep < DCI_MAX_ENDPOINTS; ep++) 
        {
          usb_fn_dci()->usb_dci_cancel_transfer(dcd_ctx->dci_ctx, ep,USB_EP_DIR_RX);
          usb_fn_dci()->usb_dci_unconfig_endpoint(ep,USB_EP_DIR_RX);
          usb_fn_dci()->usb_dci_cancel_transfer(dcd_ctx->dci_ctx, ep,USB_EP_DIR_TX);
          usb_fn_dci()->usb_dci_unconfig_endpoint(ep,USB_EP_DIR_TX);
        }
      }
      dcd_ctx->usb_is_configured = FALSE;
    }
  }

  // update the packet size after determining the speed    
  usb_fn_dci()->usb_dci_update_packet_size(dcd_ctx->dci_ctx);

  return 0;
}

//============================================================================
 /**
  * @function    usb_dcd_control_transfer
  * 
  * @brief   Initiate control transfer, Used in custom SETUP flow.
  * 
  * @note    
  *          Use to configure device to run with 
  *          already defined configuration value.
  *          It assumes enumeration has already been done and
  *          host issued SET_CONFIG before USB_ stack initialized.
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) int is_tx: 1 if Tx, 0 if Rx
  *          (INPUT) void* buff:buffer to transmit;
  *                             should not be modified till transmit completion.
  *          (INPUT) uint32 len:    number of bytes to transmit
  * @return number of bytes transferred; or negative error code
  */
// ===========================================================================
int usb_dcd_control_transfer(usb_dcd_ctx_t* dcd_ctx, int is_tx, void* buff, uint32 len)
{
  int rc = -1;
  usb_urb_t* urb = is_tx ? &dcd_ctx->ctrl_urb.tx : &dcd_ctx->ctrl_urb.rx;

  USB_LOG_DBG_2( log_usb_dcd_control_transfer__is_tx_D_len_D, is_tx, len);

  if (urb && (USB_URB_STATUS_ACTIVE != urb->transfer_status))
  {
    urb->transfer_buffer_ptr = buff;
    urb->transfer_length = len;
    rc = usb_fn_dcd()->usb_dcd_submit_urb(dcd_ctx, urb);
  }

  return rc < 0 ? rc : (int)len;
}

//============================================================================
 /**
  * @function    usb_dcd_control_reply
  * 
  * @brief   Initiate Tx transfer using dev->setup_status
  * 
  * @note    
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) uint32 len: Transfer length
  *
  * @return number of bytes transferred; or negative error code
  */
// ===========================================================================
int usb_dcd_control_reply(usb_dcd_ctx_t* dcd_ctx, uint32 len)
{
  return usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx,DIR_TX,dcd_ctx->setup_status,len);
}

//============================================================================
 /**
  * @function    handle_get_descriptor
  * 
  * @brief   Handle setup_dev: USB_SETUP_REQ_GET_DESCRIPTOR
  * 
  * @note    
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) usb_setup_packet_t* req: req buffer
  *          (INPUT) usb_ep_dir_t ctrl_data_dir: transmit direction
  *
  * @return number of bytes transferred; or negative error code
  */
// ===========================================================================
int handle_get_descriptor(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, 
  usb_ep_dir_t ctrl_data_dir)
{
  PACKED struct dsc_struct
  {
    uint8 desc_index;
    uint8 desc_type;
  } PACKED_POST;
  struct dsc_struct* dsc = (struct dsc_struct*)(void*)(&req->wValue);
  void* buff = NULL;
  int len = -1;

  switch ( dsc->desc_type ) 
  {
    case USB_DESCTYPE_DEVICE:
      
      buff = (void*)dcd_ctx->descriptor;
      if(buff == NULL)
      {
        USB_LOG_ERR(log_handle_get_descriptor__dev_dsc_null);
      }
      else
      {
        len = dcd_ctx->descriptor->bLength;
      }
      USB_LOG_DBG_1(log_handle_get_descriptor__dev_dsc_len_D, len);
    break;
    
    case USB_DESCTYPE_CONFIGURATION:
    {
      uint8 index = (req->wValue & 0xFF);
      uint8 value = index + 1; // config value is index+1
      usb_dcd_dsc_configuration_t* config;
      config = usb_fn_dcd()->find_config_by_value(dcd_ctx, value);
      
      if (NULL == config)
      {
        USB_LOG_ERR(log_handle_get_descriptor__config_null);
        return -1;
      }
      buff = (void*)config->descriptor;
      if(buff == NULL)
      {
        USB_LOG_ERR(log_handle_get_descriptor__config_dsc_null);
      }
      else
      {
        len = config->descriptor->wTotalLength;
        //To reduce memory, other speed configuration use the same as normal config
        // so we change bDescriptorType when host ask other descriptor
        // and this will fix it back when host request normal one again
        config->descriptor->bDescriptorType = USB_DESCTYPE_CONFIGURATION; 
      }
      USB_LOG_DBG_1(log_handle_get_descriptor__config_dsc_len_D, len);
    }
    break;
    
    case USB_DESCTYPE_BOS:
    {
      if(dcd_ctx->descriptor->bcdUSB > USB_BCD_USB2)
      {
        if(dcd_ctx->bos_descriptor)
        {
          buff = (void*)dcd_ctx->bos_descriptor;
          if(buff == NULL)
          {
            USB_LOG_ERR(log_handle_get_descriptor__bos_dsc_null);
          }
          else
          {
            len = dcd_ctx->bos_descriptor->wTotalLength;
          }
        }
      }
      USB_LOG_DBG_1(log_handle_get_descriptor__bos_dsc_len_D, len);
    }
    break;

    case USB_DESCTYPE_STRING:
    {
      usb_desc_header_t* str = usb_fn_dcd()->get_string_desc(dcd_ctx, req->wIndex, dsc->desc_index);
      buff = str;
      if(buff == NULL)
      {
        USB_LOG_ERR(log_handle_get_descriptor__string_dsc_null);
      }
      else
      {
        len = str->bLength;
      }
      USB_LOG_DBG_1(log_handle_get_descriptor__string_dsc_index_D, req->wIndex);
    }
    break;
    
    case USB_DESCTYPE_DEV_QUAL:
    {
      if(dcd_ctx->speed < USB_SUPER_SPEED)
      {
        buff = (void *)dcd_ctx->dev_qual->descriptor;
        if(buff == NULL)
        {
          USB_LOG_ERR(log_handle_get_descriptor__devqual_dsc_null);
        }
        else
        {
          len = dcd_ctx->dev_qual->descriptor->bLength;
        }
        USB_LOG_DBG_1(log_handle_get_descriptor__devqual_dsc_len_D, len);
      }
    }
    break;

    case USB_DESCTYPE_OTH_SPEED:
    {
      usb_dcd_dsc_configuration_t* config = dcd_ctx->other_speed_configuration;
      
      if (NULL == config)
      {
        return -1;
      }

      buff = (void*)config->descriptor;
      if(buff == NULL)
      {
        USB_LOG_ERR(log_handle_get_descriptor__other_speed_config_dsc_null);
      }
      else
      {
      len = config->descriptor->wTotalLength;
      //To reduce memory, other speed configuration use the same as normal config
      // so we fake the bDescriptorType to pass ch9 test
      config->descriptor->bDescriptorType = USB_DESCTYPE_OTH_SPEED; 
      USB_LOG_DBG_1(log_handle_get_descriptor__other_speed_config_dsc_len_D, len);
      }
    }
    break;

    case USB_DESCTYPE_HID_REPORT:
    {
      //Routing the request to class specific (Only for REPORT DESCRIPTOR)
      USB_LOG_DBG_1(log_handle_get_descriptor__get_hid_report_dsc_wval_D, req->wValue);
      len = usb_fn_dcd()->usb_dcd_handle_setup_class(dcd_ctx, req);
    }
    break;

    default:
      USB_LOG_ERR_1(log_handle_get_descriptor__unknown_dsc_type_D, dsc->desc_type);

  }

  if((len >= 0) && (buff != NULL))
  {
    if(len > req->wLength)
    {
      len = req->wLength;
    }

    /* send it */
    return usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, buff, (uint32)len);
  }

  return len;
}


//============================================================================
 /**
  * @function    handle_setup_dev
  * 
  * @brief   Handle setup_dev
  * 
  * @note    
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) usb_setup_packet_t* req: req buffer
  *          (INPUT) usb_ep_dir_t ctrl_data_dir: transmit direction
  *
  * @return number of bytes transferred; or negative error code
  */
// ===========================================================================
int handle_setup_dev(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir)
{
  int error =0x0;
  switch ( req->bRequest )
  {
    case USB_SETUP_REQ_GET_STATUS:
      if ( req->wLength >= 2 ) 
      {  /* USB standard expects 2 bytes here */
        memset(dcd_ctx->setup_data, 0, USB_MAX_CTRL_PKT_SIZE);

        if(dcd_ctx->speed == USB_SUPER_SPEED)
        {
          dcd_ctx->setup_data[0] = DEV_BUS_PWRD;
          if (dcd_ctx->u1_enabled) dcd_ctx->setup_data[0] |= U1_ENABLE;
          if (dcd_ctx->u2_enabled) dcd_ctx->setup_data[0] |= U2_ENABLE;
        }
        else
        {
          dcd_ctx->setup_data[0]= (usb_fn_dci()->usb_dci_is_remote_wakeup_enabled(dcd_ctx->dci_ctx) << 1);
          /* bit 0 - is_self_powered */
          /* bit 1 - is_remote_wakeup */
        }
        USB_LOG_DBG_1(log_handle_setup_dev__get_status_D, dcd_ctx->setup_data[0]);
        return usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, 2);
      }
    break;
    
    case USB_SETUP_REQ_CLEAR_FEATURE:
      if (req->wValue == USB_FSEL_DEV_REMOTE_WAKEUP)
      {
        usb_fn_dci()->usb_dci_handle_remote_wakeup_enabled(dcd_ctx->dci_ctx, FALSE);
      } 
      else if (req->wValue == USB_FSEL_DEV_TEST_MODE)
      {
        // Disable test mode in HW after STATUS stage (ACK) is sent to host successfully.
        usb_fn_dci()->usb_dci_test_mode_enable(dcd_ctx->dci_ctx, FALSE, USB_PORT_TEST_DISABLE);
      }
      else if ( (req->wValue == USB_FSEL_U1_ENABLE) && (dcd_ctx->usb_is_configured == TRUE))
      {
        dcd_ctx->u1_enabled = FALSE;
        usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U1_INIT_ENABLE, FALSE);
      }
      else if ((req->wValue == USB_FSEL_U2_ENABLE) && (dcd_ctx->usb_is_configured == TRUE))
      {
        dcd_ctx->u2_enabled = FALSE;
        usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U2_INIT_ENABLE, FALSE);
      }
      else
      {
        error = -1;   
      }
      USB_LOG_DBG_1(log_handle_setup_dev__clear_feature_D, req->wValue);
      return error;

    case USB_SETUP_REQ_SET_FEATURE:
      if (req->wValue == USB_FSEL_DEV_TEST_MODE)
      {
        usb_fn_dci()->usb_dci_test_mode_enable(dcd_ctx->dci_ctx, TRUE,((req->wIndex & 0x0f00) >> 8));
      }
      else if (req->wValue == USB_FSEL_DEV_REMOTE_WAKEUP)
      {
        usb_fn_dci()->usb_dci_handle_remote_wakeup_enabled(dcd_ctx->dci_ctx, TRUE);
      }
      else if ((req->wValue == USB_FSEL_U1_ENABLE) && (dcd_ctx->usb_is_configured == TRUE))
      { 
        dcd_ctx->u1_enabled = TRUE;
        usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U1_INIT_ENABLE, TRUE);
      }
      else if ((req->wValue == USB_FSEL_U2_ENABLE) && (dcd_ctx->usb_is_configured == TRUE))
      {  
        dcd_ctx->u2_enabled = TRUE;
        usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U2_INIT_ENABLE, TRUE);
      }
      else
      {
        error = -1;
      }
      USB_LOG_DBG_1(log_handle_setup_dev__set_feature_D, req->wValue);
      return error;

    case USB_SETUP_REQ_SET_ADDRESS:
      if ( 0 == dcd_ctx->config_value )
      {
        uint8 addr = (uint8)(req->wValue & 0xff);
        dcd_ctx->address = addr;
        usb_fn_dci()->usb_dci_set_address(dcd_ctx->address);
        USB_LOG_1( log_handle_setup_dev__set_address_D, dcd_ctx->address);
        usb_fn_dcd()->usb_dcd_fd_notify(dcd_ctx, USB_DCD_EVT_ADDRESS);
        return 0;
      }
    break;
    
    case USB_SETUP_REQ_SET_SEL:
      if ( req->wLength == 6 )
      {
        usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, req->wLength);
        USB_LOG_1( log_handle_setup_dev__set_sel_D, req->wLength);
        usb_fn_dci()->usb_dci_handle_set_select(dcd_ctx->dci_ctx);
        return 0;
      }
    break;
    
    case USB_SETUP_REQ_SET_ISOCH_DELAY:
      /* We are not updating any data here, we Just return Success ( For CV )*/
      USB_LOG_DBG(log_handle_setup_dev__set_isoch_delay);
      return 0;

    case USB_SETUP_REQ_GET_DESCRIPTOR:
      USB_LOG_DBG(log_handle_setup_dev__get_descriptor);
      return usb_fn_dcd()->handle_get_descriptor(dcd_ctx, req, ctrl_data_dir);
    
    case USB_SETUP_REQ_SET_DESCRIPTOR:
      USB_LOG(log_handle_setup_dev__set_descriptor);
      /* not supported (yet?) */
    break;
  
    case USB_SETUP_REQ_GET_CONFIGURATION:
      if ( req->wLength >= 1 ) 
      { /* USB standard expects 1 byte here */
        dcd_ctx->setup_data[0] = dcd_ctx->config_value;
        USB_LOG_DBG_1(log_handle_setup_dev__get_config_D, dcd_ctx->setup_data[0]);
        error = usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, 1);
        return error;
      }
    break;
    
    case USB_SETUP_REQ_SET_CONFIGURATION:
      USB_LOG_1( log_handle_setup_dev__set_config_D, (uint8)(req->wValue & 0xff));
      error = usb_fn_dcd()->usb_dcd_set_config(dcd_ctx, (uint8)(req->wValue & 0xff));
      /* Allow device to accept U1 and U2 at this point (as per SNPS spec. Table6-57:DCTL) */
      usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U1_U2_ACCPET_ENABLE, TRUE);
      return error;
    
    default:
    if ( NULL != dcd_ctx->setup )
    {
      USB_LOG_ERR_1(log_handle_setup_dev__unknown_req_D, req->bRequest);
      return dcd_ctx->setup(dcd_ctx, req);
    }
    break;
  }
  return -1;
}

//============================================================================
 /**
  * @function    handle_setup_ifc
  * 
  * @brief   Handle setup: for interface
  * 
  * @note    
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) usb_setup_packet_t* req: req buffer
  *          (INPUT) usb_ep_dir_t ctrl_data_dir: transmit direction
  *
  * @return number of bytes transferred; or negative error code
  */
// ===========================================================================
int handle_setup_ifc(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir)
{
  int error =0x0;
  uint8 ifc_num = (uint8)(req->wIndex & 0xff);
  uint8 alt_set = (uint8)(req->wValue & 0xff);
  usb_dcd_dsc_interface_t* ifc = usb_fn_dcd()->get_curr_ifc_alt_set(dcd_ctx, ifc_num);

  switch ( req->bRequest )
  {
    case USB_SETUP_REQ_GET_STATUS:
      if ( ifc && req->wLength >= 2 ) 
      { /* USB standard expects 2 bytes here */
        memset(dcd_ctx->setup_data, 0, USB_MAX_CTRL_PKT_SIZE);
        if(dcd_ctx->speed == USB_SUPER_SPEED)
        {
          if(usb_fn_dci()->usb_dci_is_remote_wakeup_enabled(dcd_ctx->dci_ctx) == TRUE)
          {
            dcd_ctx->setup_data[0] |= FUNC_REMOTE_WAKEUP_CAP |FUNC_REMOTE_WAKEUP;
          }
          else
          {
            dcd_ctx->setup_data[0] |= FUNC_REMOTE_WAKEUP_CAP;
          }
        }
        USB_LOG_1( log_handle_setup_ifc__req_get_status_D, dcd_ctx->setup_data[0]);
        error = usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, 2);
        return error;
      }
    break;
    
    case USB_SETUP_REQ_CLEAR_FEATURE:
      USB_LOG(log_handle_setup_ifc__req_clear_feature);
    break;
  
    case USB_SETUP_REQ_SET_FEATURE:
      if (req->wValue == USB_FSEL_IFACE_FUNC_SUSP)
      {
        usb_fn_dci()->usb_dci_handle_remote_wakeup_enabled(dcd_ctx->dci_ctx, 
          (( req->wIndex & 0x200 ) ? TRUE :FALSE));

        USB_LOG_1( log_handle_setup_ifc__req_set_feature_remote_wakeup_D, 
          usb_fn_dci()->usb_dci_is_remote_wakeup_enabled(dcd_ctx->dci_ctx));  

        return 0;
      }
      else
      {
        return -1;
      }

    case USB_SETUP_REQ_GET_INTERFACE:
      if ( ( ifc != NULL ) && ( req->wLength >= 1 ) ) 
      { 
        /* USB standard expects 1 byte here */
        /* usb_setup_data is already assigned to dev->setup_data */
        memset((void*)dcd_ctx->setup_data, 0, USB_MAX_CTRL_PKT_SIZE);
        dcd_ctx->setup_data[0] = ifc->current_altsetting;
        USB_LOG_DBG_1(log_handle_setup_ifc__req_get_interface_curr_alt_set_D, dcd_ctx->setup_data[0]);
        error = usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, 1);
        return error;
      }
    break;
  
    case USB_SETUP_REQ_SET_INTERFACE:
    /* ifc as found above, is irrelevant */
    {
      usb_dcd_dsc_configuration_t* conf = dcd_ctx->active_configuration;
      if(conf && conf->interfaces)
      {
        USB_LOG_2(log_handle_setup_ifc__req_set_interface_ifc_num_D_alt_set_D, ifc_num, alt_set);

        error = usb_fn_dcd()->usb_dcd_set_interface(dcd_ctx, conf->interfaces,ifc_num, alt_set);
        usb_dcd_dsc_interface_t* ifc = usb_fn_dcd()->get_curr_ifc_alt_set(dcd_ctx, ifc_num);

        if (ifc && ifc->setup)
        {
          ifc->setup(ifc,req);
        }
        return error;
      }
    }
    break;
  
  case USB_SETUP_REQ_GET_DESCRIPTOR:
  {
    uint8 desc_type;
    desc_type = (req->wValue >> 8);
    if ((desc_type == USB_DESCTYPE_HID) || (desc_type == USB_DESCTYPE_HID_REPORT))
    {
      //Routing the request to class specific (Only for REPORT DESCRIPTOR)
      USB_LOG(log_handle_setup_ifc__req_get_hid_class_desc);
      error = usb_fn_dcd()->usb_dcd_handle_setup_class(dcd_ctx, req);
      return error;
    }
  }
  break;

  default:
    if ( ( NULL != ifc ) && ( NULL != ifc->setup ) ) 
    {
      USB_LOG_ERR_1(log_handle_setup_ifc__unknown_req_D, req->bRequest);
      return ifc->setup(ifc, req);
    }
    break;
  }
  return -1;
}

//============================================================================
 /**
  * @function    handle_ep_halt
  * 
  * @brief   Handle ep halt
  * 
  * @note    
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) usb_dcd_dsc_endpoint_t* ep: ep to halt
  *          (INPUT) int halt: to tall on unstall ep
  *
  * @return 0 success, -1 fail
  */
// ===========================================================================
int handle_ep_halt(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_endpoint_t* ep, int halt)
{
  uint8 ep_num;
  boolean is_tx;

  if(ep->descriptor == NULL)
  {
    USB_LOG_ERR(log_handle_ep_halt__null_ptr);
    return -1;
  }

  ep_num = ep->descriptor->bEndpointAddress & 0x0f;
  is_tx = (ep->descriptor->bEndpointAddress & 0x80)? TRUE:FALSE;
  ep->is_halt = halt;

  USB_LOG_1( log_handle_ep_halt__ep_D, ep_num);

  if ( halt != 0 ) 
  {
    usb_fn_dci()->usb_dci_stall_endpoint(dcd_ctx->dci_ctx, ep_num, is_tx);
  } 
  else 
  {
    usb_fn_dci()->usb_dci_unstall_endpoint(dcd_ctx->dci_ctx, ep_num, is_tx);
  }
  return 0;
}

//============================================================================
 /**
  * @function    handle_setup_ep
  * 
  * @brief   Handle ep setup
  * 
  * @note    
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) usb_setup_packet_t* req: req buffer
  *          (INPUT) usb_ep_dir_t ctrl_data_dir: transmit direction
  *
  * @return number of bytes transferred; or negative error code
  */
// ===========================================================================
int handle_setup_ep(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req, usb_ep_dir_t ctrl_data_dir)
{
  int error = -1;
  usb_dcd_dsc_endpoint_t* ep = usb_fn_dcd()->usb_dcd_find_ep(dcd_ctx, req->wIndex);

  // Request is not valid for  ep=0=NULL and req->wIndex != ep when the device is  configured 
  if ( (NULL == ep) && (dcd_ctx->config_value != 0) && (req->wIndex != 0))
  {
    return error;
  }

  switch ( req->bRequest )
  {
    case USB_SETUP_REQ_GET_STATUS:
      if ( req->wLength >= 2 ) 
      {
        if(dcd_ctx->setup_data)
        {
          memset(dcd_ctx->setup_data, 0, USB_MAX_CTRL_PKT_SIZE);
          /*For Ep=0, we send zero for GET_STATUS*/

          if((req->wIndex != 0) && (ep != NULL) )
          {
            dcd_ctx->setup_data[0] = ep->is_halt;
          }

          USB_LOG_DBG_1(log_handle_setup_ep__get_status_D, dcd_ctx->setup_data[0]);
          error = usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, ctrl_data_dir, dcd_ctx->setup_data, 2);
        }
        return error;
      }
    break;
    
    case USB_SETUP_REQ_CLEAR_FEATURE:
      switch ( req->wValue )
      { /* feature selector */
        case USB_FSEL_EP_HALT:
          if(NULL != ep)
          {
            USB_LOG_DBG_1(log_handle_setup_ep__clear_feature_D, (uint8)(req->wValue & 0xff));
            return usb_fn_dcd()->handle_ep_halt(dcd_ctx, ep, 0);
          }
          else
          {
            USB_LOG_ERR_1(log_handle_setup_ep__null_ep_line_D, __LINE__);
          }
        default:
          return error;
      }
  
    case USB_SETUP_REQ_SET_FEATURE:
      switch ( req->wValue )
      { /* feature selector */
        case USB_FSEL_EP_HALT:
        if(NULL != ep)
        {
          USB_LOG_DBG_1(log_handle_setup_ep__set_feature_D, (uint8)(req->wValue & 0xff));
          return usb_fn_dcd()->handle_ep_halt(dcd_ctx, ep, 1);
        }
        else
        {
          USB_LOG_ERR_1(log_handle_setup_ep__null_ep_line_D, __LINE__);
        }    
        default:
          return error;
      }
  
    case USB_SETUP_REQ_SYNCH_FRAME:
      USB_LOG_DBG(log_handle_setup_ep__req_synch_frame);
    break;

    default:
      if ( (NULL != ep) && (NULL != ep->setup) )
      {
        USB_LOG_DBG_1(log_handle_setup_ep__call_handler_D, req->bRequest );
        return ep->setup(ep, req);
      }
      else
      {
        USB_LOG_ERR_1(log_handle_setup_ep__null_ep_line_D, __LINE__);
      }
    break;
  }
   return error;
}

int handle_setup_std(usb_dcd_ctx_t* dcd_ctx, usb_setup_packet_t* req)
{
  int data_out_len = -1;
  uint8 bm_req_recp = ((req->bmRequestType & USB_SETUP_RT_RCP_MASK) >> USB_SETUP_RT_RCP_POS);
  uint8 bm_req_dir = (req->wLength == 0) ? DIR_NONE : ((req->bmRequestType & USB_SETUP_RT_DIR_MASK) >> USB_SETUP_RT_DIR_POS);

  switch( bm_req_recp )
  {
    case USB_SETUP_RT_RCP_DEV:
    {
      data_out_len = usb_fn_dcd()->handle_setup_dev(dcd_ctx, req, (usb_ep_dir_t)bm_req_dir);
    }
    break;
  
    case USB_SETUP_RT_RCP_IFC:
    {
      data_out_len = usb_fn_dcd()->handle_setup_ifc(dcd_ctx, req, (usb_ep_dir_t)bm_req_dir);
    }
    break;
  
    case USB_SETUP_RT_RCP_EP:
    {
      data_out_len = usb_fn_dcd()->handle_setup_ep(dcd_ctx, req, (usb_ep_dir_t)bm_req_dir);
    }
    break;
  
    default:
      USB_LOG_ERR_1(log_handle_setup_std__unsupported_D, bm_req_recp);      
  }

  return data_out_len;

}

//============================================================================
 /**
  * @function    usb_dcd_handle_reset
  * 
  * @brief   Handle reset notification from DCI
  * 
  * @note    callbacks for DCI
  *          Reset moves USB device to 'default' state
  *          It means not configured and address == 0
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *
  * @return None
  */
// ===========================================================================
void usb_dcd_handle_reset(usb_dcd_ctx_t* dcd_ctx)
{

  USB_LOG(log_usb_dcd_handle_reset);
  usb_fn_dcd()->usb_dcd_set_config(dcd_ctx, 0);
  dcd_ctx->address = 0;
  usb_fn_dci()->usb_dci_set_address(dcd_ctx->address);

  /** 
  *  reset EP0 software state
  *  
  *  Hardware has reset EP0 transfers, reflect this in software.
  */
  dcd_ctx->ctrl_urb.rx.transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
  dcd_ctx->ctrl_urb.tx.transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
  dcd_ctx->usb_is_configured = FALSE;

  dcd_ctx->u1_enabled = FALSE;
  dcd_ctx->u2_enabled = FALSE;
}

//============================================================================
 /**
  * @function    usb_dcd_handle_disconnect
  * 
  * @brief   Handle disconnect notification from DCI
  * 
  * @note    callbacks for DCI
  *          pass callback to fd
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *
  * @return None
  */
// ===========================================================================
void usb_dcd_handle_disconnect(usb_dcd_ctx_t* dcd_ctx)
{
  dcd_ctx->speed = USB_UNKNOWN_SPEED;
  USB_LOG(log_usb_dcd_handle_disconnect);
  usb_fn_dcd()->usb_dcd_fd_notify(dcd_ctx,USB_DCD_EVT_DISCONNECT);
}

//============================================================================
 /**
  * @function    usb_dcd_handle_suspend
  * 
  * @brief   Handle suspend notification from DCI
  * 
  * @note    callbacks for DCI
  *          trigger dci_remote wakeup
  *          pass callback to fd
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *
  * @return None
  */
// ===========================================================================
void usb_dcd_handle_suspend(usb_dcd_ctx_t* dcd_ctx)
{
  USB_LOG(log_usb_dcd_handle_suspend);
  usb_fn_dcd()->usb_dcd_fd_notify(dcd_ctx,USB_DCD_EVT_SUSPEND);
}


//============================================================================
 /**
  * @function    usb_dcd_handle_setup
  * 
  * @brief   Handle setup notification from DCI
  * 
  * @note    callbacks for DCI
  *          handle all the setup cmd
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *          (INPUT) void* buffer_ptr: req pointer
  *
  * @return None
  */
// ===========================================================================
void usb_dcd_handle_setup(usb_dcd_ctx_t* dcd_ctx, void* buffer_ptr)
{
  int data_out_len = -1; /**< Data phase length, or negative error code */
  usb_setup_packet_t* req = (usb_setup_packet_t*)buffer_ptr;
  uint8 bm_req_type = ((req->bmRequestType & USB_SETUP_RT_TYPE_MASK) >> USB_SETUP_RT_TYPE_POS);

  // Exception Case : HID class specific request comes as standard.
  if(bm_req_type == USB_SETUP_RT_TYPE_STD)
  {
    uint8 desc_type = (req->wValue >> 8);
    if ((desc_type == USB_DESCTYPE_HID) || (desc_type == USB_DESCTYPE_HID_REPORT))
    {
      USB_LOG(log_handle_setup_ifc__req_get_hid_class_desc);
      bm_req_type = USB_SETUP_RT_TYPE_CLS;
    }
  }

  // data phase
  switch(bm_req_type)
  {
    case USB_SETUP_RT_TYPE_STD:
    {
      data_out_len = usb_fn_dcd()->handle_setup_std(dcd_ctx, req);
    }
    break;

    case USB_SETUP_RT_TYPE_CLS:
    {
      if(TRUE == usb_fn_dcd()->usb_dcd_handle_setup_class(dcd_ctx, req))
      {
        return;
      }
    }
    break;

    case USB_SETUP_RT_TYPE_VND:
    {
      data_out_len = usb_fn_dcd()->usb_dcd_handle_setup_vendor(dcd_ctx, req);
      if(data_out_len == 0)
      {
        return;
      }
    }
    break;

    case USB_SETUP_RT_TYPE_RSVD:
    default:
    {
      USB_LOG_ERR_1(log_usb_dcd_handle_setup__unsupport_req_D, bm_req_type);      
    }
  }
  
  /* handshake phase */
  if ( data_out_len > 0 )
  { 
    /* have data phase, data was sent, use Rx for handshake */
    usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_RX, dcd_ctx->setup_status, 0);
  } 
  else if ( data_out_len == 0 )
  { 
    /* no data phase, use Tx for handshake */
    usb_fn_dcd()->usb_dcd_control_reply(dcd_ctx, 0);
  } 
  else
  { 
    /* error, stall EP0 */
    USB_LOG_ERR_1(log_usb_dcd_handle_setup__stall_ep_req_D, 
       ((req->bmRequestType >> USB_SETUP_RT_RCP_POS) & USB_SETUP_RT_RCP_SEED ));      
    usb_fn_dci()->usb_dci_ctrl_error_recover(dcd_ctx->dci_ctx);
  }
}


//============================================================================
 /**
  * @function    usb_dcd_port_status_changed
  * 
  * @brief   Handle port status change notify from DCI
  * 
  * @note    callbacks for DCI
  *          pass the notify to FD
  *
  * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx: 
  *
  * @return None
  */
// ===========================================================================
void usb_dcd_port_status_changed(usb_dcd_ctx_t* dcd_ctx)
{
  dcd_ctx->speed = (usb_device_connect_speed_t) usb_fn_dci()->usb_dci_get_speed(dcd_ctx->dci_ctx);
  USB_LOG_1( log_usb_dcd_port_status_changed__spd_D, dcd_ctx->speed);
  usb_fn_dcd()->usb_dcd_fd_notify(dcd_ctx, USB_DCD_EVT_SPEED);
}

//============================================================================
/**
 * @function    usb_dcd_notify
 * 
 * @brief   API fuction pass to dci for hardware event callback
 * 
 * @note    This API pass to dci layer, it will be call from hw event
 *  
 * @param   (INPUT) void* dcd_ctx: 
 *          (INPUT) usb_notify_events_t  event: hw notify event
 *          (INPUT) void* buffer_ptr: req pointer
 * @return None
 */
// ===========================================================================
void usb_dcd_notify(void* dev_ptr, usb_notify_events_t  event, void* buffer_ptr)
{
  usb_dcd_ctx_t* dcd_ctx = dev_ptr;
  switch(event)
  {
    case USB_DCD_EVT_SPEED:
    {
      usb_fn_dcd()->usb_dcd_port_status_changed(dcd_ctx);
    }
    break;

    case USB_DCD_EVT_SUSPEND:
    {
      usb_fn_dcd()->usb_dcd_handle_suspend(dcd_ctx);
    }
    break;

    case USB_DCD_EVT_DISCONNECT:
    {
      usb_fn_dcd()->usb_dcd_handle_disconnect(dcd_ctx);
    }
    break;
    
    case USB_DCD_EVT_RESET:
    {
      usb_fn_dcd()->usb_dcd_handle_reset(dcd_ctx);
    }
    break;

    // Control events
    case USB_DCD_EVT_CTRL_SETUP_COMPLETE:
    {
      if(NULL != buffer_ptr)
      {
        usb_fn_dcd()->usb_dcd_handle_setup(dcd_ctx, buffer_ptr);
      }
    }
    break;

    case USB_DCD_EVT_CTRL_INIT:
    case USB_DCD_EVT_CTRL_STATUS_COMPLETE:
    case USB_DCD_EVT_CTRL_ERROR:
    {
      usb_fn_dcd()->usb_dcd_ctrl_start_xfer(dcd_ctx);
    }
    break;

    case USB_DCD_EVT_RECONFIG_SESSION:
    {
      usb_dcd_dsc_endpoint_t* ep_ptr;
      usb_desc_endpoint_t* dsc;
      usb_isoc_reconfig_sess_t* sess_cfg = (usb_isoc_reconfig_sess_t*) buffer_ptr;
      uint8 ep_address = (sess_cfg->dir << 7) | sess_cfg->ep;

      ep_ptr = usb_fn_dcd()->usb_dcd_find_ep(dcd_ctx, ep_address);
      dsc = ep_ptr->descriptor;

      usb_fn_dci()->usb_dci_unconfig_endpoint(sess_cfg->ep, sess_cfg->dir);

      usb_fn_dci()->usb_dci_config_endpoint (dcd_ctx->dci_ctx, sess_cfg->ep, sess_cfg->dir, 
        (uint8)(dsc->bmAttributes & 0x3), sess_cfg->bm1, dsc->wMaxPacketSize, 0);
    }
    break;

    case USB_DCD_EVT_START_SESSION:
    {
      usb_dcd_dsc_endpoint_t* ep_ptr;
      uint32 ep_address = (uint32) buffer_ptr;
      USB_ULOG_1(ENG_QLOG, "start session, ep 0x%x", ep_address);
      ep_ptr = usb_fn_dcd()->usb_dcd_find_ep(dcd_ctx, ep_address);
      USB_ASSERT(ep_ptr && ep_ptr->setup);
      ep_ptr->setup(ep_ptr, (usb_setup_packet_t*)TRUE);
    }
    break;

    case USB_DCD_EVT_STOP_SESSION:
    {
      usb_dcd_dsc_endpoint_t* ep_ptr;
      uint32 ep_address = (uint32) buffer_ptr;
      USB_ULOG_1(ENG_QLOG, "stop session, ep 0x%x", ep_address);
      ep_ptr = usb_fn_dcd()->usb_dcd_find_ep(dcd_ctx, ep_address);
      USB_ASSERT(ep_ptr && ep_ptr->setup);
      ep_ptr->setup(ep_ptr, (usb_setup_packet_t*)FALSE);
    }
    break;

    default:
    {
      USB_LOG_ERR_1(log_usb_dcd_notify__default_case_D, event);
    }
  }
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

void usb_dcd_set_bos(usb_dcd_ctx_t* dcd_ctx, usb_bos_desc_t* bos_desc)
{
  USB_ASSERT(bos_desc);
  dcd_ctx->bos_descriptor = bos_desc;
}

//============================================================================
/**
 * @function    usb_dcd_update_cfg
 * 
 * @brief   API is to update the configution_desc and other_speed_configuration 
 *          from fd
 * 
 * @note    FD will create the configutation and store in DCD layer
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *          (OUTPUT)usb_dcd_dsc_configuration_t* configurations: pointer to complete cfg
 *          (INPUT)  usb_dcd_cfg_type cfg_type: which configurations file to update
 *
 * @return  None
 */
// ===========================================================================
boolean usb_dcd_set_cfg_tree(usb_dcd_ctx_t* dcd_ctx, usb_dcd_dsc_configuration_t* cfg_tree)
{
  USB_ASSERT(cfg_tree);
  dcd_ctx->configurations = cfg_tree;
  dcd_ctx->other_speed_configuration = cfg_tree;
  return TRUE;
}

//============================================================================
/**
 * @function    usb_dcd_create_desc
 * 
 * @brief   API to create device desc after speed update
 * 
 * @note   
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx:
 *          (INPUT) uint16 product_id: 
 * @return  None
 */
// ===========================================================================
void usb_dcd_create_desc(usb_dcd_ctx_t* dcd_ctx_ptr, uint16 vendor_id, uint16 product_id, 
  uint8 n_cfg)
{
  usb_dcd_ctx_t* dcd_ctx = (usb_dcd_ctx_t*)dcd_ctx_ptr;
  if (dcd_ctx->descriptor)
  {
    usb_fn_mem_util()->usb_free((void**)&dcd_ctx->descriptor);
  }
  usb_fn_dcd()->usb_dcd_create_dev_desc(&dcd_ctx->descriptor, vendor_id, product_id, 
    dcd_ctx->speed, dcd_ctx->speed_required, n_cfg);
}

//============================================================================
/**
 * @function usb_dcd_ctrl_start_xfer
 * @brief   Start a new ep0 transfer for receiving setup.
 *
 * @param usb_dcd_ctx_t* dcd_ctx    
 *
 * @return  None.
 *
 * @ref SNPS spec 
 *
 */
//============================================================================
void usb_dcd_ctrl_start_xfer(usb_dcd_ctx_t *dcd_ctx)
{
  if (NULL == dcd_ctx)
  {
    USB_LOG_ERR(log_usb_dcd_ctrl_start_xfer__null_dcd);
    return;
  }

  //We use TRB for setup buffer 
  usb_fn_dcd()->usb_dcd_control_transfer(dcd_ctx, DIR_RX, NULL, DCI_SETUP_BUFFER_SIZE);
}

//============================================================================
/**
 * @function    usb_dcd_init
 * 
 * @brief   Initialize DCD
 * 
 * @note    Need to call after usb_dcd_ctx_alloc,
 *          Should be called prior to any other USB activity
 *  
 * @param   device Descriptor for current device composition
 *
 * @return  boolean FALSE whne fail, TRUE when success
 */
// ===========================================================================
boolean usb_dcd_init(usb_max_speed_required_t speed_required, usb_dcd_ctx_t** dcd_ctx_ptr,
  void* fd_ctx, usb_fd_callback_t fd_cb, uint16 lang_id, uint8* manuf_str, uint8* product_str, uint32 feature_flags)
{
  usb_dcd_ctx_t* dcd_ctx;
  usb_dcd_callback_t dcd_cb;
  USB_LOG(log_usb_dcd_init);

  if (NULL == fd_ctx)
  {
    USB_ULOG(ENG_QLOG, "Null FD_CTX or FD_CB.");
    return FALSE;
  }

  USB_ASSERT(dcd_ctx = (usb_dcd_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_dcd_ctx_t)));
  *dcd_ctx_ptr = dcd_ctx;

  usb_fn_dcd()->usb_dcd_allocate_strings(dcd_ctx, lang_id, manuf_str, product_str);
  usb_fn_dcd()->usb_dcd_allocate_dev_qual(&dcd_ctx->dev_qual);

  /* device ctx initialization */
  dcd_ctx->speed_required = speed_required;
  dcd_ctx->fd_ctx = fd_ctx;
  dcd_ctx->fd_cb = fd_cb;

  USB_ASSERT(dcd_ctx->vendor_buff = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_VENDOR_BUFF_SIZE));

  /* device is in "default" state - not configured, no address assigned */
  dcd_ctx->speed = USB_UNKNOWN_SPEED;
  dcd_ctx->address = 0;
  dcd_ctx->active_configuration = NULL;
  dcd_ctx->config_value = 0;

  /* prepare URB */
  //dev->ctrl_urb.tx.usb_device = dev;
  dcd_ctx->ctrl_urb.tx.fd_ctx = fd_ctx;
  dcd_ctx->ctrl_urb.tx.dcd_priv_ptr = dcd_ctx;
  dcd_ctx->ctrl_urb.tx.endpoint_address = 0x80;
  dcd_ctx->ctrl_urb.tx.complete_callback = NULL;
  dcd_ctx->ctrl_urb.tx.transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
  dcd_ctx->ctrl_urb.tx.send_zlp = TRUE;

  dcd_ctx->ctrl_urb.rx.fd_ctx = fd_ctx;
  dcd_ctx->ctrl_urb.rx.dcd_priv_ptr = dcd_ctx;
  dcd_ctx->ctrl_urb.rx.endpoint_address = 0x0;
  dcd_ctx->ctrl_urb.rx.complete_callback = NULL;
  dcd_ctx->ctrl_urb.rx.transfer_status = USB_URB_STATUS_COMPLETE_ERROR;

  dcd_ctx->usb_is_configured = FALSE;

  dcd_ctx->u1_enabled = FALSE;
  dcd_ctx->u2_enabled = FALSE;

  dcd_ctx->setup = NULL;
  
  // Initialize dcd callbacks
  dcd_cb.notify = usb_fn_dcd()->usb_dcd_notify;

  USB_ASSERT(dcd_ctx->setup_data = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_MAX_CTRL_PKT_SIZE));
  USB_ASSERT(dcd_ctx->setup_status = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_MAX_CTRL_PKT_SIZE));

  usb_fn_dci()->usb_dci_init(dcd_ctx->core_id, (void**)&dcd_ctx->dci_ctx, (void*)dcd_ctx, &dcd_cb, feature_flags);
  usb_fn_dci()->usb_dci_hw_init(dcd_ctx->dci_ctx, &dcd_ctx->speed_required);
  usb_fn_dcd()->usb_dcd_ctrl_start_xfer(dcd_ctx);

  return TRUE;
}

//============================================================================
/**
 * @function    usb_dcd_free_desc
 * 
 * @brief   API to free memory and data structures allocated for 
 *          device, config, BOS and device qualifier descriptors.
 * 
 * @note   
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx:
 *
 * @return  None
 */
// ===========================================================================
boolean usb_dcd_free_desc(usb_dcd_ctx_t* dcd_ctx)
{
  usb_dcd_dsc_configuration_t* config;
  usb_dcd_dsc_configuration_t* config_itr;
  usb_dcd_dsc_interface_t* ifc;
  usb_dcd_dsc_interface_t* ifc_itr;
  usb_dcd_dsc_endpoint_t* ep;
  usb_dcd_dsc_endpoint_t* ep_itr;

  USB_ASSERT(dcd_ctx);

  // Free configurations, interfaces and endpoint tree.
  // config
  config_itr = dcd_ctx->configurations; 
  while(config_itr)
  {
    config = config_itr;
    config_itr = config_itr->next;

    // interface
    ifc_itr = config->interfaces;
    while(ifc_itr) 
    {
      ifc = ifc_itr;
      ifc_itr = ifc_itr->next;

      // endpoints
      ep_itr = ifc->endpoints;
      while(ep_itr)
      {
        ep = ep_itr;
        ep_itr = ep_itr->next;
        usb_fn_mem_util()->usb_free((void**)&ep);
      }
      usb_fn_mem_util()->usb_free((void**)&ifc);
    }
    usb_fn_mem_util()->usb_free((void**)&config->descriptor);
    usb_fn_mem_util()->usb_free((void**)&config);
  }

  // Free BOS descriptor.
  if (dcd_ctx->bos_descriptor)
  {
    usb_fn_mem_util()->usb_free((void**)&dcd_ctx->bos_descriptor);
  }

  // Free device qualifier descriptor.
  if (dcd_ctx->dev_qual)
  {
    if (dcd_ctx->dev_qual->descriptor)
    {
      usb_fn_mem_util()->usb_free((void**)&dcd_ctx->dev_qual->descriptor);
    }
    usb_fn_mem_util()->usb_free((void **)&dcd_ctx->dev_qual);
  }

  // Free device descriptor
  if (dcd_ctx->descriptor)
  {
    usb_fn_mem_util()->usb_free((void **)&dcd_ctx->descriptor);
  }

  return TRUE;
}

//============================================================================
/**
 * @function    usb_dcd_shutdown
 * 
 * @brief   Shutdown the dcd
 * 
 * @note    call usb_dcd_snps_shutdown before trigger this. free all the dcd_ctx
 *  
 * @param   (INPUT) usb_dcd_ctx_t** dcd_ctx
 *
 * @return  None
 */
// ===========================================================================
void usb_dcd_shutdown(usb_dcd_ctx_t** dcd_ptr)
{
  usb_dcd_ctx_t* dcd_ctx = *dcd_ptr;

  USB_ASSERT(dcd_ctx);
  usb_fn_dci()->usb_dci_shutdown(&dcd_ctx->dci_ctx);

  dcd_ctx->usb_is_configured = FALSE;
  dcd_ctx->speed = USB_UNKNOWN_SPEED;
  dcd_ctx->address = 0;

  // Free data buffers
  if (dcd_ctx->setup_data)
  {
    usb_fn_mem_util()->usb_free((void**)&dcd_ctx->setup_data);
  }

  if (dcd_ctx->setup_status)
  {
    usb_fn_mem_util()->usb_free((void**)&dcd_ctx->setup_status);
  }

  if (dcd_ctx->vendor_buff)
  {
    usb_fn_mem_util()->usb_free((void**)&dcd_ctx->vendor_buff);
  }

  // Free descriptors allocated by FD layer.
  usb_fn_dcd()->usb_dcd_free_desc(dcd_ctx);

  // Free DCD ctx.
  usb_fn_mem_util()->usb_free((void**)dcd_ptr);
}

//============================================================================
 /**
  * @function    usb_dcd_submit_urb
  * 
  * @brief   Submit URB
  * 
  * @note    
  *       URB should be filled by upper layer as required
  *       After this function, ownership over URB passed to
  *       DCI and one should not access any fields. 
  *  
  *       Non blocking. 
  * 
  *       Submitter will regain ownership over URB when 
  *       a complete_callback called.
  *
  * @param  (INPUT) usb_dcd_ctx_t* dcd_ctx
  *         (INPUT) usb_urb_t* urb    Buffer to transfer. Can't be NULL.
  *
  * @return - 0 if OK
  *         - negative for error
  */
// ===========================================================================
int usb_dcd_submit_urb(usb_dcd_ctx_t* dcd_ctx, usb_urb_t* urb)
{
  urb->signature = USB_URB_SIGNATURE;
  urb->transfer_status = 0;
  urb->actual_length = 0;
  if ( dcd_ctx != NULL ) 
  {
    /**
    * When device is not in configured state, valid transfer 
    * may be only for EP0
    *  
    * urb->endpoint_address have EP number in bits 3:0
    */
    if ( ( dcd_ctx->config_value != 0 ) || 
        ( ( urb->endpoint_address & 0xf ) == 0 ) ) 
    {
      int rc = 0x0;
      rc = (int)usb_fn_dci()->usb_dci_transfer_request(dcd_ctx->dci_ctx, urb);
      return rc;
    }
  }
  urb->transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
  USB_LOG_ERR_1(log_usb_dcd_submit_urb__error_D, urb->transfer_status);
  return -1;
}

//============================================================================
/**
 * @function    usb_dcd_set_core
 * 
 * @brief   Set dcd core
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *          (INPUT) usb_core_type core_id: new core_id
 *
 * @return  None
 */
// ===========================================================================
void usb_dcd_set_core(usb_dcd_ctx_t* dcd_ctx, usb_core_type core_id)
{
  USB_ASSERT(dcd_ctx);
  dcd_ctx->core_id = core_id;
}

//============================================================================
/**
 * @function    usb_dcd_get_dci_ctx
 * 
 * @brief   return dci_ctx.
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx,
 *
 */
// ===========================================================================
void* usb_dcd_get_dci_ctx(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  return dcd_ctx->dci_ctx;
}

//============================================================================
/**
 * @function    usb_dcd_get_speed
 * 
 * @brief   Pass through function to dci layer
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx,
 *
 */
// ===========================================================================
usb_device_connect_speed_t usb_dcd_get_speed(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  return dcd_ctx->speed;
}


// ===========================================================================
/**
 * @function    usb_dcd_is_usb_configured
 * 
 * @brief   return if usb is configured
 *
 * @details This function return boolean if usb is configured
 * 
 * @param   (input) usb_dcd_ctx_t* dcd_ctx.
 * 
 * @return  boolean TRUE if usb is configured.
 * 
 */
// ===========================================================================
boolean usb_dcd_is_usb_configured(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  return dcd_ctx->usb_is_configured;
}

// ===========================================================================
/**
 * @function    usb_dcd_get_ctrl_urb_tx_transfer_status
 * 
 * @brief   return if ctrl_urb_status
 *
 * @details This function return transfer status for tx ctrl_urb
 * 
 * @param   (input) usb_dcd_ctx_t* dcd_ctx.
 * 
 * @return  urb transfer status
 * 
 */
// ===========================================================================
uint32 usb_dcd_get_ctrl_urb_tx_transfer_status (usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  return dcd_ctx->ctrl_urb.tx.transfer_status;
}

//============================================================================
/**
  PASS THROUGH FUNCTION TO DCI
*/
// ===========================================================================
//============================================================================
/**
 * @function    usb_dcd_poll
 * 
 * @brief   Pass through function to dci layer
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *
 * @return  None
 */
// ===========================================================================
void usb_dcd_poll(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  usb_fn_dci()->usb_dci_poll_events(dcd_ctx->dci_ctx);
}

//============================================================================
/**
 * @function    usb_dcd_reset
 * 
 * @brief   Pass through function to dci layer
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx
 *
 * @return  None
 */
// ===========================================================================
void usb_dcd_reset(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  usb_fn_dci()->usb_dci_handle_usb_reset(dcd_ctx->dci_ctx);
}

//============================================================================
/**
 * @function    usb_dcd_cancel_transfer
 * 
 * @brief   Pass through function to dci layer.
 *          Decode the urb before passing to dci
 *
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx,
 *          (INPUT) usb_urb_t* urb_ptr: pointer to cancel
 * @return  error_code
 */
// ===========================================================================
uint32 usb_dcd_cancel_transfer(usb_dcd_ctx_t* dcd_ctx, usb_urb_t* urb_ptr)
{
  uint32 ep;
  boolean dir;
  ep  = urb_ptr->endpoint_address & 0x0F;
  dir = VAL_TO_BOOL(urb_ptr->endpoint_address & 0x80);
  return usb_fn_dci()->usb_dci_cancel_transfer(dcd_ctx->dci_ctx, ep, dir);
}

//============================================================================
/**
 * @function    usb_dcd_get_max_packet_size
 * 
 * @brief   Pass through function to dci layer
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx,
 *
 */
// ===========================================================================
uint32 usb_dcd_get_max_packet_size(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  return usb_fn_dci()->usb_dci_get_max_packet_size(dcd_ctx->dci_ctx);
}

//============================================================================
/**
 * @function    usb_dcd_wakeup
 * 
 * @brief   Pass through function to dci layer
 *  
 * @param   (INPUT) usb_dcd_ctx_t* dcd_ctx,
 *
 */
// ===========================================================================
boolean usb_dcd_wakeup(usb_dcd_ctx_t* dcd_ctx)
{
  USB_ASSERT(dcd_ctx);
  usb_fn_dci()->usb_dci_handle_wakeup(dcd_ctx->dci_ctx);
  return TRUE;
}

/*----------------------------------------------------------------------------
 * Function table definition - DCD layer
 * -------------------------------------------------------------------------*/

usb_fn_tbl_dcd_t fn_tbl_dcd = 
{
  usb_dcd_desc_max_packet_size,
  usb_dcd_create_dev_desc,
  usb_dcd_create_dev_qual_desc,
  usb_dcd_allocate_dev_qual,
  usb_dcd_allocate_strings,
  usb_dcd_create_ep_comp_desc,
  usb_dcd_create_ep_desc,
  usb_dcd_create_ifc_desc,
  dcd_get_config_tree,
  dcd_get_config_value,
  find_config_by_value,
  get_curr_ifc_alt_set,
  usb_dcd_find_ep,
  get_string_desc,
  usb_dcd_fd_notify,
  usb_dcd_set_interface,
  usb_dcd_set_config,
  usb_dcd_control_transfer,
  usb_dcd_control_reply,
  handle_get_descriptor,
  handle_setup_dev,
  handle_setup_ifc,
  handle_ep_halt,
  handle_setup_ep,
  handle_setup_std,
  usb_dcd_handle_reset,
  usb_dcd_handle_disconnect,
  usb_dcd_handle_suspend,
  usb_dcd_handle_setup,
  usb_dcd_port_status_changed,
  usb_dcd_notify,
  usb_dcd_set_bos,
  usb_dcd_set_cfg_tree,
  usb_dcd_create_desc,
  usb_dcd_ctrl_start_xfer,
  usb_dcd_init,
  usb_dcd_free_desc,
  usb_dcd_shutdown,
  usb_dcd_submit_urb,
  usb_dcd_set_core,
  usb_dcd_get_dci_ctx,
  usb_dcd_get_speed,
  usb_dcd_is_usb_configured,
  usb_dcd_get_ctrl_urb_tx_transfer_status,
  usb_dcd_poll,
  usb_dcd_reset,
  usb_dcd_cancel_transfer,
  usb_dcd_get_max_packet_size,
  usb_dcd_wakeup,
  usb_dcd_class_status2_ack_cb,
  usb_dcd_class_data_cb,
  usb_dcd_handle_class_status3_req_ifc,
  usb_dcd_handle_class_status3_req_ep,
  usb_dcd_handle_setup_class_ifc,
  usb_dcd_handle_setup_class_ep,
  usb_dcd_handle_setup_class,
  usb_dcd_vendor_out_cb,
  usb_dcd_handle_setup_vendor,
};

