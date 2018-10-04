#define F_CPU 4912500 /*4912500UL*/
#define BAUD 9600
#define UBRREG F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include "setup.h"
#include "ADC.h"
#include "UART.h"
#include "Joystick.h"
#include "oled.h"
#include "sram.h"
#include "menu.h"

int main(void)
{
	
	
	
	struct screen *display_screen;
	char *prev_screen = " ";
	char *joy_direction = " ";
	//CAN_message_t can_msg_send;
	//CAN_message_t can_msg_receive;
	joy_position joy_pos;
	slider_position slider_pos;
	int8_t score = 0;
	uint8_t lives = 3;
	int button_pressed = 0;
	int prev_button = 0;
	//joy_position joy_pos;
	//slider_position slider_pos;
	//int left_b;
	//int right_b;
	UART_Init(UBRREG);
	ADC_init();
	joy_init();
	SRAM_init();
	OLED_init();
	init_menu();
	JOY_calibrate();
	
	
	
	

	
	printf("----TING FUNK----\n\r");

	if (joy_init() == 0) {
		printf("----Joystick working----\n\r");
		} else {
		printf("----Joystick error!!----\n\r");
	}
	OLED_clear();
	OLED_pos(1, 5);
	OLED_print("Ping Pong");
	OLED_pos(2, 5);
	OLED_print("Ping Pong");
	OLED_pos(3, 4);
	OLED_print("Press Button");
	OLED_pos(4, 5);
	OLED_print("to start");
	
	while(1){
	joy_pos = JOY_getDirection();

	init_menu();
	printf("Hoyre knapp: %d, ", joy_button(0));
	printf("Venstre knapp: %d, ", joy_button(1));
	printf("x: %d ,",ADC_read(1));
	printf("y: %d ,",ADC_read(0));
	printf("Retning: %s\n\r",joy_pos.direction);



//------------Menu------------//
	init_menu();

	}

	return 0;
}
/*
void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) 
		{
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase \n \n", write_errors, retrieval_errors);
}
*/