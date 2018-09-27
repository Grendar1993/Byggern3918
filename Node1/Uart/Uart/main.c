/*
 * Uart.c
 *
 * Created: 04.09.2018 09.43.47
 * Author : Grendar
 */ 

#define F_CPU 4912500 /*4912500UL*/
#define BAUD 9600
#define UBRREG F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "setup.h"
#include "ADC.h"
#include "UART.h"
#include "Joystick.h"
#include "oled.h"
#include "sram.h"

int main(void)
{
	UART_Init(UBRREG);
	ADC_init();
	joy_init();
	OLED_init();
	printf("----TING FUNK----\n\r");
	
	// Clear OLED screen
		while(1){
			OLED_clear();
		}
	return 0;
}