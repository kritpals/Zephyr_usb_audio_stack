//============================================================================
/**
 * @file        usb_dci.c
 * @author      shreyasr
 * @date        13-Sep-2013
 *
 * @brief       USB (Qualcomm Super-Speed USB) DCI (Device-Controller-Interface) implementation.
 *
 * @details     The USB (Qualcomm Super-Speed USB) DCI (Device-Controller-Interface) 
 *              acts like a HAL (Hardware Abtraction Layer) for Synopsys USB Hardware.
 *              The DCI should supply generic API that hides USB Hardware registers access from the upper layers.
 *              It should not be aware of Chapter-9 or specific function drivers (Mass-Storage , CDC , HID etc).
 *              It should be simple without any management algorithms.
 *              
 *              The USB Device Core Driver (DCD) shall use the DCI to implement
 *              the USB protocol chapter 9 enumeration,
 *              and handling of special BUS signaling : Reset / Suspend / Resume.
 * 
 * @note        This DCI is implementing the Synopsys hardware core.
 *              The DCI depends on the USB Core (a.k.a LINK) connection to the PHY:
 *              When a 3-wired PHY is connected (Full-Speed only) then the LINK
 *              can not control the VBUS D+ wire via the Run/Stop bit.
 * 
 * @ref         
 *
 *              Copyright (c) 2013 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
 */
//============================================================================
// ===========================================================================  
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dci/usb_dci.c#19 $$DateTime: 2018/08/30 14:53:00 $$Author: pwbldsvc $
// 
// when       who      what, where, why
// --------   ---      ----------------------------------------------------------
// 09/13/13   shreyasr Refactored the SNPS USB3 code for integration to Luxor
// 05/15/13   rthoorpu Modified the code for SNPS USB3 support. 
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "usb_dci_ulpi.h"
#include "usb_hwio_9410.h"
#include "usb_dci_9410.h"

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <stringl/stringl.h>        // For memscpy
#include "usb_dci.h"            // DCI API Prototypes
#include "usb_urb.h"             // URB structure - usb_urb_t
#include "usb_log.h"
#include "usb_isr.h"
#include "usb_mem_util.h" 
#include "usb_util.h"
//#include "led.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------
#define USB_CMDACT_DELAY        (100)
#define USB_CMDACT_DELAY_US     (1000)
#define USB_HWO_DELAY_CNT       (20)

#define USB_CTRL_TX_BUFFER_SIZE                 (1024)

// Valid Resource Index returned from HW, can range from [0, 0x7F], so we can only use 0xFF as a
// special value for resource index not being set
#define USB_RSC_IDX_NOT_SET                     (0xFF)

#if defined(TARGET_FPGA)
#define USB_USE_ULPI_PHY (1)
#else
#define USB_USE_ULPI_PHY (0)
#endif

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------
#define USB_EP_XFER_RSC_INDEX_BMSK   (0x7F)

//----------------------------------------------------------------------------
// Global Data Definitions
//----------------------------------------------------------------------------
#define LINK_STATE_SUSPEND_U3           (0x3)
#define LINK_STATE_SS_DISABLED          (0x4)

#define USB_DCI_ISOC_RECONFIG_THRES     (3)
//----------------------------------------------------------------------------
// Static Variable Definitions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Static Functions 
//----------------------------------------------------------------------------
static void usb_dci_handle_ctrl_transfers(usb_dci_ctx_t* dci_ctx, 
                                                   usb_event_depevt_t *depevt);
static void usb_dci_handle_transfer_complete(usb_dci_ctx_t* dci_ctx, 
                                                        usb_event_depevt_t *depevt);
void usb_dci_handle_connect_done(usb_dci_ctx_t* dci_ctx);
static void usb_dci_handle_usb_disconnect(usb_dci_ctx_t* dci_ctx);
static usb_link_state_t usb_dci_get_link_state(usb_dci_ctx_t* dci_ctx); 
static void usb_dci_handle_link_status_change(usb_dci_ctx_t* dci_ctx, uint32 state);
void usb_dci_handle_suspend_entry(usb_dci_ctx_t* dci_ctx);
static uint32 usb_dci_submit_trb_data(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir);
static uint32 usb_dci_transfer_data_request(usb_dci_ctx_t* dci_ctx, 
                                                     uint8 ep, 
                                                     uint8 dir,
                                                     usb_urb_t* urb_ptr,
                                                     trb_ctl_type_t trb_ctrl);
void usb_dci_core_init(usb_dci_ctx_t* dci_ctx);

uint32 usb_dci_write_ep_cmd(usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, usb_ep_cmd_t *ep_cmd);
static uint32 usb_dci_write_dev_cmd(usb_dci_ctx_t* dci_ctx, usb_dev_cmd_t *dev_cmd);
static void usb_dci_event_buffer_init(usb_dci_ctx_t* dci_ctx);

void usb_dci_init_trb_ring(usb_dci_ctx_t* dci_ctx);
static uint32 usb_dci_prepare_trbs(usb_dci_ctx_t* dci_ctx,
                                        uint32 ep, 
                                        uint32 dir, 
                                        usb_urb_t* urb_ptr,
                                        uint8 trb_ctl);
static void usb_dci_inc_trb_idx(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, uint8 *idx);
static void usb_dci_ctrl_xfer_state_machine(usb_dci_ctx_t* dci_ctx,
                                                      usb_urb_t* urb_ptr,
                                                      trb_ctl_type_t *trb_ctl);

uint32 usb_dci_ctrl_submit_request(usb_dci_ctx_t* dci_ctx, uint8 dir);
uint32 usb_dci_poll_pwr_event(usb_dci_ctx_t* dci_ctx);
uint32 usb_dci_remote_wakeup(usb_dci_ctx_t* dci_ctx);

//----------------------------------------------------------------------------
// Superspeed API implementation
//----------------------------------------------------------------------------

// ===========================================================================
/**
 * @function    usb_dci_handle_u1_u2_enable
 * 
 * @brief   This function will enable link transition to U1 or U2 state.
 * 
 * @param   Device context.
 * @param   Type of event.
 * @param   Enable/Disable.
 * 
 * @return  None.
 *
 * 
 */
// ===========================================================================
void usb_dci_handle_u1_u2_enable(usb_dci_u1_u2_event_type event, boolean enable)
{
}

//============================================================================
/**
 * @function  usb_dci_update_packet_size
 *
 * @brief Update the maximum packet size of base on speed detection
 *
 * @param usb_dci_ctx_t
 *
 * @return None  
 *
 * @ref SNPS spec 
 *       
 */
//============================================================================
void usb_dci_update_packet_size(usb_dci_ctx_t* dci_ctx)
{
  uint32 speed; 
  uint32 max_packet_size = 0x0; 

  USB_ASSERT(dci_ctx);

  speed = usb_fn_dci()->usb_dci_get_speed(dci_ctx); 

  switch(speed)
  {
    case USB_SUPER_SPEED:
      max_packet_size = 1024;
    break; 
    case USB_HIGH_SPEED: 
      max_packet_size = 512; 
    break; 
    case USB_FULL_SPEED:
    case USB_FULL_SPEED_48:
      max_packet_size = 64;
    break;
    case USB_LOW_SPEED: 
      max_packet_size = 8; 
    break;
    default:
      max_packet_size = 64;
      USB_LOG_ERR_1(log_usb_dci_update_packet_size__unknown_speed_D, speed);
      USB_ERR_HALT(FALSE);
    break; 
  }
  
  dci_ctx->usb_dci_max_packet_size = max_packet_size;
  dci_ctx->usb_dci_ep0_max_packet_size =( max_packet_size == 1024 ) ? USB_EP0_MAX_PACKET_SIZE_SUPER :
                                                  USB_EP0_MAX_PACKET_SIZE_HIGH;

  USB_LOG_1( log_usb_dci_update_packet_size__max_packet_size_D, max_packet_size);
  return;
}

// ===========================================================================
/**
 * @function    usb_dci_test_mode_enable
 * 
 * @brief   Enables the USB test mode based on set_feateure
 * 
 * @note   
 *  
 * @param   dci_ctx
 *  
 * @param   enable   - if test mode is enabled
 *  
 * @param   test_mode   - test mode based on set feature
 *
 * @return None
 *
 * @ref 
 *
 */
// ===========================================================================
void usb_dci_test_mode_enable(usb_dci_ctx_t* dci_ctx, boolean enable, uint32 test_mode)
{
  dci_ctx->test_mode_enabled = enable;
  dci_ctx->test_mode = test_mode;
}

// ===========================================================================
/**
 * @function    usb_dci_handle_test_mode
 * 
 * @brief   Enables the USB test mode.
 * 
 * @note   
 *  
 * @param   dci_ctx
 *
 * @return 
 *
 * @ref SNPS spec :
 *      Table 6-61 DCTL(4:1)
 *
 */
// ===========================================================================
void usb_dci_handle_test_mode(usb_dci_ctx_t* dci_ctx)
{ 
   if (FALSE == dci_ctx->is_usb_clk_on)
   {
     usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
   }
   
   switch(dci_ctx->test_mode) 
   {
     case USB_PORT_TEST_J_STATE:
     case USB_PORT_TEST_K_STATE:
     case USB_PORT_TEST_SE0_NAK:
     case USB_PORT_TEST_PACKET:
     case USB_PORT_TEST_FORCE_ENABLE:
       HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_TSTCTL_BMSK,(dci_ctx->test_mode << HWIO_USBCTL_DCTL_TSTCTL_SHFT));
       break;
     case USB_PORT_TEST_DISABLE:
       HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_TSTCTL_BMSK,(dci_ctx->test_mode << HWIO_USBCTL_DCTL_TSTCTL_SHFT));
       dci_ctx->test_mode_enabled = FALSE;

     default:
       USB_LOG_ERR_1(log_usb_dci_handle_test_mode__test_mode_D, dci_ctx->test_mode);
       break;
  }
}

// ===========================================================================
/**
 * @function    usb_dci_configure_device_mode
 * 
 * @brief   This is used for configuring the Device config Register post reset.
 * 
 * @param   usb_max_speed_required_t Maximum speed at which the device can operate
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_configure_device_mode(boolean is_l1_enable, usb_max_speed_required_t speed_required)
{
  /* Configure the Minimum negotiatiated Speed to  HS: 0x0 , SS: 0x4**/

#ifdef USB_KW_CONST_RESULT
    //condition always yield the same result and causes an unreachable code
  if(speed_required == USB_MAX_SPEED_SUPER)
  {
      /* Maximum Speed Configured is Super Speed */
      HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_DEVSPD_BMSK,(USB_SUPER_SPEED << HWIO_USBCTL_DCFG_DEVSPD_SHFT));
  }
  else if (speed_required == USB_MAX_SPEED_HIGH)
#else
  (void)speed_required;
#endif
  { 
      //Trigger this unconditionally if no superspeed
      /* Maximum Speed Configured is High Speed */
      HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_DEVSPD_BMSK,(USB_HIGH_SPEED << HWIO_USBCTL_DCFG_DEVSPD_SHFT));
  }

  /*set the device address to 0x0 after reset*/ 
  HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_DEVADDR_BMSK,(0x0 << HWIO_USBCTL_DCFG_DEVADDR_SHFT)); 

  if (is_l1_enable)
  {
    HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_LPMCAP_BMSK,(0x1 << HWIO_USBCTL_DCFG_LPMCAP_SHFT));

    // Note - Allow USB controller hardware to handle L1 exit. 
    // As a result, Software need not listen to L1 event (Decouple L1 event from L2 and disable L1 event interrupt)
    HWIO_USBCTL_GUCTL1_OUTM(HWIO_USBCTL_GUCTL1_DEV_L1_EXIT_BY_HW_BMSK, 
      (0x1 << HWIO_USBCTL_GUCTL1_DEV_L1_EXIT_BY_HW_SHFT));
    HWIO_USBCTL_GUCTL1_OUTM(HWIO_USBCTL_GUCTL1_DEV_DECOUPLE_L1L2_EVT_BMSK, 
      (0x1 << HWIO_USBCTL_GUCTL1_DEV_DECOUPLE_L1L2_EVT_SHFT));
  }
  else
  {
    HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_LPMCAP_BMSK,(0x0 << HWIO_USBCTL_DCFG_LPMCAP_SHFT));
  }

  // As per SNPS spec. when ISOC endpoints are used, PHY PLL clock needs to be ON
  // to keep SOFs running. Set ENBLSLPM = 0. 
  HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTMI(0x0, HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK,
    (0x0 << HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_SHFT));
  
  /*No of receieve buffer NUMP */
  HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_NUMP_BMSK,(0x4 << HWIO_USBCTL_DCFG_NUMP_SHFT));
}

// ===========================================================================
/**
 * @function    usb_dci_get_hardware_id
 * 
 * @brief   This function will be used for getting the SNPS h/w id.
 * 
 * @param   None
 * 
 * @return  uint32 - hardware id. 
 * 
 */
// ===========================================================================
uint32 usb_dci_get_hardware_id(void)
{
  uint32 hw_id =0x0;
  hw_id = HWIO_USBCTL_GSNPSID_INM(HWIO_USBCTL_GSNPSID_SYNOPSYSID_BMSK);
  return hw_id;
}

