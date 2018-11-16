/*
 * game.c
 *
 * Created: 16.11.2018 09:33:30
 *  Author: Grend
 */ 

	#ifndef F_CPU	
	#define F_CPU 16000000UL
	#endif
	//inkluder drivere
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
   
   //definere ulike variabler
   	int8_t x, y;
   	uint8_t i=0;
   	int16_t slider_left=0;
   	int16_t ref_update;
   	double skaler = 2.55;
   	int16_t prev_ref_update;
   	int8_t shoot;
	can_msg can_msg_send;
	volatile can_msg can_msg_receive;
	int diff;
	int prev_diff;
	
   

void start_spill(){
		_delay_ms(50);
// 		can_msg_receive = CAN_data_receive();
// 		x			= can_msg_receive.data[0];
// 		slider_left = can_msg_receive.data[1];
// 		shoot		= can_msg_receive.data[2];
// 		diff		= can_msg_receive.data[3];
// 		
		if(diff!=prev_diff){
			if(diff==1){
				PID_diff(EASY);}
			else if(diff==2){
				PID_diff(MEDIUM);}
			else if(diff==3){
				PID_diff(HARD);}
			}
		
	//	can_msg_send.data[0] = Lives_lost();
		printf("Liv: %d \r\n",Lives_lost());
	//	CAN_message_send(&can_msg_send);
				
				
		
		//printf("slider_left: %d \n\r",slider_left);
		ref_update = slider_left*skaler;
		update_ref(ref_update);
		set_servo(x);
		
	//	printf("Shoot: %d \r\n",slider_left);
		sol_shoot(shoot);

		prev_diff=diff;
}