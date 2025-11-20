
#include "usb_isr.h"
#include "usb_dci.h"
 #include "usb_common.h"
#include "usb_util.h"
//#include "led.h" 
#include "usb_log.h"


#include "usb_hwio_9410.h"
#include "usb_dci_9410.h"

#define USB_EVENT_AGGR_CNT        (8)
#define USB_PWR_DSR_QUEUE_SIZE    (8)
#define USB_CTRL_EE1_IRQ          (5)   // Device event
#define USB_CTRL_POWER_EVENT_IRQ  (10)  // Power event
#define USB_CTRL_HSPHY_IRQ        (11)  //
#define USB_PHY_DMSE_IRQ          (12)  // Not use
#define USB_PHY_DPSE_IRQ          (13)  // EDGE trigger, edge fall  //Enable after IN_L2, handle VOTE_PWR_USB
#define USB_SOF_IRQ               (14)  // Not use
#define USB_RECOVERED_SOF_IRQ     (15)  // Not use 

/*===========================================================================
FUNCTION usb_event_queue_init

DESCRIPTION
Create usb dsr event buffer.

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer
  uint32 size: number of event

RETURN VALUE
 none
 
SIDE EFFECTS
None.
===========================================================================*/
void usb_event_queue_init(usb_event_queue_t* q_ctx, uint32 size)
{
  USB_ASSERT(q_ctx && (size != 0));

  USB_ASSERT(q_ctx->dsr_save_event = 
    (usb_event_t*) usb_fn_mem_util()->usb_malloc((size + 1) * USB_EVT_BUFFER_UNIT_SIZE));

  q_ctx->dsr_event_read_idx  = size;
  q_ctx->dsr_event_write_idx = 0;
  q_ctx->size = size + 1;
  q_ctx->cnt = 0;
}

/*===========================================================================
FUNCTION usb_event_queue_uninit

DESCRIPTION
Destory the usb_dsr buffer

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer

RETURN VALUE
 none

SIDE EFFECTS
None.
===========================================================================*/
void usb_event_queue_uninit(usb_event_queue_t* q_ctx)
{
  USB_ASSERT(q_ctx);
  usb_fn_mem_util()->usb_free((void**)&q_ctx->dsr_save_event);
}

