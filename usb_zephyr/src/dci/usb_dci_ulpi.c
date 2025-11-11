#include "usb_dci_ulpi.h"
#include "usb_hwio_9410.h"
#include "usb_log.h"
#include "usb_dci.h"


void usb_dci_ulpi_write(uint32 address, uint32 data)
{
  uint32 reg_value = (  HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_NEWREGREQ_BMSK  |
                        HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGWR_BMSK      |
                        ((address << HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGADDR_SHFT) & HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGADDR_BMSK) |
                        ((data << HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGDATA_SHFT) & HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGDATA_BMSK)
                      );
  USB_LOG_DBG_1(log_usb_dci_ulpi_write__reg_value_D, reg_value);
  
  HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_OUTI(0,reg_value);
  while (1 != (HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_INMI(0,HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSDONE_BMSK)>>
                                                           HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSDONE_SHFT));

  return;
}

uint8 usb_dci_ulpi_read(uint32 address)
{
  uint32 reg_value = ( (HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_NEWREGREQ_BMSK |
                        ((address << HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGADDR_SHFT) & HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGADDR_BMSK)
                        )& (~HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGWR_BMSK)
                      );
  uint8 reg_return;
  //usb_log(DCI_HW_ULPI_READ_VAL_LOG, 0, reg_value);  
  HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_OUTI(0,reg_value);
  while (1 != (HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_INMI(0,HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSDONE_BMSK)
                            >> HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_VSTSDONE_SHFT));
  reg_return = HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_INMI(0, HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGDATA_BMSK)
                            >> HWIO_USBCTL_GUSB2PHYACC_REGS_p_GUSB2PHYACC_ULPI_REGDATA_SHFT;
  //usb_log(DCI_HW_ULPI_READ_RES_LOG, 0, reg_return);

  return reg_return;
}

void usb_dci_ulpi_debug_init(usb_ulpi_debug_ctx_t* ulpi_ctx)
{
  USB_ASSERT(ulpi_ctx);
  ulpi_ctx->func_ctl.value  = 0;
  ulpi_ctx->otg_ctl.value   = 0;
  ulpi_ctx->int_state.value = 0;
  ulpi_ctx->debug.value     = 0;
}

void usb_dci_ulpi_debug_update(usb_ulpi_debug_ctx_t* ulpi_ctx)
{
  USB_ASSERT(ulpi_ctx);
  ulpi_ctx->func_ctl.value  = usb_dci_ulpi_read(USB_ULPI_FUNCTION_CTRL_REG_ADDR);
  ulpi_ctx->otg_ctl.value   = usb_dci_ulpi_read(USB_ULPI_OTG_CTRL_REG_ADDR);
  ulpi_ctx->int_state.value = usb_dci_ulpi_read(USB_ULPI_ISR_STATUS_REG_ADDR);
  ulpi_ctx->debug.value     = usb_dci_ulpi_read(USB_ULPI_DEBUG_REG_ADDR);
}

void usb_dci_ulpi_test(usb_ulpi_debug_ctx_t* ulpi_ctx)
{
  uint32 ulpi_read=0;
  uint32 ulpi_new_val=0;

  USB_ASSERT(ulpi_ctx);

  ulpi_read = usb_dci_ulpi_read(USB_ULPI_SCRATCH_REG_ADDR);
  USB_LOG_DBG_1(log_usb_dci_ulpi_test__ulpi_reg_read_D, ulpi_read);
  ulpi_new_val = ulpi_read+0xAB;  //0xAB is just any value
  usb_dci_ulpi_write(USB_ULPI_SCRATCH_REG_ADDR,ulpi_new_val);

  do
  {
    ulpi_read = usb_dci_ulpi_read(USB_ULPI_SCRATCH_REG_ADDR);
    USB_LOG_DBG_1(log_usb_dci_ulpi_test__ulpi_reg_read_D, ulpi_read);
    usb_fn_util()->usb_delay_us(100);
  }  while(ulpi_read != ulpi_new_val);
  usb_dci_ulpi_debug_update(ulpi_ctx);
}

