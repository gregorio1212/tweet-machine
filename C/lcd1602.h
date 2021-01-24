/******************************************************************************
 * This file is a part of the SM2 Tutorial (C).                               *                                                 *
 ******************************************************************************/

/**
 * @file lcd1602.h
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing enums, structures and declarations for LCD 2x16.
 * @ver 0.1
 */

#ifndef LCD1602_H
#define LCD1602_H

#include "frdm_bsp.h"
#include "i2c.h"

/**
 * @brief LCD1602 initialization.
 */
void LCD1602_Init(void);
/**
 * @brief Print on the display.
 *	adapted by Gregório da Luz to return char value, which is the value of the letter written on the LCD screen
 * @param String to display.
 */
char LCD1602_Print(char *str);
/**
 * @brief Clear whole display.
 */
void LCD1602_ClearAll(void);
/**
 * @brief Set cursor on display.
 *
 * @param Column.
 * @param Row.
 */
void LCD1602_SetCursor(uint8_t col, uint8_t row);
/**
 * @brief Backlight turn on/off.
 *
 * @param State of the backlight.
 */
void LCD1602_Backlight(uint8_t state);
void LCD1602_Blink_On(void);
void LCD1602_Blink_Off(void);

void LCD1602_PrintNum(int number);
#endif  /* LCD1602_H */
