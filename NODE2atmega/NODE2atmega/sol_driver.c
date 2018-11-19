/*
 * sol_driver.c
 *
 * Created: 16.11.2018 08:41:05
 *  Author: Grend
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include "setup.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

int8_t prev_shoot = 1;

void sol_init(){
		// Set pin 12 to output
		set_bit(DDRB, PB6);
		set_bit(PORTB, PB6);
}

void sol_shoot(int8_t shoot){
	if(shoot==0){
		if(shoot!=prev_shoot){
			clear_bit(PORTB,PB6);
			_delay_ms(20);
			set_bit(PORTB,PB6);
		}
	}
	prev_shoot=shoot;
}

