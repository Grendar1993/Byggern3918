#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "font_8x8.h"
#include "oled.h"
#include "sram.h"
#include "can.h"
#include "joystick.h"
#include <util/delay.h>
#include "setup.h"

/*
Driver that makes it possible to use the OLED on the Multifunction-card, to represent data,
use a menu to change the settings of the game, and other useful things.
*/


//Address for the OLED commands
volatile char *OLED_cmd = (char *) 0x1000;
//Address for the OLED data
volatile char *OLED_data = (char *) 0x1200;

uint8_t page, col;
can_msg can_msg_send;
can_msg can_msg_receive;
char buffer[8];
extern menuactive;
extern hp;
extern menynummer;

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

int OLED_nameprompt(void){			// Prompt the user for their name (four letters) after reaching a score larger then third highest score
	OLED_clear();
	OLED_pos(2,1);
	OLED_print("New Highscore!");
	OLED_pos(3,3);
	OLED_print("Type name:");
	OLED_pos(6,6);
	OLED_print("^^^^");
	char* characterstring[25] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	char* endstr[4] = {".", ".", ".", "."};
	int positions[4];
	int stopflag = 0;
	joy_position joy_pos;
	slider_position slider_pos;
	for (int i = 0; i < 4; i++){					// Repeat four times, once for each character in the name
		for (int j = 0; j < 30;){					// Search "characterstring" by moving the joystick up and down, incrementing the position in the string and printing 
			OLED_clear_line(5);						// the corresponding letter on the screen
			for (int k = 0; k < i; k++){			// Print the previously chosen letters in front of the current letter we are choosing 
				OLED_pos(5,6+k);
				OLED_print(endstr[k]);
			}
			OLED_pos(5,6+i);
			OLED_print(characterstring[j]);
			joy_pos = JOY_getDirection();
			_delay_ms(700);
			if (joy_pos.dir == 1){					// Increment array when moving the joystick up
				j = j + 1;
			}
			else if (joy_pos.dir == 2){				// Decrement array when moving the joystick down 
				j = j - 1;
			}
			if (j > 25){							// Make the array cyclic. Moving further then the last letter we return to the first letter.
				j = 0;
			}
			else if (j < 0){						// Moving lower then the first letter we move to the last letter in the array. 
				j = 25;
			}
			else if (joy_pos.sidedir == 1){			// "Select" character by moving our joystick to the right, breaking the for-loop and move to choosing the next character
				positions[i] = j;
				endstr[i] = characterstring[positions[i]];
				break;
			}
			else if (joy_button(1) == 0){			// Exit the function when done selecting name by pressing the button. 
				stopflag = 1;
				positions[i] = j;
				endstr[i] = characterstring[positions[i]];
				break;
			}
		}
		if (stopflag == 1){
			break;
		}
	}
	OLED_clear();
	OLED_pos(3,2);
	OLED_print("Well played,");
	OLED_pos(6,4);
	OLED_print("~");
	OLED_pos(6,6);
	for (int i = 0; i < 4; i++){
		OLED_print(endstr[i]);
	}
	OLED_pos(6,10);
	OLED_print("! ~");
	_delay_ms(6000);
	char** string = endstr;
	return string;
}

int OLED_game(int diff){	// Main function for the game
	extern int gamestep;
	extern int hp;
	int hp_lost;
	extern int score;
	int counter;
	joy_position position;
	slider_position slider_pos;

	while(gamestep == 1){      //Waiting for player to shoot the first time to initiate the game or to continue the game after loosing a health point
		position = JOY_getDirection();
		OLED_clear();
		OLED_pos(4,1);
		if (hp == 3){
			OLED_print("Shoot to start!");
			counter = 0;
			score = 0;
			hp_lost = 0;
		}
		else if (hp == 0){
			gamestep = 0; 
			menuactive = 1; 
			menynummer = 27; 
			break;
		}
		else{
			OLED_pos(3,0);
			OLED_print("You lost health.");
			OLED_pos(4,3);
			OLED_print("Shoot to");
			OLED_pos(5,3);
			OLED_print("continue!");
		}
		_delay_ms(400);
		if (joy_button(1) == 0){
			can_msg_send.data[2] = joy_button(1);
			CAN_message_send(&can_msg_send);
			gamestep = 2;
		}
	}
	while(gamestep == 2){	// Game started. Score-counting active. Will break when a health point is lost, returning to gamestep 1
		slider_pos = JOY_getSliderPosition();
		position = JOY_getDirection();
		can_msg_send.data[0] = position.x;
		can_msg_send.data[1] = slider_pos.left;
		can_msg_send.data[2] = joy_button(1);
		CAN_message_send(&can_msg_send);
  		can_msg_receive = CAN_data_receive();
  		hp_lost = can_msg_receive.data[5];
		if (!test_bit(PINB,PINB0)){
			hp_lost=1;
		}
		_delay_ms(150);
		printf("hp_lost: %d \n \r", hp_lost);
		if (hp_lost == 1){
			hp_lost = 0;
			hp = hp - 1;
			gamestep = 1;
			break;
		}
		counter = counter + 1;
		if (counter == 10){
			OLED_clear();
			OLED_pos(3,2);
			if (hp == 3){
				OLED_print("Health: }}} ");
			}
			else if(hp == 2){
				OLED_print("Health: }} ");
			}
			else if(hp == 1){
				OLED_print("Health: } ");
			}
			OLED_pos(5,3);
			OLED_print("Score: ");
			OLED_print(itoa(score, buffer, 10));
			score = score + 1;
			counter = 0;
		}
	}
return score;
}

void my_delay_ms(int n) {			// For increasing game difficulty by changing the break inbetween frames.
	while(n--) {
		_delay_ms(1);
	}
}