/*===========================================================================
FUNCTION usb_event_enqueue

DESCRIPTION
Enqueue usb_buffer

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer
  uint32 usb_event

RETURN VALUE
  TRUE for success.
  FLASE for FAIL.

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_event_enqueue(usb_event_queue_t* q_ctx, uint32 new_data)
{
  USB_ASSERT(q_ctx);

  if (q_ctx->dsr_event_write_idx == q_ctx->dsr_event_read_idx)
  {
    //USB_LOG_ERR_1(log_usb_event_enqueue__queue_full_D, (uint32)queue_ctx->cnt);
    return FALSE;
  }
  q_ctx->dsr_save_event[q_ctx->dsr_event_write_idx].generic= new_data;
  q_ctx->dsr_event_write_idx = (q_ctx->dsr_event_write_idx + 1) % q_ctx->size;
  q_ctx->cnt++;
  return TRUE;
}

/*===========================================================================
FUNCTION usb_event_dequeue

DESCRIPTION
Dequeue usb_buffer. It disable usb_isr

DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer
  uint32* usb_event

RETURN VALUE
  TRUE for success.
  FLASE for FAIL.

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_event_dequeue( usb_event_queue_t* q_ctx, uint32* old_data)
{
  uint32 local_rd_idx;
  USB_ASSERT(q_ctx && old_data);

  local_rd_idx = (q_ctx->dsr_event_read_idx + 1) % q_ctx->size;

  if (local_rd_idx == q_ctx->dsr_event_write_idx)
  {
    USB_LOG_ERR_1(log_usb_event_dequeue__queue_empty_D, (uint32)q_ctx);
    return FALSE;
  }

  *old_data = q_ctx->dsr_save_event[local_rd_idx].generic;
  q_ctx->dsr_event_read_idx = local_rd_idx;
  q_ctx->cnt--;

  return TRUE;
}


/*===========================================================================
FUNCTION usb_event_queue_cnt

DESCRIPTION
  return the number of event in queue
  Disable when reading cnt
  
DEPENDENCIES
None.

INPUT
  usb_event_queue_t* queue pointer

RETURN VALUE
  uint32 Number of events in the queue

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_event_queue_cnt(usb_event_queue_t* q_ctx)
{
  USB_ASSERT(q_ctx);
  return q_ctx->cnt;
}

/*===========================================================================
FUNCTION usb_isr_ee_enable

DESCRIPTION
Enable/disable the all ee irq, usb device event

INPUT
  boolean enable; to enable to disable usb isr
DEPENDENCIES
None.

RETURN VALUE
None.

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_ee_enable(boolean enable)
{
  if (enable)
  {
    //TODO: CPEInterruptController_EnableInterrupt(USB_CTRL_EE1_IRQ);
  }
  else
  {
    //TODO: CPEInterruptController_DisableInterrupt(USB_CTRL_EE1_IRQ);
  }
}

/*===========================================================================
FUNCTION usb_isr_usbphy_enable

DESCRIPTION
Enable/disable the all usb phy irq (only usb isr)

INPUT
  boolean enable; to enable to disable usb isr
DEPENDENCIES
None.

RETURN VALUE
None.

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_usbphy_enable(boolean enable)
{
  if (enable)
  {
    //TODO: CPEInterruptController_EnableInterrupt(USB_CTRL_HSPHY_IRQ);
    //CPEInterruptController_EnableInterrupt(USB_PHY_DPSE_IRQ);
  }
  else
  {
    //CPEInterruptController_DisableInterrupt(USB_CTRL_HSPHY_IRQ);
    //CPEInterruptController_DisableInterrupt(USB_PHY_DPSE_IRQ);
  }
}

/*===========================================================================
FUNCTION usb_isr_pwr_enable

DESCRIPTION
Enable/disable the all usb pwr irq

INPUT
  boolean enable; to enable to disable usb isr
DEPENDENCIES
None.

RETURN VALUE
None.

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_pwr_enable(boolean enable)
{
  if (enable)
  {
    //TODO: CPEInterruptController_EnableInterrupt(USB_CTRL_POWER_EVENT_IRQ);
  }
  else
  {
    //CPEInterruptController_DisableInterrupt(USB_CTRL_POWER_EVENT_IRQ);
  }
}

/*===========================================================================
FUNCTION usb_isr_enable

DESCRIPTION
Enable/disable the all usb_isr (only usb isr)

INPUT
  boolean enable; to enable to disable usb isr
DEPENDENCIES
None.

RETURN VALUE
None.

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_enable(usb_isr_ctx_t* isr_ctx, boolean enable)
{
  usb_fn_isr()->usb_isr_ee_enable(enable);
  usb_fn_isr()->usb_isr_pwr_enable(enable);
}

/*===========================================================================
FUNCTION usb_isr_ee1_handle

DESCRIPTION
handle usb bus interrupt. Put the bus event to event queue and clear isr event

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

DEPENDENCIES
None.

RETURN VALUE
None

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_ee1_handle(void* ctx)
{
  usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)ctx;
  usb_mips_start(usb_mips__usb_intr_isr);
  //TODO: CPEInterruptController_ClearPending(USB_CTRL_EE1_IRQ);
  if (isr_ctx && isr_ctx->usb_events)
  {
    if(usb_fn_isr()->usb_isr_enqueue_ee_event(isr_ctx))
    {
      //TODO : k_event_set(isr_ctx->usb_events, USB_EVENT_QUEUE_FLAG);
    }
  }
  usb_mips_stop(usb_mips__usb_intr_isr);
}

/*===========================================================================
FUNCTION usb_isr_pwr_handle

DESCRIPTION
handle power event In/out L2, L1.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

DEPENDENCIES
None.

RETURN VALUE
None

SIDE EFFECTS
None.
===========================================================================*/
void usb_isr_pwr_handle(void* ctx)
{
  uint32 sts_reg=0;
  usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)ctx;
  uint32 pwr_isr_event = HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN;
  
  //TODO: CPEInterruptController_ClearPending(USB_CTRL_POWER_EVENT_IRQ);
  if (pwr_isr_event)
  {
    HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OUT(pwr_isr_event);
    //USB_LOG_1(log_usb_isr_pwr_handle__pwr_event_D, pwr_isr_event);
    if ((pwr_isr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK) &&
        (pwr_isr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK))
    {
      sts_reg = HWIO_USBCTL_USB30_STS_REG_IN;
      //USB_LOG_DBG_1(log_usb_isr_pwr_handle__in_out_l2_pwr_event_D, pwr_isr_event);

      /* State bits have negative logic */
      if ((~sts_reg) & (HWIO_USBCTL_USB30_STS_REG_USB30_CTRL_SUSPEND_N_BMSK))
      {
        // P3_L2
        if (usb_fn_isr()->usb_event_enqueue(&isr_ctx->pwr_dsr_queue, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK))
        {
          //USB_LOG_DBG_1(log_usb_isr_pwr_handle__in_l2_pwr_event_D, pwr_isr_event);
        }
      }
      else
      {
        if (usb_fn_isr()->usb_event_enqueue(&isr_ctx->pwr_dsr_queue, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK))
        {
          //USB_LOG_DBG_1(log_usb_isr_pwr_handle__out_l2_pwr_event_D, pwr_isr_event);
        }
      }   
    }
    else
    {     
      if (pwr_isr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_IN_L2_IRQ_STAT_BMSK)
      {
        //USB_LOG_DBG_1(log_usb_isr_pwr_handle__in_l2_pwr_event_D, pwr_isr_event);
      }
      
      if (pwr_isr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK)
      {
        if (usb_fn_isr()->usb_event_enqueue(&isr_ctx->pwr_dsr_queue, HWIO_USBCTL_PWR_EVNT_IRQ_STAT_LPM_OUT_L2_IRQ_STAT_BMSK))
        {
          //USB_LOG_DBG_1(log_usb_isr_pwr_handle__out_l2_pwr_event_D, pwr_isr_event);
        }
      }
    }

    if (pwr_isr_event & HWIO_USBCTL_PWR_EVNT_IRQ_STAT_USB30_GSI_L1_EXIT_IRQ_STAT_BMSK)
    {
      //USB_LOG_DBG_1(log_usb_isr_pwr_handle__gsi_event_D, pwr_isr_event);
      HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK,
                    0x0 << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
      HWIO_USBCTL_DCTL_OUTM(HWIO_USBCTL_DCTL_ULSTCHNGREQ_BMSK,
                    0x8 << HWIO_USBCTL_DCTL_ULSTCHNGREQ_SHFT);
    }
    
    if (isr_ctx && isr_ctx->pwr_handle)
    {
      isr_ctx->pwr_handle(pwr_isr_event);
    }
  }
}

