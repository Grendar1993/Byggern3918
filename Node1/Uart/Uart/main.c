/*
 * Uart.c
 *
 * Created: 04.09.2018 09.43.47
 * Author : Grendar
 */ 

#define F_CPU 4912500 /*4912500UL*/
#define BAUD 9600
#define UBRREG F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "setup.h"
#include "ADC.h"
#include "UART.h"
#include "Joystick.h"
#include "oled.h"
#include "sram.h"

int main(void)
{
// 	joy_position joy_pos;
// 	slider_position slider_pos;
// 	int left_b;
// 	int right_b;
	UART_Init(UBRREG);
	ADC_init();
	joy_init();
	OLED_init();
	SRAM_init();
	printf("----TING FUNK----\n\r");
	
	// OLED Init
	OLED_init();
	OLED_sram_clear();
	OLED_sram_draw_mario();
	OLED_pos(1, 5);
	OLED_sram_print("Ping Pong");
	OLED_pos(3, 4);
	OLED_sram_print("Press Button");
	OLED_pos(4, 5);
	OLED_sram_print("to start");
	
	//Set the GAL control pins as outputs
// 	MCUCR &= (0<<SRE);
// 	SFIOR &= (0<<XMM2);
// 	DDRC |= 0b00000101;
// 	PORTC = 0b00000000;
		
	//SRAM_test();
		
// 	for (int i = 0; i < 8; i++){
// 		OLED_clear_line(i);
// 		printf("Clearing line %d \n \r", i);
// 	}
// 	while(1){}
		
		
// 	joy_pos = JOY_getDirection();
// 	slider_pos = JOY_getSliderPosition();
// 	left_b = joy_button(1);
// 	right_b = joy_button(2);
// 	
// 	printf("Right button: %d, Left button: %d, Right Slider: %d, Left Slider: %d, Joy-pos: %s \n \r \n \r", right_b, left_b, slider_pos.right, slider_pos.left, joy_pos.direction);
//  	_delay_ms(200);
// 		

	return 0;
}
/*
void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size =x| 0x800;
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