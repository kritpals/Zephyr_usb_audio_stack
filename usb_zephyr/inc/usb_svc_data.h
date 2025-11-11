/** @file usb_svc_data.h
    This header contains the API for usb service data for h2xml.

    Copyright (c) 2016-2017 QUALCOMM Technologies, Inc. (QTI).  All Rights Reserved.
    QUALCOMM Proprietary.  Export of this technology or software is regulated
    by the U.S. Government, Diversion contrary to U.S. law prohibited.
 *//*===================================================================== */

/*========================================================================
                               Edit History

$Header: //components/rel/audio.whs/1.0/mcu_proc/audio/api/usb_svc_data.h#17 $

when       who     what, where, why
------     ---    -------------------------------------------------------

========================================================================== */

#ifndef __USB_SVC_DATA_H__
#define __USB_SVC_DATA_H__

//#include "mmdefs.h"

#define WHS_USB_BW_SLOT_CFG_MASK 0xf0
#define WHS_USB_SVC_INT_US_MASK  0x0f

#define WHS_USB_DISABLE_HID_MASK 0x01
#define WHS_USB_DISABLE_DFU_MASK 0x02
#define WHS_USB_DISABLE_LOG_MASK 0x04

// USB feature flags
#define WHS_USB_FEATURE_L1_MASK              0x00000001
#define WHS_USB_FEATURE_L2_MASK              0x00000002
#define WHS_USB_FEATURE_HALT_ON_ERROR_MASK   0x00000004

// synchronize with usb_audio.h
#define WHS_USB_FREQ_8K_MASK     0x001
#define WHS_USB_FREQ_16K_MASK    0x002
#define WHS_USB_FREQ_32K_MASK    0x004
#define WHS_USB_FREQ_44P1K_MASK  0x008
#define WHS_USB_FREQ_48K_MASK    0x010
#define WHS_USB_FREQ_88P2K_MASK  0x020
#define WHS_USB_FREQ_96K_MASK    0x040
#define WHS_USB_FREQ_176P4K_MASK 0x080
#define WHS_USB_FREQ_192K_MASK   0x100
#define WHS_USB_FREQ_352P8K_MASK 0x200
#define WHS_USB_FREQ_384K_MASK   0x400

#define WHS_USB_BW_SLOT_CFG_NONE 0
#define WHS_USB_BW_SLOT_CFG_16_2 1
#define WHS_USB_BW_SLOT_CFG_24_3 2
#define WHS_USB_BW_SLOT_CFG_24_4 3
#define WHS_USB_BW_SLOT_CFG_32_4 4

#define WHS_USB_SVC_INT_US_NONE 0
#define WHS_USB_SVC_INT_US_125  1
#define WHS_USB_SVC_INT_US_250  2
#define WHS_USB_SVC_INT_US_500  3
#define WHS_USB_SVC_INT_US_1000 4
#define WHS_USB_SVC_INT_US_2000 5
#define WHS_USB_SVC_INT_US_4000 6
#define WHS_USB_SVC_INT_US_MAX  7

#define WHS_USB_HEADSET 0
#define WHS_USB_HEADPHONE 1
#define WHS_USB_ADAPTOR 2

#define UAS_BUS_CFG_SIZE     8

#define WHS_USB_SVC_MID 0x00013298 /* GUID, do not change */
#define WHS_USB_CFG_PID 0x00013299 /* GUID, do not change */
#define WHS_USB_DRV_PID 0x0001329B /* GUID, do not change */

/**
    @h2xmlm_module      {"WHS_USB_SVC_MID", WHS_USB_SVC_MID }
    @h2xmlm_toolPolicy  {Calibration}
    @h2xmlm_description {WHS USB Service Configuration }
    @{
*/

/**
 * @struct usb_svc_params
 * @brief USB configuration parameters
 */

/**
    @h2xmlp_parameter      {"WHS_USB_CFG_PID", WHS_USB_CFG_PID }
    @h2xmlp_description {USB configuration}
    @h2xmlx_expandStructs {false}
*/

struct usb_svc_params {

