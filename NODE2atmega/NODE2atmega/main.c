	
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
	
	int8_t x, y;
	uint8_t i=0;
	int ir_val;
	int prev_ir_val = 0;
	double slider_left;
	uint8_t ref_update;
	double skaler = 2.55;

    int main(void){
		
		cli();
		
		DDRF &= ~(1 << PINF0); //Set F0(ADC0) as input
		
		EICRA |= (0 << ISC21) | (0 << ISC20);
		// Enable external interrupts of INT2
		EIMSK |= (1 << INT2);
		
		//TIMSK1|= (1 << TOIE1);
		
		DDRD &= ~(1 << PIND2);		//Set D2(INT2) as input
		
		//int variabel = 1;
		
		can_msg can_msg_send;
		volatile can_msg can_msg_receive;
		
		UART_Init(UBRREG);
 		SPI_init();
 		MCP_init();
		ADC_init();

		if (CAN_init() == 0) {
			printf("CAN BE WORKING\n\r");
			can_msg_send.id = 2;
			can_msg_send.length = 8;
			} else {
			printf("CAN NOT BE WORKING \n\r");
		}
		printf("Kommer den hit? \n\r");
		
		DAC_init();
		motor_init();
		_delay_ms(150);
		motor_read_rotation(1);
		PID_init();
		printf("init done\n\r");
		sei();

	while(1){
//<<<<<<< HEAD
			
		ir_val = IR_read();
/*		printf("ting er av verdi %d\n\r",ir_val);*/
		if (ir_val - prev_ir_val != 0){
			if (ir_val <= 3){
				printf("Lives have been reduced\n\r");
				while (ir_val<6)
				{
					_delay_ms(10);
					ir_val= IR_read();
				}
			}
			prev_ir_val = ir_val;
		}
		
		  //  }
			
//=======
		_delay_ms(10);
		printf("can receive \n\r");
 	can_msg_receive = CAN_data_receive();
 	slider_left = can_msg_receive.data[1];
 	x=can_msg_receive.data[1];
 //	y=can_msg_receive.data[1];
 //	printf("loopyloop %d \n\r",slider_left);
 	_delay_ms(500);
	 printf("slider_left: %d \n\r",ref_update);
	 ref_update = slider_left * skaler;
	 update_ref(150);
	 _delay_ms(500);
	 update_ref(50);
	
	
	

// 		ir_val = IR_read();
// 		//printf("ting er av verdi %d\n\r",ir_val);
// 		if (ir_val - prev_ir_val != 0){
// 			if (ir_val == 0){
// 				printf("Lives have been reduced\n\r");
// 			}
// 			prev_ir_val = ir_val;
// 			printf("lives have not been reduced\n\r");
// 		}
// 
 		    }
//>>>>>>> 343998c6d105f4320b87ef8e886a5445cb60bd37

}





// 			printf("loopyloop \n\r");
//  			can_msg_send.data[0] = 0x10;
// 			i=i+1;
// 			if (i>0xFF)
// 			{
// 				i=0;
// 			}
// 			can_msg_send.data[1] = i;
//
// 			CAN_message_send(&can_msg_send);
// 			_delay_ms(100);
// 			can_msg_receive = CAN_data_receive();
// 			x=can_msg_receive.data[0];
// 			y=can_msg_receive.data[1];
//
//
// 			can_msg_receive = CAN_data_receive();
// 			x=can_msg_receive.data[0];
// 			y=can_msg_receive.data[1];
// 			printf("y1 er %d \n\r",x);
// 			printf("y2 er %d \n\r",y);
// 			_delay_ms(550);
