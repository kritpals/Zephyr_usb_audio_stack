/*=======================================================================*//**
  @file         usb_cdc_acm_fd.c

  @brief        Serial commnunication CDC driver functionality

  @details      
 
                Copyright (c)  Qualcomm Technologies, Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
*//*========================================================================*/

#include "usb_cdc_acm_fd.h"

/* CDC-ACM Descriptors */
void usb_cdc_acm_notify_speed(usb_device_connect_speed_t speed, void* data)
{
    usb_cdc_acm_ctx_t* ctx = (usb_cdc_acm_ctx_t*)data;
    USB_ASSERT(ctx);
    ctx->speed = speed;
    
    switch(speed) {
        case USB_SUPER_SPEED:
        case USB_HIGH_SPEED:
            ctx->bulk_max_packet_size = CDC_ACM_BULK_EP_MPS_HS;
            break;
        case USB_FULL_SPEED:
        default:
            ctx->bulk_max_packet_size = CDC_ACM_BULK_EP_MPS_FS;
            break;
    }
}

void usb_cdc_acm_set_cfg(void* ctx, usb_dcd_dsc_interface_t* ifc)
{
    usb_cdc_acm_ctx_t* cdc_ctx = (usb_cdc_acm_ctx_t*)ctx;
    USB_ASSERT(cdc_ctx && ifc);
    
    /* Store interface pointers */
    if (ifc->id == USB_IFC_ID_CDC_CONTROL) {
        cdc_ctx->ctrl_ifc = ifc;
    } else if (ifc->id == USB_IFC_ID_CDC_DATA) {
        cdc_ctx->data_ifc = ifc;
    }
}

