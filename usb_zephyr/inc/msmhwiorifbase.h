#ifndef __MSMHWIORIFBASE_H__
#define __MSMHWIORIFBASE_H__
/*
===========================================================================
*/
/**
  @file msmhwiorifbase.h
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

  $Header: //components/rel/audio.whs/1.0/mcu_proc/core/api/systemdrivers/hwio/whs9410/msmhwiorifbase.h#1 $
  $DateTime: 2017/05/18 22:58:38 $
  $Author: pwbldsvc $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * BASE: CHIP_CFG0
 *--------------------------------------------------------------------------*/

#define CHIP_CFG0_BASE                                              0x00011001
#define CHIP_CFG0_BASE_SIZE                                         0x0000004f
#define CHIP_CFG0_BASE_PHYS                                         0x00011001

/*----------------------------------------------------------------------------
 * BASE: CHIP_CFG1
 *--------------------------------------------------------------------------*/

#define CHIP_CFG1_BASE                                              0x00012001
#define CHIP_CFG1_BASE_SIZE                                         0x0000003f
#define CHIP_CFG1_BASE_PHYS                                         0x00012001

/*----------------------------------------------------------------------------
 * BASE: FLL
 *--------------------------------------------------------------------------*/

#define FLL_BASE                                                    0x00013001
#define FLL_BASE_SIZE                                               0x0000003f
#define FLL_BASE_PHYS                                               0x00013001

/*----------------------------------------------------------------------------
 * BASE: TLMM_TLMM
 *--------------------------------------------------------------------------*/

#define TLMM_TLMM_BASE                                              0x00014001
#define TLMM_TLMM_BASE_SIZE                                         0x0000002f
#define TLMM_TLMM_BASE_PHYS                                         0x00014001

/*----------------------------------------------------------------------------
 * BASE: INTR_CTRL_INTR_CTRL
 *--------------------------------------------------------------------------*/

#define INTR_CTRL_INTR_CTRL_BASE                                    0x00015001
#define INTR_CTRL_INTR_CTRL_BASE_SIZE                               0x000000ef
#define INTR_CTRL_INTR_CTRL_BASE_PHYS                               0x00015001

/*----------------------------------------------------------------------------
 * BASE: CDC_ANC0
 *--------------------------------------------------------------------------*/

#define CDC_ANC0_BASE                                               0x00016001
#define CDC_ANC0_BASE_SIZE                                          0x00000017
#define CDC_ANC0_BASE_PHYS                                          0x00016001

/*----------------------------------------------------------------------------
 * BASE: CDC_ANC1
 *--------------------------------------------------------------------------*/

#define CDC_ANC1_BASE                                               0x00016019
#define CDC_ANC1_BASE_SIZE                                          0x00000017
#define CDC_ANC1_BASE_PHYS                                          0x00016019

/*----------------------------------------------------------------------------
 * BASE: CDC_TX0
 *--------------------------------------------------------------------------*/

#define CDC_TX0_BASE                                                0x00016031
#define CDC_TX0_BASE_SIZE                                           0x0000000f
#define CDC_TX0_BASE_PHYS                                           0x00016031

/*----------------------------------------------------------------------------
 * BASE: CDC_TX1
 *--------------------------------------------------------------------------*/

#define CDC_TX1_BASE                                                0x00016041
#define CDC_TX1_BASE_SIZE                                           0x0000000f
#define CDC_TX1_BASE_PHYS                                           0x00016041

/*----------------------------------------------------------------------------
 * BASE: CDC_TX2
 *--------------------------------------------------------------------------*/

#define CDC_TX2_BASE                                                0x00016051
#define CDC_TX2_BASE_SIZE                                           0x0000000f
#define CDC_TX2_BASE_PHYS                                           0x00016051

/*----------------------------------------------------------------------------
 * BASE: CDC_COMPANDER1
 *--------------------------------------------------------------------------*/

#define CDC_COMPANDER1_BASE                                         0x00016101
#define CDC_COMPANDER1_BASE_SIZE                                    0x00000007
#define CDC_COMPANDER1_BASE_PHYS                                    0x00016101

/*----------------------------------------------------------------------------
 * BASE: CDC_COMPANDER2
 *--------------------------------------------------------------------------*/

#define CDC_COMPANDER2_BASE                                         0x00016109
#define CDC_COMPANDER2_BASE_SIZE                                    0x00000007
#define CDC_COMPANDER2_BASE_PHYS                                    0x00016109