// ===========================================================================
/**
 * @function    usb_dci_hw_init
 * 
 * @brief   This function will be called by the DCD to initialize the hardware (DCI)
 * 
 * @param   * dci_context_ptr   - DCI context pointer 
 *
 * @param   * max_speed         - pointer to dev speed
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_hw_init(usb_dci_ctx_t* dci_ctx, usb_max_speed_required_t* max_speed)
{
  uint32 reg_in;

  USB_LOG(log_usb_dci_hw_init);

  #if defined(TARGET_FPGA)
  USB_ASSERT(dci_ctx->ulpi_debug = 
    (usb_ulpi_debug_ctx_t*)usb_fn_mem_util()->usb_malloc(sizeof(usb_ulpi_debug_ctx_t)));

  usb_dci_ulpi_debug_init(dci_ctx->ulpi_debug);
  #endif

  //1.    Release USB controller (AHB side), USB phy wrapper, AHB2PHY out of reset for USB test
  HWIO_CHIP_CFG1_RST_USB_SS_OUT(0xE);
  usb_fn_util()->usb_delay_us(100);
  HWIO_CHIP_CFG1_RST_USB_SS_OUT(0x0);
  usb_fn_util()->usb_delay_us(100);

#if defined(TARGET_FPGA)
  //1.1?  FPGA external PHY: reset pin release
  out_byte(USB_EXTERNAL_ULPI_PHY_RESET_REG_ADDR, 1);  //phy reset assert
  usb_fn_util()->usb_delay_us(200);
  out_byte(USB_EXTERNAL_ULPI_PHY_RESET_REG_ADDR, 0);      //phy reset deassert
  usb_fn_util()->usb_delay_us(200);
#endif 

  //1.  Apply USB bus vote (Set by USB driver SW. If set to 1, keeps bus and the respective block clock ON.
  //    This vote should be set to 0 in order for chip to enter into L2 suspend state)
  usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);

  //2. usb phy initialization
  usb_fn_dci_target()->usb_dci_hs_phy_init();

  //3.  Release USB from shut down (enable USB Desc RAM buffer)
  HWIO_CHIP_CFG1_PWR_MEM_SD_OUTM(HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_BMSK,
                            0x0 << HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_SHFT);

  //4.?  Enable Audio Timer  //TODO BOLT_ADD check with Ren
  //usb_dci_enable_audio_timer();

  //5.  Debug bus setup - USBCTL_USB30_QSCRATCH_DBG_BUS_REG
  HWIO_USBCTL_DBG_BUS_REG_OUT(0xC3DC06ED);

  //6. USBCTL_USB30_QSCRATCH_HW_SW_EVT_CTRL_REG
  HWIO_USBCTL_HW_SW_EVT_CTRL_REG_OUT(0x7AC4DB39);

  //7. USBCTL_USB30_QSCRATCH_CGCTL_REG -- Enable DBM FSM CGC, LSP CGC 
  HWIO_USBCTL_CGCTL_REG_OUT(HWIO_USBCTL_CGCTL_REG_LSP_CGC_EN_N_BMSK | HWIO_USBCTL_CGCTL_REG_DBM_FSM_EN_BMSK); 
    
  //8. USBCTL_USB30_QSCRATCH_GENERAL_CFG 
  // PIPE UTMI CLK DISABLE
  HWIO_USBCTL_GENERAL_CFG_OUTM(HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
    0x1 << HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);

  //9. USBCTL_USB30_QSCRATCH_GENERAL_CFG 
  // PIPE UTMI CLK SELECT
  // PHYSTATUS SW OVERRIDE
  reg_in = HWIO_USBCTL_GENERAL_CFG_IN;
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK,
                        HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_SEL_SHFT);

  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK,
                        HWIO_USBCTL_GENERAL_CFG_PIPE3_PHYSTATUS_SW_SHFT);
  HWIO_USBCTL_GENERAL_CFG_OUT(reg_in);

#if defined(TARGET_FPGA)
  //For FPGA: (select ULPI for external PHY)
  //ULPI_4BIT_EN, enaable 4-bit ULPI mode for usb, 0 for FPGA
  HWIO_MCU_SS_USB_CTRL_OUTM(HWIO_MCU_SS_USB_CTRL_ULPI_4BIT_EN_BMSK, 
                        0x0 << HWIO_MCU_SS_USB_CTRL_ULPI_4BIT_EN_SHFT);

  //10.1 USBCTL_DWC_USB3_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG, p=[0..0] 
  usb_fn_dci_target()->usb_dci_select_phy_mode(USB_PHY_MODE_ULPI);
#else
  //For ASIC:
  //10. USBCTL_USB30_QSCRATCH_GENERAL_CFG 
  usb_fn_dci_target()->usb_dci_select_phy_mode(USB_PHY_MODE_UTMI);

  //TODO: TODO BOLT_ADD
  HWIO_USBCTL_GENERAL_CFG_OUTM(HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
                    0x0 << HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);

#endif

  //11. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0[0] – setup TX FIFO start 
  //addr and depth
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_OUTI(0, 0x04DA0014);

  //12. USBCTL_ DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_OUTI(0, 0x04EE0104);

      
  //13. USBCTL_ DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_OUTI(0, 0x05F20104);
      
  //14. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_OUTI(0, 0x06F60104);
      
  //15. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_OUTI(0, 0x07FA0203);

  //16. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_OUTI(0, 0x09FD0203);
      
  //17. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_OUTI(0, 0x0C000024);
      
  //18. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_OUTI(0, 0x0C240203);
      
  //19. USBCTL_DWC_USB3_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8[0]
  HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_OUTI(0, 0x0E270104);
      
      
  //20. USBCTL_DWC_USB3_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0[0] 
  HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_OUTMI(0, HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RXFDEP_N_BMSK,
                                                0x0187 << HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RXFDEP_N_SHFT);

  //21. USBCTL_DWC_USB3_GEVNTADRLO_REGS_p_GEVNTADRLO[0]
  //22. USBCTL_DWC_USB3_GEVNTADRLO_REGS_p_GEVNTADRHI[0]
  //23. USBCTL_DWC_USB3_GEVNTADRLO_REGS_p_GEVNTSIZ[0]
  //24. USBCTL_DWC_USB3_GEVNTADRLO_REGS_p_GEVNTCOUNT[0]
  usb_fn_dci()->usb_dci_event_buffer_init(dci_ctx);

  //25. USBCTL_DWC_USB3_GCTL
  // Power Down Scale(0x0010000), Port Capability Dir - Device(0x00002008), Scaledown(0x000000030), DISABLE SCRAMBLE(0x00000008) 
  HWIO_USBCTL_GCTL_OUT(0x00102008);  //TODO BOLT_ADD -HWIO_USBCTL_GCTL_SCALEDOWN_BMSK document
  
  //26. USBCTL_DWC_USB3_DCFG – enable LPM
  // LPMCAP(0x400000), No. of receive buffers Nump (0x80000)
  usb_fn_dci()->usb_dci_configure_device_mode(dci_ctx->is_l1_feature_enabled, *max_speed);
  //HWIO_USBCTL_DCFG_OUT(0x480000);

  //27. USBCTL_DWC_USB3_DEVTEN – L1/L2 event
  // (0x1247) VENDEVTSTRCVDEN, ERRTICERREVTEN, U3L2L1SuspEn, CONNECTDONEEVTEN, USBRSTEVTEN, DISSCONNEVTEN
  HWIO_USBCTL_DEVTEN_OUT(
    HWIO_USBCTL_DEVTEN_VENDEVTSTRCVDEN_BMSK
    | HWIO_USBCTL_DEVTEN_ERRTICERREVTEN_BMSK
    | HWIO_USBCTL_DEVTEN_U3L2L1SUSPEN_BMSK
    | HWIO_USBCTL_DEVTEN_CONNECTDONEEVTEN_BMSK
    | HWIO_USBCTL_DEVTEN_USBRSTEVTEN_BMSK
    | HWIO_USBCTL_DEVTEN_DISSCONNEVTEN_BMSK);

  //28. Config EP0, EP1
  //Sequence details are in section 2.16.2.3 - 2.16.2.4  
  usb_fn_dci()->usb_dci_core_init(dci_ctx);

  //29.USBCTL_DWC_USB3_DALEPENA - Device Active USB Endpoint Enable
  // Enable EP0, EP1
  HWIO_USBCTL_DALEPENA_OUTM(HWIO_USBCTL_DALEPENA_USBACTEP_BMSK, 
                       (0x3 << HWIO_USBCTL_DALEPENA_USBACTEP_SHFT));


  //30. Added 1K page boundary limit per BDC logs
  HWIO_USBCTL_GSBUSCFG1_OUT(0x1700); // EN1KPAGE, PIPE Trans Limit 15 requests  //todo BOLT_CHANGE SW 15 rquest is E


  //31.To control type of AHB INCR transfers on Master port
  //By default, usb dma can initiate AHB transfer of INCR4, 8, and 16 on AHB master
  //soc does not support INC4, INCR 8 and 16 from USB DMA. so we have to disable INCR4, 8 and 16 before RUN_STOP bit is set
  HWIO_USBCTL_GSBUSCFG0_OUTM(0x000000ff, 0x0);

#if defined(TARGET_FPGA) 
      usb_dci_ulpi_test(dci_ctx->ulpi_debug);
#endif

  //32. Set the RUN/STOP bit in DCTL
  reg_in = HWIO_USBCTL_DCTL_IN;
  // RUN_STOP 
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_DCTL_RUN_STOP_BMSK,
                             HWIO_USBCTL_DCTL_RUN_STOP_SHFT);
  // HIRD_THRESHOLD
  reg_in = USB_VAR_OUTM(reg_in, 0x7, HWIO_USBCTL_DCTL_HIRDTHRES_BMSK,
                             HWIO_USBCTL_DCTL_HIRDTHRES_SHFT);

  // LPM_NYET_THRES
  reg_in = USB_VAR_OUTM(reg_in, 0x8, HWIO_USBCTL_DCTL_LPM_NYET_THRES_BMSK,
                             HWIO_USBCTL_DCTL_LPM_NYET_THRES_SHFT);
  // ACCEPT_U2_ENA
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_DCTL_ACCEPTU2ENA_BMSK,
                             HWIO_USBCTL_DCTL_ACCEPTU2ENA_SHFT);
  // ACCEPT_U1_ENA
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_DCTL_ACCEPTU1ENA_BMSK,
                             HWIO_USBCTL_DCTL_ACCEPTU1ENA_SHFT);
  HWIO_USBCTL_DCTL_OUT(reg_in);

  HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK, 
    0x8 << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
  
#if !defined(TARGET_FPGA)  
  //33,34 not for FPGA external PHY
  usb_fn_dci_target()->usb_dci_enable_vbus_valid(*max_speed);
#endif
/*              
   35. Setup TRB for all EPs
   Sequence details are in 2.12.6.2 
  
   36. Start EP transfer for Enumeration, etc.
   Sequence details are in 2.12.6.2 
*/
}

// ===========================================================================
/**
 * @function    usb_dci_init
 * 
 * @brief   This function will be called by the DCD to initialize the hw(dci) ctx
 * 
 * @param   core_id             - Core ID of the controller
 *  
 * @param   ** dci_ctx_ptr      - DCI context pointer 
 *  
 * @param   * dcd_ctx          - DCD context pointer (core ctx)
 *  
 * @param   *callback_table_ptr - Function Call back Pointer
 *               
 * @return  None.
 * 
 */
// ===========================================================================
uint32 usb_dci_init(usb_core_type core_id, void** dci_ctx_ptr, void* dcd_ctx, 
  usb_dcd_callback_t* cb_table_ptr, uint32 feature_flags)
{
  usb_dci_ctx_t* dci_ctx = NULL;

  USB_LOG(log_usb_dci_init);

  if (NULL == dcd_ctx || NULL == cb_table_ptr)
  {
    USB_LOG_ERR(log_usb_dci_init__null_ptr);
    return DCI_ERROR; 
  }

  USB_ASSERT(dci_ctx = (usb_dci_ctx_t*)usb_fn_mem_util()->usb_malloc_uncached(sizeof(usb_dci_ctx_t))); 

  USB_ASSERT(dci_ctx->usb_control_tx_buffer = (uint8*)usb_fn_mem_util()->usb_malloc_uncached(USB_CTRL_TX_BUFFER_SIZE));

  /* Update core_ctx */
  *dci_ctx_ptr = (void**)dci_ctx;

  /* DCI Context Initialization */
  dci_ctx->dcd_ctx = dcd_ctx;
  (dci_ctx->dcd_cb).notify = cb_table_ptr->notify;
  dci_ctx->core_id = core_id;

  dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;

  dci_ctx->is_attached = FALSE;
  dci_ctx->link_state = LS_SS_DIS;

  dci_ctx->test_mode = USB_PORT_TEST_DISABLE;
  dci_ctx->test_mode_enabled = FALSE;

  dci_ctx->usb_set_stall_on_xfer_nrdy_wrong_dir= TRUE;
  dci_ctx->usb_dci_soft_rst_enabled = TRUE;
  dci_ctx->remote_wakeup_enabled = FALSE;

  dci_ctx->is_suspended= FALSE;
  dci_ctx->is_disconnected = FALSE;
  dci_ctx->is_usb_clk_on = FALSE;

#if defined (USB_L1_ENABLE)
  dci_ctx->is_l1_feature_enabled = feature_flags & WHS_USB_FEATURE_L1_MASK;
#else
  dci_ctx->is_l1_feature_enabled = FALSE;
#endif

#if defined (USB_L2_ENABLE)
  dci_ctx->is_l2_feature_enabled = feature_flags & WHS_USB_FEATURE_L2_MASK;
#else
  dci_ctx->is_l2_feature_enabled = FALSE;
#endif

  // Initialize TRBs including link TRB
  usb_fn_dci()->usb_dci_init_trb_ring(dci_ctx);

  return DCI_OK; 
}
//============================================================================
/**
 * @function  usb_dci_core_init
 *
 * @brief
 *    This function initializes the USB device controller according to the SNPS spec:
 *    1.
 *  @Note : Endpoint 0 is designed as a control endpoint only and does not need to be
 *      configured using ENDPTCTRL0 register.
 *      It is also not necessary to initially prime Endpoint 0
 *      because the first packet received will always be a setup packet. 
 *      The contents of the first setup packet will require a response
 *      in accordance with USB device framework (Chapter 9) command set.
 *
 * @param dcd_context_ptr    
 *              A pointer to a DCD initernal context. This is not NULL.
 *
 * @return status
 *              0 = ok , otherwise error.
 *
 * @ref SNPS spec "":
 *      Chapter 8.1.1 
 *      HPG 4.4. 2 ,  steps 18 -19
 *      
 *
 */
//============================================================================
void usb_dci_core_init(usb_dci_ctx_t* dci_ctx)
{
  uint32 ep0, dir;
  usb_ep_cmd_t ep_cmd;

  USB_ASSERT(dci_ctx);

  USB_LOG(log_usb_dci_core_init);
 
  /* Initialize of  the core ( SNPS 8.1.1 ,  HPG 4.4. 2 ,  steps 18 -19 ) */
  memset(&ep_cmd, 0, sizeof(ep_cmd));

  /* Initialize and configure  EP info ( for EP0 OUT, EP0 IN ) */
  ep0 = DCI_EP0; 
  /* Issue DEPSTARTCFG  ( SNPS 6.3.2.5.8  and Table 8-1) */
  ep_cmd.start_new_config.cmd.cmd_typ = USB_EP_CMD_START_NEW_CONFIG_VAL;
  ep_cmd.start_new_config.cmd.cmd_act = 1 ;

  if (DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep0, DIR_RX, &ep_cmd))
  {
    USB_LOG_ERR_1(log_usb_dci_core_init__write_ep_cmd_line_D, __LINE__);
  } 

  for (dir =0 ; dir < DCI_MAX_DIRECTION; dir++) 
  {

    memset(&ep_cmd, 0, sizeof(ep_cmd));

    /* Set EP config (SNPS 6.3.2.5.1 , Table 6-69) */
    ep_cmd.set_ep_config.cmd.cmd_typ = USB_EP_CMD_SET_EP_CONFIG_VAL;
    ep_cmd.set_ep_config.cmd.cmd_act = USB_EXECUTE_EP_GENERIC_COMMAND;
    ep_cmd.set_ep_config.usb_ep_num =
    (ep0 << USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_NUM_SHIFT) |
    (dir << USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_DIR_SHIFT);
    ep_cmd.set_ep_config.fifo_num  = USB_EP_FIFO_NUMBER; // FIFO # of CTRL IN/OUT both should be set to same value.
    ep_cmd.set_ep_config.xfer_nrdy_en = USB_ENABLE_XFER_NOT_READY;
    ep_cmd.set_ep_config.xfer_cmpl_en = USB_ENABLE_XFER_COMPLETE;
    ep_cmd.set_ep_config.max_packet_sz = USB_EP0_MAX_PACKET_SIZE_SUPER;
    ep_cmd.set_ep_config.brst_siz = USB_BURST_SIZE_1;
    ep_cmd.set_ep_config.ep_type = USB_EP_TYPE_CONTROL;
    ep_cmd.set_ep_config.intr_num = USB_DEV_INTR_LINE;

    /* Push the EP config */
    if(DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep0, dir, &ep_cmd))
    {
      USB_LOG_ERR_1(log_usb_dci_core_init__write_ep_cmd_line_D, __LINE__);
    }

    memset(&ep_cmd, 0, sizeof(ep_cmd));  

    /* Config EP xfer resorces  (SNPS 6.3.2.5.2 , Table 6-70) */
    ep_cmd.set_ep_xfer_rsc_config.cmd.cmd_typ = USB_EP_CMD_SET_EP_XFER_RSC_CONFIG_VAL;
    ep_cmd.set_ep_xfer_rsc_config.cmd.cmd_act = USB_EXECUTE_EP_GENERIC_COMMAND;
    ep_cmd.set_ep_xfer_rsc_config.num_xfer_res = 1; /*Bit field needs to be set to 1*/

    //Push the EP cmd
    if(DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep0, dir, &ep_cmd))
    {
      USB_LOG_ERR_1(log_usb_dci_core_init__write_ep_cmd_line_D, __LINE__);
    }

    /* Initialize the TRBs for EP0 OUT */
    if (dir == DIR_RX)
    {
      dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;
    }
  }
}

//============================================================================
/**
 * @function  usb_dci_write_ep_cmd
 *
 * @brief
 *    This function updates the USB EP data with the device controller 
 *    
 * @param ep - The endpoint number for which the command is being written
 * @param dir - Direction of the endpoint IN/OUT
 * @param ep_cmd - The command type for the Endpoint. Ref.6.3.2.5
 *
 * @return status
 *              0 = ok , otherwise error.
 *
 * @ref SNPS spec "":
 *      Chapter 6.3.2.5 " "
 *      
 *
 */
//============================================================================
uint32 usb_dci_write_ep_cmd(usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, usb_ep_cmd_t *ep_cmd)
{
  uint8 ep_index;
  uint32 reg_val = 0;
  uint32 delay_count = 0;

  USB_ASSERT(dci_ctx && ep_cmd);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  usb_fn_mem_util()->usb_mem_barrier();

  ep_index = USB_EP_INDEX(ep, dir); /* index cannot exceed 32 */

  /* make sure a command isnt executing currently */
  if (HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INMI(ep_index,HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_BMSK))
  {
    USB_LOG_ERR_1(log_usb_dci_write_ep_cmd__ep_cmd_active_ep_index_D, ep_index);
  }

  /* write the command and parameter registers */
  switch (ep_cmd->template.cmd.reg.cmd_typ) 
  {
    case USB_EP_CMD_SET_EP_CONFIG_VAL:
    case USB_EP_CMD_START_XFER_VAL:
    // write command parameter 1 register and fall through
    HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_OUTI(ep_index,ep_cmd->template.parameter1);


    case USB_EP_CMD_SET_EP_XFER_RSC_CONFIG_VAL:
    // write command parameter 0 register and fall through
    HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_OUTI(ep_index,ep_cmd->template.parameter0);

    case USB_EP_CMD_GET_EP_STATE_VAL:
    case USB_EP_CMD_SET_STALL_VAL:
    case USB_EP_CMD_CLEAR_STALL_VAL:
    case USB_EP_CMD_UPDATE_XFER_VAL:
    case USB_EP_CMD_END_XFER_VAL:
    case USB_EP_CMD_START_NEW_CONFIG_VAL:
    // write the command register
    HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_OUTI(ep_index,ep_cmd->template.cmd.dword);
    break;

    default:
    USB_LOG_ERR_1(log_usb_dci_write_ep_cmd__ep_cmd_invalid_type_D, ep_cmd->template.cmd.reg.cmd_typ);
    return USB_ERR_INVALID_COMMAND;
  }

  // Optimization - poll cmdact w/o delay until it is zero
  for(delay_count = 0; delay_count < USB_CMDACT_DELAY; delay_count++)
  {
    reg_val = HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INMI(ep_index, HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_BMSK);   
    if (!(reg_val & HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_BMSK))
    {
      return DCI_OK;
    }
  }

  // poll cmdact with delay untill it is zero.
  for(delay_count = 0; delay_count < USB_CMDACT_DELAY_US; delay_count++)
  {
    reg_val = HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INMI(ep_index, HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_BMSK);   
    if (!(reg_val & HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_BMSK))
    {
#ifndef TARGET_FPGA    
      USB_LOG_ERR_1(log_usb_dci_write_ep_cmd__cmdact_us_delay_cnt_D, delay_count);
#endif
      return DCI_OK;
    }
    usb_fn_util()->usb_delay_us(1);
  }

  USB_LOG_ERR_1(log_usb_dci_write_ep_cmd__cmd_timedout_delay_cnt_D, delay_count);
  return DCI_ERROR;
}

//============================================================================
/**
 * @function  usb_dci_write_dev_cmd
 *
 * @brief
 *    This function updates the USB EP data with the device controller 
 *    
 * @param ep_cmd
 *
 * @return status
 *              0 = ok , otherwise error.
 *
 * @ref SNPS spec "":
 *      Chapter 6.3.2.5 " "
 *      
 *
 */
