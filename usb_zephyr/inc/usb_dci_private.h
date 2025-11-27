#ifndef USB_DCI_PRIVATE_H
#define USB_DCI_PRIVATE_H

/*=======================================================================*//**
 * @file        usb_dci_private.h
 * @author:     kameya
 * @date        12-Dec-2017
 *
 * @brief       USB Synopsys DCI (Device-Controller-Interface) defines, types.
 *
 * @details     This header file contains structures and type definitions
 *              specific to Synopsys DWC3 hardware.
 *              This file should only be included by Synopsys specific DCI layer.
 *              
 * @ref         Synopsys DWC3 Databook
 *              Chapter 6 Device Data Structures
 *
 *              Copyright (c) 2008-2018 Qualcomm Technologies, Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/

//===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dci/usb_dci_private.h#2 $ $DateTime: 2018/02/12 17:09:34 $ $Author: pwbldsvc $
// 
// when       who      what, where, why
// --------   ---      ----------------------------------------------------------
// 07/14/08   amirs    First Draft
// 08/08/08   amirs    First working DLOAD process
// 08/11/08   amirs    Add files and functions headers according to coding standard.
// 08/30/10   dpatnaik Port USB to RPM, add ULPI based charger detection
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h"     // common defines and types
#include "usb_common.h"

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

// DCI Error Codes
#define DCI_OK                                  (0)
#define DCI_ERROR                               (0xDEADBEEF)

#define DCI_SETUP_BUFFER_SIZE                   (8)

#define DCI_MAX_ENDPOINTS                       (5)
#define DCI_MAX_DIRECTION                       (2)  // RX=OUT=0,TX=IN=1

#define USB_EP0_MAX_PACKET_SIZE_SUPER           (512)
#define USB_EP0_MAX_PACKET_SIZE_HIGH            (64)
#define USB_EP0_MAX_PACKET_SIZE_FULL            (64)
#define USB_EP0_MAX_PACKET_SIZE_LOW             (8)

#define USB_EP0_MAX_PACKET_SIZE_SUPER_BMAX0     (0x9)
#define USB_EVT_BUFFER_UNIT_SIZE                (0x4)

// Endpoint Type  see Chapter 3.6.24 ENDPTCTRL1 – ENDPTCTRL15
#define USB_EP_TYPE_CONTROL                     (0)
#define USB_EP_TYPE_ISO                         (1)
#define USB_EP_TYPE_BULK                        (2)
#define USB_EP_TYPE_INTERRUPT                   (3)

//Endpoint command related enable/disable MACROS
// Bit to enable the execution of Generic command
#define USB_EXECUTE_EP_GENERIC_COMMAND          (0x1) 

#define USB_EP_FIFO_NUMBER                      (0x0) 
#define USB_ENABLE_XFER_NOT_READY               (0x1)
#define USB_DISABLE_XFER_NOT_READY              (0x0)
#define USB_ENABLE_XFER_COMPLETE                (0x1)
#define USB_DISABLE_XFER_COMPLETE               (0x0)

//Define the Burst Size Parameters 
#define USB_BURST_SIZE_1                        (0x0)
#define USB_BURST_SIZE_2                        (0x1)
#define USB_BURST_SIZE_3                        (0x2)
#define USB_BURST_SIZE_4                        (0x3)
#define USB_BURST_SIZE_5                        (0x4)
#define USB_BURST_SIZE_6                        (0x5)
#define USB_BURST_SIZE_7                        (0x6)
#define USB_BURST_SIZE_8                        (0x7)
#define USB_BURST_SIZE_9                        (0x8)
#define USB_BURST_SIZE_10                       (0x9)
#define USB_BURST_SIZE_11                       (0xA)
#define USB_BURST_SIZE_12                       (0xB)
#define USB_BURST_SIZE_13                       (0xC)
#define USB_BURST_SIZE_14                       (0xD)
#define USB_BURST_SIZE_15                       (0xE)                   
#define USB_BURST_SIZE_16                       (0xF)

#define DCI_EP0                                 (0)
#define DCI_ZLP_TRB                             (0x1)
#define VAL_TO_BOOL(x)                         ((boolean)((x) != 0))
#define USB_DCI_POLLING_TIMEOUT_US              (100)

/****************************************USB3***********************************/

