# USB Zephyr Functions List
## Directory: Z:\usb\soccp_glymur\soccp_proc\battman\usb\usb_zephyr

This document lists all functions in the USB Zephyr driver with their descriptions organized by file.

---

## 1. inc/usb_api.h - Main USB API Header

### usb_set_params
- **Description**: Application or service layer can call this API to pass important ACDB information like qc_pid, vid_override, pid_override. A unique composition will be returned corresponding to qc_pid.
- **Parameters**: 
  - `usb_dev_params_t* params` - Pointer to ACDB info
  - `usb_ifc_id** usb_comp` - Pointer to USB composition (output)
  - `uint8* usb_comp_num_ifc` - Number of interfaces in USB composition (output)
- **Returns**: boolean

### usb_open
- **Description**: Client calls this function to register with USB. All clients need to call this function to receive callbacks from USB.
- **Parameters**:
  - `client_ctx_t** usb_ctx` - Client context (output)
  - `usb_ifc_id ifc_id` - Client interface ID
  - `void* data` - Client data
  - `usb_event_func_t event_cb` - Event callback function
  - `usb_func_cb_t rx_cb` - RX callback function
  - `usb_func_cb_t tx_cb` - TX callback function
  - `uint32 rx_buf_num` - Max size of RX buffer queue
  - `uint32 tx_buf_num` - Max size of TX buffer queue
- **Returns**: uint32 error code

### usb_read
- **Description**: Client calls this function to submit buffer to receive data from USB host. Only submits the buffer into queue; client still needs to call usb_signal for USB thread to submit to hardware.
- **Parameters**:
  - `client_ctx_t* client_ctx` - USB context
  - `uint8* buf_ptr` - Pointer to buffer
  - `uint32 buffer_size` - Max size of buffer to receive
- **Returns**: uint32 error code (0 = success, non-zero = fail)

### usb_write
- **Description**: Client calls this function to submit buffer to send data to USB host. Only submits the buffer into queue; client still needs to call usb_signal for USB thread to submit to hardware.
- **Parameters**:
  - `client_ctx_t* client_ctx` - USB context
  - `uint8* buf_ptr` - Pointer to buffer
  - `uint32 transfer_size` - Number of bytes to transfer
- **Returns**: uint32 error code (0 = success, non-zero = fail)

### usb_close
- **Description**: Close USB with that client. When all clients are closed, USB will shutdown.
- **Parameters**:
  - `client_ctx_t* client_ctx` - Client context
- **Returns**: uint32 error code (0 = success, non-zero = fail)

### usb_create_thread
- **Description**: This function will create USB driver thread and register it with OS. Essential when using independent USB thread.
- **Parameters**: None
- **Returns**: TRUE when thread created successfully, FALSE when failed

### usb_thread_init
- **Description**: Enable USB memory and global variables + enable USB hardware. Call to allocate all the USB stack before calling usb_open.
- **Parameters**:
  - `void* client_sig` - Thread signal pointer for USB (USB uses signal bit 0x000F0000)
- **Returns**: None

### usb_handle_signal
- **Description**: Handles various events signaled to USB thread from other threads and interrupt contexts. Handles USB controller events, power events, and VBUS events.
- **Parameters**:
  - `uint32 client_sig` - Current state of USB thread signals
- **Returns**: None

### usb_open_ctrl
- **Description**: API for USB bus control channel clients to register in/out data callbacks. Provides means to register callbacks for clients communicating over control channel (e.g., audio tune service).
- **Parameters**:
  - `ctrl_client_ctx_t** client_ctx` - Context of the control client (output)
  - `usb_ifc_id ifc_id` - Identifier for interface type
  - `ctrl_out_cb_t ctrl_out_cb` - Callback to receive data from host
  - `ctrl_in_cb_t ctrl_in_cb` - Callback to send data to host
- **Returns**: uint32 (TRUE if successful, FALSE if failed)

### usb_lb_task_init
- **Description**: USB dummy loopback client initialization API. Can only be used for verifying USB layer functionality through a simple loopback application that exercises Audio and HID functionality.
- **Parameters**: None
- **Returns**: boolean (Success or Failure)

---

## 2. inc/usb_hid_api.h - HID API Functions

