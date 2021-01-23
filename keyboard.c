/*-----------------------------------------------------------------------------
* Name: keyboard.c
* PROJECT: TEXT EDITOR for FRDM-KL05Z board using 4x4 keyboard and LCD
* Author: Gregório da Luz
*----------------------------------------------------------------------------*/

#include "MKL05Z4.h" 
#include "keyboard.h"
#include "lcd1602.h"

//PORT A INPUT
#define R1 12   
#define R2 7		
#define R3 11		
#define R4 6		

//PORT B OUTPUT
#define C1 0
#define C2 7 
#define C3 6
#define C4 11

#define MASK_PULLUP (1UL << 0 | 1UL << 1)

void delay_Us(int n){
volatile int i;
volatile int j;
for( i = 0 ; i < n; i++)
for(j = 0; j < 5; j++) {}
}

void delay_ms(int n){
volatile int p;
volatile int f;
for( f = 0 ; f < n; f++)
for(p = 0; p < 2300; p++) {}
}

void keyboardInitialize(void){
SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
PORTA->PCR[R1] |= PORT_PCR_MUX(1)|MASK_PULLUP; 
PORTA->PCR[R2] |= PORT_PCR_MUX(1)|MASK_PULLUP;   
PORTA->PCR[R3] |= PORT_PCR_MUX(1)|MASK_PULLUP;
PORTA->PCR[R4] |= PORT_PCR_MUX(1)|MASK_PULLUP; 
	
PORTB->PCR[C1] |= PORT_PCR_MUX(1);
PORTB->PCR[C2] |= PORT_PCR_MUX(1);	
PORTB->PCR[C3] |= PORT_PCR_MUX(1);
PORTB->PCR[C4] |= PORT_PCR_MUX(1);	
}

char keypad_getkey(void){
	int col, row;
	const char col_select[]={0x01, 0x80, 0x40, 0x20}; // C1,C2,C3,C4 PORTB

	/* SETTING OUTPUTS FOR 0 on the columns */
	PTB->PDDR |= (1<<C1|1<<C2|1<<C3|1<<C4);
	PTB->PCOR = (1<<C1|1<<C2|1<<C3|1<<C4);
	delay_Us(2);	//safety
	
	row = PTA->PDIR & 0X18C0; //read rows
	
	PTB->PDDR = 0; //disable columns
	
	if(row == 0x18C0) return 0; //no zero on the rows so no key pressed
	
	for(col=0;col<4;col++){							//if a key is pressed, we move on
		PTB->PDDR = 0; 										//disable columns
		PTB->PDDR |= col_select[col]; 		//enable one column
		PTB->PCOR = col_select[col];
		delay_Us(2);
		row = PTA->PDIR & 0X18C0;
		if(row != 0x18C0) break;
	}
	PTB->PDDR = 0; //disable columns
	
	if(col == 4) return 0; // in this case, no key pressed
	
	if(row == 0x8C0)  return col*4+1; //row 1  ( row = 0x18C0 - value of the pressed button) value of the rows can be read at beginning of the file
	if(row == 0x1840) return col*4+2; //row 2
	if(row == 0x10C0) return col*4+3; //row 3
	if(row == 0x1880) return col*4+4; //row 1
	
	return 0; //safety
}

char pressed_key(char button, uint8_t group){
	char temp;
	if(group == 0){
		switch(button) {
			case 4:
				temp = LCD1602_Print("1");
				break;
			case 3:
				temp = LCD1602_Print("2");
				break;
			case 2:
				temp = LCD1602_Print("3");
				break;
			case 8:
				temp = LCD1602_Print("4");
				break; 	
			case 7:
				temp = LCD1602_Print("5");
				break;
			case 6:
				temp = LCD1602_Print("6");
				break; 	
			case 12:
				temp = LCD1602_Print("7");
				break;
			case 11:
				temp = LCD1602_Print("8");
				break; 	
			case 10:
				temp = LCD1602_Print("9");
				break; 	
			case 9:
				temp = LCD1602_Print("0");
				break; 	
		}
	}
	if(group == 1){
		switch(button) {
			case 4:
				temp = LCD1602_Print("a");
				break;
			case 3:
				temp = LCD1602_Print("d");
				break;
			case 2:
				temp = LCD1602_Print("g");
				break;
			case 8:
				temp = LCD1602_Print("j");
				break; 	
			case 7:
				temp = LCD1602_Print("m");
				break;
			case 6:
				temp = LCD1602_Print("p");
				break; 	
			case 12:
				temp = LCD1602_Print("s");
				break;
			case 11:
				temp = LCD1602_Print("v");
				break; 	
			case 10:
				temp = LCD1602_Print("y");
				break;
			case 9:
				temp = LCD1602_Print("?");
				break; 			
		}
	}
	if(group == 2){
		switch(button) {
			case 4:
				temp = LCD1602_Print("b");
				break;
			case 3:
				temp = LCD1602_Print("e");
				break;
			case 2:
				temp = LCD1602_Print("h");
				break;
			case 8:
				temp = LCD1602_Print("k");
				break; 	
			case 7:
				temp = LCD1602_Print("n");
				break;
			case 6:
				temp = LCD1602_Print("q");
				break; 	
			case 12:
				temp = LCD1602_Print("t");
				break;
			case 11:
				temp = LCD1602_Print("w");
				break; 	
			case 10:
				temp = LCD1602_Print("z");
				break; 
			case 9:
				temp = LCD1602_Print(" ");
				break; 			
		}
	}
	if(group == 3){
		switch(button) {
			case 4:
				temp = LCD1602_Print("c");
				break;
			case 3:
				temp = LCD1602_Print("f");
				break;
			case 2:
				temp = LCD1602_Print("i");
				break;
			case 8:
				temp = LCD1602_Print("l");
				break; 	
			case 7:
				temp = LCD1602_Print("o");
				break;
			case 6:
				temp = LCD1602_Print("r");
				break; 	
			case 12:
				temp = LCD1602_Print("u");
				break;
			case 11:
				temp = LCD1602_Print("x");
				break; 	
			case 10:
				temp = LCD1602_Print(".");
				break; 
			case 9:
				temp = LCD1602_Print("!");
				break; 			
		}
	}
	return temp;
}



