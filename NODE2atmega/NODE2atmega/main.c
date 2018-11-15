	
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
	
	uint8_t x, y;
	uint8_t i=0;
<<<<<<< HEAD
	int ir_val;
	int prev_ir_val = 0;
	double slider_left;
	uint8_t ref_update;
	double skaler = 2.55;
=======
	
>>>>>>> 3103c84a9367bd6c29525ddfb1efe5607576c098

    int main(void){
		
		cli();
		
		
		
		EICRA |= (0 << ISC21) | (0 << ISC20);
		// Enable external interrupts of INT2
		EIMSK |= (1 << INT2);
		
		DDRD &= ~(1 << PIND2);		//Set D2(INT2) as input
		
		//int variabel = 1;
		
		can_msg can_msg_send;
		volatile can_msg can_msg_receive;
		
		UART_Init(UBRREG);
 		SPI_init();
 		MCP_init();

		if (CAN_init() == 0) {
			printf("CAN BE WORKING\n\r");
			can_msg_send.id = 1;
			can_msg_send.length = 8;
			} else {
			printf("CAN NOT BE WORKING \n\r");
		}

		sei();

	while(1){

			printf("loopyloop \n\r");
 			can_msg_send.data[0] = 0x10;
			i=i+1;
			if (i>0xFF)
			{
				i=0;
			}
			can_msg_send.data[1] = i;
			
<<<<<<< HEAD
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
	
=======
			CAN_message_send(&can_msg_send);
			_delay_ms(100);
			can_msg_receive = CAN_data_receive();
			x=can_msg_receive.data[0];
			y=can_msg_receive.data[1];
>>>>>>> 3103c84a9367bd6c29525ddfb1efe5607576c098
	
			
			can_msg_receive = CAN_data_receive();
			x=can_msg_receive.data[0];
			y=can_msg_receive.data[1];
			printf("y1 er %02x \n\r",x);
			printf("y2 er %02x \n\r",y);
			_delay_ms(550);			
		    }

}