/*----------------------------------------------------------------------------
 * BASE: CDC_RX1
 *--------------------------------------------------------------------------*/

#define CDC_RX1_BASE                                                0x00016155
#define CDC_RX1_BASE_SIZE                                           0x00000013
#define CDC_RX1_BASE_PHYS                                           0x00016155

/*----------------------------------------------------------------------------
 * BASE: CDC_RX2
 *--------------------------------------------------------------------------*/

#define CDC_RX2_BASE                                                0x00016169
#define CDC_RX2_BASE_SIZE                                           0x00000013
#define CDC_RX2_BASE_PHYS                                           0x00016169

/*----------------------------------------------------------------------------
 * BASE: CDC_EQ_IIR0
 *--------------------------------------------------------------------------*/

#define CDC_EQ_IIR0_BASE                                            0x000161d1
#define CDC_EQ_IIR0_BASE_SIZE                                       0x0000000f
#define CDC_EQ_IIR0_BASE_PHYS                                       0x000161d1

/*----------------------------------------------------------------------------
 * BASE: CDC_EQ_IIR1
 *--------------------------------------------------------------------------*/

#define CDC_EQ_IIR1_BASE                                            0x000161e1
#define CDC_EQ_IIR1_BASE_SIZE                                       0x0000000f
#define CDC_EQ_IIR1_BASE_PHYS                                       0x000161e1

/*----------------------------------------------------------------------------
 * BASE: CDC_CLSH_CDC_CLSH
 *--------------------------------------------------------------------------*/

#define CDC_CLSH_CDC_CLSH_BASE                                      0x00016201
#define CDC_CLSH_CDC_CLSH_BASE_SIZE                                 0x00000017
#define CDC_CLSH_CDC_CLSH_BASE_PHYS                                 0x00016201

/*----------------------------------------------------------------------------
 * BASE: MIXING_ASRC0
 *--------------------------------------------------------------------------*/

#define MIXING_ASRC0_BASE                                           0x00016255
#define MIXING_ASRC0_BASE_SIZE                                      0x0000000b
#define MIXING_ASRC0_BASE_PHYS                                      0x00016255

/*----------------------------------------------------------------------------
 * BASE: MIXING_ASRC1
 *--------------------------------------------------------------------------*/

#define MIXING_ASRC1_BASE                                           0x00016261
#define MIXING_ASRC1_BASE_SIZE                                      0x0000000b
#define MIXING_ASRC1_BASE_PHYS                                      0x00016261

/*----------------------------------------------------------------------------
 * BASE: CDC_SIDETONE_SRC0
 *--------------------------------------------------------------------------*/

#define CDC_SIDETONE_SRC0_BASE                                      0x000162b5
#define CDC_SIDETONE_SRC0_BASE_SIZE                                 0x00000003
#define CDC_SIDETONE_SRC0_BASE_PHYS                                 0x000162b5

/*----------------------------------------------------------------------------
 * BASE: SIDETONE_ASRC0
 *--------------------------------------------------------------------------*/

#define SIDETONE_ASRC0_BASE                                         0x000162bd
#define SIDETONE_ASRC0_BASE_SIZE                                    0x0000000b
#define SIDETONE_ASRC0_BASE_PHYS                                    0x000162bd

/*----------------------------------------------------------------------------
 * BASE: EC_REF_HQ0
 *--------------------------------------------------------------------------*/

#define EC_REF_HQ0_BASE                                             0x000162d5
#define EC_REF_HQ0_BASE_SIZE                                        0x00000007
#define EC_REF_HQ0_BASE_PHYS                                        0x000162d5

/*----------------------------------------------------------------------------
 * BASE: EC_REF_HQ1
 *--------------------------------------------------------------------------*/

#define EC_REF_HQ1_BASE                                             0x000162dd
#define EC_REF_HQ1_BASE_SIZE                                        0x00000007
#define EC_REF_HQ1_BASE_PHYS                                        0x000162dd

/*----------------------------------------------------------------------------
 * BASE: EC_ASRC0
 *--------------------------------------------------------------------------*/

#define EC_ASRC0_BASE                                               0x000162e5
#define EC_ASRC0_BASE_SIZE                                          0x0000000b
#define EC_ASRC0_BASE_PHYS                                          0x000162e5

/*----------------------------------------------------------------------------
 * BASE: EC_ASRC1
 *--------------------------------------------------------------------------*/

#define EC_ASRC1_BASE                                               0x000162f1
#define EC_ASRC1_BASE_SIZE                                          0x0000000b
#define EC_ASRC1_BASE_PHYS                                          0x000162f1

