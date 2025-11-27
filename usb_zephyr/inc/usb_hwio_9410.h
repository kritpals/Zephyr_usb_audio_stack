#ifndef __USB_HWIO_9410_H__
#define __USB_HWIO_9410_H__
/*
===========================================================================
*/
/**
  @file usb_hwio_9410.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    WHS9410 (Bolt) v2 [2.0_Pre-P3]
 
  This file contains HWIO register definitions for the following modules:
    USBCTL_DWC_USB3
    USBCTL_USB30_DBM_REGFILE
    USBCTL_USB30_QSCRATCH
    USBPHY_CM_DWC_USB2
    AHB2PHY


  Generation parameters: 
  { u'filename': u'usb_hwio_9410.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [ u'USBCTL_DWC_USB3',
                  u'USBCTL_USB30_DBM_REGFILE',
                  u'USBCTL_USB30_QSCRATCH',
                  u'USBPHY_CM_DWC_USB2',
                  u'AHB2PHY'],
    u'output-offsets': True,
    u'output-phys': True,
    u'output-resets': True}
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

  ===========================================================================

  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/wiredconnectivity/usb/src/dci/usb_hwio_9410.h#1 $
  $DateTime: 2017/10/02 14:38:13 $
  $Author: pwbldsvc $

  ===========================================================================
*/
#include "msmhwiobase.h"
#include "msmhwiorifbase.h"
#include "HALhwio.h"

#define USB_VAR_OUTM(old_value, new_value, mask, shft) \
      (((old_value) & (unsigned int)(~(mask))) | ((unsigned int)(((new_value) << (shft)) & (mask))))
  
#define USB_VAR_INM(value, mask, shft) \
      (((value) & ((mask))) >> (shft))


/*----------------------------------------------------------------------------
 * MODULE: USBCTL_DWC_USB3
 *--------------------------------------------------------------------------*/

#define USBCTL_DWC_USB3_REG_BASE                                                                     (USB20S_BASE      + 0x00000000)
#define USBCTL_DWC_USB3_REG_BASE_PHYS                                                                (USB20S_BASE_PHYS + 0x00000000)
#define USBCTL_DWC_USB3_REG_BASE_OFFS                                                                0x00000000

#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ADDR(p)                                           (USBCTL_DWC_USB3_REG_BASE      + 0x0000c200 + 0x4 * (p))
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYS(p)                                           (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c200 + 0x4 * (p))
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS(p)                                           (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c200 + 0x4 * (p))
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_RMSK                                              0xfdfebfff
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_MAXp                                                       0
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_POR                                               0x00102500
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_POR_RMSK                                          0xffffffff
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ADDR(p), HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_RMSK)
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ADDR(p), mask)
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ADDR(p),val)
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ADDR(p),mask,val,HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_INI(p))
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYSOFTRST_BMSK                                   0x80000000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYSOFTRST_SHFT                                         0x1f
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_U2_FREECLK_EXISTS_BMSK                            0x40000000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_U2_FREECLK_EXISTS_SHFT                                  0x1e
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_LPM_WITH_OPMODE_CHK_BMSK                     0x20000000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_LPM_WITH_OPMODE_CHK_SHFT                           0x1d
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_HSIC_CON_WIDTH_ADJ_BMSK                           0x18000000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_HSIC_CON_WIDTH_ADJ_SHFT                                 0x1b
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_INV_SEL_HSIC_BMSK                                  0x4000000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_INV_SEL_HSIC_SHFT                                       0x1a
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_LSTRD_BMSK                                         0x1c00000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_LSTRD_SHFT                                              0x16
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_LSIPD_BMSK                                          0x380000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_LSIPD_SHFT                                              0x13
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPIEXTVBUSINDIACTOR_BMSK                            0x40000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPIEXTVBUSINDIACTOR_SHFT                               0x12
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPIEXTVBUSDRV_BMSK                                  0x20000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPIEXTVBUSDRV_SHFT                                     0x11
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPIAUTORES_BMSK                                      0x8000
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPIAUTORES_SHFT                                         0xf
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_USBTRDTIM_BMSK                                        0x3c00
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_USBTRDTIM_SHFT                                           0xa
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_XCVRDLY_BMSK                                           0x200
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_XCVRDLY_SHFT                                             0x9
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK                                          0x100
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_SHFT                                            0x8
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYSEL_BMSK                                             0x80
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYSEL_SHFT                                              0x7
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_SUSPENDUSB20_BMSK                                       0x40
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_SUSPENDUSB20_SHFT                                        0x6
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_FSINTF_BMSK                                             0x20
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_FSINTF_SHFT                                              0x5
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_UTMI_SEL_BMSK                                      0x10
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ULPI_UTMI_SEL_SHFT                                       0x4
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYIF_BMSK                                               0x8
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_PHYIF_SHFT                                               0x3
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_TOUTCAL_BMSK                                             0x7
#define HWIO_USBCTL_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_TOUTCAL_SHFT                                             0x0

#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_ADDR(p)                                      (USBCTL_DWC_USB3_REG_BASE      + 0x0000c280 + 0x4 * (p))
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_PHYS(p)                                      (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c280 + 0x4 * (p))
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_OFFS(p)                                      (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c280 + 0x4 * (p))
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_RMSK                                          0x7ffffff
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_MAXp                                                  0
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_POR                                          0x00000000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_POR_RMSK                                     0xffffffff
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_ADDR(p), HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_RMSK)
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_ADDR(p), mask)
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_ADDR(p),val)
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_ADDR(p),mask,val,HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_INI(p))
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_DISUIPIDRVR_BMSK                              0x4000000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_DISUIPIDRVR_SHFT                                   0x1a
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_NEWREGREQ_BMSK                                0x2000000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_NEWREGREQ_SHFT                                     0x19
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSDONE_BMSK                                 0x1000000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSDONE_SHFT                                      0x18
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSBSY_BMSK                                   0x800000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSBSY_SHFT                                       0x17
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGWR_BMSK                                     0x400000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGWR_SHFT                                         0x16
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGADDR_BMSK                                   0x3f0000
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGADDR_SHFT                                       0x10
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_EXTREGADDR_BMSK                                  0xff00
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_EXTREGADDR_SHFT                                     0x8
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGDATA_BMSK                                       0xff
#define HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGDATA_SHFT                                        0x0

#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ADDR(p)                                         (USBCTL_DWC_USB3_REG_BASE      + 0x0000c2c0 + 0x4 * (p))
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_PHYS(p)                                         (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c2c0 + 0x4 * (p))
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(p)                                         (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c2c0 + 0x4 * (p))
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_RMSK                                            0xffffffff
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_MAXp                                                     0
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_POR                                             0x010c0002
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_POR_RMSK                                        0xffffffff
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ADDR(p), HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_RMSK)
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ADDR(p), mask)
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ADDR(p),val)
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ADDR(p),mask,val,HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_INI(p))
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_PHYSOFTRST_BMSK                                 0x80000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_PHYSOFTRST_SHFT                                       0x1f
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK                                 0x40000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT                                       0x1e
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_U2P3OK_BMSK                                     0x20000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_U2P3OK_SHFT                                           0x1d
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DISRXDETP3_BMSK                                 0x10000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DISRXDETP3_SHFT                                       0x1c
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK                               0x8000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_SHFT                                    0x1b
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_PING_ENHANCEMENT_EN_BMSK                         0x4000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_PING_ENHANCEMENT_EN_SHFT                              0x1a
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_U1U2EXITFAIL_TO_RECOV_BMSK                       0x2000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_U1U2EXITFAIL_TO_RECOV_SHFT                            0x19
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_REQUEST_P1P2P3_BMSK                              0x1000000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_REQUEST_P1P2P3_SHFT                                   0x18
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_STARTRXDETU3RXDET_BMSK                            0x800000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_STARTRXDETU3RXDET_SHFT                                0x17
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DISRXDETU3RXDET_BMSK                              0x400000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DISRXDETU3RXDET_SHFT                                  0x16
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1P2P3_BMSK                                  0x380000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1P2P3_SHFT                                      0x13
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_BMSK                                  0x40000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_SHFT                                     0x12
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SUSPENDENABLE_BMSK                                 0x20000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SUSPENDENABLE_SHFT                                    0x11
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DATWIDTH_BMSK                                      0x18000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DATWIDTH_SHFT                                          0xf
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ABORTRXDETINU2_BMSK                                 0x4000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ABORTRXDETINU2_SHFT                                    0xe
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SKIPRXDET_BMSK                                      0x2000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SKIPRXDET_SHFT                                         0xd
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_LFPSP0ALGN_BMSK                                     0x1000
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_LFPSP0ALGN_SHFT                                        0xc
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3P2TRANOK_BMSK                                      0x800
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3P2TRANOK_SHFT                                        0xb
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3EXSIGP2_BMSK                                       0x400
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3EXSIGP2_SHFT                                         0xa
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_LFPSFILTER_BMSK                                      0x200
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_LFPSFILTER_SHFT                                        0x9
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_RX_DETECT_TO_POLLING_LFPS_CONTROL_BMSK               0x100
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_RX_DETECT_TO_POLLING_LFPS_CONTROL_SHFT                 0x8
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SSICEN_BMSK                                           0x80
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SSICEN_SHFT                                            0x7
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_TX_SWING_BMSK                                         0x40
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_TX_SWING_SHFT                                          0x6
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_TX_MARGIN_BMSK                                        0x38
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_TX_MARGIN_SHFT                                         0x3
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SS_TX_DE_EMPHASIS_BMSK                                 0x6
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_SS_TX_DE_EMPHASIS_SHFT                                 0x1
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ELASTIC_BUFFER_MODE_BMSK                               0x1
#define HWIO_USBCTL_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_ELASTIC_BUFFER_MODE_SHFT                               0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c300 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c300 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c300 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_POR                                                0x05c60042
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ0_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c304 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c304 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c304 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_POR                                                0x06080203
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ1_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c308 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c308 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c308 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_POR                                                0x080b0082
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ2_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c30c + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c30c + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c30c + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_POR                                                0x088d0203
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ3_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c310 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c310 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c310 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_POR                                                0x0a900203
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ4_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c314 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c314 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c314 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_POR                                                0x0c930024
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ5_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c318 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c318 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c318 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_POR                                                0x0cb70024
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ6_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c31c + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c31c + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c31c + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_POR                                                0x0cdb0012
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ7_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c320 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c320 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c320 + 0x40 * (p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_RMSK                                               0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_MAXp                                                        0
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_POR                                                0x0ced0012
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_ADDR(p), HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_RMSK)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_ADDR(p), mask)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_ADDR(p),val)
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_ADDR(p),mask,val,HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_INI(p))
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_TXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_TXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_TXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GTXFIFOSIZ_REGS_p_GTXFIFOSIZ8_TXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_ADDR(p)                                            (USBCTL_DWC_USB3_REG_BASE      + 0x0000c380 + 0x40 * (p))
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_PHYS(p)                                            (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c380 + 0x40 * (p))
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_OFFS(p)                                            (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c380 + 0x40 * (p))
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RMSK                                               0xffffffff
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_MAXp                                                        0
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_POR                                                0x02bc030a
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_ADDR(p), HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RMSK)
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_ADDR(p), mask)
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_ADDR(p),val)
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_ADDR(p),mask,val,HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_INI(p))
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RXFSTADDR_N_BMSK                                   0xffff0000
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RXFSTADDR_N_SHFT                                         0x10
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RXFDEP_N_BMSK                                          0xffff
#define HWIO_USBCTL_GRXFIFOSIZ_REGS_p_GRXFIFOSIZ0_RXFDEP_N_SHFT                                             0x0

#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_ADDR(p)                                             (USBCTL_DWC_USB3_REG_BASE      + 0x0000c400 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_PHYS(p)                                             (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c400 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_OFFS(p)                                             (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c400 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_RMSK                                                0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_MAXp                                                         0
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_POR                                                 0x00000000
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_ADDR(p), HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_RMSK)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_ADDR(p), mask)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_ADDR(p),val)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_ADDR(p),mask,val,HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_INI(p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_EVNTADRLO_BMSK                                      0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRLO_EVNTADRLO_SHFT                                             0x0

#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_ADDR(p)                                             (USBCTL_DWC_USB3_REG_BASE      + 0x0000c404 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_PHYS(p)                                             (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c404 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_OFFS(p)                                             (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c404 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_RMSK                                                0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_MAXp                                                         0
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_POR                                                 0x00000000
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_ADDR(p), HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_RMSK)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_ADDR(p), mask)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_ADDR(p),val)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_ADDR(p),mask,val,HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_INI(p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_EVNTADRHI_BMSK                                      0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTADRHI_EVNTADRHI_SHFT                                             0x0

#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_ADDR(p)                                               (USBCTL_DWC_USB3_REG_BASE      + 0x0000c408 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_PHYS(p)                                               (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c408 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_OFFS(p)                                               (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c408 + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_RMSK                                                  0x8000ffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_MAXp                                                           0
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_POR                                                   0x00000000
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_POR_RMSK                                              0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_ADDR(p), HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_RMSK)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_ADDR(p), mask)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_ADDR(p),val)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_ADDR(p),mask,val,HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_INI(p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_EVNTINTRPTMASK_BMSK                                   0x80000000
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_EVNTINTRPTMASK_SHFT                                         0x1f
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_EVENTSIZ_BMSK                                             0xffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTSIZ_EVENTSIZ_SHFT                                                0x0

#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_ADDR(p)                                             (USBCTL_DWC_USB3_REG_BASE      + 0x0000c40c + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_PHYS(p)                                             (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c40c + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OFFS(p)                                             (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c40c + 0x10 * (p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_RMSK                                                0x8000ffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_MAXp                                                         0
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_POR                                                 0x00000000
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INI(p)        \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_ADDR(p), HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_RMSK)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_ADDR(p), mask)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_ADDR(p),val)
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_ADDR(p),mask,val,HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INI(p))
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNT_HANDLER_BUSY_BMSK                              0x80000000
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNT_HANDLER_BUSY_SHFT                                    0x1f
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK                                          0xffff
#define HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_SHFT                                             0x0

#define HWIO_USBCTL_GSBUSCFG0_ADDR                                                                   (USBCTL_DWC_USB3_REG_BASE      + 0x0000c100)
#define HWIO_USBCTL_GSBUSCFG0_PHYS                                                                   (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c100)
#define HWIO_USBCTL_GSBUSCFG0_OFFS                                                                   (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c100)
#define HWIO_USBCTL_GSBUSCFG0_RMSK                                                                   0xffff0cff
#define HWIO_USBCTL_GSBUSCFG0_POR                                                                    0xc0c0000e
#define HWIO_USBCTL_GSBUSCFG0_POR_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GSBUSCFG0_IN          \
        in_dword_masked(HWIO_USBCTL_GSBUSCFG0_ADDR, HWIO_USBCTL_GSBUSCFG0_RMSK)
#define HWIO_USBCTL_GSBUSCFG0_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GSBUSCFG0_ADDR, m)
#define HWIO_USBCTL_GSBUSCFG0_OUT(v)      \
        out_dword(HWIO_USBCTL_GSBUSCFG0_ADDR,v)
#define HWIO_USBCTL_GSBUSCFG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GSBUSCFG0_ADDR,m,v,HWIO_USBCTL_GSBUSCFG0_IN)
#define HWIO_USBCTL_GSBUSCFG0_DATRDREQINFO_BMSK                                                      0xf0000000
#define HWIO_USBCTL_GSBUSCFG0_DATRDREQINFO_SHFT                                                            0x1c
#define HWIO_USBCTL_GSBUSCFG0_DESRDREQINFO_BMSK                                                       0xf000000
#define HWIO_USBCTL_GSBUSCFG0_DESRDREQINFO_SHFT                                                            0x18
#define HWIO_USBCTL_GSBUSCFG0_DATWRREQINFO_BMSK                                                        0xf00000
#define HWIO_USBCTL_GSBUSCFG0_DATWRREQINFO_SHFT                                                            0x14
#define HWIO_USBCTL_GSBUSCFG0_DESWRREQINFO_BMSK                                                         0xf0000
#define HWIO_USBCTL_GSBUSCFG0_DESWRREQINFO_SHFT                                                            0x10
#define HWIO_USBCTL_GSBUSCFG0_DATBIGEND_BMSK                                                              0x800
#define HWIO_USBCTL_GSBUSCFG0_DATBIGEND_SHFT                                                                0xb
#define HWIO_USBCTL_GSBUSCFG0_DESBIGEND_BMSK                                                              0x400
#define HWIO_USBCTL_GSBUSCFG0_DESBIGEND_SHFT                                                                0xa
#define HWIO_USBCTL_GSBUSCFG0_INCR256BRSTENA_BMSK                                                          0x80
#define HWIO_USBCTL_GSBUSCFG0_INCR256BRSTENA_SHFT                                                           0x7
#define HWIO_USBCTL_GSBUSCFG0_INCR128BRSTENA_BMSK                                                          0x40
#define HWIO_USBCTL_GSBUSCFG0_INCR128BRSTENA_SHFT                                                           0x6
#define HWIO_USBCTL_GSBUSCFG0_INCR64BRSTENA_BMSK                                                           0x20
#define HWIO_USBCTL_GSBUSCFG0_INCR64BRSTENA_SHFT                                                            0x5
#define HWIO_USBCTL_GSBUSCFG0_INCR32BRSTENA_BMSK                                                           0x10
#define HWIO_USBCTL_GSBUSCFG0_INCR32BRSTENA_SHFT                                                            0x4
#define HWIO_USBCTL_GSBUSCFG0_INCR16BRSTENA_BMSK                                                            0x8
#define HWIO_USBCTL_GSBUSCFG0_INCR16BRSTENA_SHFT                                                            0x3
#define HWIO_USBCTL_GSBUSCFG0_INCR8BRSTENA_BMSK                                                             0x4
#define HWIO_USBCTL_GSBUSCFG0_INCR8BRSTENA_SHFT                                                             0x2
#define HWIO_USBCTL_GSBUSCFG0_INCR4BRSTENA_BMSK                                                             0x2
#define HWIO_USBCTL_GSBUSCFG0_INCR4BRSTENA_SHFT                                                             0x1
#define HWIO_USBCTL_GSBUSCFG0_INCRBRSTENA_BMSK                                                              0x1
#define HWIO_USBCTL_GSBUSCFG0_INCRBRSTENA_SHFT                                                              0x0

#define HWIO_USBCTL_GSBUSCFG1_ADDR                                                                   (USBCTL_DWC_USB3_REG_BASE      + 0x0000c104)
#define HWIO_USBCTL_GSBUSCFG1_PHYS                                                                   (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c104)
#define HWIO_USBCTL_GSBUSCFG1_OFFS                                                                   (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c104)
#define HWIO_USBCTL_GSBUSCFG1_RMSK                                                                       0x1f00
#define HWIO_USBCTL_GSBUSCFG1_POR                                                                    0x00001700
#define HWIO_USBCTL_GSBUSCFG1_POR_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GSBUSCFG1_IN          \
        in_dword_masked(HWIO_USBCTL_GSBUSCFG1_ADDR, HWIO_USBCTL_GSBUSCFG1_RMSK)
#define HWIO_USBCTL_GSBUSCFG1_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GSBUSCFG1_ADDR, m)
#define HWIO_USBCTL_GSBUSCFG1_OUT(v)      \
        out_dword(HWIO_USBCTL_GSBUSCFG1_ADDR,v)
#define HWIO_USBCTL_GSBUSCFG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GSBUSCFG1_ADDR,m,v,HWIO_USBCTL_GSBUSCFG1_IN)
#define HWIO_USBCTL_GSBUSCFG1_EN1KPAGE_BMSK                                                              0x1000
#define HWIO_USBCTL_GSBUSCFG1_EN1KPAGE_SHFT                                                                 0xc
#define HWIO_USBCTL_GSBUSCFG1_PIPETRANSLIMIT_BMSK                                                         0xf00
#define HWIO_USBCTL_GSBUSCFG1_PIPETRANSLIMIT_SHFT                                                           0x8

#define HWIO_USBCTL_GTXTHRCFG_ADDR                                                                   (USBCTL_DWC_USB3_REG_BASE      + 0x0000c108)
#define HWIO_USBCTL_GTXTHRCFG_PHYS                                                                   (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c108)
#define HWIO_USBCTL_GTXTHRCFG_OFFS                                                                   (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c108)
#define HWIO_USBCTL_GTXTHRCFG_RMSK                                                                   0x2fff0000
#define HWIO_USBCTL_GTXTHRCFG_POR                                                                    0x00000000
#define HWIO_USBCTL_GTXTHRCFG_POR_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GTXTHRCFG_IN          \
        in_dword_masked(HWIO_USBCTL_GTXTHRCFG_ADDR, HWIO_USBCTL_GTXTHRCFG_RMSK)
#define HWIO_USBCTL_GTXTHRCFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GTXTHRCFG_ADDR, m)
#define HWIO_USBCTL_GTXTHRCFG_OUT(v)      \
        out_dword(HWIO_USBCTL_GTXTHRCFG_ADDR,v)
#define HWIO_USBCTL_GTXTHRCFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GTXTHRCFG_ADDR,m,v,HWIO_USBCTL_GTXTHRCFG_IN)
#define HWIO_USBCTL_GTXTHRCFG_USBTXPKTCNTSEL_BMSK                                                    0x20000000
#define HWIO_USBCTL_GTXTHRCFG_USBTXPKTCNTSEL_SHFT                                                          0x1d
#define HWIO_USBCTL_GTXTHRCFG_USBTXPKTCNT_BMSK                                                        0xf000000
#define HWIO_USBCTL_GTXTHRCFG_USBTXPKTCNT_SHFT                                                             0x18
#define HWIO_USBCTL_GTXTHRCFG_USBMAXTXBURSTSIZE_BMSK                                                   0xff0000
#define HWIO_USBCTL_GTXTHRCFG_USBMAXTXBURSTSIZE_SHFT                                                       0x10

#define HWIO_USBCTL_GRXTHRCFG_ADDR                                                                   (USBCTL_DWC_USB3_REG_BASE      + 0x0000c10c)
#define HWIO_USBCTL_GRXTHRCFG_PHYS                                                                   (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c10c)
#define HWIO_USBCTL_GRXTHRCFG_OFFS                                                                   (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c10c)
#define HWIO_USBCTL_GRXTHRCFG_RMSK                                                                   0x2ff81fff
#define HWIO_USBCTL_GRXTHRCFG_POR                                                                    0x00000000
#define HWIO_USBCTL_GRXTHRCFG_POR_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GRXTHRCFG_IN          \
        in_dword_masked(HWIO_USBCTL_GRXTHRCFG_ADDR, HWIO_USBCTL_GRXTHRCFG_RMSK)
#define HWIO_USBCTL_GRXTHRCFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GRXTHRCFG_ADDR, m)
#define HWIO_USBCTL_GRXTHRCFG_OUT(v)      \
        out_dword(HWIO_USBCTL_GRXTHRCFG_ADDR,v)
#define HWIO_USBCTL_GRXTHRCFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GRXTHRCFG_ADDR,m,v,HWIO_USBCTL_GRXTHRCFG_IN)
#define HWIO_USBCTL_GRXTHRCFG_USBRXPKTCNTSEL_BMSK                                                    0x20000000
#define HWIO_USBCTL_GRXTHRCFG_USBRXPKTCNTSEL_SHFT                                                          0x1d
#define HWIO_USBCTL_GRXTHRCFG_USBRXPKTCNT_BMSK                                                        0xf000000
#define HWIO_USBCTL_GRXTHRCFG_USBRXPKTCNT_SHFT                                                             0x18
#define HWIO_USBCTL_GRXTHRCFG_USBMAXRXBURSTSIZE_BMSK                                                   0xf80000
#define HWIO_USBCTL_GRXTHRCFG_USBMAXRXBURSTSIZE_SHFT                                                       0x13
#define HWIO_USBCTL_GRXTHRCFG_RESVISOCOUTSPC_BMSK                                                        0x1fff
#define HWIO_USBCTL_GRXTHRCFG_RESVISOCOUTSPC_SHFT                                                           0x0

#define HWIO_USBCTL_GCTL_ADDR                                                                        (USBCTL_DWC_USB3_REG_BASE      + 0x0000c110)
#define HWIO_USBCTL_GCTL_PHYS                                                                        (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c110)
#define HWIO_USBCTL_GCTL_OFFS                                                                        (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c110)
#define HWIO_USBCTL_GCTL_RMSK                                                                        0xffffffff
#define HWIO_USBCTL_GCTL_POR                                                                         0x00102000
#define HWIO_USBCTL_GCTL_POR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_GCTL_IN          \
        in_dword_masked(HWIO_USBCTL_GCTL_ADDR, HWIO_USBCTL_GCTL_RMSK)
#define HWIO_USBCTL_GCTL_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GCTL_ADDR, m)
#define HWIO_USBCTL_GCTL_OUT(v)      \
        out_dword(HWIO_USBCTL_GCTL_ADDR,v)
#define HWIO_USBCTL_GCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GCTL_ADDR,m,v,HWIO_USBCTL_GCTL_IN)
#define HWIO_USBCTL_GCTL_PWRDNSCALE_BMSK                                                             0xfff80000
#define HWIO_USBCTL_GCTL_PWRDNSCALE_SHFT                                                                   0x13
#define HWIO_USBCTL_GCTL_MASTERFILTBYPASS_BMSK                                                          0x40000
#define HWIO_USBCTL_GCTL_MASTERFILTBYPASS_SHFT                                                             0x12
#define HWIO_USBCTL_GCTL_BYPSSETADDR_BMSK                                                               0x20000
#define HWIO_USBCTL_GCTL_BYPSSETADDR_SHFT                                                                  0x11
#define HWIO_USBCTL_GCTL_U2RSTECN_BMSK                                                                  0x10000
#define HWIO_USBCTL_GCTL_U2RSTECN_SHFT                                                                     0x10
#define HWIO_USBCTL_GCTL_FRMSCLDWN_BMSK                                                                  0xc000
#define HWIO_USBCTL_GCTL_FRMSCLDWN_SHFT                                                                     0xe
#define HWIO_USBCTL_GCTL_PRTCAPDIR_BMSK                                                                  0x3000
#define HWIO_USBCTL_GCTL_PRTCAPDIR_SHFT                                                                     0xc
#define HWIO_USBCTL_GCTL_CORESOFTRESET_BMSK                                                               0x800
#define HWIO_USBCTL_GCTL_CORESOFTRESET_SHFT                                                                 0xb
#define HWIO_USBCTL_GCTL_SOFITPSYNC_BMSK                                                                  0x400
#define HWIO_USBCTL_GCTL_SOFITPSYNC_SHFT                                                                    0xa
#define HWIO_USBCTL_GCTL_U1U2TIMERSCALE_BMSK                                                              0x200
#define HWIO_USBCTL_GCTL_U1U2TIMERSCALE_SHFT                                                                0x9
#define HWIO_USBCTL_GCTL_DEBUGATTACH_BMSK                                                                 0x100
#define HWIO_USBCTL_GCTL_DEBUGATTACH_SHFT                                                                   0x8
#define HWIO_USBCTL_GCTL_RAMCLKSEL_BMSK                                                                    0xc0
#define HWIO_USBCTL_GCTL_RAMCLKSEL_SHFT                                                                     0x6
#define HWIO_USBCTL_GCTL_SCALEDOWN_BMSK                                                                    0x30
#define HWIO_USBCTL_GCTL_SCALEDOWN_SHFT                                                                     0x4
#define HWIO_USBCTL_GCTL_DISSCRAMBLE_BMSK                                                                   0x8
#define HWIO_USBCTL_GCTL_DISSCRAMBLE_SHFT                                                                   0x3
#define HWIO_USBCTL_GCTL_U2EXIT_LFPS_BMSK                                                                   0x4
#define HWIO_USBCTL_GCTL_U2EXIT_LFPS_SHFT                                                                   0x2
#define HWIO_USBCTL_GCTL_GBLHIBERNATIONEN_BMSK                                                              0x2
#define HWIO_USBCTL_GCTL_GBLHIBERNATIONEN_SHFT                                                              0x1
#define HWIO_USBCTL_GCTL_DSBLCLKGTNG_BMSK                                                                   0x1
#define HWIO_USBCTL_GCTL_DSBLCLKGTNG_SHFT                                                                   0x0

#define HWIO_USBCTL_GPMSTS_ADDR                                                                      (USBCTL_DWC_USB3_REG_BASE      + 0x0000c114)
#define HWIO_USBCTL_GPMSTS_PHYS                                                                      (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c114)
#define HWIO_USBCTL_GPMSTS_OFFS                                                                      (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c114)
#define HWIO_USBCTL_GPMSTS_RMSK                                                                      0xf001f3ff
#define HWIO_USBCTL_GPMSTS_POR                                                                       0x00000000
#define HWIO_USBCTL_GPMSTS_POR_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GPMSTS_IN          \
        in_dword_masked(HWIO_USBCTL_GPMSTS_ADDR, HWIO_USBCTL_GPMSTS_RMSK)
#define HWIO_USBCTL_GPMSTS_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPMSTS_ADDR, m)
#define HWIO_USBCTL_GPMSTS_OUT(v)      \
        out_dword(HWIO_USBCTL_GPMSTS_ADDR,v)
#define HWIO_USBCTL_GPMSTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPMSTS_ADDR,m,v,HWIO_USBCTL_GPMSTS_IN)
#define HWIO_USBCTL_GPMSTS_PORTSEL_BMSK                                                              0xf0000000
#define HWIO_USBCTL_GPMSTS_PORTSEL_SHFT                                                                    0x1c
#define HWIO_USBCTL_GPMSTS_U3WAKEUP_BMSK                                                                0x1f000
#define HWIO_USBCTL_GPMSTS_U3WAKEUP_SHFT                                                                    0xc
#define HWIO_USBCTL_GPMSTS_U2WAKEUP_BMSK                                                                  0x3ff
#define HWIO_USBCTL_GPMSTS_U2WAKEUP_SHFT                                                                    0x0

#define HWIO_USBCTL_GSTS_ADDR                                                                        (USBCTL_DWC_USB3_REG_BASE      + 0x0000c118)
#define HWIO_USBCTL_GSTS_PHYS                                                                        (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c118)
#define HWIO_USBCTL_GSTS_OFFS                                                                        (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c118)
#define HWIO_USBCTL_GSTS_RMSK                                                                        0xfff00ff3
#define HWIO_USBCTL_GSTS_POR                                                                         0x00000000
#define HWIO_USBCTL_GSTS_POR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_GSTS_IN          \
        in_dword_masked(HWIO_USBCTL_GSTS_ADDR, HWIO_USBCTL_GSTS_RMSK)
#define HWIO_USBCTL_GSTS_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GSTS_ADDR, m)
#define HWIO_USBCTL_GSTS_OUT(v)      \
        out_dword(HWIO_USBCTL_GSTS_ADDR,v)
#define HWIO_USBCTL_GSTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GSTS_ADDR,m,v,HWIO_USBCTL_GSTS_IN)
#define HWIO_USBCTL_GSTS_CBELT_BMSK                                                                  0xfff00000
#define HWIO_USBCTL_GSTS_CBELT_SHFT                                                                        0x14
#define HWIO_USBCTL_GSTS_SSIC_IP_BMSK                                                                     0x800
#define HWIO_USBCTL_GSTS_SSIC_IP_SHFT                                                                       0xb
#define HWIO_USBCTL_GSTS_OTG_IP_BMSK                                                                      0x400
#define HWIO_USBCTL_GSTS_OTG_IP_SHFT                                                                        0xa
#define HWIO_USBCTL_GSTS_BC_IP_BMSK                                                                       0x200
#define HWIO_USBCTL_GSTS_BC_IP_SHFT                                                                         0x9
#define HWIO_USBCTL_GSTS_ADP_IP_BMSK                                                                      0x100
#define HWIO_USBCTL_GSTS_ADP_IP_SHFT                                                                        0x8
#define HWIO_USBCTL_GSTS_HOST_IP_BMSK                                                                      0x80
#define HWIO_USBCTL_GSTS_HOST_IP_SHFT                                                                       0x7
#define HWIO_USBCTL_GSTS_DEVICE_IP_BMSK                                                                    0x40
#define HWIO_USBCTL_GSTS_DEVICE_IP_SHFT                                                                     0x6
#define HWIO_USBCTL_GSTS_CSRTIMEOUT_BMSK                                                                   0x20
#define HWIO_USBCTL_GSTS_CSRTIMEOUT_SHFT                                                                    0x5
#define HWIO_USBCTL_GSTS_BUSERRADDRVLD_BMSK                                                                0x10
#define HWIO_USBCTL_GSTS_BUSERRADDRVLD_SHFT                                                                 0x4
#define HWIO_USBCTL_GSTS_CURMOD_BMSK                                                                        0x3
#define HWIO_USBCTL_GSTS_CURMOD_SHFT                                                                        0x0

#define HWIO_USBCTL_GUCTL1_ADDR                                                                      (USBCTL_DWC_USB3_REG_BASE      + 0x0000c11c)
#define HWIO_USBCTL_GUCTL1_PHYS                                                                      (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c11c)
#define HWIO_USBCTL_GUCTL1_OFFS                                                                      (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c11c)
#define HWIO_USBCTL_GUCTL1_RMSK                                                                      0xffff87ff
#define HWIO_USBCTL_GUCTL1_POR                                                                       0x000c0002
#define HWIO_USBCTL_GUCTL1_POR_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GUCTL1_IN          \
        in_dword_masked(HWIO_USBCTL_GUCTL1_ADDR, HWIO_USBCTL_GUCTL1_RMSK)
#define HWIO_USBCTL_GUCTL1_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GUCTL1_ADDR, m)
#define HWIO_USBCTL_GUCTL1_OUT(v)      \
        out_dword(HWIO_USBCTL_GUCTL1_ADDR,v)