void usb_isr_hsphy_handle(void* ctx)
{
  usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)ctx;
  usb_dci_ctx_t* dci_ctx;
  USB_ASSERT(isr_ctx && isr_ctx->dci_ctx);
  dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  //CPEInterruptController_ClearPending(USB_CTRL_HSPHY_IRQ);
  //led_chg_mode(LED_BLUE, LED_MODE_BLINK);
  //led_start(LED_BLUE);

  //USB_LOG_DBG(log_usb_isr_hsphy_handle); 
  usb_fn_isr()->usb_isr_usbphy_enable(FALSE);
  usb_fn_util()->usb_enable_clocks_in_isr();
}

void usb_isr_dpse_handle(void* ctx)
{
  usb_isr_ctx_t* isr_ctx = (usb_isr_ctx_t*)ctx;
  usb_dci_ctx_t* dci_ctx;
  USB_ASSERT(isr_ctx && isr_ctx->dci_ctx);
  dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;
  
  usb_fn_util()->usb_enable_clocks_in_isr();
  //led_chg_mode(LED_WHITE, LED_MODE_BLINK);
  //led_start(LED_WHITE);

  //USB_LOG_DBG(log_usb_isr_dpse_handle);
  // usb_isr_usbphy_enable(FALSE);
}

/*===========================================================================
FUNCTION usb_isr_lpm_init

DESCRIPTION
Mask the proper interrupt for power events

INPUT
  boolean is_l1_enable: is L1(sleep) feature enable
  boolean is_l2_enable: is L2(suspend) feature enable

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_isr_lpm_init(boolean is_l1_enable)
{
  uint32 pwr_isr_event = HWIO_USBCTL_PWR_EVNT_IRQ_STAT_IN;
 
  //CPEInterruptController_DisableInterrupt(USB_CTRL_POWER_EVENT_IRQ);
  //CPEInterruptController_ClearPending(USB_CTRL_POWER_EVENT_IRQ);

  HWIO_USBCTL_PWR_EVNT_IRQ_STAT_OUT(pwr_isr_event);
  HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OUT(0);

  HWIO_USBCTL_PWR_EVNT_IRQ_MASK_OUTM(HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_BMSK,
                                 0x1 << HWIO_USBCTL_PWR_EVNT_IRQ_MASK_LPM_OUT_L2_IRQ_MASK_SHFT);

  //CPEInterruptController_EnableInterrupt(USB_CTRL_POWER_EVENT_IRQ);
  return 0;
}


/*===========================================================================
FUNCTION usb_isr_ee_init

DESCRIPTION
Enable usb bus interrupt. Create event queue to handle bus event in DSR

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_isr_ee_init(usb_isr_ctx_t* isr_ctx)
{
  //CPEInterruptController_DisableInterrupt(USB_CTRL_EE1_IRQ);
  //CPEInterruptController_ClearPending(USB_CTRL_EE1_IRQ);

  usb_fn_isr()->usb_event_queue_init(&isr_ctx->ee_dsr_queue, EVENT_BUFFER_SIZE/sizeof(usb_event_t));

#ifdef USB_KW_CONST_RESULT
  //condition always yield the same result and causes an unreachable code
  if(CPEInterruptController_RegisterInterrupt(USB_CTRL_EE1_IRQ, usb_fn_isr()->usb_isr_ee1_handle, isr_ctx, 
         CPEINT_SETTRIGGER(CPEINT_TRIGGER_LEVEL_HIGH) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM)))
  {
    USB_LOG_ERR_1(log_usb_ee_pwr_init__failed_to_reg_interrupt_D, USB_CTRL_EE1_IRQ);
    USB_ASSERT(0);
    return FALSE;
  }
#else
  //TODO: CPEInterruptController_RegisterInterrupt(USB_CTRL_EE1_IRQ, usb_fn_isr()->usb_isr_ee1_handle, isr_ctx, 
         //CPEINT_SETTRIGGER(CPEINT_TRIGGER_LEVEL_HIGH) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM));
#endif
  return TRUE;
}

/*===========================================================================
FUNCTION usb_isr_pwr_init

DESCRIPTION
Enable usb vbus interrupt.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_isr_pwr_init(usb_isr_ctx_t* isr_ctx)
{
#ifdef USB_KW_CONST_RESULT
  CPEInterruptController_DisableInterrupt(USB_CTRL_POWER_EVENT_IRQ);
  CPEInterruptController_ClearPending(USB_CTRL_POWER_EVENT_IRQ);

  usb_fn_isr()->usb_event_queue_init(&isr_ctx->pwr_dsr_queue, USB_PWR_DSR_QUEUE_SIZE);


    //condition always yield the same result and causes an unreachable code

  if(CPEInterruptController_RegisterInterrupt(USB_CTRL_POWER_EVENT_IRQ, usb_fn_isr()->usb_isr_pwr_handle, isr_ctx, 
         CPEINT_SETTRIGGER(CPEINT_TRIGGER_RISING_EDGE) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM)))
  {
    USB_LOG_ERR_1(log_usb_isr_pwr_init__failed_to_reg_interrupt_D, USB_CTRL_POWER_EVENT_IRQ);
    USB_ASSERT(0);
    return FALSE;
  }

  CPEInterruptController_DisableInterrupt(USB_CTRL_HSPHY_IRQ);
  CPEInterruptController_ClearPending(USB_CTRL_HSPHY_IRQ);
  if(CPEInterruptController_RegisterInterrupt(USB_CTRL_HSPHY_IRQ, usb_fn_isr()->usb_isr_hsphy_handle, isr_ctx, 
         CPEINT_SETTRIGGER(CPEINT_TRIGGER_DUAL_EDGE) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM)))
  {
    USB_LOG_ERR_1(log_usb_isr_pwr_init__failed_to_reg_interrupt_D, USB_CTRL_HSPHY_IRQ);
    USB_ASSERT(0);
    return FALSE;
  }


  if(CPEInterruptController_RegisterInterrupt(USB_PHY_DPSE_IRQ, usb_fn_isr()->usb_isr_dpse_handle, isr_ctx, 
       CPEINT_SETTRIGGER(CPEINT_TRIGGER_RISING_EDGE) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM)))
  {
    USB_LOG_ERR_1(log_usb_isr_pwr_init__failed_to_reg_interrupt_D, USB_PHY_DPSE_IRQ);
    USB_ASSERT(0);
    return FALSE;
  }
#else
  /* TODO : CPEInterruptController_RegisterInterrupt(USB_CTRL_POWER_EVENT_IRQ, usb_fn_isr()->usb_isr_pwr_handle, isr_ctx, 
         CPEINT_SETTRIGGER(CPEINT_TRIGGER_RISING_EDGE) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM));

  CPEInterruptController_RegisterInterrupt(USB_CTRL_HSPHY_IRQ, usb_fn_isr()->usb_isr_hsphy_handle, isr_ctx, 
         CPEINT_SETTRIGGER(CPEINT_TRIGGER_DUAL_EDGE) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM));

  CPEInterruptController_RegisterInterrupt(USB_PHY_DPSE_IRQ, usb_fn_isr()->usb_isr_dpse_handle, isr_ctx, 
    CPEINT_SETTRIGGER(CPEINT_TRIGGER_RISING_EDGE) | CPEINT_SETPRIORITY(CPEINT_PRIORITY_MEDIUM));
    
  CPEInterruptController_DisableInterrupt(USB_PHY_DPSE_IRQ);
  */