/* Allocate CDC-ACM descriptors */
usb_dcd_dsc_interface_t* usb_cdc_acm_alloc_desc(
    uint8_t **dsc, uint16_t *len, uint16_t dsc_size,
    void *data, uint8_t ifc_num, uint8_t *ep_in_num, 
    uint8_t *ep_out_num, uint32_t rev_not_used)
{
    usb_cdc_acm_ctx_t* ctx = (usb_cdc_acm_ctx_t*)data;
    usb_dcd_dsc_interface_t* ctrl_ifc;
    usb_dcd_dsc_interface_t* data_ifc;
    usb_dcd_dsc_endpoint_t* ep_itr;
    uint8_t* cs_dsc_start;
    uint16_t cs_dsc_len = 0;
    
    USB_ASSERT(ctx);
    
    /* Control Interface (Interface 0) */
    ctrl_ifc = usb_fn_fd()->usb_fd_alloc_ifc_desc(
        dsc, len, dsc_size, ifc_num, 0, 1,  /* 1 interrupt EP */
        USB_CDC_ACM_CLASS, USB_CDC_ACM_SUBCLASS, 
        USB_CDC_ACM_PROTOCOL, USB_INTERFACE_STR_INDEX_NONE);
    
    ctrl_ifc->id = USB_IFC_ID_CDC_CONTROL;
    
    /* Add CDC functional descriptors */
    cs_dsc_start = *dsc;
    
    /* Header Functional Descriptor */
    struct cdc_header_descriptor {
        uint8_t bFunctionLength;
        uint8_t bDescriptorType;
        uint8_t bDescriptorSubtype;
        uint16_t bcdCDC;
    } __attribute__((packed));
    
    struct cdc_header_descriptor* header = (struct cdc_header_descriptor*)(*dsc);
    header->bFunctionLength = 5;
    header->bDescriptorType = USB_DESC_CS_INTERFACE;
    header->bDescriptorSubtype = 0x00; /* Header */
    header->bcdCDC = 0x0110; /* CDC 1.1 */
    *dsc += 5;
    *len += 5;
    cs_dsc_len += 5;
    
    /* Call Management Functional Descriptor */
    struct cdc_cm_descriptor* cm = (struct cdc_cm_descriptor*)(*dsc);
    cm->bFunctionLength = 5;
    cm->bDescriptorType = USB_DESC_CS_INTERFACE;
    cm->bDescriptorSubtype = 0x01; /* Call Management */
    cm->bmCapabilities = 0x00; /* No call management */
    cm->bDataInterface = ifc_num + 1; /* Data interface */
    *dsc += 5;
    *len += 5;
    cs_dsc_len += 5;
    
    /* ACM Functional Descriptor */
    struct cdc_acm_descriptor* acm = (struct cdc_acm_descriptor*)(*dsc);
    acm->bFunctionLength = 4;
    acm->bDescriptorType = USB_DESC_CS_INTERFACE;
    acm->bDescriptorSubtype = 0x02; /* ACM */
    acm->bmCapabilities = 0x02; /* Support line coding */
    *dsc += 4;
    *len += 4;
    cs_dsc_len += 4;
    
    /* Union Functional Descriptor */
    struct cdc_union_descriptor* un = (struct cdc_union_descriptor*)(*dsc);
    un->bFunctionLength = 5;
    un->bDescriptorType = USB_DESC_CS_INTERFACE;
    un->bDescriptorSubtype = 0x06; /* Union */
    un->bControlInterface = ifc_num;
    un->bSubordinateInterface0 = ifc_num + 1;
    *dsc += 5;
    *len += 5;
    cs_dsc_len += 5;
    
    /* Store class-specific descriptors */
    ctrl_ifc->cs_dsc = cs_dsc_start;
    ctrl_ifc->cs_dsc_size = cs_dsc_len;
    
    /* Interrupt IN endpoint for notifications */
    ep_itr = usb_fn_fd()->usb_fd_alloc_ep_desc(
        dsc, len, dsc_size, ++(*ep_in_num), USB_EP_ADDR_IN,
        USB_EP_ATTR_INTR, 10, CDC_ACM_INT_EP_MPS);
    
    INSERT_TAIL(usb_dcd_dsc_endpoint, ctrl_ifc->endpoints, ep_itr);
    ep_itr->ifc = ctrl_ifc;
    ep_itr->cs_dsc = NULL;
    ep_itr->cs_dsc_size = 0;
    
    /* Data Interface (Interface 1) */
    data_ifc = usb_fn_fd()->usb_fd_alloc_ifc_desc(
        dsc, len, dsc_size, ifc_num + 1, 0, 2,  /* 2 bulk EPs */
        USB_CDC_DATA_CLASS, 0, 0, USB_INTERFACE_STR_INDEX_NONE);
    
    data_ifc->id = USB_IFC_ID_CDC_DATA;
    data_ifc->cs_dsc = NULL;
    data_ifc->cs_dsc_size = 0;
    
    /* Bulk IN endpoint */
    ep_itr = usb_fn_fd()->usb_fd_alloc_ep_desc(
        dsc, len, dsc_size, ++(*ep_in_num), USB_EP_ADDR_IN,
        USB_EP_ATTR_BULK, 0, ctx->bulk_max_packet_size);
    
    INSERT_TAIL(usb_dcd_dsc_endpoint, data_ifc->endpoints, ep_itr);
    ep_itr->ifc = data_ifc;
    ep_itr->cs_dsc = NULL;
    ep_itr->cs_dsc_size = 0;
    
    /* Bulk OUT endpoint */
    ep_itr = usb_fn_fd()->usb_fd_alloc_ep_desc(
        dsc, len, dsc_size, ++(*ep_out_num), USB_EP_ADDR_OUT,
        USB_EP_ATTR_BULK, 0, ctx->bulk_max_packet_size);
    
    INSERT_TAIL(usb_dcd_dsc_endpoint, data_ifc->endpoints, ep_itr);
    ep_itr->ifc = data_ifc;
    ep_itr->cs_dsc = NULL;
    ep_itr->cs_dsc_size = 0;
    
    ctx->ctrl_ifc = ctrl_ifc;
    ctx->data_ifc = data_ifc;
    
    /* Link data interface after control interface */
    ctrl_ifc->next = data_ifc;
    data_ifc->next = NULL;
    
    return ctrl_ifc;
}

