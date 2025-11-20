# Zephyr OS Dependent Functions and APIs Analysis

## Overview
This document lists all OS-dependent functions and APIs in the USB driver code (battman/usb/usb_zephyr) that require modification for Zephyr OS compatibility.

---

## 1. THREADING AND SYNCHRONIZATION APIs

### 1.1 Thread Management (usb_al_hlos.c)
**Current Implementation:** QuRT (Qualcomm Real-Time OS)

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_create_thread()` | `qurt_thread_create()` | Create USB thread | `k_thread_create()` |
| `usb_thread_main()` | QuRT thread entry | Thread main function | Zephyr thread entry |
| Thread attributes | `qurt_thread_attr_t` | Thread configuration | `k_thread_stack_t` |
| Thread stack | `malloc()` for stack | Dynamic stack allocation | `K_THREAD_STACK_DEFINE()` |
| Thread priority | `qurt_thread_attr_set_priority()` | Set thread priority | `k_thread_priority_set()` |

**Files affected:**
- `src/al/usb_al_hlos.c` - Lines with `qurt_thread_*` APIs

---

### 1.2 Signal/Event Management (usb_al_hlos.c)
**Current Implementation:** QuRT Signals

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| Signal initialization | `qurt_signal2_init()` | Initialize signal object | `k_poll_signal_init()` or `k_event_init()` |
| Signal wait | `qurt_signal2_wait()` | Wait for signals | `k_poll()` or `k_event_wait()` |
| Signal set | `qurt_signal2_set()` | Set signal bits | `k_poll_signal_raise()` or `k_event_post()` |
| Signal clear | `qurt_signal2_clear()` | Clear signal bits | `k_event_clear()` |

**Signal Types Used:**
- `USB0_TASK_EVENT_QUEUE_SIG` (0x00010000)
- `USB0_TASK_ENUM_DONE_SIG` (0x00020000)
- `USB0_TASK_PWR_EVENT_QUEUE_SIG` (0x00040000)
- `USB0_TASK_VBUS_EVENT_SIG` (0x00080000)
- `USB0_TASK_LOG_TIMER_EXP_SIG` (0x00100000)

**Files affected:**
- `src/al/usb_al_hlos.c` - All signal operations
- `src/al/usb_al_hlos.h` - Signal type definitions

---

### 1.3 Mutex/Lock Management (usb_util.c)
**Current Implementation:** QuRT Mutex and Custom Spinlock

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_mutex_init()` | `qurt_mutex_init()` | Initialize mutex | `k_mutex_init()` |
| `usb_mutex_lock()` | `qurt_mutex_lock()` | Lock mutex | `k_mutex_lock()` |
| `usb_mutex_unlock()` | `qurt_mutex_unlock()` | Unlock mutex | `k_mutex_unlock()` |
| `usb_mutex_deinit()` | `qurt_mutex_destroy()` | Destroy mutex | N/A (static in Zephyr) |
| `usb_os_spinlock_init()` | `usblock_init()` | Initialize spinlock | `k_spin_lock_init()` |
| `usb_os_spinlock_lock()` | `usblock_lock()` | Acquire spinlock | `k_spin_lock()` |
| `usb_os_spinlock_unlock()` | `usblock_unlock()` | Release spinlock | `k_spin_unlock()` |

**Files affected:**
- `src/common/usb_util.c` - All mutex/lock functions
- `src/common/usb_util.h` - Lock type definitions

---

## 2. MEMORY MANAGEMENT APIs

### 2.1 Dynamic Memory Allocation (usb_mem_util.c)
**Current Implementation:** Standard C malloc/free with custom tracking

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_malloc()` | `malloc()` | Allocate cached memory | `k_malloc()` or `k_heap_alloc()` |
| `usb_malloc_uncached()` | `malloc()` + cache ops | Allocate uncached memory | `k_malloc()` with memory attributes |
| `usb_free()` | `free()` | Free memory | `k_free()` |
| `usb_mem_init()` | Custom tracking init | Initialize memory subsystem | Zephyr heap initialization |
| `usb_mem_deinit()` | Custom cleanup | Deinitialize memory | N/A |

**Files affected:**
- `src/common/usb_mem_util.c` - All memory allocation functions

---

### 2.2 Cache Management (usb_mem_util.c)
**Current Implementation:** Xtensa-specific cache operations

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_mem_barrier()` | `__asm__ __volatile__("memw")` | Memory barrier | `barrier()` or `z_barrier_dmem_fence_full()` |
| `usb_mem_attr_uncached()` | Direct address manipulation | Convert to uncached | `sys_cache_data_invd_range()` |
| `usb_mem_attr_uncached_inv()` | `xthal_dcache_region_writeback_inv()` | Invalidate cache | `sys_cache_data_invd_range()` |
| Cache line size | `USB_MEM_CACHE_ALIGN_BYTES` (32) | Cache alignment | `CONFIG_DCACHE_LINE_SIZE` |

