/*
 * can.h
 *
 * Created: 04.10.2018 17.31.03
 *  Author: Max-Pc
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <avr/io.h>
 /*
 Structure that makes it easier to construct a message to be send in CAN,
 contains id, length and the data to be send in the message, can contain at most 8 byte data.
 */
typedef struct can_msg{
	unsigned int id;
	uint8_t length;		// max 8
	uint8_t data[8];
}can_msg;


int CAN_init(void);
int CAN_message_send(can_msg* message);
int CAN_error(void);
int CAN_transmit_complete(void);
int CAN_int_vect(void);
can_msg CAN_data_receive(void);

#endif /* CAN_H_ */