#define HWIO_USBCTL_GUCTL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GUCTL1_ADDR,m,v,HWIO_USBCTL_GUCTL1_IN)
#define HWIO_USBCTL_GUCTL1_DEV_DECOUPLE_L1L2_EVT_BMSK                                                0x80000000
#define HWIO_USBCTL_GUCTL1_DEV_DECOUPLE_L1L2_EVT_SHFT                                                      0x1f
#define HWIO_USBCTL_GUCTL1_DS_RXDET_MAX_TOUT_CTRL_BMSK                                               0x40000000
#define HWIO_USBCTL_GUCTL1_DS_RXDET_MAX_TOUT_CTRL_SHFT                                                     0x1e
#define HWIO_USBCTL_GUCTL1_FILTER_SE0_FSLS_EOP_BMSK                                                  0x20000000
#define HWIO_USBCTL_GUCTL1_FILTER_SE0_FSLS_EOP_SHFT                                                        0x1d
#define HWIO_USBCTL_GUCTL1_TX_IPGAP_LINECHECK_DIS_BMSK                                               0x10000000
#define HWIO_USBCTL_GUCTL1_TX_IPGAP_LINECHECK_DIS_SHFT                                                     0x1c
#define HWIO_USBCTL_GUCTL1_DEV_TRB_OUT_SPR_IND_BMSK                                                   0x8000000
#define HWIO_USBCTL_GUCTL1_DEV_TRB_OUT_SPR_IND_SHFT                                                        0x1b
#define HWIO_USBCTL_GUCTL1_DEV_FORCE_20_CLK_FOR_30_CLK_BMSK                                           0x4000000
#define HWIO_USBCTL_GUCTL1_DEV_FORCE_20_CLK_FOR_30_CLK_SHFT                                                0x1a
#define HWIO_USBCTL_GUCTL1_P3_IN_U2_BMSK                                                              0x2000000
#define HWIO_USBCTL_GUCTL1_P3_IN_U2_SHFT                                                                   0x19
#define HWIO_USBCTL_GUCTL1_DEV_L1_EXIT_BY_HW_BMSK                                                     0x1000000
#define HWIO_USBCTL_GUCTL1_DEV_L1_EXIT_BY_HW_SHFT                                                          0x18
#define HWIO_USBCTL_GUCTL1_IP_GAP_ADD_ON_BMSK                                                          0xe00000
#define HWIO_USBCTL_GUCTL1_IP_GAP_ADD_ON_SHFT                                                              0x15
#define HWIO_USBCTL_GUCTL1_DEV_LSP_TAIL_LOCK_DIS_BMSK                                                  0x100000
#define HWIO_USBCTL_GUCTL1_DEV_LSP_TAIL_LOCK_DIS_SHFT                                                      0x14
#define HWIO_USBCTL_GUCTL1_NAK_PER_ENH_FS_BMSK                                                          0x80000
#define HWIO_USBCTL_GUCTL1_NAK_PER_ENH_FS_SHFT                                                             0x13
#define HWIO_USBCTL_GUCTL1_NAK_PER_ENH_HS_BMSK                                                          0x40000
#define HWIO_USBCTL_GUCTL1_NAK_PER_ENH_HS_SHFT                                                             0x12
#define HWIO_USBCTL_GUCTL1_PARKMODE_DISABLE_SS_BMSK                                                     0x20000
#define HWIO_USBCTL_GUCTL1_PARKMODE_DISABLE_SS_SHFT                                                        0x11
#define HWIO_USBCTL_GUCTL1_PARKMODE_DISABLE_HS_BMSK                                                     0x10000
#define HWIO_USBCTL_GUCTL1_PARKMODE_DISABLE_HS_SHFT                                                        0x10
#define HWIO_USBCTL_GUCTL1_PARKMODE_DISABLE_FSLS_BMSK                                                    0x8000
#define HWIO_USBCTL_GUCTL1_PARKMODE_DISABLE_FSLS_SHFT                                                       0xf
#define HWIO_USBCTL_GUCTL1_RESUME_OPMODE_HS_HOST_BMSK                                                     0x400
#define HWIO_USBCTL_GUCTL1_RESUME_OPMODE_HS_HOST_SHFT                                                       0xa
#define HWIO_USBCTL_GUCTL1_DEV_HS_NYET_BULK_SPR_BMSK                                                      0x200
#define HWIO_USBCTL_GUCTL1_DEV_HS_NYET_BULK_SPR_SHFT                                                        0x9
#define HWIO_USBCTL_GUCTL1_L1_SUSP_THRLD_EN_FOR_HOST_BMSK                                                 0x100
#define HWIO_USBCTL_GUCTL1_L1_SUSP_THRLD_EN_FOR_HOST_SHFT                                                   0x8
#define HWIO_USBCTL_GUCTL1_L1_SUSP_THRLD_FOR_HOST_BMSK                                                     0xf0
#define HWIO_USBCTL_GUCTL1_L1_SUSP_THRLD_FOR_HOST_SHFT                                                      0x4
#define HWIO_USBCTL_GUCTL1_HC_ERRATA_ENABLE_BMSK                                                            0x8
#define HWIO_USBCTL_GUCTL1_HC_ERRATA_ENABLE_SHFT                                                            0x3
#define HWIO_USBCTL_GUCTL1_HC_PARCHK_DISABLE_BMSK                                                           0x4
#define HWIO_USBCTL_GUCTL1_HC_PARCHK_DISABLE_SHFT                                                           0x2
#define HWIO_USBCTL_GUCTL1_OVRLD_L1_SUSP_COM_BMSK                                                           0x2
#define HWIO_USBCTL_GUCTL1_OVRLD_L1_SUSP_COM_SHFT                                                           0x1
#define HWIO_USBCTL_GUCTL1_LOA_FILTER_EN_BMSK                                                               0x1
#define HWIO_USBCTL_GUCTL1_LOA_FILTER_EN_SHFT                                                               0x0

#define HWIO_USBCTL_GSNPSID_ADDR                                                                     (USBCTL_DWC_USB3_REG_BASE      + 0x0000c120)
#define HWIO_USBCTL_GSNPSID_PHYS                                                                     (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c120)
#define HWIO_USBCTL_GSNPSID_OFFS                                                                     (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c120)
#define HWIO_USBCTL_GSNPSID_RMSK                                                                     0xffffffff
#define HWIO_USBCTL_GSNPSID_POR                                                                      0x5533320a
#define HWIO_USBCTL_GSNPSID_POR_RMSK                                                                 0xffffffff
#define HWIO_USBCTL_GSNPSID_IN          \
        in_dword_masked(HWIO_USBCTL_GSNPSID_ADDR, HWIO_USBCTL_GSNPSID_RMSK)
#define HWIO_USBCTL_GSNPSID_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GSNPSID_ADDR, m)
#define HWIO_USBCTL_GSNPSID_SYNOPSYSID_BMSK                                                          0xffffffff
#define HWIO_USBCTL_GSNPSID_SYNOPSYSID_SHFT                                                                 0x0

#define HWIO_USBCTL_GGPIO_ADDR                                                                       (USBCTL_DWC_USB3_REG_BASE      + 0x0000c124)
#define HWIO_USBCTL_GGPIO_PHYS                                                                       (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c124)
#define HWIO_USBCTL_GGPIO_OFFS                                                                       (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c124)
#define HWIO_USBCTL_GGPIO_RMSK                                                                       0xffffffff
#define HWIO_USBCTL_GGPIO_POR                                                                        0x00000000
#define HWIO_USBCTL_GGPIO_POR_RMSK                                                                   0xffffffff
#define HWIO_USBCTL_GGPIO_IN          \
        in_dword_masked(HWIO_USBCTL_GGPIO_ADDR, HWIO_USBCTL_GGPIO_RMSK)
#define HWIO_USBCTL_GGPIO_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GGPIO_ADDR, m)
#define HWIO_USBCTL_GGPIO_OUT(v)      \
        out_dword(HWIO_USBCTL_GGPIO_ADDR,v)
#define HWIO_USBCTL_GGPIO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GGPIO_ADDR,m,v,HWIO_USBCTL_GGPIO_IN)
#define HWIO_USBCTL_GGPIO_GPO_BMSK                                                                   0xffff0000
#define HWIO_USBCTL_GGPIO_GPO_SHFT                                                                         0x10
#define HWIO_USBCTL_GGPIO_GPI_BMSK                                                                       0xffff
#define HWIO_USBCTL_GGPIO_GPI_SHFT                                                                          0x0

#define HWIO_USBCTL_GUID_ADDR                                                                        (USBCTL_DWC_USB3_REG_BASE      + 0x0000c128)
#define HWIO_USBCTL_GUID_PHYS                                                                        (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c128)
#define HWIO_USBCTL_GUID_OFFS                                                                        (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c128)
#define HWIO_USBCTL_GUID_RMSK                                                                        0xffffffff
#define HWIO_USBCTL_GUID_POR                                                                         0x30012490
#define HWIO_USBCTL_GUID_POR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_GUID_IN          \
        in_dword_masked(HWIO_USBCTL_GUID_ADDR, HWIO_USBCTL_GUID_RMSK)
#define HWIO_USBCTL_GUID_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GUID_ADDR, m)
#define HWIO_USBCTL_GUID_OUT(v)      \
        out_dword(HWIO_USBCTL_GUID_ADDR,v)
#define HWIO_USBCTL_GUID_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GUID_ADDR,m,v,HWIO_USBCTL_GUID_IN)
#define HWIO_USBCTL_GUID_USERID_BMSK                                                                 0xffffffff
#define HWIO_USBCTL_GUID_USERID_SHFT                                                                        0x0

#define HWIO_USBCTL_GUCTL_ADDR                                                                       (USBCTL_DWC_USB3_REG_BASE      + 0x0000c12c)
#define HWIO_USBCTL_GUCTL_PHYS                                                                       (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c12c)
#define HWIO_USBCTL_GUCTL_OFFS                                                                       (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c12c)
#define HWIO_USBCTL_GUCTL_RMSK                                                                       0xffe37fff
#define HWIO_USBCTL_GUCTL_POR                                                                        0x0c804010
#define HWIO_USBCTL_GUCTL_POR_RMSK                                                                   0xffffffff
#define HWIO_USBCTL_GUCTL_IN          \
        in_dword_masked(HWIO_USBCTL_GUCTL_ADDR, HWIO_USBCTL_GUCTL_RMSK)
#define HWIO_USBCTL_GUCTL_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GUCTL_ADDR, m)
#define HWIO_USBCTL_GUCTL_OUT(v)      \
        out_dword(HWIO_USBCTL_GUCTL_ADDR,v)
#define HWIO_USBCTL_GUCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GUCTL_ADDR,m,v,HWIO_USBCTL_GUCTL_IN)
#define HWIO_USBCTL_GUCTL_REFCLKPER_BMSK                                                             0xffc00000
#define HWIO_USBCTL_GUCTL_REFCLKPER_SHFT                                                                   0x16
#define HWIO_USBCTL_GUCTL_NOEXTRDL_BMSK                                                                0x200000
#define HWIO_USBCTL_GUCTL_NOEXTRDL_SHFT                                                                    0x15
#define HWIO_USBCTL_GUCTL_SPRSCTRLTRANSEN_BMSK                                                          0x20000
#define HWIO_USBCTL_GUCTL_SPRSCTRLTRANSEN_SHFT                                                             0x11
#define HWIO_USBCTL_GUCTL_RESBWHSEPS_BMSK                                                               0x10000
#define HWIO_USBCTL_GUCTL_RESBWHSEPS_SHFT                                                                  0x10
#define HWIO_USBCTL_GUCTL_USBHSTINAUTORETRYEN_BMSK                                                       0x4000
#define HWIO_USBCTL_GUCTL_USBHSTINAUTORETRYEN_SHFT                                                          0xe
#define HWIO_USBCTL_GUCTL_ENOVERLAPCHK_BMSK                                                              0x2000
#define HWIO_USBCTL_GUCTL_ENOVERLAPCHK_SHFT                                                                 0xd
#define HWIO_USBCTL_GUCTL_EXTCAPSUPPTEN_BMSK                                                             0x1000
#define HWIO_USBCTL_GUCTL_EXTCAPSUPPTEN_SHFT                                                                0xc
#define HWIO_USBCTL_GUCTL_INSRTEXTRFSBODI_BMSK                                                            0x800
#define HWIO_USBCTL_GUCTL_INSRTEXTRFSBODI_SHFT                                                              0xb
#define HWIO_USBCTL_GUCTL_DTCT_BMSK                                                                       0x600
#define HWIO_USBCTL_GUCTL_DTCT_SHFT                                                                         0x9
#define HWIO_USBCTL_GUCTL_DTFT_BMSK                                                                       0x1ff
#define HWIO_USBCTL_GUCTL_DTFT_SHFT                                                                         0x0

#define HWIO_USBCTL_GBUSERRADDRLO_ADDR                                                               (USBCTL_DWC_USB3_REG_BASE      + 0x0000c130)
#define HWIO_USBCTL_GBUSERRADDRLO_PHYS                                                               (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c130)
#define HWIO_USBCTL_GBUSERRADDRLO_OFFS                                                               (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c130)
#define HWIO_USBCTL_GBUSERRADDRLO_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GBUSERRADDRLO_POR                                                                0x00000000
#define HWIO_USBCTL_GBUSERRADDRLO_POR_RMSK                                                           0xffffffff
#define HWIO_USBCTL_GBUSERRADDRLO_IN          \
        in_dword_masked(HWIO_USBCTL_GBUSERRADDRLO_ADDR, HWIO_USBCTL_GBUSERRADDRLO_RMSK)
#define HWIO_USBCTL_GBUSERRADDRLO_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GBUSERRADDRLO_ADDR, m)
#define HWIO_USBCTL_GBUSERRADDRLO_BUSERRADDR_BMSK                                                    0xffffffff
#define HWIO_USBCTL_GBUSERRADDRLO_BUSERRADDR_SHFT                                                           0x0

#define HWIO_USBCTL_GBUSERRADDRHI_ADDR                                                               (USBCTL_DWC_USB3_REG_BASE      + 0x0000c134)
#define HWIO_USBCTL_GBUSERRADDRHI_PHYS                                                               (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c134)
#define HWIO_USBCTL_GBUSERRADDRHI_OFFS                                                               (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c134)
#define HWIO_USBCTL_GBUSERRADDRHI_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GBUSERRADDRHI_POR                                                                0x00000000
#define HWIO_USBCTL_GBUSERRADDRHI_POR_RMSK                                                           0xffffffff
#define HWIO_USBCTL_GBUSERRADDRHI_IN          \
        in_dword_masked(HWIO_USBCTL_GBUSERRADDRHI_ADDR, HWIO_USBCTL_GBUSERRADDRHI_RMSK)
#define HWIO_USBCTL_GBUSERRADDRHI_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GBUSERRADDRHI_ADDR, m)
#define HWIO_USBCTL_GBUSERRADDRHI_BUSERRADDR_BMSK                                                    0xffffffff
#define HWIO_USBCTL_GBUSERRADDRHI_BUSERRADDR_SHFT                                                           0x0

#define HWIO_USBCTL_GPRTBIMAPLO_ADDR                                                                 (USBCTL_DWC_USB3_REG_BASE      + 0x0000c138)
#define HWIO_USBCTL_GPRTBIMAPLO_PHYS                                                                 (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c138)
#define HWIO_USBCTL_GPRTBIMAPLO_OFFS                                                                 (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c138)
#define HWIO_USBCTL_GPRTBIMAPLO_RMSK                                                                 0xffffffff
#define HWIO_USBCTL_GPRTBIMAPLO_POR                                                                  0x00000000
#define HWIO_USBCTL_GPRTBIMAPLO_POR_RMSK                                                             0xffffffff
#define HWIO_USBCTL_GPRTBIMAPLO_IN          \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAPLO_ADDR, HWIO_USBCTL_GPRTBIMAPLO_RMSK)
#define HWIO_USBCTL_GPRTBIMAPLO_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAPLO_ADDR, m)
#define HWIO_USBCTL_GPRTBIMAPLO_OUT(v)      \
        out_dword(HWIO_USBCTL_GPRTBIMAPLO_ADDR,v)
#define HWIO_USBCTL_GPRTBIMAPLO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPRTBIMAPLO_ADDR,m,v,HWIO_USBCTL_GPRTBIMAPLO_IN)
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM8_BMSK                                                          0xf0000000
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM8_SHFT                                                                0x1c
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM7_BMSK                                                           0xf000000
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM7_SHFT                                                                0x18
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM6_BMSK                                                            0xf00000
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM6_SHFT                                                                0x14
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM5_BMSK                                                             0xf0000
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM5_SHFT                                                                0x10
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM4_BMSK                                                              0xf000
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM4_SHFT                                                                 0xc
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM3_BMSK                                                               0xf00
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM3_SHFT                                                                 0x8
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM2_BMSK                                                                0xf0
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM2_SHFT                                                                 0x4
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM1_BMSK                                                                 0xf
#define HWIO_USBCTL_GPRTBIMAPLO_BINUM1_SHFT                                                                 0x0

#define HWIO_USBCTL_GPRTBIMAPHI_ADDR                                                                 (USBCTL_DWC_USB3_REG_BASE      + 0x0000c13c)
#define HWIO_USBCTL_GPRTBIMAPHI_PHYS                                                                 (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c13c)
#define HWIO_USBCTL_GPRTBIMAPHI_OFFS                                                                 (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c13c)
#define HWIO_USBCTL_GPRTBIMAPHI_RMSK                                                                  0xfffffff
#define HWIO_USBCTL_GPRTBIMAPHI_POR                                                                  0x00000000
#define HWIO_USBCTL_GPRTBIMAPHI_POR_RMSK                                                             0xffffffff
#define HWIO_USBCTL_GPRTBIMAPHI_IN          \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAPHI_ADDR, HWIO_USBCTL_GPRTBIMAPHI_RMSK)
#define HWIO_USBCTL_GPRTBIMAPHI_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAPHI_ADDR, m)
#define HWIO_USBCTL_GPRTBIMAPHI_OUT(v)      \
        out_dword(HWIO_USBCTL_GPRTBIMAPHI_ADDR,v)
#define HWIO_USBCTL_GPRTBIMAPHI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPRTBIMAPHI_ADDR,m,v,HWIO_USBCTL_GPRTBIMAPHI_IN)
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM15_BMSK                                                          0xf000000
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM15_SHFT                                                               0x18
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM14_BMSK                                                           0xf00000
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM14_SHFT                                                               0x14
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM13_BMSK                                                            0xf0000
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM13_SHFT                                                               0x10
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM12_BMSK                                                             0xf000
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM12_SHFT                                                                0xc
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM11_BMSK                                                              0xf00
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM11_SHFT                                                                0x8
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM10_BMSK                                                               0xf0
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM10_SHFT                                                                0x4
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM9_BMSK                                                                 0xf
#define HWIO_USBCTL_GPRTBIMAPHI_BINUM9_SHFT                                                                 0x0

#define HWIO_USBCTL_GHWPARAMS0_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c140)
#define HWIO_USBCTL_GHWPARAMS0_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c140)
#define HWIO_USBCTL_GHWPARAMS0_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c140)
#define HWIO_USBCTL_GHWPARAMS0_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS0_POR                                                                   0x20202000
#define HWIO_USBCTL_GHWPARAMS0_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS0_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS0_ADDR, HWIO_USBCTL_GHWPARAMS0_RMSK)
#define HWIO_USBCTL_GHWPARAMS0_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS0_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_31_24_BMSK                                                 0xff000000
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_31_24_SHFT                                                       0x18
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_23_16_BMSK                                                   0xff0000
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_23_16_SHFT                                                       0x10
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_15_8_BMSK                                                      0xff00
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_15_8_SHFT                                                         0x8
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_7_6_BMSK                                                         0xc0
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_7_6_SHFT                                                          0x6
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_5_3_BMSK                                                         0x38
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_5_3_SHFT                                                          0x3
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_2_0_BMSK                                                          0x7
#define HWIO_USBCTL_GHWPARAMS0_GHWPARAMS0_2_0_SHFT                                                          0x0

#define HWIO_USBCTL_GHWPARAMS1_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c144)
#define HWIO_USBCTL_GHWPARAMS1_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c144)
#define HWIO_USBCTL_GHWPARAMS1_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c144)
#define HWIO_USBCTL_GHWPARAMS1_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS1_POR                                                                   0x01a0c93b
#define HWIO_USBCTL_GHWPARAMS1_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS1_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS1_ADDR, HWIO_USBCTL_GHWPARAMS1_RMSK)
#define HWIO_USBCTL_GHWPARAMS1_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS1_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_31_BMSK                                                    0x80000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_31_SHFT                                                          0x1f
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_30_BMSK                                                    0x40000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_30_SHFT                                                          0x1e
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_29_BMSK                                                    0x20000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_29_SHFT                                                          0x1d
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_28_BMSK                                                    0x10000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_28_SHFT                                                          0x1c
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_27_BMSK                                                     0x8000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_27_SHFT                                                          0x1b
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_26_BMSK                                                     0x4000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_26_SHFT                                                          0x1a
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_25_24_BMSK                                                  0x3000000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_25_24_SHFT                                                       0x18
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_23_BMSK                                                      0x800000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_23_SHFT                                                          0x17
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_22_21_BMSK                                                   0x600000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_22_21_SHFT                                                       0x15
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_20_15_BMSK                                                   0x1f8000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_20_15_SHFT                                                        0xf
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_14_12_BMSK                                                     0x7000
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_14_12_SHFT                                                        0xc
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_11_9_BMSK                                                       0xe00
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_11_9_SHFT                                                         0x9
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_8_6_BMSK                                                        0x1c0
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_8_6_SHFT                                                          0x6
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_5_3_BMSK                                                         0x38
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_5_3_SHFT                                                          0x3
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_2_0_BMSK                                                          0x7
#define HWIO_USBCTL_GHWPARAMS1_GHWPARAMS1_2_0_SHFT                                                          0x0

#define HWIO_USBCTL_GHWPARAMS2_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c148)
#define HWIO_USBCTL_GHWPARAMS2_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c148)
#define HWIO_USBCTL_GHWPARAMS2_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c148)
#define HWIO_USBCTL_GHWPARAMS2_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS2_POR                                                                   0x30012490
#define HWIO_USBCTL_GHWPARAMS2_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS2_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS2_ADDR, HWIO_USBCTL_GHWPARAMS2_RMSK)
#define HWIO_USBCTL_GHWPARAMS2_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS2_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS2_GHWPARAMS2_31_0_BMSK                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS2_GHWPARAMS2_31_0_SHFT                                                         0x0

#define HWIO_USBCTL_GHWPARAMS3_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c14c)
#define HWIO_USBCTL_GHWPARAMS3_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c14c)
#define HWIO_USBCTL_GHWPARAMS3_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c14c)
#define HWIO_USBCTL_GHWPARAMS3_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS3_POR                                                                   0x06a4d08c
#define HWIO_USBCTL_GHWPARAMS3_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS3_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS3_ADDR, HWIO_USBCTL_GHWPARAMS3_RMSK)
#define HWIO_USBCTL_GHWPARAMS3_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS3_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_31_BMSK                                                    0x80000000
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_31_SHFT                                                          0x1f
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_30_23_BMSK                                                 0x7f800000
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_30_23_SHFT                                                       0x17
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_22_18_BMSK                                                   0x7c0000
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_22_18_SHFT                                                       0x12
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_17_12_BMSK                                                    0x3f000
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_17_12_SHFT                                                        0xc
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_11_BMSK                                                         0x800
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_11_SHFT                                                           0xb
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_10_BMSK                                                         0x400
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_10_SHFT                                                           0xa
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_9_8_BMSK                                                        0x300
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_9_8_SHFT                                                          0x8
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_7_6_BMSK                                                         0xc0
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_7_6_SHFT                                                          0x6
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_5_4_BMSK                                                         0x30
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_5_4_SHFT                                                          0x4
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_3_2_BMSK                                                          0xc
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_3_2_SHFT                                                          0x2
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_1_0_BMSK                                                          0x3
#define HWIO_USBCTL_GHWPARAMS3_GHWPARAMS3_1_0_SHFT                                                          0x0

#define HWIO_USBCTL_GHWPARAMS4_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c150)
#define HWIO_USBCTL_GHWPARAMS4_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c150)
#define HWIO_USBCTL_GHWPARAMS4_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c150)
#define HWIO_USBCTL_GHWPARAMS4_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS4_POR                                                                   0x47822004
#define HWIO_USBCTL_GHWPARAMS4_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS4_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS4_ADDR, HWIO_USBCTL_GHWPARAMS4_RMSK)
#define HWIO_USBCTL_GHWPARAMS4_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS4_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_31_28_BMSK                                                 0xf0000000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_31_28_SHFT                                                       0x1c
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_27_24_BMSK                                                  0xf000000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_27_24_SHFT                                                       0x18
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_23_BMSK                                                      0x800000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_23_SHFT                                                          0x17
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_22_BMSK                                                      0x400000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_22_SHFT                                                          0x16
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_21_BMSK                                                      0x200000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_21_SHFT                                                          0x15
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_20_17_BMSK                                                   0x1e0000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_20_17_SHFT                                                       0x11
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_16_13_BMSK                                                    0x1e000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_16_13_SHFT                                                        0xd
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_12_BMSK                                                        0x1000
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_12_SHFT                                                           0xc
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_11_BMSK                                                         0x800
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_11_SHFT                                                           0xb
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_10_9_BMSK                                                       0x600
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_10_9_SHFT                                                         0x9
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_8_7_BMSK                                                        0x180
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_8_7_SHFT                                                          0x7
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_6_BMSK                                                           0x40
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_6_SHFT                                                            0x6
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_5_0_BMSK                                                         0x3f
#define HWIO_USBCTL_GHWPARAMS4_GHWPARAMS4_5_0_SHFT                                                          0x0

#define HWIO_USBCTL_GHWPARAMS5_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c154)
#define HWIO_USBCTL_GHWPARAMS5_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c154)
#define HWIO_USBCTL_GHWPARAMS5_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c154)
#define HWIO_USBCTL_GHWPARAMS5_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS5_POR                                                                   0x04204108
#define HWIO_USBCTL_GHWPARAMS5_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS5_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS5_ADDR, HWIO_USBCTL_GHWPARAMS5_RMSK)
#define HWIO_USBCTL_GHWPARAMS5_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS5_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_31_28_BMSK                                                 0xf0000000
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_31_28_SHFT                                                       0x1c
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_27_22_BMSK                                                  0xfc00000
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_27_22_SHFT                                                       0x16
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_21_16_BMSK                                                   0x3f0000
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_21_16_SHFT                                                       0x10
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_15_10_BMSK                                                     0xfc00
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_15_10_SHFT                                                        0xa
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_9_4_BMSK                                                        0x3f0
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_9_4_SHFT                                                          0x4
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_3_0_BMSK                                                          0xf
#define HWIO_USBCTL_GHWPARAMS5_GHWPARAMS5_3_0_SHFT                                                          0x0

#define HWIO_USBCTL_GHWPARAMS6_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c158)
#define HWIO_USBCTL_GHWPARAMS6_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c158)
#define HWIO_USBCTL_GHWPARAMS6_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c158)
#define HWIO_USBCTL_GHWPARAMS6_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS6_POR                                                                   0x0cff8020
#define HWIO_USBCTL_GHWPARAMS6_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS6_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS6_ADDR, HWIO_USBCTL_GHWPARAMS6_RMSK)
#define HWIO_USBCTL_GHWPARAMS6_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS6_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_31_16_BMSK                                                 0xffff0000
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_31_16_SHFT                                                       0x10
#define HWIO_USBCTL_GHWPARAMS6_BUSFLTRSSUPPORT_BMSK                                                      0x8000
#define HWIO_USBCTL_GHWPARAMS6_BUSFLTRSSUPPORT_SHFT                                                         0xf
#define HWIO_USBCTL_GHWPARAMS6_BCSUPPORT_BMSK                                                            0x4000
#define HWIO_USBCTL_GHWPARAMS6_BCSUPPORT_SHFT                                                               0xe
#define HWIO_USBCTL_GHWPARAMS6_OTG_SS_SUPPORT_BMSK                                                       0x2000
#define HWIO_USBCTL_GHWPARAMS6_OTG_SS_SUPPORT_SHFT                                                          0xd
#define HWIO_USBCTL_GHWPARAMS6_ADPSUPPORT_BMSK                                                           0x1000
#define HWIO_USBCTL_GHWPARAMS6_ADPSUPPORT_SHFT                                                              0xc
#define HWIO_USBCTL_GHWPARAMS6_HNPSUPPORT_BMSK                                                            0x800
#define HWIO_USBCTL_GHWPARAMS6_HNPSUPPORT_SHFT                                                              0xb
#define HWIO_USBCTL_GHWPARAMS6_SRPSUPPORT_BMSK                                                            0x400
#define HWIO_USBCTL_GHWPARAMS6_SRPSUPPORT_SHFT                                                              0xa
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_9_8_BMSK                                                        0x300
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_9_8_SHFT                                                          0x8
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_7_BMSK                                                           0x80
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_7_SHFT                                                            0x7
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_6_BMSK                                                           0x40
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_6_SHFT                                                            0x6
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_5_0_BMSK                                                         0x3f
#define HWIO_USBCTL_GHWPARAMS6_GHWPARAMS6_5_0_SHFT                                                          0x0

#define HWIO_USBCTL_GHWPARAMS7_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c15c)
#define HWIO_USBCTL_GHWPARAMS7_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c15c)
#define HWIO_USBCTL_GHWPARAMS7_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c15c)
#define HWIO_USBCTL_GHWPARAMS7_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS7_POR                                                                   0x00000000
#define HWIO_USBCTL_GHWPARAMS7_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS7_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS7_ADDR, HWIO_USBCTL_GHWPARAMS7_RMSK)
#define HWIO_USBCTL_GHWPARAMS7_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS7_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS7_GHWPARAMS7_31_16_BMSK                                                 0xffff0000
#define HWIO_USBCTL_GHWPARAMS7_GHWPARAMS7_31_16_SHFT                                                       0x10
#define HWIO_USBCTL_GHWPARAMS7_GHWPARAMS7_15_0_BMSK                                                      0xffff
#define HWIO_USBCTL_GHWPARAMS7_GHWPARAMS7_15_0_SHFT                                                         0x0

#define HWIO_USBCTL_GDBGFIFOSPACE_ADDR                                                               (USBCTL_DWC_USB3_REG_BASE      + 0x0000c160)
#define HWIO_USBCTL_GDBGFIFOSPACE_PHYS                                                               (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c160)
#define HWIO_USBCTL_GDBGFIFOSPACE_OFFS                                                               (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c160)
#define HWIO_USBCTL_GDBGFIFOSPACE_RMSK                                                               0xffff01ff
#define HWIO_USBCTL_GDBGFIFOSPACE_POR                                                                0x00420000
#define HWIO_USBCTL_GDBGFIFOSPACE_POR_RMSK                                                           0xffffffff
#define HWIO_USBCTL_GDBGFIFOSPACE_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGFIFOSPACE_ADDR, HWIO_USBCTL_GDBGFIFOSPACE_RMSK)
#define HWIO_USBCTL_GDBGFIFOSPACE_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGFIFOSPACE_ADDR, m)
#define HWIO_USBCTL_GDBGFIFOSPACE_OUT(v)      \
        out_dword(HWIO_USBCTL_GDBGFIFOSPACE_ADDR,v)
#define HWIO_USBCTL_GDBGFIFOSPACE_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GDBGFIFOSPACE_ADDR,m,v,HWIO_USBCTL_GDBGFIFOSPACE_IN)
#define HWIO_USBCTL_GDBGFIFOSPACE_SPACE_AVAILABLE_BMSK                                               0xffff0000
#define HWIO_USBCTL_GDBGFIFOSPACE_SPACE_AVAILABLE_SHFT                                                     0x10
#define HWIO_USBCTL_GDBGFIFOSPACE_FIFO_QUEUE_SELECT_BMSK                                                  0x1ff
#define HWIO_USBCTL_GDBGFIFOSPACE_FIFO_QUEUE_SELECT_SHFT                                                    0x0

#define HWIO_USBCTL_GDBGLTSSM_ADDR                                                                   (USBCTL_DWC_USB3_REG_BASE      + 0x0000c164)
#define HWIO_USBCTL_GDBGLTSSM_PHYS                                                                   (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c164)
#define HWIO_USBCTL_GDBGLTSSM_OFFS                                                                   (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c164)
#define HWIO_USBCTL_GDBGLTSSM_RMSK                                                                   0x7fffffff
#define HWIO_USBCTL_GDBGLTSSM_POR                                                                    0x41010440
#define HWIO_USBCTL_GDBGLTSSM_POR_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GDBGLTSSM_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGLTSSM_ADDR, HWIO_USBCTL_GDBGLTSSM_RMSK)
#define HWIO_USBCTL_GDBGLTSSM_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGLTSSM_ADDR, m)
#define HWIO_USBCTL_GDBGLTSSM_RXELECIDLE_BMSK                                                        0x40000000
#define HWIO_USBCTL_GDBGLTSSM_RXELECIDLE_SHFT                                                              0x1e
#define HWIO_USBCTL_GDBGLTSSM_X3_XS_SWAPPING_BMSK                                                    0x20000000
#define HWIO_USBCTL_GDBGLTSSM_X3_XS_SWAPPING_SHFT                                                          0x1d
#define HWIO_USBCTL_GDBGLTSSM_X3_DS_HOST_SHUTDOWN_BMSK                                               0x10000000
#define HWIO_USBCTL_GDBGLTSSM_X3_DS_HOST_SHUTDOWN_SHFT                                                     0x1c
#define HWIO_USBCTL_GDBGLTSSM_PRTDIRECTION_BMSK                                                       0x8000000
#define HWIO_USBCTL_GDBGLTSSM_PRTDIRECTION_SHFT                                                            0x1b
#define HWIO_USBCTL_GDBGLTSSM_LTDBTIMEOUT_BMSK                                                        0x4000000
#define HWIO_USBCTL_GDBGLTSSM_LTDBTIMEOUT_SHFT                                                             0x1a
#define HWIO_USBCTL_GDBGLTSSM_LTDBLINKSTATE_BMSK                                                      0x3c00000
#define HWIO_USBCTL_GDBGLTSSM_LTDBLINKSTATE_SHFT                                                           0x16
#define HWIO_USBCTL_GDBGLTSSM_LTDBSUBSTATE_BMSK                                                        0x3c0000
#define HWIO_USBCTL_GDBGLTSSM_LTDBSUBSTATE_SHFT                                                            0x12
#define HWIO_USBCTL_GDBGLTSSM_ELASTICBUFFERMODE_BMSK                                                    0x20000
#define HWIO_USBCTL_GDBGLTSSM_ELASTICBUFFERMODE_SHFT                                                       0x11
#define HWIO_USBCTL_GDBGLTSSM_TXELECLDLE_BMSK                                                           0x10000
#define HWIO_USBCTL_GDBGLTSSM_TXELECLDLE_SHFT                                                              0x10
#define HWIO_USBCTL_GDBGLTSSM_RXPOLARITY_BMSK                                                            0x8000
#define HWIO_USBCTL_GDBGLTSSM_RXPOLARITY_SHFT                                                               0xf
#define HWIO_USBCTL_GDBGLTSSM_TXDETRXLOOPBACK_BMSK                                                       0x4000
#define HWIO_USBCTL_GDBGLTSSM_TXDETRXLOOPBACK_SHFT                                                          0xe
#define HWIO_USBCTL_GDBGLTSSM_LTDBPHYCMDSTATE_BMSK                                                       0x3800
#define HWIO_USBCTL_GDBGLTSSM_LTDBPHYCMDSTATE_SHFT                                                          0xb
#define HWIO_USBCTL_GDBGLTSSM_POWERDOWN_BMSK                                                              0x600
#define HWIO_USBCTL_GDBGLTSSM_POWERDOWN_SHFT                                                                0x9
#define HWIO_USBCTL_GDBGLTSSM_RXEQTRAIN_BMSK                                                              0x100
#define HWIO_USBCTL_GDBGLTSSM_RXEQTRAIN_SHFT                                                                0x8
#define HWIO_USBCTL_GDBGLTSSM_TXDEEMPHASIS_BMSK                                                            0xc0
#define HWIO_USBCTL_GDBGLTSSM_TXDEEMPHASIS_SHFT                                                             0x6
#define HWIO_USBCTL_GDBGLTSSM_LTDBCLKSTATE_BMSK                                                            0x38
#define HWIO_USBCTL_GDBGLTSSM_LTDBCLKSTATE_SHFT                                                             0x3
#define HWIO_USBCTL_GDBGLTSSM_TXSWING_BMSK                                                                  0x4
#define HWIO_USBCTL_GDBGLTSSM_TXSWING_SHFT                                                                  0x2
#define HWIO_USBCTL_GDBGLTSSM_RXTERMINATION_BMSK                                                            0x2
#define HWIO_USBCTL_GDBGLTSSM_RXTERMINATION_SHFT                                                            0x1
#define HWIO_USBCTL_GDBGLTSSM_TXONESZEROS_BMSK                                                              0x1
#define HWIO_USBCTL_GDBGLTSSM_TXONESZEROS_SHFT                                                              0x0

