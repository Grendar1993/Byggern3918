/*
 * adc.c
 *
 * Created: 08.11.2018 15.28.38
 *  Author: Max-Pc
 */ 

#include "adc.h"

void ADC_init( void )
{
	// Enable ADC and set prescaler to 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA &= ~(1<<ADIF);
	ADCSRA &= ~(1<<ADIE);
	//ADCSRB &= ~(1 << MUX0); 
	// Reference selection: AVCC w/ external capacitor at AREF. Left adjust result
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	printf("adc value is %d \n\r", ADCH);
}

uint8_t ADC_read( void )
{
	
	
	
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait until conversion is complete
	while(ADCSRA & (1 << ADSC));
	
	// Read converted data
	printf("adc value is %d \n\r", ADCH);
	return ADCH;
}