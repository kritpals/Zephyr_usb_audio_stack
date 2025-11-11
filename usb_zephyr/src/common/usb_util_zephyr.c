//============================================================================
/**
 * @file      usb_util_zephyr.c
 * @author    Ported to Zephyr OS
 * @date      16-Oct-2025
 *
 * @brief     USB utility APIs for Zephyr OS
 *
 * @details   Zephyr OS implementation of USB utility functions
 * 
 */
//============================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <zephyr/kernel.h>
#include <zephyr/pm/device.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

#include "usb_log.h"
#include "usb_util.h"

LOG_MODULE_REGISTER(usb_util, LOG_LEVEL_DBG);

/*----------------------------------------------------------------------------
 *  Function definitions
 * -------------------------------------------------------------------------*/

boolean usb_feature_halt_on_error = FALSE;

//============================================================================
/**
* @function  - usb_delay_us
*
* @brief - Busywait delay in microseconds.
*
* @param - Delay in microseconds
*
* @return - None
*
*/
//============================================================================
void usb_delay_us(uint32 usecs)
{
  k_busy_wait(usecs);
}

//============================================================================
/**
* @function  - usb_delay_ms
*
* @brief - Delay in mili-seconds.
*
* @param - Delay in mili-seconds.
*
* @return - None
*
*/
//============================================================================
void usb_delay_ms(uint32 msecs)
{
  k_msleep(msecs);
}

// ===========================================================================
/**
 * @function    usb_enable_clocks
 * 
 * @brief   This function will used to turn ON the USB clocks
 * 
 * @param   boolean* status_flag_ptr: pointer to dci_ctx->is_clk_on
 *          boolean enable : If set would enable all clocks
 * 
 * @return  none
 * 
 */
// ===========================================================================
void usb_enable_clocks(boolean* status_flag_ptr, boolean enable)
{
  LOG_DBG("Enable clocks: %d", enable);
  *status_flag_ptr = enable;
  
  // TODO: Implement Zephyr PM device control
  // const struct device *usb_dev = DEVICE_DT_GET(DT_NODELABEL(usb));
  // if (enable) {
  //   pm_device_action_run(usb_dev, PM_DEVICE_ACTION_RESUME);
  // } else {
  //   pm_device_action_run(usb_dev, PM_DEVICE_ACTION_SUSPEND);
  // }
}

// ===========================================================================
/**
 * @function    usb_enable_clocks_in_isr
 * 
 * @brief   This function will turn ON the USB clocks in IRQ thread
 * 
 * @return  none
 * 
 */
// ===========================================================================
void usb_enable_clocks_in_isr(void)
{
  LOG_DBG("Enable clocks in ISR");
  // TODO: Implement Zephyr PM runtime get
  // pm_device_runtime_get(usb_dev);
}

// ===========================================================================
/**
 * @function    usb_get_acdb_params
 * 
 * @brief   This function will read USB parameters from device tree
 * 
 * @details  This function reads USB driver parameters from device tree.
 *           On failure, all params are set to default values.
 *
 * @param   usb_drv_params_t - [IN] - Struct to copy USB driver params into.
 * 
 * @return  None
 * 
 */
// ===========================================================================
void usb_get_acdb_params(usb_drv_params_t* params)
{
  // Initialize with default values
  memset(params, 0, sizeof(usb_drv_params_t));
  
  // Enable L1 and L2 feature as default
  params->feature_flags = WHS_USB_FEATURE_L1_MASK | WHS_USB_FEATURE_L2_MASK;
  
  // TODO: Read from device tree
  // params->qc_pid = DT_PROP(DT_NODELABEL(usb), qc-pid);
  // params->vid_override = DT_PROP_OR(DT_NODELABEL(usb), vid-override, 0);
  // etc.
  
  LOG_INF("USB params loaded from defaults");
}

void usb_error_fatal(void)
{
  LOG_ERR("USB Fatal Error!");
  k_panic();
}

void usb_set_halt_on_err(boolean val)
{
  usb_feature_halt_on_error = val;
}

void usb_error_halt(uint32 log_enum)
{
  if(log_enum)
  {
    LOG_ERR("USB Error: %u", log_enum);
  }

  if(usb_feature_halt_on_error)
  {
    usb_fn_util()->usb_error_fatal();
  }
}

/*===========================================================================
FUNCTION usb_os_spinlock_init

DESCRIPTION
Initialize spinlock for USB driver

DEPENDENCIES
None.

PARAMETER
None

RETURN VALUE
None

SIDE EFFECTS
None.
===========================================================================*/
static struct k_spinlock usb_os_lock;
static boolean usb_os_lock_init = FALSE;

void usb_os_spinlock_init(void)
{
  if(FALSE == usb_os_lock_init)
  {
    // Zephyr spinlocks are statically initialized
    usb_os_lock_init = TRUE;
  }
}

/*===========================================================================
FUNCTION usb_os_spinlock_lock

DESCRIPTION
Acquire spinlock and disable interrupts

DEPENDENCIES
None.

PARAMETER
None

RETURN VALUE
None

SIDE EFFECTS
None.
===========================================================================*/
static k_spinlock_key_t usb_lock_key;

void usb_os_spinlock_lock(void)
{
  usb_lock_key = k_spin_lock(&usb_os_lock);
}

/*===========================================================================
FUNCTION usb_os_spinlock_unlock

DESCRIPTION
Release spinlock and restore interrupts

DEPENDENCIES
None.

PARAMETER
None

RETURN VALUE
None

SIDE EFFECTS
None.
===========================================================================*/
void usb_os_spinlock_unlock(void)
{
  k_spin_unlock(&usb_os_lock, usb_lock_key);
}

/*===========================================================================
FUNCTION usb_os_safe_enter_d

DESCRIPTION
  Placeholder for safe enter (not needed in Zephyr with spinlocks)

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void usb_os_safe_enter_d(void)
{
  // Not needed with spinlocks
}

/*===========================================================================
FUNCTION usb_os_safe_leave_d

DESCRIPTION
  Placeholder for safe leave (not needed in Zephyr with spinlocks)

DEPENDENCIES
  None.

RETURN VALUE
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void usb_os_safe_leave_d(void)
{
  // Not needed with spinlocks
}

void usb_mutex_init(struct k_mutex *lock)
{
  k_mutex_init(lock);
}

void usb_mutex_lock(struct k_mutex *lock)
{
  k_mutex_lock(lock, K_FOREVER);
}

void usb_mutex_unlock(struct k_mutex *lock)
{
  k_mutex_unlock(lock);
}

void usb_mutex_deinit(struct k_mutex *lock)
{
  // Zephyr mutexes don't need explicit destruction
  (void)lock;
}

//----------------------------------------------------------------------------
// Function table definition of utility layer
//----------------------------------------------------------------------------

usb_fn_tbl_util_t fn_tbl_util = 
{
  usb_delay_us,
  usb_delay_ms,
  usb_enable_clocks,
  usb_enable_clocks_in_isr,
  usb_get_acdb_params,
  usb_error_fatal,
  usb_set_halt_on_err,
  usb_error_halt,
  usb_os_spinlock_init,
  usb_os_spinlock_lock,
  usb_os_spinlock_unlock,
  usb_os_safe_enter_d,
  usb_os_safe_leave_d
};
