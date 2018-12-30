/**
 * @file    uart.h
 * @author  Ferenc Nemeth
 * @date    21 Dec 2018
 * @brief   This module is a layer between the HAL UART functions and my Xmodem protocol.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart1;

/* Timeout for HAL. */
#define UART_TIMEOUT ((uint16_t)1000u)

/* Status report for the functions. */
typedef enum {
  UART_OK     = 0x00u, /**< The action was successful. */
  UART_ERROR  = 0xFFu  /**< Generic error. */
} uart_status;

uart_status uart_receive(uint8_t *data, uint16_t length);
uart_status uart_transmit_str(uint8_t *data);
uart_status uart_transmit_ch(uint8_t data);


#endif /* UART_H_ */