    uint16_t qc_pid;
    /**< @h2xmle_rangeList {USB_PID_UAC1_HEADSET                = 0x9604,
                            USB_PID_UAC2_HEADSET                = 0x9605,
                            USB_PID_UAC1_BADD3_HEADSET          = 0x9606,
                            USB_PID_UAC2_BADD3_HEADSET          = 0x9607,
                            USB_PID_UAC1_BADD3_UAC3_HEADSET     = 0x9608,
                            USB_PID_UAC2_BADD3_UAC3_HEADSET     = 0x9609,
                            USB_PID_UAC1_HEADPHONE              = 0x960A,
                            USB_PID_UAC2_HEADPHONE              = 0x960B,
                            USB_PID_UAC1_BADD3_HEADPHONE        = 0x960C,
                            USB_PID_UAC2_BADD3_HEADPHONE        = 0x960D,
                            USB_PID_UAC1_BADD3_UAC3_HEADPHONE   = 0x960E,
                            USB_PID_UAC2_BADD3_UAC3_HEADPHONE   = 0x960F,
                            USB_PID_UAC1_MICROPHONE             = 0x9610,
                            USB_PID_UAC2_MICROPHONE             = 0x9611,
                            USB_PID_UAC1_BADD3_MICROPHONE       = 0x9612,
                            USB_PID_UAC2_BADD3_MICROPHONE       = 0x9613,
                            USB_PID_UAC1_BADD3_UAC3_MICROPHONE  = 0x9614,
                            USB_PID_UAC2_BADD3_UAC3_MICROPHONE  = 0x9615}
         @h2xmle_description {QC Product ID}
         @h2xmle_default {0x9605}
    */

    uint16_t vid_override;
    /**< @h2xmle_range {0x0..0xFFFF}
         @h2xmle_description {OEM Vendor ID}
         @h2xmle_default {0}
    */
    uint16_t pid_override;
    /**< @h2xmle_range {0x0..0xFFFF}
         @h2xmle_description {OEM Vendor Product ID}
         @h2xmle_default {0}
    */

    uint8_t audio_profile;
    /**< @h2xmle_rangeList { USB_AUDIO_HEADSET         = 0,
                             USB_AUDIO_HEADSET_ADAPTOR = 1,
                             USB_AUDIO_SPEAKERPHONE    = 2,
                             USB_AUDIO_HEADPHONE       = 3,
                             USB_AUDIO_SPEAKER         = 4,
                             USB_AUDIO_MICROPHONE      = 5}
         @h2xmle_description {Target device audio profile}
         @h2xmle_default {0}
    */

    uint8_t as_disable_flags;
    /**< @h2xmle_bitfield {WHS_USB_DISABLE_HID_MASK}
         @h2xmle_bitName {DISABLE_HID}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_description {0=enable HID, 1=disable HID}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_DISABLE_DFU_MASK}
         @h2xmle_bitName {DISABLE_DFU}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_description {0=enable DFU, 1=disable DFU}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_DISABLE_LOG_MASK}
         @h2xmle_bitName {DISABLE_LOG}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_description {0=enable LOG over USB, 1=disable LOG over USB}
         @h2xmle_bitfieldEnd
    */

    uint32_t system_id1;
    /**< @h2xmle_range {0x0..0xFFFFFFFF}
         @h2xmle_description {OEM System ID1 (to check suitability of DFU update file)}
         @h2xmle_default {0x4d4f4351}
    */

    uint32_t system_id2;
    /**< @h2xmle_range {0x0..0xFFFFFFFF}
         @h2xmle_description {OEM System ID2 (to check suitability of DFU update file}
         @h2xmle_default {0x30323439}
    */

    uint16_t rx_main_as_freqs;
    /**< @h2xmle_description {RX main sampling frequencies}
         @h2xmle_bitfield {WHS_USB_FREQ_8K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_16K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_16K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_32K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_32K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_44P1K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_44P1K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_48K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_48K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_88P2K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_88P2K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_96K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_96K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_176P4K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_176P4K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_192K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_192K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_352P8K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_352P8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_384K_MASK}
         @h2xmle_bitName {RX_MAIN_FREQ_384K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd
    */

    uint8_t rx_main_as_bus_cfg[UAS_BUS_CFG_SIZE];
    /**< @h2xmle_bitfield {WHS_USB_BW_SLOT_CFG_MASK}
         @h2xmle_description {RX main bitwidth/slotsize combination}
         @h2xmle_bitName {RX_MAIN_AS_BW_SLOT_CFG}
         @h2xmle_rangeList {none=WHS_USB_BW_SLOT_CFG_NONE;
                            bitwidth16_slot2=WHS_USB_BW_SLOT_CFG_16_2;
                            bitwidth24_slot3=WHS_USB_BW_SLOT_CFG_24_3;
                            bitwidth24_slot4=WHS_USB_BW_SLOT_CFG_24_4;
                            bitwidth32_slot4=WHS_USB_BW_SLOT_CFG_32_4
                           }
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_SVC_INT_US_MASK}
         @h2xmle_description {RX main service interval}
         @h2xmle_bitName {RX_MAIN_SVC_INT}
         @h2xmle_rangeList {none=WHS_USB_SVC_INT_US_NONE;
                            serv_int_125us=WHS_USB_SVC_INT_US_125;
                            serv_int_250us=WHS_USB_SVC_INT_US_250;
                            serv_int_500us=WHS_USB_SVC_INT_US_500;
                            serv_int_1ms=WHS_USB_SVC_INT_US_1000;
                            serv_int_2ms=WHS_USB_SVC_INT_US_2000;
                            serv_int_4ms=WHS_USB_SVC_INT_US_4000
                           }
         @h2xmle_bitfieldEnd
    */