//============================================================================
static uint32 usb_dci_write_dev_cmd(usb_dci_ctx_t* dci_ctx, usb_dev_cmd_t *dev_cmd)
{
  uint32 reg_val = 0x0;
  uint32 delay_count = 0;

  USB_ASSERT(dci_ctx && dev_cmd);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }
  
  if(HWIO_USBCTL_DGCMD_INM(HWIO_USBCTL_DGCMD_CMDACT_BMSK))
  {
    USB_LOG_ERR(log_usb_dci_write_dev_cmd__cmd_active);
  }

  /*write the command and parameter register*/
  switch(dev_cmd->template.cmd.reg.cmd_typ)
  {
    case USB_DEV_CMD_TX_SET_LINK_FN_LMP_VAL:            
    case USB_DEV_CMD_SET_PERIODIC_PARAMS_VAL:           
    case USB_DEV_CMD_TX_FN_WAKE_DEV_NOTIFY_VAL:         
    case USB_DEV_CMD_SET_SCRATCHPAD_BUF_LO_VAL:         
    case USB_DEV_CMD_SET_SCRATCHPAD_BUF_HI_VAL:         
    case USB_DEV_CMD_TX_FN_HOST_REQ_NOTIFY_VAL:         
    case USB_DEV_CMD_TX_DEVICE_NOTIFY_VAL:              
    case USB_DEV_CMD_SELECTED_FIFO_FLUSH_VAL:
      /*write the parameter*/
      HWIO_USBCTL_DGCMDPAR_OUT(dev_cmd->template.parameter);
      /*write the command register*/ 
      
      HWIO_USBCTL_DGCMD_OUT(dev_cmd->template.cmd.dword);
      break;
    case USB_DEV_CMD_ALL_FIFO_FLUSH_VAL:
      /*write the command register*/ 
      HWIO_USBCTL_DGCMD_OUT(dev_cmd->template.cmd.dword);
    break;
    
    default:
    USB_LOG_ERR_1(log_usb_dci_write_dev_cmd__cmd_invalid_type_D, dev_cmd->template.cmd.reg.cmd_typ);
    return USB_ERR_INVALID_COMMAND;			
  }

  // Optimization - poll cmdact w/o delay until it is zero
  for(delay_count = 0; delay_count < USB_CMDACT_DELAY; delay_count++)
  {
    reg_val = HWIO_USBCTL_DGCMD_INM(HWIO_USBCTL_DGCMD_CMDACT_BMSK);
    if(!(reg_val & HWIO_USBCTL_DGCMD_CMDACT_BMSK))
    {
      return DCI_OK;
    }
  }

  for(delay_count = 0; delay_count < USB_CMDACT_DELAY_US; delay_count++)
  {
    reg_val = HWIO_USBCTL_DGCMD_INM(HWIO_USBCTL_DGCMD_CMDACT_BMSK);
    if(!(reg_val & HWIO_USBCTL_DGCMD_CMDACT_BMSK))
    {
#ifndef TARGET_FPGA
      USB_LOG_ERR_1(log_usb_dci_write_dev_cmd__cmdact_us_delay_cnt_D, delay_count);
#endif
      return DCI_OK;
    }
    usb_fn_util()->usb_delay_us(1);
  }

  USB_LOG_ERR_1(log_usb_dci_write_dev_cmd__cmd_timedout_delay_cnt_D, delay_count);
  return DCI_ERROR; 
}

//============================================================================
/**
 * @function  usb_dci_event_buffer_init
 *
 * @brief
 *    This function initializes the USB device controller event buffers:
 *    
 * @param None
 *
 * @return None
 *
 * @ref SNPS spec "":
 *      Chapter 8.2.2 " "
 *      
 *
 */
//============================================================================
void usb_dci_event_buffer_init(usb_dci_ctx_t* dci_ctx)
{
  USB_ASSERT(dci_ctx);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  memset((void*)dci_ctx->usb_event_buffer, 0xFF, EVENT_BUFFER_SIZE);  
  dci_ctx->usb_evt_buf_info.buf = dci_ctx->usb_event_buffer;

  dci_ctx->usb_evt_buf_info.cur_pos = 0x0; 

  USB_LOG(log_usb_dci_event_buffer_init);

  HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_OUTMI(0, HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_EVNTADRLO_BMSK,
                                                   (((uint32)(dci_ctx->usb_evt_buf_info.buf)) << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_EVNTADRLO_SHFT));
  
  HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_OUTMI(0, HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_EVNTADRHI_BMSK,
                                                    0x0 << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_EVNTADRHI_SHFT);
  HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_OUTMI(0, HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_EVENTSIZ_BMSK,
                                                  EVENT_BUFFER_SIZE << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_EVENTSIZ_SHFT);
  HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OUTMI(0,HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK,
                                                    0x0 << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_SHFT);
}

// ===========================================================================
/**
 * @function    usb_dci_set_run_stop
 * 
 * @brief   API used to set or clear Run Stop Bit.
 * 
 * 
 * @param   dci_ctx - DCI layer context.
 * @param  Set - Value for setting or clearing run stop
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_set_run_stop(usb_dci_ctx_t* dci_ctx, boolean set)
{
  USB_LOG_1( log_usb_dci_set_run_stop__state_D, set);
  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }
  HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_RUN_STOP_BMSK,(set << HWIO_USBCTL_DCTL_RUN_STOP_SHFT));
}

// ===========================================================================
/**
 * @function    usb_dci_get_bm1_from_uf
 * 
 * @brief   This API converts micro-frame or frame difference into 
 *          bInterval - 1 (bm1) provided micro-frame or frame is a power of 2. 
 *          e.g. 1, 2, 4, 8 etc.
 * 
 * @param  uf - micro-frames or frames on USB bus.
 * @return  0 = invalid bInterval, val > 0 = valid bInterval.
 * 
 */
// ===========================================================================
uint8 usb_dci_get_bm1_from_uf(uint16 uf)
{
  uint8 i = 0;

  if((uf & (uf-1)) == 0) // make sure uf difference is power of 2
  {
    for(i = 0; uf > 0; i++)
    {
      uf >>= 1;
    }

    if(i > 0)
    {
      i -= 1; // i is bInterval, subtract 1 to get bm1
    }
  }
  return i;
}

//============================================================================
/**
 * @function usb_dci_handle_ep_event
 * @brief   Check for any pending endpoint events  and call the relevant callbacks.
 *
 * @param usb_event_depevt - Device Endpoint specific events.    
 *
 * @return  none.
 *
 * @ref SNPS spec 
 *      Chapter 8.2.2  
 *      Chapter 6.2.8.1 DEPEVT
 *
 */
//============================================================================
void usb_dci_handle_ep_event(usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt)
{
  uint8 phy_ep_num = 0x0; 
  uint8 ep;
  uint8 dir;
  usb_trb_ring_t* trb_ring_ptr;
   
  USB_ASSERT(depevt);

  phy_ep_num = depevt->phy_ep_number;
  USB_LOG(log_usb_dci_handle_ep_event__event + depevt->ep_xfer_event);

  if(phy_ep_num < 2)
  {
    usb_fn_dci()->usb_dci_handle_ctrl_transfers(dci_ctx, depevt);
  }
  else
  {
    ep  = USB_PHY_EP_TO_EP(phy_ep_num);
    dir = USB_PHY_EP_TO_DIR(phy_ep_num);

    switch(depevt->ep_xfer_event)
    {
      case USB_EVT_EP_XFER_IN_PROGRESS:
      {
        trb_ring_ptr = &dci_ctx->usb_trb_ring[ep][dir];

        if(trb_ring_ptr->xfer_res_idx == USB_RSC_IDX_NOT_SET)
        {
          break;
        }

        if(trb_ring_ptr->trb_ctl == USB_TRB_CTL_ISOCHRONOUS_FIRST && depevt->event_status & 0x8)
        {
          if(trb_ring_ptr->missed_isoc == 0) // notify DCD layer of only first missed ISOC event
          {
            // DCD layer will notify appropriate handler that will cancel pending transfers
            dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_STOP_SESSION,
              (void*)((dir << 7) | ep));
          }
          trb_ring_ptr->missed_isoc++;
          USB_LOG_ERR_3(log_usb_dci_handle_ep_event__missed_isoc_on_ep_D_dir_D_uF_D, ep, 
            dir, depevt->event_param);
          break;
        }
        usb_fn_dci()->usb_dci_handle_transfer_complete(dci_ctx, depevt);
      }
      break;

      case USB_EVT_EP_XFER_COMPLETE:
      {
        trb_ring_ptr = &dci_ctx->usb_trb_ring[ep][dir];
        usb_fn_dci()->usb_dci_handle_transfer_complete(dci_ctx, depevt);
      }
      break;

      case USB_EVT_EP_XFER_NOT_READY: 
      {
        uint16 curr_uf_diff;
        trb_ring_ptr = &dci_ctx->usb_trb_ring[ep][dir];
        if (trb_ring_ptr->trb_ctl == USB_TRB_CTL_ISOCHRONOUS_FIRST)
        {
          trb_ring_ptr->xfer_nrdy_uf_prev = trb_ring_ptr->xfer_nrdy_uf;
          trb_ring_ptr->xfer_nrdy_uf = depevt->event_param;
          curr_uf_diff = (trb_ring_ptr->xfer_nrdy_uf - trb_ring_ptr->xfer_nrdy_uf_prev);

          if ((trb_ring_ptr->xfer_nrdy_uf_diff != 0) && (trb_ring_ptr->xfer_nrdy_uf_diff == curr_uf_diff))
          {
            trb_ring_ptr->xfer_nrdy_uf_diff_cnt++;
            if(trb_ring_ptr->xfer_nrdy_uf_diff_cnt >= USB_DCI_ISOC_RECONFIG_THRES)
            {
              uint8 bm1 = usb_fn_dci()->usb_dci_get_bm1_from_uf(trb_ring_ptr->xfer_nrdy_uf_diff);
              usb_isoc_reconfig_sess_t sess_cfg = { ep, dir, bm1 };
              trb_ring_ptr->xfer_nrdy_uf_diff_cnt = 0;

              // if bm1 is valid then request DCD layer to reconfigure ISOC endpoint to new bm1.
              if(bm1)
              {
                USB_LOG_ERR_1(log_usb_dci_handle_ep_event__sync_to_host_polling_at_rate_uF_D, depevt->event_param);               
                dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_RECONFIG_SESSION, &sess_cfg);              
              }
            }
          }
          else
          {
            trb_ring_ptr->xfer_nrdy_uf_diff = curr_uf_diff;
            trb_ring_ptr->xfer_nrdy_uf_diff_cnt = 0;
          }

          trb_ring_ptr->missed_isoc = 0;
          USB_LOG_ERR_3(log_usb_dci_handle_ep_event__xfer_nrdy_isoc_ep_D_dir_D_uf_D, ep, dir, 
            depevt->event_param);

          // pass endpoint address as data to callback.
          dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_START_SESSION, (void*)((dir << 7) | ep));
        }
      }
      break;

      case USB_EVT_EP_CMD_COMPLETE:
      {
      }
      break;
    }
  }
}

//============================================================================
/**
 * @function usb_dci_handle_dev_event
 * @brief   Check for any pending dev events  and call the relevant callbacks.
 *          There are some requests which the current SBL driver doesn't 
 *          support. All those events are simply not handled. 
 *
 * @param usb_event_devt    
 *
 * @return  none.
 *
 * @ref SNPS spec 
 *      Chapter 8.2.2  
 *      Chapter 6.2.8.2 DEVT
 *
 */
//============================================================================
void usb_dci_handle_dev_event(usb_dci_ctx_t* dci_ctx, usb_event_devt_t  *devevt)
{
  USB_ASSERT(dci_ctx && devevt);
  
  USB_LOG_2(log_usb_dci_handle_dev_event__disconnect_D, devevt->dev_event, 
    devevt->event_info);
  
  switch(devevt->dev_event)
  {
    case USB_EVT_DEV_USB_RESET:
      usb_fn_dci()->usb_dci_handle_usb_reset(dci_ctx);
    break;

    case USB_EVT_DEV_CONNECT_DONE:
      usb_fn_dci()->usb_dci_handle_connect_done(dci_ctx);
    break;

    case USB_EVT_DEV_USB_LINK_STATE_CHANGE:
      usb_fn_dci()->usb_dci_handle_link_status_change(dci_ctx, devevt->event_info);
    break;   

    case USB_EVT_DEV_DISCONNECT_EVENT:
      usb_fn_dci()->usb_dci_handle_usb_disconnect(dci_ctx);
    break;

    case USB_EVT_DEV_REMOTE_WAKE_UP:
      usb_fn_dci()->usb_dci_handle_wakeup(dci_ctx);
    break;

    case USB_EVT_DEV_HIBERNATION_REQUEST:
    break;

    case USB_EVT_DEV_SUSPEND_ENTRY:
      usb_fn_dci()->usb_dci_handle_suspend_entry(dci_ctx);
    break;

    case USB_EVT_DEV_START_OF_FRAME:
    break;

    case USB_EVT_DEV_ERRATIC_ERROR:
    break;

    case USB_EVT_DEV_CMD_COMPLETE:
    break;

    case USB_EVT_DEV_EVENT_BUFFER_OVERFLOW:
      // This is error condition and this should not happen.
      USB_ERR_HALT_LOG(FALSE, log_usb_dci_handle_dev_event__event_buffer_overflow); 
    break;

    case USB_EVT_DEV_VNDR_DEV_TST_LMP_RCVED:
    break;

    default:
    break;

  }
}

//============================================================================
/**
 * @function usb_dci_poll_events
 * @brief   Check for any pending events (interrupts are disabled) and call the relevant callbacks.
 *
 *   When an event occurs within the core, hardware checks the enable bit that corresponds to the event 
 *   to decide whether the event will be written to the Event Buffer or not. 
 *   The Event Buffer contains one of the following types of information:
 *      -  Endpoint-Specific Event (DEPEVT)
 *      -  Device-Specific Event (DEVT)
 *   
 *   Number of events ( interrupters)  -  1
 *   Event buffer size                         -  1024 bytes
 *   Number entries in each buffer      -  256 (each event is 4 bytes long ) 
 *   initial event count                        -  0
 *   
 *   Logic : 
 *   check for the event count. If the event count is greater than zero, check for the event type ( EP or Dev ) and handle 
 *   the corresponding event. Update the HW about the number of events ( in bytes) SW has processed. 
 *   Move to the next 4 bytes (i.e. next event) in the current event and repeat it until there are no pending events.
 *               
 * @return  none.
 *
 * @ref SNPS spec 
 *      Chapter 8.2.2 , 6.2.7.3 ,  6.2.8
 *
 */
//============================================================================
void usb_dci_poll_events(usb_dci_ctx_t* dci_ctx)
{
  uint32 evt_byte_count;
  uint32 cur_buf_pos;
  
  USB_ASSERT(dci_ctx);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }
  
  /* Get the event count  ( number of valid bytes ) from the event buffer - SNPS 6.2.7.3 */
  evt_byte_count = HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INMI(0,
     HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK);

  if (!evt_byte_count)
  {
    //No new events in buffer 
    return;
  }

  while (evt_byte_count > 0) 
  {
    usb_event_t event;
    uint32 evt_read_max_tries = USB_MAX_EVENT_READ_TRIES;

    /* position of the event to be handled in the current event buffer */
    cur_buf_pos = dci_ctx->usb_evt_buf_info.cur_pos;

    /* Move the event buffer to the new location */
    event.generic = *(volatile uint32 *)((uint8 *)(dci_ctx->usb_evt_buf_info.buf) + cur_buf_pos );

    /* Fix for race condition that exists when USB controller writes to QSRAM:
       USB HW writes events to buffer in QSRAM through SNOC. When SNOC is loaded the write 
       can get delayed. If SW reads event before write to QSRAM completes SW reads stale event. 
       Once a valid value is read from event buffer SW invalidates event buffer position.
    */

    while((event.generic == USB_DCI_INVALID_EVENT) && --evt_read_max_tries)
    {
        usb_fn_util()->usb_delay_us(50);
        event.generic = *(volatile uint32 *)((uint8 *)dci_ctx->usb_evt_buf_info.buf + cur_buf_pos );
    }
    *(volatile uint32 *)((uint8 *)dci_ctx->usb_evt_buf_info.buf + cur_buf_pos) = USB_DCI_INVALID_EVENT;

    if (evt_read_max_tries == 0)
    {
      USB_LOG_ERR(log_usb_dci_poll_events__invalid_event);
    }

    USB_LOG_1(log_usb_dci_poll_events__event_D, event.generic);

    /* EP specific Event */
    if(event.depevt.event_type == USB_EVT_TYPE_EP)
    {
      usb_fn_dci()->usb_dci_handle_ep_event(dci_ctx, &event.depevt);
    }
    else if(event.devt.event_type == USB_EVT_TYPE_NON_EP && !(event.devt.dev_spec_event) )
    {
      /* Dev specific Event  */
      /* Event type should be "Non Ep'' and bits-7:1  should be Zero ( SNPS pg. 478, Table-649 ) */
      usb_fn_dci()->usb_dci_handle_dev_event(dci_ctx, &event.devt);
    }
    else
    {
      USB_LOG_ERR(log_usb_dci_poll_events__unknown_event_type);
    }

    /* Move to the next Event in the current buffer */
    /* Event buffer is 1K in size and each Event entry is 4 bytes long. We wrap at 1K. */
    /* Wrap the circular buffer at EVENT_BUFFER_SIZE to ensure there is no overflow */
    dci_ctx->usb_evt_buf_info.cur_pos = (cur_buf_pos + USB_EVT_BUFFER_UNIT_SIZE ) % EVENT_BUFFER_SIZE ;
    evt_byte_count -= USB_EVT_BUFFER_UNIT_SIZE;
    USB_LOG_DBG_2(log_usb_dci_poll_events__bytes_left_D_cur_pos_D, evt_byte_count, 
      dci_ctx->usb_evt_buf_info.cur_pos);

    /* SW indicates to HW how many events it processed by writing the byte count (we process 4 at a time ) */
    HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OUTMI(0,
        HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK,
        USB_EVT_BUFFER_UNIT_SIZE << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_SHFT);
  }
}

// ===========================================================================
/**
 * @function    usb_dci_handle_ctrl_transfers
 * 
 * @brief       This function handles control transfers
 * 
 * @details 
 *         
 *  @note : After receiving a new setup packet ( with xfer complete ) dci delegates the handling to dcd.
 *              Setup is processed and corresponding DATA and STATUS3 (3 stage)  or STATUS2 stages (2 stage) requests 
 *              are queued but are submitted to the HW only after receiving XFER_NRDY event for the particular stage.
 * 
 * @param *depevt - Pointer to Control Endpoint Events    
 *
 * @return  none.
 *
 * @see usb_dci_poll_events
 *
 * @ref SNPS spec 
 *     Chapter 8.4 Control transfer programming model (2.3 hardware and later)
 *     Chapter 8.5.2 Operational Model For Setup Transfers
 *
 */
