/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file uart.h
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing enums, structures and declarations.
 * @ver 0.1
 * Print functions have a "size" parameter added by Greg�rio
 */

#ifndef UART_H
#define UART_H

#include "frdm_bsp.h"

/**
 * @brief UART initialization
 *
 * @param Baud rate (e.g. 9600)
 */
void UART_Init(uint32_t baud_rate);
/**
 * @brief Print to serial port
 *
 * @param String to display.
 * new parameter added by Greg�rio
 */
void UART_Print(const char *str, uint8_t size);
/**
 * @brief Print to serial port and go to the next line
 *
 * @param String to display.
 * new parameter added by Greg�rio
 */
void UART_Println(const char *str, uint8_t size);

#endif /* UART_H */
