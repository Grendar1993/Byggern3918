/*
 * ADC.c
 *
 * Created: 20.09.2018 16.44.27
 *  Author: Max-Pc
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "setup.h"
#include <util/delay.h>

int ADC_init(void) {
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	//Set the interrupt pin to input
	//DDRB &= ~(1<<PIND2);
	
	return 0;
}

uint8_t ADC_read(uint8_t channel) {
	//Address for the ADC
	volatile char *adc = (char *) 0x1400;
	
	if(channel > 3) {return 0;}
	
	//Choose channel in ADC
	*adc = 0x04 | channel;
	
	//Wait for the data to be read (this can be done with an interrupt)
	//while(test_bit(PIND, PIND2));
	_delay_us(100);
	return *adc;
}