// ===========================================================================
static void usb_dci_handle_ctrl_transfers(usb_dci_ctx_t* dci_ctx,
                                                   usb_event_depevt_t *depevt)
{
  usb_evt_ep_evt_type    ep_evt_type;
  uint8 ep,dir;
  uint8 phy_ep_num;

  USB_ASSERT(dci_ctx && depevt);
  
  phy_ep_num = depevt->phy_ep_number;
  ep  = USB_PHY_EP_TO_EP(phy_ep_num);
  dir = USB_PHY_EP_TO_DIR(phy_ep_num);

  /* EP event completion type*/
  ep_evt_type = (usb_evt_ep_evt_type)depevt->ep_xfer_event;


  switch (ep_evt_type) 
  {
    case USB_EVT_EP_XFER_COMPLETE:

      /* Setup stage complete  */
      if (dci_ctx->ctrl_state == EP0_STATE_SETUP_TRB)
      {
        dci_ctx->ctrl_state = EP0_STATE_INTRPT_SETUP;
        USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_complete_setup_D, 
            depevt->event_status);

        usb_fn_dci()->usb_dci_handle_transfer_complete(dci_ctx, depevt);

        dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_CTRL_SETUP_COMPLETE,
                                            (void*)dci_ctx->usb_trb_list);
      }
      /* Data stage complete   */
      else if (dci_ctx->ctrl_state == EP0_STATE_DATA_IN_PROGRESS)
      {
        /* Host aborted DATA stage, then start over */
        if(depevt->event_status == 0)
        {
          dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;
          dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_CTRL_ERROR, NULL);
        }   
        else
        {
          USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_complete_data_D, depevt->event_status);
          dci_ctx->ctrl_state = EP0_STATE_STATUS_3;
          usb_fn_dci()->usb_dci_handle_transfer_complete(dci_ctx, depevt);
        }
      }
      else if (dci_ctx->ctrl_state == EP0_STATE_DATA)
      {
        USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_complete_unexpected_D, depevt->event_status);
      }
      /* status stage complete */
      else if (dci_ctx->ctrl_state == EP0_STATE_STATUS_2 ||
               dci_ctx->ctrl_state == EP0_STATE_STATUS_3)
      {
        USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_complete_status_D, depevt->event_status);
        usb_fn_dci()->usb_dci_handle_transfer_complete(dci_ctx, depevt);

        /* start a new setup */
        dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;
        dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_CTRL_STATUS_COMPLETE, NULL);
      }
      else
      {
        /* Default handler returns stall for restarting state machine */
        usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
      }

    break; /* USB_EVT_EP_XFER_COMPLETE */

    case USB_EVT_EP_XFER_NOT_READY: 

    /* We are expecting a xfercomplete but, instead, we receive xferNotReady(Setup), 
      * we should STALL and restart  the control transfers.  
      *  Otherwise, we just continue waiting for the XferComplete event. 
      */
      if(dci_ctx->ctrl_state == EP0_STATE_SETUP_TRB)
      {
        USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_nrdy_in_setup_stage_dir_D, dir);
        dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;
      }
      else if(dci_ctx->ctrl_state == EP0_STATE_DATA)
      {
        if (depevt->event_status == USB_DDEPEVT_STATUS_CONTROL_DATA)
        {
          USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_nrdy_data_dir_D, dir);
          if(dci_ctx->ctrl_data_dir == dir)
          {
            dci_ctx->ctrl_state = EP0_STATE_DATA_IN_PROGRESS;
            usb_fn_dci()->usb_dci_ctrl_submit_request(dci_ctx, dir);  
          }
          else
          {
            USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_nrdy_wrong_dir_D, dci_ctx->ctrl_data_dir);
            if(dci_ctx->usb_set_stall_on_xfer_nrdy_wrong_dir == TRUE)
            {
              usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
            }
          }
        }
        else if (depevt->event_status == USB_DDEPEVT_STATUS_CONTROL_STATUS)
        {
          USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_nrdy_status_in_data_stage_D, depevt->event_status);
          usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
        }
        else
        {
          USB_LOG_2(log_usb_dci_handle_ctrl_transfers__invalid_event_status_D_ctrl_sta_D, depevt->event_status, dci_ctx->ctrl_state );
        }
      }
      else if(dci_ctx->ctrl_state == EP0_STATE_DATA_IN_PROGRESS)
      {
        if (depevt->event_status == USB_DDEPEVT_STATUS_CONTROL_DATA)
        {
          USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_nrdy_data_still_in_progress_D, depevt->event_status);
        }
        else
        {
          USB_LOG_2(log_usb_dci_handle_ctrl_transfers__invalid_event_status_D_ctrl_sta_D, depevt->event_status, dci_ctx->ctrl_state );
        }
      }
      else if (dci_ctx->ctrl_state == EP0_STATE_STATUS_2)
      {
        if (depevt->event_status == USB_DDEPEVT_STATUS_CONTROL_STATUS)
        {
          USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_nrdy_status2_D, dir);
          if(dir == DIR_TX)
          {
            usb_fn_dci()->usb_dci_ctrl_submit_request(dci_ctx, dir);
          }
          else
          {
            USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_nrdy_status2_wrong_dir_D, dci_ctx->ctrl_data_dir);
            usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
          }
        }
        else
        {
          USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_nrdy_data_in_status2_stage_D, depevt->event_status);
          usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
        }
      }
      else if (dci_ctx->ctrl_state == EP0_STATE_STATUS_3)
      {
        if (depevt->event_status == USB_DDEPEVT_STATUS_CONTROL_STATUS)
        {
          USB_LOG_1( log_usb_dci_handle_ctrl_transfers__xfer_nrdy_status3_D, dir); 
          if(dci_ctx->ctrl_data_dir != dir)
          {
            usb_fn_dci()->usb_dci_ctrl_submit_request(dci_ctx, dir);
          }
          else
          {
            USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_nrdy_status3_wrong_dir_D, dci_ctx->ctrl_data_dir);
            if(dci_ctx->usb_set_stall_on_xfer_nrdy_wrong_dir == TRUE)
            {
              usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
            }
          }
        }
        else
        {
          USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__xfer_nrdy_data_in_status3_stage_D, depevt->event_status);
          usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
        }
      }
      else
      {
        /* Default handler returns stall for restarting state machine */
        usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
      }
    break; /* USB_EVT_EP_XFER_NOT_READY */

    case USB_EVT_EP_CMD_COMPLETE:
      USB_LOG_1( log_usb_dci_handle_ctrl_transfers__event_ep_cmd_complete_D, ep_evt_type);
    break;
    
    default:
            /*The other event which occurs here is USB_EVT_EP_CMD_COMPLETE*/
      USB_LOG_ERR_1(log_usb_dci_handle_ctrl_transfers__uknown_event_D, ep_evt_type);
    break;
  }
  return;
}

// ===========================================================================
/**
 * @function    usb_dci_inc_trb_idx
 * 
 * @brief       This function increaments TRB index through a link TRB.
 * 
 * @details     
 *      To retrieve a TRB index for next TRB, index is increamented. While increamenting the index
 *      if a link TRB is encountered, the API increaments index again.
 *
 * 
 * @param *dci_ctx - DCI layer context.
 * @param ep - endpoint logical address.
 * @param dir - endpoint direction RX or TX.
 * @param *idx - pointer to TRB index to be increamented.
 *
 * @return  none.
 *
 * @see usb_dci_prepare_trbs
 *
 * @ref 
 */
// ===========================================================================
static void usb_dci_inc_trb_idx(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir, uint8 *idx)
{
  usb_trb_t *trb_ptr;

  CIRINC(*idx, DCI_TRBS);
  trb_ptr = &dci_ctx->usb_trb_list[ep][dir][(*idx)];
  if (USB_TRB_CTL_LINK_TRB == trb_ptr->trb_ctl)
  {
    CIRINC(*idx, DCI_TRBS);
  }
}

// ===========================================================================
/**
 * @function    usb_dci_handle_transfer_complete
 * 
 * @brief       This function handles transfer complete event.
 * 
 * @details     
 *      After a TRB has been initialized and submitted to the HW the device controller will execute the transfer 
 *      upon the hostinitiated request.  
 *      The DCD will be notified with a USB interrupt if the Interrupt On Complete bit was set or alternately,
 *      the DCD can poll the endpoint complete register to find when the dTD had been executed.
 *      
 * 
 * @param *depevt - Pointer to Device Endpoint Events   
 *
 * @return  none.
 *
 * @see usb_dci_poll_events
 *
 * @ref 
 */
// ===========================================================================
static void usb_dci_handle_transfer_complete(usb_dci_ctx_t* dci_ctx, usb_event_depevt_t *depevt)
{
  uint8  ep;
  uint8  dir;
  usb_urb_t *urb_ptr;
  uint8 urb_comp_idx;
  uint8 *trb_comp_idx;
  uint8 phy_ep_num; 
  volatile usb_trb_t *trb_ptr;
  uint8 hwo_loop_cnt = 0;

  USB_ASSERT(dci_ctx && depevt);

  phy_ep_num = depevt->phy_ep_number;
  ep  = USB_PHY_EP_TO_EP(phy_ep_num);
  dir = USB_PHY_EP_TO_DIR(phy_ep_num);

  if(ep >= DCI_MAX_ENDPOINTS) 
  {
    USB_LOG_ERR(log_usb_dci_handle_transfer_complete__ep_D_dir_D_out_of_bounds);
    return;
  }

  USB_LOG_DBG_3(log_usb_dci_handle_transfer_complete__ep_D_dir_D_event_status_D, ep, dir, depevt->event_status);

  // If ep0 always set comp_idx to 0 else read it from trb_ring.
  urb_comp_idx = (ep == 0) ? 0: dci_ctx->usb_trb_ring[ep][dir].urb_comp_idx;
  trb_comp_idx = &dci_ctx->usb_trb_ring[ep][dir].trb_comp_idx;
  (*trb_comp_idx) = (ep == 0) ? 0: (*trb_comp_idx);

  trb_ptr = (volatile usb_trb_t *) &dci_ctx->usb_trb_list[ep][dir][(*trb_comp_idx)];
  urb_ptr = dci_ctx->usb_trb_ring[ep][dir].urb_ptr[urb_comp_idx];

  USB_LOG_DBG_2(log_usb_dci_handle_transfer_complete__urb_comp_idx_D_trb_comp_idx_D, urb_comp_idx, (*trb_comp_idx));

  if(NULL == urb_ptr)
  {
    USB_LOG_ERR_1(log_usb_dci_handle_transfer_complete__null_ptr_urb_trb_phy_ep_num_D, phy_ep_num);
    return;
  }

  // If HWO bit is set for TRB completed TRB, wait for upto 20us to be cleared by HW.
  for(hwo_loop_cnt = 0; (trb_ptr->hwo) && (hwo_loop_cnt < USB_HWO_DELAY_CNT); hwo_loop_cnt++)
  {
    usb_fn_util()->usb_delay_us(1);
  }

  dci_ctx->usb_trb_ring[ep][dir].swo[(*trb_comp_idx)] = 0;
  urb_ptr->actual_length = urb_ptr->transfer_length - trb_ptr->buf_size;

  // Complete ZLP TRB if present
  if ( (trb_ptr->chn == 1) && (trb_ptr->ioc == 0) )
  {
    usb_fn_dci()->usb_dci_inc_trb_idx(dci_ctx, ep, dir, trb_comp_idx);
    trb_ptr = (volatile usb_trb_t *) &dci_ctx->usb_trb_list[ep][dir][(*trb_comp_idx)];
    // If HWO bit is set for TRB completed TRB, wait for upto 20us to be cleared by HW.
    for(hwo_loop_cnt = 0; (trb_ptr->hwo) && (hwo_loop_cnt < USB_HWO_DELAY_CNT); hwo_loop_cnt++)
    {
      usb_fn_util()->usb_delay_us(1);
    }

    dci_ctx->usb_trb_ring[ep][dir].swo[(*trb_comp_idx)] = 0;
    if (0 == trb_ptr->buf_ptr_lo && 0 == trb_ptr->buf_ptr_hi && trb_ptr->ioc)
    {
      USB_LOG_DBG_3(log_usb_dci_handle_transfer_complete__zlp_phy_ep_D_urb_idx_D_trb_idx_D, phy_ep_num, 
        urb_comp_idx, (uint32) (*trb_comp_idx));
    }
  }

  /* Increament URB and TRB comp idx */
  usb_fn_dci()->usb_dci_inc_trb_idx(dci_ctx, ep, dir, trb_comp_idx);
  CIRINC(dci_ctx->usb_trb_ring[ep][dir].urb_comp_idx, USB_URB_MAX);

  urb_ptr->transfer_status = USB_URB_STATUS_COMPLETE_OK;

  USB_LOG_DBG_3(log_usb_dci_handle_transfer_complete__zlp_phy_ep_D_urb_idx_D_trb_idx_D, phy_ep_num, 
    urb_comp_idx, (uint32) (*trb_comp_idx));  
  USB_LOG_DBG_2(log_usb_dci_handle_transfer_complete__urb_status_ok_urb_ptr_D_cb_ptr_D, (uint32) urb_ptr, 
    (uint32) urb_ptr->complete_callback);

  /* URB completion callbacks */
  if(urb_ptr->complete_callback != NULL) 
  {
    //xthal_dcache_region_invalidate(urb_ptr->transfer_buffer_ptr, urb_ptr->transfer_length);
    urb_ptr->complete_callback((struct usb_urb *)urb_ptr);
  }
  
  /* Enabling the TEST mode should happen after the completion of Status stage of Set_Feature (TEST) */
  if(dci_ctx->test_mode_enabled)
  {
    usb_fn_dci()->usb_dci_handle_test_mode(dci_ctx);
  }
}

// ===========================================================================
/**
 * @function    usb_dci_handle_usb_reset
 * 
 * @brief       This function handles USB Reset event.
 * 
 * @details     
 *      A bus reset is used by the host to initialize downstream devices. 
 *      When a bus reset is detected, the DEVICE CONTROLLER will:
 *       1. Renegotiate its attachment speed, 
 *       2. Reset the device address to 0, 
 *       3. Notify the DCD by interrupt (assuming the USB Reset Interrupt Enable is set). 
 *      
 *      After a reset is received, all endpoints (except endpoint 0) are disabled 
 *      and any primed transactions will be canceled by the device controller. 
 *      
 *      The DCD must perform the following tasks when a reset is received:
 *       1. If a control transfer is still in progress, complete it and get the core into the “Setup a Control-Setup TRB / Start Transfer” state
 *       2. Issue a DEPENDXFER command for any active transfers (except for the default control endpoint0).
 *       3. Issue a DEPCSTALL (ClearStall) command for any endpoint that was put into STALL mode prior to the USB Reset.
 *       4. Set DevAddr to 0. 
 * 
 * @param none    
 *
 * @return  none.
 *
 * @see usb_dci_poll_events
 *
 * @ref SNPS spec 
 *       Chapter 8.1.2 initialization on USB Reset
 */
// ===========================================================================
void usb_dci_handle_usb_reset(usb_dci_ctx_t* dci_ctx)
{
  uint8 ep, dir;

  USB_ASSERT(dci_ctx);

  USB_LOG(log_usb_dci_handle_usb_reset);


  dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;

  for (ep = 1; ep < DCI_MAX_ENDPOINTS; ep++ )
  {
    for (dir = 0; dir < DCI_MAX_DIRECTION; dir++)
    {
      /* End all of the unfinished transfers */
      usb_fn_dci()->usb_dci_cancel_transfer(dci_ctx, ep, dir);
      
      /* Clear Stall for any Halted EPs */
      usb_fn_dci()->usb_dci_unstall_endpoint(dci_ctx, ep, dir);
    }    
  }

  usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U1_INIT_ENABLE, FALSE);
  usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U2_INIT_ENABLE, FALSE);
  usb_fn_dci()->usb_dci_handle_u1_u2_enable(USB_DCI_U1_U2_ACCPET_ENABLE, FALSE);

  /* reset complete callback */
  dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_RESET, NULL);
}

// ===========================================================================
/**
 * @function    usb_dci_handle_connect_done
 * 
 * @brief       This function handles USB Connect Done event.
 * 
 * @details     
 *      
 *      The DCD must perform the following tasks when a connect done  is received:
 *       1. Read DSTS register to obtain the connection speed
 *       2. Program the RAMClkSel field to select the correct clock for the RAM clock domain. This field is
 *           reset to 0 after USB reset, so it must be reprogrammed each time on Connect Done.
 *       3. Issue a DEPCFG command (with Config Action set to “Modify”) for physical endpoints 0 & 1 with a max packet size
 *           based on speed.
 *       4. Depending on the connected speed, write to the other PHY’s control register to suspend it. 
 *       5. (optional) Based on the new MaxPacketSize of IN endpoint 0, software may choose to re-allocate
 *           the TX FIFO sizes by writing to these registers.
 * 
 * @param None    
 *
 * @return  none.
 *
 * @see usb_dci_poll_events
 *
 * @ref SNPS spec 
 *       Chapter 8.1.3 initialization on Connect Done
 */
// ===========================================================================
void usb_dci_handle_connect_done(usb_dci_ctx_t* dci_ctx)
{
  uint8 ep0, dir;   
  usb_ep_cmd_t ep_cmd;

  USB_ASSERT(dci_ctx);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  // Read DSTS to determine the speed
  dci_ctx->speed = (usb_device_connect_speed_t)HWIO_USBCTL_DSTS_INM(HWIO_USBCTL_DSTS_CONNECTSPD_BMSK);

  USB_LOG(log_usb_dci_handle_connect_done);

  if( dci_ctx->speed > USB_SUPER_SPEED)
  {
    USB_LOG_ERR_1(log_usb_dci_handle_connect_done__unknown_speed_D, dci_ctx->speed);
  }

  //  Program RAMClkSel
  HWIO_USBCTL_GCTL_OUTM(HWIO_USBCTL_GCTL_RAMCLKSEL_BMSK, 0x0 << HWIO_USBCTL_GCTL_RAMCLKSEL_SHFT);

  //Initialize and configure  EP0 info as is from usb_dcd_core_init()  but with a Max packet size based on the " speed "
  ep0 = DCI_EP0;
  for (dir =0 ; dir < DCI_MAX_DIRECTION; dir++) 
  {

    memset(&ep_cmd, 0, sizeof(ep_cmd));

    //Set EP config (SNPS 6.3.2.5.1 , Table 6-69)
    ep_cmd.set_ep_config.cmd.cmd_typ = USB_EP_CMD_SET_EP_CONFIG_VAL;
    ep_cmd.set_ep_config.cmd.cmd_act = USB_EXECUTE_EP_GENERIC_COMMAND;

    ep_cmd.set_ep_config.usb_ep_num =
      (ep0 << USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_NUM_SHIFT) |
        (dir << USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_DIR_SHIFT);
    ep_cmd.set_ep_config.fifo_num  = USB_EP_FIFO_NUMBER; 
    ep_cmd.set_ep_config.xfer_nrdy_en = USB_ENABLE_XFER_NOT_READY;
    ep_cmd.set_ep_config.xfer_cmpl_en = USB_ENABLE_XFER_COMPLETE;
    if(dci_ctx->speed == USB_SUPER_SPEED)
    {
      ep_cmd.set_ep_config.max_packet_sz = USB_EP0_MAX_PACKET_SIZE_SUPER;
    } 
    else if (dci_ctx->speed == USB_LOW_SPEED)
    {
      ep_cmd.set_ep_config.max_packet_sz = USB_EP0_MAX_PACKET_SIZE_LOW; 
    }
    else
    {
      ep_cmd.set_ep_config.max_packet_sz = USB_EP0_MAX_PACKET_SIZE_HIGH;
    }
    ep_cmd.set_ep_config.brst_siz = USB_BURST_SIZE_1;
    ep_cmd.set_ep_config.ep_type = USB_EP_TYPE_CONTROL;
    ep_cmd.set_ep_config.intr_num = USB_DEV_INTR_LINE;
    ep_cmd.set_ep_config.config_action = USB_EP_CMD_SET_EP_CONFIG_CONFIG_ACT_MODIFY;

    //Push the EP config 
    if(DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep0, dir, &ep_cmd))
    {
      USB_LOG_ERR(log_usb_dci_handle_connect_done__write_ep_cmd_fail);
    }
  }  // end for(dir<DCI_MAX_DIRECTION)


  if (dci_ctx->speed == USB_SUPER_SPEED)
  {
    HWIO_USBCTL_SS_PHY_CTRL_OUTM(HWIO_USBCTL_SS_PHY_CTRL_LANE0_PWR_PRESENT_BMSK,
                    (uint32 )0x0 << HWIO_USBCTL_SS_PHY_CTRL_LANE0_PWR_PRESENT_SHFT);
  }

  //Notify the client
  dci_ctx->is_attached = TRUE;

  /* If any pending control transfer stall state machine to recover */
  if (dci_ctx->ctrl_state != EP0_STATE_SETUP_TRB)
  {
    USB_LOG_ERR_1(log_usb_dci_handle_connect_done__ctrl_sm_state_D, dci_ctx->ctrl_state);
    usb_fn_dci()->usb_dci_ctrl_error_recover(dci_ctx);
  }

  usb_fn_dci()->usb_dci_update_packet_size(dci_ctx);

  dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_SPEED, NULL);
   
  usb_fn_isr()->usb_isr_lpm_init(dci_ctx->is_l1_feature_enabled);
  dci_ctx->is_suspended = FALSE;
}

