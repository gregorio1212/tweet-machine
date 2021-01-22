/*-----------------------------------------------------------------------------
* Name: keyboard.h
* PROJECT: TEXT EDITOR for FRDM-KL05Z board using 4x4 keyboard and LCD
* Author: Gregório da Luz
*----------------------------------------------------------------------------*/

#ifndef keyboard_h
#define keyboard_h

void keyboardInitialize(void);
char keypad_getkey(void);
void delay_Us(int n);
void delay_ms(int n);
char pressed_key(char button, uint8_t group);
#endif