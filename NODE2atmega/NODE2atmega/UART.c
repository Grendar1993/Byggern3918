#include <avr/io.h>
#include <stdio.h>
#include "UART.h"


void UART_Init(unsigned int ubrr)
{
	// Baud rate
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)(ubrr);
	
	// Enable Rx and Tx
	
	UCSR0B = (1 << RXEN0 ) | (1 << TXEN0);
	UCSR0C = (1 << USBS0);
	UCSR0C = (3 << UCSZ00);
	
	

	
	fdevopen(UART_TX, UART_RX);
}

int UART_TX(char data, FILE * _in){
	(void)(_in);
	
	while( !(UCSR0A & (1 << UDRE0)) );
	
	// send data
	UDR0 = data;
	
	return 0;
}

int UART_RX(FILE * _in ){
	(void)(_in);
	while( !(UCSR0A & (1 << RXC0)) );
	
	// Data recieved
	return UDR0;
}