/* Handle CDC-ACM class-specific SET requests */
boolean usb_cdc_acm_handle_set_req(void* ctx, usb_setup_packet_t* setup, uint32* buff, uint32 len)
{
    usb_cdc_acm_ctx_t* cdc_ctx = (usb_cdc_acm_ctx_t*)ctx;
    
    if (!cdc_ctx) {
        return FALSE;
    }
    
    switch(setup->bRequest) {
        case USB_CDC_SET_LINE_CODING:
            /* Handle SET_LINE_CODING - host sends line coding */
            if (len >= sizeof(struct cdc_acm_line_coding)) {
                memcpy(&cdc_ctx->line_coding, buff, sizeof(struct cdc_acm_line_coding));
                USB_LOG_DBG_1(log_cdc_acm__set_line_coding, cdc_ctx->line_coding.dwDTERate);
                return TRUE;
            }
            break;
            
        case USB_CDC_SET_CONTROL_LINE_STATE:
            /* Handle SET_CONTROL_LINE_STATE (DTR/RTS) */
            cdc_ctx->line_state = setup->wValue;
            USB_LOG_DBG_1(log_cdc_acm__set_ctrl_line_state, cdc_ctx->line_state);
            /* Bit 0: DTR, Bit 1: RTS */
            return TRUE;
            
        default:
            USB_LOG_ERR_1(log_cdc_acm__unknown_set_request, setup->bRequest);
            return FALSE;
    }
    
    return FALSE;
}

/* Handle CDC-ACM class-specific GET requests */
uint8_t* usb_cdc_acm_handle_get_req(void* ctx, usb_setup_packet_t* setup, uint32* len)
{
    usb_cdc_acm_ctx_t* cdc_ctx = (usb_cdc_acm_ctx_t*)ctx;
    static uint8_t line_coding_buffer[sizeof(struct cdc_acm_line_coding)];
    
    if (!cdc_ctx || !len) {
        return NULL;
    }
    
    switch(setup->bRequest) {
        case USB_CDC_GET_LINE_CODING:
            /* Handle GET_LINE_CODING - device sends line coding to host */
            memcpy(line_coding_buffer, &cdc_ctx->line_coding, sizeof(struct cdc_acm_line_coding));
            *len = sizeof(struct cdc_acm_line_coding);
            USB_LOG_DBG_1(log_cdc_acm__get_line_coding, cdc_ctx->line_coding.dwDTERate);
            return line_coding_buffer;
            
        default:
            USB_LOG_ERR_1(log_cdc_acm__unknown_get_request, setup->bRequest);
            return NULL;
    }
}

/* Initialize CDC-ACM context */
void* usb_cdc_acm_init(usb_ifc_id ifc_id, uint8_t ifc_num, void* data)
{
    usb_cdc_acm_ctx_t* ctx;
    
    USB_ASSERT(ctx = (usb_cdc_acm_ctx_t*)usb_fn_mem_util()->usb_malloc(
        sizeof(usb_cdc_acm_ctx_t)));
    
    ctx->ifc_id = ifc_id;
    ctx->ctrl_ifc_num = ifc_num;
    ctx->data_ifc_num = ifc_num + 1;
    
    /* Default line coding: 115200 8N1 */
    ctx->line_coding.dwDTERate = 115200;
    ctx->line_coding.bCharFormat = 0;  /* 1 stop bit */
    ctx->line_coding.bParityType = 0;  /* No parity */
    ctx->line_coding.bDataBits = 8;
    
    return ctx;
}

void usb_cdc_acm_deinit(void* data)
{
    usb_cdc_acm_ctx_t* ctx = (usb_cdc_acm_ctx_t*)data;
    USB_ASSERT(ctx);
    usb_fn_mem_util()->usb_free((void**)&ctx);
}

/* Function table */
usb_fn_tbl_cdc_acm_t fn_tbl_cdc_acm = {
    usb_cdc_acm_alloc_desc,
    usb_cdc_acm_handle_set_req,
    usb_cdc_acm_handle_get_req,
    usb_cdc_acm_init,
    usb_cdc_acm_deinit,
    usb_cdc_acm_notify_speed,
    usb_cdc_acm_set_cfg,
};
