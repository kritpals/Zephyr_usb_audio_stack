#ifndef USB_LOG_API_H
#define USB_LOG_API_H

// ===================================================================
/**
 * @function  usb_log_open
 * 
 * @brief     API to initialize USB obex interface to send ulog over USB.
 *
 * @details   API to initialize USB obex interface to send ulog over USB.
 *            The API internally calls usb_open() for USB_IFC_ID_BULK interface.
 *            Allocates RX buffer to receive log commands.
 *            Allocates TX buffer to send ulog data to host.
 * 
 * @param     none.
 * 
 * @return    none.
 */
// ===================================================================
void usb_log_open(void);

// ===================================================================
/**
 * @function  usb_log_close
 * 
 * @brief     API to clean up USB obex interface to send ulog over USB.
 *
 * @details   API to clean up USB obex interface to send ulog over USB.
 *            The API internally calls usb_close() for USB_IFC_ID_BULK interface.
 *            Deallocates RX buffer to receive log commands.
 *            Deallocates TX buffer to send ulog data to host.
 * 
 * @param     none.
 * 
 * @return    none.
 */
// ===================================================================
void usb_log_close(void);

// ===================================================================
/**
 * @function  usb_log_read_send_ulog
 * 
 * @brief     API to read ulog data buffer and send over USB.
 *
 * @details   API accumulates data bytes read from ulog API.
 *            If TX buffer has sufficient ulog data accumulated,
 *            then the data will be sent over USB through usb_write() API.
 *            In case, TX buffer does not have enough data, a timer 
 *            will be scheduled to re-accumulate.
 *
 * @param     none.
 * 
 * @return    none.
 */
// ===================================================================
void usb_log_read_send_ulog(void);

#endif /* USB_LOG_API_H */

