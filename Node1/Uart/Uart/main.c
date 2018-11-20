#define F_CPU 4912500 /*4912500UL*/
#define BAUD 9600
#define UBRREG F_CPU/16/BAUD-1

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
#include "menu.h"
#include "MCP2515.h"
#include "spi.h"
#include "can.h"

can_msg can_msg_send;
can_msg can_msg_receive;

joy_position joy_pos;
slider_position slider_pos;

struct screen *display_screen;
char *prev_screen = " ";
char *joy_direction = " ";

uint8_t lives = 3;
uint8_t menuactive = 1;
uint8_t diff = 1;
uint8_t music;

extern int 



















gamestep = 1;
extern int hp = 3;
extern int menynummer = 0;
int button_pressed = 0;
int prev_button = 0;
int score;
int x, y;
	
int main(void)
{
	cli();
	
	GICR  |= (1 << INT0);						//Enable INT0
	MCUCR |= (0 << ISC01) | (0 << ISC00);		//On falling edge
	DDRD &= ~(1 << PIND2);						//Set D2(INT0) as input
	
	UART_Init(UBRREG);
	ADC_init();
	SPI_init();
	MCP_init();
	joy_init();
	SRAM_init();
	OLED_init();;
	JOY_calibrate();
	
	if (CAN_init() == 0) {
		printf("CAN initiated \n\r");
		can_msg_send.id = 2;
		can_msg_send.length = 7;
		} else {
		printf("CAN not initiated properly \n\r");
	}

	if (joy_init() == 0) {
		printf(" Joystick initiated \n\r");
		} else {
		printf(" Joystick not initiated properly\n\r");
	}
	
	sei();
	
	while(1){
			joy_pos = JOY_getDirection();
			slider_pos = JOY_getSliderPosition();
		if (menuactive == 1){
			gamestep = init_menu();
			can_msg_send.data[4] = 0;
			CAN_message_send(&can_msg_send);
		}
		if (menuactive == 2){
			can_msg_send.data[3] = diff;
			can_msg_send.data[4] = 1;
			CAN_message_send(&can_msg_send);
			_delay_ms(50);
			score = OLED_game(diff);
			gamestep = 1;
		}
	}
	return 0;
}