// ===========================================================================
/**
 * @function    usb_dci_handle_usb_disconnect
 * 
 * @brief       This function handles USB device disconnect
 * 
 * @details     When the application receives a Disconnect event,
 *                  it must set DCTL[8:5] to 5. Other than this, the core does not require any initialization. 
 * 
 * @param       None    
 *
 * @return  none.
 *
 * @see usb_dci_poll_events
 *
 * @ref SNPS spec 
 *       Chapter 8.1.7 ( pg. 566)
 */
// ===========================================================================
static void usb_dci_handle_usb_disconnect(usb_dci_ctx_t* dci_ctx)
{
  uint8  ep, dir;
  
  USB_ASSERT(dci_ctx);
  USB_LOG(log_usb_dci_handle_usb_disconnect);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  if(dci_ctx->speed == USB_SUPER_SPEED )
  {
    HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK, LS_RX_DET << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
  }

  for (ep = 0; ep < DCI_MAX_ENDPOINTS; ep++ )
  {
    for (dir = 0; dir < DCI_MAX_DIRECTION; dir++)
    {
      /* End all of the unfinished transfers */
      usb_fn_dci()->usb_dci_cancel_transfer(dci_ctx, ep, dir);
    }
  }
  dci_ctx->speed = USB_UNKNOWN_SPEED;
  //usb_dci_set_max_packet_size(dci_ctx, 0);
  dci_ctx->is_attached = FALSE;
  dci_ctx->is_disconnected=TRUE;
  dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_DISCONNECT, NULL);
} 

// ===========================================================================
/**
 * @function    usb_dci_get_link_state
 * 
 * @brief       This function returns USB Link status.
 * 
 * @details     
 * 
 * @param    
 *
 * @return  usb_link_state_t
 *
 * @see 
 *
 * @ref SNPS spec 
 *        DSTS ( bits 21-18) , Table 6-60 (pg. 499)
 *       
 */
// ===========================================================================
static usb_link_state_t usb_dci_get_link_state(usb_dci_ctx_t* dci_ctx)
{
  /* Read the DSTS to detrmine the Actual state. */
  dci_ctx->link_state = (usb_link_state_t)(HWIO_USBCTL_DSTS_INM(HWIO_USBCTL_DSTS_USBLNKST_BMSK) >> HWIO_USBCTL_DSTS_USBLNKST_SHFT);
  USB_LOG_1( log_usb_dci_get_link_state__state_D, dci_ctx->link_state);
  return dci_ctx->link_state ;
}

// ===========================================================================
/**
 * @function    usb_dci_handle_link_status_change
 * 
 * @brief       This function handles USB Link status changed.
 * 
 * @details     
 * 
 * @param   state - Link State    
 *
 * @return  none.
 *
 * @see usb_dci_handle_dev_event
 *
 * @ref SNPS spec 
 *       
 */
// ===========================================================================
static void usb_dci_handle_link_status_change(usb_dci_ctx_t* dci_ctx, uint32 state)
{
  USB_ASSERT(dci_ctx);

  //Update the Link State 
  dci_ctx->link_state = (usb_link_state_t)(state & USB_EVT_LINK_STATE);
  USB_LOG_1( log_usb_dci_handle_link_status_change__state_D, dci_ctx->link_state);
    
  switch(dci_ctx->link_state)
  {
    case LS_U0:
      if(dci_ctx->is_suspended == TRUE)
      {
        usb_fn_dci()->usb_dci_handle_wakeup(dci_ctx);
        // Clear the ULSTCHGEN event interrupts
        HWIO_USBCTL_DEVTEN_OUTM(HWIO_USBCTL_DEVTEN_ULSTCNGEN_BMSK, 0x0 << HWIO_USBCTL_DEVTEN_ULSTCNGEN_SHFT);
      }
    break;

    case LS_SS_DIS:
      if(dci_ctx->is_attached == TRUE)
      {
        usb_fn_dci()->usb_dci_handle_usb_disconnect(dci_ctx);
      }
    break;	

    // Other Events are not Handled 
    default:
    break;
  }
}

// ===========================================================================
/**
 * @function    usb_dci_drive_remote_wakeup
 * 
 * @brief       This function drives remote wake up event  * 
 * @details     
 * @param       dci_ctx
 * @return  none.
 * @see none.
 *
 * @ref SNPS spec 
 *   
 */
// ===========================================================================
void usb_dci_drive_remote_wakeup(usb_dci_ctx_t* dci_ctx)
{
  USB_LOG(log_usb_dci_drive_remote_wakeup);

  // Set the ULSTCHGEN event interrupts
  HWIO_USBCTL_DEVTEN_OUTM(HWIO_USBCTL_DEVTEN_ULSTCNGEN_BMSK, 0x1 << HWIO_USBCTL_DEVTEN_ULSTCNGEN_SHFT);
  /* Triggering Remote wakeup */
  usb_fn_util()->usb_delay_ms(10);
  HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK, LS_U0 << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
  HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK, LS_RECOV << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
  usb_fn_util()->usb_delay_ms(10);

}

// ===========================================================================
/**
 * @function    usb_dci_handle_suspend_entry
 * 
 * @brief       This function handles USB suspend entry event
 * 
 * @details     
 *  This event provides a notification that the link has gone to a suspend state (L2, U3, or L1). This event is
 *  generated when hibernation mode is disabled. The existing Link State Change event (3) provides the same
 *  information, but is generated for every link state change. 
 *
 *  Note: Enable suspend event, Sec. 6.3.1.3 ( set bit 6,  DEVTEN registers )
 * 
 * @param       None    
 *
 * @return  none.
 *
 * @see usb_dci_handle_dev_event
 *
 * @ref SNPS spec 
 *   Sec. 6.3.1.3 , 
 *   Table 6-60 ( Pg. 500) - DSTS ( bits 21-18)
 *   
 */
// ===========================================================================
void usb_dci_handle_suspend_entry(usb_dci_ctx_t* dci_ctx)
{
  uint32 is_ss_disabled;
  USB_ASSERT(dci_ctx);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  //Check for GDBGLTSSM[LTDBlinkstate] is in SS Disabled
  is_ss_disabled = HWIO_USBCTL_GDBGLTSSM_INM(HWIO_USBCTL_GDBGLTSSM_LTDBLINKSTATE_BMSK)
                                            >> HWIO_USBCTL_GDBGLTSSM_LTDBLINKSTATE_SHFT;
  /* Read the DSTS to detrmine the Actual state 
  *Link state event also gives the state of the Link 
  */
  dci_ctx->link_state = usb_fn_dci()->usb_dci_get_link_state(dci_ctx);

  USB_LOG_2(log_usb_dci_handle_suspend_entry__link_state_D_is_ss_disabled_D, 
    dci_ctx->link_state, is_ss_disabled);

  if (dci_ctx->link_state != LS_U3)
  {
    USB_LOG_ERR(log_usb_dci_handle_suspend_entry__link_state_not_ls_u3);
  }
  else
  {
    if ((dci_ctx->is_l2_feature_enabled) && 
      (0 == usb_fn_dci()->usb_dci_buffer_is_empty(dci_ctx)) && 
      (TRUE == dci_ctx->is_attached)) // && (is_ss_disabled == LINK_STATE_SS_DISABLED))
    {
      USB_LOG_ERR(log_usb_dci_handle_suspend_entry__enter_suspended_state);

      //HWIO_USBCTL_DEVTEN_OUTM(HWIO_USBCTL_DEVTEN_ULSTCNGEN_BMSK,
      //                   0x1 << HWIO_USBCTL_DEVTEN_ULSTCNGEN_SHFT);

      //3. Enable PHY susepnd -> GUSB2_[SUSPEND_ENABLE] =1
      HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTMI(0, HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_SUSPENDUSB20_BMSK,
                                                   0x1 << HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_SUSPENDUSB20_SHFT);
      
      if (HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK != 
         usb_fn_dci()->usb_dci_poll_pwr_event(dci_ctx))
      {
        return;
      }
      
      dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_SUSPEND, NULL);
      dci_ctx->is_suspended = TRUE;
    }
    else
    {
      //LINK_STATE not L2 return active L0 
      USB_LOG_ERR_3(log_usb_dci_handle_suspend_entry__l2_enable_D__buf_empt_D__is_att_D, 
        dci_ctx->is_l2_feature_enabled, usb_fn_dci()->usb_dci_buffer_is_empty(dci_ctx), 
        dci_ctx->is_attached);

      if (dci_ctx->remote_wakeup_enabled)
      {
        usb_fn_dci()->usb_dci_drive_remote_wakeup(dci_ctx);
      }
    }
  }
}

// ===========================================================================
/**
 * @function    usb_dci_handle_wakeup
 * 
 * @brief       This function handles wakeup event
 * 
 * @details     
 *  This event provides a notification that when there is a resume on the bus . The existing Link State moves to Active.
 *
 *  Note: 
 * 
 * @param       None    
 *
 * @return  none.
 *
 * @see dci_handle_dev_event
 *
 * @ref SNPS spec 
 *   Sec. 6.3.1.3 , 
 *   Table 6-60 ( Pg. 500) - DSTS ( bits 21-18)
 *   
 */
// ===========================================================================
void usb_dci_handle_wakeup(usb_dci_ctx_t* dci_ctx)
{
  USB_ASSERT(dci_ctx);

  /* Read the DSTS to detrmine the Actual state.
   * Link state event also gives the state of the Link
   */
   
  if(dci_ctx->link_state == LS_U3)
  {
    USB_LOG(log_usb_dci_handle_wakeup__link_state_ls_u3);

    //3. software vote for resume clocks
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
    
    usb_fn_isr()->usb_isr_usbphy_enable(FALSE);
    
    //4. if usb ram are in sleep mode, sw should wake-up the ram.
    HWIO_USBCTL_GCTL_OUTM(HWIO_USBCTL_GCTL_DSBLCLKGTNG_BMSK,      //Disable clock gating is off
                     0x0 << HWIO_USBCTL_GCTL_DSBLCLKGTNG_SHFT);   
    HWIO_CHIP_CFG1_PWR_MEM_SD_OUTM(HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_BMSK,
                               0x0 << HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_SHFT);

    //5. disable phy suspend    
    HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTMI(0, HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_SUSPENDUSB20_BMSK,
                                                      0x0 << HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_SUSPENDUSB20_SHFT);
    //6. transition to L0 state
    dci_ctx->link_state = LS_U0;

    //7. software issue a remote wakup
    //a. software votes for resumeing clocks
    //b. transtion to L0 state

    //8. MCU clear suspend state (SWI bit)
    //9. software vote for DMA/BLSP by MCU
    //
    //HWIO_CHIP_CFG1_DMA_BUS_VOTE_OUTM(HWIO_CHIP_CFG1_DMA_BUS_VOTE_ENABLE_BMSK,
    //                             0x1 << HWIO_CHIP_CFG1_DMA_BUS_VOTE_ENABLE_SHFT);
    //HWIO_CHIP_CFG1_BLSP_BUS_VOTE_OUTM(HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ENABLE_BMSK,
    //                              0x1 << HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ENABLE_BMSK);
    

  }

  USB_LOG(log_usb_dci_handle_wakeup__out_of_suspended_state);

  dci_ctx->is_suspended = FALSE;
} 

// ===========================================================================
/**
 * @function    usb_dci_get_address
 * 
 * @brief   Read adress of the device from register.
 * 
 * @note    Function to read set address from device register.
 *  
 * @param   None.
 *
 */
// ===========================================================================
uint8 usb_dci_get_address(void)
{  
  return (HWIO_USBCTL_DCFG_INM(HWIO_USBCTL_DCFG_DEVADDR_BMSK) >> HWIO_USBCTL_DCFG_DEVADDR_SHFT);
}

// ===========================================================================
/**
 * @function    usb_dci_set_address
 * 
 * @brief       This function set the device address
 * 
 * @details     
 *       
 * @param address
 *      New Device Address.
 * 
 * @return  none.
 *
 * @ref 
 */
// ===========================================================================
void usb_dci_set_address(uint8 address)
{
  USB_LOG_1(log_usb_dci_set_address__address_D, address);
  HWIO_USBCTL_DCFG_OUTM(HWIO_USBCTL_DCFG_DEVADDR_BMSK, address << HWIO_USBCTL_DCFG_DEVADDR_SHFT);
}

// ===========================================================================
/**
 * @function    usb_dci_get_event_cnt
 * 
 * @brief   Read number of event from device register.
 * 
 * @note    
 *  
 * @param   None.
 *
 * @return  number of event in the register.
 */
// ===========================================================================
uint32 usb_dci_get_event_cnt(void)
{
  return HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INMI(0, 
    HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK);
}

// ===========================================================================
/**
 * @function    usb_dci_stall_endpoint
 * 
 * @brief       This function stall an endpoint
 * 
 * @details     
 *      There are two occasions where the device controller may need to return to the host a STALL.
 *  
 *      The first occasion is the FUNCTIONAL stall, 
 *      which is a condition set by the DCD as described in the USB 2.0 device framework (chapter 9). 
 *      A functional stall is only used on noncontrol endpoints and can be enabled in the device
 *      controller by setting the endpoint stall bit in the ENDPTCTRLx register 
 *      associated with the given endpoint and the given direction. 
 *      
 *      In a functional stall condition, the device controller will continue to return STALL responses to all
 *      transactions occurring on the respective endpoint and direction until the endpoint stall bit is cleared by the DCD.
 *      
 *      A PROTOCOL stall, unlike a function stall, is used on control endpoints is automatically cleared by the device
 *      controller at the start of a new control transaction (setup phase). 
 *      When enabling a protocol stall, the DCD should enable the stall bits (both directions) as a pair. 
 *
 *  
 * @param ep    
 *          endpoint number
 * 
 * @param dir    
 *          endpoint direction (1=TX=IN,0=RX=OUT)
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @ref SNPS spec 
 *   Chapter 8.2.7 Page 579
 *   Chapter 6.3.2.5.4 Page 512
 */
// ===========================================================================
uint32 usb_dci_stall_endpoint(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir)
{
  uint32 status=DCI_OK;
  usb_ep_cmd_t ep_cmd;

  USB_LOG_1( log_usb_dci_stall_endpoint__ep_D, ep);

  if((ep >= DCI_MAX_ENDPOINTS) || (dir >= DCI_MAX_DIRECTION))
  {
    USB_LOG_ERR_2(log_usb_dci_stall_endpoint__ep_D_dir_D_out_of_bounds, ep, dir);
    return(DCI_ERROR);
  }
  memset(&ep_cmd, 0, sizeof(ep_cmd));

  ep_cmd.set_stall.cmd.cmd_typ = USB_EP_CMD_SET_STALL_VAL;
  ep_cmd.set_ep_config.cmd.cmd_act = USB_EXECUTE_EP_GENERIC_COMMAND;

  status = usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep, dir, &ep_cmd); 
  dci_ctx->usb_trb_ring[ep][dir].ep_state |= USB_EP_HALTED;

  return(status);

}

// ===========================================================================
/**
 * @function    usb_dci_unstall_endpoint
 * 
 * @brief       This function unstall a stalled endpoint
 * 
 * @details
 *      There are two occasions where the device controller may need to return to the host a STALL.
 *  
 *      The first occasion is the FUNCTIONAL stall, 
 *      which is a condition set by the DCD as described in the USB 2.0 device framework (chapter 9). 
 *      A functional stall is only used on noncontrol endpoints and can be enabled in the device
 *      controller by setting the endpoint stall bit in the ENDPTCTRLx register 
 *      associated with the given endpoint and the given direction. 
 *      
 *      In a functional stall condition, the device controller will continue to return STALL responses to all
 *      transactions occurring on the respective endpoint and direction until the endpoint stall bit is cleared by the DCD.
 *      
 *      A PROTOCOL stall, unlike a function stall, is used on control endpoints is automatically cleared by the device
 *      controller at the start of a new control transaction (setup phase). 
 *      When enabling a protocol stall, the DCD should enable the stall bits (both directions) as a pair. 
 *      A single write to the ENDPTCTRLx register can ensure that both stall bits are set at the same instant.
 *  
 * @note : Any write to the ENDPTCTRLx register during operational mode must preserve the endpoint type field (i.e. perform a readmodifywrite).
 *  
 * @note : Reset Data-Toggle as mentioned in Chapter 8.3.3.1 Data Toggle Reset
 *    
 *
 * @param ep    
 *          endpoint number
 * 
 * @param dir    
 *          endpoint direction (1=TX=IN,0=RX=OUT)
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see usb_dci_stall_endpoint
 *
 * @ref SNPS spec 
 *   Chapter 8.2.7 Page 579
 *   Chapter 6.3.2.5.4 Page 512
 */