    uint16_t rx_mixin_as_freqs;
    /**< @h2xmle_description {RX mixin sampling frequencies}
         @h2xmle_bitfield {WHS_USB_FREQ_8K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_16K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_16K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_32K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_32K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_44P1K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_44P1K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_48K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_48K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_88P2K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_88P2K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_96K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_96K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_176P4K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_176P4K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_192K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_192K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_352P8K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_352P8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_384K_MASK}
         @h2xmle_bitName {RX_MIXIN_FREQ_384K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd
    */

    uint8_t rx_mixin_as_bus_cfg[UAS_BUS_CFG_SIZE];
    /**< @h2xmle_bitfield {WHS_USB_BW_SLOT_CFG_MASK}
         @h2xmle_description {RX mixin bitwidth/slotsize combination}
         @h2xmle_bitName {RX_MIXIN_AS_BW_SLOT_CFG}
         @h2xmle_rangeList {none=WHS_USB_BW_SLOT_CFG_NONE;
                            bitwidth16_slot2=WHS_USB_BW_SLOT_CFG_16_2;
                            bitwidth24_slot3=WHS_USB_BW_SLOT_CFG_24_3;
                            bitwidth24_slot4=WHS_USB_BW_SLOT_CFG_24_4;
                            bitwidth32_slot4=WHS_USB_BW_SLOT_CFG_32_4
                           }
        @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_SVC_INT_US_MASK}
         @h2xmle_description {RX mixin service interval}
         @h2xmle_bitName {RX_MIXIN_SVC_INT}
         @h2xmle_rangeList {none=WHS_USB_SVC_INT_US_NONE;
                            serv_int_125us=WHS_USB_SVC_INT_US_125;
                            serv_int_250us=WHS_USB_SVC_INT_US_250;
                            serv_int_500us=WHS_USB_SVC_INT_US_500;
                            serv_int_1ms=WHS_USB_SVC_INT_US_1000;
                            serv_int_2ms=WHS_USB_SVC_INT_US_2000;
                            serv_int_4ms=WHS_USB_SVC_INT_US_4000
                           }
         @h2xmle_bitfieldEnd
    */


    uint16_t tx_binaural_as_freqs;
    /**< @h2xmle_description {TX binaural sampling frequencies}
         @h2xmle_bitfield {WHS_USB_FREQ_8K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_16K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_16K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_32K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_32K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_44P1K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_44P1K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_48K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_48K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_88P2K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_88P2K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_96K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_96K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_176P4K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_176P4K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_192K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_192K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_352P8K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_352P8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_384K_MASK}
         @h2xmle_bitName {TX_BINAURAL_FREQ_384K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd
    */

    uint8_t tx_binaural_as_bus_cfg[UAS_BUS_CFG_SIZE];
    /**< @h2xmle_bitfield {WHS_USB_BW_SLOT_CFG_MASK}
         @h2xmle_description {TX binaural bitwidth/slotsize combination}
         @h2xmle_bitName {TX_BINAURAL_AS_BW_SLOT_CFG}
         @h2xmle_rangeList {none=WHS_USB_BW_SLOT_CFG_NONE;
                            bitwidth16_slot2=WHS_USB_BW_SLOT_CFG_16_2;
                            bitwidth24_slot3=WHS_USB_BW_SLOT_CFG_24_3;
                            bitwidth24_slot4=WHS_USB_BW_SLOT_CFG_24_4;
                            bitwidth32_slot4=WHS_USB_BW_SLOT_CFG_32_4
                           }
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_SVC_INT_US_MASK}
         @h2xmle_description {TX binaural service interval}
         @h2xmle_bitName {TX_BINAURAL_SVC_INT}
         @h2xmle_rangeList {none=WHS_USB_SVC_INT_US_NONE;
                            serv_int_125us=WHS_USB_SVC_INT_US_125;
                            serv_int_250us=WHS_USB_SVC_INT_US_250;
                            serv_int_500us=WHS_USB_SVC_INT_US_500;
                            serv_int_1ms=WHS_USB_SVC_INT_US_1000;
                            serv_int_2ms=WHS_USB_SVC_INT_US_2000;
                            serv_int_4ms=WHS_USB_SVC_INT_US_4000
                           }
         @h2xmle_bitfieldEnd
    */