#define HWIO_USBCTL_GDBGLNMCC_ADDR                                                                   (USBCTL_DWC_USB3_REG_BASE      + 0x0000c168)
#define HWIO_USBCTL_GDBGLNMCC_PHYS                                                                   (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c168)
#define HWIO_USBCTL_GDBGLNMCC_OFFS                                                                   (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c168)
#define HWIO_USBCTL_GDBGLNMCC_RMSK                                                                        0x1ff
#define HWIO_USBCTL_GDBGLNMCC_POR                                                                    0x00000000
#define HWIO_USBCTL_GDBGLNMCC_POR_RMSK                                                               0xffffffff
#define HWIO_USBCTL_GDBGLNMCC_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGLNMCC_ADDR, HWIO_USBCTL_GDBGLNMCC_RMSK)
#define HWIO_USBCTL_GDBGLNMCC_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGLNMCC_ADDR, m)
#define HWIO_USBCTL_GDBGLNMCC_LNMCC_BERC_BMSK                                                             0x1ff
#define HWIO_USBCTL_GDBGLNMCC_LNMCC_BERC_SHFT                                                               0x0

#define HWIO_USBCTL_GDBGBMU_ADDR                                                                     (USBCTL_DWC_USB3_REG_BASE      + 0x0000c16c)
#define HWIO_USBCTL_GDBGBMU_PHYS                                                                     (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c16c)
#define HWIO_USBCTL_GDBGBMU_OFFS                                                                     (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c16c)
#define HWIO_USBCTL_GDBGBMU_RMSK                                                                     0xffffffff
#define HWIO_USBCTL_GDBGBMU_POR                                                                      0x00000000
#define HWIO_USBCTL_GDBGBMU_POR_RMSK                                                                 0xffffffff
#define HWIO_USBCTL_GDBGBMU_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGBMU_ADDR, HWIO_USBCTL_GDBGBMU_RMSK)
#define HWIO_USBCTL_GDBGBMU_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGBMU_ADDR, m)
#define HWIO_USBCTL_GDBGBMU_BMU_BCU_BMSK                                                             0xffffff00
#define HWIO_USBCTL_GDBGBMU_BMU_BCU_SHFT                                                                    0x8
#define HWIO_USBCTL_GDBGBMU_BMU_DCU_BMSK                                                                   0xf0
#define HWIO_USBCTL_GDBGBMU_BMU_DCU_SHFT                                                                    0x4
#define HWIO_USBCTL_GDBGBMU_BMU_CCU_BMSK                                                                    0xf
#define HWIO_USBCTL_GDBGBMU_BMU_CCU_SHFT                                                                    0x0

#define HWIO_USBCTL_GDBGLSPMUX_HST_ADDR                                                              (USBCTL_DWC_USB3_REG_BASE      + 0x0000c170)
#define HWIO_USBCTL_GDBGLSPMUX_HST_PHYS                                                              (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c170)
#define HWIO_USBCTL_GDBGLSPMUX_HST_OFFS                                                              (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c170)
#define HWIO_USBCTL_GDBGLSPMUX_HST_RMSK                                                                0xff3fff
#define HWIO_USBCTL_GDBGLSPMUX_HST_POR                                                               0x003f0000
#define HWIO_USBCTL_GDBGLSPMUX_HST_POR_RMSK                                                          0xffffffff
#define HWIO_USBCTL_GDBGLSPMUX_HST_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGLSPMUX_HST_ADDR, HWIO_USBCTL_GDBGLSPMUX_HST_RMSK)
#define HWIO_USBCTL_GDBGLSPMUX_HST_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGLSPMUX_HST_ADDR, m)
#define HWIO_USBCTL_GDBGLSPMUX_HST_OUT(v)      \
        out_dword(HWIO_USBCTL_GDBGLSPMUX_HST_ADDR,v)
#define HWIO_USBCTL_GDBGLSPMUX_HST_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GDBGLSPMUX_HST_ADDR,m,v,HWIO_USBCTL_GDBGLSPMUX_HST_IN)
#define HWIO_USBCTL_GDBGLSPMUX_HST_LOGIC_ANALYZER_TRACE_BMSK                                           0xff0000
#define HWIO_USBCTL_GDBGLSPMUX_HST_LOGIC_ANALYZER_TRACE_SHFT                                               0x10
#define HWIO_USBCTL_GDBGLSPMUX_HST_HOSTSELECT_BMSK                                                       0x3fff
#define HWIO_USBCTL_GDBGLSPMUX_HST_HOSTSELECT_SHFT                                                          0x0

#define HWIO_USBCTL_GDBGLSP_ADDR                                                                     (USBCTL_DWC_USB3_REG_BASE      + 0x0000c174)
#define HWIO_USBCTL_GDBGLSP_PHYS                                                                     (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c174)
#define HWIO_USBCTL_GDBGLSP_OFFS                                                                     (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c174)
#define HWIO_USBCTL_GDBGLSP_RMSK                                                                     0xffffffff
#define HWIO_USBCTL_GDBGLSP_POR                                                                      0x00000000
#define HWIO_USBCTL_GDBGLSP_POR_RMSK                                                                 0xffffffff
#define HWIO_USBCTL_GDBGLSP_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGLSP_ADDR, HWIO_USBCTL_GDBGLSP_RMSK)
#define HWIO_USBCTL_GDBGLSP_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGLSP_ADDR, m)
#define HWIO_USBCTL_GDBGLSP_LSPDEBUG_BMSK                                                            0xffffffff
#define HWIO_USBCTL_GDBGLSP_LSPDEBUG_SHFT                                                                   0x0

#define HWIO_USBCTL_GDBGEPINFO0_ADDR                                                                 (USBCTL_DWC_USB3_REG_BASE      + 0x0000c178)
#define HWIO_USBCTL_GDBGEPINFO0_PHYS                                                                 (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c178)
#define HWIO_USBCTL_GDBGEPINFO0_OFFS                                                                 (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c178)
#define HWIO_USBCTL_GDBGEPINFO0_RMSK                                                                 0xffffffff
#define HWIO_USBCTL_GDBGEPINFO0_POR                                                                  0x00000000
#define HWIO_USBCTL_GDBGEPINFO0_POR_RMSK                                                             0xffffffff
#define HWIO_USBCTL_GDBGEPINFO0_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGEPINFO0_ADDR, HWIO_USBCTL_GDBGEPINFO0_RMSK)
#define HWIO_USBCTL_GDBGEPINFO0_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGEPINFO0_ADDR, m)
#define HWIO_USBCTL_GDBGEPINFO0_EPDEBUG_BMSK                                                         0xffffffff
#define HWIO_USBCTL_GDBGEPINFO0_EPDEBUG_SHFT                                                                0x0

#define HWIO_USBCTL_GDBGEPINFO1_ADDR                                                                 (USBCTL_DWC_USB3_REG_BASE      + 0x0000c17c)
#define HWIO_USBCTL_GDBGEPINFO1_PHYS                                                                 (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c17c)
#define HWIO_USBCTL_GDBGEPINFO1_OFFS                                                                 (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c17c)
#define HWIO_USBCTL_GDBGEPINFO1_RMSK                                                                 0xffffffff
#define HWIO_USBCTL_GDBGEPINFO1_POR                                                                  0x00800000
#define HWIO_USBCTL_GDBGEPINFO1_POR_RMSK                                                             0xffffffff
#define HWIO_USBCTL_GDBGEPINFO1_IN          \
        in_dword_masked(HWIO_USBCTL_GDBGEPINFO1_ADDR, HWIO_USBCTL_GDBGEPINFO1_RMSK)
#define HWIO_USBCTL_GDBGEPINFO1_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GDBGEPINFO1_ADDR, m)
#define HWIO_USBCTL_GDBGEPINFO1_EPDEBUG_BMSK                                                         0xffffffff
#define HWIO_USBCTL_GDBGEPINFO1_EPDEBUG_SHFT                                                                0x0

#define HWIO_USBCTL_GPRTBIMAP_HSLO_ADDR                                                              (USBCTL_DWC_USB3_REG_BASE      + 0x0000c180)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_PHYS                                                              (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c180)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_OFFS                                                              (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c180)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GPRTBIMAP_HSLO_POR                                                               0x00000000
#define HWIO_USBCTL_GPRTBIMAP_HSLO_POR_RMSK                                                          0xffffffff
#define HWIO_USBCTL_GPRTBIMAP_HSLO_IN          \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_HSLO_ADDR, HWIO_USBCTL_GPRTBIMAP_HSLO_RMSK)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_HSLO_ADDR, m)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_OUT(v)      \
        out_dword(HWIO_USBCTL_GPRTBIMAP_HSLO_ADDR,v)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPRTBIMAP_HSLO_ADDR,m,v,HWIO_USBCTL_GPRTBIMAP_HSLO_IN)
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM8_BMSK                                                       0xf0000000
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM8_SHFT                                                             0x1c
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM7_BMSK                                                        0xf000000
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM7_SHFT                                                             0x18
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM6_BMSK                                                         0xf00000
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM6_SHFT                                                             0x14
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM5_BMSK                                                          0xf0000
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM5_SHFT                                                             0x10
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM4_BMSK                                                           0xf000
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM4_SHFT                                                              0xc
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM3_BMSK                                                            0xf00
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM3_SHFT                                                              0x8
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM2_BMSK                                                             0xf0
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM2_SHFT                                                              0x4
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM1_BMSK                                                              0xf
#define HWIO_USBCTL_GPRTBIMAP_HSLO_BINUM1_SHFT                                                              0x0

#define HWIO_USBCTL_GPRTBIMAP_HSHI_ADDR                                                              (USBCTL_DWC_USB3_REG_BASE      + 0x0000c184)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_PHYS                                                              (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c184)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_OFFS                                                              (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c184)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_RMSK                                                               0xfffffff
#define HWIO_USBCTL_GPRTBIMAP_HSHI_POR                                                               0x00000000
#define HWIO_USBCTL_GPRTBIMAP_HSHI_POR_RMSK                                                          0xffffffff
#define HWIO_USBCTL_GPRTBIMAP_HSHI_IN          \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_HSHI_ADDR, HWIO_USBCTL_GPRTBIMAP_HSHI_RMSK)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_HSHI_ADDR, m)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_OUT(v)      \
        out_dword(HWIO_USBCTL_GPRTBIMAP_HSHI_ADDR,v)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPRTBIMAP_HSHI_ADDR,m,v,HWIO_USBCTL_GPRTBIMAP_HSHI_IN)
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM15_BMSK                                                       0xf000000
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM15_SHFT                                                            0x18
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM14_BMSK                                                        0xf00000
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM14_SHFT                                                            0x14
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM13_BMSK                                                         0xf0000
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM13_SHFT                                                            0x10
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM12_BMSK                                                          0xf000
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM12_SHFT                                                             0xc
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM11_BMSK                                                           0xf00
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM11_SHFT                                                             0x8
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM10_BMSK                                                            0xf0
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM10_SHFT                                                             0x4
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM9_BMSK                                                              0xf
#define HWIO_USBCTL_GPRTBIMAP_HSHI_BINUM9_SHFT                                                              0x0

#define HWIO_USBCTL_GPRTBIMAP_FSLO_ADDR                                                              (USBCTL_DWC_USB3_REG_BASE      + 0x0000c188)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_PHYS                                                              (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c188)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_OFFS                                                              (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c188)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GPRTBIMAP_FSLO_POR                                                               0x00000000
#define HWIO_USBCTL_GPRTBIMAP_FSLO_POR_RMSK                                                          0xffffffff
#define HWIO_USBCTL_GPRTBIMAP_FSLO_IN          \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_FSLO_ADDR, HWIO_USBCTL_GPRTBIMAP_FSLO_RMSK)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_FSLO_ADDR, m)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_OUT(v)      \
        out_dword(HWIO_USBCTL_GPRTBIMAP_FSLO_ADDR,v)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPRTBIMAP_FSLO_ADDR,m,v,HWIO_USBCTL_GPRTBIMAP_FSLO_IN)
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM8_BMSK                                                       0xf0000000
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM8_SHFT                                                             0x1c
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM7_BMSK                                                        0xf000000
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM7_SHFT                                                             0x18
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM6_BMSK                                                         0xf00000
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM6_SHFT                                                             0x14
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM5_BMSK                                                          0xf0000
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM5_SHFT                                                             0x10
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM4_BMSK                                                           0xf000
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM4_SHFT                                                              0xc
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM3_BMSK                                                            0xf00
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM3_SHFT                                                              0x8
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM2_BMSK                                                             0xf0
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM2_SHFT                                                              0x4
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM1_BMSK                                                              0xf
#define HWIO_USBCTL_GPRTBIMAP_FSLO_BINUM1_SHFT                                                              0x0

#define HWIO_USBCTL_GPRTBIMAP_FSHI_ADDR                                                              (USBCTL_DWC_USB3_REG_BASE      + 0x0000c18c)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_PHYS                                                              (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c18c)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_OFFS                                                              (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c18c)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_RMSK                                                               0xfffffff
#define HWIO_USBCTL_GPRTBIMAP_FSHI_POR                                                               0x00000000
#define HWIO_USBCTL_GPRTBIMAP_FSHI_POR_RMSK                                                          0xffffffff
#define HWIO_USBCTL_GPRTBIMAP_FSHI_IN          \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_FSHI_ADDR, HWIO_USBCTL_GPRTBIMAP_FSHI_RMSK)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GPRTBIMAP_FSHI_ADDR, m)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_OUT(v)      \
        out_dword(HWIO_USBCTL_GPRTBIMAP_FSHI_ADDR,v)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GPRTBIMAP_FSHI_ADDR,m,v,HWIO_USBCTL_GPRTBIMAP_FSHI_IN)
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM15_BMSK                                                       0xf000000
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM15_SHFT                                                            0x18
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM14_BMSK                                                        0xf00000
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM14_SHFT                                                            0x14
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM13_BMSK                                                         0xf0000
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM13_SHFT                                                            0x10
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM12_BMSK                                                          0xf000
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM12_SHFT                                                             0xc
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM11_BMSK                                                           0xf00
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM11_SHFT                                                             0x8
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM10_BMSK                                                            0xf0
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM10_SHFT                                                             0x4
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM9_BMSK                                                              0xf
#define HWIO_USBCTL_GPRTBIMAP_FSHI_BINUM9_SHFT                                                              0x0

#define HWIO_USBCTL_GUCTL2_ADDR                                                                      (USBCTL_DWC_USB3_REG_BASE      + 0x0000c19c)
#define HWIO_USBCTL_GUCTL2_PHYS                                                                      (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c19c)
#define HWIO_USBCTL_GUCTL2_OFFS                                                                      (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c19c)
#define HWIO_USBCTL_GUCTL2_RMSK                                                                       0x3ffdfff
#define HWIO_USBCTL_GUCTL2_POR                                                                       0x0000040d
#define HWIO_USBCTL_GUCTL2_POR_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GUCTL2_IN          \
        in_dword_masked(HWIO_USBCTL_GUCTL2_ADDR, HWIO_USBCTL_GUCTL2_RMSK)
#define HWIO_USBCTL_GUCTL2_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GUCTL2_ADDR, m)
#define HWIO_USBCTL_GUCTL2_OUT(v)      \
        out_dword(HWIO_USBCTL_GUCTL2_ADDR,v)
#define HWIO_USBCTL_GUCTL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GUCTL2_ADDR,m,v,HWIO_USBCTL_GUCTL2_IN)
#define HWIO_USBCTL_GUCTL2_EN_HP_PM_TIMER_BMSK                                                        0x3f80000
#define HWIO_USBCTL_GUCTL2_EN_HP_PM_TIMER_SHFT                                                             0x13
#define HWIO_USBCTL_GUCTL2_NOLOWPWRDUR_BMSK                                                             0x78000
#define HWIO_USBCTL_GUCTL2_NOLOWPWRDUR_SHFT                                                                 0xf
#define HWIO_USBCTL_GUCTL2_RST_ACTBITLATER_BMSK                                                          0x4000
#define HWIO_USBCTL_GUCTL2_RST_ACTBITLATER_SHFT                                                             0xe
#define HWIO_USBCTL_GUCTL2_ENABLEEPCACHEEVICT_BMSK                                                       0x1000
#define HWIO_USBCTL_GUCTL2_ENABLEEPCACHEEVICT_SHFT                                                          0xc
#define HWIO_USBCTL_GUCTL2_DISABLECFC_BMSK                                                                0x800
#define HWIO_USBCTL_GUCTL2_DISABLECFC_SHFT                                                                  0xb
#define HWIO_USBCTL_GUCTL2_RXPINGDURATION_BMSK                                                            0x7e0
#define HWIO_USBCTL_GUCTL2_RXPINGDURATION_SHFT                                                              0x5
#define HWIO_USBCTL_GUCTL2_TXPINGDURATION_BMSK                                                             0x1f
#define HWIO_USBCTL_GUCTL2_TXPINGDURATION_SHFT                                                              0x0

#define HWIO_USBCTL_GHWPARAMS8_ADDR                                                                  (USBCTL_DWC_USB3_REG_BASE      + 0x0000c600)
#define HWIO_USBCTL_GHWPARAMS8_PHYS                                                                  (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c600)
#define HWIO_USBCTL_GHWPARAMS8_OFFS                                                                  (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c600)
#define HWIO_USBCTL_GHWPARAMS8_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS8_POR                                                                   0x000002bc
#define HWIO_USBCTL_GHWPARAMS8_POR_RMSK                                                              0xffffffff
#define HWIO_USBCTL_GHWPARAMS8_IN          \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS8_ADDR, HWIO_USBCTL_GHWPARAMS8_RMSK)
#define HWIO_USBCTL_GHWPARAMS8_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GHWPARAMS8_ADDR, m)
#define HWIO_USBCTL_GHWPARAMS8_GHWPARAMS8_32_0_BMSK                                                  0xffffffff
#define HWIO_USBCTL_GHWPARAMS8_GHWPARAMS8_32_0_SHFT                                                         0x0

#define HWIO_USBCTL_GTXFIFOPRIDEV_ADDR                                                               (USBCTL_DWC_USB3_REG_BASE      + 0x0000c610)
#define HWIO_USBCTL_GTXFIFOPRIDEV_PHYS                                                               (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c610)
#define HWIO_USBCTL_GTXFIFOPRIDEV_OFFS                                                               (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c610)
#define HWIO_USBCTL_GTXFIFOPRIDEV_RMSK                                                                    0x1ff
#define HWIO_USBCTL_GTXFIFOPRIDEV_POR                                                                0x00000000
#define HWIO_USBCTL_GTXFIFOPRIDEV_POR_RMSK                                                           0xffffffff
#define HWIO_USBCTL_GTXFIFOPRIDEV_IN          \
        in_dword_masked(HWIO_USBCTL_GTXFIFOPRIDEV_ADDR, HWIO_USBCTL_GTXFIFOPRIDEV_RMSK)
#define HWIO_USBCTL_GTXFIFOPRIDEV_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GTXFIFOPRIDEV_ADDR, m)
#define HWIO_USBCTL_GTXFIFOPRIDEV_OUT(v)      \
        out_dword(HWIO_USBCTL_GTXFIFOPRIDEV_ADDR,v)
#define HWIO_USBCTL_GTXFIFOPRIDEV_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GTXFIFOPRIDEV_ADDR,m,v,HWIO_USBCTL_GTXFIFOPRIDEV_IN)
#define HWIO_USBCTL_GTXFIFOPRIDEV_GTXFIFOPRIDEV_BMSK                                                      0x1ff
#define HWIO_USBCTL_GTXFIFOPRIDEV_GTXFIFOPRIDEV_SHFT                                                        0x0

#define HWIO_USBCTL_GFLADJ_ADDR                                                                      (USBCTL_DWC_USB3_REG_BASE      + 0x0000c630)
#define HWIO_USBCTL_GFLADJ_PHYS                                                                      (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c630)
#define HWIO_USBCTL_GFLADJ_OFFS                                                                      (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c630)
#define HWIO_USBCTL_GFLADJ_RMSK                                                                      0xffbfffbf
#define HWIO_USBCTL_GFLADJ_POR                                                                       0x00000000
#define HWIO_USBCTL_GFLADJ_POR_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_GFLADJ_IN          \
        in_dword_masked(HWIO_USBCTL_GFLADJ_ADDR, HWIO_USBCTL_GFLADJ_RMSK)
#define HWIO_USBCTL_GFLADJ_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GFLADJ_ADDR, m)
#define HWIO_USBCTL_GFLADJ_OUT(v)      \
        out_dword(HWIO_USBCTL_GFLADJ_ADDR,v)
#define HWIO_USBCTL_GFLADJ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GFLADJ_ADDR,m,v,HWIO_USBCTL_GFLADJ_IN)
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_240MHZDECR_PLS1_BMSK                                        0x80000000
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_240MHZDECR_PLS1_SHFT                                              0x1f
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_240MHZ_DECR_BMSK                                            0x7f000000
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_240MHZ_DECR_SHFT                                                  0x18
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_LPM_SEL_BMSK                                                  0x800000
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_LPM_SEL_SHFT                                                      0x17
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_FLADJ_BMSK                                                    0x3fff00
#define HWIO_USBCTL_GFLADJ_GFLADJ_REFCLK_FLADJ_SHFT                                                         0x8
#define HWIO_USBCTL_GFLADJ_GFLADJ_30MHZ_SDBND_SEL_BMSK                                                     0x80
#define HWIO_USBCTL_GFLADJ_GFLADJ_30MHZ_SDBND_SEL_SHFT                                                      0x7
#define HWIO_USBCTL_GFLADJ_GFLADJ_30MHZ_BMSK                                                               0x3f
#define HWIO_USBCTL_GFLADJ_GFLADJ_30MHZ_SHFT                                                                0x0

#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_ADDR(p)                                             (USBCTL_DWC_USB3_REG_BASE      + 0x0000c800 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_PHYS(p)                                             (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c800 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_OFFS(p)                                             (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c800 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_RMSK                                                0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_MAXp                                                        12
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_POR                                                 0x00000000
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_INI(p)        \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_ADDR(p), HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_RMSK)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_ADDR(p), mask)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_ADDR(p),val)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_ADDR(p),mask,val,HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_INI(p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_PARAMETER_BMSK                                      0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR2_PARAMETER_SHFT                                             0x0

#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_ADDR(p)                                             (USBCTL_DWC_USB3_REG_BASE      + 0x0000c804 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_PHYS(p)                                             (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c804 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_OFFS(p)                                             (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c804 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_RMSK                                                0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_MAXp                                                        12
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_POR                                                 0x00000000
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_INI(p)        \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_ADDR(p), HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_RMSK)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_ADDR(p), mask)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_ADDR(p),val)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_ADDR(p),mask,val,HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_INI(p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_PARAMETER_BMSK                                      0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR1_PARAMETER_SHFT                                             0x0

#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_ADDR(p)                                             (USBCTL_DWC_USB3_REG_BASE      + 0x0000c808 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_PHYS(p)                                             (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c808 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_OFFS(p)                                             (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c808 + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_RMSK                                                0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_MAXp                                                        12
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_POR                                                 0x00000000
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_INI(p)        \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_ADDR(p), HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_RMSK)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_ADDR(p), mask)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_ADDR(p),val)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_ADDR(p),mask,val,HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_INI(p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_PARAMETER_BMSK                                      0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMDPAR0_PARAMETER_SHFT                                             0x0

#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_ADDR(p)                                                 (USBCTL_DWC_USB3_REG_BASE      + 0x0000c80c + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_PHYS(p)                                                 (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c80c + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_OFFS(p)                                                 (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c80c + 0x10 * (p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_RMSK                                                    0xfffffd0f
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_MAXp                                                            12
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_POR                                                     0x00000000
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_POR_RMSK                                                0xffffffff
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INI(p)        \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_ADDR(p), HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_RMSK)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_ADDR(p), mask)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_ADDR(p),val)
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_ADDR(p),mask,val,HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_INI(p))
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_COMMANDPARAM_BMSK                                       0xffff0000
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_COMMANDPARAM_SHFT                                             0x10
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDSTATUS_BMSK                                              0xf000
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDSTATUS_SHFT                                                 0xc
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_HIPRI_FORCERM_BMSK                                           0x800
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_HIPRI_FORCERM_SHFT                                             0xb
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_BMSK                                                  0x400
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDACT_SHFT                                                    0xa
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDIOC_BMSK                                                  0x100
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDIOC_SHFT                                                    0x8
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDTYP_BMSK                                                    0xf
#define HWIO_USBCTL_DEPCMDPAR2_REGS_p_DEPCMD_CMDTYP_SHFT                                                    0x0

#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_ADDR(p)                                                 (USBCTL_DWC_USB3_REG_BASE      + 0x0000ca00 + 0x4 * (p))
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_PHYS(p)                                                 (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000ca00 + 0x4 * (p))
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_OFFS(p)                                                 (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000ca00 + 0x4 * (p))
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_RMSK                                                    0xffffffff
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_MAXp                                                             0
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_POR                                                     0x00000000
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_POR_RMSK                                                0xffffffff
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_INI(p)        \
        in_dword_masked(HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_ADDR(p), HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_RMSK)
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_INMI(p,mask)    \
        in_dword_masked(HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_ADDR(p), mask)
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_OUTI(p,val)    \
        out_dword(HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_ADDR(p),val)
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_OUTMI(p,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_ADDR(p),mask,val,HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_INI(p))
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_DEVICE_IMODC_BMSK                                       0xffff0000
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_DEVICE_IMODC_SHFT                                             0x10
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_DEVICE_IMODI_BMSK                                           0xffff
#define HWIO_USBCTL_DEV_IMOD_REGS_p_DEV_IMOD_DEVICE_IMODI_SHFT                                              0x0

#define HWIO_USBCTL_DCFG_ADDR                                                                        (USBCTL_DWC_USB3_REG_BASE      + 0x0000c700)
#define HWIO_USBCTL_DCFG_PHYS                                                                        (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c700)
#define HWIO_USBCTL_DCFG_OFFS                                                                        (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c700)
#define HWIO_USBCTL_DCFG_RMSK                                                                          0xfff3ff
#define HWIO_USBCTL_DCFG_POR                                                                         0x00080000
#define HWIO_USBCTL_DCFG_POR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_DCFG_IN          \
        in_dword_masked(HWIO_USBCTL_DCFG_ADDR, HWIO_USBCTL_DCFG_RMSK)
#define HWIO_USBCTL_DCFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DCFG_ADDR, m)
#define HWIO_USBCTL_DCFG_OUT(v)      \
        out_dword(HWIO_USBCTL_DCFG_ADDR,v)
#define HWIO_USBCTL_DCFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DCFG_ADDR,m,v,HWIO_USBCTL_DCFG_IN)
#define HWIO_USBCTL_DCFG_IGNSTRMPP_BMSK                                                                0x800000
#define HWIO_USBCTL_DCFG_IGNSTRMPP_SHFT                                                                    0x17
#define HWIO_USBCTL_DCFG_LPMCAP_BMSK                                                                   0x400000
#define HWIO_USBCTL_DCFG_LPMCAP_SHFT                                                                       0x16
#define HWIO_USBCTL_DCFG_NUMP_BMSK                                                                     0x3e0000
#define HWIO_USBCTL_DCFG_NUMP_SHFT                                                                         0x11
#define HWIO_USBCTL_DCFG_INTRNUM_BMSK                                                                   0x1f000
#define HWIO_USBCTL_DCFG_INTRNUM_SHFT                                                                       0xc
#define HWIO_USBCTL_DCFG_DEVADDR_BMSK                                                                     0x3f8
#define HWIO_USBCTL_DCFG_DEVADDR_SHFT                                                                       0x3
#define HWIO_USBCTL_DCFG_DEVSPD_BMSK                                                                        0x7
#define HWIO_USBCTL_DCFG_DEVSPD_SHFT                                                                        0x0

#define HWIO_USBCTL_DCTL_ADDR                                                                        (USBCTL_DWC_USB3_REG_BASE      + 0x0000c704)
#define HWIO_USBCTL_DCTL_PHYS                                                                        (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c704)
#define HWIO_USBCTL_DCTL_OFFS                                                                        (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c704)
#define HWIO_USBCTL_DCTL_RMSK                                                                        0xdfff1ffe
#define HWIO_USBCTL_DCTL_POR                                                                         0x00f00000
#define HWIO_USBCTL_DCTL_POR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_DCTL_IN          \
        in_dword_masked(HWIO_USBCTL_DCTL_ADDR, HWIO_USBCTL_DCTL_RMSK)
#define HWIO_USBCTL_DCTL_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DCTL_ADDR, m)
#define HWIO_USBCTL_DCTL_OUT(v)      \
        out_dword(HWIO_USBCTL_DCTL_ADDR,v)
#define HWIO_USBCTL_DCTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DCTL_ADDR,m,v,HWIO_USBCTL_DCTL_IN)
#define HWIO_USBCTL_DCTL_RUN_STOP_BMSK                                                               0x80000000
#define HWIO_USBCTL_DCTL_RUN_STOP_SHFT                                                                     0x1f
#define HWIO_USBCTL_DCTL_CSFTRST_BMSK                                                                0x40000000
#define HWIO_USBCTL_DCTL_CSFTRST_SHFT                                                                      0x1e
#define HWIO_USBCTL_DCTL_HIRDTHRES_BMSK                                                              0x1f000000
#define HWIO_USBCTL_DCTL_HIRDTHRES_SHFT                                                                    0x18
#define HWIO_USBCTL_DCTL_LPM_NYET_THRES_BMSK                                                           0xf00000
#define HWIO_USBCTL_DCTL_LPM_NYET_THRES_SHFT                                                               0x14
#define HWIO_USBCTL_DCTL_KEEPCONNECT_BMSK                                                               0x80000
#define HWIO_USBCTL_DCTL_KEEPCONNECT_SHFT                                                                  0x13
#define HWIO_USBCTL_DCTL_L1HIBERNATIONEN_BMSK                                                           0x40000
#define HWIO_USBCTL_DCTL_L1HIBERNATIONEN_SHFT                                                              0x12
#define HWIO_USBCTL_DCTL_CRS_BMSK                                                                       0x20000
#define HWIO_USBCTL_DCTL_CRS_SHFT                                                                          0x11
#define HWIO_USBCTL_DCTL_CSS_BMSK                                                                       0x10000
#define HWIO_USBCTL_DCTL_CSS_SHFT                                                                          0x10
#define HWIO_USBCTL_DCTL_INITU2ENA_BMSK                                                                  0x1000
#define HWIO_USBCTL_DCTL_INITU2ENA_SHFT                                                                     0xc
#define HWIO_USBCTL_DCTL_ACCEPTU2ENA_BMSK                                                                 0x800
#define HWIO_USBCTL_DCTL_ACCEPTU2ENA_SHFT                                                                   0xb
#define HWIO_USBCTL_DCTL_INITU1ENA_BMSK                                                                   0x400
#define HWIO_USBCTL_DCTL_INITU1ENA_SHFT                                                                     0xa
#define HWIO_USBCTL_DCTL_ACCEPTU1ENA_BMSK                                                                 0x200
#define HWIO_USBCTL_DCTL_ACCEPTU1ENA_SHFT                                                                   0x9
#define HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK                                                                 0x1e0
#define HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT                                                                   0x5
#define HWIO_USBCTL_DCTL_TSTCTL_BMSK                                                                       0x1e
#define HWIO_USBCTL_DCTL_TSTCTL_SHFT                                                                        0x1

#define HWIO_USBCTL_DEVTEN_ADDR                                                                      (USBCTL_DWC_USB3_REG_BASE      + 0x0000c708)
#define HWIO_USBCTL_DEVTEN_PHYS                                                                      (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c708)
#define HWIO_USBCTL_DEVTEN_OFFS                                                                      (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c708)
#define HWIO_USBCTL_DEVTEN_RMSK                                                                         0x153ff
#define HWIO_USBCTL_DEVTEN_POR                                                                       0x00000000
#define HWIO_USBCTL_DEVTEN_POR_RMSK                                                                  0xffffffff
#define HWIO_USBCTL_DEVTEN_IN          \
        in_dword_masked(HWIO_USBCTL_DEVTEN_ADDR, HWIO_USBCTL_DEVTEN_RMSK)