### usb_hid_open
- **Description**: Opens HID interface for client.
- **Parameters**:
  - `client_ctx_t** client_ctx` - Client context (output)
  - `usb_ifc_id ifc_id` - Interface ID
- **Returns**: uint32 error code

### usb_hid_report
- **Description**: Sends HID report to host.
- **Parameters**:
  - `client_ctx_t* client_ctx` - Client context
  - `usb_hid_bitmask_cmd_t report` - HID command bitmask (play/pause, volume, etc.)
- **Returns**: uint32 error code

---

## 3. inc/usb_log_api.h - USB Logging API

### usb_log_open
- **Description**: API to initialize USB obex interface to send ulog over USB. Internally calls usb_open() for USB_IFC_ID_BULK interface. Allocates RX buffer to receive log commands and TX buffer to send ulog data to host.
- **Parameters**: None
- **Returns**: None

### usb_log_close
- **Description**: API to clean up USB obex interface to send ulog over USB. Internally calls usb_close() for USB_IFC_ID_BULK interface. Deallocates RX and TX buffers.
- **Parameters**: None
- **Returns**: None

### usb_log_read_send_ulog
- **Description**: API to read ulog data buffer and send over USB. Accumulates data bytes read from ulog API. If TX buffer has sufficient data, sends over USB through usb_write(). Otherwise, schedules a timer to re-accumulate.
- **Parameters**: None
- **Returns**: None

---

## 4. src/al/usb_al_zephyr.c - Adaptation Layer Functions

### usb_client_get_config
- **Description**: Gets client configuration data.
- **Parameters**: `uint8 client_id` - Client ID
- **Returns**: void* pointer to client data

### usb_client_notification
- **Description**: Notifies client of USB events (DFU entry/exit, audio control config, stream enable/disable, etc.).
- **Parameters**:
  - `uint32 event` - Event type
  - `uint32 client_id` - Client ID
  - `void* data` - Event data
- **Returns**: None

### usb_ctrl_out_cb
- **Description**: Control OUT callback handler.
- **Parameters**:
  - `uint8* setup_ptr` - Setup packet pointer
  - `uint8* payload` - Payload data
  - `uint32 payload_size` - Payload size
- **Returns**: boolean (success/failure)

### usb_ctrl_in_cb
- **Description**: Control IN callback handler.
- **Parameters**:
  - `uint8* setup_ptr` - Setup packet pointer
  - `uint8* payload` - Payload buffer
  - `uint32* payload_size` - Payload size (in/out)
- **Returns**: boolean (success/failure)

### usb_register_ctrl_client
- **Description**: Registers control channel client.
- **Parameters**: `ctrl_client_ctx_t* ctrl_ctx` - Control client context
- **Returns**: None

### usb_al_hlos_isr_vbus_event
- **Description**: Handles VBUS interrupt event.
- **Parameters**: `uint32 vbus_high` - VBUS state (high/low)
- **Returns**: None

### usb_al_hlos_isr_pwr_event
- **Description**: Handles power event interrupt.
- **Parameters**: `uint32 event_id` - Event ID
- **Returns**: None

### usb_al_hlos_log_timer_cb
- **Description**: Log timer callback handler.
- **Parameters**: `uint32 event_id` - Event ID
- **Returns**: None

### usb_al_hlos_enum_complete
- **Description**: Handles enumeration complete event.
- **Parameters**: `boolean enum_flag` - Enumeration status
- **Returns**: None (static function)

### usb_al_hlos_disconnect_handler
- **Description**: Handles USB disconnect event. Returns buffers and shuts down USB.
- **Parameters**: None
- **Returns**: None

### usb_al_disconnect_cb
- **Description**: Disconnect callback (error path).
- **Parameters**: None
- **Returns**: None

### usb_al_notify_suspend
- **Description**: Notifies suspend state change.
- **Parameters**: `boolean is_suspend` - Suspend state
- **Returns**: None

### usb_ctx_init
- **Description**: Initializes USB context structure. Allocates memory and sets up initial state.
- **Parameters**: None
- **Returns**: None

### usb_ctx_free
- **Description**: Frees USB context and associated resources.
- **Parameters**: None
- **Returns**: None

### usb_tx_complete
- **Description**: TX transfer completion callback. Validates transfer and calls client TX callback.
- **Parameters**: `usb_urb_t* urb` - USB Request Block
- **Returns**: None