#endif
  return TRUE;
}

/*===========================================================================
FUNCTION usb_isr_ee_uninit

DESCRIPTION
Deregister all the usb ee isr anre remove all the event_queue

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail


SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_isr_ee_uninit(usb_isr_ctx_t* isr_ctx)
{
  uint32 error_code = USB_SUCCESS;
  usb_dci_ctx_t* dci_ctx = (usb_dci_ctx_t*)(isr_ctx->dci_ctx);

  USB_ASSERT(dci_ctx);

  //error_code = CPEInterruptController_DeregisterInterrupt(USB_CTRL_EE1_IRQ);
  
#ifdef USB_KW_CONST_RESULT
      //condition always yield the same result and causes an unreachable code
  if(error_code)
  {
    USB_LOG_ERR_2(log_usb_ee_pwr_uninit__failed_to_dereg_interrupt_D_errcode_D, 
      USB_CTRL_EE1_IRQ, error_code);
    return error_code;
  }
#endif

  if (NULL != (isr_ctx->ee_dsr_queue).dsr_save_event)
  {
    usb_fn_isr()->usb_event_queue_uninit(&(isr_ctx->ee_dsr_queue));
  }
  return error_code;
}

/*===========================================================================
FUNCTION usb_isr_pwr_uninit

DESCRIPTION
Deregister all the usb power isr

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail


SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_isr_pwr_uninit(usb_isr_ctx_t* isr_ctx)
{
  uint32 error_code = USB_SUCCESS;
  usb_dci_ctx_t* dci_ctx = (usb_dci_ctx_t*)(isr_ctx->dci_ctx);

  USB_ASSERT(dci_ctx);
 
#ifdef USB_KW_CONST_RESULT
      //condition always yield the same result and causes an unreachable code
  error_code = CPEInterruptController_DeregisterInterrupt(USB_CTRL_POWER_EVENT_IRQ);  
  if(error_code)
  {
    USB_LOG_ERR_2(log_usb_isr_pwr_uninit__failed_to_dereg_interrupt_D_errcode_D, 
      USB_CTRL_POWER_EVENT_IRQ, error_code);
    return error_code;
  }
  error_code = CPEInterruptController_DeregisterInterrupt(USB_CTRL_HSPHY_IRQ);  
  if(error_code)
  {
    USB_LOG_ERR_2(log_usb_isr_pwr_uninit__failed_to_dereg_interrupt_D_errcode_D, 
      USB_CTRL_HSPHY_IRQ, error_code);
    return error_code;
  }
  error_code = CPEInterruptController_DeregisterInterrupt(USB_PHY_DPSE_IRQ);  
  if(error_code)
  {
    USB_LOG_ERR_2(log_usb_isr_pwr_uninit__failed_to_dereg_interrupt_D_errcode_D, 
      USB_PHY_DPSE_IRQ, error_code);
    return error_code;
  }
#else
 // CPEInterruptController_DeregisterInterrupt(USB_CTRL_POWER_EVENT_IRQ);  
 // CPEInterruptController_DeregisterInterrupt(USB_CTRL_HSPHY_IRQ);  
 // CPEInterruptController_DeregisterInterrupt(USB_PHY_DPSE_IRQ);  
#endif

  if (NULL != (isr_ctx->pwr_dsr_queue).dsr_save_event)
  {
    usb_fn_isr()->usb_event_queue_uninit(&isr_ctx->pwr_dsr_queue);
  }
  return error_code;
}


/*===========================================================================
FUNCTION usb_isr_init

DESCRIPTION
Initializes a USB core's interrupt. Inital the event buffer for usb_dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
  uint32 return 0 Success
         return 1 Fail

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_isr_init(usb_isr_ctx_t* isr_ctx)
{
  USB_ASSERT(isr_ctx);

#ifdef USB_KW_CONST_RESULT
    //condition always yield the same result and causes an unreachable code 
  if (FALSE == usb_fn_isr()->usb_isr_ee_init(isr_ctx))
  {
    return USB_ERR_UNKNOWN;
  }
  if (FALSE == usb_fn_isr()->usb_isr_pwr_init(isr_ctx))
  {
    return USB_ERR_UNKNOWN;
  }
#else
  usb_fn_isr()->usb_isr_ee_init(isr_ctx);
  usb_fn_isr()->usb_isr_pwr_init(isr_ctx);
#endif
  return USB_SUCCESS;//eRes;//HSU_JSUCCESS;
}  /* hsu_os_bus_interrupt_init */

