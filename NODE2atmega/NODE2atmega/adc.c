/*
 * adc.c
 *
 * Created: 08.11.2018 15.28.38
 *  Author: Max-Pc
 */ 

#include "adc.h"

/*
This driver enables the use of the ADC for node 2
*/


//This function sets up the ADC for use
void ADC_init( void )
{
	// Enable ADC and set prescaler to 128
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA &= ~(1<<ADIF);
	ADCSRA &= ~(1<<ADIE);
	
	// Reference selection, internal Vref
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
}


//function that starts the ADC conversion
uint8_t ADC_read( void )
{
		
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait until conversion is complete
	while(ADCSRA & (1 << ADSC));
	
	// Read converted data
	return ADCH;
}