    uint16_t tx_voice_as_freqs;
    /**< @h2xmle_description {TX voice sampling frequencies}
         @h2xmle_bitfield {WHS_USB_FREQ_8K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_16K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_16K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_32K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_32K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_44P1K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_44P1K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_48K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_48K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_88P2K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_88P2K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_96K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_96K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_176P4K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_176P4K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_192K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_192K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_352P8K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_352P8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_384K_MASK}
         @h2xmle_bitName {TX_VOICE_FREQ_384K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd
    */

    uint8_t tx_voice_as_bus_cfg[UAS_BUS_CFG_SIZE];
    /**< @h2xmle_bitfield {WHS_USB_BW_SLOT_CFG_MASK}
         @h2xmle_description {TX voice bitwidth/slotsize combination}
         @h2xmle_bitName {TX_VOICE_AS_BW_SLOT_CFG}
         @h2xmle_rangeList {none=WHS_USB_BW_SLOT_CFG_NONE;
                            bitwidth16_slot2=WHS_USB_BW_SLOT_CFG_16_2;
                            bitwidth24_slot3=WHS_USB_BW_SLOT_CFG_24_3;
                            bitwidth24_slot4=WHS_USB_BW_SLOT_CFG_24_4;
                            bitwidth32_slot4=WHS_USB_BW_SLOT_CFG_32_4
                           }
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_SVC_INT_US_MASK}
         @h2xmle_description {TX voice service interval}
         @h2xmle_bitName {TX_VOICE_SVC_INT}
         @h2xmle_rangeList {none=WHS_USB_SVC_INT_US_NONE;
                            serv_int_125us=WHS_USB_SVC_INT_US_125;
                            serv_int_250us=WHS_USB_SVC_INT_US_250;
                            serv_int_500us=WHS_USB_SVC_INT_US_500;
                            serv_int_1ms=WHS_USB_SVC_INT_US_1000;
                            serv_int_2ms=WHS_USB_SVC_INT_US_2000;
                            serv_int_4ms=WHS_USB_SVC_INT_US_4000
                           }
         @h2xmle_bitfieldEnd
    */


    uint16_t tx_ec_as_freqs;
    /**< @h2xmle_description {TX ec sampling frequencies}
         @h2xmle_bitfield {WHS_USB_FREQ_8K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_16K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_16K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_32K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_32K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_44P1K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_44P1K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_48K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_48K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_88P2K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_88P2K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_96K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_96K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_176P4K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_176P4K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_192K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_192K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_352P8K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_352P8K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {0}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FREQ_384K_MASK}
         @h2xmle_bitName {TX_EC_FREQ_384K}
         @h2xmle_rangeList {YES=1; NO=0}
         @h2xmle_default {1}
         @h2xmle_bitfieldEnd
    */

    uint8_t tx_ec_as_bus_cfg[UAS_BUS_CFG_SIZE];
    /**< @h2xmle_bitfield {WHS_USB_BW_SLOT_CFG_MASK}
         @h2xmle_description {TX ec bitwidth/slotsize combination}
         @h2xmle_bitName {TX_EC_AS_BW_SLOT_CFG}
         @h2xmle_rangeList {none=WHS_USB_BW_SLOT_CFG_NONE;
                            bitwidth16_slot2=WHS_USB_BW_SLOT_CFG_16_2;
                            bitwidth24_slot3=WHS_USB_BW_SLOT_CFG_24_3;
                            bitwidth24_slot4=WHS_USB_BW_SLOT_CFG_24_4;
                            bitwidth32_slot4=WHS_USB_BW_SLOT_CFG_32_4
                           }
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_SVC_INT_US_MASK}
         @h2xmle_description {TX ec service interval}
         @h2xmle_bitName {TX_EC_SVC_INT}
         @h2xmle_rangeList {none=WHS_USB_SVC_INT_US_NONE;
                            serv_int_125us=WHS_USB_SVC_INT_US_125;
                            serv_int_250us=WHS_USB_SVC_INT_US_250;
                            serv_int_500us=WHS_USB_SVC_INT_US_500;
                            serv_int_1ms=WHS_USB_SVC_INT_US_1000;
                            serv_int_2ms=WHS_USB_SVC_INT_US_2000;
                            serv_int_4ms=WHS_USB_SVC_INT_US_4000
                           }
         @h2xmle_bitfieldEnd
    */

