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

void charac_choice(char key, uint8_t group, uint8_t column_LCD, uint8_t charac, char text[]){
	char temp_c;							        // holding temporary character chosen
	while(key == keypad_getkey()) {
			if(group < 4){
				LCD1602_SetCursor(charac,column_LCD);
				temp_c = pressed_key(key, group);
				group++;
			} else {group = 0;}
			delay_ms(700);
	}
		
	if(column_LCD==1){
		charac += 15;
		text[charac] = temp_c;
		charac -= 15;
	} else { text[charac] = temp_c; }
}

void delete_character(uint8_t column_LCD, uint8_t charac){
		LCD1602_SetCursor(charac,column_LCD);
		LCD1602_Print(" ");
		LCD1602_SetCursor(charac,column_LCD);
		delay_ms(700);
}
	
void send_tweet(uint8_t column_LCD, uint8_t charac, char text[]){
		if(column_LCD == 1){
			charac += 15;
			UART_Println(text, charac);
			charac -= 15;
		} else{
			UART_Println(text,charac);
		}
		delay_ms(700);	//after sending the tweet we must clean the screen and reset "charac" and "column_LCD" values
		LCD1602_ClearAll();
}

int main()
{	
	uint8_t charac = 0; 					// it controls the position of the characters on the LCD
	uint8_t group = 0;					// group control for characters in the buttons
	uint8_t column_LCD = 0;					// column selector for the LCD1602_SetCursor()
	char key;						// keeps the number of the key pressed
	char lcd_text[99];			   		// keeps the typped values
	
	UART_Init(9600);
	keyboardInitialize();
	LCD1602_Init();	
	
	while(1){
		key = keypad_getkey();
		if(key != 0 && key != 1 && key != 5){	// buttons 1 and 5 have special functions, if key==0 no button is pressed
			charac_choice(key, group, column_LCD, charac, lcd_text);
			charac++;	
		}
		if(key == 1){ //button 1 deletes last character
			if(charac == 0 && column_LCD == 1){ //deleting procedure for when character is the 1st character on 2nd row
				column_LCD--;
				charac = 15;
			}	else if(charac != 0){ charac--;} //normal procedure when deleting charater
			delete_character(column_LCD, charac);
		}
		if(key == 5){ //button 5 is for send the tweet
			send_tweet(column_LCD, charac, lcd_text);
			charac = 0;
			column_LCD = 0;
		}
//LCD END OF LINE BEHAVIORS
		if(charac==16){
			charac = 0;
			if(column_LCD==0){ //moving to new line on LCD screen
				column_LCD++;
				LCD1602_SetCursor(charac,column_LCD);
			} else{ //Send the TWEET, cleaning the screen and resetting parameters
				column_LCD--;
				UART_Println(lcd_text,32);
				LCD1602_ClearAll();
			}
		}
	}
}
