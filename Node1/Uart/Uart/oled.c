#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "font_8x8.h"
#include "oled.h"
#include "sram.h"

/*
Driver that makes it possible to use the OLED on the Multifunction-card, to represent data,
use a menu to change the settings of the game, and other useful things.
*/


//Address for the OLED commands
volatile char *OLED_cmd = (char *) 0x1000;
//Address for the OLED data
volatile char *OLED_data = (char *) 0x1200;

uint8_t page, col;


//function to set up the OLED
int OLED_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);

	//Setup the OLED display
	
	//display off
	*OLED_cmd = 0xAE;
	//segment remap
	*OLED_cmd = 0xA1;
	
	//common pads hardware: alternative
	*OLED_cmd = 0xDA;
	*OLED_cmd = 0x12;
	
	//common output scan direction:com63~com0
	*OLED_cmd = 0xC8;

	//multiplex ration mode:63
	*OLED_cmd = 0xA8;
	*OLED_cmd = 0x3F;

	//display divide ratio/osc. freq. mode
	*OLED_cmd = 0xD5;
	*OLED_cmd = 0x80;

	//contrast control
	*OLED_cmd = 0x81;
	*OLED_cmd = 0x50;

	//set pre-charge period
	*OLED_cmd = 0xD9;
	*OLED_cmd = 0x21;

	//set Memory Addressing Mode
	*OLED_cmd = 0x20;
	*OLED_cmd = 0x02;

	//VCOM deselect level mode
	*OLED_cmd = 0xDB;
	*OLED_cmd = 0x30;

	//master configuration
	*OLED_cmd = 0xAD;
	*OLED_cmd = 0x00;

	//out follows RAM content
	*OLED_cmd = 0xA4;

	//set normal display
	*OLED_cmd = 0xA6;
	//display on
	*OLED_cmd = 0xAF;
	
	//Set page start address
	*OLED_cmd = 0xB0;
	//Set lower column start address
	*OLED_cmd = 0x00;
	//Set higher column start address
	*OLED_cmd = 0x10;
	
	//Clear the display
	OLED_clear();
	OLED_home();

	return 0;
}

//function that returns the OLED to its start-state
int OLED_home(void) {
	//Reset the page and column
	page = 0;
	col = 0;
	*OLED_cmd =0xD3; 	
	 *OLED_cmd = 0b11001000;
	//Set the cursor to the start of the screen
	*OLED_cmd = 0x21;
	*OLED_cmd = 0x00;
	*OLED_cmd = 0x7f;
		
	*OLED_cmd = 0x22;
	*OLED_cmd = 0x00;
	*OLED_cmd = 0x7;
		
 	return 0;
 }
 
//function that lets us go to the specified line on the OLED 
int OLED_goto_line(uint8_t line) {
	OLED_home();
	
	//Check if it's a valid page
	if (line < 8) {
		//Save the page we are moving to
		page = line;
		//Set lower column address
		*OLED_cmd = 0x00;
		//Set higher column address
		*OLED_cmd = 0x10;
		//Set page address
		*OLED_cmd = 0xB0 | line;
	}
 
 	return 0;
 }

//function that lets us define a specific position on the OLED
int OLED_pos(uint8_t line, uint8_t column) {
	OLED_goto_line(line);
	
	//Check if it's a valid column according to the font
	if (column < (128/FONTWIDTH)) {
		//Save the column we are moving to
		col = column*FONTWIDTH;
		//Set lower column start address
		//*OLED_cmd = 0x00 + (column*(FONTWIDTH)<<4);
		//Set higher column start address
		*OLED_cmd = 0X0F & col;
		*OLED_cmd = 0x10 | (column*(FONTWIDTH)>>4);
	}
	
	return 0;
}


//function that clears a line
int OLED_clear_line(uint8_t line) {
	OLED_goto_line(line);
	
	//Clear the page
	for (int i = 0; i < 128; i++) {
		*OLED_data=0x00;
	}
	
	OLED_home();
	
	return 0;
}

//function that clears everything that is on the OLED
int OLED_clear(void) {
	//Clear every page
	for (int k = 0; k < 8; k++) {
		OLED_clear_line(k);
	}
	
	return 0;
}

// function that lets us print characters defined by the defined
int OLED_print_char(char c) {
	//Write the complete character
	for (int i = 0; i < FONTWIDTH; i++) {
		*OLED_data = pgm_read_byte(&font[c-' '][i]);
	}
	
	return 0;
}

//function that prints the startscreen of the OLED
// int OLED_print_startscr(int col) {  //fig = figurnummer, col = kolonnenummer (hvor p� skjermen skal figuren printes)
// 	//Write the complete figure
// 	for (int y = 0; y < 7; y++){
// 		OLED_pos(y, col);
// 		for (int i = 0; i < 128; i++) {
// 			*OLED_data = pgm_read_byte(&ntnu[y+1][i]);
// 		}
// 	}
// 	
// 	return 0;
// }

//writes a complete string, with the use of the print char function
int OLED_print(char *data) {
	int i = 0;
	
	//Write the complete string
	while(data[i] != '\0'){
		OLED_print_char(data[i]);
		i++;
	}
	
	return 0;
}
