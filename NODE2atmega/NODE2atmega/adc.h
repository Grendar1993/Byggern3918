/*
 * adc.h
 *
 * Created: 08.11.2018 15.28.54
 *  Author: Max-Pc
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_init( void );
uint8_t ADC_read( void );



#endif /* ADC_H_ */