// ===========================================================================
uint32 usb_dci_unstall_endpoint(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir)
{
  uint32 status=DCI_OK;
  usb_ep_cmd_t ep_cmd;
  USB_LOG_1( log_usb_dci_unstall_endpoint__ep_D, ep);
  if((ep < DCI_MAX_ENDPOINTS) && (dir < DCI_MAX_DIRECTION))
  {
    memset(&ep_cmd, 0, sizeof(ep_cmd));
    ep_cmd.clear_stall.cmd.cmd_typ = USB_EP_CMD_CLEAR_STALL_VAL;
    ep_cmd.set_ep_config.cmd.cmd_act = 1;
    status = usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep, dir, &ep_cmd); 
    dci_ctx->usb_trb_ring[ep][dir].ep_state &= ~USB_EP_HALTED;
  }
  else
  {
    USB_LOG_ERR_2(log_usb_dci_unstall_endpoint__ep_D_dir_D_out_of_bounds, ep, dir);
    status = DCI_ERROR; 
  }
  return(status);
}

// ===========================================================================
/**
 * @function    usb_dci_config_endpoint
 * 
 * @brief       This function configures the endpoint
 * 
 * @details     
 * 
 * @note        This function should be called on "Set Configuration" USB Standard Command.
 * 
 *
 * @param ep    
 *          endpoint number
 * @param dir    
 *          endpoint direction (1=TX,0=RX)
 * @param ep_type 
 *          endpoint type:    
 *          USB_EP_TYPE_CONTROL      0
 *          USB_EP_TYPE_ISO          1
 *          USB_EP_TYPE_BULK         2    
 *          USB_EP_TYPE_INTERRUPT    3
 * @param max_packet_length    
 *          maximum packet length - depends on the connection speed and the Hardware FIFOs.
 * @param zero_length_transfer    
 *          if set to TRUE, and the transfer length is a multiply of the max_packet_length
 *          then a zero lenfth packet is added.
 * 
 * @return None
 * 
 * @ref SNPS spec
 *       
 */
// ===========================================================================
void usb_dci_config_endpoint
(
  usb_dci_ctx_t* dci_ctx,
  uint8 ep,
  uint8 dir, 
  uint8 ep_type,
  uint8 ep_interval,
  uint16 max_packet_length, 
  boolean zero_length_transfer
)
{
  uint32 val;
  usb_ep_cmd_t ep_cmd;

  memset(&ep_cmd, 0, sizeof(ep_cmd));

  ep_cmd.start_new_config.cmd.cmd_typ = USB_EP_CMD_SET_EP_CONFIG_VAL;
  ep_cmd.start_new_config.cmd.cmd_act = 1 ;
  ep_cmd.set_ep_config.usb_ep_num = 
  (ep << USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_NUM_SHIFT) |
  (dir << USB_EP_CMD_SET_EP_CONFIG_USB_ENDPT_DIR_SHIFT);

  /*FIFO cfg is only needed for IN EPs. SNPS Table 6-69: DEPCFG */
  if (dir == DIR_TX)
  {
    if (ep >= DCI_MAX_ENDPOINTS)
    {
      USB_LOG_ERR(log_usb_dci_config_endpoint__insuff_hw_resources);
      return;
    }
    ep_cmd.set_ep_config.fifo_num  = ep; //This take physical TX_FIFO.
  }   
  else
  {
    ep_cmd.set_ep_config.fifo_num  = USB_EP_INDEX(ep, dir); //0; //Rx always take RX_FIFO_0
  }

  ep_cmd.set_ep_config.xfer_nrdy_en = USB_ENABLE_XFER_NOT_READY;
  ep_cmd.set_ep_config.xfer_in_progess= 1;
  ep_cmd.set_ep_config.xfer_cmpl_en = USB_ENABLE_XFER_COMPLETE;
  ep_cmd.set_ep_config.max_packet_sz = max_packet_length;
  ep_cmd.set_ep_config.brst_siz = USB_BURST_SIZE_4;
  ep_cmd.set_ep_config.ep_type = ep_type;
  ep_cmd.set_ep_config.intr_num = USB_DEV_INTR_LINE;

  switch (ep_type)
  {
    case USB_EP_TYPE_ISO:
      dci_ctx->usb_trb_ring[ep][dir].trb_ctl = USB_TRB_CTL_ISOCHRONOUS_FIRST;
      dci_ctx->usb_trb_ring[ep][dir].b_interval = ep_interval;
      ep_cmd.set_ep_config.brst_siz = USB_BURST_SIZE_1;
      ep_cmd.set_ep_config.bInterval_m1 = ep_interval;
    break;
  
     case USB_EP_TYPE_INTERRUPT:
         dci_ctx->usb_trb_ring[ep][dir].trb_ctl = USB_TRB_CTL_NORMAL;
         ep_cmd.set_ep_config.bInterval_m1 = ep_interval;
     break;

      case USB_EP_TYPE_BULK:
      default:
        dci_ctx->usb_trb_ring[ep][dir].trb_ctl = USB_TRB_CTL_NORMAL;
      break;
  }

  /* Push the EP config */
  if (DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep, dir, &ep_cmd))
  {
    USB_LOG_ERR(log_usb_dci_config_endpoint__write_ep_cmd_cfg_failure);
  }

  memset(&ep_cmd, 0, sizeof(ep_cmd));  

  /*Config EP xfer resorces  (SNPS 6.3.2.5.2 , Table 6-70) */
  ep_cmd.set_ep_xfer_rsc_config.cmd.cmd_typ = USB_EP_CMD_SET_EP_XFER_RSC_CONFIG_VAL;
  ep_cmd.set_ep_xfer_rsc_config.cmd.cmd_act = USB_EXECUTE_EP_GENERIC_COMMAND;
  ep_cmd.set_ep_xfer_rsc_config.num_xfer_res = 1;

  /* Push the EP cmd */
  if (DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep, dir, &ep_cmd))
  {
    USB_LOG_ERR(log_usb_dci_config_endpoint__write_ep_cmd_failure);
  }

  /* Enable EP */
  val = HWIO_USBCTL_DALEPENA_IN;
  val |= (1 << USB_EP_INDEX(ep, dir));
  HWIO_USBCTL_DALEPENA_OUT(val);
  return;
}

// ===========================================================================
/**
 * @function    usb_dci_unconfig_endpoint
 * 
 * @brief       This function de-configures the endpoint
 * 
 * @details     
 * 
 * @note        This function should be called on "Set Configuration" USB Standard Command.
 * 
 * @note        caution: if one endpoint direction is enabled and the paired endpoint of opposite
 *              direction is disabled
 *              then the unused direction type must be changed from the default controltype
 *              to any other type (ie. bulktype).
 *              leaving an unconfigured endpoint control will cause undefined behavior 
 *              for the data pid tracking on the active endpoint/direction.
 * 
 * @param ep    
 *          endpoint number
 * 
 * @param dir    
 *          endpoint direction (1=TX,0=RX)
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see usb_dci_config_endpoint
 * 
 * @ref SNPS spec 
 *        
 */
// ===========================================================================
uint32 usb_dci_unconfig_endpoint( uint8 ep, uint8 dir)
{
  uint32 status=DCI_OK;
  uint32 val;
  /* Disable EP  */
  val = HWIO_USBCTL_DALEPENA_IN;
  val &= ~(1 << USB_EP_INDEX(ep, dir));
  HWIO_USBCTL_DALEPENA_OUT(val);

  return status;
}
// ===========================================================================
/**
 * @function    usb_dci_submit_trb_data
 * 
 * @brief       This function initate rx/tx dir data transfer for an EP
 * 
 * @details     
 * 
 * @param ep    
 *          endpoint number
 * @param dir    
 *          endpoint direction (1=TX,0=RX)
 *
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @ref SNPS spec 
 *
 * */  
// ===========================================================================
static uint32 usb_dci_submit_trb_data(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir)
{
  usb_ep_cmd_t start_cmd = { {0, 0, 0} };
  usb_trb_ring_t* trb_ring_ptr;
  void* phy_ring_ptr;
  uint8 res_idx;
  uint16 bint_n_uf;
  uint16 cmd_params =0;
  void* buf;
  uint16 ep_index =  USB_EP_INDEX(ep,dir);
  uint16 curr_uf;

  USB_ASSERT(dci_ctx);

  if(dci_ctx->is_suspended)
  {
    usb_fn_dci()->usb_dci_remote_wakeup(dci_ctx);
  }

  trb_ring_ptr = &dci_ctx->usb_trb_ring[ep][dir];
  res_idx = trb_ring_ptr->xfer_res_idx;

  USB_LOG_DBG_2(log_usb_dci_submit_trb_data__ep_D_dir_D, ep, dir);
  USB_LOG_DBG_2(log_usb_dci_submit_trb_data__trb_idx_D_trb_size_D, trb_ring_ptr->trb_submit_idx, 
    dci_ctx->usb_trb_list[ep][dir][trb_ring_ptr->trb_submit_idx].buf_size);

  if (USB_RSC_IDX_NOT_SET == res_idx)
  {
    // Start Transfer   
    // Reference : DWC3 databook - Isoc Transfer Programming Model (Section 8.3.5 - Starting a Transfer)
    // Issue the Start Transfer command to the endpoint with a future microframe time written into the upper
    // 16 bits of DEPCMD register.
    if (trb_ring_ptr->trb_ctl == USB_TRB_CTL_ISOCHRONOUS_FIRST)
    {
      curr_uf = HWIO_USBCTL_DSTS_INM(HWIO_USBCTL_DSTS_SOFFN_BMSK) >> HWIO_USBCTL_DSTS_SOFFN_SHFT;

      bint_n_uf = (1 << trb_ring_ptr->b_interval); // convert bInterval to number of microframes
      // convert 14 bit uf read from DSTS to 16 bit uf for start xfer cmd using upper 2 bits of xfer_nrdy_uf
      if (curr_uf >= (trb_ring_ptr->xfer_nrdy_uf & 0x3FFF))
      {
        curr_uf |= (trb_ring_ptr->xfer_nrdy_uf & 0xC000);
        USB_LOG_DBG_2(log_usb_dci_submit_trb_data__bint_n_uf_D_curr_uf_D, bint_n_uf, curr_uf);
      }
      else  // wraparound condition - compare lower 14 bits
      {
        curr_uf |= ((((trb_ring_ptr->xfer_nrdy_uf & 0xC000) >> 14) + 1) << 14);
        USB_LOG_DBG_2(log_usb_dci_submit_trb_data__wrap_bint_n_uf_D_curr_uf_D, bint_n_uf, curr_uf);
      }

      cmd_params = bint_n_uf * ((curr_uf / bint_n_uf) + 1); // align to next microframe to bInterval.
      if (cmd_params <= (curr_uf+1)) // Gurantee at least one uf of time between current uf and next uf.
      {
        cmd_params += bint_n_uf;
      }
      USB_LOG_ERR_2(log_usb_dci_submit_trb_data__next_uf_D_curr_uf_D, cmd_params, curr_uf);
    }

    buf = (void *) &(dci_ctx->usb_trb_list[ep][dir][trb_ring_ptr->trb_submit_idx]);

    phy_ring_ptr = usb_fn_mem_util()->usb_mem_attr_uncached(buf);
    start_cmd.start_xfer.td_address_lo  = ((uint64)(uintptr_t)phy_ring_ptr) & 0xFFFFFFFF;
    start_cmd.start_xfer.td_address_hi  = (((uint64)(uintptr_t)phy_ring_ptr)  >> 32) & 0xFFFFFFFF;

    start_cmd.start_xfer.cmd.cmd_typ   = USB_EP_CMD_START_XFER_VAL;
    start_cmd.start_xfer.cmd.cmd_ioc   = 0;
    start_cmd.start_xfer.cmd.cmd_act   = USB_EXECUTE_EP_GENERIC_COMMAND;
    start_cmd.start_xfer.cmd.cmd_param = cmd_params;

    USB_LOG_2(log_usb_dci_submit_trb_data__start_xfer_addrh_D_addrl_D, 
      start_cmd.start_xfer.td_address_hi, start_cmd.start_xfer.td_address_lo);   
  }
  else
  {
    // Update Transfer
    start_cmd.start_xfer.cmd.cmd_typ   = USB_EP_CMD_UPDATE_XFER_VAL;
    start_cmd.start_xfer.cmd.cmd_act   = USB_EXECUTE_EP_GENERIC_COMMAND;
    start_cmd.start_xfer.cmd.cmd_param = trb_ring_ptr->xfer_res_idx;
    USB_LOG_DBG_1(log_usb_dci_submit_trb_data__update_xfer_res_idx_D, trb_ring_ptr->xfer_res_idx);       
  }

  if(DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep, dir, &start_cmd))
  {
    USB_ULOG_3(DBG_E_LOG,"write ep cmd failure, ep %d, dir %d, idx %d", 
      ep, dir, trb_ring_ptr->trb_submit_idx);
    USB_LOG_ERR_2(log_usb_dci_submit_trb_data__write_ep_cmd_failure, ep, dir);
    return (DCI_ERROR);
  }

  // Update transfer resource index only if start transfer command was issued.
  if (USB_RSC_IDX_NOT_SET == res_idx)
  {
    cmd_params = HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INMI(ep_index, HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_COMMANDPARAM_BMSK) 
              >> HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_COMMANDPARAM_SHFT;

    trb_ring_ptr->xfer_res_idx = (uint8)(cmd_params & USB_EP_XFER_RSC_INDEX_BMSK);
    USB_ULOG_3(ENG_QUSB_LOG, "resource index %d, ep %u, dir %u", trb_ring_ptr->xfer_res_idx, ep, dir);
  }

  return(DCI_OK);
}

//============================================================================
/**
 * @function  usb_dci_init_trb_ring
 *
 * @brief
 *    This function initializes the TRB structures for all EP.
 *    
 *  @Note : This API initializes Link TRBs and TRB ring structure.
 *      
 *
 * @param dci_ctx - DCI layer context.
 *
 * @return None
 *
 *
 */
//============================================================================
void usb_dci_init_trb_ring(usb_dci_ctx_t* dci_ctx)
{
  uint8 ep;
  uint8 dir;
  uint8 trb_cnt, urb_cnt;
  usb_trb_t *trb;
  void* phy_trb_ptr;
  usb_trb_ring_t *trb_ring;
  void* addr;

  // Setup last trb as a link trb for each non-control EP.
  for(ep=0; ep<DCI_MAX_ENDPOINTS; ep++)
  {
    for(dir=0; dir<DCI_MAX_DIRECTION; dir++)
    {
      // Initialize trb_ring
      trb_ring = &(dci_ctx->usb_trb_ring[ep][dir]);
      trb_ring->xfer_res_idx = USB_RSC_IDX_NOT_SET;
      trb_ring->trb_idx = 0;
      trb_ring->trb_submit_idx = 0;
      trb_ring->trb_comp_idx = 0;
      trb_ring->trb_ctl = USB_TRB_CTL_NORMAL;
      
      // Initialize link_trb
      trb = &dci_ctx->usb_trb_list[ep][dir][DCI_TRBS-1];
      trb->hwo = 1;
      addr = &dci_ctx->usb_trb_list[ep][dir][0];

      phy_trb_ptr = usb_fn_mem_util()->usb_mem_attr_uncached((void*) addr); 
      trb->buf_ptr_lo = ((uint64)(uintptr_t)phy_trb_ptr & 0xFFFFFFFF);
      trb->buf_ptr_hi = (((uint64)(uintptr_t)phy_trb_ptr >> 32) & 0xFFFFFFFF);

      trb->trb_ctl = USB_TRB_CTL_LINK_TRB;

      trb_ring->ep_state = 0;

      trb_ring->urb_comp_idx=0;
      trb_ring->urb_idx =0;
      for (urb_cnt=0; urb_cnt<USB_URB_MAX;urb_cnt++)
      {
        trb_ring->urb_ptr[urb_cnt] =0;
      }
      for (trb_cnt=0; trb_cnt<DCI_TRBS; trb_cnt++)
      {
        trb_ring->swo[trb_cnt] =0;
      }
    }
  }
}
//============================================================================
/**
 * @function  usb_dci_prepare_trbs
 *
 * @brief
 *    This function initializes the TRB structures for an EP:
 *    
 *  @Note : 
 *      
 *
 * @param ep
 *            EP number
 * @param dir  
 *            EP direction 
 * @param buf_addr
 *            data buffer supplied by upper laer
 * @param byte_count
 *              Number of bytes 
 * @param send_zlp
 *            whether zlp should be sent
 * @param trb_ctl
 *            Type of TRB  * @return None
 *
 * @ref SNPS spec "":
 *      Chapter 7.1
 *      Chapter 8.2.3
 *      
 *
 */