**Files affected:**
- `src/common/usb_mem_util.c` - Cache operations
- Include: `<xtensa/core-macros.h>` → Replace with Zephyr cache APIs

---

## 3. INTERRUPT MANAGEMENT APIs

### 3.1 Interrupt Controller (usb_isr.c)
**Current Implementation:** CPEInterruptController (Custom Qualcomm)

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| Interrupt registration | `CPEInterruptController_RegisterInterrupt()` | Register ISR handler | `IRQ_CONNECT()` macro |
| Interrupt deregistration | `CPEInterruptController_DeregisterInterrupt()` | Unregister ISR | N/A (static in Zephyr) |
| Enable interrupt | `CPEInterruptController_EnableInterrupt()` | Enable IRQ line | `irq_enable()` |
| Disable interrupt | `CPEInterruptController_DisableInterrupt()` | Disable IRQ line | `irq_disable()` |
| Clear pending | `CPEInterruptController_ClearPending()` | Clear pending IRQ | Platform-specific |

**Interrupt Numbers Used:**
- `USB_CTRL_EE1_IRQ` (5) - Device event
- `USB_CTRL_POWER_EVENT_IRQ` (10) - Power event
- `USB_CTRL_HSPHY_IRQ` (11) - High-speed PHY
- `USB_PHY_DMSE_IRQ` (12) - Not used
- `USB_PHY_DPSE_IRQ` (13) - DP/DM edge detection
- `USB_SOF_IRQ` (14) - Not used
- `USB_RECOVERED_SOF_IRQ` (15) - Not used

**Files affected:**
- `src/dci/usb_isr.c` - All interrupt functions
- `src/dci/usb_isr.h` - Interrupt definitions
- Include: `CPEInterruptController.h` → Replace with Zephyr IRQ APIs

---

## 4. TIMING AND DELAY APIs

### 4.1 Delay Functions (usb_util.c)
**Current Implementation:** Qualcomm busywait

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_delay_us()` | `busywait()` | Microsecond busy-wait | `k_busy_wait()` |
| `usb_delay_ms()` | Loop of `busywait()` | Millisecond delay | `k_msleep()` or `k_busy_wait()` |

**Files affected:**
- `src/common/usb_util.c` - Delay functions
- Include: `busywait.h` → Replace with `<zephyr/kernel.h>`

---

## 5. POWER MANAGEMENT APIs

### 5.1 Clock and Power Control (usb_util.c)
**Current Implementation:** Qualcomm Power Manager

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_enable_clocks()` | `pm_vote()` | Enable/disable USB clocks | `pm_device_action_run()` |
| `usb_enable_clocks_in_isr()` | `pm_wake_if_idle()` | Wake from ISR context | `pm_device_runtime_get()` |

**Files affected:**
- `src/common/usb_util.c` - Power management functions
- Include: `pwr_mgr.h` → Replace with `<zephyr/pm/device.h>`

---

## 6. HARDWARE REGISTER ACCESS

### 6.1 Hardware I/O Macros (usb_hwio_9410.h, usb_dci_9410.c)
**Current Implementation:** Qualcomm HWIO macros

| Macro Pattern | Description | Zephyr Equivalent |
|---------------|-------------|-------------------|
| `HWIO_*_IN` | Read register | `sys_read32()` or direct pointer access |
| `HWIO_*_OUT()` | Write register | `sys_write32()` or direct pointer access |
| `HWIO_*_OUTM()` | Masked write | `sys_write32()` with masking |
| `HWIO_*_INM()` | Masked read | `sys_read32()` with masking |

