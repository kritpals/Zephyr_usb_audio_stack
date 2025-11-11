#ifndef USB_HID_API_H
#define USB_HID_API_H

#include "usb_common.h"

#define USB_HID_REPORT_ID (1)

typedef struct
{
  uint8 report_id;
  uint8 cmd1;
  uint8 cmd2;
} usb_hid_buff_t;

typedef enum
{
  HID_RELEASE      = 0x0000,
  HID_PLAY_PAUSE   = 0x0001,
  HID_NEXT_TRACK   = 0x0002,
  HID_PREV_TRACK   = 0x0004,
  HID_STOP         = 0x0008,
  HID_PLAY         = 0x0010,
  HID_PAUSE        = 0x0020,
  HID_FAST_FORWARD = 0x0040,
  HID_REWIND       = 0x0080,
  HID_VOL_INC      = 0x0100,
  HID_VOL_DEC      = 0x0200,
  HID_MUTE         = 0x0400,
  HID_MAX          = 0x0800
} usb_hid_bitmask_cmd_t;

uint32 usb_hid_open(client_ctx_t** client_ctx, usb_ifc_id ifc_id);

uint32 usb_hid_report(client_ctx_t* client_ctx, usb_hid_bitmask_cmd_t report);

#endif /*USB_HID_API_H*/
