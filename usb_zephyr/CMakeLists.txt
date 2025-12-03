# ------------------------------------------------------------------------------
#  Copyright (c) Qualcomm Technologies, Inc.
#  All rights reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
# ------------------------------------------------------------------------------

zephyr_library()

# Include directories

zephyr_library_sources(
    src/al/usb_al_zephyr.c
    #src/al/usb_log_api.c
    src/al/usb_cdc_acm_class.c
    src/func/usb_cdc_acm_fd.c
    src/common/usb_api_fn_tbl.c
    src/common/usb_fn_tbl.c
    src/common/usb_mem_util_zephyr.c
    src/common/usb_log.c
    src/common/usb_util_zephyr.c
    src/dcd/usb_class_dcd.c
    src/dcd/usb_dcd.c
    src/dci/usb_dci.c
    src/dci/usb_dci_9410.c
    src/dci/usb_dci_ulpi.c
    src/dci/usb_isr.c
    src/func/usb_bulk_fd.c
    src/func/usb_dfu_fd.c
    src/func/usb_fd.c
    src/func/usb_hid_fd.c
)

zephyr_include_directories(inc)

#require for logging.
zephyr_include_directories(../../include/battman)