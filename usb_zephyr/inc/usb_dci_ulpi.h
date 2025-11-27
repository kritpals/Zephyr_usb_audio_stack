#ifndef USB_DCI_ULPI_H
#define USB_DCI_ULPI_H

#include "comdef.h"     // common defines and types

typedef union
{
  struct
  {
    uint8 XcvrSelect :2;
    uint8 TermSelect :1;
    uint8 OpMode     :2;
    uint8 reset      :1;
    uint8 SuspendM   :1;
    uint8 reserved      :1;
  }bit_value;
  uint8 value;
} usb_ulpi_func_ctl;

typedef union
{
  struct
  {
    uint8 IdPullup      :1;
    uint8 DpPulldown    :1;
    uint8 DmPulldown    :1;
    uint8 DischrgVbus   :1;
    uint8 ChrgVbus      :1;
    uint8 DrvVbus       :1;
    uint8 DrvVbusExt    :1;
    uint8 UseExtVbusInd :1;
  }bit_value;
  uint8 value;
} usb_ulpi_otg_ctl;

typedef union
{
  struct
  {
    uint8 Hostisconnect :1;
    uint8 VbusValid     :1;
    uint8 SessValid     :1;
    uint8 SessEnd       :1;
    uint8 IdGnd         :1;
    uint8 reserved      :3;
  }bit_value;
  uint8 value;
} usb_ulpi_int_state;

typedef union
{
  struct
  {
    uint8 linestate0 :1;
    uint8 linestate1 :1;
    uint8 reserved   :6;
  }bit_value;
  uint8 value;
} usb_ulpi_debug;

#define USB_EXTERNAL_ULPI_PHY_RESET_REG_ADDR (0x19031)

#define USB_ULPI_FUNCTION_CTRL_REG_ADDR   (0x04)
#define USB_ULPI_INTERFACE_CTRL_REG_ADDR  (0x07)
#define USB_ULPI_OTG_CTRL_REG_ADDR        (0x0A)
#define USB_ULPI_ISR_STATUS_REG_ADDR      (0x13)
#define USB_ULPI_DEBUG_REG_ADDR           (0x15)
#define USB_ULPI_SCRATCH_REG_ADDR         (0x16)



typedef struct usb_ulpi_debug
{
  usb_ulpi_func_ctl func_ctl;
  usb_ulpi_otg_ctl otg_ctl;
  usb_ulpi_int_state int_state;
  usb_ulpi_debug debug;
}usb_ulpi_debug_ctx_t;

void usb_dci_ulpi_write(uint32 address, uint32 data);
uint8 usb_dci_ulpi_read(uint32 address);

void usb_dci_ulpi_debug_init(usb_ulpi_debug_ctx_t* ulpi_ctx);

void usb_dci_ulpi_debug_update(usb_ulpi_debug_ctx_t* ulpi_ctx);

void usb_dci_ulpi_test(usb_ulpi_debug_ctx_t* ulpi_ctx);

#endif