#define HWIO_USBCTL_DEVTEN_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DEVTEN_ADDR, m)
#define HWIO_USBCTL_DEVTEN_OUT(v)      \
        out_dword(HWIO_USBCTL_DEVTEN_ADDR,v)
#define HWIO_USBCTL_DEVTEN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DEVTEN_ADDR,m,v,HWIO_USBCTL_DEVTEN_IN)
#define HWIO_USBCTL_DEVTEN_ECCERREN_BMSK                                                                0x10000
#define HWIO_USBCTL_DEVTEN_ECCERREN_SHFT                                                                   0x10
#define HWIO_USBCTL_DEVTEN_L1WKUPEVTEN_BMSK                                                              0x4000
#define HWIO_USBCTL_DEVTEN_L1WKUPEVTEN_SHFT                                                                 0xe
#define HWIO_USBCTL_DEVTEN_VENDEVTSTRCVDEN_BMSK                                                          0x1000
#define HWIO_USBCTL_DEVTEN_VENDEVTSTRCVDEN_SHFT                                                             0xc
#define HWIO_USBCTL_DEVTEN_ERRTICERREVTEN_BMSK                                                            0x200
#define HWIO_USBCTL_DEVTEN_ERRTICERREVTEN_SHFT                                                              0x9
#define HWIO_USBCTL_DEVTEN_L1SUSPEN_BMSK                                                                  0x100
#define HWIO_USBCTL_DEVTEN_L1SUSPEN_SHFT                                                                    0x8
#define HWIO_USBCTL_DEVTEN_SOFTEVTEN_BMSK                                                                  0x80
#define HWIO_USBCTL_DEVTEN_SOFTEVTEN_SHFT                                                                   0x7
#define HWIO_USBCTL_DEVTEN_U3L2L1SUSPEN_BMSK                                                               0x40
#define HWIO_USBCTL_DEVTEN_U3L2L1SUSPEN_SHFT                                                                0x6
#define HWIO_USBCTL_DEVTEN_HIBERNATIONREQEVTEN_BMSK                                                        0x20
#define HWIO_USBCTL_DEVTEN_HIBERNATIONREQEVTEN_SHFT                                                         0x5
#define HWIO_USBCTL_DEVTEN_WKUPEVTEN_BMSK                                                                  0x10
#define HWIO_USBCTL_DEVTEN_WKUPEVTEN_SHFT                                                                   0x4
#define HWIO_USBCTL_DEVTEN_ULSTCNGEN_BMSK                                                                   0x8
#define HWIO_USBCTL_DEVTEN_ULSTCNGEN_SHFT                                                                   0x3
#define HWIO_USBCTL_DEVTEN_CONNECTDONEEVTEN_BMSK                                                            0x4
#define HWIO_USBCTL_DEVTEN_CONNECTDONEEVTEN_SHFT                                                            0x2
#define HWIO_USBCTL_DEVTEN_USBRSTEVTEN_BMSK                                                                 0x2
#define HWIO_USBCTL_DEVTEN_USBRSTEVTEN_SHFT                                                                 0x1
#define HWIO_USBCTL_DEVTEN_DISSCONNEVTEN_BMSK                                                               0x1
#define HWIO_USBCTL_DEVTEN_DISSCONNEVTEN_SHFT                                                               0x0

#define HWIO_USBCTL_DSTS_ADDR                                                                        (USBCTL_DWC_USB3_REG_BASE      + 0x0000c70c)
#define HWIO_USBCTL_DSTS_PHYS                                                                        (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c70c)
#define HWIO_USBCTL_DSTS_OFFS                                                                        (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c70c)
#define HWIO_USBCTL_DSTS_RMSK                                                                        0x33ffffff
#define HWIO_USBCTL_DSTS_POR                                                                         0x00d20001
#define HWIO_USBCTL_DSTS_POR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_DSTS_IN          \
        in_dword_masked(HWIO_USBCTL_DSTS_ADDR, HWIO_USBCTL_DSTS_RMSK)
#define HWIO_USBCTL_DSTS_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DSTS_ADDR, m)
#define HWIO_USBCTL_DSTS_OUT(v)      \
        out_dword(HWIO_USBCTL_DSTS_ADDR,v)
#define HWIO_USBCTL_DSTS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DSTS_ADDR,m,v,HWIO_USBCTL_DSTS_IN)
#define HWIO_USBCTL_DSTS_DCNRD_BMSK                                                                  0x20000000
#define HWIO_USBCTL_DSTS_DCNRD_SHFT                                                                        0x1d
#define HWIO_USBCTL_DSTS_SRE_BMSK                                                                    0x10000000
#define HWIO_USBCTL_DSTS_SRE_SHFT                                                                          0x1c
#define HWIO_USBCTL_DSTS_RSS_BMSK                                                                     0x2000000
#define HWIO_USBCTL_DSTS_RSS_SHFT                                                                          0x19
#define HWIO_USBCTL_DSTS_SSS_BMSK                                                                     0x1000000
#define HWIO_USBCTL_DSTS_SSS_SHFT                                                                          0x18
#define HWIO_USBCTL_DSTS_COREIDLE_BMSK                                                                 0x800000
#define HWIO_USBCTL_DSTS_COREIDLE_SHFT                                                                     0x17
#define HWIO_USBCTL_DSTS_DEVCTRLHLT_BMSK                                                               0x400000
#define HWIO_USBCTL_DSTS_DEVCTRLHLT_SHFT                                                                   0x16
#define HWIO_USBCTL_DSTS_USBLNKST_BMSK                                                                 0x3c0000
#define HWIO_USBCTL_DSTS_USBLNKST_SHFT                                                                     0x12
#define HWIO_USBCTL_DSTS_RXFIFOEMPTY_BMSK                                                               0x20000
#define HWIO_USBCTL_DSTS_RXFIFOEMPTY_SHFT                                                                  0x11
#define HWIO_USBCTL_DSTS_SOFFN_BMSK                                                                     0x1fff8
#define HWIO_USBCTL_DSTS_SOFFN_SHFT                                                                         0x3
#define HWIO_USBCTL_DSTS_CONNECTSPD_BMSK                                                                    0x7
#define HWIO_USBCTL_DSTS_CONNECTSPD_SHFT                                                                    0x0

#define HWIO_USBCTL_DGCMDPAR_ADDR                                                                    (USBCTL_DWC_USB3_REG_BASE      + 0x0000c710)
#define HWIO_USBCTL_DGCMDPAR_PHYS                                                                    (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c710)
#define HWIO_USBCTL_DGCMDPAR_OFFS                                                                    (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c710)
#define HWIO_USBCTL_DGCMDPAR_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_DGCMDPAR_POR                                                                     0x00000000
#define HWIO_USBCTL_DGCMDPAR_POR_RMSK                                                                0xffffffff
#define HWIO_USBCTL_DGCMDPAR_IN          \
        in_dword_masked(HWIO_USBCTL_DGCMDPAR_ADDR, HWIO_USBCTL_DGCMDPAR_RMSK)
#define HWIO_USBCTL_DGCMDPAR_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DGCMDPAR_ADDR, m)
#define HWIO_USBCTL_DGCMDPAR_OUT(v)      \
        out_dword(HWIO_USBCTL_DGCMDPAR_ADDR,v)
#define HWIO_USBCTL_DGCMDPAR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DGCMDPAR_ADDR,m,v,HWIO_USBCTL_DGCMDPAR_IN)
#define HWIO_USBCTL_DGCMDPAR_PARAMETER_BMSK                                                          0xffffffff
#define HWIO_USBCTL_DGCMDPAR_PARAMETER_SHFT                                                                 0x0

#define HWIO_USBCTL_DGCMD_ADDR                                                                       (USBCTL_DWC_USB3_REG_BASE      + 0x0000c714)
#define HWIO_USBCTL_DGCMD_PHYS                                                                       (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c714)
#define HWIO_USBCTL_DGCMD_OFFS                                                                       (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c714)
#define HWIO_USBCTL_DGCMD_RMSK                                                                           0xf5ff
#define HWIO_USBCTL_DGCMD_POR                                                                        0x00000000
#define HWIO_USBCTL_DGCMD_POR_RMSK                                                                   0xffffffff
#define HWIO_USBCTL_DGCMD_IN          \
        in_dword_masked(HWIO_USBCTL_DGCMD_ADDR, HWIO_USBCTL_DGCMD_RMSK)
#define HWIO_USBCTL_DGCMD_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DGCMD_ADDR, m)
#define HWIO_USBCTL_DGCMD_OUT(v)      \
        out_dword(HWIO_USBCTL_DGCMD_ADDR,v)
#define HWIO_USBCTL_DGCMD_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DGCMD_ADDR,m,v,HWIO_USBCTL_DGCMD_IN)
#define HWIO_USBCTL_DGCMD_CMDSTATUS_BMSK                                                                 0xf000
#define HWIO_USBCTL_DGCMD_CMDSTATUS_SHFT                                                                    0xc
#define HWIO_USBCTL_DGCMD_CMDACT_BMSK                                                                     0x400
#define HWIO_USBCTL_DGCMD_CMDACT_SHFT                                                                       0xa
#define HWIO_USBCTL_DGCMD_CMDIOC_BMSK                                                                     0x100
#define HWIO_USBCTL_DGCMD_CMDIOC_SHFT                                                                       0x8
#define HWIO_USBCTL_DGCMD_CMDTYP_BMSK                                                                      0xff
#define HWIO_USBCTL_DGCMD_CMDTYP_SHFT                                                                       0x0

#define HWIO_USBCTL_DALEPENA_ADDR                                                                    (USBCTL_DWC_USB3_REG_BASE      + 0x0000c720)
#define HWIO_USBCTL_DALEPENA_PHYS                                                                    (USBCTL_DWC_USB3_REG_BASE_PHYS + 0x0000c720)
#define HWIO_USBCTL_DALEPENA_OFFS                                                                    (USBCTL_DWC_USB3_REG_BASE_OFFS + 0x0000c720)
#define HWIO_USBCTL_DALEPENA_RMSK                                                                    0xffffffff
#define HWIO_USBCTL_DALEPENA_POR                                                                     0x00000000
#define HWIO_USBCTL_DALEPENA_POR_RMSK                                                                0xffffffff
#define HWIO_USBCTL_DALEPENA_IN          \
        in_dword_masked(HWIO_USBCTL_DALEPENA_ADDR, HWIO_USBCTL_DALEPENA_RMSK)
#define HWIO_USBCTL_DALEPENA_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DALEPENA_ADDR, m)
#define HWIO_USBCTL_DALEPENA_OUT(v)      \
        out_dword(HWIO_USBCTL_DALEPENA_ADDR,v)
#define HWIO_USBCTL_DALEPENA_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DALEPENA_ADDR,m,v,HWIO_USBCTL_DALEPENA_IN)
#define HWIO_USBCTL_DALEPENA_USBACTEP_BMSK                                                           0xffffffff
#define HWIO_USBCTL_DALEPENA_USBACTEP_SHFT                                                                  0x0

/*----------------------------------------------------------------------------
 * MODULE: USBCTL_USB30_DBM_REGFILE
 *--------------------------------------------------------------------------*/

#define USBCTL_USB30_DBM_REGFILE_REG_BASE                                      (USB20S_BASE      + 0x000f8000)
#define USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS                                 (USB20S_BASE_PHYS + 0x000f8000)
#define USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS                                 0x000f8000

#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_ADDR(n)                                   (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000000 + 0x4 * (n))
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_PHYS(n)                                   (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000000 + 0x4 * (n))
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_OFFS(n)                                   (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000000 + 0x4 * (n))
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_RMSK                                          0x7d3f
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_MAXn                                               0
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_POR                                       0x00000000
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_POR_RMSK                                  0xffffffff
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_EP_CFG_ADDRn_ADDR(n), HWIO_USBCTL_DBM_EP_CFG_ADDRn_RMSK)
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_EP_CFG_ADDRn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_DBM_EP_CFG_ADDRn_ADDR(n),val)
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_EP_CFG_ADDRn_ADDR(n),mask,val,HWIO_USBCTL_DBM_EP_CFG_ADDRn_INI(n))
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_BAM_P_SW_RST_DISABLE_BMSK                 0x4000
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_BAM_P_SW_RST_DISABLE_SHFT                    0xe
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_ZLT_DISABLE_BMSK                          0x2000
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_ZLT_DISABLE_SHFT                             0xd
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_LINK_TAG_DISABLE_BMSK                     0x1000
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_LINK_TAG_DISABLE_SHFT                        0xc
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_SINGLE_MODE_BMSK                           0x800
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_SINGLE_MODE_SHFT                             0xb
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_INT_RAM_ACC_BMSK                           0x400
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_INT_RAM_ACC_SHFT                             0xa
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_PRODUCER_BMSK                              0x100
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_PRODUCER_SHFT                                0x8
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_USB3_EPNUM_BMSK                                 0x3e
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_USB3_EPNUM_SHFT                                  0x1
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_EN_EP_BMSK                                   0x1
#define HWIO_USBCTL_DBM_EP_CFG_ADDRn_DBM_EN_EP_SHFT                                   0x0

#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_ADDR(n)                                (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000080 + 0x4 * (n))
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_PHYS(n)                                (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000080 + 0x4 * (n))
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_OFFS(n)                                (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000080 + 0x4 * (n))
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_RMSK                                       0xffff
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_MAXn                                            0
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_POR                                    0x00000000
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_POR_RMSK                               0xffffffff
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_ADDR(n), HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_RMSK)
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_ADDR(n),val)
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_ADDR(n),mask,val,HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_INI(n))
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_DATA_FIFO_SIZE_BMSK                        0xffff
#define HWIO_USBCTL_DBM_DATA_SIZE_ADDRn_DATA_FIFO_SIZE_SHFT                           0x0

#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_ADDR(n)                            (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000100 + 0x8 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_PHYS(n)                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000100 + 0x8 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_OFFS(n)                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000100 + 0x8 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_RMSK                               0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_MAXn                                        0
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_POR                                0x00000000
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_POR_RMSK                           0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_ADDR(n), HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_RMSK)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_ADDR(n),val)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_ADDR(n),mask,val,HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_INI(n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_DATA_FIFO_ADDR_LSB_BMSK            0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_LSBn_DATA_FIFO_ADDR_LSB_SHFT                   0x0

#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_ADDR(n)                            (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000104 + 0x8 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_PHYS(n)                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000104 + 0x8 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_OFFS(n)                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000104 + 0x8 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_RMSK                               0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_MAXn                                        0
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_POR                                0x00000000
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_POR_RMSK                           0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_ADDR(n), HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_RMSK)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_ADDR(n),val)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_ADDR(n),mask,val,HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_INI(n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_DATA_FIFO_ADDR_MSB_BMSK            0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_MSBn_DATA_FIFO_ADDR_MSB_SHFT                   0x0

#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_ADDR                                 (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000200)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_PHYS                                 (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000200)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_OFFS                                 (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000200)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_RMSK                                        0x1
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_POR                                  0x00000001
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_POR_RMSK                             0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_ADDR, HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_RMSK)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_ADDR, m)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_ADDR,v)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_ADDR,m,v,HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_IN)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_DBM_DATA_FIFO_ADDR_ENN_BMSK                 0x1
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDR_EN_DBM_DATA_FIFO_ADDR_ENN_SHFT                 0x0

#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_ADDR                                 (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000204)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_PHYS                                 (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000204)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_OFFS                                 (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000204)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_RMSK                                        0x1
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_POR                                  0x00000001
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_POR_RMSK                             0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_ADDR, HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_RMSK)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_ADDR, m)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_ADDR,v)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_ADDR,m,v,HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_IN)
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_DBM_DATA_FIFO_SIZE_ENN_BMSK                 0x1
#define HWIO_USBCTL_DBM_DATA_FIFO_SIZE_EN_DBM_DATA_FIFO_SIZE_ENN_SHFT                 0x0

#define HWIO_USBCTL_DBM_DBG_CNFG_ADDR                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000208)
#define HWIO_USBCTL_DBM_DBG_CNFG_PHYS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000208)
#define HWIO_USBCTL_DBM_DBG_CNFG_OFFS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000208)
#define HWIO_USBCTL_DBM_DBG_CNFG_RMSK                                                 0x1
#define HWIO_USBCTL_DBM_DBG_CNFG_POR                                           0x00000000
#define HWIO_USBCTL_DBM_DBG_CNFG_POR_RMSK                                      0xffffffff
#define HWIO_USBCTL_DBM_DBG_CNFG_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DBG_CNFG_ADDR, HWIO_USBCTL_DBM_DBG_CNFG_RMSK)
#define HWIO_USBCTL_DBM_DBG_CNFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DBG_CNFG_ADDR, m)
#define HWIO_USBCTL_DBM_DBG_CNFG_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DBG_CNFG_ADDR,v)
#define HWIO_USBCTL_DBM_DBG_CNFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DBG_CNFG_ADDR,m,v,HWIO_USBCTL_DBM_DBG_CNFG_IN)
#define HWIO_USBCTL_DBM_DBG_CNFG_ENABLE_IOCN_BMSK                                     0x1
#define HWIO_USBCTL_DBM_DBG_CNFG_ENABLE_IOCN_SHFT                                     0x0

#define HWIO_USBCTL_DBM_DIS_UPDXFER_ADDR                                       (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000298)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_PHYS                                       (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000298)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_OFFS                                       (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000298)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_RMSK                                              0x1
#define HWIO_USBCTL_DBM_DIS_UPDXFER_POR                                        0x00000000
#define HWIO_USBCTL_DBM_DIS_UPDXFER_POR_RMSK                                   0xffffffff
#define HWIO_USBCTL_DBM_DIS_UPDXFER_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DIS_UPDXFER_ADDR, HWIO_USBCTL_DBM_DIS_UPDXFER_RMSK)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DIS_UPDXFER_ADDR, m)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DIS_UPDXFER_ADDR,v)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DIS_UPDXFER_ADDR,m,v,HWIO_USBCTL_DBM_DIS_UPDXFER_IN)
#define HWIO_USBCTL_DBM_DIS_UPDXFER_DIS_UPDXFER_EP0_BMSK                              0x1
#define HWIO_USBCTL_DBM_DIS_UPDXFER_DIS_UPDXFER_EP0_SHFT                              0x0

#define HWIO_USBCTL_DBM_DEPCMD_IOC_ADDR                                        (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x0000029c)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_PHYS                                        (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x0000029c)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_OFFS                                        (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x0000029c)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_RMSK                                               0x1
#define HWIO_USBCTL_DBM_DEPCMD_IOC_POR                                         0x00000000
#define HWIO_USBCTL_DBM_DEPCMD_IOC_POR_RMSK                                    0xffffffff
#define HWIO_USBCTL_DBM_DEPCMD_IOC_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DEPCMD_IOC_ADDR, HWIO_USBCTL_DBM_DEPCMD_IOC_RMSK)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DEPCMD_IOC_ADDR, m)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DEPCMD_IOC_ADDR,v)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DEPCMD_IOC_ADDR,m,v,HWIO_USBCTL_DBM_DEPCMD_IOC_IN)
#define HWIO_USBCTL_DBM_DEPCMD_IOC_DEPCMD_IOC_EP0_BMSK                                0x1
#define HWIO_USBCTL_DBM_DEPCMD_IOC_DEPCMD_IOC_EP0_SHFT                                0x0

#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_ADDR                                     (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000300)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_PHYS                                     (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000300)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_OFFS                                     (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000300)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_RMSK                                            0x1
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_POR                                      0x00000001
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_POR_RMSK                                 0xffffffff
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DEPCMD_CMDACT_ADDR, HWIO_USBCTL_DBM_DEPCMD_CMDACT_RMSK)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DEPCMD_CMDACT_ADDR, m)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DEPCMD_CMDACT_ADDR,v)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DEPCMD_CMDACT_ADDR,m,v,HWIO_USBCTL_DBM_DEPCMD_CMDACT_IN)
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_DEPCMD_CMDACT_EP0_BMSK                          0x1
#define HWIO_USBCTL_DBM_DEPCMD_CMDACT_DEPCMD_CMDACT_EP0_SHFT                          0x0

#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_ADDR                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000304)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_PHYS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000304)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_OFFS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000304)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_RMSK                                             0x1
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_POR                                       0x00000000
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_POR_RMSK                                  0xffffffff
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DEPCMD_HIPRI_ADDR, HWIO_USBCTL_DBM_DEPCMD_HIPRI_RMSK)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DEPCMD_HIPRI_ADDR, m)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DEPCMD_HIPRI_ADDR,v)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DEPCMD_HIPRI_ADDR,m,v,HWIO_USBCTL_DBM_DEPCMD_HIPRI_IN)
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_DEPCMD_HIPRI_EP0_BMSK                            0x1
#define HWIO_USBCTL_DBM_DEPCMD_HIPRI_DEPCMD_HIPRI_EP0_SHFT                            0x0

#define HWIO_USBCTL_DBM_SOFT_RESET_ADDR                                        (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x0000020c)
#define HWIO_USBCTL_DBM_SOFT_RESET_PHYS                                        (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x0000020c)
#define HWIO_USBCTL_DBM_SOFT_RESET_OFFS                                        (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x0000020c)
#define HWIO_USBCTL_DBM_SOFT_RESET_RMSK                                        0x800000ff
#define HWIO_USBCTL_DBM_SOFT_RESET_POR                                         0x00000000
#define HWIO_USBCTL_DBM_SOFT_RESET_POR_RMSK                                    0xffffffff
#define HWIO_USBCTL_DBM_SOFT_RESET_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_SOFT_RESET_ADDR, HWIO_USBCTL_DBM_SOFT_RESET_RMSK)
#define HWIO_USBCTL_DBM_SOFT_RESET_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_SOFT_RESET_ADDR, m)
#define HWIO_USBCTL_DBM_SOFT_RESET_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_SOFT_RESET_ADDR,v)
#define HWIO_USBCTL_DBM_SOFT_RESET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_SOFT_RESET_ADDR,m,v,HWIO_USBCTL_DBM_SOFT_RESET_IN)
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_BMSK                            0x80000000
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_SHFT                                  0x1f
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP7_BMSK                              0x80
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP7_SHFT                               0x7
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP6_BMSK                              0x40
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP6_SHFT                               0x6
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP5_BMSK                              0x20
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP5_SHFT                               0x5
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP4_BMSK                              0x10
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP4_SHFT                               0x4
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP3_BMSK                               0x8
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP3_SHFT                               0x3
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP2_BMSK                               0x4
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP2_SHFT                               0x2
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP1_BMSK                               0x2
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP1_SHFT                               0x1
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP0_BMSK                               0x1
#define HWIO_USBCTL_DBM_SOFT_RESET_DBM_SFT_RST_EP0_SHFT                               0x0

#define HWIO_USBCTL_DBM_GEN_CFG_ADDR                                           (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000210)
#define HWIO_USBCTL_DBM_GEN_CFG_PHYS                                           (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000210)
#define HWIO_USBCTL_DBM_GEN_CFG_OFFS                                           (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000210)
#define HWIO_USBCTL_DBM_GEN_CFG_RMSK                                              0x1ff3f
#define HWIO_USBCTL_DBM_GEN_CFG_POR                                            0x00001005
#define HWIO_USBCTL_DBM_GEN_CFG_POR_RMSK                                       0xffffffff
#define HWIO_USBCTL_DBM_GEN_CFG_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_GEN_CFG_ADDR, HWIO_USBCTL_DBM_GEN_CFG_RMSK)
#define HWIO_USBCTL_DBM_GEN_CFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_GEN_CFG_ADDR, m)
#define HWIO_USBCTL_DBM_GEN_CFG_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_GEN_CFG_ADDR,v)
#define HWIO_USBCTL_DBM_GEN_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_GEN_CFG_ADDR,m,v,HWIO_USBCTL_DBM_GEN_CFG_IN)
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_TRACE_BUFF_EN_BMSK                            0x10000
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_TRACE_BUFF_EN_SHFT                               0x10
#define HWIO_USBCTL_DBM_GEN_CFG_BPTR_EPNUM_CB_BMSK                                 0x8000
#define HWIO_USBCTL_DBM_GEN_CFG_BPTR_EPNUM_CB_SHFT                                    0xf
#define HWIO_USBCTL_DBM_GEN_CFG_PIPE_SIZE_REC_CB_BMSK                              0x4000
#define HWIO_USBCTL_DBM_GEN_CFG_PIPE_SIZE_REC_CB_SHFT                                 0xe
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_RD_AFTR_SP_CB_BMSK                             0x2000
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_RD_AFTR_SP_CB_SHFT                                0xd
#define HWIO_USBCTL_DBM_GEN_CFG_SW_TRB_P_DISABLE_CB_BMSK                           0x1000
#define HWIO_USBCTL_DBM_GEN_CFG_SW_TRB_P_DISABLE_CB_SHFT                              0xc
#define HWIO_USBCTL_DBM_GEN_CFG_LINK_TRB_C_CB_BMSK                                  0x800
#define HWIO_USBCTL_DBM_GEN_CFG_LINK_TRB_C_CB_SHFT                                    0xb
#define HWIO_USBCTL_DBM_GEN_CFG_LINK_TRB_P_CB_BMSK                                  0x400
#define HWIO_USBCTL_DBM_GEN_CFG_LINK_TRB_P_CB_SHFT                                    0xa
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_C_64B_ALGN_DIS_N_BMSK                           0x200
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_C_64B_ALGN_DIS_N_SHFT                             0x9
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_P_64B_ALGN_DIS_N_BMSK                           0x100
#define HWIO_USBCTL_DBM_GEN_CFG_TRB_P_64B_ALGN_DIS_N_SHFT                             0x8
#define HWIO_USBCTL_DBM_GEN_CFG_DBM_SUPPORT_LEADING_DATA_BMSK                        0x20
#define HWIO_USBCTL_DBM_GEN_CFG_DBM_SUPPORT_LEADING_DATA_SHFT                         0x5
#define HWIO_USBCTL_DBM_GEN_CFG_AXI_COMPLIANCE_CB_1_BMSK                             0x10
#define HWIO_USBCTL_DBM_GEN_CFG_AXI_COMPLIANCE_CB_1_SHFT                              0x4
#define HWIO_USBCTL_DBM_GEN_CFG_AXI_COMPLIANCE_CB_0_BMSK                              0x8
#define HWIO_USBCTL_DBM_GEN_CFG_AXI_COMPLIANCE_CB_0_SHFT                              0x3
#define HWIO_USBCTL_DBM_GEN_CFG_BAM_ZLT_SUPPORT_BMSK                                  0x4
#define HWIO_USBCTL_DBM_GEN_CFG_BAM_ZLT_SUPPORT_SHFT                                  0x2
#define HWIO_USBCTL_DBM_GEN_CFG_DBM_TRB_INDIC_DIS_BMSK                                0x2
#define HWIO_USBCTL_DBM_GEN_CFG_DBM_TRB_INDIC_DIS_SHFT                                0x1
#define HWIO_USBCTL_DBM_GEN_CFG_DBM_EN_USB3_BMSK                                      0x1
#define HWIO_USBCTL_DBM_GEN_CFG_DBM_EN_USB3_SHFT                                      0x0

#define HWIO_USBCTL_DBM_STATUS_ADDR                                            (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000214)
#define HWIO_USBCTL_DBM_STATUS_PHYS                                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000214)
#define HWIO_USBCTL_DBM_STATUS_OFFS                                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000214)
#define HWIO_USBCTL_DBM_STATUS_RMSK                                                   0x1
#define HWIO_USBCTL_DBM_STATUS_POR                                             0x00000000
#define HWIO_USBCTL_DBM_STATUS_POR_RMSK                                        0xffffffff
#define HWIO_USBCTL_DBM_STATUS_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_STATUS_ADDR, HWIO_USBCTL_DBM_STATUS_RMSK)
#define HWIO_USBCTL_DBM_STATUS_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_STATUS_ADDR, m)
#define HWIO_USBCTL_DBM_STATUS_SET_UNALIGNED_ZLTN_BMSK                                0x1
#define HWIO_USBCTL_DBM_STATUS_SET_UNALIGNED_ZLTN_SHFT                                0x0

#define HWIO_USBCTL_DBM_STATES_ADDR                                            (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000218)
#define HWIO_USBCTL_DBM_STATES_PHYS                                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000218)
#define HWIO_USBCTL_DBM_STATES_OFFS                                            (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000218)
#define HWIO_USBCTL_DBM_STATES_RMSK                                             0xfffffff
#define HWIO_USBCTL_DBM_STATES_POR                                             0x00000000
#define HWIO_USBCTL_DBM_STATES_POR_RMSK                                        0xffffffff
#define HWIO_USBCTL_DBM_STATES_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_STATES_ADDR, HWIO_USBCTL_DBM_STATES_RMSK)
#define HWIO_USBCTL_DBM_STATES_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_STATES_ADDR, m)
#define HWIO_USBCTL_DBM_STATES_CUR_DBM_EPNUM_BMSK                               0xe000000
#define HWIO_USBCTL_DBM_STATES_CUR_DBM_EPNUM_SHFT                                    0x19
#define HWIO_USBCTL_DBM_STATES_AHBM_UPDXFER_STATE_BMSK                          0x1800000
#define HWIO_USBCTL_DBM_STATES_AHBM_UPDXFER_STATE_SHFT                               0x17
#define HWIO_USBCTL_DBM_STATES_AHBM_DEPCMD_STATE_BMSK                            0x700000
#define HWIO_USBCTL_DBM_STATES_AHBM_DEPCMD_STATE_SHFT                                0x14
#define HWIO_USBCTL_DBM_STATES_ERR_RSP_STATE_BMSK                                 0xc0000
#define HWIO_USBCTL_DBM_STATES_ERR_RSP_STATE_SHFT                                    0x12
#define HWIO_USBCTL_DBM_STATES_RAM13_RD_STATE_BMSK                                0x38000
#define HWIO_USBCTL_DBM_STATES_RAM13_RD_STATE_SHFT                                    0xf
#define HWIO_USBCTL_DBM_STATES_AHB_CTRL_STATE_BMSK                                 0x6000
#define HWIO_USBCTL_DBM_STATES_AHB_CTRL_STATE_SHFT                                    0xd
#define HWIO_USBCTL_DBM_STATES_AXI_WR_STATE_BMSK                                   0x1c00
#define HWIO_USBCTL_DBM_STATES_AXI_WR_STATE_SHFT                                      0xa
#define HWIO_USBCTL_DBM_STATES_AXI_RD_STATE_BMSK                                    0x380
#define HWIO_USBCTL_DBM_STATES_AXI_RD_STATE_SHFT                                      0x7
#define HWIO_USBCTL_DBM_STATES_DEPCMD_STATE_BMSK                                     0x40
#define HWIO_USBCTL_DBM_STATES_DEPCMD_STATE_SHFT                                      0x6
#define HWIO_USBCTL_DBM_STATES_WB_STATE_BMSK                                         0x20
#define HWIO_USBCTL_DBM_STATES_WB_STATE_SHFT                                          0x5
#define HWIO_USBCTL_DBM_STATES_UPDXFER_STATE_BMSK                                    0x10
#define HWIO_USBCTL_DBM_STATES_UPDXFER_STATE_SHFT                                     0x4
#define HWIO_USBCTL_DBM_STATES_TF_STATE_BMSK                                          0xf
#define HWIO_USBCTL_DBM_STATES_TF_STATE_SHFT                                          0x0

#define HWIO_USBCTL_DBM_HW_TRB0_EPn_ADDR(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000220 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_PHYS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000220 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_OFFS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000220 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_RMSK                                       0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_MAXn                                                3
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_POR                                        0x00000000
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_POR_RMSK                                   0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB0_EPn_ADDR(n), HWIO_USBCTL_DBM_HW_TRB0_EPn_RMSK)
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB0_EPn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_HW_TRB_31_0_BMSK                           0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB0_EPn_HW_TRB_31_0_SHFT                                  0x0

#define HWIO_USBCTL_DBM_HW_TRB1_EPn_ADDR(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000230 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_PHYS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000230 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_OFFS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000230 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_RMSK                                       0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_MAXn                                                3
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_POR                                        0x00000000
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_POR_RMSK                                   0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB1_EPn_ADDR(n), HWIO_USBCTL_DBM_HW_TRB1_EPn_RMSK)
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB1_EPn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_HW_TRB_63_32_BMSK                          0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB1_EPn_HW_TRB_63_32_SHFT                                 0x0

#define HWIO_USBCTL_DBM_HW_TRB2_EPn_ADDR(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000240 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_PHYS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000240 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_OFFS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000240 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_RMSK                                       0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_MAXn                                                3
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_POR                                        0x00000000
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_POR_RMSK                                   0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB2_EPn_ADDR(n), HWIO_USBCTL_DBM_HW_TRB2_EPn_RMSK)
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB2_EPn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_HW_TRB_95_64_BMSK                          0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB2_EPn_HW_TRB_95_64_SHFT                                 0x0

#define HWIO_USBCTL_DBM_HW_TRB3_EPn_ADDR(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000250 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_PHYS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000250 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_OFFS(n)                                    (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000250 + 0x4 * (n))
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_RMSK                                       0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_MAXn                                                3
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_POR                                        0x00000000
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_POR_RMSK                                   0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB3_EPn_ADDR(n), HWIO_USBCTL_DBM_HW_TRB3_EPn_RMSK)
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_HW_TRB3_EPn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_HW_TRB_127_96_BMSK                         0xffffffff
#define HWIO_USBCTL_DBM_HW_TRB3_EPn_HW_TRB_127_96_SHFT                                0x0

#define HWIO_USBCTL_DBM_GEVNTADR_LSB_ADDR                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000260)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_PHYS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000260)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_OFFS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000260)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_RMSK                                      0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_POR                                       0x00000000
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_POR_RMSK                                  0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTADR_LSB_ADDR, HWIO_USBCTL_DBM_GEVNTADR_LSB_RMSK)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTADR_LSB_ADDR, m)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_GEVNTADR_LSB_ADDR,v)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_GEVNTADR_LSB_ADDR,m,v,HWIO_USBCTL_DBM_GEVNTADR_LSB_IN)
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_GEVNTADR_LSB_BMSK                         0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_LSB_GEVNTADR_LSB_SHFT                                0x0

