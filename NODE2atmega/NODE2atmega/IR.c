/*
 * IR.c
 *
 * Created: 08.11.2018 16.16.36
 *  Author: Max-Pc
 */ 


#include "ir.h"
#include "adc.h"

uint8_t IR_read( void )
{
	static uint8_t values[4];
	int avg = 0;
	
	values[0] = ADC_read();
	for (int i = 3; i >= 0; i--){
		avg = avg + values[i];
		if (i != 0){
			values[i] = values[i - 1];
		}
	}
	avg = avg / 4;
	return avg;
}