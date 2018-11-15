/*
 * can.c
 *
 * Created: 04.10.2018 17.30.43
 *  Author: Max-Pc
 */ 

#include "can.h"
#include "MCP2515.h"
#include "UART.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
//#include <util/delay.h>
#include "setup.h"

enum interrupt_flags interrupt_flag = no_flag;



uint8_t rx_flag = 0;

int CAN_init(void) {
	//Enter config mode
	MCP_init();
	
	//RX0 - Turn masks/filters off, rollover disabled?
	MCP_bit_modify(MCP_RXB0CTRL, MCP_FILTER_OFF, 0b01101000);
	//Enable interrupt when message is received (RX0IE = 1)
	MCP_bit_modify(MCP_CANINTE, MCP_RX_INT, 0x01);
	
	//Enable normal mode
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	
	uint8_t value = MCP_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_NORMAL){
		printf("ERROR..ERROR...LOOPBACK NOT WORKING");
		return 1;
	}
	
	

	return 0;
}

int CAN_message_send(can_msg* message) {
	uint8_t i;
	
	//Check if there is no pending transmission
	if (CAN_transmit_complete()) {
		
		//Set the message id (use standard identifier)
		MCP_write(MCP_TXB0SIDH, (int8_t)(message->id >> 3));
		MCP_write(MCP_TXB0SIDL, (int8_t)(message->id << 5));
		MCP_write(MCP_TXB0EID8, 0);
		MCP_write(MCP_TXB0EID0, 0);
		
		//Set data length and use data frame (RTR = 0)
		MCP_write(MCP_TXB0DLC, message->length);

		//Set data bytes (max. 8 bytes)
		for (i = 0; i < message->length; i++) {
			MCP_write(MCP_TXB0D0 + i, message->data[i]);
		}
		
		//Request to send via TX0
		MCP_request_to_send(MCP_RTS_TX0);
		
		} else {
		if (CAN_error() < 0) {
			return -1;
		}
	}
	
	return 0;
}

int CAN_error(void) {
	uint8_t error = MCP_read(MCP_TXB0CTRL);
	
	//Transmission error detected
	if (test_bit(error, 4)) return -1;
	
	//Message lost arbitration
	if (test_bit(error, 5)) return -2;
	
	return 0;
}


int CAN_transmit_complete(void) {
	//Check if TX buffer is not pending transmission (TXREQ = 0)
	if (test_bit(MCP_read(MCP_TXB0CTRL), 3)) {
		return 0;
		} else {
		return 1;
	}
}

 int CAN_int_vect(void) {
 	//Clear interrupt flag
  	MCP_bit_modify(MCP_CANINTF, MCP_RXF0SIDL, MCP_RXF0SIDH);
  	rx_flag = 1;
 	return 0;
 }



can_msg CAN_data_receive(void) {
	printf("asdfassdf\n\r");
	uint8_t i;
	can_msg message = {0};
	
	//Check if RX buffer has a message
	if (rx_flag == 1) {
		
		//Get message id
		message.id  = (MCP_read(MCP_RXB0SIDH) << 3) | (MCP_read(MCP_RXB0SIDL) >> 5);
		
		//Get message length
		//message.length = (MCP_CANCTRL) & (MCP_read(MCP_RXB0DLC));
		message.length = (MCP_read(MCP_RXB0CTRL+5) & 0x0F);
		printf("len %d\n\r", message.length);
		
		//Get message data
		for(i = 0; i < message.length; i++) {
			message.data[i] = MCP_read(MCP_RXB0D0 + i);
		}
		
		//Clear interrupt flag
		rx_flag = 0;
	}
		//} else {
		//Message not received
		//message.id = -1;
	//}
	
	return message;
}

//Interrupt service routine for CAN bus
ISR(INT0_vect) {
//	_delay_ms(10);
	CAN_int_vect();
// printf("ghjkhk\r\n");
// 	uint8_t interrupt = MCP_read(MCP_CANINTF);
// 
// 	if (interrupt & MCP_RX0IF){
// 		rx_flag = 1;
// 		//clear CANINTF.RX0IF
// 		MCP_bit_modify(MCP_CANINTF, 0x01, 0x00);
// 	}
// 	else if (interrupt & MCP_RX1IF){
// 		rx_flag = 1;
// 		// clear CANINTF.RX1IF
// 		MCP_bit_modify(MCP_CANINTF, 0x02, 0x00);
// 	}
}