/*----------------------------------------------------------------------------
 * BASE: CDC_RX_INP_MUX_CDC_RX_INP_MUX
 *--------------------------------------------------------------------------*/

#define CDC_RX_INP_MUX_CDC_RX_INP_MUX_BASE                          0x00016301
#define CDC_RX_INP_MUX_CDC_RX_INP_MUX_BASE_SIZE                     0x0000001b
#define CDC_RX_INP_MUX_CDC_RX_INP_MUX_BASE_PHYS                     0x00016301

/*----------------------------------------------------------------------------
 * BASE: CDC_TX_INP_MUX_CDC_TX_INP_MUX
 *--------------------------------------------------------------------------*/

#define CDC_TX_INP_MUX_CDC_TX_INP_MUX_BASE                          0x0001631d
#define CDC_TX_INP_MUX_CDC_TX_INP_MUX_BASE_SIZE                     0x00000013
#define CDC_TX_INP_MUX_CDC_TX_INP_MUX_BASE_PHYS                     0x0001631d

/*----------------------------------------------------------------------------
 * BASE: CDC_SIDETONE_IIR_INP_MUX_CDC_SIDETONE_IIR_INP_MUX
 *--------------------------------------------------------------------------*/

#define CDC_SIDETONE_IIR_INP_MUX_CDC_SIDETONE_IIR_INP_MUX_BASE      0x00016331
#define CDC_SIDETONE_IIR_INP_MUX_CDC_SIDETONE_IIR_INP_MUX_BASE_SIZE 0x00000007
#define CDC_SIDETONE_IIR_INP_MUX_CDC_SIDETONE_IIR_INP_MUX_BASE_PHYS 0x00016331

/*----------------------------------------------------------------------------
 * BASE: CDC_IF_ROUTER_CDC_IF_ROUTER
 *--------------------------------------------------------------------------*/

#define CDC_IF_ROUTER_CDC_IF_ROUTER_BASE                            0x0001633d
#define CDC_IF_ROUTER_CDC_IF_ROUTER_BASE_SIZE                       0x00000003
#define CDC_IF_ROUTER_CDC_IF_ROUTER_BASE_PHYS                       0x0001633d

/*----------------------------------------------------------------------------
 * BASE: CDC_CLK_RST_CTRL_CDC_CLK_RST_CTRL
 *--------------------------------------------------------------------------*/

#define CDC_CLK_RST_CTRL_CDC_CLK_RST_CTRL_BASE                      0x00016341
#define CDC_CLK_RST_CTRL_CDC_CLK_RST_CTRL_BASE_SIZE                 0x00000007
#define CDC_CLK_RST_CTRL_CDC_CLK_RST_CTRL_BASE_PHYS                 0x00016341

/*----------------------------------------------------------------------------
 * BASE: CDC_SIDETONE_IIR0
 *--------------------------------------------------------------------------*/

#define CDC_SIDETONE_IIR0_BASE                                      0x00016355
#define CDC_SIDETONE_IIR0_BASE_SIZE                                 0x0000000f
#define CDC_SIDETONE_IIR0_BASE_PHYS                                 0x00016355

/*----------------------------------------------------------------------------
 * BASE: CDC_TOP_CDC_TOP
 *--------------------------------------------------------------------------*/

#define CDC_TOP_CDC_TOP_BASE                                        0x00016381
#define CDC_TOP_CDC_TOP_BASE_SIZE                                   0x0000002f
#define CDC_TOP_CDC_TOP_BASE_PHYS                                   0x00016381

/*----------------------------------------------------------------------------
 * BASE: CDC_DSD0
 *--------------------------------------------------------------------------*/

#define CDC_DSD0_BASE                                               0x000163b1
#define CDC_DSD0_BASE_SIZE                                          0x0000000f
#define CDC_DSD0_BASE_PHYS                                          0x000163b1

/*----------------------------------------------------------------------------
 * BASE: CDC_DSD1
 *--------------------------------------------------------------------------*/

#define CDC_DSD1_BASE                                               0x000163c1
#define CDC_DSD1_BASE_SIZE                                          0x0000000f
#define CDC_DSD1_BASE_PHYS                                          0x000163c1

/*----------------------------------------------------------------------------
 * BASE: CDC_RX_IDLE_DET_CDC_RX_IDLE_DET
 *--------------------------------------------------------------------------*/