/***************************************ERRORS**********************************/
#define USB_ERR_NOT_SUPPORTED                        (1)
#define USB_ERR_HW_FAILURE                           (2)
#define USB_ERR_BAD_PARAM                            (3)
#define USB_ERR_URB_SIGNATURE                        (4)
#define USB_ERR_SETUP_PENDING                        (5)
#define USB_ERR_TIMER_IS_RUNNING                     (6)
#define USB_ERR_INVALID_OPERATION                    (7)
#define USB_ERR_EP_CMD_ACTIVE                        (8)
#define USB_ERR_INVALID_COMMAND                      (9)

/*******************************************************************************
 * TRBs
 ******************************************************************************/
#define DCI_MAX_TRBS                                (1)
#define USB_TRB_MAX_BUFFER_SIZE                     (0xFFFFFF)
#define USB_TRB_MAX_OUT_XFER_BUFFER_SIZE            (0xFFFC00)

/*******************************************************************************
 * Events
 ******************************************************************************/
#define EVENT_BUFFER_SIZE                           (4*60)
#define USB_DEV_INTR_LINE                           (0)
#define USB_EVT_TYPE_EP                             (0)
#define USB_EVT_TYPE_NON_EP                         (1)
#define USB_DCI_INVALID_EVENT                       (0xFFFFFFFF)
#define USB_MAX_EVENT_READ_TRIES                    (1000)

typedef enum trb_ctl_type 
{
  USB_TRB_CTL_NORMAL = 1,
  USB_TRB_CTL_CONTROL_SETUP,
  USB_TRB_CTL_CONTROL_STATUS_2,
  USB_TRB_CTL_CONTROL_STATUS_3,
  USB_TRB_CTL_CONTROL_DATA,
  USB_TRB_CTL_ISOCHRONOUS_FIRST,
  USB_TRB_CTL_ISOCHRONOUS,
  USB_TRB_CTL_LINK_TRB
} trb_ctl_type_t;

/* SNPS 6.2.8.1 , Table 6-48 */
typedef struct usb_event_depevt
{
  uint32  event_type:1;
  uint32  phy_ep_number:5;
  uint32  ep_xfer_event:4;
  uint32  rsvd1:2;
  uint32  event_status:4;
  uint32  event_param:16;
} usb_event_depevt_t;

  /* Control EP Status */
#define USB_DEPEVT_STATUS_CONTROL_SETUP	   0
#define USB_DDEPEVT_STATUS_CONTROL_DATA	   1
#define USB_DDEPEVT_STATUS_CONTROL_STATUS   2

#define USB_EVT_LINK_STATE 0xF
#define USB_EVT_INFO_SS 1
#define USB_EVT_INFO_HS 0
#define USB_EVT_INFO_SPEED_TYPE(x)  (((x >> 4) & 0x1))  
 
/* SNPS 6.2.8.2 , Table 6-49 */
typedef struct usb_event_devt
{
  uint32  event_type:1;
  uint32  dev_spec_event:7;
  uint32  dev_event:4;
  uint32  rsvd1:4;
  uint32  event_info:9;
  uint32  rsvd2:7;
} usb_event_devt_t;
 
typedef union usb_event{
  uint32  generic;
  usb_event_depevt_t depevt;
  usb_event_devt_t    devt;
} usb_event_t;

typedef struct usb_event_buffer_info {
  //events are generally 4Bytes long, exception of 1 event, which is 5 Bytes Long
  void    *buf;
  uint32  cur_pos;
} usb_event_buffer_info_t;


typedef enum usb_evt_dev_evt_t{
  USB_EVT_DEV_DISCONNECT_EVENT = 0,
  USB_EVT_DEV_USB_RESET,
  USB_EVT_DEV_CONNECT_DONE,
  USB_EVT_DEV_USB_LINK_STATE_CHANGE,
  USB_EVT_DEV_REMOTE_WAKE_UP,
  USB_EVT_DEV_HIBERNATION_REQUEST,
  USB_EVT_DEV_SUSPEND_ENTRY,
  USB_EVT_DEV_START_OF_FRAME,
  USB_EVT_DEV_ERRATIC_ERROR,
  USB_EVT_DEV_CMD_COMPLETE,
  USB_EVT_DEV_EVENT_BUFFER_OVERFLOW,
  USB_EVT_DEV_VNDR_DEV_TST_LMP_RCVED
} usb_evt_dev_evt_type;


typedef enum usb_evt_ep_evt_t{
  USB_EVT_EP_RSV0 = 0,
  USB_EVT_EP_XFER_COMPLETE,
  USB_EVT_EP_XFER_IN_PROGRESS,
  USB_EVT_EP_XFER_NOT_READY,
  USB_EVT_EP_RSV1,
  USB_EVT_EP_RSV2,
  USB_EVT_EP_STREAM,
  USB_EVT_EP_CMD_COMPLETE
} usb_evt_ep_evt_type;