**Files affected:**
- `src/dci/usb_hwio_9410.h` - All HWIO macro definitions
- `src/dci/usb_dci_9410.c` - Register access code
- `src/dci/usb_dci.c` - Register operations
- `src/dci/usb_isr.c` - ISR register access

---

## 7. LOGGING AND DEBUG APIs

### 7.1 Logging System (usb_log.c, usb_log_api.c)
**Current Implementation:** Custom USB logging with ACDB

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `USB_LOG()` | Custom log macro | General logging | `LOG_INF()`, `LOG_DBG()` |
| `USB_LOG_ERR()` | Custom error log | Error logging | `LOG_ERR()` |
| `USB_LOG_DBG()` | Custom debug log | Debug logging | `LOG_DBG()` |
| `USB_ULOG()` | Custom micro log | Micro logging | `LOG_INF()` |
| `USB_ASSERT()` | Custom assert | Assertion | `__ASSERT()` |

**Files affected:**
- `src/common/usb_log.c` - Logging implementation
- `src/common/usb_log.h` - Log macros
- `src/al/usb_log_api.c` - Log API implementation
- All source files using logging macros

---

## 8. ERROR HANDLING APIs

### 8.1 Fatal Error Handling (usb_util.c)
**Current Implementation:** Qualcomm error handler

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_error_fatal()` | `err_Fatal_internal0()` | Fatal error handler | `k_panic()` or `__ASSERT()` |

**Files affected:**
- `src/common/usb_util.c` - Error handling
- Include: `err.h` → Replace with Zephyr panic APIs

---

## 9. CONFIGURATION AND CALIBRATION APIs

### 9.1 ACDB (Audio Calibration Database) (usb_util.c)
**Current Implementation:** Qualcomm ACDB

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `usb_get_acdb_params()` | `acdb_ioctl()` | Get USB parameters from ACDB | Device tree or Kconfig |

**Files affected:**
- `src/common/usb_util.c` - ACDB access
- Include: `acdb.h` → Replace with device tree parsing

---

## 10. STRING OPERATIONS

### 10.1 Safe String Functions (usb_al_hlos.c)
**Current Implementation:** Qualcomm stringl library

| Function | Current API | Description | Zephyr Equivalent |
|----------|-------------|-------------|-------------------|
| `memscpy()` | Safe memory copy | Bounds-checked memcpy | `memcpy()` with manual checks or `strncpy()` |

**Files affected:**
- `src/al/usb_al_hlos.c` - String operations
- Include: `<stringl/stringl.h>` → Replace with standard C or Zephyr APIs

---

## 11. PLATFORM-SPECIFIC HEADERS

### Headers to Replace:

| Current Header | Purpose | Zephyr Replacement |
|----------------|---------|-------------------|
| `qurt.h` | QuRT OS APIs | `<zephyr/kernel.h>` |
| `qurt_signal2.h` | Signal APIs | `<zephyr/kernel.h>` |
| `qurt_thread.h` | Thread APIs | `<zephyr/kernel.h>` |
| `qurt_error.h` | Error codes | `<zephyr/sys/errno.h>` |
| `qurt_mutex.h` | Mutex APIs | `<zephyr/kernel.h>` |
| `busywait.h` | Delay functions | `<zephyr/kernel.h>` |
| `pwr_mgr.h` | Power management | `<zephyr/pm/device.h>` |
| `err.h` | Error handling | `<zephyr/sys/__assert.h>` |
| `acdb.h` | Calibration DB | Device tree APIs |
| `memheap_lite.h` | Memory heap | `<zephyr/kernel.h>` |
| `<xtensa/core-macros.h>` | Xtensa cache ops | `<zephyr/cache.h>` |
| `CPEInterruptController.h` | Interrupt controller | `<zephyr/irq.h>` |
| `<stringl/stringl.h>` | Safe strings | Standard C library |
| `led.h` | LED control | `<zephyr/drivers/led.h>` |
| `usb_svc_data.h` | Service data | Custom implementation |

---

## 12. ARCHITECTURE-SPECIFIC CODE

### 12.1 Memory Address Mapping (usb_mem_util.c)
**Current Implementation:** Direct address manipulation for cache attributes

```c
#define UNCACHED(addr) ((void*)((((uint32_t)addr) & ~0xf0000000)))
#define CACHED(addr) ((void*)((((uint32_t)addr) & ~0xf0000000) | 0x20000000))
```

**Zephyr Approach:**
- Use memory regions defined in device tree
- Use Zephyr cache management APIs
- Platform-specific memory attributes

**Files affected:**
- `src/common/usb_mem_util.c` - Address manipulation macros

---

## 13. FUNCTION TABLE ARCHITECTURE

### 13.1 Function Pointer Tables
The code uses function pointer tables for abstraction. These don't need OS changes but should be reviewed:

| Table | File | Purpose |
|-------|------|---------|
| `fn_tbl_al` | `usb_al_hlos.c` | Adaptation layer functions |
| `fn_tbl_api` | `usb_al_hlos.c` | API functions |
| `fn_tbl_util` | `usb_util.c` | Utility functions |
| `fn_tbl_mem_util` | `usb_mem_util.c` | Memory utility functions |
| `fn_tbl_isr` | `usb_isr.c` | ISR functions |

---

## 14. SUMMARY OF CRITICAL CHANGES NEEDED

### High Priority (Core OS Dependencies):
1. **Threading System** - Replace QuRT threads with Zephyr threads
2. **Synchronization** - Replace QuRT signals/mutexes with Zephyr equivalents
3. **Interrupt Handling** - Replace CPEInterruptController with Zephyr IRQ APIs
4. **Memory Management** - Adapt to Zephyr heap and cache APIs
5. **Hardware Register Access** - Replace HWIO macros with Zephyr register access

### Medium Priority (Platform Services):
6. **Power Management** - Integrate with Zephyr PM subsystem
7. **Timing/Delays** - Replace busywait with Zephyr delay APIs
8. **Logging** - Migrate to Zephyr logging subsystem
9. **Configuration** - Replace ACDB with device tree

### Low Priority (Utilities):
10. **String Operations** - Use standard C or Zephyr string functions
11. **Error Handling** - Use Zephyr panic/assert mechanisms

---

## 15. RECOMMENDED PORTING STRATEGY

### Phase 1: Core OS Abstraction Layer
1. Create Zephyr-specific implementations in new files:
   - `usb_al_zephyr.c` (replace `usb_al_hlos.c`)
   - `usb_util_zephyr.c` (replace OS-specific parts of `usb_util.c`)
   - `usb_mem_util_zephyr.c` (replace platform-specific memory code)
   - `usb_isr_zephyr.c` (replace interrupt controller code)

### Phase 2: Hardware Abstraction
2. Create Zephyr device tree bindings for USB controller
3. Replace HWIO macros with Zephyr register access patterns
4. Implement power management using Zephyr PM APIs

### Phase 3: Integration
5. Update build system (CMakeLists.txt, Kconfig)
6. Migrate logging to Zephyr logging subsystem
7. Replace ACDB with device tree configuration
8. Testing and validation

---

## 16. FILES REQUIRING MODIFICATION

### Critical Files (Major Changes):
- `src/al/usb_al_hlos.c` - Complete rewrite for Zephyr
- `src/al/usb_al_hlos.h` - Update for Zephyr types
- `src/common/usb_util.c` - OS-specific functions
- `src/common/usb_mem_util.c` - Memory and cache operations
- `src/dci/usb_isr.c` - Interrupt handling
- `src/dci/usb_hwio_9410.h` - Register access macros

### Moderate Changes:
- `src/common/usb_log.c` - Logging implementation
- `src/al/usb_log_api.c` - Log API
- All files with `#include` statements for OS headers

### Minor Changes:
- Header files with type definitions
- Files using logging macros
- Build configuration files

---

## CONCLUSION

The USB driver has significant dependencies on Qualcomm's QuRT RTOS and proprietary libraries. A successful port to Zephyr OS requires:

1. **Systematic replacement** of all QuRT APIs with Zephyr equivalents
2. **Abstraction layer redesign** to support Zephyr's threading and synchronization models
3. **Hardware register access** migration from HWIO macros to Zephyr patterns
4. **Device tree integration** for configuration instead of ACDB
5. **Interrupt controller** adaptation to Zephyr's IRQ subsystem
6. **Memory management** alignment with Zephyr's heap and cache APIs

The modular architecture with function tables provides good separation, making the port more manageable by isolating OS-specific code in the adaptation layer.