### usb_rx_complete
- **Description**: RX transfer completion callback. Validates transfer and calls client RX callback.
- **Parameters**: `usb_urb_t* urb` - USB Request Block
- **Returns**: None

### usb_handle_reset
- **Description**: Handles USB reset event. Resets enumeration state and function driver.
- **Parameters**: None
- **Returns**: None

### usb_al_hlos_bulk_init
- **Description**: Initializes USB hardware and function driver. Sets up callbacks and starts USB controller.
- **Parameters**: `usb_max_speed_required_t speed_required` - Required USB speed
- **Returns**: None

### usb_client_cnt
- **Description**: Counts number of registered clients.
- **Parameters**: None
- **Returns**: uint32 client count

### usb_deregister_client
- **Description**: Deregisters a client from USB.
- **Parameters**: `client_ctx_t* client_ctx` - Client context
- **Returns**: None

### usb_register_client
- **Description**: Registers a client with USB. Assigns client ID and checks if all clients are registered to start USB.
- **Parameters**: `client_ctx_t* client_ctx` - Client context
- **Returns**: boolean (success/failure)

### usb_copy_client_data
- **Description**: Copies client data to allocated memory.
- **Parameters**:
  - `void* data_in` - Input data
  - `uint32 size` - Data size
- **Returns**: void* pointer to copied data

### usb_alloc_register_client_ctx
- **Description**: Allocates and registers client context.
- **Parameters**:
  - `usb_ifc_id ifc_id` - Interface ID
  - `usb_event_func_t event_cb` - Event callback
  - `usb_func_cb_t rx_cb` - RX callback
  - `usb_func_cb_t tx_cb` - TX callback
  - `void* data` - Client data
  - `uint32 data_size` - Data size
- **Returns**: client_ctx_t* pointer

### usb_send_tx
- **Description**: Sends TX packet if USB is enumerated and VBUS is high.
- **Parameters**:
  - `unsigned char* pkt` - Packet buffer
  - `uint32 len` - Length
  - `uint32 req_id` - Request ID
  - `uint32 client_id` - Client ID
  - `void* cb_data` - Callback data
- **Returns**: uint32 error code

### usb_send_hid_report
- **Description**: Sends HID report if USB is enumerated.
- **Parameters**:
  - `uint32 client_id` - Client ID
  - `usb_hid_bitmask_cmd_t report_mask` - Report bitmask
- **Returns**: uint32 error code

### usb_send_rx
- **Description**: Submits RX packet if USB is enumerated and VBUS is high.
- **Parameters**:
  - `unsigned char* pkt` - Packet buffer
  - `uint32 len` - Length
  - `uint32 req_id` - Request ID
  - `uint32 client_id` - Client ID
  - `void* cb_data` - Callback data
- **Returns**: uint32 error code

### usb_check_enum
- **Description**: Checks if USB is enumerated.
- **Parameters**: None
- **Returns**: boolean enumeration status

### usb_get_max_packet_size
- **Description**: Gets maximum packet size for current speed.
- **Parameters**: None
- **Returns**: uint32 max packet size

### usb_remove_thread
- **Description**: Removes USB thread and cleans up resources.
- **Parameters**: None
- **Returns**: None

### usb_shutdown
- **Description**: Shuts down USB hardware and function driver.
- **Parameters**: None
- **Returns**: None

### usb_return_buffer
- **Description**: Returns/cancels pending buffers for a client.
- **Parameters**: `client_ctx_t* client_ctx` - Client context
- **Returns**: None

### usb_internal_close
- **Description**: Internal close function. Returns buffers, notifies client, deregisters client, and shuts down if no clients remain.
- **Parameters**: `client_ctx_t* client_ctx` - Client context
- **Returns**: boolean (always TRUE)

### usb_thread_entry
- **Description**: USB thread entry point. Waits for events and handles them.
- **Parameters**: Zephyr thread parameters (p1, p2, p3)
- **Returns**: None (static function)

---

## 5. src/dcd/usb_dcd.c - Device Controller Driver Functions

### usb_dcd_desc_max_packet_size
- **Description**: Returns max packet size for descriptor based on speed.
- **Parameters**: `usb_device_connect_speed_t speed` - USB speed
- **Returns**: uint32 max packet size (1024 for SuperSpeed, 512 otherwise)