#define CDC_RX_IDLE_DET_CDC_RX_IDLE_DET_BASE                        0x000163d1
#define CDC_RX_IDLE_DET_CDC_RX_IDLE_DET_BASE_SIZE                   0x00000007
#define CDC_RX_IDLE_DET_CDC_RX_IDLE_DET_BASE_PHYS                   0x000163d1

/*----------------------------------------------------------------------------
 * BASE: CDC_DEBUG_CDC_DEBUG
 *--------------------------------------------------------------------------*/

#define CDC_DEBUG_CDC_DEBUG_BASE                                    0x000165a1
#define CDC_DEBUG_CDC_DEBUG_BASE_SIZE                               0x0000005e
#define CDC_DEBUG_CDC_DEBUG_BASE_PHYS                               0x000165a1

/*----------------------------------------------------------------------------
 * BASE: ANA
 *--------------------------------------------------------------------------*/

#define ANA_BASE                                                    0x00017000
#define ANA_BASE_SIZE                                               0x00000022
#define ANA_BASE_PHYS                                               0x00017000

/*----------------------------------------------------------------------------
 * BASE: BIAS
 *--------------------------------------------------------------------------*/

#define BIAS_BASE                                                   0x00017028
#define BIAS_BASE_SIZE                                              0x00000001
#define BIAS_BASE_PHYS                                              0x00017028

/*----------------------------------------------------------------------------
 * BASE: LED
 *--------------------------------------------------------------------------*/

#define LED_BASE                                                    0x0001702e
#define LED_BASE_SIZE                                               0x00000005
#define LED_BASE_PHYS                                               0x0001702e

/*----------------------------------------------------------------------------
 * BASE: LDOH
 *--------------------------------------------------------------------------*/

#define LDOH_BASE                                                   0x0001703a
#define LDOH_BASE_SIZE                                              0x00000003
#define LDOH_BASE_PHYS                                              0x0001703a

/*----------------------------------------------------------------------------
 * BASE: LDOL
 *--------------------------------------------------------------------------*/

#define LDOL_BASE                                                   0x00017040
#define LDOL_BASE_SIZE                                              0x00000001
#define LDOL_BASE_PHYS                                              0x00017040

/*----------------------------------------------------------------------------
 * BASE: BUCK_5V
 *--------------------------------------------------------------------------*/

#define BUCK_5V_BASE                                                0x00017044
#define BUCK_5V_BASE_SIZE                                           0x0000000e
#define BUCK_5V_BASE_PHYS                                           0x00017044

/*----------------------------------------------------------------------------
 * BASE: MBHC
 *--------------------------------------------------------------------------*/

#define MBHC_BASE                                                   0x00017056
#define MBHC_BASE_SIZE                                              0x00000006
#define MBHC_BASE_PHYS                                              0x00017056

/*----------------------------------------------------------------------------
 * BASE: MICB1
 *--------------------------------------------------------------------------*/

#define MICB1_BASE                                                  0x0001706b
#define MICB1_BASE_SIZE                                             0x00000002
#define MICB1_BASE_PHYS                                             0x0001706b

/*----------------------------------------------------------------------------
 * BASE: MICB1_MISC
 *--------------------------------------------------------------------------*/

#define MICB1_MISC_BASE                                             0x0001706e
#define MICB1_MISC_BASE_SIZE                                        0x00000003
#define MICB1_MISC_BASE_PHYS                                        0x0001706e

/*----------------------------------------------------------------------------
 * BASE: TX_COM
 *--------------------------------------------------------------------------*/

#define TX_COM_BASE                                                 0x00017077
#define TX_COM_BASE_SIZE                                            0x00000007
#define TX_COM_BASE_PHYS                                            0x00017077

/*----------------------------------------------------------------------------
 * BASE: TX_1_2
 *--------------------------------------------------------------------------*/

#define TX_1_2_BASE                                                 0x0001707f
#define TX_1_2_BASE_SIZE                                            0x00000007
#define TX_1_2_BASE_PHYS                                            0x0001707f

/*----------------------------------------------------------------------------
 * BASE: TX_3
 *--------------------------------------------------------------------------*/

#define TX_3_BASE                                                   0x00017087
#define TX_3_BASE_SIZE                                              0x00000007
#define TX_3_BASE_PHYS                                              0x00017087

/*----------------------------------------------------------------------------
 * BASE: TX
 *--------------------------------------------------------------------------*/

#define TX_BASE                                                     0x0001708f
#define TX_BASE_SIZE                                                0x00000000
#define TX_BASE_PHYS                                                0x0001708f