/*******************************************************************************
 * Endpoint Commands
 ******************************************************************************/

typedef struct usb_ep_cmd_reg {
  uint32                    cmd_typ              :4;
  uint32                    rsvd0                :4;
  uint32                    cmd_ioc              :1;
  uint32                    rsvd1                :1;
  uint32                    cmd_act              :1;
  uint32                    hi_pri_force_rm      :1;
  uint32                    cmd_status           :4;
  uint32                    cmd_param            :16;
} usb_ep_cmd_reg_t;

typedef struct usb_ep_cmd_template {
  uint32                    parameter2;
  uint32                    parameter1;
  uint32                    parameter0;
  union 
  {
    uint32                  dword;
    usb_ep_cmd_reg_t     reg;
  } cmd;
} usb_ep_cmd_template_t;

#define USB_EP_CMD_SET_EP_CONFIG_VAL                          0x01
#define USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_NUM_SHIFT          0x1
#define USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_DIR_SHIFT          0x0
#define USB_EP_CMD_SET_EP_CONFIG_CONFIG_ACT_INIT              0
#define USB_EP_CMD_SET_EP_CONFIG_CONFIG_ACT_RESTORE           1
#define USB_EP_CMD_SET_EP_CONFIG_CONFIG_ACT_MODIFY            2
#define USB_EP_CMD_SET_EP_CONFIG_EP_TYPE_CTRL                 0
#define USB_EP_CMD_SET_EP_CONFIG_EP_TYPE_ISOC                 1
#define USB_EP_CMD_SET_EP_CONFIG_EP_TYPE_BULK                 2
#define USB_EP_CMD_SET_EP_CONFIG_EP_TYPE_INTR                 3

typedef struct usb_ep_cmd_set_ep_config {
  uint32                    Rsvd0;
  uint32                    intr_num            :5;
  uint32                    Rsvd1               :3;
  uint32                    xfer_cmpl_en        :1;
  uint32                    xfer_in_progess     :1;
  uint32                    xfer_nrdy_en        :1;
  uint32                    Rsvd2               :1;
  uint32                    rsvd3               :1;
  uint32                    strm_evt_en         :1;
  uint32                    rsvd4               :1;
  uint32                    ebc                 :1;
  uint32                    bInterval_m1        :8;
  uint32                    strm_cap            :1;
  uint32                    usb_ep_num          :5;
  uint32                    bulk_based          :1;
  uint32                    fifo_based          :1;
  uint32                    rsvd5               :1;
  uint32                    ep_type             :2;
  uint32                    max_packet_sz       :11;
  uint32                    rsvd6               :3;
  uint32                    fifo_num            :5;
  uint32                    brst_siz            :4;
  uint32                    rsvd7               :4;
  uint32                    config_action       :2;

  usb_ep_cmd_reg_t            cmd;
} usb_ep_cmd_set_ep_config_t;


#define USB_EP_CMD_SET_EP_XFER_RSC_CONFIG_VAL   (0x02)
#define USB_EP_CMD_GET_EP_STATE_VAL             (0x03)
#define USB_EP_CMD_SET_STALL_VAL                (0x04)
#define USB_EP_CMD_CLEAR_STALL_VAL              (0x05)
#define USB_EP_CMD_START_XFER_VAL               (0x06)
#define USB_EP_CMD_UPDATE_XFER_VAL              (0x07)
#define USB_EP_CMD_END_XFER_VAL                 (0x08)
#define USB_EP_CMD_START_NEW_CONFIG_VAL         (0x09)

typedef struct usb_ep_cmd_set_ep_xfer_rsc_config {
  uint32                    rsvd0;
  uint32                    Rsvd1;
  uint32                    num_xfer_res        :16;
  uint32                    rsvd2               :16;
  usb_ep_cmd_reg_t         cmd;
} usb_ep_cmd_set_ep_xfer_rsc_config_t;

typedef struct usb_ep_cmd_get_ep_state {
  uint32                    rsvd0;
  uint32                    rsvd1;
  uint32                    rsvd2;
  usb_ep_cmd_reg_t       cmd;
} usb_ep_cmd_get_ep_state_t;


