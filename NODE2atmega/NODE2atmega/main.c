	
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
	
	int8_t x, y;
	uint8_t i=0;
	

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
			can_msg_send.id = 2;
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
			
			CAN_message_send(&can_msg_send);
			_delay_ms(100);
			can_msg_receive = CAN_data_receive();
			x=can_msg_receive.data[0];
			y=can_msg_receive.data[1];
	
			
			can_msg_receive = CAN_data_receive();
			x=can_msg_receive.data[0];
			y=can_msg_receive.data[1];
			printf("y1 er %d \n\r",x);
			printf("y2 er %d \n\r",y);
			_delay_ms(550);			
		    }

}