/*----------------------------------------------------------------------------
 * BASE: CLASSH
 *--------------------------------------------------------------------------*/

#define CLASSH_BASE                                                 0x00017097
#define CLASSH_BASE_SIZE                                            0x0000000c
#define CLASSH_BASE_PHYS                                            0x00017097

/*----------------------------------------------------------------------------
 * BASE: FLYBACK
 *--------------------------------------------------------------------------*/

#define FLYBACK_BASE                                                0x000170a4
#define FLYBACK_BASE_SIZE                                           0x0000000e
#define FLYBACK_BASE_PHYS                                           0x000170a4

/*----------------------------------------------------------------------------
 * BASE: RX
 *--------------------------------------------------------------------------*/

#define RX_BASE                                                     0x000170b3
#define RX_BASE_SIZE                                                0x00000015
#define RX_BASE_PHYS                                                0x000170b3

/*----------------------------------------------------------------------------
 * BASE: HPH
 *--------------------------------------------------------------------------*/

#define HPH_BASE                                                    0x000170c9
#define HPH_BASE_SIZE                                               0x00000017
#define HPH_BASE_PHYS                                               0x000170c9

/*----------------------------------------------------------------------------
 * BASE: ANA_NEW
 *--------------------------------------------------------------------------*/

#define ANA_NEW_BASE                                                0x00017100
#define ANA_NEW_BASE_SIZE                                           0x00000000
#define ANA_NEW_BASE_PHYS                                           0x00017100

/*----------------------------------------------------------------------------
 * BASE: HPH_NEW
 *--------------------------------------------------------------------------*/

#define HPH_NEW_BASE                                                0x00017101
#define HPH_NEW_BASE_SIZE                                           0x00000001
#define HPH_NEW_BASE_PHYS                                           0x00017101

/*----------------------------------------------------------------------------
 * BASE: CLK_SYS
 *--------------------------------------------------------------------------*/

#define CLK_SYS_BASE                                                0x0001710e
#define CLK_SYS_BASE_SIZE                                           0x00000006
#define CLK_SYS_BASE_PHYS                                           0x0001710e

/*----------------------------------------------------------------------------
 * BASE: MBHC_NEW
 *--------------------------------------------------------------------------*/

#define MBHC_NEW_BASE                                               0x0001711f
#define MBHC_NEW_BASE_SIZE                                          0x00000007
#define MBHC_NEW_BASE_PHYS                                          0x0001711f

/*----------------------------------------------------------------------------
 * BASE: HPH_NEW_INT
 *--------------------------------------------------------------------------*/

#define HPH_NEW_INT_BASE                                            0x00017132
#define HPH_NEW_INT_BASE_SIZE                                       0x0000000d
#define HPH_NEW_INT_BASE_PHYS                                       0x00017132

/*----------------------------------------------------------------------------
 * BASE: RX_NEW_INT
 *--------------------------------------------------------------------------*/

#define RX_NEW_INT_BASE                                             0x00017145
#define RX_NEW_INT_BASE_SIZE                                        0x00000002
#define RX_NEW_INT_BASE_PHYS                                        0x00017145

/*----------------------------------------------------------------------------
 * BASE: CLK_SYS_INT
 *--------------------------------------------------------------------------*/

#define CLK_SYS_INT_BASE                                            0x0001716c
#define CLK_SYS_INT_BASE_SIZE                                       0x00000011
#define CLK_SYS_INT_BASE_PHYS                                       0x0001716c

/*----------------------------------------------------------------------------
 * BASE: MBHC_NEW_INT
 *--------------------------------------------------------------------------*/

#define MBHC_NEW_INT_BASE                                           0x000171af
#define MBHC_NEW_INT_BASE_SIZE                                      0x00000003
#define MBHC_NEW_INT_BASE_PHYS                                      0x000171af

/*----------------------------------------------------------------------------
 * BASE: I2S
 *--------------------------------------------------------------------------*/

#define I2S_BASE                                                    0x00018001
#define I2S_BASE_SIZE                                               0x0000001f
#define I2S_BASE_PHYS                                               0x00018001

/*----------------------------------------------------------------------------
 * BASE: PAD_CTRL_PAD_CTRL
 *--------------------------------------------------------------------------*/

#define PAD_CTRL_PAD_CTRL_BASE                                      0x00019001
#define PAD_CTRL_PAD_CTRL_BASE_SIZE                                 0x0000003f
#define PAD_CTRL_PAD_CTRL_BASE_PHYS                                 0x00019001


#endif /* __MSMHWIORIFBASE_H__ */
