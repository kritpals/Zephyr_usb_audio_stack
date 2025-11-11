//============================================================================
/**
 * @file        usb_dci_9x45.c
 * @author      shreyasr
 * @date        19-June-2013
 *
 * @brief       USB (Qualcomm High-Speed USB) DCI (Device-Controller-Interface) PHY specific handling.
 *
 * @details      There might be different PHY types for different targets.
 *               When using 3-wired Full-Speed PHY the USB Core (Link) cannot conntrol the D+/D-.
 * 
 * @note 
 * 
 * @ref         Design Ware Controller spec "DWC_usb3_databook.pdf".
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
// $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dci/usb_dci_9410.c#8 $$DateTime: 2018/02/12 17:09:34 $$Author: pwbldsvc $
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 2013-06-19    shreyasr Added changes for MDM9x35
// 2012-04-14    tnk     Added flat file changes 
// 2010-04-14    yli     MSM8960 branch
// 2008-09-03   amirs    First Draft
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "comdef.h"                 // common defines - basic types as uint32 etc
#include "usb_hwio_9410.h"
#include "usb_dci_9410.h"
#include "usb_util.h"
#include "usb_log.h" 

//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Global Data Definitions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Externalized Function Definitions
//----------------------------------------------------------------------------

// ===========================================================================
/**
 * @function    usb_dci_reset_hw
 * 
 * @brief   API used for resetting the Link and PHYs using GCC control
 *  
 * @details This API is used for resetting the Link and PHYs using clock control 
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_reset_hw(void)
{
  // Release usb mem out of power down
  HWIO_CHIP_CFG1_PWR_MEM_SD_OUTM(HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_BMSK, 
    0 << HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_SHFT);

  // Reset USB sub system
  HWIO_CHIP_CFG1_RST_USB_SS_OUT(0xE);
  usb_fn_util()->usb_delay_us(200);
  HWIO_CHIP_CFG1_RST_USB_SS_OUT(0x0);
}

// ===========================================================================
/**
 * @function    usb_dci_select_utmi_clk
 * 
 * @brief   This is used for configuring the core to UTMI clock instead of pipe
 *          clock.  This needs to be called when there is no SS USB PHY.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_select_utmi_clk()
{
  USB_LOG_ERR(log_usb_dci_select_utmi_clk);
  
  // If operating without SS PHY, follow this sequence to disable 
  // pipe clock requirement
  HWIO_USBCTL_GENERAL_CFG_OUTM(HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
    0x1 << HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);
  
  usb_fn_util()->usb_delay_us(100);
  
  HWIO_USBCTL_GENERAL_CFG_OUTM(HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK,
    0x1 << HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_SEL_SHFT);

  HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTMI(0x0, 
    HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_UTMI_SEL_BMSK, ((uint32)0x10));

  usb_fn_util()->usb_delay_us(1000);
  
  HWIO_USBCTL_GENERAL_CFG_OUTM(HWIO_USBCTL_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK,
    0x1 << HWIO_USBCTL_GENERAL_CFG_PIPE3_PHYSTATUS_SW_SHFT);
  
  usb_fn_util()->usb_delay_us(100);
  
  HWIO_USBCTL_GENERAL_CFG_OUTM(HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK,
    0x0 << HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT);     
}

// ===========================================================================
/**
 * @function    usb_dci_enable_vbus_valid
 * 
 * @brief       API used to enable VBUS using s/w control
 * 
 * @param   usb_max_speed_required_t - Max speed at which device should be 
 *          configured.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_enable_vbus_valid(usb_max_speed_required_t speed_required)
{
  uint32 reg_in;

  //33. USBCTL_USB30_QSCRATCH_HS_PHY_CTRL – not for FPGA external PHY
  reg_in = HWIO_USBCTL_HS_PHY_CTRL_IN;

  // SLEEP SUSPEND PHY CHICKEN BIT
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_HS_PHY_CTRL_SLP_SUSP_PHY_CB_BMSK,
                             HWIO_USBCTL_HS_PHY_CTRL_SLP_SUSP_PHY_CB_SHFT);
  // UTMI SELECT SOURCE OF VALID SEL
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_HS_PHY_CTRL_SW_SESSVLD_SEL_BMSK,
                             HWIO_USBCTL_HS_PHY_CTRL_SW_SESSVLD_SEL_SHFT);
  // UTMI_OTG_VBUS_VALID
  reg_in = USB_VAR_OUTM(reg_in, 0x1, HWIO_USBCTL_HS_PHY_CTRL_UTMI_OTG_VBUS_VALID_BMSK,
                             HWIO_USBCTL_HS_PHY_CTRL_UTMI_OTG_VBUS_VALID_SHFT);
  HWIO_USBCTL_HS_PHY_CTRL_OUT(reg_in);

  //34 USB_CTL_USB30QSCRATCH_SS_PHY_CTRL - not for fpga external PHY
  if (USB_MAX_SPEED_SUPER == speed_required)
  {
    HWIO_USBCTL_SS_PHY_CTRL_OUTM(HWIO_USBCTL_SS_PHY_CTRL_LANE0_PWR_PRESENT_BMSK, 
      (0x1 << HWIO_USBCTL_SS_PHY_CTRL_LANE0_PWR_PRESENT_SHFT));
  }
  
  return;
}


// ------------------------------------------------------------------------------------------------
// Core Initialization APIs
// ------------------------------------------------------------------------------------------------

void usb_dci_enable_audio_timer(void)
{
  //4.  Enable Audio Timer
/*
          // Select clock source as MCLK
          read_data = 0;    // Initialize
          read_data[2] = 'b0;   // TIMER CLOCK SOURCE SELECT
        reg_write("AUDIO_TIMER_CFG_CTRL", read_data);
  
          // Apply reset and release counter 
        reg_read("AUDIO_TIMER_CFG_CTRL", read_data);
        read_data[0] = 'b1;   // TIMER RESET 
        reg_write("AUDIO_TIMER_CFG_CTRL", read_data);
  
          reg_read("AUDIO_TIMER_CFG_CTRL", read_data);
        read_data[0] = 'b0;   // TIMER RESET 
        reg_write("AUDIO_TIMER_CFG_CTRL", read_data);
  
          reg_write("AUDIO_TIMER_INIT_TIMER_MSB", AUDIO_TIMER_INIT_MSB);
        reg_write("AUDIO_TIMER_INIT_TIMER_LSB", AUDIO_TIMER_INIT_LSB);
  
          read_data = 'd9;  // TIMER L_VALUE
        reg_write("AUDIO_TIMER_L_VALUE", read_data);

          read_data = 'd3;  // TIMER M_VALUE
        reg_write("AUDIO_TIMER_M_VALUE", read_data);
  
          read_data = 'd5;  // TIMER N_VALUE
        reg_write("AUDIO_TIMER_N_VALUE", read_data);
  
          reg_read("AUDIO_TIMER_CFG_CTRL", read_data);
        read_data[1] = 'b1;   // TIMER_ENABLE
          reg_write("AUDIO_TIMER_CFG_CTRL", read_data);
        
*/
}