### usb_dcd_create_dev_desc
- **Description**: Allocates and initializes device descriptor.
- **Parameters**:
  - `usb_desc_device_t** dev_desc` - Device descriptor pointer (output)
  - `uint16 vendor_id` - Vendor ID
  - `uint16 product_id` - Product ID
  - `usb_device_connect_speed_t speed` - Current speed
  - `usb_max_speed_required_t speed_required` - Required speed
  - `uint8 n_cfg` - Number of configurations
- **Returns**: None

### usb_dcd_create_dev_qual_desc
- **Description**: Allocates and initializes device qualifier descriptor.
- **Parameters**: `usb_desc_dev_qual_t** dev_qual_desc` - Device qualifier descriptor (output)
- **Returns**: None

### usb_dcd_allocate_dev_qual
- **Description**: Allocates device qualifier descriptor structure.
- **Parameters**: `usb_dcd_dsc_qual_t** dev_qual` - Device qualifier (output)
- **Returns**: None

### usb_dcd_allocate_strings
- **Description**: Allocates string descriptor pointers.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint16 lang_id` - Language ID
  - `uint8* manuf_str` - Manufacturer string
  - `uint8* product_str` - Product string
- **Returns**: None

### usb_dcd_create_ep_comp_desc
- **Description**: Creates endpoint companion descriptor (for SuperSpeed).
- **Parameters**:
  - `usb_ep_comp_desc_t** ep_comp_ptr` - EP companion descriptor (output)
  - `uint8 burst_size` - Burst size
  - `uint8 attr` - Attributes
  - `uint8 bpi` - Bytes per interval
- **Returns**: None

### usb_dcd_create_ep_desc
- **Description**: Creates endpoint descriptor.
- **Parameters**:
  - `usb_dcd_dsc_endpoint_t** endpoint` - Endpoint descriptor (output)
  - `uint8 ep_num` - Endpoint number
  - `uint8 ep_mask` - Endpoint direction mask
  - `uint8 ep_attr` - Endpoint attributes
  - `uint8 ep_interval` - Polling interval
  - `uint16 max_packet_size` - Max packet size
- **Returns**: None

### usb_dcd_create_ifc_desc
- **Description**: Creates interface descriptor.
- **Parameters**:
  - `usb_dcd_dsc_interface_t** interface` - Interface descriptor (output)
  - `uint8 ifc_index` - Interface number
  - `uint8 alt_setting` - Alternate setting
  - `uint8 n_ep` - Number of endpoints
  - `uint8 ifc_class` - Interface class
  - `uint8 subclass` - Interface subclass
  - `uint8 protocol` - Interface protocol
  - `uint8 str_index` - String index
- **Returns**: None

### dcd_get_config_tree
- **Description**: Gets configuration tree.
- **Parameters**: `const usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: usb_dcd_dsc_configuration_t* configuration tree

### dcd_get_config_value
- **Description**: Gets current configuration value.
- **Parameters**: `const usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: int configuration value

### find_config_by_value
- **Description**: Finds configuration by value.
- **Parameters**:
  - `const usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint8 value` - Configuration value
- **Returns**: usb_dcd_dsc_configuration_t* configuration

### get_curr_ifc_alt_set
- **Description**: Finds interface with current alternate setting by interface number.
- **Parameters**:
  - `const usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint8 ifc_num` - Interface number
- **Returns**: usb_dcd_dsc_interface_t* interface

### usb_dcd_find_ep
- **Description**: Finds endpoint configuration by endpoint address.
- **Parameters**:
  - `const usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint16 ep_address` - Endpoint address
- **Returns**: usb_dcd_dsc_endpoint_t* endpoint

### get_string_desc
- **Description**: Finds string descriptor by language ID and index.
- **Parameters**:
  - `const usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint16 lang_id` - Language ID
  - `uint8 index` - String index
- **Returns**: usb_desc_header_t* string descriptor

### usb_dcd_fd_notify
- **Description**: Triggers function driver notification callback.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_notify_events_t event` - Notification event
- **Returns**: None

### usb_dcd_set_interface
- **Description**: Sets alternate setting for given interface. Configures endpoints for new alternate setting.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_dcd_dsc_interface_t* ifc` - Interface
  - `uint8 ifc_num` - Interface number
  - `uint8 alt` - Alternate setting
- **Returns**: int (0 if OK, negative if error)

### usb_dcd_set_config
- **Description**: Sets new configuration value. Configures device with specified configuration.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint8 new_config` - New configuration value
- **Returns**: int (0 if OK, negative if error)

