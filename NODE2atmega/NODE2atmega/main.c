	
	#define F_CPU 16000000
	#define BAUD 9600
	#define UBRREG F_CPU/16/BAUD-1
  
    #include <stdio.h>
	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdlib.h>
	#include <string.h>
	#include <avr/interrupt.h>
	#include <avr/sfr_defs.h>
	#include "setup.h"
	#include "UART.h"
	#include "MCP2515.h"
	#include "spi.h"
	#include "can.h"
	#include "TIMER.h"
	#include "adc.h"
	#include "IR.h"
	#include "MOTOR_driver.h"
	#include "DAC_driver.h"
	#include "Motor_controller.h"
	#include "math.h"
	#include "Servo_driver.h"
	#include "sol_driver.h"
	#include "game.h"
	
// 	int8_t x, y;
// 	uint8_t i=0;
// 	int16_t slider_left=0; 
// 	int16_t ref_update;
// 	double skaler = 2.55;
// 	int16_t prev_ref_update;
// 	int shoot;
// 	int prev_shoot;

    int main(void){
		
		cli();
		
		DDRF &= ~(1 << PINF0); //Set F0(ADC0) as input
		
		EICRA |= (0 << ISC21) | (0 << ISC20);
		EIMSK |= (1 << INT2);
		
		DDRD &= ~(1 << PIND2);		//Set D2(INT2) as input
 		can_msg can_msg_send;
 		volatile can_msg can_msg_receive;
		
		UART_Init(UBRREG);
 		SPI_init();
 		MCP_init();
		ADC_init();
		servo_init(F_CPU);
		sol_init();
		if (CAN_init() == 0) {
			printf("CAN BE WORKING\n\r");
			can_msg_send.id = 2;
			can_msg_send.length = 7;
			} else {
			printf("CAN NOT BE WORKING \n\r");
		}		
		DAC_init();
		motor_init();
		_delay_ms(150);
		motor_read_rotation(1);
		PID_init();
		printf("|------NODE-2 INIT COMPLETE--------|\n\r");
		sei();
		
	while(1){
		
	start_spill();
	
		}
	}