    uint16_t rx_feedback_interval;
    /**< @h2xmle_range {1..65535}
         @h2xmle_description {feedback interval of RX channels in microseconds} - (internal !!! not for customers)
         @h2xmle_default {16000}
    */

    uint16_t top_aud_rev;
    /**< @h2xmle_rangeList {UAC_REV_NONE = 0x0000,
                            UAC_REV_1    = 0x0100,
                            UAC_REV_2    = 0x0200,
                            UAC_BADD3    = 0x02FF,
                            UAC_REV_3    = 0x0300
                           }
         @h2xmle_description {Advertise preference for a certain USB audio class revision}
         @h2xmle_default {0}
    */

    int8_t rx_volume_min;
    /**< @h2xmle_range {-84..40}
         @h2xmle_description {RX minimum volume in dB}
         @h2xmle_default {-84}
    */

    int8_t rx_volume_max;
    /**< @h2xmle_range {-84..40}
         @h2xmle_description {RX maximum volume in dB}
         @h2xmle_default {40}
    */

    uint8_t rx_volume_resolution;
    /**< @h2xmle_range {1..16}
         @h2xmle_description {RX volume granularity in half dB, e.g.: 1=0.5 dB}
         @h2xmle_default {1}
    */

    int8_t rx_volume_default;
    /**< @h2xmle_range {-84..40}
         @h2xmle_description {RX default volume in dB}
         @h2xmle_default {0}
    */

    uint8_t usb_clock_mode; 
    /**< @h2xmle_default {0}
         @h2xmle_description {USB audio topology clock mode}
         @h2xmle_rangeList {MULTI_CLOCK=0; SINGLE_CLOCK=1} 
    */

    uint8_t usb_mic_type;
    /**< @h2xmle_rangeList {USB_MIC_MONO   = 0,
                            USB_MIC_STEREO = 1,
                            USB_MIC_QUAD   = 2
                            }
         @h2xmle_description {Type of microphone hardware to be used}
         @h2xmle_default {0}
    */


};

/** @h2xml_select {usb_svc_params::rx_main_as_bus_cfg}
    @h2xmle_defaultList {0x14, 0x23, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00}
*/

/** @h2xml_select {usb_svc_params::tx_voice_as_bus_cfg}
    @h2xmle_defaultList {0x14, 0x23, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00}
*/

/**
 * @struct usb_drv_params
 * @brief USB driver configuration parameters
 */

/**
    @h2xmlp_parameter      {"WHS_USB_DRV_PID", WHS_USB_DRV_PID}
    @h2xmlp_description {USB driver configuration}
    @h2xmlx_expandStructs {false}
*/

typedef struct usb_drv_params {
    uint32_t feature_flags;
    /**< @h2xmle_bitfield {WHS_USB_FEATURE_L1_MASK}
         @h2xmle_bitName {L1}
         @h2xmle_rangeList {ENABLE=1; DISABLE=0}
         @h2xmle_default {1}
         @h2xmle_description {0=disable USB L1, 1=enable USB L1}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FEATURE_L2_MASK}
         @h2xmle_bitName {L2}
         @h2xmle_rangeList {ENABLE=1; DISABLE=0}
         @h2xmle_default {1}
         @h2xmle_description {0=disable USB L2, 1=enable USB L2}
         @h2xmle_bitfieldEnd

         @h2xmle_bitfield {WHS_USB_FEATURE_HALT_ON_ERROR_MASK}
         @h2xmle_bitName {HALT_ON_ERROR}
         @h2xmle_rangeList {ENABLE=1; DISABLE=0}
         @h2xmle_default {0}
         @h2xmle_description {0=do not halt on error, 1=halt on error in USB driver}
         @h2xmle_bitfieldEnd
    */

    uint16_t lang_id;
    /**< @h2xmle_range {0x0..0xFFFF}
         @h2xmle_description {Language ID of Product and Manufacturer String.}
         @h2xmle_default {0x0409}
    */

    uint8_t manuf_str_len;
    /**< @h2xmle_range {0..64}
         @h2xmle_description {Length of Manufacturer String}
         @h2xmle_default {0}
    */

    uint8_t product_str_len;
    /**< @h2xmle_range {0..64}
         @h2xmle_description {Length of Product String}
         @h2xmle_default {0}
    */

    uint16_t manuf_str[64];
    /**< @h2xmle_description {Manufacturer String}
         @h2xmle_default {0x0000}
    */

    uint16_t product_str[64];
    /**< @h2xmle_description {Product String}
         @h2xmle_default {0x0000}
    */

} usb_drv_params_t;

/** @} */ /* End of Module */

#endif /* __USB_SVC_DATA_H__ */
