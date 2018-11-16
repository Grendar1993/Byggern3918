/*
 * ADC.c
 *
 * Created: 20.09.2018 16.44.27
 *  Author: Max-Pc
 */ 

/*
This driver sets up the ADC,
and lets you chose between reading channel 1-4.
*/

#include <avr/io.h>
#include <stdio.h>
#include "setup.h"
#include <util/delay.h>

int ADC_init(void) {
	//Enable the external memory interface/4 bits address, page 26-35 in Atmega162 data sheet
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	//Set the interrupt pin to input, INT0, PD2
	DDRB &= ~(1<<PIND2);
	
	return 0;
}

uint8_t ADC_read(uint8_t channel) {
	//Address for the ADC, used as chip select
	volatile char *adc = (char *) 0x1400;
	
	//checks if the channel is valid, we can only use channel 1-4.
	if(channel > 3) {return 0;}
	
	//Choose channel in ADC, lets us chose what device we want to read
	*adc = 0x04 | channel;

	//delay to let the adc finish its conversion
	_delay_us(100);
	return *adc;
}