//============================================================================
static uint32 usb_dci_prepare_trbs(usb_dci_ctx_t* dci_ctx, uint32 ep, uint32 dir, 
  usb_urb_t* urb_ptr, uint8 trb_ctl)
{
  usb_trb_t *trb;
  usb_trb_t *zlp_trb;
  usb_trb_ring_t *trb_ring;
  void* phy_trb_ptr;
  void* buf;

  USB_ASSERT(dci_ctx);

  /* Update TRB ring */
  trb_ring = &(dci_ctx->usb_trb_ring[ep][dir]);
  
  if (ep == 0)
  {
    trb_ring->trb_idx = 0;
    trb_ring->xfer_res_idx = USB_RSC_IDX_NOT_SET;
    USB_LOG_DBG_1(log_usb_dci_prepare_trbs__ep0_dbg_trb_idx_D, trb_ring->trb_idx);
  }

  trb = &dci_ctx->usb_trb_list[ep][dir][trb_ring->trb_idx];

  if (trb->hwo == 1)
  {
    USB_LOG_ERR_3(log_usb_dci_prepare_trbs__insuff_hw_rsrc_ep_D_dir_D_trb_idx_D, ep, dir, trb_ring->trb_idx);
    return (DCI_ERROR);
  }

  if (trb_ring->swo[trb_ring->trb_idx])
  {
    USB_LOG_ERR_3(log_usb_dci_prepare_trbs__trb_swo_ep_D_dir_D_trb_idx_D, ep, dir, trb_ring->trb_idx);
    return (DCI_ERROR);
  }

  trb_ring->trb_submit_idx = trb_ring->trb_idx;

  USB_LOG_DBG_3(log_usb_dci_prepare_trbs__ep_D_dir_D_trb_idx_D, ep, dir, trb_ring->trb_idx);

  if (urb_ptr->transfer_length> USB_TRB_MAX_BUFFER_SIZE) 
  {
    USB_LOG_ERR_1(log_usb_dci_prepare_trbs__invalid_buff_size_D, urb_ptr->transfer_length);
    return (DCI_ERROR);
  }

  // Note : For RX on non control endpoints transfer length must be set to wMaxPacketSize of endpoint 
  // config cmd at DCD or FD layer.
  if(dir == DIR_RX && trb_ctl == USB_TRB_CTL_CONTROL_DATA) 
  {
    urb_ptr->transfer_length = dci_ctx->usb_dci_ep0_max_packet_size;
  }

  if(trb_ctl == USB_TRB_CTL_CONTROL_SETUP)
  {
    buf = (void *) &(dci_ctx->usb_trb_list[ep][dir][trb_ring->trb_idx]);
  }
  else
  {
    buf = (void *) urb_ptr->transfer_buffer_ptr;
  }

  phy_trb_ptr = usb_fn_mem_util()->usb_mem_attr_uncached((void*) buf);

  // Prepare TRB
  trb_ring->swo[trb_ring->trb_idx] = 1;
  memset(trb, 0, sizeof(usb_trb_t));  
  trb->buf_size   = urb_ptr->transfer_length;
  trb->buf_ptr_lo = (uint32) phy_trb_ptr;
  trb->buf_ptr_hi = 0;  
  trb->lst        = (ep == 0);
  trb->chn        = 0;
  trb->csp        = (ep!=0 && dir == DIR_RX);
  trb->trb_ctl    = trb_ctl;
  trb->ioc        = 1;

  /* Zero length TRB, Append an ZLP if byte_count is a multiple of max packet length or  ZLP for EP0 status stage */
  if((urb_ptr->send_zlp == 1) && (urb_ptr->transfer_length) &&
    ((((urb_ptr->transfer_length % usb_fn_dci()->usb_dci_get_max_packet_size(dci_ctx)) == 0)) || 
    ((ep == 0) && ( dir == DIR_TX) && 
    ((urb_ptr->transfer_length % dci_ctx->usb_dci_ep0_max_packet_size) == 0))))
  {
    trb->chn = 1;
    trb->ioc = 0;
    trb->lst = 0;

    // Increment trb_idx and read next trb in list.
    usb_fn_dci()->usb_dci_inc_trb_idx(dci_ctx, ep, dir, &trb_ring->trb_idx);

    USB_LOG_DBG_3(log_usb_dci_prepare_trbs__send_zlp_ep_D_dir_D_trb_idx_D, ep, dir, 
      trb_ring->trb_idx);

    zlp_trb = (usb_trb_t *) &(dci_ctx->usb_trb_list[ep][dir][trb_ring->trb_idx]);
    memset(zlp_trb, 0, sizeof(usb_trb_t));
    zlp_trb->buf_ptr_lo = 0;
    zlp_trb->buf_ptr_hi = 0;
    zlp_trb->buf_size   = 0;
    zlp_trb->lst        = (ep == 0);
    zlp_trb->chn        = 0;
    zlp_trb->csp        = (ep !=0 && dir == DIR_RX);;
    zlp_trb->trb_ctl    = trb_ctl;
    zlp_trb->ioc        = 1;         // XferInProgress event
    zlp_trb->hwo        = 1;
  }

  // set HWO at the end on data TRB.
  trb->hwo  = 1;

  // Increment trb_idx
  usb_fn_dci()->usb_dci_inc_trb_idx(dci_ctx, ep, dir, &trb_ring->trb_idx);

  return (DCI_OK);
}

// ===========================================================================
/**
 * @function    usb_dci_transfer_data_request
 * 
 * @brief       This function queues rx/dir data transfer
 * 
 * @details     
 * 
 *  The behaviors of the device controller for interrupt and bulk endpoints are identical. 
 *  All valid IN and OUT transactions to bulk pipes will handshake with a NAK unless the endpoint had been primed. 
 *  Once the endpoint has been primed, data delivery will commence.
 *  
 * @param ep    
 *          endpoint number
 * @param dir    
 *          endpoint direction (1=TX,0=RX)
 * @param buffer_ptr    
 *          pointer to buffer
 * @param byte_count    
 *          number of bytes to send (dir) 
 *          or
 *          maximum number of bytes to receive (rx) 
 * @param send_zlp    
 *          specify whether to transmit a ZLP at the end of the transfer.
  * @param trb_ctrl    
 *          type of the TRB ( SNPS pg. 547 table 7.1, bits 9:4).
 *
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @ref SNPS spec 
 *
 * */  
// ===========================================================================
static uint32 usb_dci_transfer_data_request(usb_dci_ctx_t* dci_ctx, 
  uint8 ep, uint8 dir, usb_urb_t* urb_ptr, trb_ctl_type_t trb_ctrl)
{
  USB_LOG_1( log_usb_dci_transfer_data_request__transfer_length_D, urb_ptr->transfer_length);

  /* max transfer to be less than to fit in num of TRBs */
  if (urb_ptr->transfer_length > (DCI_MAX_TRBS * USB_TRB_MAX_BUFFER_SIZE)) 
  {
    USB_LOG_ERR_1(log_usb_dci_transfer_data_request__size_too_large_D, urb_ptr->transfer_length);
    return(USB_ERR_BAD_PARAM);
  }

  if((ep >= DCI_MAX_ENDPOINTS) || (dir >= DCI_MAX_DIRECTION))
  {
    USB_LOG_ERR(log_usb_dci_transfer_data_request__ep_D_dir_D_out_of_bounds);
    return(USB_ERR_BAD_PARAM);
  }

  // buffer can be NULL for SETUP on CONTROL EP
  // i.e. usb_dcd_control_transfer(dcd_dev, DIR_RX, NULL, DCI_SETUP_BUFFER_SIZE);     

  /*  Intialize TRB ring and update the TRB structure with the data */
  if (DCI_ERROR == usb_fn_dci()->usb_dci_prepare_trbs(dci_ctx, ep, dir, urb_ptr, trb_ctrl))
  {
    return(DCI_ERROR);
  }

  usb_fn_mem_util()->usb_mem_barrier();
  
  /* Submit the TRB for setup or normal */
  /* For all the other control requests, we submit to the HW , after xfer_nrdy  is received */
  if ((trb_ctrl == USB_TRB_CTL_CONTROL_SETUP) || (trb_ctrl == USB_TRB_CTL_NORMAL) || 
    (trb_ctrl == USB_TRB_CTL_ISOCHRONOUS_FIRST) || (trb_ctrl == USB_TRB_CTL_ISOCHRONOUS))
  {
    /* push the TRB into the HW */
    usb_fn_dci()->usb_dci_submit_trb_data(dci_ctx, ep, dir);
  }
  return(DCI_OK);
}

// ===========================================================================
/**
 * @function    usb_dci_ctrl_error_recover
 * 
 * @brief       This function drives control state machine error recovery
 * 
 * @details     
 *              
 * 
 * @note    
 *
 * @param dci_ctx
 * 
 * @return None.
 * 
 * @see 
 * 
 */
// ==========================================================================
void usb_dci_ctrl_error_recover(usb_dci_ctx_t* dci_ctx)
{
  usb_fn_dci()->usb_dci_stall_endpoint(dci_ctx, DCI_EP0, DIR_RX);
  dci_ctx->ctrl_state = EP0_STATE_SETUP_TRB;
  dci_ctx->dcd_cb.notify(dci_ctx->dcd_ctx, USB_DCD_EVT_CTRL_INIT, NULL);
}

// ===========================================================================
/**
 * @function    usb_dci_ctrl_xfer_state_machine
 * 
 * @brief       This function updates the state of the control transfer and TRB  
 *              type that should be programmed while initiating a control 
 *              transfer.
 * 
 * @details     
 *              
 * 
 * @note    
 *
 * @param urb_ptr
 *              A pointer to URB structure.
 * @param urb_ptr
 *              pointer to TRB control state.
 *
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see transfer_data_request
 * 
 */
// ==========================================================================
static void usb_dci_ctrl_xfer_state_machine(usb_dci_ctx_t* dci_ctx, 
                                                      usb_urb_t *urb_ptr, 
                                                      trb_ctl_type_t *trb_ctl)
{
  USB_ASSERT(urb_ptr && trb_ctl);

  switch (dci_ctx->ctrl_state)
  {
    case EP0_STATE_SETUP_TRB:
       dci_ctx->ctrl_data_dir = DIR_NONE;
      *trb_ctl = USB_TRB_CTL_CONTROL_SETUP;
    break;

    case EP0_STATE_INTRPT_SETUP:

      if (urb_ptr->transfer_length > 0 )
      {
        dci_ctx->ctrl_data_dir = (usb_ep_dir_t)VAL_TO_BOOL(urb_ptr->endpoint_address & 0x80);
        dci_ctx->ctrl_state = EP0_STATE_DATA;
        *trb_ctl = USB_TRB_CTL_CONTROL_DATA;
      }
      else
      {
        dci_ctx->ctrl_state = EP0_STATE_STATUS_2;
        *trb_ctl = USB_TRB_CTL_CONTROL_STATUS_2;
      }     
    break;

    case EP0_STATE_STATUS_2:
      *trb_ctl = USB_TRB_CTL_CONTROL_STATUS_2;
    break;

    case EP0_STATE_DATA:
      *trb_ctl = USB_TRB_CTL_CONTROL_STATUS_3;
    break;

    case EP0_STATE_STATUS_3:
      *trb_ctl = USB_TRB_CTL_CONTROL_STATUS_3;
    break;

    default:
      // No action needed
      break;
  }
}

// ===========================================================================
/**
 * @function    usb_dci_ctrl_submit_request
 * 
 * @brief       This function initiates data transfer according to URB.
 * 
 * @details     
 *              This function calls submit_trb_data() and updates the URB.
 * 
 * @note        The USB is a Master-Slave protocol where the Device is the Slave.
 *              The Device's data is actually sent/received on the USB bus 
 *              only when the Host sends SETUP/IN/OUT token.
 *              Therefore, the caller only starts a REQUEST.
 *              A callback is called upon complete/error detection.
 *              The caller May poll the status in the URB.
 *
 * @param dir
 *              ep direction.
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see transfer_data_request
 * 
 */
// ===========================================================================
uint32 usb_dci_ctrl_submit_request(usb_dci_ctx_t* dci_ctx, uint8 dir)
{
  uint32  status=0;

  if(dir >= DCI_MAX_DIRECTION)
  {
    USB_LOG_ERR_1(log_usb_dci_ctrl_submit_request__ep_0_dir_D_out_of_bounds, dir);
    status = DCI_ERROR; 
    return(status);
  }

  /* push the TRB into the HW */
  status = usb_fn_dci()->usb_dci_submit_trb_data(dci_ctx, 0, dir);

  // EP0 uses URB ptr corresponding to index 0 always.
  dci_ctx->usb_trb_ring[0][dir].urb_ptr[0]->transfer_status = USB_URB_STATUS_ACTIVE;

  return(status);
}

// ===========================================================================
/**
 * @function    usb_dci_transfer_request
 * 
 * @brief       This function ques data transfer according to URB.
 * 
 * @details     
 *              This function calls transfer_data_request() and update the URB.
 * 
 * @note        The USB is a Master-Slave protocol where the Device is the Slave.
 *              The Device's data is actually sent/received on the USB bus 
 *              only when the Host send SETUP/IN/OUT token.
 *              Therefore, the caller only start a REQUEST.
 *              A callback is called upon complete/error detection.
 *              The caller May poll the status in the URB.
 * 
 * @param urb_ptr
 *              A pointer to URB structure.
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see transfer_data_request
 * 
 */
// ===========================================================================
uint32 usb_dci_transfer_request(usb_dci_ctx_t* dci_ctx, usb_urb_t* urb_ptr)
{
  uint32  status=0;
  uint8   ep=0;
  boolean dir=FALSE;
  trb_ctl_type_t trb_ctl;
  uint8 urb_idx;

  USB_ASSERT(urb_ptr && dci_ctx);

  ep = urb_ptr->endpoint_address & 0x0F;
  dir = VAL_TO_BOOL(urb_ptr->endpoint_address & 0x80);

  if ((ep >= DCI_MAX_ENDPOINTS) || (dir >= DCI_MAX_DIRECTION))
  {
    return(USB_ERR_BAD_PARAM);
  }

  /* update the state machine for EP0 and get the TRB type to be sent */
  if (ep == 0)
  {
    usb_fn_dci()->usb_dci_ctrl_xfer_state_machine(dci_ctx, urb_ptr, &trb_ctl);

    // Copy TX response buffer to generic ZI buffer
    if(DIR_TX == dir)
    {
      memscpy((void*)(dci_ctx->usb_control_tx_buffer), urb_ptr->transfer_length,
            urb_ptr->transfer_buffer_ptr, urb_ptr->transfer_length);

      urb_ptr->transfer_buffer_ptr =  (dci_ctx->usb_control_tx_buffer);
    }
    
    urb_idx=0;
  }
  else
  {
    urb_idx = dci_ctx->usb_trb_ring[ep][dir].urb_idx;
    trb_ctl = dci_ctx->usb_trb_ring[ep][dir].trb_ctl;
  }
  
  USB_LOG_DBG_2(log_usb_dci_transfer_request__urb_ptr_D_urb_idx_D, (uint32)urb_ptr, urb_idx);

  status = usb_fn_dci()->usb_dci_transfer_data_request(dci_ctx, ep, dir, urb_ptr, trb_ctl);

  if (status == DCI_OK)
  {
    urb_ptr->transfer_status =  USB_URB_STATUS_ACTIVE;

    /* Mark as queued */
    if ( (trb_ctl == USB_TRB_CTL_CONTROL_DATA) || (trb_ctl == USB_TRB_CTL_CONTROL_STATUS_2) || 
      (trb_ctl == USB_TRB_CTL_CONTROL_STATUS_3) )
    {
      urb_ptr->transfer_status = USB_URB_STATUS_QUEUED;
    }
  
    urb_ptr->actual_length   = 0;


    /* Set TRB to point at the URB */
    dci_ctx->usb_trb_ring[ep][dir].urb_ptr[urb_idx] = urb_ptr;
    /* Make urb_idx point to next URB */
    CIRINC(dci_ctx->usb_trb_ring[ep][dir].urb_idx, USB_URB_MAX);
  }
  else
  {
    USB_LOG_ERR_2(log_usb_dci_transfer_request__failed_to_queue_xfer_ep_D_dir_D, ep, dir);
    dci_ctx->usb_trb_ring[ep][dir].urb_ptr[urb_idx] = NULL;
    urb_ptr->transfer_status = USB_URB_STATUS_COMPLETE_ERROR;
  }

  return(status);
}

// ===========================================================================
/**
 * @function    usb_dci_cancel_transfer
 * 
 * @brief       This function terminates an active transfers
 * 
 * @details     
 * 
 * @param core_id    
 *
 * @param ep    
 *          endpoint number
 * @param dir    
 *          endpoint direction (1=TX,0=RX)
 * 
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see usb_dci_shutdown
 * 
 * @ref SNPS Spec
 */
// ===========================================================================
uint32 usb_dci_cancel_transfer(usb_dci_ctx_t* dci_ctx, uint8 ep, uint8 dir)
{
  usb_ep_cmd_t ep_cmd;
  usb_trb_ring_t* trb_ring_ptr;
  uint8 *trb_comp_idx;
  usb_trb_t *trb_ptr;
  usb_urb_t *urb_ptr;
  uint8 urb_cnt;
  uint8 trb_cnt;

  trb_ring_ptr = &dci_ctx->usb_trb_ring[ep][dir];
  if (trb_ring_ptr->xfer_res_idx == USB_RSC_IDX_NOT_SET)
  {
    USB_LOG_DBG_2(log_usb_dci_cancel_transfer__no_pending_transfer_ep_D_dir_D, ep, dir);
  }
  else
  {
    memset(&ep_cmd, 0, sizeof(ep_cmd));
    ep_cmd.end_xfer.cmd.cmd_typ = USB_EP_CMD_END_XFER_VAL;
    ep_cmd.set_ep_config.cmd.cmd_act = 1;
    ep_cmd.set_ep_config.cmd.hi_pri_force_rm = 1;
    ep_cmd.set_ep_config.cmd.cmd_param= trb_ring_ptr->xfer_res_idx; 

    USB_LOG_DBG_2(log_usb_dci_cancel_transfer__issue_cancel_xfer_cmd_ep_D_dir_D, ep, dir);

    if(DCI_OK != usb_fn_dci()->usb_dci_write_ep_cmd(dci_ctx, ep, dir, &ep_cmd))
    {
      USB_LOG_ERR_2(log_usb_dci_cancel_transfer__ep_cmd_write_ep_D_dir_D, ep, dir);
    }

    // for ep0 always set comp_idx to 0 else read it from trb_ring
    dci_ctx->usb_trb_ring[ep][dir].urb_comp_idx
      = (ep == 0) ? 0: dci_ctx->usb_trb_ring[ep][dir].urb_comp_idx;

    trb_comp_idx = &dci_ctx->usb_trb_ring[ep][dir].trb_comp_idx;
    (*trb_comp_idx) = (ep == 0) ? 0: (*trb_comp_idx);

    // identify any hwo TRBs and call their completion.
    for(urb_cnt=0; urb_cnt < USB_URB_MAX; urb_cnt++, CIRINC(trb_ring_ptr->urb_comp_idx, USB_URB_MAX))
    {
      urb_ptr = trb_ring_ptr->urb_ptr[trb_ring_ptr->urb_comp_idx];
      if(urb_ptr && (urb_ptr->transfer_status == USB_URB_STATUS_ACTIVE))
      {
        trb_ptr = &dci_ctx->usb_trb_list[ep][dir][(*trb_comp_idx)];

        if (trb_ptr->hwo)
        {
          trb_ptr->hwo = 0;
          USB_LOG_ERR_2(log_usb_dci_cancel_transfer__trb_hwo_ep_D_dir_D, ep, dir);
        }

        /* If a ZLP TRB was queued increament trb_comp_idx accordingly */
        if ((trb_ptr->chn == 1) && (trb_ptr->ioc == 0))
        {
          usb_fn_dci()->usb_dci_inc_trb_idx(dci_ctx, ep, dir, trb_comp_idx);
          trb_ptr = &dci_ctx->usb_trb_list[ep][dir][(*trb_comp_idx)];

          if (trb_ptr->hwo)
          {
            trb_ptr->hwo = 0;
            USB_LOG_ERR_2(log_usb_dci_cancel_transfer__zlp_trb_hwo_ep_D_dir_D, ep, dir);
          }
        }

        usb_fn_dci()->usb_dci_inc_trb_idx(dci_ctx, ep, dir, trb_comp_idx);

        urb_ptr->transfer_status = USB_URB_STATUS_TRANSFER_CANCEL;
        
        /* URB completion callbacks */
        if(urb_ptr->complete_callback != NULL)
        {
          urb_ptr->complete_callback(urb_ptr);
        }

      }
      urb_ptr = NULL;
    }
  }
  // Reset all TRB counters to point to initial
  trb_ring_ptr->trb_idx = 0;
  trb_ring_ptr->urb_idx = 0;
  trb_ring_ptr->trb_submit_idx = 0;
  trb_ring_ptr->trb_comp_idx = 0;
  trb_ring_ptr->urb_comp_idx = 0;
  trb_ring_ptr->xfer_res_idx = USB_RSC_IDX_NOT_SET;

  for(trb_cnt = 0; trb_cnt < DCI_TRBS; trb_cnt++)
  {
    trb_ring_ptr->swo[trb_cnt] = 0;
  }
  return(DCI_OK);
}