/*===========================================================================
FUNCTION usb_isr_uninit

DESCRIPTION
Deregister all usb ISR (EE1+ pwr_isr)

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

DEPENDENCIES
None.

RETURN VALUE
  0 for success
  1 for Fail

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_isr_uninit(usb_isr_ctx_t* isr_ctx)
{
  uint32 error_value=USB_SUCCESS ;
  USB_ASSERT(isr_ctx);
#ifdef USB_KW_CONST_RESULT
    //condition always yield the same result and causes an unreachable code   
  error_value = usb_fn_isr()->usb_isr_ee_uninit(isr_ctx);
  if (error_value)
  {
    return error_value;
  }  
  
  error_value = usb_fn_isr()->usb_isr_pwr_uninit(isr_ctx);
  if (error_value)
  {
    return error_value;
  }  
#else
  usb_fn_isr()->usb_isr_ee_uninit(isr_ctx);
  usb_fn_isr()->usb_isr_pwr_uninit(isr_ctx);
#endif
  return error_value;
}

/*===========================================================================
FUNCTION usb_isr_enqueue_ee_event

DESCRIPTION
This is call from usb_isr_ee1_handle. To enqueue usb event to dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
 TRUE for success.
 FLASE for FAIL.

SIDE EFFECTS
None.
===========================================================================*/
boolean usb_isr_enqueue_ee_event(usb_isr_ctx_t* isr_ctx)
{
  uint32 evt_byte_count;
  uint32 cur_buf_pos;
  usb_dci_ctx_t* dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  USB_ASSERT(dci_ctx);

  /* Get the event count  ( number of valid bytes ) from the event buffer - SNPS 6.2.7.3 */
  evt_byte_count = HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_INMI(0,
     HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK);

  if (!evt_byte_count)
  {
    //USB_ULOG(DBG_E_QLOG, "interrupt WITHOUT event!");
    //USB_LOG_ERR(log_usb_isr_enqueue_ee_event__no_event);
    return FALSE;
  }

  while (evt_byte_count > 0) 
  {
    usb_event_t event;
    /* position of the event to be handled in the current event buffer */
    cur_buf_pos = dci_ctx->usb_evt_buf_info.cur_pos;
  
        /* Move the event buffer to the new location */
    event.generic = *(volatile uint32 *)((uint8 *)(dci_ctx->usb_evt_buf_info.buf) + cur_buf_pos );

    if (FALSE == usb_fn_isr()->usb_event_enqueue(&isr_ctx->ee_dsr_queue, event.generic))
    {
      //USB_ULOG_1(DBG_E_QLOG, "enqueue_fail, queue_ptr 0x%X", (uint32)&isr_ctx->ee_dsr_queue);    
      return FALSE;
    }
    *(volatile uint32 *)((uint8 *)dci_ctx->usb_evt_buf_info.buf + cur_buf_pos) = event.generic | 0xFF000000;
    //USB_LOG_DBG_2(log_usb_isr_enqueue_ee_event__event_cnt_D__event_D, usb_event_queue_cnt(&isr_ctx->ee_dsr_queue), event.generic);
    //USB_ULOG_3(ENG_QLOG, "Save Events - 0x%x, write_idx %u, cnt %u", event.generic, isr_ctx->ee_dsr_queue.dsr_event_write_idx, isr_ctx->ee_dsr_queue.cnt);

      /* Move to the next Event in the current buffer */
      /* Event buffer is 1K in size and each Event entry is 4 bytes long. We wrap at 1K. */
      /* Wrap the circular buffer at EVENT_BUFFER_SIZE to ensure there is no overflow */
    dci_ctx->usb_evt_buf_info.cur_pos = (cur_buf_pos + USB_EVT_BUFFER_UNIT_SIZE ) % EVENT_BUFFER_SIZE ;
    evt_byte_count -= USB_EVT_BUFFER_UNIT_SIZE;

    /* SW indicates to HW how many events it processed by writing the byte count (we process 4 at a time ) */
    HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_OUTMI(0,
            HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_BMSK,
            USB_EVT_BUFFER_UNIT_SIZE << HWIO_USBCTL_GEVNTADRLO_REGS_p_GEVNTCOUNT_EVNTCOUNT_SHFT );

  }
  return TRUE;
}


