/*-----------------------------------------------------------------------------
* Name: main.c
* PROJECT: TEXT EDITOR for FRDM-KL05Z board using 4x4 keyboard and LCD
* Author: Gregório da Luz
*----------------------------------------------------------------------------*/
#include "MKL05Z4.h"   
#include "keyboard.h"
#include "i2c.h"
#include "lcd1602.h"
#include "uart.h"

int main()
{	
	uint8_t charac = 0; 							// it server to control the position of the characters on the LCD 2 rows 16 characters each
	uint8_t group = 0;								// group control for the buttons
	uint8_t column_LCD = 0;						// column selector for the LCD1602_SetCursor()
	char key;													// keeps the number of the key pressed
	char lcd_text[99];						    // keeps the registers read from the Hitachi driver on the LCD
	char temp_c;							        // holding temporary char value
	
	
	UART_Init(9600);
	keyboardInitialize();
	LCD1602_Init();	
	
while(1){
	key = keypad_getkey();
	// buttons 1 and 5 have special functions
	if(key != 0 && key != 1 && key != 5){
		while(key == keypad_getkey()) {
			if(group < 4){
				LCD1602_SetCursor(charac,column_LCD);
				temp_c = pressed_key(key, group);
				group++;
				}
			else {group = 0;}
			delay_ms(700);
		}
		
		if(column_LCD==1){
			charac += 15;
			lcd_text[charac] = temp_c;
			charac -= 15;
		} else {
			lcd_text[charac] = temp_c;
		}
		
		charac++;	
	}
	
	//button 1 delete last character
	if(key == 1){
			//deleting from second row first column
		if(charac == 0 && column_LCD == 1){
			column_LCD--;
			charac = 15;
		}
		else if(charac != 0){
			charac--;
		}
		LCD1602_SetCursor(charac,column_LCD);
		LCD1602_Print(" ");
		LCD1602_SetCursor(charac,column_LCD);
		delay_ms(700);
	}
	
	//button 5 is for send the tweet
	if(key == 5){
		if(column_LCD == 1){
			charac += 15;
			UART_Println(lcd_text, charac);
			charac -= 15;
		}
		else{
			UART_Println(lcd_text,charac);
		}
		//after sending the tweet we must clean the screen and reset "charac" and "column_LCD" values
		delay_ms(700);
		LCD1602_ClearAll();
		charac = 0;
		column_LCD = 0;
	}
	
	
	/**
	 * END OF LINE BEHAVIORS
	 **/
	//changes to new line on LCD when we reach the end of line 0
	if(charac == 16 && column_LCD == 0){
		charac = 0;
		column_LCD++;
		LCD1602_SetCursor(charac,column_LCD);
	}

	//Send the TWEET, cleaning the screen and resetting parameters
	if(charac == 16 && column_LCD == 1){
		UART_Println(lcd_text,32);		//why 32 you ask? because here we know we will always have 32 characters, it's the end of the road
		LCD1602_ClearAll();
		charac = 0;
		column_LCD--;
	}
	
	//zero the group before starting a new loop
	group = 0;
	}
}