### usb_dcd_control_transfer
- **Description**: Initiates control transfer. Used in custom SETUP flow.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `int is_tx` - 1 if TX, 0 if RX
  - `void* buff` - Buffer to transmit
  - `uint32 len` - Number of bytes
- **Returns**: int (bytes transferred or negative error code)

### usb_dcd_control_reply
- **Description**: Initiates TX transfer using setup_status buffer.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `uint32 len` - Transfer length
- **Returns**: int (bytes transferred or negative error code)

### handle_get_descriptor
- **Description**: Handles USB_SETUP_REQ_GET_DESCRIPTOR request. Returns device, configuration, BOS, string, device qualifier, or other speed descriptors.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_setup_packet_t* req` - Setup request
  - `usb_ep_dir_t ctrl_data_dir` - Control data direction
- **Returns**: int (bytes transferred or negative error code)

### handle_setup_dev
- **Description**: Handles device-level setup requests (GET_STATUS, CLEAR_FEATURE, SET_FEATURE, SET_ADDRESS, SET_SEL, SET_ISOCH_DELAY, GET/SET_DESCRIPTOR, GET/SET_CONFIGURATION).
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_setup_packet_t* req` - Setup request
  - `usb_ep_dir_t ctrl_data_dir` - Control data direction
- **Returns**: int (bytes transferred or negative error code)

### handle_setup_ifc
- **Description**: Handles interface-level setup requests (GET_STATUS, CLEAR_FEATURE, SET_FEATURE, GET_INTERFACE, SET_INTERFACE, GET_DESCRIPTOR).
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_setup_packet_t* req` - Setup request
  - `usb_ep_dir_t ctrl_data_dir` - Control data direction
- **Returns**: int (bytes transferred or negative error code)

### handle_ep_halt
- **Description**: Handles endpoint halt/unhalt (stall/unstall).
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_dcd_dsc_endpoint_t* ep` - Endpoint
  - `int halt` - 1 to halt, 0 to unhalt
- **Returns**: int (0 success, -1 fail)

### handle_setup_ep
- **Description**: Handles endpoint-level setup requests (GET_STATUS, CLEAR_FEATURE, SET_FEATURE, SYNCH_FRAME).
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_setup_packet_t* req` - Setup request
  - `usb_ep_dir_t ctrl_data_dir` - Control data direction
- **Returns**: int (bytes transferred or negative error code)

### handle_setup_std
- **Description**: Routes standard setup requests to device, interface, or endpoint handlers.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_setup_packet_t* req` - Setup request
- **Returns**: int (bytes transferred or negative error code)

### usb_dcd_handle_reset
- **Description**: Handles reset notification from DCI. Moves device to 'default' state (not configured, address = 0).
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_handle_disconnect
- **Description**: Handles disconnect notification from DCI. Passes callback to function driver.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_handle_suspend
- **Description**: Handles suspend notification from DCI. Passes callback to function driver.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_handle_setup
- **Description**: Handles setup notification from DCI. Routes to standard, class, or vendor handlers.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `void* buffer_ptr` - Setup packet buffer
- **Returns**: None

### usb_dcd_port_status_changed
- **Description**: Handles port status change notification from DCI. Updates speed and notifies function driver.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_notify
- **Description**: API function passed to DCI for hardware event callbacks. Routes events to appropriate handlers.
- **Parameters**:
  - `void* dev_ptr` - DCD context
  - `usb_notify_events_t event` - Notification event
  - `void* buffer_ptr` - Event data buffer
- **Returns**: None

### usb_dcd_set_bos
- **Description**: Sets BOS (Binary Object Store) descriptor.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_bos_desc_t* bos_desc` - BOS descriptor
- **Returns**: None

### usb_dcd_set_cfg_tree
- **Description**: Updates configuration descriptor tree from function driver.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_dcd_dsc_configuration_t* cfg_tree` - Configuration tree
- **Returns**: boolean (TRUE if successful)

