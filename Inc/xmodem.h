/**
 * @file    xmodem.h
 * @author  Ferenc Nemeth
 * @date    21 Dec 2018
 * @brief   This module is the implementation of the Xmodem protocol.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth
 */

#ifndef XMODEM_H_
#define XMODEM_H_

#include "uart.h"
#include "flash.h"
#include "stdbool.h"

/* Maximum allowed errors (user defined). */
#define X_MAX_ERRORS ((uint8_t)1u)

/* Sizes of the packets. */
#define X_PACKET_128_SIZE ((uint16_t)128u)
#define X_PACKET_1K_SIZE  ((uint16_t)1024u)
#define X_PACKET_CRC_SIZE ((uint16_t)2u)

/* Relative location of the packets. */
#define X_PACKET_NUMBER_INDEX     ((uint16_t)0u)
#define X_PACKET_NUMBER_C_INDEX   ((uint16_t)1u)
#define X_PACKET_DATA_INDEX       ((uint16_t)2u)

/* Bytes defined by the protocol. */
#define X_SOH ((uint8_t)0x01u)  /**< Start Of Header (128 bytes). */
#define X_STX ((uint8_t)0x02u)  /**< Start Of Header (1024 bytes). */
#define X_EOT ((uint8_t)0x04u)  /**< End Of Transmission. */
#define X_ACK ((uint8_t)0x06u)  /**< Acknowledge. */
#define X_NAK ((uint8_t)0x15u)  /**< Not Acknowledge. */
#define X_CAN ((uint8_t)0x18u)  /**< Cancel. */
#define X_C   ((uint8_t)0x43u)  /**< ASCII "C", to notify the host, we want to use CRC16. */

/* Status report for the functions. */
typedef enum {
  X_OK            = 0x00u, /**< The action was successful. */
  X_ERROR_CRC     = 0x01u, /**< CRC calculation error. */
  X_ERROR_NUMBER  = 0x02u, /**< Packet number mismatch error. */
  X_ERROR_UART    = 0x04u, /**< UART communication error. */
  X_ERROR_FLASH   = 0x06u, /**< Flash related error. */
  X_ERROR         = 0xFFu  /**< Generic error. */
} xmodem_status;

void xmodem_receive(void);

#endif /* XMODEM_H_ */