#define HWIO_USBCTL_DBM_GEVNTADR_MSB_ADDR                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000264)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_PHYS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000264)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_OFFS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000264)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_RMSK                                      0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_POR                                       0x00000000
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_POR_RMSK                                  0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTADR_MSB_ADDR, HWIO_USBCTL_DBM_GEVNTADR_MSB_RMSK)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTADR_MSB_ADDR, m)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_GEVNTADR_MSB_ADDR,v)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_GEVNTADR_MSB_ADDR,m,v,HWIO_USBCTL_DBM_GEVNTADR_MSB_IN)
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_GEVNTADR_MSB_BMSK                         0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_MSB_GEVNTADR_MSB_SHFT                                0x0

#define HWIO_USBCTL_DBM_GEVNTSIZ_ADDR                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000268)
#define HWIO_USBCTL_DBM_GEVNTSIZ_PHYS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000268)
#define HWIO_USBCTL_DBM_GEVNTSIZ_OFFS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000268)
#define HWIO_USBCTL_DBM_GEVNTSIZ_RMSK                                              0xffff
#define HWIO_USBCTL_DBM_GEVNTSIZ_POR                                           0x00000000
#define HWIO_USBCTL_DBM_GEVNTSIZ_POR_RMSK                                      0xffffffff
#define HWIO_USBCTL_DBM_GEVNTSIZ_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTSIZ_ADDR, HWIO_USBCTL_DBM_GEVNTSIZ_RMSK)
#define HWIO_USBCTL_DBM_GEVNTSIZ_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTSIZ_ADDR, m)
#define HWIO_USBCTL_DBM_GEVNTSIZ_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_GEVNTSIZ_ADDR,v)
#define HWIO_USBCTL_DBM_GEVNTSIZ_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_GEVNTSIZ_ADDR,m,v,HWIO_USBCTL_DBM_GEVNTSIZ_IN)
#define HWIO_USBCTL_DBM_GEVNTSIZ_GEVNTSIZ_BMSK                                     0xffff
#define HWIO_USBCTL_DBM_GEVNTSIZ_GEVNTSIZ_SHFT                                        0x0

#define HWIO_USBCTL_DBM_DATA_FIFO_EN_ADDR                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x0000026c)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_PHYS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x0000026c)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_OFFS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x0000026c)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_RMSK                                            0xff
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_POR                                       0x000000ff
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_POR_RMSK                                  0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_EN_ADDR, HWIO_USBCTL_DBM_DATA_FIFO_EN_RMSK)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_EN_ADDR, m)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_DATA_FIFO_EN_ADDR,v)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_FIFO_EN_ADDR,m,v,HWIO_USBCTL_DBM_DATA_FIFO_EN_IN)
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_DBM_DATA_FIFO_SIZE_ENN_BMSK                     0xf0
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_DBM_DATA_FIFO_SIZE_ENN_SHFT                      0x4
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_DBM_DATA_FIFO_ADDR_ENN_BMSK                      0xf
#define HWIO_USBCTL_DBM_DATA_FIFO_EN_DBM_DATA_FIFO_ADDR_ENN_SHFT                      0x0

#define HWIO_USBCTL_DBM_GEVNTADR_ADDR                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000270)
#define HWIO_USBCTL_DBM_GEVNTADR_PHYS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000270)
#define HWIO_USBCTL_DBM_GEVNTADR_OFFS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000270)
#define HWIO_USBCTL_DBM_GEVNTADR_RMSK                                          0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_POR                                           0x00000000
#define HWIO_USBCTL_DBM_GEVNTADR_POR_RMSK                                      0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTADR_ADDR, HWIO_USBCTL_DBM_GEVNTADR_RMSK)
#define HWIO_USBCTL_DBM_GEVNTADR_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_GEVNTADR_ADDR, m)
#define HWIO_USBCTL_DBM_GEVNTADR_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_GEVNTADR_ADDR,v)
#define HWIO_USBCTL_DBM_GEVNTADR_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_GEVNTADR_ADDR,m,v,HWIO_USBCTL_DBM_GEVNTADR_IN)
#define HWIO_USBCTL_DBM_GEVNTADR_GEVNTADR_BMSK                                 0xffffffff
#define HWIO_USBCTL_DBM_GEVNTADR_GEVNTADR_SHFT                                        0x0

#define HWIO_USBCTL_DBM_PIPE_CFG_ADDR                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000274)
#define HWIO_USBCTL_DBM_PIPE_CFG_PHYS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000274)
#define HWIO_USBCTL_DBM_PIPE_CFG_OFFS                                          (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000274)
#define HWIO_USBCTL_DBM_PIPE_CFG_RMSK                                                0xff
#define HWIO_USBCTL_DBM_PIPE_CFG_POR                                           0x000000e4
#define HWIO_USBCTL_DBM_PIPE_CFG_POR_RMSK                                      0xffffffff
#define HWIO_USBCTL_DBM_PIPE_CFG_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_PIPE_CFG_ADDR, HWIO_USBCTL_DBM_PIPE_CFG_RMSK)
#define HWIO_USBCTL_DBM_PIPE_CFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_PIPE_CFG_ADDR, m)
#define HWIO_USBCTL_DBM_PIPE_CFG_OUT(v)      \
        out_dword(HWIO_USBCTL_DBM_PIPE_CFG_ADDR,v)
#define HWIO_USBCTL_DBM_PIPE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_PIPE_CFG_ADDR,m,v,HWIO_USBCTL_DBM_PIPE_CFG_IN)
#define HWIO_USBCTL_DBM_PIPE_CFG_DBM_PIPE_CFGN_BMSK                                  0xff
#define HWIO_USBCTL_DBM_PIPE_CFG_DBM_PIPE_CFGN_SHFT                                   0x0

#define HWIO_USBCTL_INACTIVITY_TIMER_ADDR                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000278)
#define HWIO_USBCTL_INACTIVITY_TIMER_PHYS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000278)
#define HWIO_USBCTL_INACTIVITY_TIMER_OFFS                                      (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000278)
#define HWIO_USBCTL_INACTIVITY_TIMER_RMSK                                      0xffffffff
#define HWIO_USBCTL_INACTIVITY_TIMER_POR                                       0x00000000
#define HWIO_USBCTL_INACTIVITY_TIMER_POR_RMSK                                  0xffffffff
#define HWIO_USBCTL_INACTIVITY_TIMER_IN          \
        in_dword_masked(HWIO_USBCTL_INACTIVITY_TIMER_ADDR, HWIO_USBCTL_INACTIVITY_TIMER_RMSK)
#define HWIO_USBCTL_INACTIVITY_TIMER_INM(m)      \
        in_dword_masked(HWIO_USBCTL_INACTIVITY_TIMER_ADDR, m)
#define HWIO_USBCTL_INACTIVITY_TIMER_OUT(v)      \
        out_dword(HWIO_USBCTL_INACTIVITY_TIMER_ADDR,v)
#define HWIO_USBCTL_INACTIVITY_TIMER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_INACTIVITY_TIMER_ADDR,m,v,HWIO_USBCTL_INACTIVITY_TIMER_IN)
#define HWIO_USBCTL_INACTIVITY_TIMER_TIMER_ENABLE_BMSK                         0x80000000
#define HWIO_USBCTL_INACTIVITY_TIMER_TIMER_ENABLE_SHFT                               0x1f
#define HWIO_USBCTL_INACTIVITY_TIMER_TIMER_LIMIT_BMSK                          0x7fffffff
#define HWIO_USBCTL_INACTIVITY_TIMER_TIMER_LIMIT_SHFT                                 0x0

#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_ADDR(n)                                (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000280 + 0x4 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_PHYS(n)                                (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000280 + 0x4 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_OFFS(n)                                (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000280 + 0x4 * (n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_RMSK                                   0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_MAXn                                            3
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_POR                                    0x00000000
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_POR_RMSK                               0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_ADDR(n), HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_RMSK)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_ADDR(n), mask)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_ADDR(n),val)
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_ADDR(n),mask,val,HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_INI(n))
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_DATA_FIFO_ADDR_BMSK                    0xffffffff
#define HWIO_USBCTL_DBM_DATA_FIFO_ADDRn_DATA_FIFO_ADDR_SHFT                           0x0

#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_ADDR                                     (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000290)
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_PHYS                                     (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000290)
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_OFFS                                     (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000290)
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_RMSK                                          0x3ff
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_POR                                      0x00000000
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_POR_RMSK                                 0xffffffff
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_IN          \
        in_dword_masked(HWIO_USBCTL_DBM_TRB_TRACE_CNT_ADDR, HWIO_USBCTL_DBM_TRB_TRACE_CNT_RMSK)
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBM_TRB_TRACE_CNT_ADDR, m)
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_TRB_TRACE_CNTR_BMSK                           0x3ff
#define HWIO_USBCTL_DBM_TRB_TRACE_CNT_TRB_TRACE_CNTR_SHFT                             0x0

#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_ADDR                                  (USBCTL_USB30_DBM_REGFILE_REG_BASE      + 0x00000294)
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_PHYS                                  (USBCTL_USB30_DBM_REGFILE_REG_BASE_PHYS + 0x00000294)
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_OFFS                                  (USBCTL_USB30_DBM_REGFILE_REG_BASE_OFFS + 0x00000294)
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_RMSK                                         0x1
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_POR                                   0x00000000
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_POR_RMSK                              0xffffffff
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_IN          \
        in_dword_masked(HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_ADDR, HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_RMSK)
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_INM(m)      \
        in_dword_masked(HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_ADDR, m)
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_EP_FIFO_OVERRUN_STAT_BMSK                    0x1
#define HWIO_USBCTL_EP_FIFO_OVERRUN_ADDR_EP_FIFO_OVERRUN_STAT_SHFT                    0x0

/*----------------------------------------------------------------------------
 * MODULE: USBCTL_USB30_QSCRATCH
 *--------------------------------------------------------------------------*/

#define USBCTL_USB30_QSCRATCH_REG_BASE                                                 (USB20S_BASE      + 0x000f8800)
#define USBCTL_USB30_QSCRATCH_REG_BASE_PHYS                                            (USB20S_BASE_PHYS + 0x000f8800)
#define USBCTL_USB30_QSCRATCH_REG_BASE_OFFS                                            0x000f8800

#define HWIO_USBCTL_IPCAT_REG_ADDR                                                     (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000000)
#define HWIO_USBCTL_IPCAT_REG_PHYS                                                     (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000000)
#define HWIO_USBCTL_IPCAT_REG_OFFS                                                     (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000000)
#define HWIO_USBCTL_IPCAT_REG_RMSK                                                     0xffffffff
#define HWIO_USBCTL_IPCAT_REG_POR                                                      0x200d0001
#define HWIO_USBCTL_IPCAT_REG_POR_RMSK                                                 0xffffffff
#define HWIO_USBCTL_IPCAT_REG_IN          \
        in_dword_masked(HWIO_USBCTL_IPCAT_REG_ADDR, HWIO_USBCTL_IPCAT_REG_RMSK)
#define HWIO_USBCTL_IPCAT_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_IPCAT_REG_ADDR, m)
#define HWIO_USBCTL_IPCAT_REG_MAJOR_BMSK                                               0xf0000000
#define HWIO_USBCTL_IPCAT_REG_MAJOR_SHFT                                                     0x1c
#define HWIO_USBCTL_IPCAT_REG_MINOR_BMSK                                                0xfff0000
#define HWIO_USBCTL_IPCAT_REG_MINOR_SHFT                                                     0x10
#define HWIO_USBCTL_IPCAT_REG_STEP_BMSK                                                    0xffff
#define HWIO_USBCTL_IPCAT_REG_STEP_SHFT                                                       0x0

#define HWIO_USBCTL_CTRL_REG_ADDR                                                      (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000004)
#define HWIO_USBCTL_CTRL_REG_PHYS                                                      (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000004)
#define HWIO_USBCTL_CTRL_REG_OFFS                                                      (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000004)
#define HWIO_USBCTL_CTRL_REG_RMSK                                                           0x3ff
#define HWIO_USBCTL_CTRL_REG_POR                                                       0x00000190
#define HWIO_USBCTL_CTRL_REG_POR_RMSK                                                  0xffffffff
#define HWIO_USBCTL_CTRL_REG_IN          \
        in_dword_masked(HWIO_USBCTL_CTRL_REG_ADDR, HWIO_USBCTL_CTRL_REG_RMSK)
#define HWIO_USBCTL_CTRL_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_CTRL_REG_ADDR, m)
#define HWIO_USBCTL_CTRL_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_CTRL_REG_ADDR,v)
#define HWIO_USBCTL_CTRL_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_CTRL_REG_ADDR,m,v,HWIO_USBCTL_CTRL_REG_IN)
#define HWIO_USBCTL_CTRL_REG_BC_XCVR_SELECT_BMSK                                            0x300
#define HWIO_USBCTL_CTRL_REG_BC_XCVR_SELECT_SHFT                                              0x8
#define HWIO_USBCTL_CTRL_REG_BC_TERM_SELECT_BMSK                                             0x80
#define HWIO_USBCTL_CTRL_REG_BC_TERM_SELECT_SHFT                                              0x7
#define HWIO_USBCTL_CTRL_REG_BC_TX_VALID_BMSK                                                0x40
#define HWIO_USBCTL_CTRL_REG_BC_TX_VALID_SHFT                                                 0x6
#define HWIO_USBCTL_CTRL_REG_BC_OPMODE_BMSK                                                  0x30
#define HWIO_USBCTL_CTRL_REG_BC_OPMODE_SHFT                                                   0x4
#define HWIO_USBCTL_CTRL_REG_BC_DMPULLDOWN_BMSK                                               0x8
#define HWIO_USBCTL_CTRL_REG_BC_DMPULLDOWN_SHFT                                               0x3
#define HWIO_USBCTL_CTRL_REG_BC_DPPULLDOWN_BMSK                                               0x4
#define HWIO_USBCTL_CTRL_REG_BC_DPPULLDOWN_SHFT                                               0x2
#define HWIO_USBCTL_CTRL_REG_BC_IDPULLUP_BMSK                                                 0x2
#define HWIO_USBCTL_CTRL_REG_BC_IDPULLUP_SHFT                                                 0x1
#define HWIO_USBCTL_CTRL_REG_BC_SEL_BMSK                                                      0x1
#define HWIO_USBCTL_CTRL_REG_BC_SEL_SHFT                                                      0x0

#define HWIO_USBCTL_GENERAL_CFG_ADDR                                                   (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000008)
#define HWIO_USBCTL_GENERAL_CFG_PHYS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000008)
#define HWIO_USBCTL_GENERAL_CFG_OFFS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000008)
#define HWIO_USBCTL_GENERAL_CFG_RMSK                                                        0x30f
#define HWIO_USBCTL_GENERAL_CFG_POR                                                    0x00000004
#define HWIO_USBCTL_GENERAL_CFG_POR_RMSK                                               0xffffffff
#define HWIO_USBCTL_GENERAL_CFG_IN          \
        in_dword_masked(HWIO_USBCTL_GENERAL_CFG_ADDR, HWIO_USBCTL_GENERAL_CFG_RMSK)
#define HWIO_USBCTL_GENERAL_CFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_GENERAL_CFG_ADDR, m)
#define HWIO_USBCTL_GENERAL_CFG_OUT(v)      \
        out_dword(HWIO_USBCTL_GENERAL_CFG_ADDR,v)
#define HWIO_USBCTL_GENERAL_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_GENERAL_CFG_ADDR,m,v,HWIO_USBCTL_GENERAL_CFG_IN)
#define HWIO_USBCTL_GENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_BMSK                                 0x200
#define HWIO_USBCTL_GENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_SHFT                                   0x9
#define HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK                                      0x100
#define HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_DIS_SHFT                                        0x8
#define HWIO_USBCTL_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK                                       0x8
#define HWIO_USBCTL_GENERAL_CFG_PIPE3_PHYSTATUS_SW_SHFT                                       0x3
#define HWIO_USBCTL_GENERAL_CFG_QSRAM_EN_BMSK                                                 0x4
#define HWIO_USBCTL_GENERAL_CFG_QSRAM_EN_SHFT                                                 0x2
#define HWIO_USBCTL_GENERAL_CFG_DBM_EN_BMSK                                                   0x2
#define HWIO_USBCTL_GENERAL_CFG_DBM_EN_SHFT                                                   0x1
#define HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK                                        0x1
#define HWIO_USBCTL_GENERAL_CFG_PIPE_UTMI_CLK_SEL_SHFT                                        0x0

#define HWIO_USBCTL_RAM1_REG_ADDR                                                      (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x0000000c)
#define HWIO_USBCTL_RAM1_REG_PHYS                                                      (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x0000000c)
#define HWIO_USBCTL_RAM1_REG_OFFS                                                      (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x0000000c)
#define HWIO_USBCTL_RAM1_REG_RMSK                                                             0x5
#define HWIO_USBCTL_RAM1_REG_POR                                                       0x00000000
#define HWIO_USBCTL_RAM1_REG_POR_RMSK                                                  0xffffffff
#define HWIO_USBCTL_RAM1_REG_IN          \
        in_dword_masked(HWIO_USBCTL_RAM1_REG_ADDR, HWIO_USBCTL_RAM1_REG_RMSK)
#define HWIO_USBCTL_RAM1_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_RAM1_REG_ADDR, m)
#define HWIO_USBCTL_RAM1_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_RAM1_REG_ADDR,v)
#define HWIO_USBCTL_RAM1_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_RAM1_REG_ADDR,m,v,HWIO_USBCTL_RAM1_REG_IN)
#define HWIO_USBCTL_RAM1_REG_RAM13_EN_BMSK                                                    0x4
#define HWIO_USBCTL_RAM1_REG_RAM13_EN_SHFT                                                    0x2
#define HWIO_USBCTL_RAM1_REG_RAM11_EN_BMSK                                                    0x1
#define HWIO_USBCTL_RAM1_REG_RAM11_EN_SHFT                                                    0x0

#define HWIO_USBCTL_HS_PHY_CTRL_ADDR                                                   (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000010)
#define HWIO_USBCTL_HS_PHY_CTRL_PHYS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000010)
#define HWIO_USBCTL_HS_PHY_CTRL_OFFS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000010)
#define HWIO_USBCTL_HS_PHY_CTRL_RMSK                                                   0x50100000
#define HWIO_USBCTL_HS_PHY_CTRL_POR                                                    0x50000000
#define HWIO_USBCTL_HS_PHY_CTRL_POR_RMSK                                               0xffffffff
#define HWIO_USBCTL_HS_PHY_CTRL_IN          \
        in_dword_masked(HWIO_USBCTL_HS_PHY_CTRL_ADDR, HWIO_USBCTL_HS_PHY_CTRL_RMSK)
#define HWIO_USBCTL_HS_PHY_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBCTL_HS_PHY_CTRL_ADDR, m)
#define HWIO_USBCTL_HS_PHY_CTRL_OUT(v)      \
        out_dword(HWIO_USBCTL_HS_PHY_CTRL_ADDR,v)
#define HWIO_USBCTL_HS_PHY_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_HS_PHY_CTRL_ADDR,m,v,HWIO_USBCTL_HS_PHY_CTRL_IN)
#define HWIO_USBCTL_HS_PHY_CTRL_SLP_SUSP_PHY_CB_BMSK                                   0x40000000
#define HWIO_USBCTL_HS_PHY_CTRL_SLP_SUSP_PHY_CB_SHFT                                         0x1e
#define HWIO_USBCTL_HS_PHY_CTRL_SW_SESSVLD_SEL_BMSK                                    0x10000000
#define HWIO_USBCTL_HS_PHY_CTRL_SW_SESSVLD_SEL_SHFT                                          0x1c
#define HWIO_USBCTL_HS_PHY_CTRL_UTMI_OTG_VBUS_VALID_BMSK                                 0x100000
#define HWIO_USBCTL_HS_PHY_CTRL_UTMI_OTG_VBUS_VALID_SHFT                                     0x14

#define HWIO_USBCTL_CHARGING_DET_OUTPUT_ADDR                                           (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x0000001c)
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_PHYS                                           (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x0000001c)
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_OFFS                                           (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x0000001c)
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_RMSK                                                0x700
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_POR                                            0x00000000
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_POR_RMSK                                       0xffffffff
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_IN          \
        in_dword_masked(HWIO_USBCTL_CHARGING_DET_OUTPUT_ADDR, HWIO_USBCTL_CHARGING_DET_OUTPUT_RMSK)
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_INM(m)      \
        in_dword_masked(HWIO_USBCTL_CHARGING_DET_OUTPUT_ADDR, m)
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_UTMI_LINESTATE_SYNC_MODE_BMSK                       0x400
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_UTMI_LINESTATE_SYNC_MODE_SHFT                         0xa
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_LINESTATE_BMSK                                      0x300
#define HWIO_USBCTL_CHARGING_DET_OUTPUT_LINESTATE_SHFT                                        0x8

#define HWIO_USBCTL_ALT_INTERRUPT_EN_ADDR                                              (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000020)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_PHYS                                              (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000020)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_OFFS                                              (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000020)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_RMSK                                                  0x1000
#define HWIO_USBCTL_ALT_INTERRUPT_EN_POR                                               0x00000000
#define HWIO_USBCTL_ALT_INTERRUPT_EN_POR_RMSK                                          0xffffffff
#define HWIO_USBCTL_ALT_INTERRUPT_EN_IN          \
        in_dword_masked(HWIO_USBCTL_ALT_INTERRUPT_EN_ADDR, HWIO_USBCTL_ALT_INTERRUPT_EN_RMSK)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_INM(m)      \
        in_dword_masked(HWIO_USBCTL_ALT_INTERRUPT_EN_ADDR, m)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_OUT(v)      \
        out_dword(HWIO_USBCTL_ALT_INTERRUPT_EN_ADDR,v)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_ALT_INTERRUPT_EN_ADDR,m,v,HWIO_USBCTL_ALT_INTERRUPT_EN_IN)
#define HWIO_USBCTL_ALT_INTERRUPT_EN_LINESTATE_INTEN_BMSK                                  0x1000
#define HWIO_USBCTL_ALT_INTERRUPT_EN_LINESTATE_INTEN_SHFT                                     0xc

#define HWIO_USBCTL_HS_PHY_IRQ_STAT_ADDR                                               (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000024)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_PHYS                                               (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000024)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_OFFS                                               (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000024)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_RMSK                                                   0x1000
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_POR                                                0x00000000
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_IN          \
        in_dword_masked(HWIO_USBCTL_HS_PHY_IRQ_STAT_ADDR, HWIO_USBCTL_HS_PHY_IRQ_STAT_RMSK)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_INM(m)      \
        in_dword_masked(HWIO_USBCTL_HS_PHY_IRQ_STAT_ADDR, m)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_OUT(v)      \
        out_dword(HWIO_USBCTL_HS_PHY_IRQ_STAT_ADDR,v)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_HS_PHY_IRQ_STAT_ADDR,m,v,HWIO_USBCTL_HS_PHY_IRQ_STAT_IN)
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_LINESTATE_INTLCH_BMSK                                  0x1000
#define HWIO_USBCTL_HS_PHY_IRQ_STAT_LINESTATE_INTLCH_SHFT                                     0xc

#define HWIO_USBCTL_CGCTL_REG_ADDR                                                     (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000028)
#define HWIO_USBCTL_CGCTL_REG_PHYS                                                     (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000028)
#define HWIO_USBCTL_CGCTL_REG_OFFS                                                     (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000028)
#define HWIO_USBCTL_CGCTL_REG_RMSK                                                          0x1e6
#define HWIO_USBCTL_CGCTL_REG_POR                                                      0x00000000
#define HWIO_USBCTL_CGCTL_REG_POR_RMSK                                                 0xffffffff
#define HWIO_USBCTL_CGCTL_REG_IN          \
        in_dword_masked(HWIO_USBCTL_CGCTL_REG_ADDR, HWIO_USBCTL_CGCTL_REG_RMSK)
#define HWIO_USBCTL_CGCTL_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_CGCTL_REG_ADDR, m)
#define HWIO_USBCTL_CGCTL_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_CGCTL_REG_ADDR,v)
#define HWIO_USBCTL_CGCTL_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_CGCTL_REG_ADDR,m,v,HWIO_USBCTL_CGCTL_REG_IN)
#define HWIO_USBCTL_CGCTL_REG_DBM_REGFILE_CGC_EN_N_BMSK                                     0x100
#define HWIO_USBCTL_CGCTL_REG_DBM_REGFILE_CGC_EN_N_SHFT                                       0x8
#define HWIO_USBCTL_CGCTL_REG_QSCRATCH_CLK_CGC_EN_N_BMSK                                     0x80
#define HWIO_USBCTL_CGCTL_REG_QSCRATCH_CLK_CGC_EN_N_SHFT                                      0x7
#define HWIO_USBCTL_CGCTL_REG_LSP_DBC_CGC_EN_N_BMSK                                          0x40
#define HWIO_USBCTL_CGCTL_REG_LSP_DBC_CGC_EN_N_SHFT                                           0x6
#define HWIO_USBCTL_CGCTL_REG_LSP_CGC_EN_N_BMSK                                              0x20
#define HWIO_USBCTL_CGCTL_REG_LSP_CGC_EN_N_SHFT                                               0x5
#define HWIO_USBCTL_CGCTL_REG_BAM_CGC_EN_BMSK                                                 0x4
#define HWIO_USBCTL_CGCTL_REG_BAM_CGC_EN_SHFT                                                 0x2
#define HWIO_USBCTL_CGCTL_REG_DBM_FSM_EN_BMSK                                                 0x2
#define HWIO_USBCTL_CGCTL_REG_DBM_FSM_EN_SHFT                                                 0x1

#define HWIO_USBCTL_DBG_BUS_REG_ADDR                                                   (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x0000002c)
#define HWIO_USBCTL_DBG_BUS_REG_PHYS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x0000002c)
#define HWIO_USBCTL_DBG_BUS_REG_OFFS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x0000002c)
#define HWIO_USBCTL_DBG_BUS_REG_RMSK                                                    0xffff1f1
#define HWIO_USBCTL_DBG_BUS_REG_POR                                                    0x00000000
#define HWIO_USBCTL_DBG_BUS_REG_POR_RMSK                                               0xffffffff
#define HWIO_USBCTL_DBG_BUS_REG_IN          \
        in_dword_masked(HWIO_USBCTL_DBG_BUS_REG_ADDR, HWIO_USBCTL_DBG_BUS_REG_RMSK)
#define HWIO_USBCTL_DBG_BUS_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBG_BUS_REG_ADDR, m)
#define HWIO_USBCTL_DBG_BUS_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_DBG_BUS_REG_ADDR,v)
#define HWIO_USBCTL_DBG_BUS_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_DBG_BUS_REG_ADDR,m,v,HWIO_USBCTL_DBG_BUS_REG_IN)
#define HWIO_USBCTL_DBG_BUS_REG_GENERAL_DBG_SEL_BMSK                                    0xf000000
#define HWIO_USBCTL_DBG_BUS_REG_GENERAL_DBG_SEL_SHFT                                         0x18
#define HWIO_USBCTL_DBG_BUS_REG_DBM_DBG_EN_BMSK                                          0xf00000
#define HWIO_USBCTL_DBG_BUS_REG_DBM_DBG_EN_SHFT                                              0x14
#define HWIO_USBCTL_DBG_BUS_REG_DBM_DBG_SEL_BMSK                                          0xff000
#define HWIO_USBCTL_DBG_BUS_REG_DBM_DBG_SEL_SHFT                                              0xc
#define HWIO_USBCTL_DBG_BUS_REG_GSI_IF_DBG_SEL_BMSK                                         0x1f0
#define HWIO_USBCTL_DBG_BUS_REG_GSI_IF_DBG_SEL_SHFT                                           0x4
#define HWIO_USBCTL_DBG_BUS_REG_CTRL_DBG_SEL_BMSK                                             0x1
#define HWIO_USBCTL_DBG_BUS_REG_CTRL_DBG_SEL_SHFT                                             0x0

#define HWIO_USBCTL_DBG_BUS_DATA_ADDR                                                  (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000034)
#define HWIO_USBCTL_DBG_BUS_DATA_PHYS                                                  (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000034)
#define HWIO_USBCTL_DBG_BUS_DATA_OFFS                                                  (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000034)
#define HWIO_USBCTL_DBG_BUS_DATA_RMSK                                                  0xffffffff
#define HWIO_USBCTL_DBG_BUS_DATA_POR                                                   0x00000000
#define HWIO_USBCTL_DBG_BUS_DATA_POR_RMSK                                              0xffffffff
#define HWIO_USBCTL_DBG_BUS_DATA_IN          \
        in_dword_masked(HWIO_USBCTL_DBG_BUS_DATA_ADDR, HWIO_USBCTL_DBG_BUS_DATA_RMSK)
#define HWIO_USBCTL_DBG_BUS_DATA_INM(m)      \
        in_dword_masked(HWIO_USBCTL_DBG_BUS_DATA_ADDR, m)
#define HWIO_USBCTL_DBG_BUS_DATA_DBG_BUS_BMSK                                          0xffffffff
#define HWIO_USBCTL_DBG_BUS_DATA_DBG_BUS_SHFT                                                 0x0

#define HWIO_USBCTL_SS_PHY_CTRL_ADDR                                                   (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000030)
#define HWIO_USBCTL_SS_PHY_CTRL_PHYS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000030)
#define HWIO_USBCTL_SS_PHY_CTRL_OFFS                                                   (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000030)
#define HWIO_USBCTL_SS_PHY_CTRL_RMSK                                                    0x1000000
#define HWIO_USBCTL_SS_PHY_CTRL_POR                                                    0x00000000
#define HWIO_USBCTL_SS_PHY_CTRL_POR_RMSK                                               0xffffffff
#define HWIO_USBCTL_SS_PHY_CTRL_IN          \
        in_dword_masked(HWIO_USBCTL_SS_PHY_CTRL_ADDR, HWIO_USBCTL_SS_PHY_CTRL_RMSK)
#define HWIO_USBCTL_SS_PHY_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBCTL_SS_PHY_CTRL_ADDR, m)
#define HWIO_USBCTL_SS_PHY_CTRL_OUT(v)      \
        out_dword(HWIO_USBCTL_SS_PHY_CTRL_ADDR,v)
#define HWIO_USBCTL_SS_PHY_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_SS_PHY_CTRL_ADDR,m,v,HWIO_USBCTL_SS_PHY_CTRL_IN)
#define HWIO_USBCTL_SS_PHY_CTRL_LANE0_PWR_PRESENT_BMSK                                  0x1000000
#define HWIO_USBCTL_SS_PHY_CTRL_LANE0_PWR_PRESENT_SHFT                                       0x18

#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_ADDR                                             (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000058)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_PHYS                                             (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000058)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OFFS                                             (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000058)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_RMSK                                              0x1fcf03c
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POR                                              0x00000000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POR_RMSK                                         0xffffffff
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN          \
        in_dword_masked(HWIO_USBCTL_PWR_EVNT_IRQ_STAT_ADDR, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_RMSK)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_INM(m)      \
        in_dword_masked(HWIO_USBCTL_PWR_EVNT_IRQ_STAT_ADDR, m)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OUT(v)      \
        out_dword(HWIO_USBCTL_PWR_EVNT_IRQ_STAT_ADDR,v)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_PWR_EVNT_IRQ_STAT_ADDR,m,v,HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN)
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_L1_EXIT_IRQ_STAT_BMSK                   0x1000000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_L1_EXIT_IRQ_STAT_SHFT                        0x18
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_ERROR_IRQ_STAT_BMSK                      0x800000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_ERROR_IRQ_STAT_SHFT                          0x17
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_L1_SUSPEND_OUT_IRQ_STAT_BMSK                       0x400000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_L1_SUSPEND_OUT_IRQ_STAT_SHFT                           0x16
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_RX_ELECIDLE_ASYNC_IRQ_STAT_BMSK            0x200000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_RX_ELECIDLE_ASYNC_IRQ_STAT_SHFT                0x15
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_ASYNC_IRQ_STAT_BMSK                     0x100000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_ASYNC_IRQ_STAT_SHFT                         0x14
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POWERDOWN_OUT_P3_ASYNC_IRQ_STAT_BMSK                0x80000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POWERDOWN_OUT_P3_ASYNC_IRQ_STAT_SHFT                   0x13
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_LINESTATE_INTSTS_BMSK                         0x40000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_LINESTATE_INTSTS_SHFT                            0x12
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_DBM_EP_FIFO_OVERRUN_STAT_BMSK                        0x8000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_DBM_EP_FIFO_OVERRUN_STAT_SHFT                           0xf
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_PME_IRQ_STAT_BMSK                                    0x4000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_PME_IRQ_STAT_SHFT                                       0xe
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L1_IRQ_STAT_BMSK                             0x2000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L1_IRQ_STAT_SHFT                                0xd
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_RX_ELECIDLE_IRQ_STAT_BMSK                    0x1000
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_RX_ELECIDLE_IRQ_STAT_SHFT                       0xc
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK                               0x20
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_SHFT                                0x5
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK                                0x10
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_SHFT                                 0x4
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POWERDOWN_OUT_P3_IRQ_STAT_BMSK                          0x8
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POWERDOWN_OUT_P3_IRQ_STAT_SHFT                          0x3
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POWERDOWN_IN_P3_IRQ_STAT_BMSK                           0x4
#define HWIO_USBCTL_PWR_EVNT_IRQ_STAT_POWERDOWN_IN_P3_IRQ_STAT_SHFT                           0x2