### usb_dcd_create_desc
- **Description**: Creates device descriptor after speed update.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx_ptr` - DCD context
  - `uint16 vendor_id` - Vendor ID
  - `uint16 product_id` - Product ID
  - `uint8 n_cfg` - Number of configurations
- **Returns**: None

### usb_dcd_ctrl_start_xfer
- **Description**: Starts a new EP0 transfer for receiving setup packets.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_init
- **Description**: Initializes DCD layer. Should be called prior to any other USB activity.
- **Parameters**:
  - `usb_max_speed_required_t speed_required` - Required speed
  - `usb_dcd_ctx_t** dcd_ctx_ptr` - DCD context (output)
  - `void* fd_ctx` - Function driver context
  - `usb_fd_callback_t fd_cb` - Function driver callbacks
  - `uint16 lang_id` - Language ID
  - `uint8* manuf_str` - Manufacturer string
  - `uint8* product_str` - Product string
  - `uint32 feature_flags` - Feature flags
- **Returns**: boolean (FALSE when fail, TRUE when success)

### usb_dcd_free_desc
- **Description**: Frees memory and data structures allocated for device, config, BOS, and device qualifier descriptors.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: boolean (TRUE if successful)

### usb_dcd_shutdown
- **Description**: Shuts down the DCD layer. Frees all DCD context resources.
- **Parameters**: `usb_dcd_ctx_t** dcd_ptr` - DCD context pointer
- **Returns**: None

### usb_dcd_submit_urb
- **Description**: Submits URB (USB Request Block) for transfer. Non-blocking. Ownership passes to DCI until complete_callback is called.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_urb_t* urb` - USB Request Block
- **Returns**: int (0 if OK, negative for error)

### usb_dcd_set_core
- **Description**: Sets DCD core type.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_core_type core_id` - Core ID
- **Returns**: None

### usb_dcd_get_dci_ctx
- **Description**: Returns DCI context pointer.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: void* DCI context

### usb_dcd_get_speed
- **Description**: Gets current USB connection speed.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: usb_device_connect_speed_t speed

### usb_dcd_is_usb_configured
- **Description**: Returns whether USB is configured.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: boolean (TRUE if configured)

### usb_dcd_get_ctrl_urb_tx_transfer_status
- **Description**: Returns transfer status for TX control URB.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: uint32 URB transfer status

### usb_dcd_poll
- **Description**: Pass-through function to DCI layer for polling events.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_reset
- **Description**: Pass-through function to DCI layer for USB reset.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: None

### usb_dcd_cancel_transfer
- **Description**: Pass-through function to DCI layer to cancel transfer. Decodes URB before passing to DCI.
- **Parameters**:
  - `usb_dcd_ctx_t* dcd_ctx` - DCD context
  - `usb_urb_t* urb_ptr` - URB to cancel
- **Returns**: uint32 error code

### usb_dcd_get_max_packet_size
- **Description**: Pass-through function to DCI layer to get max packet size.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: uint32 max packet size

### usb_dcd_wakeup
- **Description**: Pass-through function to DCI layer to handle remote wakeup.
- **Parameters**: `usb_dcd_ctx_t* dcd_ctx` - DCD context
- **Returns**: boolean (TRUE if successful)

---

## Summary

The USB Zephyr driver is organized into several layers:

1. **API Layer** (inc/usb_api.h): Main client-facing APIs for USB operations
2. **HID Layer** (inc/usb_hid_api.h): HID-specific functions
3. **Logging Layer** (inc/usb_log_api.h): USB logging over bulk interface
4. **Adaptation Layer** (src/al/): OS-specific adaptation (Zephyr RTOS)
5. **Device Controller Driver** (src/dcd/): USB device controller management
6. **Device Controller Interface** (src/dci/): Hardware abstraction layer
7. **Function Driver** (src/func/): USB function implementations (Audio, HID, DFU, Bulk)
8. **Common Utilities** (src/common/): Memory management, logging, utilities

The driver supports:
- Multiple USB speeds (Full, High, Super Speed)
- Multiple device classes (Audio, HID, DFU, Bulk)
- Control, Bulk, Isochronous, and Interrupt transfers
- USB enumeration and configuration
- Power management (suspend/resume, remote wakeup)
- Dynamic descriptor generation
- Multiple client registration

---

**Note**: This list covers the main API functions. Additional internal/static functions exist in source files for implementation details. For complete function signatures and detailed parameter descriptions, refer to the individual header and source files.
