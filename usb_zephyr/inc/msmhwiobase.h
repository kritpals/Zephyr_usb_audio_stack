#ifndef __MSMHWIOBASE_H__
#define __MSMHWIOBASE_H__
/*
===========================================================================
*/
/**
  @file msmhwiobase.h
  @brief Auto-generated HWIO base include file.
*/
/*
  ===========================================================================

  Copyright (c) 2017 Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/api/systemdrivers/hwio/whs9410/msmhwiobase.h#1 $
  $DateTime: 2017/04/04 22:16:44 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: DMA
 *--------------------------------------------------------------------------*/

#define DMA_BASE                                                    0x00030000
#define DMA_BASE_SIZE                                               0x000003ff
#define DMA_BASE_PHYS                                               0x00030000

/*----------------------------------------------------------------------------
 * BASE: MCU_SS
 *--------------------------------------------------------------------------*/

#define MCU_SS_BASE                                                 0x00031000
#define MCU_SS_BASE_SIZE                                            0x0000007f
#define MCU_SS_BASE_PHYS                                            0x00031000

/*----------------------------------------------------------------------------
 * BASE: AUDIO_TIMER
 *--------------------------------------------------------------------------*/

#define AUDIO_TIMER_BASE                                            0x00032000
#define AUDIO_TIMER_BASE_SIZE                                       0x0000003f
#define AUDIO_TIMER_BASE_PHYS                                       0x00032000

/*----------------------------------------------------------------------------
 * BASE: BUS_TIMOUT
 *--------------------------------------------------------------------------*/

#define BUS_TIMOUT_BASE                                             0x00033000
#define BUS_TIMOUT_BASE_SIZE                                        0x0000003f
#define BUS_TIMOUT_BASE_PHYS                                        0x00033000

/*----------------------------------------------------------------------------
 * BASE: LED_DRIVER_1
 *--------------------------------------------------------------------------*/

#define LED_DRIVER_1_BASE                                           0x00034000
#define LED_DRIVER_1_BASE_SIZE                                      0x00000fff
#define LED_DRIVER_1_BASE_PHYS                                      0x00034000

/*----------------------------------------------------------------------------
 * BASE: LED_DRIVER_2
 *--------------------------------------------------------------------------*/

#define LED_DRIVER_2_BASE                                           0x00035000
#define LED_DRIVER_2_BASE_SIZE                                      0x00000fff
#define LED_DRIVER_2_BASE_PHYS                                      0x00035000

/*----------------------------------------------------------------------------
 * BASE: LED_DRIVER_3
 *--------------------------------------------------------------------------*/

#define LED_DRIVER_3_BASE                                           0x00036000
#define LED_DRIVER_3_BASE_SIZE                                      0x00000fff
#define LED_DRIVER_3_BASE_PHYS                                      0x00036000

/*----------------------------------------------------------------------------
 * BASE: CM_DWC_USB2
 *--------------------------------------------------------------------------*/

#define CM_DWC_USB2_BASE                                            0x00037000
#define CM_DWC_USB2_BASE_SIZE                                       0x000000bb
#define CM_DWC_USB2_BASE_PHYS                                       0x00037000

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY
 *--------------------------------------------------------------------------*/

#define AHB2PHY_BASE                                                0x00037800
#define AHB2PHY_BASE_SIZE                                           0x000003ff
#define AHB2PHY_BASE_PHYS                                           0x00037800

/*----------------------------------------------------------------------------
 * BASE: AHB2PHY_BROADCAST
 *--------------------------------------------------------------------------*/

#define AHB2PHY_BROADCAST_BASE                                      0x00037c00
#define AHB2PHY_BROADCAST_BASE_SIZE                                 0x000003ff
#define AHB2PHY_BROADCAST_BASE_PHYS                                 0x00037c00

/*----------------------------------------------------------------------------
 * BASE: USB20S
 *--------------------------------------------------------------------------*/

#define USB20S_BASE                                                 0x00038000
#define USB20S_BASE_SIZE                                            0x000f89ff
#define USB20S_BASE_PHYS                                            0x00038000

/*----------------------------------------------------------------------------
 * BASE: BLSP
 *--------------------------------------------------------------------------*/

#define BLSP_BASE                                                   0x00238000
#define BLSP_BASE_SIZE                                              0x000365ff
#define BLSP_BASE_PHYS                                              0x00238000


#endif /* __MSMHWIOBASE_H__ */
