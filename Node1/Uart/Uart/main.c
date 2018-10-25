/*
 * Uart.c
 *
 * Created: 04.09.2018 09.43.47
 * Author : Grendar
 */ 


#define F_CPU 4912500 /*4912500UL*/
#define BAUD 9600
#define UBRREG F_CPU/16/BAUD-1




int x, y;


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include "setup.h"
#include "ADC.h"
#include "UART.h"
#include "Joystick.h"
#include "oled.h"
#include "sram.h"
//#include "menu.h"
#include "MCP2515.h"
#include "spi.h"
#include "can.h"

int main(void)
{
	
	cli();
	
	//DDRD |= (1 << PIND5);		//Set D5(OC1A) as output
	
	
	
	GICR  |= (1 << INT0);		//Enable INT0
	MCUCR |= (0 << ISC01) | (0 << ISC00);	//On falling edge
	
	
	DDRD &= ~(1 << PIND2);		//Set D2(INT0) as input
	
	can_msg can_msg_send;
	can_msg can_msg_receive;
	
	UART_Init(UBRREG);
	ADC_init();
	SPI_init();
	MCP_init();
	joy_init();
	SRAM_init();
	//OLED_init();
	//init_menu();
	JOY_calibrate();
	
	if (CAN_init() == 0) {
		printf("CAN BE WORKING\n\r");
		can_msg_send.id = 1;
		can_msg_send.length = 8;
		} else {
		printf("CAN NOT BE WORKING \n\r");
	}
	
	
	
	//SRAM_test();
	
	
	struct screen *display_screen;
	char *prev_screen = " ";
	char *joy_direction = " ";
	
	joy_position joy_pos;
	slider_position slider_pos;
	int8_t score = 0;
	uint8_t lives = 3;
	int button_pressed = 0;
	int prev_button = 0;
	uint8_t i=0;
	
	
	

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
	
	printf("----TING FUNK----\n\r");
	
	sei();
	
	while(1){
	joy_pos = JOY_getDirection();

	//init_menu();
	printf("Hoyre knapp: %d, ", joy_button(0));
	printf("Venstre knapp: %d, ", joy_button(1));
	printf("x: %d ,",ADC_read(1));
	printf("y: %d ,",ADC_read(0));
	printf("Retning: %s\n\r",joy_pos.direction);
	
	//can_msg_send.data[0] = joy_pos.x;
	//can_msg_send.data[1] = joy_pos.y;
	
 			can_msg_send.data[0] = 0x10;
 			i=i+1;
 			if (i>0xFF)
 			{
 				i=0;
 			}
 			can_msg_send.data[1] = i;
	
	CAN_message_send(&can_msg_send);
// 	can_msg_receive = CAN_data_receive();
// 	x=can_msg_receive.data[0];
// 	y=can_msg_receive.data[1];
//  	printf("y1 er %02x \n\r",x);
// 	printf("y2 er %02x \n\r",y);
	_delay_ms(250);




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