typedef struct usb_ep_cmd_set_stall {
  uint32                    rsvd0;
  uint32                    rsvd1;
  uint32                    rsvd2;
  usb_ep_cmd_reg_t       cmd;
} usb_ep_cmd_set_stall_t;

typedef struct usb_ep_cmd_clear_stall {
  uint32                    rsvd0;
  uint32                    rsvd1;
  uint32                    rsvd2;
  usb_ep_cmd_reg_t            cmd;
} usb_ep_cmd_clear_stall_t;


typedef struct usb_ep_cmd_start_xfer {
  uint32                    rsvd0;
  uint32                    td_address_lo;
  uint32                    td_address_hi;
  usb_ep_cmd_reg_t            cmd;
} usb_ep_cmd_start_xfer_t;


typedef struct usb_ep_cmd_update_xfer {
  uint32                    rsvd0;
  uint32                    rsvd1;
  uint32                    rsvd2;
  usb_ep_cmd_reg_t            cmd;
} usb_ep_cmd_update_xfer_t;


typedef struct usb_ep_cmd_end_xfer {
  uint32                    rsvd0;
  uint32                    rsvd1;
  uint32                    rsvd2;
  usb_ep_cmd_reg_t            cmd;
} usb_ep_cmd_end_xfer_t;


typedef struct usb_ep_cmd_start_new_config {
  uint32                    rsvd0;
  uint32                    rsvd1;
  uint32                    rsvd2;
  usb_ep_cmd_reg_t            cmd;
} usb_ep_cmd_start_new_config_t;

typedef union usb_ep_cmd {
  usb_ep_cmd_template_t                 template;
  usb_ep_cmd_set_ep_config_t            set_ep_config;
  usb_ep_cmd_set_ep_xfer_rsc_config_t   set_ep_xfer_rsc_config;
  usb_ep_cmd_get_ep_state_t             get_ep_state;
  usb_ep_cmd_set_stall_t                set_stall;
  usb_ep_cmd_clear_stall_t              clear_stall;
  usb_ep_cmd_start_xfer_t               start_xfer;
  usb_ep_cmd_update_xfer_t              update_xfer;
  usb_ep_cmd_end_xfer_t                 end_xfer;
  usb_ep_cmd_start_new_config_t         start_new_config;
} usb_ep_cmd_t;

/*******************************************************************************
 * Device Commands
 ******************************************************************************/
typedef struct usb_dev_cmd_reg {
  uint32                    cmd_typ                     :8;
  uint32                    cmd_ioc                     :1;
  uint32                    rsvd1                       :1;
  uint32                    cmd_act                     :1;
  uint32                    rsvd2                       :21; 
} usb_dev_cmd_reg_t;

typedef struct usb_dev_cmd_template {
  uint32                    parameter;
  union
  {
    uint32                  dword;
    usb_dev_cmd_reg_t    reg;    
  } cmd;
} usb_dev_cmd_template_t;

#define USB_DEV_CMD_TX_SET_LINK_FN_LMP_VAL            0x01
#define USB_DEV_CMD_SET_PERIODIC_PARAMS_VAL           0x02
#define USB_DEV_CMD_TX_FN_WAKE_DEV_NOTIFY_VAL         0x03
#define USB_DEV_CMD_SET_SCRATCHPAD_BUF_LO_VAL         0x04
#define USB_DEV_CMD_SET_SCRATCHPAD_BUF_HI_VAL         0x05
#define USB_DEV_CMD_TX_FN_HOST_REQ_NOTIFY_VAL         0x06
#define USB_DEV_CMD_TX_DEVICE_NOTIFY_VAL              0x07
#define USB_DEV_CMD_SELECTED_FIFO_FLUSH_VAL           0x09
#define USB_DEV_CMD_ALL_FIFO_FLUSH_VAL                0x0A
#define USB_DEV_CMD_SET_EP_NRDY_VAL                   0x0C
#define USB_DEV_CMD_RUN_SOC_LOOPBACK_TEST_VAL         0x10