/*===========================================================================
FUNCTION usb_dsr_handle_ee_event

DESCRIPTION
this function is called in usb_thread to get the usb event from dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
  uint32 return 0 for successful
         return 1 for Fail
  

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_dsr_handle_ee_event(usb_isr_ctx_t* isr_ctx)
{
  /* EP specific Event */
  usb_event_t event_arr[USB_EVENT_AGGR_CNT];
  uint8 event_arr_size;
  uint8 i;
  uint32 event_cnt;
  usb_dci_ctx_t* dci_ctx;

  USB_ASSERT(isr_ctx && isr_ctx->dci_ctx);
  dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  event_cnt = usb_fn_isr()->usb_event_queue_cnt(&isr_ctx->ee_dsr_queue);
  while (event_cnt != 0)
  {
    usb_fn_isr()->usb_isr_ee_enable(FALSE);
    event_arr_size = MIN(event_cnt, USB_EVENT_AGGR_CNT);
    for(i=0; i < event_arr_size; i++)
    {
      if(FALSE == usb_fn_isr()->usb_event_dequeue(&isr_ctx->ee_dsr_queue, (uint32*)&event_arr[i]))
    {
        event_arr_size = i+1;
        break;
      }
    }

    usb_fn_isr()->usb_isr_ee_enable(TRUE);

    usb_mips_start(usb_mips__usb_handle_events);

    for(i=0; i < event_arr_size; i++)
    {
      if(event_arr[i].depevt.event_type == USB_EVT_TYPE_EP)
      {
        usb_fn_dci()->usb_dci_handle_ep_event(dci_ctx, &event_arr[i].depevt);
      }
      else if(event_arr[i].devt.event_type == USB_EVT_TYPE_NON_EP && !(event_arr[i].devt.dev_spec_event) )
      {
      /* Dev specific Event  */
      /* Event type should be "Non Ep'' and bits-7:1  should be Zero ( SNPS pg. 478, Table-649 ) */
        usb_fn_dci()->usb_dci_handle_dev_event(dci_ctx, &event_arr[i].devt);
      }
      else
      {
        USB_LOG_ERR_1(log_usb_dsr_handle_ee_event__unknown_event_D, event_arr[i].devt.dev_spec_event);
      }
      event_cnt--;
    }
    usb_mips_stop(usb_mips__usb_handle_events);
  }

  return 0;
}