// ===========================================================================
/**
 * @function    usb_dci_shutdown
 * 
 * @brief       This function cancel any active transfer.
 * 
 * @note        This function is called at the end of the DLOAD program before jumping to ARMPROG.
 *              Since ep#1 rx is still active , it need to be canceled.
 * 
 * @param 
 *
 * @return status
 *              0 = ok , otherwise error.
 * 
 * @see usb_dci_cancel_transfer
 * 
 * @ref SNPS spec.
 *      Chapter 8.1.8  Device Initiated disconnect
 */
// ===========================================================================
uint32 usb_dci_shutdown(usb_dci_ctx_t** dci_ptr)
{
  usb_dci_ctx_t* dci_ctx = *dci_ptr;
  uint8  ep, dir;

  USB_ASSERT(dci_ctx);
  dci_ctx->is_attached = FALSE;

  USB_LOG(log_usb_dci_shutdown);

  usb_fn_dci()->usb_dci_set_run_stop(dci_ctx, FALSE);

  // Delay for spoof disconnect( SNPS USB - Table 6-62 )
  usb_fn_util()->usb_delay_ms(30);

  usb_fn_dci_target()->usb_dci_deinit_hs_phy();

  // Cancel pending transfers on all endpoints
  for (ep = 0; ep < DCI_MAX_ENDPOINTS; ep++ )
  {
    for (dir = 0; dir < DCI_MAX_DIRECTION; dir++)
    {
      /* End all of the unfinished transfers */
      usb_fn_dci()->usb_dci_cancel_transfer(dci_ctx, ep, dir);
    }
  }
  
  // Put USB controller (AHB side), USB phy wrapper, AHB2PHY in reset state
  HWIO_CHIP_CFG1_RST_USB_SS_OUT(0xE); 

  usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, FALSE);

  if(dci_ctx->usb_control_tx_buffer)
  {
    usb_fn_mem_util()->usb_free((void **)&dci_ctx->usb_control_tx_buffer);
  }

  usb_fn_mem_util()->usb_free((void**)dci_ptr);

  return(DCI_OK);
}

//============================================================================
/**
 * @function  usb_dci_get_speed
 *
 * @brief Report the USB connection speed.
 *
 * @Note : Although the device is high-speed, the Host might be full-speed.
 *
 * @Note : The USB HW can be forced to Full-Speed.
 *
 * @param None 
 * @return Speed
 *              USB_SPEED_FULL        
 *              USB_SPEED_LOW         
 *              USB_SPEED_HIGH        
 *              USB_SPEED_FULL
 *              USB_SPEED_UNKNOWN     
 *
 * @ref SNPS spec 
 *       Chapter 6.3.1.4 DSTS ( bits 0-2)
 *
 */
//============================================================================
uint32 usb_dci_get_speed(usb_dci_ctx_t* dci_ctx)
{ 
  USB_ASSERT(dci_ctx);

  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  /* Read DSTS to determine the speed */
  dci_ctx->speed = (usb_device_connect_speed_t)HWIO_USBCTL_DSTS_INM(HWIO_USBCTL_DSTS_CONNECTSPD_BMSK);
  
  USB_LOG_1( log_usb_dci_get_speed_log_speed_D, dci_ctx->speed);
  return(dci_ctx->speed);
}

//============================================================================
/**
 * @function  usb_dci_set_max_packet_size
 *
 * @brief Sets the maximum packet size of EP0 to be used
 *
 * @param max_packet_size  
 *
 * @return None  
 *
 * @ref SNPS spec 
 *       
 */
//============================================================================
void usb_dci_set_max_packet_size(usb_dci_ctx_t* dci_ctx, uint32 max_packet_size)
{
  USB_ASSERT(dci_ctx);
  USB_LOG_1( log_usb_dci_set_max_packet_size__D, max_packet_size);
  dci_ctx->usb_dci_max_packet_size = max_packet_size;
  dci_ctx->usb_dci_ep0_max_packet_size =( max_packet_size == 1024 ) ? USB_EP0_MAX_PACKET_SIZE_SUPER :
    USB_EP0_MAX_PACKET_SIZE_HIGH;
}

//============================================================================
/**
 * @function  usb_dci_get_max_packet_size
 *
 * @brief Returns the maximum packet size of EP0 to be used
 *
 * @param None 
 *
 * @return uint32 - max_packet_size   
 *
 * @ref SNPS spec 
 *       
 */
//============================================================================
uint32 usb_dci_get_max_packet_size(usb_dci_ctx_t* dci_ctx)
{
  USB_ASSERT(dci_ctx);
  USB_LOG_1( log_usb_dci_get_max_packet_size__D, dci_ctx->usb_dci_max_packet_size);
  return dci_ctx->usb_dci_max_packet_size;
}

// ===========================================================================
/**
 * @function    usb_dci_handle_set_select
 * 
 * @brief   This function will be used for specifying the system exit latency
 *          in USB. Currently Power management is not supported in SBL driver
 *          so it is safe to set all these values to 0x0. 
 * 
 * @param   dci_ctx - DCI layer context.
 * 
 * @return  None
 * 
 */
// ===========================================================================
void usb_dci_handle_set_select(usb_dci_ctx_t* dci_ctx)
{
  usb_dev_cmd_t dev_cmd;
  USB_LOG(log_usb_dci_handle_set_select);
  memset(&dev_cmd, 0, sizeof(dev_cmd));
  dev_cmd.set_periodic_params.cmd.cmd_typ = USB_DEV_CMD_SET_PERIODIC_PARAMS_VAL; 
  dev_cmd.set_periodic_params.cmd.cmd_act = 0x1; 
  dev_cmd.set_periodic_params.system_exit_latency = 0x00; 

  usb_fn_dci()->usb_dci_write_dev_cmd(dci_ctx, &dev_cmd); 

  return;
}

// ===========================================================================
/**
 * @function    usb_dci_buffer_is_empty
 * 
 * @brief       if any data in the hardware
 * 
 * @details     go through every trb from everypoint to see if any trb is
 *              submit to hardware
 * 
 * @param  usb_dci_ctx_t* dci_ctx
 * 
 * @return status
 *              0 = empty , number trb is submit in hw.
 * 
 * @see 
 * 
 */
// ===========================================================================
uint32 usb_dci_buffer_is_empty(usb_dci_ctx_t* dci_ctx)
{
  uint8  ep, dir, trb_idx;
  USB_ASSERT(dci_ctx);  
  usb_trb_ring_t* trb_ring_ptr;
  uint8 ep_not_empty =0;

  for (ep = 1; ep < DCI_MAX_ENDPOINTS; ep++ )
  {
    for (dir = 0; dir < DCI_MAX_DIRECTION; dir++)
    {
      trb_ring_ptr = &dci_ctx->usb_trb_ring[ep][dir];
      for (trb_idx =0; trb_idx < DCI_TRBS; trb_idx++)
      {
        if (trb_ring_ptr->swo[trb_idx])
        {
          ep_not_empty++;
        }
      }
    }
  }
  return ep_not_empty;
}


void usb_dci_enter_lpm(usb_dci_ctx_t* dci_ctx, pwr_evnt_t event)
{
  USB_ASSERT(dci_ctx);

  switch (event)
  {
    case PWR_EVNT_PHY_L2:
    {
      if (TRUE == dci_ctx->is_usb_clk_on)
      {
        usb_fn_util()->usb_delay_us(3);

        //3. Enabled USBPHY interrupt
        usb_fn_isr()->usb_isr_usbphy_enable(TRUE);
        //4. sw can put usb ram in sleep mode with retention (shutdown usb desc ram buffer)
        //HWIO_CHIP_CFG1_PWR_MEM_SD_OUTM(HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_BMSK,
        //                        0x1 << HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_SHFT);
        
        //5. To save power, software can halt the following clk
        usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, FALSE);

       
        //6. Enabled USBPHY interrupt
        //usb_fn_isr()->usb_isr_usbphy_enable(TRUE);
        //7. sw can put usb ram in sleep mode with retention (shutdown usb desc ram buffer)
        //HWIO_CHIP_CFG1_PWR_MEM_SD_OUTM(HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_BMSK,
        //                           0x1 << HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_SHFT);

        //8. To save power, software can halt the following clk


        //9. MCU set suspend state (SWI bit)
        //10. MCU clear DMA/BLSP votes
        //11. MCU clear the interrupt. No pending interrupts
        //12. MCU run wait 1 instruction which cause pwait signal generation -> trigger uc clock off
      }
      else
      {
        USB_LOG_ERR_2(log_usb_dci_enter_lpm__link_state_D_phy_in_l2_D, dci_ctx->link_state, dci_ctx->phy_in_l2);
      }
    }
    break;

    default:
    break;
  }
}

uint32 usb_dci_poll_pwr_event(usb_dci_ctx_t* dci_ctx)
{
  uint32 pwr_event;
  uint32 sts_reg;
  int32 timeout = USB_DCI_POLLING_TIMEOUT_US;
  pwr_event = HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN;
  while((timeout > 0) && (0 == (pwr_event & (HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK |
                           HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK))))
  {
    usb_fn_util()->usb_delay_us(1);
    timeout--;
    pwr_event = HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN;
  }
  
  if (timeout == 0)
  {
     USB_LOG_ERR(log_usb_dci_poll_pwr_event__timed_out);
     return 0;
  }

  USB_LOG_DBG_1(log_usb_dci_poll_pwr_event__pwr_event_D, pwr_event);
  HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OUT(pwr_event);

  if ((pwr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK) &&
       (pwr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK))
  {
    sts_reg = HWIO_USBCTL_USB30_STS_REG_IN;
    USB_LOG_DBG(log_usb_dci_poll_pwr_event__pwr_ctrl_in_out_l2);    
     
    /* State bits have negative logic */
    if ((~sts_reg) & (HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_SUSPEND_N_BMSK))
    {
      // P3_L2
      usb_fn_dci()->usb_dci_handle_event(dci_ctx, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK);
      USB_LOG_DBG(log_usb_dci_poll_pwr_event__pwr_ctrl_in_l2); 
      return HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK;
    }
    else
    {
      usb_fn_dci()->usb_dci_handle_event(dci_ctx, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK);
      USB_LOG_DBG(log_usb_dci_poll_pwr_event__pwr_ctrl_out_l2);
      return HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK;
    }   
  }
  else
  {     
    if (pwr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK)
    {
      usb_fn_dci()->usb_dci_handle_event(dci_ctx, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK);
      USB_LOG_DBG(log_usb_dci_poll_pwr_event__pwr_ctrl_in_l2); 
      return HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK;
    }
      
    if (pwr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK)
    {
      usb_fn_dci()->usb_dci_handle_event(dci_ctx, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK);
      USB_LOG_DBG(log_usb_dci_poll_pwr_event__pwr_ctrl_out_l2);
      return HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK;
    }

    if (pwr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_L1_EXIT_IRQ_STAT_BMSK)
    {
       USB_LOG_DBG(log_usb_dci_poll_pwr_event__gsi_l1_exit);
       HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK,
                     0x0 << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
       HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK,
                     0x8 << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
       return HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_L1_EXIT_IRQ_STAT_BMSK;
    }
  }
  return 0;
}

void usb_dci_handle_event(usb_dci_ctx_t* dci_ctx, uint32 pwr_event)
{
  if(pwr_event == HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK)
  {
    //led_chg_mode(LED_RED, LED_MODE_BLINK);
    //led_start(LED_RED);

    usb_fn_dci()->usb_dci_enter_lpm(dci_ctx, PWR_EVNT_PHY_L2);
  }
  else if(pwr_event == HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK)
  {
    //led_chg_mode(LED_GREEN, LED_MODE_BLINK);
    //led_start(LED_GREEN);

    usb_fn_dci()->usb_dci_handle_wakeup(dci_ctx);;
  }
  else
  { 
    USB_LOG_ERR_1(log_usb_dci_handle_event__pwr_event_D, pwr_event);
  }  
}

uint32 usb_dci_remote_wakeup(usb_dci_ctx_t* dci_ctx)
{
  uint32 poll_event =0;
  if (FALSE == dci_ctx->remote_wakeup_enabled)
  {
    USB_LOG_ERR(log_usb_dci_remote_wakeup_err_disabled);
    return DCI_ERROR;
  }
 
  if (FALSE == dci_ctx->is_usb_clk_on)
  {
    usb_fn_isr()->usb_isr_usbphy_enable(FALSE); 
   
    usb_fn_util()->usb_enable_clocks(&dci_ctx->is_usb_clk_on, TRUE);
  }

  if (dci_ctx->is_suspended)
  {
    HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OUTM(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_BMSK,
                                    0x0 << HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_SHFT);
      
    usb_fn_dci()->usb_dci_drive_remote_wakeup(dci_ctx);

    poll_event = usb_fn_dci()->usb_dci_poll_pwr_event(dci_ctx);
    if (HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK != poll_event)
    {
      USB_LOG_ERR_1(log_usb_dci_remote_wakeup__failure_poll_event_D, poll_event);
      return DCI_ERROR;
    }
    HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OUTM(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_BMSK,
                                   0x1 << HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_SHFT);
  }
  return 0;
}
void usb_dci_handle_remote_wakeup_enabled(usb_dci_ctx_t* dci_ctx, boolean enabled)
{
  dci_ctx->remote_wakeup_enabled = enabled;
}

boolean usb_dci_is_remote_wakeup_enabled(usb_dci_ctx_t* dci_ctx)
{
  return dci_ctx->remote_wakeup_enabled;
}


#ifdef USB_HWIO_MEM_OPTIMIZE
void usb_out_byte_masked(uint32 addr, uint8 mask, uint8 val)
{
  uint8 current_reg_content = in_byte(addr);
  uint32 final_value = ((current_reg_content & (uint16)(~(mask))) | ((uint16)((val) & (mask))));
  out_byte( addr, final_value);
}


void usb_out_word_masked(uint32 addr, uint16 mask, uint16 val)
{
  uint16 current_reg_content = in_word(addr);
  uint16 final_value = ((current_reg_content & (uint16)(~(mask))) | ((uint16)((val) & (mask))));
  out_word( addr, final_value);
}



void usb_out_dword_masked(uint32 addr, uint32 mask, uint32 val)
{
  uint32 current_reg_content = in_dword(addr);
  uint32 final_value = ((current_reg_content & (uint32)(~(mask))) | ((uint32)((val) & (mask))));
  out_dword( addr, final_value);
}
#endif

//----------------------------------------------------------------------------
// Function table definition - DCI layer
//----------------------------------------------------------------------------

usb_fn_tbl_dci_t fn_tbl_dci = 
{
  usb_dci_handle_u1_u2_enable,
  usb_dci_update_packet_size,
  usb_dci_test_mode_enable,
  usb_dci_handle_test_mode,
  usb_dci_configure_device_mode,
  usb_dci_hw_init,
  usb_dci_init,
  usb_dci_core_init,
  usb_dci_write_ep_cmd,
  usb_dci_write_dev_cmd,
  usb_dci_event_buffer_init,
  usb_dci_set_run_stop,
  usb_dci_get_bm1_from_uf,
  usb_dci_handle_ep_event,
  usb_dci_handle_dev_event,
  usb_dci_poll_events,
  usb_dci_handle_ctrl_transfers,
  usb_dci_inc_trb_idx,
  usb_dci_handle_transfer_complete,
  usb_dci_handle_usb_reset,
  usb_dci_handle_connect_done,
  usb_dci_handle_usb_disconnect,
  usb_dci_get_link_state,
  usb_dci_handle_link_status_change,
  usb_dci_drive_remote_wakeup,
  usb_dci_handle_suspend_entry,
  usb_dci_handle_wakeup,
  usb_dci_get_address,
  usb_dci_set_address,
  usb_dci_get_event_cnt,
  usb_dci_stall_endpoint,
  usb_dci_unstall_endpoint,
  usb_dci_config_endpoint,
  usb_dci_unconfig_endpoint,
  usb_dci_submit_trb_data,
  usb_dci_init_trb_ring,
  usb_dci_prepare_trbs,
  usb_dci_transfer_data_request,
  usb_dci_ctrl_error_recover,
  usb_dci_ctrl_xfer_state_machine,
  usb_dci_ctrl_submit_request,
  usb_dci_transfer_request,
  usb_dci_cancel_transfer,
  usb_dci_shutdown,
  usb_dci_get_speed,
  usb_dci_set_max_packet_size,
  usb_dci_get_max_packet_size,
  usb_dci_handle_set_select,
  usb_dci_buffer_is_empty,
  usb_dci_enter_lpm,
  usb_dci_poll_pwr_event,
  usb_dci_handle_event,
  usb_dci_remote_wakeup,
  usb_dci_handle_remote_wakeup_enabled,
  usb_dci_is_remote_wakeup_enabled, 
};