typedef struct usb_dev_cmd_tx_set_link_fn_lmp {
  uint32                    force_link_pm_accept        :1;
  uint32                    rsvd                        :31;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_tx_set_link_fn_lmp_t;

typedef struct usb_dev_cmd_set_periodic_params {
  uint32                    system_exit_latency         :10;
  uint32                    rsvd                        :22;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_set_periodic_params_t; 

typedef struct usb_dev_cmd_tx_fn_wake_dev_notify {
  uint32                    int_f_num                   :8;
  uint32                    rsvd                        :24;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_tx_fn_wake_dev_notify_t;

typedef struct usb_dev_cmd_set_scratchpad_buf_lo {
  uint32                    address_lo;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_set_scratchpad_buf_lo_t;

typedef struct usb_dev_cmd_set_scratchpad_buf_hi {
  uint32                    address_hi;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_set_scratchpad_buf_hi_t;

typedef struct usb_dev_cmd_tx_fn_host_req_notify {
  uint32                    initiate                    :1;
  uint32                    confirm                     :1;
  uint32                    rsvd                        :30;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_tx_fn_host_req_notify_t;

typedef struct usb_dev_cmd_tx_device_notify {
  uint32                    notification_type           :4;
  uint32                    notification_params         :28;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_tx_device_notify_t;

typedef struct usb_dev_cmd_selected_fifo_flush {
  uint32                    fifo_number                 :5;
  uint32                    tx_rx_fifo                  :1;
  uint32                    rsvd                        :26;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_selected_fifo_flush_t;

typedef struct usb_dev_cmd_all_fifo_flush {
  uint32                    rsvd;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_all_fifo_flush_t;

typedef struct usb_dev_cmd_set_ep_nrdy {
  uint32                    phys_ep_number              :5;
  uint32                    rsvd0                       :27;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_set_ep_nrdy_t;

typedef struct usb_dev_cmd_run_soc_loopback_test {
  uint32                    loopback_enable             :1;
  uint32                    rsvd                        :31;
  usb_dev_cmd_reg_t      cmd;
} usb_dev_cmd_run_soc_loopback_test_t;

typedef union usb_dev_cmd {
  usb_dev_cmd_template_t                 template;
  usb_dev_cmd_tx_set_link_fn_lmp_t       set_link_fn_lmp; 
  usb_dev_cmd_set_periodic_params_t      set_periodic_params; 
  usb_dev_cmd_tx_fn_wake_dev_notify_t    tx_fn_wake_dev_notify;
  usb_dev_cmd_set_scratchpad_buf_lo_t    set_scratchpad_buf_lo;
  usb_dev_cmd_set_scratchpad_buf_hi_t    set_scratchpad_buf_hi;
  usb_dev_cmd_tx_fn_host_req_notify_t    tx_fn_host_req_notify;
  usb_dev_cmd_tx_device_notify_t         tx_device_notify;
  usb_dev_cmd_selected_fifo_flush_t      selected_fifo_flush;
  usb_dev_cmd_all_fifo_flush_t           all_fifo_flush;
  usb_dev_cmd_set_ep_nrdy_t              set_ep_nrdy;
  usb_dev_cmd_run_soc_loopback_test_t    run_soc_loopback_test;
} usb_dev_cmd_t;


#define USB_EP_INDEX(ep,dir)                    (((ep) * 2) + (dir))
#define USB_PHY_EP_TO_DIR(x)                    (x%2)
#define USB_PHY_EP_TO_EP(x)                      (((x+1) >> 1 ) - (x%2))

typedef enum
{
  EP0_STATE_MIN = 0,
  EP0_STATE_SETUP_TRB,
  EP0_STATE_INTRPT_SETUP,
  EP0_STATE_STATUS_2,
  EP0_STATE_DATA,
  EP0_STATE_DATA_IN_PROGRESS,
  EP0_STATE_STATUS_3,
  EP0_STATE_MAX
} usb_dci_ctrl_trb_state_t;


#define USB_EP_ACTIVE                       ( 1 << 0 )
#define USB_EP_HALTED                       ( 1 << 1 ) 

#define USB_EP0_OUT                         (1 << 0) 
#define USB_EP0_IN                          (1 << 1)
#define USB_EP1_OUT                         (1 << 2) 
#define USB_EP1_IN                          (1 << 3)


typedef struct usb_trb {
  uint32                    buf_ptr_lo;
  uint32                    buf_ptr_hi;
  uint32                    buf_size            :24;
  uint32                    pcm1                :2;
  uint32                    rsvd0               :2;
  uint32                    trbsts              :4;
  uint32                    hwo                 :1;
  uint32                    lst                 :1;
  uint32                    chn                 :1;
  uint32                    csp                 :1;
  uint32                    trb_ctl             :6;
  uint32                    isp_imi             :1;
  uint32                    ioc                 :1;
  uint32                    rsvd1               :2;
  uint32                    sid_sofn            :16;
  uint32                    rsvd2               :2;
} usb_trb_t;


#endif /*USB_DCI_PRIVATE_H*/
