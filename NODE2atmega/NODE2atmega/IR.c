/*
 * IR.c
 *
 * Created: 08.11.2018 16.16.36
 *  Author: Max-Pc
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "ir.h"
#include "adc.h"
#include <util/delay.h>

int ir_val;
int prev_ir_val = 0;
int life=0;

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
	//printf("dfad %d \n\r",avg);
	return avg;
}


uint8_t Lives_lost(void){
	 		ir_val = IR_read();
	 		printf("ting er av verdi %d\n\r",ir_val);
	 		if (ir_val - prev_ir_val != 0){
	 			if (ir_val <= 3){
					 // mister liv
					 life=1;
	 				while (ir_val<6)
	 				{
	 					_delay_ms(10);
	 					ir_val= IR_read();
	 				}
	 			}
	 			prev_ir_val = ir_val;
			}
	return life;	
}