#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_ADDR                                             (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x0000005c)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_PHYS                                             (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x0000005c)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OFFS                                             (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x0000005c)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_RMSK                                              0x1fcf03c
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POR                                              0x00000000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POR_RMSK                                         0xffffffff
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_IN          \
        in_dword_masked(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_ADDR, HWIO_USBCTL_PWR_EVNT_IRQ_MASK_RMSK)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_INM(m)      \
        in_dword_masked(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_ADDR, m)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OUT(v)      \
        out_dword(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_ADDR,v)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_ADDR,m,v,HWIO_USBCTL_PWR_EVNT_IRQ_MASK_IN)
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_USB30_GSI_L1_EXIT_IRQ_MASK_BMSK                   0x1000000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_USB30_GSI_L1_EXIT_IRQ_MASK_SHFT                        0x18
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_USB30_GSI_ERROR_IRQ_MASK_BMSK                      0x800000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_USB30_GSI_ERROR_IRQ_MASK_SHFT                          0x17
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_L1_SUSPEND_OUT_IRQ_MASK_BMSK                       0x400000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_L1_SUSPEND_OUT_IRQ_MASK_SHFT                           0x16
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_RX_ELECIDLE_ASYNC_IRQ_MASK_BMSK            0x200000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_RX_ELECIDLE_ASYNC_IRQ_MASK_SHFT                0x15
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_ASYNC_IRQ_MASK_BMSK                     0x100000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_ASYNC_IRQ_MASK_SHFT                         0x14
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POWERDOWN_OUT_P3_ASYNC_IRQ_MASK_BMSK                0x80000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POWERDOWN_OUT_P3_ASYNC_IRQ_MASK_SHFT                   0x13
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_USB30_LINESTATE_MASK_BMSK                           0x40000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_USB30_LINESTATE_MASK_SHFT                              0x12
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_DBM_EP_FIFO_OVERRUN_MASK_BMSK                        0x8000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_DBM_EP_FIFO_OVERRUN_MASK_SHFT                           0xf
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_PME_IRQ_MASK_BMSK                                    0x4000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_PME_IRQ_MASK_SHFT                                       0xe
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L1_IRQ_MASK_BMSK                             0x2000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L1_IRQ_MASK_SHFT                                0xd
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_RX_ELECIDLE_IRQ_MASK_BMSK                    0x1000
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_RX_ELECIDLE_IRQ_MASK_SHFT                       0xc
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_BMSK                               0x20
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_SHFT                                0x5
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_IN_L2_IRQ_MASK_BMSK                                0x10
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_IN_L2_IRQ_MASK_SHFT                                 0x4
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POWERDOWN_OUT_P3_IRQ_MASK_BMSK                          0x8
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POWERDOWN_OUT_P3_IRQ_MASK_SHFT                          0x3
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POWERDOWN_IN_P3_IRQ_MASK_BMSK                           0x4
#define HWIO_USBCTL_PWR_EVNT_IRQ_MASK_POWERDOWN_IN_P3_IRQ_MASK_SHFT                           0x2

#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_ADDR                                            (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000060)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_PHYS                                            (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000060)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_OFFS                                            (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000060)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_RMSK                                                 0x131
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_POR                                             0x00000001
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_POR_RMSK                                        0xffffffff
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_IN          \
        in_dword_masked(HWIO_USBCTL_HW_SW_EVT_CTRL_REG_ADDR, HWIO_USBCTL_HW_SW_EVT_CTRL_REG_RMSK)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_HW_SW_EVT_CTRL_REG_ADDR, m)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_HW_SW_EVT_CTRL_REG_ADDR,v)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_HW_SW_EVT_CTRL_REG_ADDR,m,v,HWIO_USBCTL_HW_SW_EVT_CTRL_REG_IN)
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_SW_EVT_MUX_SEL_BMSK                                  0x100
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_SW_EVT_MUX_SEL_SHFT                                    0x8
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_HW_EVT_MUX_CTRL_BMSK                                  0x30
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_HW_EVT_MUX_CTRL_SHFT                                   0x4
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_EVENT_BUS_HALT_BMSK                                    0x1
#define HWIO_USBCTL_HW_SW_EVT_CTRL_REG_EVENT_BUS_HALT_SHFT                                    0x0

#define HWIO_USBCTL_FLADJ_30MHZ_REG_ADDR                                               (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000068)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_PHYS                                               (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000068)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_OFFS                                               (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000068)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_RMSK                                                     0x3f
#define HWIO_USBCTL_FLADJ_30MHZ_REG_POR                                                0x00000020
#define HWIO_USBCTL_FLADJ_30MHZ_REG_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_FLADJ_30MHZ_REG_IN          \
        in_dword_masked(HWIO_USBCTL_FLADJ_30MHZ_REG_ADDR, HWIO_USBCTL_FLADJ_30MHZ_REG_RMSK)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_FLADJ_30MHZ_REG_ADDR, m)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_FLADJ_30MHZ_REG_ADDR,v)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_FLADJ_30MHZ_REG_ADDR,m,v,HWIO_USBCTL_FLADJ_30MHZ_REG_IN)
#define HWIO_USBCTL_FLADJ_30MHZ_REG_FLADJ_30MHZ_VALUE_BMSK                                   0x3f
#define HWIO_USBCTL_FLADJ_30MHZ_REG_FLADJ_30MHZ_VALUE_SHFT                                    0x0

#define HWIO_USBCTL_M_AW_USER_REG_ADDR                                                 (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x0000006c)
#define HWIO_USBCTL_M_AW_USER_REG_PHYS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x0000006c)
#define HWIO_USBCTL_M_AW_USER_REG_OFFS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x0000006c)
#define HWIO_USBCTL_M_AW_USER_REG_RMSK                                                      0x97f
#define HWIO_USBCTL_M_AW_USER_REG_POR                                                  0x00000122
#define HWIO_USBCTL_M_AW_USER_REG_POR_RMSK                                             0xffffffff
#define HWIO_USBCTL_M_AW_USER_REG_IN          \
        in_dword_masked(HWIO_USBCTL_M_AW_USER_REG_ADDR, HWIO_USBCTL_M_AW_USER_REG_RMSK)
#define HWIO_USBCTL_M_AW_USER_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_M_AW_USER_REG_ADDR, m)
#define HWIO_USBCTL_M_AW_USER_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_M_AW_USER_REG_ADDR,v)
#define HWIO_USBCTL_M_AW_USER_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_M_AW_USER_REG_ADDR,m,v,HWIO_USBCTL_M_AW_USER_REG_IN)
#define HWIO_USBCTL_M_AW_USER_REG_AW_MEMTYPE_1_SEL_BMSK                                     0x800
#define HWIO_USBCTL_M_AW_USER_REG_AW_MEMTYPE_1_SEL_SHFT                                       0xb
#define HWIO_USBCTL_M_AW_USER_REG_AW_NOALLOACATE_BMSK                                       0x100
#define HWIO_USBCTL_M_AW_USER_REG_AW_NOALLOACATE_SHFT                                         0x8
#define HWIO_USBCTL_M_AW_USER_REG_AW_MEMTYPE_BMSK                                            0x70
#define HWIO_USBCTL_M_AW_USER_REG_AW_MEMTYPE_SHFT                                             0x4
#define HWIO_USBCTL_M_AW_USER_REG_AW_CACHE_BMSK                                               0xf
#define HWIO_USBCTL_M_AW_USER_REG_AW_CACHE_SHFT                                               0x0

#define HWIO_USBCTL_M_AR_USER_REG_ADDR                                                 (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000070)
#define HWIO_USBCTL_M_AR_USER_REG_PHYS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000070)
#define HWIO_USBCTL_M_AR_USER_REG_OFFS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000070)
#define HWIO_USBCTL_M_AR_USER_REG_RMSK                                                      0x97f
#define HWIO_USBCTL_M_AR_USER_REG_POR                                                  0x00000122
#define HWIO_USBCTL_M_AR_USER_REG_POR_RMSK                                             0xffffffff
#define HWIO_USBCTL_M_AR_USER_REG_IN          \
        in_dword_masked(HWIO_USBCTL_M_AR_USER_REG_ADDR, HWIO_USBCTL_M_AR_USER_REG_RMSK)
#define HWIO_USBCTL_M_AR_USER_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_M_AR_USER_REG_ADDR, m)
#define HWIO_USBCTL_M_AR_USER_REG_OUT(v)      \
        out_dword(HWIO_USBCTL_M_AR_USER_REG_ADDR,v)
#define HWIO_USBCTL_M_AR_USER_REG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_M_AR_USER_REG_ADDR,m,v,HWIO_USBCTL_M_AR_USER_REG_IN)
#define HWIO_USBCTL_M_AR_USER_REG_AR_MEMTYPE_1_SEL_BMSK                                     0x800
#define HWIO_USBCTL_M_AR_USER_REG_AR_MEMTYPE_1_SEL_SHFT                                       0xb
#define HWIO_USBCTL_M_AR_USER_REG_AR_NOALLOACATE_BMSK                                       0x100
#define HWIO_USBCTL_M_AR_USER_REG_AR_NOALLOACATE_SHFT                                         0x8
#define HWIO_USBCTL_M_AR_USER_REG_AR_MEMTYPE_BMSK                                            0x70
#define HWIO_USBCTL_M_AR_USER_REG_AR_MEMTYPE_SHFT                                             0x4
#define HWIO_USBCTL_M_AR_USER_REG_AR_CACHE_BMSK                                               0xf
#define HWIO_USBCTL_M_AR_USER_REG_AR_CACHE_SHFT                                               0x0

#define HWIO_USBCTL_QSCRTCH_REG_n_ADDR(n)                                              (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x000000b4 + 0x4 * (n))
#define HWIO_USBCTL_QSCRTCH_REG_n_PHYS(n)                                              (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x000000b4 + 0x4 * (n))
#define HWIO_USBCTL_QSCRTCH_REG_n_OFFS(n)                                              (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x000000b4 + 0x4 * (n))
#define HWIO_USBCTL_QSCRTCH_REG_n_RMSK                                                 0xffffffff
#define HWIO_USBCTL_QSCRTCH_REG_n_MAXn                                                          4
#define HWIO_USBCTL_QSCRTCH_REG_n_POR                                                  0x00000000
#define HWIO_USBCTL_QSCRTCH_REG_n_POR_RMSK                                             0xffffffff
#define HWIO_USBCTL_QSCRTCH_REG_n_INI(n)        \
        in_dword_masked(HWIO_USBCTL_QSCRTCH_REG_n_ADDR(n), HWIO_USBCTL_QSCRTCH_REG_n_RMSK)
#define HWIO_USBCTL_QSCRTCH_REG_n_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_QSCRTCH_REG_n_ADDR(n), mask)
#define HWIO_USBCTL_QSCRTCH_REG_n_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_QSCRTCH_REG_n_ADDR(n),val)
#define HWIO_USBCTL_QSCRTCH_REG_n_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_QSCRTCH_REG_n_ADDR(n),mask,val,HWIO_USBCTL_QSCRTCH_REG_n_INI(n))
#define HWIO_USBCTL_QSCRTCH_REG_n_QSCRTCH_REG_BMSK                                     0xffffffff
#define HWIO_USBCTL_QSCRTCH_REG_n_QSCRTCH_REG_SHFT                                            0x0

#define HWIO_USBCTL_SS_QMP_PHY_CTRL_ADDR                                               (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x000000f0)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_PHYS                                               (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x000000f0)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_OFFS                                               (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x000000f0)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_RMSK                                                      0x1
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_POR                                                0x00000001
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_POR_RMSK                                           0xffffffff
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_IN          \
        in_dword_masked(HWIO_USBCTL_SS_QMP_PHY_CTRL_ADDR, HWIO_USBCTL_SS_QMP_PHY_CTRL_RMSK)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBCTL_SS_QMP_PHY_CTRL_ADDR, m)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_OUT(v)      \
        out_dword(HWIO_USBCTL_SS_QMP_PHY_CTRL_ADDR,v)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_SS_QMP_PHY_CTRL_ADDR,m,v,HWIO_USBCTL_SS_QMP_PHY_CTRL_IN)
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_USB3QMP_PHY_RESET_EN_BMSK                                 0x1
#define HWIO_USBCTL_SS_QMP_PHY_CTRL_USB3QMP_PHY_RESET_EN_SHFT                                 0x0

#define HWIO_USBCTL_SNPS_CORE_CFG_ADDR                                                 (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x000000f4)
#define HWIO_USBCTL_SNPS_CORE_CFG_PHYS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x000000f4)
#define HWIO_USBCTL_SNPS_CORE_CFG_OFFS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x000000f4)
#define HWIO_USBCTL_SNPS_CORE_CFG_RMSK                                                        0x1
#define HWIO_USBCTL_SNPS_CORE_CFG_POR                                                  0x00000000
#define HWIO_USBCTL_SNPS_CORE_CFG_POR_RMSK                                             0xffffffff
#define HWIO_USBCTL_SNPS_CORE_CFG_IN          \
        in_dword_masked(HWIO_USBCTL_SNPS_CORE_CFG_ADDR, HWIO_USBCTL_SNPS_CORE_CFG_RMSK)
#define HWIO_USBCTL_SNPS_CORE_CFG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_SNPS_CORE_CFG_ADDR, m)
#define HWIO_USBCTL_SNPS_CORE_CFG_OUT(v)      \
        out_dword(HWIO_USBCTL_SNPS_CORE_CFG_ADDR,v)
#define HWIO_USBCTL_SNPS_CORE_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_SNPS_CORE_CFG_ADDR,m,v,HWIO_USBCTL_SNPS_CORE_CFG_IN)
#define HWIO_USBCTL_SNPS_CORE_CFG_SNPS_CORE_PME_EN_BMSK                                       0x1
#define HWIO_USBCTL_SNPS_CORE_CFG_SNPS_CORE_PME_EN_SHFT                                       0x0

#define HWIO_USBCTL_USB30_STS_REG_ADDR                                                 (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x000000f8)
#define HWIO_USBCTL_USB30_STS_REG_PHYS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x000000f8)
#define HWIO_USBCTL_USB30_STS_REG_OFFS                                                 (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x000000f8)
#define HWIO_USBCTL_USB30_STS_REG_RMSK                                                       0x3f
#define HWIO_USBCTL_USB30_STS_REG_POR                                                  0x0000003d
#define HWIO_USBCTL_USB30_STS_REG_POR_RMSK                                             0xffffffff
#define HWIO_USBCTL_USB30_STS_REG_IN          \
        in_dword_masked(HWIO_USBCTL_USB30_STS_REG_ADDR, HWIO_USBCTL_USB30_STS_REG_RMSK)
#define HWIO_USBCTL_USB30_STS_REG_INM(m)      \
        in_dword_masked(HWIO_USBCTL_USB30_STS_REG_ADDR, m)
#define HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_SLEEP_N_BMSK                                    0x20
#define HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_SLEEP_N_SHFT                                     0x5
#define HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_SUSPEND_N_BMSK                                  0x10
#define HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_SUSPEND_N_SHFT                                   0x4
#define HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_L1_SUSPEND_N_BMSK                                0x8
#define HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_L1_SUSPEND_N_SHFT                                0x3
#define HWIO_USBCTL_USB30_STS_REG_USB30_PHY_STATUS_BMSK                                       0x4
#define HWIO_USBCTL_USB30_STS_REG_USB30_PHY_STATUS_SHFT                                       0x2
#define HWIO_USBCTL_USB30_STS_REG_USB30_OPMODE_BMSK                                           0x3
#define HWIO_USBCTL_USB30_STS_REG_USB30_OPMODE_SHFT                                           0x0

#define HWIO_USBCTL_USB30_IMODn_ADDR(n)                                                (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000170 + 0x4 * (n))
#define HWIO_USBCTL_USB30_IMODn_PHYS(n)                                                (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000170 + 0x4 * (n))
#define HWIO_USBCTL_USB30_IMODn_OFFS(n)                                                (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000170 + 0x4 * (n))
#define HWIO_USBCTL_USB30_IMODn_RMSK                                                       0x17ff
#define HWIO_USBCTL_USB30_IMODn_MAXn                                                            1
#define HWIO_USBCTL_USB30_IMODn_POR                                                    0x00000000
#define HWIO_USBCTL_USB30_IMODn_POR_RMSK                                               0xffffffff
#define HWIO_USBCTL_USB30_IMODn_INI(n)        \
        in_dword_masked(HWIO_USBCTL_USB30_IMODn_ADDR(n), HWIO_USBCTL_USB30_IMODn_RMSK)
#define HWIO_USBCTL_USB30_IMODn_INMI(n,mask)    \
        in_dword_masked(HWIO_USBCTL_USB30_IMODn_ADDR(n), mask)
#define HWIO_USBCTL_USB30_IMODn_OUTI(n,val)    \
        out_dword(HWIO_USBCTL_USB30_IMODn_ADDR(n),val)
#define HWIO_USBCTL_USB30_IMODn_OUTMI(n,mask,val) \
        out_dword_masked_ns(HWIO_USBCTL_USB30_IMODn_ADDR(n),mask,val,HWIO_USBCTL_USB30_IMODn_INI(n))
#define HWIO_USBCTL_USB30_IMODn_USB30_IMOD_EE_EN_BMSK                                      0x1000
#define HWIO_USBCTL_USB30_IMODn_USB30_IMOD_EE_EN_SHFT                                         0xc
#define HWIO_USBCTL_USB30_IMODn_USB30_IMOD_EE_CNT_BMSK                                      0x7ff
#define HWIO_USBCTL_USB30_IMODn_USB30_IMOD_EE_CNT_SHFT                                        0x0

#define HWIO_USBCTL_USB30_USEC_CNT_ADDR                                                (USBCTL_USB30_QSCRATCH_REG_BASE      + 0x00000180)
#define HWIO_USBCTL_USB30_USEC_CNT_PHYS                                                (USBCTL_USB30_QSCRATCH_REG_BASE_PHYS + 0x00000180)
#define HWIO_USBCTL_USB30_USEC_CNT_OFFS                                                (USBCTL_USB30_QSCRATCH_REG_BASE_OFFS + 0x00000180)
#define HWIO_USBCTL_USB30_USEC_CNT_RMSK                                                      0xff
#define HWIO_USBCTL_USB30_USEC_CNT_POR                                                 0x00000000
#define HWIO_USBCTL_USB30_USEC_CNT_POR_RMSK                                            0xffffffff
#define HWIO_USBCTL_USB30_USEC_CNT_IN          \
        in_dword_masked(HWIO_USBCTL_USB30_USEC_CNT_ADDR, HWIO_USBCTL_USB30_USEC_CNT_RMSK)
#define HWIO_USBCTL_USB30_USEC_CNT_INM(m)      \
        in_dword_masked(HWIO_USBCTL_USB30_USEC_CNT_ADDR, m)
#define HWIO_USBCTL_USB30_USEC_CNT_OUT(v)      \
        out_dword(HWIO_USBCTL_USB30_USEC_CNT_ADDR,v)
#define HWIO_USBCTL_USB30_USEC_CNT_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBCTL_USB30_USEC_CNT_ADDR,m,v,HWIO_USBCTL_USB30_USEC_CNT_IN)
#define HWIO_USBCTL_USB30_USEC_CNT_USB30_USEC_CNT_BMSK                                       0xff
#define HWIO_USBCTL_USB30_USEC_CNT_USB30_USEC_CNT_SHFT                                        0x0

/*----------------------------------------------------------------------------
 * MODULE: USBPHY_CM_DWC_USB2
 *--------------------------------------------------------------------------*/

#define USBPHY_CM_DWC_USB2_REG_BASE                                                       (CM_DWC_USB2_BASE      + 0x00000000)
#define USBPHY_CM_DWC_USB2_REG_BASE_PHYS                                                  (CM_DWC_USB2_BASE_PHYS + 0x00000000)
#define USBPHY_CM_DWC_USB2_REG_BASE_OFFS                                                  0x00000000

#define HWIO_USBPHY_USB_PHY_REVISION_ID0_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000000)
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000000)
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000000)
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_RMSK                                                   0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_POR                                              0x00000000
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID0_ADDR, HWIO_USBPHY_USB_PHY_REVISION_ID0_RMSK)
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_STEP_7_0_BMSK                                          0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID0_STEP_7_0_SHFT                                           0x0

#define HWIO_USBPHY_USB_PHY_REVISION_ID1_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000004)
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000004)
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000004)
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_RMSK                                                   0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_POR                                              0x00000000
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID1_ADDR, HWIO_USBPHY_USB_PHY_REVISION_ID1_RMSK)
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_STEP_15_8_BMSK                                         0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID1_STEP_15_8_SHFT                                          0x0

#define HWIO_USBPHY_USB_PHY_REVISION_ID2_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000008)
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000008)
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000008)
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_RMSK                                                   0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_POR                                              0x00000003
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID2_ADDR, HWIO_USBPHY_USB_PHY_REVISION_ID2_RMSK)
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_MINOR_7_0_BMSK                                         0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID2_MINOR_7_0_SHFT                                          0x0

#define HWIO_USBPHY_USB_PHY_REVISION_ID3_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000000c)
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000000c)
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000000c)
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_RMSK                                                   0xff
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_POR                                              0x00000010
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID3_ADDR, HWIO_USBPHY_USB_PHY_REVISION_ID3_RMSK)
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REVISION_ID3_ADDR, m)
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_MAJOR_BMSK                                             0xf0
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_MAJOR_SHFT                                              0x4
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_MINOR_11_8_BMSK                                         0xf
#define HWIO_USBPHY_USB_PHY_REVISION_ID3_MINOR_11_8_SHFT                                         0x0

#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_ADDR                                          (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000010)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_PHYS                                          (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000010)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_OFFS                                          (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000010)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_RMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_POR                                           0x00000000
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_POR_RMSK                                      0xffffffff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_ADDR, HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_RMSK)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_DEBUG_BUS_7_0_BMSK                                  0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT0_DEBUG_BUS_7_0_SHFT                                   0x0

#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_ADDR                                          (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000014)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_PHYS                                          (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000014)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_OFFS                                          (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000014)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_RMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_POR                                           0x00000000
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_POR_RMSK                                      0xffffffff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_ADDR, HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_RMSK)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_DEBUG_BUS_15_8_BMSK                                 0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT1_DEBUG_BUS_15_8_SHFT                                  0x0

#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_ADDR                                          (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000018)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_PHYS                                          (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000018)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_OFFS                                          (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000018)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_RMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_POR                                           0x00000000
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_POR_RMSK                                      0xffffffff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_ADDR, HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_RMSK)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_DEBUG_BUS_23_16_BMSK                                0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT2_DEBUG_BUS_23_16_SHFT                                 0x0

#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_ADDR                                          (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000001c)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_PHYS                                          (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000001c)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_OFFS                                          (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000001c)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_RMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_POR                                           0x00000000
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_POR_RMSK                                      0xffffffff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_ADDR, HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_RMSK)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_ADDR, m)
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_DEBUG_BUS_31_24_BMSK                                0xff
#define HWIO_USBPHY_USB_PHY_DEBUG_BUS_STAT3_DEBUG_BUS_31_24_SHFT                                 0x0

#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_ADDR                                       (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000020)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_PHYS                                       (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000020)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_OFFS                                       (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000020)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RMSK                                             0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_POR                                        0x00000003
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_POR_RMSK                                   0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_ADDR, HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RSVD_BMSK                                        0xc0
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RSVD_SHFT                                         0x6
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_PHY_RX_TESTER_STATUS_BMSK                        0x3c
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_PHY_RX_TESTER_STATUS_SHFT                         0x2
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RX_ALL_BAD_BMSK                                   0x2
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RX_ALL_BAD_SHFT                                   0x1
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RX_ALL_GOOD_BMSK                                  0x1
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_OUT_1_RX_ALL_GOOD_SHFT                                  0x0

#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000024)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000024)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000024)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_RMSK                                            0xff
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_POR                                       0x00000000
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_ADDR, HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_RMSK)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_ADDR, m)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_RSVD_BMSK                                       0xf0
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_RSVD_SHFT                                        0x4
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_VDATDETENB0_BMSK                                 0x8
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_VDATDETENB0_SHFT                                 0x3
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_VDATSRCENB0_BMSK                                 0x4
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_VDATSRCENB0_SHFT                                 0x2
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_CHRGSEL0_BMSK                                    0x2
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_CHRGSEL0_SHFT                                    0x1
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_DCDENB0_BMSK                                     0x1
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_OUTPUT_DCDENB0_SHFT                                     0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_ADDR                                        (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000028)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_PHYS                                        (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000028)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_OFFS                                        (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000028)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_RMSK                                               0xf
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_POR                                         0x00000000
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_POR_RMSK                                    0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_TESTDATAOUT_BMSK                                   0xf
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST_OUT_1_TESTDATAOUT_SHFT                                   0x0

#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_ADDR                                 (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000002c)
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_PHYS                                 (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000002c)
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_OFFS                                 (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000002c)
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_RMSK                                        0x1
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_POR                                  0x00000000
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_POR_RMSK                             0xffffffff
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_ADDR, HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_RMSK)
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_ADDR, m)
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_REFCLK_RXTAP_VOUTP_MON_BMSK                 0x1
#define HWIO_USBPHY_USB_PHY_REFCLK_RXTAP_TEST_STATUS_REFCLK_RXTAP_VOUTP_MON_SHFT                 0x0

#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_ADDR                                     (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000030)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_PHYS                                     (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000030)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_OFFS                                     (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000030)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_RMSK                                           0xff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_POR                                      0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_POR_RMSK                                 0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_ADDR, HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_RX_DATA_BMSK                                   0xff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAL_STATUS_RX_DATA_SHFT                                    0x0

#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_ADDR                                     (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000034)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_PHYS                                     (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000034)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_OFFS                                     (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000034)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_RMSK                                           0xff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_POR                                      0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_POR_RMSK                                 0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_ADDR, HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_RX_DATA_BMSK                                   0xff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_DATAH_STATUS_RX_DATA_SHFT                                    0x0

#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000038)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000038)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000038)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RMSK                                            0xff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_POR                                       0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_ADDR, HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RSVD_BMSK                                       0x80
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RSVD_SHFT                                        0x7
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_LINESTATE_BMSK                                  0x60
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_LINESTATE_SHFT                                   0x5
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_TX_READY_BMSK                                   0x10
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_TX_READY_SHFT                                    0x4
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_ERROR_BMSK                                    0x8
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_ERROR_SHFT                                    0x3
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_ACTIVE_BMSK                                   0x4
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_ACTIVE_SHFT                                   0x2
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_VALIDH_BMSK                                   0x2
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_VALIDH_SHFT                                   0x1
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_VALIDL_BMSK                                   0x1
#define HWIO_USBPHY_USB_PHY_UTMI_RX_PORT_STATUS_RX_VALIDL_SHFT                                   0x0

#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000003c)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000003c)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000003c)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_RMSK                                                     0x7f
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_POR                                                0x00000001
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL0_ADDR, HWIO_USBPHY_USB_PHY_UTMI_CTRL0_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_UTMI_CTRL0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_UTMI_CTRL0_ADDR,m,v,HWIO_USBPHY_USB_PHY_UTMI_CTRL0_IN)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_USB_HS_RX_TEST_EN_BMSK                                   0x40
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_USB_HS_RX_TEST_EN_SHFT                                    0x6
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_TERMSEL_BMSK                                             0x20
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_TERMSEL_SHFT                                              0x5
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_OPMODE_BMSK                                              0x18
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_OPMODE_SHFT                                               0x3
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_RX_TESTER_RESET_BMSK                                      0x4
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_RX_TESTER_RESET_SHFT                                      0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_PORTRESET_BMSK                                            0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_PORTRESET_SHFT                                            0x1
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_SLEEPM_BMSK                                               0x1
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL0_SLEEPM_SHFT                                               0x0

#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000040)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000040)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000040)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_RMSK                                                      0xf
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL1_ADDR, HWIO_USBPHY_USB_PHY_UTMI_CTRL1_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_UTMI_CTRL1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_UTMI_CTRL1_ADDR,m,v,HWIO_USBPHY_USB_PHY_UTMI_CTRL1_IN)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_DMPULLDOWN_BMSK                                           0x8
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_DMPULLDOWN_SHFT                                           0x3
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_DPPULLDOWN_BMSK                                           0x4
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_DPPULLDOWN_SHFT                                           0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_XCVRSEL_BMSK                                              0x3
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL1_XCVRSEL_SHFT                                              0x0

#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000044)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000044)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000044)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_RMSK                                                     0xff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL2_ADDR, HWIO_USBPHY_USB_PHY_UTMI_CTRL2_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_UTMI_CTRL2_ADDR,v)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_UTMI_CTRL2_ADDR,m,v,HWIO_USBPHY_USB_PHY_UTMI_CTRL2_IN)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_DATAIN_7_0_BMSK                                          0xff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL2_DATAIN_7_0_SHFT                                           0x0

#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000048)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000048)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000048)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_RMSK                                                     0xff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL3_ADDR, HWIO_USBPHY_USB_PHY_UTMI_CTRL3_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL3_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_UTMI_CTRL3_ADDR,v)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_UTMI_CTRL3_ADDR,m,v,HWIO_USBPHY_USB_PHY_UTMI_CTRL3_IN)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_DATAIN_15_8_BMSK                                         0xff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL3_DATAIN_15_8_SHFT                                          0x0

#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000004c)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000004c)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000004c)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_RMSK                                                      0x7
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL4_ADDR, HWIO_USBPHY_USB_PHY_UTMI_CTRL4_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL4_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_UTMI_CTRL4_ADDR,v)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_UTMI_CTRL4_ADDR,m,v,HWIO_USBPHY_USB_PHY_UTMI_CTRL4_IN)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_IDPULLUP_BMSK                                             0x4
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_IDPULLUP_SHFT                                             0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_TXVALIDH_BMSK                                             0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_TXVALIDH_SHFT                                             0x1
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_TXVALID_BMSK                                              0x1
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL4_TXVALID_SHFT                                              0x0

#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000050)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000050)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000050)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_RMSK                                                      0x7
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ADDR, HWIO_USBPHY_USB_PHY_UTMI_CTRL5_RMSK)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ADDR, m)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ADDR,v)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ADDR,m,v,HWIO_USBPHY_USB_PHY_UTMI_CTRL5_IN)
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_SW_UTMI_HOSTDISCONNECT_BMSK                               0x4
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_SW_UTMI_HOSTDISCONNECT_SHFT                               0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_BMSK                                                  0x2
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_POR_SHFT                                                  0x1
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ATERESET_BMSK                                             0x1
#define HWIO_USBPHY_USB_PHY_UTMI_CTRL5_ATERESET_SHFT                                             0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000054)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000054)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000054)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_RMSK                                            0xff
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_POR                                       0x0000008c
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_COMMONONN_BMSK                                  0x80
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_COMMONONN_SHFT                                   0x7
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_BMSK                                       0x70
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_FSEL_SHFT                                        0x4
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_RETENABLEN_BMSK                                  0x8
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_RETENABLEN_SHFT                                  0x3
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_BMSK                                       0x4
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_SIDDQ_SHFT                                       0x2
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_BMSK                                   0x3
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON0_VATESTENB_SHFT                                   0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000058)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000058)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000058)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_RMSK                                            0x1f
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_POR                                       0x0000001b
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_BMSK                             0x10
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_VBUSVLDEXTSEL0_SHFT                              0x4
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OTGDISABLE0_BMSK                                 0x8
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OTGDISABLE0_SHFT                                 0x3
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OTGTUNE0_BMSK                                    0x7
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL_COMMON1_OTGTUNE0_SHFT                                    0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000005c)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000005c)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000005c)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_RMSK                                                    0x1
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_POR                                              0x00000001
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_BMSK                                        0x1
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL1_VBUSVLDEXT0_SHFT                                        0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000060)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000060)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000060)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_RMSK                                                    0x7
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_POR                                              0x00000003
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_BMSK                                 0x4
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SEL_SHFT                                 0x2
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_BMSK                                     0x2
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_SUSPEND_N_SHFT                                     0x1
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_UTMI_CLK_EN_BMSK                                   0x1
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL2_USB2_UTMI_CLK_EN_SHFT                                   0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000064)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000064)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000064)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_RMSK                                                    0x1
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_POR                                              0x00000000
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_TESTDATAOUT_EN_BMSK                                     0x1
#define HWIO_USBPHY_USB_PHY_HS_PHY_CTRL3_TESTDATAOUT_EN_SHFT                                     0x0

#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_ADDR                                    (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000068)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_PHYS                                    (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000068)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_OFFS                                    (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000068)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_RMSK                                          0xff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_POR                                     0x00000064
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_POR_RMSK                                0xffffffff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_ADDR, HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_RMSK)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_ADDR,m,v,HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_IN)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_SQRXTUNE0_BMSK                                0xe0
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_SQRXTUNE0_SHFT                                 0x5
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_RSVD_BMSK                                     0x18
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_RSVD_SHFT                                      0x3
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_COMPDISTUNE0_BMSK                              0x7
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X0_COMPDISTUNE0_SHFT                              0x0

#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_ADDR                                    (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000006c)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_PHYS                                    (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000006c)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_OFFS                                    (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000006c)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_RMSK                                          0xff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_POR                                     0x00000003
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_POR_RMSK                                0xffffffff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_ADDR, HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_RMSK)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_ADDR,m,v,HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_IN)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_TXPREEMPAMPTUNE0_BMSK                         0xc0
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_TXPREEMPAMPTUNE0_SHFT                          0x6
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_TXPREEMPPULSETUNE0_BMSK                       0x20
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_TXPREEMPPULSETUNE0_SHFT                        0x5
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_RSVD_BMSK                                     0x10
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_RSVD_SHFT                                      0x4
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_TXVREFTUNE0_BMSK                               0xf
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X1_TXVREFTUNE0_SHFT                               0x0

#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_ADDR                                    (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000070)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_PHYS                                    (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000070)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_OFFS                                    (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000070)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_RMSK                                          0xff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_POR                                     0x0000002d
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_POR_RMSK                                0xffffffff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_ADDR, HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_RMSK)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_ADDR,v)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_ADDR,m,v,HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_IN)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_RSVD_BMSK                                     0xc0
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_RSVD_SHFT                                      0x6
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_TXRESTUNE0_BMSK                               0x30
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_TXRESTUNE0_SHFT                                0x4
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_TXHSXVTUNE0_BMSK                               0xc
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_TXHSXVTUNE0_SHFT                               0x2
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_TXRISETUNE0_BMSK                               0x3
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X2_TXRISETUNE0_SHFT                               0x0

#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_ADDR                                    (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000074)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_PHYS                                    (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000074)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_OFFS                                    (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000074)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_RMSK                                          0xff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_POR                                     0x00000003
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_POR_RMSK                                0xffffffff
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_ADDR, HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_RMSK)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_ADDR, m)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_ADDR,v)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_ADDR,m,v,HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_IN)
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_RSVD_BMSK                                     0xf0
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_RSVD_SHFT                                      0x4
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_TXFSLSTUNE0_BMSK                               0xf
#define HWIO_USBPHY_USB_PHY_PARAMETER_OVERRIDE_X3_TXFSLSTUNE0_SHFT                               0x0