/*===========================================================================
FUNCTION usb_dsr_handle_pwr_event

DESCRIPTION
this function is called in usb_thread to get the usb event from dsr

DEPENDENCIES
None.

INPUT
  usb_isr_ctx_t* isr_ctx pointer to isr_ctx

RETURN VALUE
  uint32 return 0 for successful
         return 1 for Fail
  

SIDE EFFECTS
None.
===========================================================================*/
uint32 usb_dsr_handle_pwr_event(usb_isr_ctx_t* isr_ctx)
{
  uint32 event_cnt;
  usb_dci_ctx_t* dci_ctx;
  uint32 pwr_event;
  USB_ASSERT(isr_ctx && isr_ctx->dci_ctx);
  dci_ctx = (usb_dci_ctx_t*)isr_ctx->dci_ctx;

  event_cnt = usb_fn_isr()->usb_event_queue_cnt(&isr_ctx->pwr_dsr_queue);
  while (event_cnt != 0)
  {
    usb_fn_isr()->usb_isr_pwr_enable(FALSE);
    if(FALSE == usb_fn_isr()->usb_event_dequeue(&isr_ctx->pwr_dsr_queue, (uint32*)&pwr_event))
    {
      usb_fn_isr()->usb_isr_pwr_enable(TRUE);
      return 1;
    }
    usb_fn_isr()->usb_isr_pwr_enable(TRUE);
    //USB_LOG_1(log_usb_dsr_handle_pwr_event__pwr_event_D, pwr_event);
    event_cnt--;
    usb_fn_dci()->usb_dci_handle_event(dci_ctx, pwr_event);
  }
  return 0;
}

//----------------------------------------------------------------------------
// Function table definition
//----------------------------------------------------------------------------

usb_fn_tbl_isr_t fn_tbl_isr = 
{
  usb_event_queue_init,
  usb_event_queue_uninit,
  usb_event_enqueue,
  usb_event_dequeue,
  usb_event_queue_cnt,
  usb_isr_ee_enable,
  usb_isr_usbphy_enable,
  usb_isr_pwr_enable,
  usb_isr_enable,
  usb_isr_ee1_handle,
  usb_isr_pwr_handle,
  usb_isr_hsphy_handle,
  usb_isr_dpse_handle,
  usb_isr_lpm_init,
  usb_isr_ee_init,
  usb_isr_pwr_init,
  usb_isr_ee_uninit,
  usb_isr_pwr_uninit,
  usb_isr_init,
  usb_isr_uninit,
  usb_isr_enqueue_ee_event,
  usb_dsr_handle_ee_event,
  usb_dsr_handle_pwr_event,
};