// ===========================================================================
/**
 * @function    usb_dci_select_phy_mode
 * 
 * @brief   This is used for select to use ULPI or UTMI PHY
 * 
 * @param   usb_phy_mode  PHY mode (ulpi, utmi)
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_select_phy_mode(usb_phy_mode phy_mode)
{
    uint32 mode = 0x0;

    USB_LOG_1(log_usb_dci_select_phy_mode__phy_mode_D, phy_mode);

    switch (phy_mode)
    {
      case USB_PHY_MODE_UTMI:
        mode = 0x0;
        break;

      case USB_PHY_MODE_ULPI:
        mode = 0x1;
        break;

      default:
        break;
    }

    HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTMI(0, 
      HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_UTMI_SEL_BMSK,
      mode << HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_UTMI_SEL_SHFT);

    usb_fn_util()->usb_delay_us(100);
}


// ===========================================================================
/**
 * @function    usb_dci_update_override
 * 
 * @brief   This function update default phy setting, call this before
 *          usb_dci_hw_init
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_update_override(void)
{
  HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_OUT(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_POR);
  HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_OUT(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_POR);
  HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_OUT(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_POR);
  HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_OUT(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_POR);
};

// ===========================================================================
/**
 * @function    usb_dci_hs_phy_init
 * 
 * @brief   API used for initializing the HS PHY 
 *  
 * @details Perform any HS PHY calibration here as needed 
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_hs_phy_init(void)
{
  // UTMI_PHY_CMN_CNTRL_OVERRIDE_EN=1. This is a MUX select signal
  HWIO_USBPHY_USB_PHY_CFG0_OUTM(HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);

  // POR (active high)to the PHY. This power on reset must
  // be asserted at least for 10us, after all supplies ramped-up
  HWIO_USBPHY_USB_PHY_UTMI_CTRL5_OUTM(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_SHFT);

  usb_fn_util()->usb_delay_us(20);

  // Turn on analog circuitary in PHY by clearing SIDDQ (retainable) bit.
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT);

  // This sets the refclk (FSEL) frequency to 9.6 Mhz. 
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT);

  // Selects reference clock source. REFCLKSEL[1:0] = 10; select the CLKCORE 
  HWIO_USBPHY_USB_PHY_REFCLK_CTRL_OUTM(HWIO_USBPHY_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK,
    0x2 << HWIO_USBPHY_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT);

  // Selects external VBUS valid by setting VBUSVLDEXTSEL0 to 1
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT);

  // VBUSVLDEXT0 is set to 1. This make VBUS signal valid. Note, the VBUS and ID are not used in the femtoPHY. 
  // They are used in PMU and the information needs to transferred from PMU to AOSS via the SPMI interface 
  // if there is a need for. 
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT);

  // Set parameter OVERRIDE_X as needed
  usb_fn_dci_target()->usb_dci_update_override();

  // Set all inputs to default

  // Set ATERESET = 0 or tie ATERESET with POR: PHYCLOCK is available,after atereset is deasserted.
  HWIO_USBPHY_USB_PHY_UTMI_CTRL5_OUTM(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ATERESET_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ATERESET_SHFT);

  // Set test signals

  // Sets TESTDATAOUTSEL to 0.   
  HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT);
  
  // Sets TESTCLK=0
  HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT);

  // Set VATESTENB=00
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT);
  
  // Sets the TESTDATAIN bits to zero, Until PHYCLOCK is available
  HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK,
    0x00 << HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT);

  // During RESET all the outputs are indeterminate and ignored

  // This sets USB2_SUSPEND_N_SEL=1.  Set suspendm = 1; 
  // until PHYCLOCK is available by setting USB2_SUSPEND_N_SEL and USB2_SUSPEND_N 
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);

  // This sets USB2_SUSPEND_N=1
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT);

  // Sets sleepm = 1; until PHYCLOCK is available 
  HWIO_USBPHY_USB_PHY_UTMI_CTRL0_OUTM(HWIO_USBPHY_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK,
    0x1 << HWIO_USBPHY_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT);

  // Delay 20us
  usb_fn_util()->usb_delay_us(20);

  // Bring PHY out of reset. Set POR = 0; 
  HWIO_USBPHY_USB_PHY_UTMI_CTRL5_OUTM(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_SHFT);
  
  // Set USB2_SUSPEND_N_SEL=0 to de-select the MUX
  HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_OUTM(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT);
  
  // Set UTMI_PHY_CMN_CNTRL_OVERRIDE_EN=0. This is a MUX select signal.
  HWIO_USBPHY_USB_PHY_CFG0_OUTM(HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK,
    0x0 << HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT);
    
}

// ===========================================================================
/**
 * @function    usb_dci_deinit_hs_phy
 * 
 * @brief   API used to de-initialize the High Speed PHY.
 * 
 * @param   None.
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_dci_deinit_hs_phy(void)
{
   /**Clear the D+ Pull Up Assertion*/
   HWIO_USBCTL_HS_PHY_CTRL_OUTM(HWIO_USBCTL_HS_PHY_CTRL_UTMI_OTG_VBUS_VALID_BMSK, 
    (0x0 << HWIO_USBCTL_HS_PHY_CTRL_UTMI_OTG_VBUS_VALID_SHFT));

   HWIO_USBCTL_HS_PHY_CTRL_OUTM(HWIO_USBCTL_HS_PHY_CTRL_SW_SESSVLD_SEL_BMSK, 
    (0x0 << HWIO_USBCTL_HS_PHY_CTRL_SW_SESSVLD_SEL_SHFT));
}

//----------------------------------------------------------------------------
// Function table definition - target specific DCI layer
//----------------------------------------------------------------------------

usb_fn_tbl_dci_target_t fn_tbl_dci_target = 
{
  usb_dci_reset_hw,
  usb_dci_select_utmi_clk,
  usb_dci_enable_vbus_valid,
  usb_dci_select_phy_mode,
  usb_dci_update_override,
  usb_dci_hs_phy_init,
  usb_dci_deinit_hs_phy,
};