#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_ADDR                                        (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000078)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_PHYS                                        (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000078)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_OFFS                                        (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000078)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_RMSK                                               0xf
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_POR                                         0x00000000
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_POR_RMSK                                    0xffffffff
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_ADDR, HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_RMSK)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_ADDR, m)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_ADDR,v)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_ADDR,m,v,HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_IN)
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_VDATDETENB0_BMSK                                   0x8
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_VDATDETENB0_SHFT                                   0x3
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_VDATSRCENB0_BMSK                                   0x4
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_VDATSRCENB0_SHFT                                   0x2
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_CHRGSEL0_BMSK                                      0x2
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_CHRGSEL0_SHFT                                      0x1
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_DCDENB0_BMSK                                       0x1
#define HWIO_USBPHY_USB_PHY_CHARGING_DET_CTRL_DCDENB0_SHFT                                       0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000007c)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000007c)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000007c)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_RMSK                                                   0xff
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_POR                                              0x00000000
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_TESTDATAIN_BMSK                                        0xff
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST0_TESTDATAIN_SHFT                                         0x0

#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000080)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000080)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000080)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_RMSK                                                   0x7f
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_POR                                              0x00000000
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_ADDR, HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_IN)
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_BMSK                                        0x40
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TOGGLE_2WR_SHFT                                         0x6
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_USB_HSPW_CLK_480M_TEST_EN_BMSK                         0x20
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_USB_HSPW_CLK_480M_TEST_EN_SHFT                          0x5
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_BMSK                                    0x10
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TESTDATAOUTSEL_SHFT                                     0x4
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TESTADDR_BMSK                                           0xf
#define HWIO_USBPHY_USB_PHY_HS_PHY_TEST1_TESTADDR_SHFT                                           0x0

#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000084)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000084)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000084)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_RMSK                                            0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_POR                                       0x00000000
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_ADDR, HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_IN)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_RX_PKT_VALUE_7_0_BMSK                           0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG0_RX_PKT_VALUE_7_0_SHFT                            0x0

#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000088)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000088)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000088)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_RMSK                                            0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_POR                                       0x00000000
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_ADDR, HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_IN)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_RX_PKT_VALUE_15_8_BMSK                          0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG1_RX_PKT_VALUE_15_8_SHFT                           0x0

#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_ADDR                                      (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000008c)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_PHYS                                      (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000008c)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_OFFS                                      (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000008c)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_RMSK                                            0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_POR                                       0x00000000
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_POR_RMSK                                  0xffffffff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_ADDR, HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_RMSK)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_ADDR,v)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_ADDR,m,v,HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_IN)
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_RX_PKT_VALUE_23_16_BMSK                         0xff
#define HWIO_USBPHY_USB_PHY_HS_RX_TESTER_1_REG2_RX_PKT_VALUE_23_16_SHFT                          0x0

#define HWIO_USBPHY_USB_PHY_CFG0_ADDR                                                     (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000090)
#define HWIO_USBPHY_USB_PHY_CFG0_PHYS                                                     (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000090)
#define HWIO_USBPHY_USB_PHY_CFG0_OFFS                                                     (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000090)
#define HWIO_USBPHY_USB_PHY_CFG0_RMSK                                                            0x3
#define HWIO_USBPHY_USB_PHY_CFG0_POR                                                      0x00000000
#define HWIO_USBPHY_USB_PHY_CFG0_POR_RMSK                                                 0xffffffff
#define HWIO_USBPHY_USB_PHY_CFG0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_CFG0_ADDR, HWIO_USBPHY_USB_PHY_CFG0_RMSK)
#define HWIO_USBPHY_USB_PHY_CFG0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_CFG0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_CFG0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_CFG0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_CFG0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_CFG0_ADDR,m,v,HWIO_USBPHY_USB_PHY_CFG0_IN)
#define HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_BMSK                              0x2
#define HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_CMN_CTRL_OVERRIDE_EN_SHFT                              0x1
#define HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_BMSK                         0x1
#define HWIO_USBPHY_USB_PHY_CFG0_UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN_SHFT                         0x0

#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000094)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000094)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000094)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_RMSK                                                     0x7f
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_POR                                                0x00000000
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_IN          \
        in_dword_masked(HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_ADDR, HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_RMSK)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_ADDR, m)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_OUT(v)      \
        out_dword(HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_ADDR,v)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_ADDR,m,v,HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_IN)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_TESTBURNIN_BMSK                                          0x40
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_TESTBURNIN_SHFT                                           0x6
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_LOOPBACKENB_BMSK                                         0x20
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_LOOPBACKENB_SHFT                                          0x5
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDPDATA_BMSK                                        0x10
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDPDATA_SHFT                                         0x4
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSSEL_BMSK                                            0x8
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSSEL_SHFT                                            0x3
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDMEN_BMSK                                           0x4
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDMEN_SHFT                                           0x2
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDPEN_BMSK                                           0x2
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDPEN_SHFT                                           0x1
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDMDATA_BMSK                                         0x1
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL0_BYPASSDMDATA_SHFT                                         0x0

#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x00000098)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x00000098)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x00000098)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_RMSK                                                      0x7
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_POR                                                0x00000004
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_IN          \
        in_dword_masked(HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_ADDR, HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_RMSK)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_ADDR, m)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_OUT(v)      \
        out_dword(HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_ADDR,v)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_ADDR,m,v,HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_IN)
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_UTMI_TX_ENABLE_N_BMSK                                     0x4
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_UTMI_TX_ENABLE_N_SHFT                                     0x2
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_UTMI_TX_SE0_BMSK                                          0x2
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_UTMI_TX_SE0_SHFT                                          0x1
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_UTMI_TX_DAT_BMSK                                          0x1
#define HWIO_USBPHY_UTMI_PHY_CMN_CTRL1_UTMI_TX_DAT_SHFT                                          0x0

#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_ADDR                                              (USBPHY_CM_DWC_USB2_REG_BASE      + 0x0000009c)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_PHYS                                              (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x0000009c)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_OFFS                                              (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x0000009c)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_RMSK                                                     0x3
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_POR                                               0x00000002
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_POR_RMSK                                          0xffffffff
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REFCLK_CTRL_ADDR, HWIO_USBPHY_USB_PHY_REFCLK_CTRL_RMSK)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_REFCLK_CTRL_ADDR, m)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_REFCLK_CTRL_ADDR,v)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_REFCLK_CTRL_ADDR,m,v,HWIO_USBPHY_USB_PHY_REFCLK_CTRL_IN)
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_REFCLK_SEL_BMSK                                          0x3
#define HWIO_USBPHY_USB_PHY_REFCLK_CTRL_REFCLK_SEL_SHFT                                          0x0

#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_ADDR                                             (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000a0)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_PHYS                                             (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000a0)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_OFFS                                             (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000a0)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_RMSK                                                    0x1
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_POR                                              0x00000001
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_POR_RMSK                                         0xffffffff
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_ADDR, HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_RMSK)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_ADDR, m)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_ADDR,v)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_ADDR,m,v,HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_IN)
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_PWRDN_B_BMSK                                            0x1
#define HWIO_USBPHY_USB_PHY_PWRDOWN_CTRL_PWRDN_B_SHFT                                            0x0

#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_ADDR                                          (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000a4)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_PHYS                                          (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000a4)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_OFFS                                          (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000a4)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_RMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_POR                                           0x00000000
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_POR_RMSK                                      0xffffffff
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_ADDR, HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_RMSK)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_ADDR, m)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_ADDR,v)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_ADDR,m,v,HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_IN)
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_DEBUG_BUS_SEL_BMSK                                  0xe0
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_DEBUG_BUS_SEL_SHFT                                   0x5
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_DTESTMUX_SEL_BMSK                                   0x1f
#define HWIO_USBPHY_USB_PHY_TEST_DEBUG_CTRL_DTESTMUX_SEL_SHFT                                    0x0

#define HWIO_USBPHY_USB_PHY_RESET_CTRL_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000a8)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000a8)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000a8)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_RMSK                                                      0x1
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESET_CTRL_ADDR, HWIO_USBPHY_USB_PHY_RESET_CTRL_RMSK)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESET_CTRL_ADDR, m)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_RESET_CTRL_ADDR,v)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_RESET_CTRL_ADDR,m,v,HWIO_USBPHY_USB_PHY_RESET_CTRL_IN)
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_SW_RESET_BMSK                                             0x1
#define HWIO_USBPHY_USB_PHY_RESET_CTRL_SW_RESET_SHFT                                             0x0

#define HWIO_USBPHY_USB_PHY_AC_EN_ADDR                                                    (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000ac)
#define HWIO_USBPHY_USB_PHY_AC_EN_PHYS                                                    (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000ac)
#define HWIO_USBPHY_USB_PHY_AC_EN_OFFS                                                    (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000ac)
#define HWIO_USBPHY_USB_PHY_AC_EN_RMSK                                                           0x3
#define HWIO_USBPHY_USB_PHY_AC_EN_POR                                                     0x00000000
#define HWIO_USBPHY_USB_PHY_AC_EN_POR_RMSK                                                0xffffffff
#define HWIO_USBPHY_USB_PHY_AC_EN_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_AC_EN_ADDR, HWIO_USBPHY_USB_PHY_AC_EN_RMSK)
#define HWIO_USBPHY_USB_PHY_AC_EN_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_AC_EN_ADDR, m)
#define HWIO_USBPHY_USB_PHY_AC_EN_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_AC_EN_ADDR,v)
#define HWIO_USBPHY_USB_PHY_AC_EN_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_AC_EN_ADDR,m,v,HWIO_USBPHY_USB_PHY_AC_EN_IN)
#define HWIO_USBPHY_USB_PHY_AC_EN_USB_HS_AC_POLARITY_BMSK                                        0x2
#define HWIO_USBPHY_USB_PHY_AC_EN_USB_HS_AC_POLARITY_SHFT                                        0x1
#define HWIO_USBPHY_USB_PHY_AC_EN_USB_HS_AC_EN_BMSK                                              0x1
#define HWIO_USBPHY_USB_PHY_AC_EN_USB_HS_AC_EN_SHFT                                              0x0

#define HWIO_USBPHY_USB_PHY_RESERVED_0_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000b0)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000b0)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000b0)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_RMSK                                                     0xff
#define HWIO_USBPHY_USB_PHY_RESERVED_0_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_RESERVED_0_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_RESERVED_0_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESERVED_0_ADDR, HWIO_USBPHY_USB_PHY_RESERVED_0_RMSK)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESERVED_0_ADDR, m)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_RESERVED_0_ADDR,v)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_RESERVED_0_ADDR,m,v,HWIO_USBPHY_USB_PHY_RESERVED_0_IN)
#define HWIO_USBPHY_USB_PHY_RESERVED_0_RSVD_BMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_RESERVED_0_RSVD_SHFT                                                 0x0

#define HWIO_USBPHY_USB_PHY_RESERVED_1_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000b4)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000b4)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000b4)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_RMSK                                                     0xff
#define HWIO_USBPHY_USB_PHY_RESERVED_1_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_RESERVED_1_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_RESERVED_1_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESERVED_1_ADDR, HWIO_USBPHY_USB_PHY_RESERVED_1_RMSK)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESERVED_1_ADDR, m)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_RESERVED_1_ADDR,v)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_RESERVED_1_ADDR,m,v,HWIO_USBPHY_USB_PHY_RESERVED_1_IN)
#define HWIO_USBPHY_USB_PHY_RESERVED_1_RSVD_BMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_RESERVED_1_RSVD_SHFT                                                 0x0

#define HWIO_USBPHY_USB_PHY_RESERVED_2_ADDR                                               (USBPHY_CM_DWC_USB2_REG_BASE      + 0x000000b8)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_PHYS                                               (USBPHY_CM_DWC_USB2_REG_BASE_PHYS + 0x000000b8)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_OFFS                                               (USBPHY_CM_DWC_USB2_REG_BASE_OFFS + 0x000000b8)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_RMSK                                                     0xff
#define HWIO_USBPHY_USB_PHY_RESERVED_2_POR                                                0x00000000
#define HWIO_USBPHY_USB_PHY_RESERVED_2_POR_RMSK                                           0xffffffff
#define HWIO_USBPHY_USB_PHY_RESERVED_2_IN          \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESERVED_2_ADDR, HWIO_USBPHY_USB_PHY_RESERVED_2_RMSK)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_INM(m)      \
        in_dword_masked(HWIO_USBPHY_USB_PHY_RESERVED_2_ADDR, m)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_OUT(v)      \
        out_dword(HWIO_USBPHY_USB_PHY_RESERVED_2_ADDR,v)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_OUTM(m,v) \
        out_dword_masked_ns(HWIO_USBPHY_USB_PHY_RESERVED_2_ADDR,m,v,HWIO_USBPHY_USB_PHY_RESERVED_2_IN)
#define HWIO_USBPHY_USB_PHY_RESERVED_2_RSVD_BMSK                                                0xff
#define HWIO_USBPHY_USB_PHY_RESERVED_2_RSVD_SHFT                                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: AHB2PHY
 *--------------------------------------------------------------------------*/

#define AHB2PHY_REG_BASE                                                             (AHB2PHY_BASE      + 0x00000000)
#define AHB2PHY_REG_BASE_PHYS                                                        (AHB2PHY_BASE_PHYS + 0x00000000)
#define AHB2PHY_REG_BASE_OFFS                                                        0x00000000

#define HWIO_AHB2PHY_HW_VERSION_ADDR                                                 (AHB2PHY_REG_BASE      + 0x00000000)
#define HWIO_AHB2PHY_HW_VERSION_PHYS                                                 (AHB2PHY_REG_BASE_PHYS + 0x00000000)
#define HWIO_AHB2PHY_HW_VERSION_OFFS                                                 (AHB2PHY_REG_BASE_OFFS + 0x00000000)
#define HWIO_AHB2PHY_HW_VERSION_RMSK                                                   0xffffff
#define HWIO_AHB2PHY_HW_VERSION_POR                                                  0x00010000
#define HWIO_AHB2PHY_HW_VERSION_POR_RMSK                                             0xffffffff
#define HWIO_AHB2PHY_HW_VERSION_IN          \
        in_dword_masked(HWIO_AHB2PHY_HW_VERSION_ADDR, HWIO_AHB2PHY_HW_VERSION_RMSK)
#define HWIO_AHB2PHY_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_AHB2PHY_HW_VERSION_ADDR, m)
#define HWIO_AHB2PHY_HW_VERSION_MAJOR_BMSK                                             0xff0000
#define HWIO_AHB2PHY_HW_VERSION_MAJOR_SHFT                                                 0x10
#define HWIO_AHB2PHY_HW_VERSION_MINOR_BMSK                                               0xff00
#define HWIO_AHB2PHY_HW_VERSION_MINOR_SHFT                                                  0x8
#define HWIO_AHB2PHY_HW_VERSION_STEP_BMSK                                                  0xff
#define HWIO_AHB2PHY_HW_VERSION_STEP_SHFT                                                   0x0

#define HWIO_AHB2PHY_HW_INFO_ADDR                                                    (AHB2PHY_REG_BASE      + 0x00000004)
#define HWIO_AHB2PHY_HW_INFO_PHYS                                                    (AHB2PHY_REG_BASE_PHYS + 0x00000004)
#define HWIO_AHB2PHY_HW_INFO_OFFS                                                    (AHB2PHY_REG_BASE_OFFS + 0x00000004)
#define HWIO_AHB2PHY_HW_INFO_RMSK                                                    0xffffffff
#define HWIO_AHB2PHY_HW_INFO_POR                                                     0x01000200
#define HWIO_AHB2PHY_HW_INFO_POR_RMSK                                                0xffffffff
#define HWIO_AHB2PHY_HW_INFO_IN          \
        in_dword_masked(HWIO_AHB2PHY_HW_INFO_ADDR, HWIO_AHB2PHY_HW_INFO_RMSK)
#define HWIO_AHB2PHY_HW_INFO_INM(m)      \
        in_dword_masked(HWIO_AHB2PHY_HW_INFO_ADDR, m)
#define HWIO_AHB2PHY_HW_INFO_HW_MAJOR_BMSK                                           0xff000000
#define HWIO_AHB2PHY_HW_INFO_HW_MAJOR_SHFT                                                 0x18
#define HWIO_AHB2PHY_HW_INFO_HW_BRANCH_BMSK                                            0xff0000
#define HWIO_AHB2PHY_HW_INFO_HW_BRANCH_SHFT                                                0x10
#define HWIO_AHB2PHY_HW_INFO_HW_MINOR_BMSK                                               0xff00
#define HWIO_AHB2PHY_HW_INFO_HW_MINOR_SHFT                                                  0x8
#define HWIO_AHB2PHY_HW_INFO_HW_ECO_BMSK                                                   0xff
#define HWIO_AHB2PHY_HW_INFO_HW_ECO_SHFT                                                    0x0

#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR                             (AHB2PHY_REG_BASE      + 0x00000008)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_PHYS                             (AHB2PHY_REG_BASE_PHYS + 0x00000008)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_OFFS                             (AHB2PHY_REG_BASE_OFFS + 0x00000008)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_RMSK                             0xffffffff
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_POR                              0x00000000
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_POR_RMSK                         0xffffffff
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_IN          \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR, HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_RMSK)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_INM(m)      \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR, m)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_OUT(v)      \
        out_dword(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR,v)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR,m,v,HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_IN)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_BROADCAST_EN_LOWER_BMSK          0xffffffff
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_LOWER_BROADCAST_EN_LOWER_SHFT                 0x0

#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR                             (AHB2PHY_REG_BASE      + 0x0000000c)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_PHYS                             (AHB2PHY_REG_BASE_PHYS + 0x0000000c)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_OFFS                             (AHB2PHY_REG_BASE_OFFS + 0x0000000c)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_RMSK                             0x3fffffff
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_POR                              0x00000000
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_POR_RMSK                         0xffffffff
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_IN          \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR, HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_RMSK)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_INM(m)      \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR, m)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_OUT(v)      \
        out_dword(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR,v)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR,m,v,HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_IN)
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_BROADCAST_EN_UPPER_BMSK          0x3fffffff
#define HWIO_AHB2PHY_AHB2PHY_BROADCAST_EN_CFG_UPPER_BROADCAST_EN_UPPER_SHFT                 0x0

#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_ADDR                                            (AHB2PHY_REG_BASE      + 0x00000010)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_PHYS                                            (AHB2PHY_REG_BASE_PHYS + 0x00000010)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_OFFS                                            (AHB2PHY_REG_BASE_OFFS + 0x00000010)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_RMSK                                                  0x33
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_POR                                             0x00000000
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_POR_RMSK                                        0xffffffff
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_IN          \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_TOP_CFG_ADDR, HWIO_AHB2PHY_AHB2PHY_TOP_CFG_RMSK)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_INM(m)      \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_TOP_CFG_ADDR, m)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_OUT(v)      \
        out_dword(HWIO_AHB2PHY_AHB2PHY_TOP_CFG_ADDR,v)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AHB2PHY_AHB2PHY_TOP_CFG_ADDR,m,v,HWIO_AHB2PHY_AHB2PHY_TOP_CFG_IN)
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_BMSK                                0x30
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_SHFT                                 0x4
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_READ_WAIT_STATES_BMSK                                  0x3
#define HWIO_AHB2PHY_AHB2PHY_TOP_CFG_READ_WAIT_STATES_SHFT                                  0x0

#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_ADDR                                      (AHB2PHY_REG_BASE      + 0x00000014)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_PHYS                                      (AHB2PHY_REG_BASE_PHYS + 0x00000014)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_OFFS                                      (AHB2PHY_REG_BASE_OFFS + 0x00000014)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_RMSK                                             0x3
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_POR                                       0x00000000
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_POR_RMSK                                  0xffffffff
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_IN          \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_ADDR, HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_RMSK)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_INM(m)      \
        in_dword_masked(HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_ADDR, m)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_OUT(v)      \
        out_dword(HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_ADDR,v)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_ADDR,m,v,HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_IN)
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_BMSK                               0x3
#define HWIO_AHB2PHY_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SHFT                               0x0

/**
  @file usb_hwio_9410.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    WHS9410 (Bolt) v2 [pTO_2p0]
 
  This file contains HWIO register definitions for the following modules:
    CHIP_CFG0
    CHIP_CFG1


  Generation parameters: 
  { u'filename': u'usb_hwio_9410.h',
    u'module-filter-exclude': { },
    u'module-filter-include': { },
    u'modules': [u'CHIP_CFG0', u'CHIP_CFG1'],
    u'output-offsets': True,
    u'output-phys': True,
    u'output-resets': True}
*/

/*----------------------------------------------------------------------------
 * MODULE: CHIP_CFG0
 *--------------------------------------------------------------------------*/

#define CHIP_CFG0_REG_BASE                                                (CHIP_CFG0_BASE      + 0x00000000)
#define CHIP_CFG0_REG_BASE_PHYS                                           (CHIP_CFG0_BASE_PHYS + 0x00000000)
#define CHIP_CFG0_REG_BASE_OFFS                                           0x00000000

#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_ADDR                                 (CHIP_CFG0_REG_BASE      + 0x00000000)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_PHYS                                 (CHIP_CFG0_REG_BASE_PHYS + 0x00000000)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_OFFS                                 (CHIP_CFG0_REG_BASE_OFFS + 0x00000000)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_RMSK                                       0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_POR                                  0x00000000
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_POR_RMSK                             0x000000ff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE0_ADDR, HWIO_CHIP_CFG0_CHIP_ID_BYTE0_RMSK)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE0_ADDR, m)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_VAL_BMSK                                   0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE0_VAL_SHFT                                    0x0

#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_ADDR                                 (CHIP_CFG0_REG_BASE      + 0x00000001)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_PHYS                                 (CHIP_CFG0_REG_BASE_PHYS + 0x00000001)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_OFFS                                 (CHIP_CFG0_REG_BASE_OFFS + 0x00000001)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_RMSK                                       0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_POR                                  0x00000001
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_POR_RMSK                             0x000000ff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE1_ADDR, HWIO_CHIP_CFG0_CHIP_ID_BYTE1_RMSK)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE1_ADDR, m)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_VAL_BMSK                                   0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE1_VAL_SHFT                                    0x0

#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_ADDR                                 (CHIP_CFG0_REG_BASE      + 0x00000002)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_PHYS                                 (CHIP_CFG0_REG_BASE_PHYS + 0x00000002)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_OFFS                                 (CHIP_CFG0_REG_BASE_OFFS + 0x00000002)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_RMSK                                       0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_POR                                  0x00000000
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_POR_RMSK                             0x000000ff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE2_ADDR, HWIO_CHIP_CFG0_CHIP_ID_BYTE2_RMSK)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE2_ADDR, m)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_VAL_BMSK                                   0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE2_VAL_SHFT                                    0x0

#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_ADDR                                 (CHIP_CFG0_REG_BASE      + 0x00000003)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_PHYS                                 (CHIP_CFG0_REG_BASE_PHYS + 0x00000003)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_OFFS                                 (CHIP_CFG0_REG_BASE_OFFS + 0x00000003)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_RMSK                                       0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_POR                                  0x00000002
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_POR_RMSK                             0x000000ff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE3_ADDR, HWIO_CHIP_CFG0_CHIP_ID_BYTE3_RMSK)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CHIP_ID_BYTE3_ADDR, m)
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_VAL_BMSK                                   0xff
#define HWIO_CHIP_CFG0_CHIP_ID_BYTE3_VAL_SHFT                                    0x0

#define HWIO_CHIP_CFG0_EFUSE_CTL_ADDR                                     (CHIP_CFG0_REG_BASE      + 0x00000004)
#define HWIO_CHIP_CFG0_EFUSE_CTL_PHYS                                     (CHIP_CFG0_REG_BASE_PHYS + 0x00000004)
#define HWIO_CHIP_CFG0_EFUSE_CTL_OFFS                                     (CHIP_CFG0_REG_BASE_OFFS + 0x00000004)
#define HWIO_CHIP_CFG0_EFUSE_CTL_RMSK                                           0x3f
#define HWIO_CHIP_CFG0_EFUSE_CTL_POR                                      0x00000010
#define HWIO_CHIP_CFG0_EFUSE_CTL_POR_RMSK                                 0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_CTL_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_CTL_ADDR, HWIO_CHIP_CFG0_EFUSE_CTL_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_CTL_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_CTL_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_CTL_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_EFUSE_CTL_ADDR,v)
#define HWIO_CHIP_CFG0_EFUSE_CTL_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_EFUSE_CTL_ADDR,m,v,HWIO_CHIP_CFG0_EFUSE_CTL_IN)
#define HWIO_CHIP_CFG0_EFUSE_CTL_RESET_BMSK                                     0x20
#define HWIO_CHIP_CFG0_EFUSE_CTL_RESET_SHFT                                      0x5
#define HWIO_CHIP_CFG0_EFUSE_CTL_SENSE_STATE_BMSK                               0x1e
#define HWIO_CHIP_CFG0_EFUSE_CTL_SENSE_STATE_SHFT                                0x1
#define HWIO_CHIP_CFG0_EFUSE_CTL_ENABLE_BMSK                                     0x1
#define HWIO_CHIP_CFG0_EFUSE_CTL_ENABLE_SHFT                                     0x0

#define HWIO_CHIP_CFG0_EFUSE_TEST0_ADDR                                   (CHIP_CFG0_REG_BASE      + 0x00000005)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_PHYS                                   (CHIP_CFG0_REG_BASE_PHYS + 0x00000005)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_OFFS                                   (CHIP_CFG0_REG_BASE_OFFS + 0x00000005)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_RMSK                                         0xff
#define HWIO_CHIP_CFG0_EFUSE_TEST0_POR                                    0x00000000
#define HWIO_CHIP_CFG0_EFUSE_TEST0_POR_RMSK                               0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_TEST0_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_TEST0_ADDR, HWIO_CHIP_CFG0_EFUSE_TEST0_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_TEST0_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_EFUSE_TEST0_ADDR,v)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_EFUSE_TEST0_ADDR,m,v,HWIO_CHIP_CFG0_EFUSE_TEST0_IN)
#define HWIO_CHIP_CFG0_EFUSE_TEST0_BITS_BMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE_TEST0_BITS_SHFT                                     0x0

#define HWIO_CHIP_CFG0_EFUSE_TEST1_ADDR                                   (CHIP_CFG0_REG_BASE      + 0x00000006)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_PHYS                                   (CHIP_CFG0_REG_BASE_PHYS + 0x00000006)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_OFFS                                   (CHIP_CFG0_REG_BASE_OFFS + 0x00000006)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_RMSK                                         0xff
#define HWIO_CHIP_CFG0_EFUSE_TEST1_POR                                    0x00000000
#define HWIO_CHIP_CFG0_EFUSE_TEST1_POR_RMSK                               0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_TEST1_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_TEST1_ADDR, HWIO_CHIP_CFG0_EFUSE_TEST1_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_TEST1_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_EFUSE_TEST1_ADDR,v)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_EFUSE_TEST1_ADDR,m,v,HWIO_CHIP_CFG0_EFUSE_TEST1_IN)
#define HWIO_CHIP_CFG0_EFUSE_TEST1_BITS_BMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE_TEST1_BITS_SHFT                                     0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_ADDR                                (CHIP_CFG0_REG_BASE      + 0x00000008)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x00000008)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x00000008)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_MCU_SKU_BMSK                              0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT0_MCU_SKU_SHFT                               0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_ADDR                                (CHIP_CFG0_REG_BASE      + 0x00000009)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x00000009)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x00000009)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_ZDET_CAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT1_ZDET_CAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000000a)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000000a)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000000a)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_ZDET_CAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT2_ZDET_CAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000000b)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000000b)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000000b)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_ZDET_CAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT3_ZDET_CAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000000c)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000000c)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000000c)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_ZDET_CAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT4_ZDET_CAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000000d)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000000d)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000000d)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_HPH_GAIN_ERR_BMSK                         0xf0
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_HPH_GAIN_ERR_SHFT                          0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_HPH_GAIN_LMT_BMSK                          0xe
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_HPH_GAIN_LMT_SHFT                          0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_HW_EQ_DISABLE_BMSK                         0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT5_HW_EQ_DISABLE_SHFT                         0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000000e)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000000e)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000000e)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_BITS_BMSK                                 0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT6_BITS_SHFT                                  0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000000f)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000000f)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000000f)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_BITS_BMSK                                 0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT7_BITS_SHFT                                  0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_ADDR                                (CHIP_CFG0_REG_BASE      + 0x00000010)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x00000010)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x00000010)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_BITS_BMSK                                 0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT8_BITS_SHFT                                  0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_ADDR                                (CHIP_CFG0_REG_BASE      + 0x00000011)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x00000011)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x00000011)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_RMSK                                      0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_POR                                 0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_BITS_BMSK                                 0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT9_BITS_SHFT                                  0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000012)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000012)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000012)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_AUDIO_32BIT_DISABLE_BMSK                 0x80
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_AUDIO_32BIT_DISABLE_SHFT                  0x7
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_MIX_CH_DISABLE_BMSK                      0x40
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_MIX_CH_DISABLE_SHFT                       0x6
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_SPI_MSTR_DISABLE_BMSK                    0x20
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_SPI_MSTR_DISABLE_SHFT                     0x5
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_I2C_MSTR_DISABLE_BMSK                    0x10
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_I2C_MSTR_DISABLE_SHFT                     0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_DFU_DISABLE_BMSK                          0x8
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_DFU_DISABLE_SHFT                          0x3
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_HID_DISABLE_BMSK                          0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_HID_DISABLE_SHFT                          0x2
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_I2S_DISABLE_BMSK                          0x2
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_I2S_DISABLE_SHFT                          0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_USB_DISABLE_BMSK                          0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT10_USB_DISABLE_SHFT                          0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000013)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000013)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000013)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_SYS_BOOT_FREQ_BMSK                       0xc0
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_SYS_BOOT_FREQ_SHFT                        0x6
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_LED1_DISABLE_BMSK                        0x20
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_LED1_DISABLE_SHFT                         0x5
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_LED2_DISABLE_BMSK                        0x10
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_LED2_DISABLE_SHFT                         0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_LED3_DISABLE_BMSK                         0x8
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_LED3_DISABLE_SHFT                         0x3
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_DEC2_DISABLE_BMSK                         0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_DEC2_DISABLE_SHFT                         0x2
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_DEC1_DISABLE_BMSK                         0x2
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_DEC1_DISABLE_SHFT                         0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_DEC0_DISABLE_BMSK                         0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT11_DEC0_DISABLE_SHFT                         0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000014)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000014)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000014)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_BITS_BMSK                                0xfe
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_BITS_SHFT                                 0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_LO_HIFI_DISABLE_BMSK                      0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT12_LO_HIFI_DISABLE_SHFT                      0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000015)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000015)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000015)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PBK_192K_DMA_DISABLE_BMSK                0x80
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PBK_192K_DMA_DISABLE_SHFT                 0x7
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_UHQA_DISABLE_BMSK                        0x40
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_UHQA_DISABLE_SHFT                         0x6
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PBK_384K_DMA_DISABLE_BMSK                0x20
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PBK_384K_DMA_DISABLE_SHFT                 0x5
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_DSD_DISABLE_BMSK                         0x10
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_DSD_DISABLE_SHFT                          0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_DIFF_PA_DISABLE_BMSK                      0x8
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_DIFF_PA_DISABLE_SHFT                      0x3
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_WDOG_DIS_BMSK                             0x4
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_WDOG_DIS_SHFT                             0x2
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_ANC_DIS_BMSK                              0x2
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_ANC_DIS_SHFT                              0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PROC_JTAG_DISABLE_BMSK                    0x1
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT13_PROC_JTAG_DISABLE_SHFT                    0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000016)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000016)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000016)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT14_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000017)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000017)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000017)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_ADDR, HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE_VAL_OUT15_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE_STATUS_ADDR                                  (CHIP_CFG0_REG_BASE      + 0x00000018)
#define HWIO_CHIP_CFG0_EFUSE_STATUS_PHYS                                  (CHIP_CFG0_REG_BASE_PHYS + 0x00000018)
#define HWIO_CHIP_CFG0_EFUSE_STATUS_OFFS                                  (CHIP_CFG0_REG_BASE_OFFS + 0x00000018)
#define HWIO_CHIP_CFG0_EFUSE_STATUS_RMSK                                         0x1
#define HWIO_CHIP_CFG0_EFUSE_STATUS_POR                                   0x00000000
#define HWIO_CHIP_CFG0_EFUSE_STATUS_POR_RMSK                              0x000000ff
#define HWIO_CHIP_CFG0_EFUSE_STATUS_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_STATUS_ADDR, HWIO_CHIP_CFG0_EFUSE_STATUS_RMSK)
#define HWIO_CHIP_CFG0_EFUSE_STATUS_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE_STATUS_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE_STATUS_VALID_BMSK                                   0x1
#define HWIO_CHIP_CFG0_EFUSE_STATUS_VALID_SHFT                                   0x0

#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_ADDR                          (CHIP_CFG0_REG_BASE      + 0x00000019)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_PHYS                          (CHIP_CFG0_REG_BASE_PHYS + 0x00000019)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_OFFS                          (CHIP_CFG0_REG_BASE_OFFS + 0x00000019)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_RMSK                                0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_POR                           0x0000000d
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_POR_RMSK                      0x000000ff
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_ADDR, HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_RMSK)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_ADDR, m)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_VAL_BMSK                            0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_NONNEGO_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000001a)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000001a)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000001a)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_RMSK                                      0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_POR                                 0x00000000
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_ADDR, HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_RMSK)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_ADDR, m)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_ADDR,v)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_ADDR,m,v,HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_IN)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_VAL_BMSK                                  0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_1_VAL_SHFT                                   0x0

#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000001b)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000001b)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000001b)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_RMSK                                      0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_POR                                 0x00000000
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_ADDR, HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_RMSK)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_ADDR, m)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_ADDR,v)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_ADDR,m,v,HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_IN)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_VAL_BMSK                                  0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_2_VAL_SHFT                                   0x0

#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_ADDR                                (CHIP_CFG0_REG_BASE      + 0x0000001c)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_PHYS                                (CHIP_CFG0_REG_BASE_PHYS + 0x0000001c)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_OFFS                                (CHIP_CFG0_REG_BASE_OFFS + 0x0000001c)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_RMSK                                      0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_POR                                 0x00000000
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_ADDR, HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_RMSK)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_ADDR, m)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_ADDR,v)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_ADDR,m,v,HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_IN)
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_VAL_BMSK                                  0x7f
#define HWIO_CHIP_CFG0_I2C_SLAVE_ID_3_VAL_SHFT                                   0x0

#define HWIO_CHIP_CFG0_I2C_ACTIVE_ADDR                                    (CHIP_CFG0_REG_BASE      + 0x0000001f)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_PHYS                                    (CHIP_CFG0_REG_BASE_PHYS + 0x0000001f)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_OFFS                                    (CHIP_CFG0_REG_BASE_OFFS + 0x0000001f)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_RMSK                                           0x1
#define HWIO_CHIP_CFG0_I2C_ACTIVE_POR                                     0x00000000
#define HWIO_CHIP_CFG0_I2C_ACTIVE_POR_RMSK                                0x000000ff
#define HWIO_CHIP_CFG0_I2C_ACTIVE_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_ACTIVE_ADDR, HWIO_CHIP_CFG0_I2C_ACTIVE_RMSK)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_I2C_ACTIVE_ADDR, m)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_I2C_ACTIVE_ADDR,v)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_I2C_ACTIVE_ADDR,m,v,HWIO_CHIP_CFG0_I2C_ACTIVE_IN)
#define HWIO_CHIP_CFG0_I2C_ACTIVE_ENABLE_BMSK                                    0x1
#define HWIO_CHIP_CFG0_I2C_ACTIVE_ENABLE_SHFT                                    0x0

#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_ADDR                                  (CHIP_CFG0_REG_BASE      + 0x00000020)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_PHYS                                  (CHIP_CFG0_REG_BASE_PHYS + 0x00000020)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_OFFS                                  (CHIP_CFG0_REG_BASE_OFFS + 0x00000020)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_RMSK                                         0x7
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_POR                                   0x00000004
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_POR_RMSK                              0x000000ff
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CLK_CFG_MCLK_ADDR, HWIO_CHIP_CFG0_CLK_CFG_MCLK_RMSK)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CLK_CFG_MCLK_ADDR, m)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_CLK_CFG_MCLK_ADDR,v)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_CLK_CFG_MCLK_ADDR,m,v,HWIO_CHIP_CFG0_CLK_CFG_MCLK_IN)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_GATE_BMSK                                    0x4
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_GATE_SHFT                                    0x2
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_FREQ_BMSK                                    0x3
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK_FREQ_SHFT                                    0x0

#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_ADDR                                 (CHIP_CFG0_REG_BASE      + 0x00000021)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_PHYS                                 (CHIP_CFG0_REG_BASE_PHYS + 0x00000021)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_OFFS                                 (CHIP_CFG0_REG_BASE_OFFS + 0x00000021)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_RMSK                                        0x3
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_POR                                  0x00000002
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_POR_RMSK                             0x000000ff
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CLK_CFG_MCLK2_ADDR, HWIO_CHIP_CFG0_CLK_CFG_MCLK2_RMSK)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CLK_CFG_MCLK2_ADDR, m)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_CLK_CFG_MCLK2_ADDR,v)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_CLK_CFG_MCLK2_ADDR,m,v,HWIO_CHIP_CFG0_CLK_CFG_MCLK2_IN)
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_FREQ_BMSK                                   0x3
#define HWIO_CHIP_CFG0_CLK_CFG_MCLK2_FREQ_SHFT                                   0x0

#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000022)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000022)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000022)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_RMSK                                      0x1
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_POR                                0x00000000
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ADDR, HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_RMSK)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ADDR, m)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ADDR,v)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ADDR,m,v,HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_IN)
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ENABLE_BMSK                               0x1
#define HWIO_CHIP_CFG0_CLK_CTL_CDC_DIG_ENABLE_SHFT                               0x0

#define HWIO_CHIP_CFG0_RST_CTL_ADDR                                       (CHIP_CFG0_REG_BASE      + 0x00000031)
#define HWIO_CHIP_CFG0_RST_CTL_PHYS                                       (CHIP_CFG0_REG_BASE_PHYS + 0x00000031)
#define HWIO_CHIP_CFG0_RST_CTL_OFFS                                       (CHIP_CFG0_REG_BASE_OFFS + 0x00000031)
#define HWIO_CHIP_CFG0_RST_CTL_RMSK                                              0x3
#define HWIO_CHIP_CFG0_RST_CTL_POR                                        0x00000002
#define HWIO_CHIP_CFG0_RST_CTL_POR_RMSK                                   0x000000ff
#define HWIO_CHIP_CFG0_RST_CTL_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_RST_CTL_ADDR, HWIO_CHIP_CFG0_RST_CTL_RMSK)
#define HWIO_CHIP_CFG0_RST_CTL_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_RST_CTL_ADDR, m)
#define HWIO_CHIP_CFG0_RST_CTL_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_RST_CTL_ADDR,v)
#define HWIO_CHIP_CFG0_RST_CTL_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_RST_CTL_ADDR,m,v,HWIO_CHIP_CFG0_RST_CTL_IN)
#define HWIO_CHIP_CFG0_RST_CTL_RIF_REG_RST_BMSK                                  0x2
#define HWIO_CHIP_CFG0_RST_CTL_RIF_REG_RST_SHFT                                  0x1
#define HWIO_CHIP_CFG0_RST_CTL_CODEC_DIG_RST_BMSK                                0x1
#define HWIO_CHIP_CFG0_RST_CTL_CODEC_DIG_RST_SHFT                                0x0

#define HWIO_CHIP_CFG0_EFUSE2_CTL_ADDR                                    (CHIP_CFG0_REG_BASE      + 0x0000003c)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_PHYS                                    (CHIP_CFG0_REG_BASE_PHYS + 0x0000003c)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_OFFS                                    (CHIP_CFG0_REG_BASE_OFFS + 0x0000003c)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_RMSK                                          0x3f
#define HWIO_CHIP_CFG0_EFUSE2_CTL_POR                                     0x00000010
#define HWIO_CHIP_CFG0_EFUSE2_CTL_POR_RMSK                                0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_CTL_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_CTL_ADDR, HWIO_CHIP_CFG0_EFUSE2_CTL_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_CTL_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_EFUSE2_CTL_ADDR,v)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_EFUSE2_CTL_ADDR,m,v,HWIO_CHIP_CFG0_EFUSE2_CTL_IN)
#define HWIO_CHIP_CFG0_EFUSE2_CTL_RESET_BMSK                                    0x20
#define HWIO_CHIP_CFG0_EFUSE2_CTL_RESET_SHFT                                     0x5
#define HWIO_CHIP_CFG0_EFUSE2_CTL_SENSE_STATE_BMSK                              0x1e
#define HWIO_CHIP_CFG0_EFUSE2_CTL_SENSE_STATE_SHFT                               0x1
#define HWIO_CHIP_CFG0_EFUSE2_CTL_ENABLE_BMSK                                    0x1
#define HWIO_CHIP_CFG0_EFUSE2_CTL_ENABLE_SHFT                                    0x0

#define HWIO_CHIP_CFG0_EFUSE2_TEST0_ADDR                                  (CHIP_CFG0_REG_BASE      + 0x0000003d)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_PHYS                                  (CHIP_CFG0_REG_BASE_PHYS + 0x0000003d)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_OFFS                                  (CHIP_CFG0_REG_BASE_OFFS + 0x0000003d)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_RMSK                                        0xff
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_POR                                   0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_POR_RMSK                              0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_TEST0_ADDR, HWIO_CHIP_CFG0_EFUSE2_TEST0_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_TEST0_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_EFUSE2_TEST0_ADDR,v)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_EFUSE2_TEST0_ADDR,m,v,HWIO_CHIP_CFG0_EFUSE2_TEST0_IN)
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_BITS_BMSK                                   0xff
#define HWIO_CHIP_CFG0_EFUSE2_TEST0_BITS_SHFT                                    0x0

#define HWIO_CHIP_CFG0_EFUSE2_TEST1_ADDR                                  (CHIP_CFG0_REG_BASE      + 0x0000003e)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_PHYS                                  (CHIP_CFG0_REG_BASE_PHYS + 0x0000003e)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_OFFS                                  (CHIP_CFG0_REG_BASE_OFFS + 0x0000003e)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_RMSK                                        0xff
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_POR                                   0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_POR_RMSK                              0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_TEST1_ADDR, HWIO_CHIP_CFG0_EFUSE2_TEST1_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_TEST1_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_OUT(v)      \
        out_byte(HWIO_CHIP_CFG0_EFUSE2_TEST1_ADDR,v)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG0_EFUSE2_TEST1_ADDR,m,v,HWIO_CHIP_CFG0_EFUSE2_TEST1_IN)
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_BITS_BMSK                                   0xff
#define HWIO_CHIP_CFG0_EFUSE2_TEST1_BITS_SHFT                                    0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_ADDR                               (CHIP_CFG0_REG_BASE      + 0x0000003f)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x0000003f)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x0000003f)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT0_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000040)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000040)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000040)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT1_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000041)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000041)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000041)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT2_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000042)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000042)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000042)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT3_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000043)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000043)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000043)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT4_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000044)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000044)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000044)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT5_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000045)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000045)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000045)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT6_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000046)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000046)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000046)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT7_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000047)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000047)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000047)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT8_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_ADDR                               (CHIP_CFG0_REG_BASE      + 0x00000048)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_PHYS                               (CHIP_CFG0_REG_BASE_PHYS + 0x00000048)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_OFFS                               (CHIP_CFG0_REG_BASE_OFFS + 0x00000048)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_RMSK                                     0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_POR                                0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_PTE_VAL_BMSK                             0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT9_PTE_VAL_SHFT                              0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_ADDR                              (CHIP_CFG0_REG_BASE      + 0x00000049)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_PHYS                              (CHIP_CFG0_REG_BASE_PHYS + 0x00000049)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_OFFS                              (CHIP_CFG0_REG_BASE_OFFS + 0x00000049)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_RMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_POR                               0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_PTE_VAL_BMSK                            0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT10_PTE_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_ADDR                              (CHIP_CFG0_REG_BASE      + 0x0000004a)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_PHYS                              (CHIP_CFG0_REG_BASE_PHYS + 0x0000004a)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_OFFS                              (CHIP_CFG0_REG_BASE_OFFS + 0x0000004a)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_RMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_POR                               0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_PTE_VAL_BMSK                            0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT11_PTE_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_ADDR                              (CHIP_CFG0_REG_BASE      + 0x0000004b)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_PHYS                              (CHIP_CFG0_REG_BASE_PHYS + 0x0000004b)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_OFFS                              (CHIP_CFG0_REG_BASE_OFFS + 0x0000004b)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_RMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_POR                               0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_PTE_VAL_BMSK                            0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT12_PTE_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_ADDR                              (CHIP_CFG0_REG_BASE      + 0x0000004c)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_PHYS                              (CHIP_CFG0_REG_BASE_PHYS + 0x0000004c)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_OFFS                              (CHIP_CFG0_REG_BASE_OFFS + 0x0000004c)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_RMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_POR                               0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_PTE_VAL_BMSK                            0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT13_PTE_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_ADDR                              (CHIP_CFG0_REG_BASE      + 0x0000004d)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_PHYS                              (CHIP_CFG0_REG_BASE_PHYS + 0x0000004d)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_OFFS                              (CHIP_CFG0_REG_BASE_OFFS + 0x0000004d)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_RMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_POR                               0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_PTE_VAL_BMSK                            0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT14_PTE_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_ADDR                              (CHIP_CFG0_REG_BASE      + 0x0000004e)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_PHYS                              (CHIP_CFG0_REG_BASE_PHYS + 0x0000004e)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_OFFS                              (CHIP_CFG0_REG_BASE_OFFS + 0x0000004e)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_RMSK                                    0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_POR                               0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_ADDR, HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_PTE_VAL_BMSK                            0xff
#define HWIO_CHIP_CFG0_EFUSE2_VAL_OUT15_PTE_VAL_SHFT                             0x0

#define HWIO_CHIP_CFG0_EFUSE2_STATUS_ADDR                                 (CHIP_CFG0_REG_BASE      + 0x0000004f)
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_PHYS                                 (CHIP_CFG0_REG_BASE_PHYS + 0x0000004f)
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_OFFS                                 (CHIP_CFG0_REG_BASE_OFFS + 0x0000004f)
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_RMSK                                        0x1
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_POR                                  0x00000000
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_POR_RMSK                             0x000000ff
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_IN          \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_STATUS_ADDR, HWIO_CHIP_CFG0_EFUSE2_STATUS_RMSK)
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG0_EFUSE2_STATUS_ADDR, m)
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_VALID_BMSK                                  0x1
#define HWIO_CHIP_CFG0_EFUSE2_STATUS_VALID_SHFT                                  0x0

/*----------------------------------------------------------------------------
 * MODULE: CHIP_CFG1
 *--------------------------------------------------------------------------*/

#define CHIP_CFG1_REG_BASE                                            (CHIP_CFG1_BASE      + 0x00000000)
#define CHIP_CFG1_REG_BASE_PHYS                                       (CHIP_CFG1_BASE_PHYS + 0x00000000)
#define CHIP_CFG1_REG_BASE_OFFS                                       0x00000000

#define HWIO_CHIP_CFG1_PWR_CTL_ADDR                                   (CHIP_CFG1_REG_BASE      + 0x00000000)
#define HWIO_CHIP_CFG1_PWR_CTL_PHYS                                   (CHIP_CFG1_REG_BASE_PHYS + 0x00000000)
#define HWIO_CHIP_CFG1_PWR_CTL_OFFS                                   (CHIP_CFG1_REG_BASE_OFFS + 0x00000000)
#define HWIO_CHIP_CFG1_PWR_CTL_RMSK                                          0x7
#define HWIO_CHIP_CFG1_PWR_CTL_POR                                    0x00000000
#define HWIO_CHIP_CFG1_PWR_CTL_POR_RMSK                               0x000000ff
#define HWIO_CHIP_CFG1_PWR_CTL_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_CTL_ADDR, HWIO_CHIP_CFG1_PWR_CTL_RMSK)
#define HWIO_CHIP_CFG1_PWR_CTL_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_CTL_ADDR, m)
#define HWIO_CHIP_CFG1_PWR_CTL_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_PWR_CTL_ADDR,v)
#define HWIO_CHIP_CFG1_PWR_CTL_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_PWR_CTL_ADDR,m,v,HWIO_CHIP_CFG1_PWR_CTL_IN)
#define HWIO_CHIP_CFG1_PWR_CTL_EXT_MCLK_SEL_BMSK                             0x6
#define HWIO_CHIP_CFG1_PWR_CTL_EXT_MCLK_SEL_SHFT                             0x1
#define HWIO_CHIP_CFG1_PWR_CTL_USB_L2_SUSPEND_EN_BMSK                        0x1
#define HWIO_CHIP_CFG1_PWR_CTL_USB_L2_SUSPEND_EN_SHFT                        0x0

#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_ADDR                              (CHIP_CFG1_REG_BASE      + 0x00000001)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_PHYS                              (CHIP_CFG1_REG_BASE_PHYS + 0x00000001)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_OFFS                              (CHIP_CFG1_REG_BASE_OFFS + 0x00000001)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_RMSK                                    0x1f
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_POR                               0x00000016
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_BUS_MTRX_CFG_ADDR, HWIO_CHIP_CFG1_BUS_MTRX_CFG_RMSK)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_BUS_MTRX_CFG_ADDR, m)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_BUS_MTRX_CFG_ADDR,v)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_BUS_MTRX_CFG_ADDR,m,v,HWIO_CHIP_CFG1_BUS_MTRX_CFG_IN)
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_AHB_TO_EN_BMSK                          0x10
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_AHB_TO_EN_SHFT                           0x4
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_N_VAL_BMSK                               0xe
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_N_VAL_SHFT                               0x1
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_ARB_MODE_BMSK                            0x1
#define HWIO_CHIP_CFG1_BUS_MTRX_CFG_ARB_MODE_SHFT                            0x0

#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_ADDR                              (CHIP_CFG1_REG_BASE      + 0x00000002)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_PHYS                              (CHIP_CFG1_REG_BASE_PHYS + 0x00000002)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_OFFS                              (CHIP_CFG1_REG_BASE_OFFS + 0x00000002)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_RMSK                                     0x1
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_POR                               0x00000000
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_DMA_BUS_VOTE_ADDR, HWIO_CHIP_CFG1_DMA_BUS_VOTE_RMSK)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_DMA_BUS_VOTE_ADDR, m)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_DMA_BUS_VOTE_ADDR,v)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_DMA_BUS_VOTE_ADDR,m,v,HWIO_CHIP_CFG1_DMA_BUS_VOTE_IN)
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_ENABLE_BMSK                              0x1
#define HWIO_CHIP_CFG1_DMA_BUS_VOTE_ENABLE_SHFT                              0x0

#define HWIO_CHIP_CFG1_USB_BUS_VOTE_ADDR                              (CHIP_CFG1_REG_BASE      + 0x00000003)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_PHYS                              (CHIP_CFG1_REG_BASE_PHYS + 0x00000003)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_OFFS                              (CHIP_CFG1_REG_BASE_OFFS + 0x00000003)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_RMSK                                     0x1
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_POR                               0x00000000
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_USB_BUS_VOTE_ADDR, HWIO_CHIP_CFG1_USB_BUS_VOTE_RMSK)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_USB_BUS_VOTE_ADDR, m)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_USB_BUS_VOTE_ADDR,v)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_USB_BUS_VOTE_ADDR,m,v,HWIO_CHIP_CFG1_USB_BUS_VOTE_IN)
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_ENABLE_BMSK                              0x1
#define HWIO_CHIP_CFG1_USB_BUS_VOTE_ENABLE_SHFT                              0x0

#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ADDR                             (CHIP_CFG1_REG_BASE      + 0x00000004)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_PHYS                             (CHIP_CFG1_REG_BASE_PHYS + 0x00000004)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_OFFS                             (CHIP_CFG1_REG_BASE_OFFS + 0x00000004)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_RMSK                                    0x1
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_POR                              0x00000000
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_POR_RMSK                         0x000000ff
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ADDR, HWIO_CHIP_CFG1_BLSP_BUS_VOTE_RMSK)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ADDR, m)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ADDR,v)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ADDR,m,v,HWIO_CHIP_CFG1_BLSP_BUS_VOTE_IN)
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ENABLE_BMSK                             0x1
#define HWIO_CHIP_CFG1_BLSP_BUS_VOTE_ENABLE_SHFT                             0x0

#define HWIO_CHIP_CFG1_PWR_MEM_SD_ADDR                                (CHIP_CFG1_REG_BASE      + 0x00000008)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_PHYS                                (CHIP_CFG1_REG_BASE_PHYS + 0x00000008)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_OFFS                                (CHIP_CFG1_REG_BASE_OFFS + 0x00000008)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_RMSK                                       0x7
#define HWIO_CHIP_CFG1_PWR_MEM_SD_POR                                 0x00000007
#define HWIO_CHIP_CFG1_PWR_MEM_SD_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG1_PWR_MEM_SD_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_MEM_SD_ADDR, HWIO_CHIP_CFG1_PWR_MEM_SD_RMSK)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_MEM_SD_ADDR, m)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_PWR_MEM_SD_ADDR,v)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_PWR_MEM_SD_ADDR,m,v,HWIO_CHIP_CFG1_PWR_MEM_SD_IN)
#define HWIO_CHIP_CFG1_PWR_MEM_SD_UART_MEM_SD_BMSK                           0x4
#define HWIO_CHIP_CFG1_PWR_MEM_SD_UART_MEM_SD_SHFT                           0x2
#define HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_BMSK                             0x2
#define HWIO_CHIP_CFG1_PWR_MEM_SD_USBRAM_SD_SHFT                             0x1
#define HWIO_CHIP_CFG1_PWR_MEM_SD_TRACE_MEM_SD_BMSK                          0x1
#define HWIO_CHIP_CFG1_PWR_MEM_SD_TRACE_MEM_SD_SHFT                          0x0

#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_ADDR                        (CHIP_CFG1_REG_BASE      + 0x0000000b)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_PHYS                        (CHIP_CFG1_REG_BASE_PHYS + 0x0000000b)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_OFFS                        (CHIP_CFG1_REG_BASE_OFFS + 0x0000000b)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_RMSK                              0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_POR                         0x00000000
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_POR_RMSK                    0x000000ff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_ADDR, HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_RMSK)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_ADDR, m)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_ADDR,v)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_ADDR,m,v,HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_IN)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_EN_BMSK                           0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_RAM_EN_SHFT                            0x0

#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_ADDR                        (CHIP_CFG1_REG_BASE      + 0x0000000c)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_PHYS                        (CHIP_CFG1_REG_BASE_PHYS + 0x0000000c)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_OFFS                        (CHIP_CFG1_REG_BASE_OFFS + 0x0000000c)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_RMSK                              0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_POR                         0x00000000
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_POR_RMSK                    0x000000ff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_ADDR, HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_RMSK)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_ADDR, m)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_ADDR,v)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_ADDR,m,v,HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_IN)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_EN_BMSK                           0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_SD_ROM_EN_SHFT                            0x0

#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ADDR                  (CHIP_CFG1_REG_BASE      + 0x0000000d)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_PHYS                  (CHIP_CFG1_REG_BASE_PHYS + 0x0000000d)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_OFFS                  (CHIP_CFG1_REG_BASE_OFFS + 0x0000000d)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_RMSK                        0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_POR                   0x00000000
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_POR_RMSK              0x000000ff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ADDR, HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_RMSK)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ADDR, m)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ADDR,v)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ADDR,m,v,HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_IN)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ON_BMSK                     0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_RAM_ON_SHFT                      0x0

#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ADDR                  (CHIP_CFG1_REG_BASE      + 0x0000000e)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_PHYS                  (CHIP_CFG1_REG_BASE_PHYS + 0x0000000e)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_OFFS                  (CHIP_CFG1_REG_BASE_OFFS + 0x0000000e)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_RMSK                        0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_POR                   0x00000000
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_POR_RMSK              0x000000ff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ADDR, HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_RMSK)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ADDR, m)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ADDR,v)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ADDR,m,v,HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_IN)
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ON_BMSK                     0xff
#define HWIO_CHIP_CFG1_PWR_SYS_MEM_FORCE_DS_ROM_ON_SHFT                      0x0

#define HWIO_CHIP_CFG1_CLK_CFG_FLL_ADDR                               (CHIP_CFG1_REG_BASE      + 0x00000010)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_PHYS                               (CHIP_CFG1_REG_BASE_PHYS + 0x00000010)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_OFFS                               (CHIP_CFG1_REG_BASE_OFFS + 0x00000010)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_RMSK                                     0x7f
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_POR                                0x00000020
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_POR_RMSK                           0x000000ff
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_FLL_ADDR, HWIO_CHIP_CFG1_CLK_CFG_FLL_RMSK)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_FLL_ADDR, m)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_CLK_CFG_FLL_ADDR,v)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_CLK_CFG_FLL_ADDR,m,v,HWIO_CHIP_CFG1_CLK_CFG_FLL_IN)
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_DIV2_BOOT_FREQ_BMSK                      0x40
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_DIV2_BOOT_FREQ_SHFT                       0x6
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_SYSFLL_LVAL_HW_CTRL_BMSK                 0x20
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_SYSFLL_LVAL_HW_CTRL_SHFT                  0x5
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_BUSMTRX_CLK_ON_BMSK                0x10
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_BUSMTRX_CLK_ON_SHFT                 0x4
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_MEM_CLK_ON_BMSK                     0x8
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_MEM_CLK_ON_SHFT                     0x3
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_MCU_CLK_ON_BMSK                     0x4
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_MCU_CLK_ON_SHFT                     0x2
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_FLL_SLEEP_BMSK                      0x2
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_FLL_SLEEP_SHFT                      0x1
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_FLL_CLK_ON_BMSK                     0x1
#define HWIO_CHIP_CFG1_CLK_CFG_FLL_FORCE_FLL_CLK_ON_SHFT                     0x0

#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_ADDR                             (CHIP_CFG1_REG_BASE      + 0x00000011)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_PHYS                             (CHIP_CFG1_REG_BASE_PHYS + 0x00000011)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_OFFS                             (CHIP_CFG1_REG_BASE_OFFS + 0x00000011)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_RMSK                                   0xff
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_POR                              0x00000001
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_POR_RMSK                         0x000000ff
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_SPI_M_ADDR, HWIO_CHIP_CFG1_CLK_CFG_SPI_M_RMSK)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_SPI_M_ADDR, m)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_CLK_CFG_SPI_M_ADDR,v)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_CLK_CFG_SPI_M_ADDR,m,v,HWIO_CHIP_CFG1_CLK_CFG_SPI_M_IN)
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_DIV_RATIO_BMSK                         0xff
#define HWIO_CHIP_CFG1_CLK_CFG_SPI_M_DIV_RATIO_SHFT                          0x0

#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_ADDR                             (CHIP_CFG1_REG_BASE      + 0x00000012)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_PHYS                             (CHIP_CFG1_REG_BASE_PHYS + 0x00000012)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_OFFS                             (CHIP_CFG1_REG_BASE_OFFS + 0x00000012)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_RMSK                                   0xff
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_POR                              0x00000001
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_POR_RMSK                         0x000000ff
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_I2C_M_ADDR, HWIO_CHIP_CFG1_CLK_CFG_I2C_M_RMSK)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_I2C_M_ADDR, m)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_CLK_CFG_I2C_M_ADDR,v)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_CLK_CFG_I2C_M_ADDR,m,v,HWIO_CHIP_CFG1_CLK_CFG_I2C_M_IN)
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_DIV_RATIO_BMSK                         0xff
#define HWIO_CHIP_CFG1_CLK_CFG_I2C_M_DIV_RATIO_SHFT                          0x0

#define HWIO_CHIP_CFG1_CLK_CFG_UART_ADDR                              (CHIP_CFG1_REG_BASE      + 0x00000013)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_PHYS                              (CHIP_CFG1_REG_BASE_PHYS + 0x00000013)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_OFFS                              (CHIP_CFG1_REG_BASE_OFFS + 0x00000013)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_RMSK                                    0xff
#define HWIO_CHIP_CFG1_CLK_CFG_UART_POR                               0x00000001
#define HWIO_CHIP_CFG1_CLK_CFG_UART_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG1_CLK_CFG_UART_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_UART_ADDR, HWIO_CHIP_CFG1_CLK_CFG_UART_RMSK)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_CLK_CFG_UART_ADDR, m)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_CLK_CFG_UART_ADDR,v)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_CLK_CFG_UART_ADDR,m,v,HWIO_CHIP_CFG1_CLK_CFG_UART_IN)
#define HWIO_CHIP_CFG1_CLK_CFG_UART_DIV_RATIO_BMSK                          0xff
#define HWIO_CHIP_CFG1_CLK_CFG_UART_DIV_RATIO_SHFT                           0x0

#define HWIO_CHIP_CFG1_RST_USB_SS_ADDR                                (CHIP_CFG1_REG_BASE      + 0x00000020)
#define HWIO_CHIP_CFG1_RST_USB_SS_PHYS                                (CHIP_CFG1_REG_BASE_PHYS + 0x00000020)
#define HWIO_CHIP_CFG1_RST_USB_SS_OFFS                                (CHIP_CFG1_REG_BASE_OFFS + 0x00000020)
#define HWIO_CHIP_CFG1_RST_USB_SS_RMSK                                      0x1f
#define HWIO_CHIP_CFG1_RST_USB_SS_POR                                 0x0000000e
#define HWIO_CHIP_CFG1_RST_USB_SS_POR_RMSK                            0x000000ff
#define HWIO_CHIP_CFG1_RST_USB_SS_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_RST_USB_SS_ADDR, HWIO_CHIP_CFG1_RST_USB_SS_RMSK)
#define HWIO_CHIP_CFG1_RST_USB_SS_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_RST_USB_SS_ADDR, m)
#define HWIO_CHIP_CFG1_RST_USB_SS_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_RST_USB_SS_ADDR,v)
#define HWIO_CHIP_CFG1_RST_USB_SS_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_RST_USB_SS_ADDR,m,v,HWIO_CHIP_CFG1_RST_USB_SS_IN)
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_RST_SEL_BMSK                       0x10
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_RST_SEL_SHFT                        0x4
#define HWIO_CHIP_CFG1_RST_USB_SS_USBCTRL_AHB_RESET_BMSK                     0x8
#define HWIO_CHIP_CFG1_RST_USB_SS_USBCTRL_AHB_RESET_SHFT                     0x3
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_AHB_RESET_BMSK                      0x4
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_AHB_RESET_SHFT                      0x2
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_WRPR_RESET_BMSK                     0x2
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_WRPR_RESET_SHFT                     0x1
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_ATE_RESET_BMSK                      0x1
#define HWIO_CHIP_CFG1_RST_USB_SS_USBPHY_ATE_RESET_SHFT                      0x0

#define HWIO_CHIP_CFG1_RST_BLSP_ADDR                                  (CHIP_CFG1_REG_BASE      + 0x00000021)
#define HWIO_CHIP_CFG1_RST_BLSP_PHYS                                  (CHIP_CFG1_REG_BASE_PHYS + 0x00000021)
#define HWIO_CHIP_CFG1_RST_BLSP_OFFS                                  (CHIP_CFG1_REG_BASE_OFFS + 0x00000021)
#define HWIO_CHIP_CFG1_RST_BLSP_RMSK                                         0xf
#define HWIO_CHIP_CFG1_RST_BLSP_POR                                   0x0000000f
#define HWIO_CHIP_CFG1_RST_BLSP_POR_RMSK                              0x000000ff
#define HWIO_CHIP_CFG1_RST_BLSP_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_RST_BLSP_ADDR, HWIO_CHIP_CFG1_RST_BLSP_RMSK)
#define HWIO_CHIP_CFG1_RST_BLSP_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_RST_BLSP_ADDR, m)
#define HWIO_CHIP_CFG1_RST_BLSP_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_RST_BLSP_ADDR,v)
#define HWIO_CHIP_CFG1_RST_BLSP_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_RST_BLSP_ADDR,m,v,HWIO_CHIP_CFG1_RST_BLSP_IN)
#define HWIO_CHIP_CFG1_RST_BLSP_BLSP_RESET_BMSK                              0x8
#define HWIO_CHIP_CFG1_RST_BLSP_BLSP_RESET_SHFT                              0x3
#define HWIO_CHIP_CFG1_RST_BLSP_UART_RESET_BMSK                              0x4
#define HWIO_CHIP_CFG1_RST_BLSP_UART_RESET_SHFT                              0x2
#define HWIO_CHIP_CFG1_RST_BLSP_SPI_M_RESET_BMSK                             0x2
#define HWIO_CHIP_CFG1_RST_BLSP_SPI_M_RESET_SHFT                             0x1
#define HWIO_CHIP_CFG1_RST_BLSP_I2C_M_RESET_BMSK                             0x1
#define HWIO_CHIP_CFG1_RST_BLSP_I2C_M_RESET_SHFT                             0x0

#define HWIO_CHIP_CFG1_RST_BUS_MTRX_ADDR                              (CHIP_CFG1_REG_BASE      + 0x00000022)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_PHYS                              (CHIP_CFG1_REG_BASE_PHYS + 0x00000022)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_OFFS                              (CHIP_CFG1_REG_BASE_OFFS + 0x00000022)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_RMSK                                     0x3
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_POR                               0x00000000
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_POR_RMSK                          0x000000ff
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_RST_BUS_MTRX_ADDR, HWIO_CHIP_CFG1_RST_BUS_MTRX_RMSK)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_RST_BUS_MTRX_ADDR, m)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_RST_BUS_MTRX_ADDR,v)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_RST_BUS_MTRX_ADDR,m,v,HWIO_CHIP_CFG1_RST_BUS_MTRX_IN)
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_PIF_MASTER_RESET_BMSK                    0x2
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_PIF_MASTER_RESET_SHFT                    0x1
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_AHB_RESET_BMSK                           0x1
#define HWIO_CHIP_CFG1_RST_BUS_MTRX_AHB_RESET_SHFT                           0x0

#define HWIO_CHIP_CFG1_RST_MISC_ADDR                                  (CHIP_CFG1_REG_BASE      + 0x00000023)
#define HWIO_CHIP_CFG1_RST_MISC_PHYS                                  (CHIP_CFG1_REG_BASE_PHYS + 0x00000023)
#define HWIO_CHIP_CFG1_RST_MISC_OFFS                                  (CHIP_CFG1_REG_BASE_OFFS + 0x00000023)
#define HWIO_CHIP_CFG1_RST_MISC_RMSK                                         0x7
#define HWIO_CHIP_CFG1_RST_MISC_POR                                   0x00000000
#define HWIO_CHIP_CFG1_RST_MISC_POR_RMSK                              0x000000ff
#define HWIO_CHIP_CFG1_RST_MISC_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_RST_MISC_ADDR, HWIO_CHIP_CFG1_RST_MISC_RMSK)
#define HWIO_CHIP_CFG1_RST_MISC_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_RST_MISC_ADDR, m)
#define HWIO_CHIP_CFG1_RST_MISC_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_RST_MISC_ADDR,v)
#define HWIO_CHIP_CFG1_RST_MISC_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_RST_MISC_ADDR,m,v,HWIO_CHIP_CFG1_RST_MISC_IN)
#define HWIO_CHIP_CFG1_RST_MISC_LED_GLOBAL_RESET_BMSK                        0x4
#define HWIO_CHIP_CFG1_RST_MISC_LED_GLOBAL_RESET_SHFT                        0x2
#define HWIO_CHIP_CFG1_RST_MISC_DIAG_DEBUG_RESET_BMSK                        0x2
#define HWIO_CHIP_CFG1_RST_MISC_DIAG_DEBUG_RESET_SHFT                        0x1
#define HWIO_CHIP_CFG1_RST_MISC_DMA_SS_RESET_BMSK                            0x1
#define HWIO_CHIP_CFG1_RST_MISC_DMA_SS_RESET_SHFT                            0x0

#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_ADDR                        (CHIP_CFG1_REG_BASE      + 0x00000030)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_PHYS                        (CHIP_CFG1_REG_BASE_PHYS + 0x00000030)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_OFFS                        (CHIP_CFG1_REG_BASE_OFFS + 0x00000030)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_RMSK                              0xff
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_POR                         0x000000cc
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_POR_RMSK                    0x000000ff
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_IN          \
        in_byte_masked(HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_ADDR, HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_RMSK)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_INM(m)      \
        in_byte_masked(HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_ADDR, m)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_OUT(v)      \
        out_byte(HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_ADDR,v)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_OUTM(m,v) \
        out_byte_masked_ns(HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_ADDR,m,v,HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_IN)
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_RD_WAIT_BMSK                      0xf0
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_RD_WAIT_SHFT                       0x4
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_WR_WAIT_BMSK                       0xf
#define HWIO_CHIP_CFG1_ANA_WAIT_STATE_CTL_WR_WAIT_SHFT                       0x0

#endif /* __USB_HWIO_9410_H__ */
