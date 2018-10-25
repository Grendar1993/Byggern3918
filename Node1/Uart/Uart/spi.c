/*
 * spi.c
 *
 * Created: 04.10.2018 14.19.47
 *  Author: Max-Pc
 */ 

#include "spi.h"
#include "setup.h"


#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

void SPI_init( void )
{
	// Set MOSI, SCK and SS output
	DDRB |= (1 << DDB5)|(1 << DDB7)|(1 << DDB4);
	DDRB &= ~(1<<DDB6);
	//usikker DDRB |= (1 << DDB2)|(1 << DDB1)|(1 << DDB0) | (1 << DDB7);
	
	// Enable SPI, Master, set clock rate
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
}

uint8_t SPI_send(uint8_t data)
{
	// Start transmission (write to data register)
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & (1 << SPIF)));
	// kanskje _delay_us(200);
	
	return SPDR;
	
}

//kinda pointless
uint8_t SPI_read(void) {
	//Send dummy data to read for slave
	SPI_send(0);
	
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

// Defines chip-select, unsure if necessary
void SPI_set_ss( int select )
{
	//for ATmega 162 set chip-select
	if (select == 1){
		set_bit(PORTB, PB4);
	}
	else if (select == 0){
		clear_bit(PORTB, PB4);
	}
	
	
	//for ATmega 2560 sets chip-select
// 	if (select == 1){
// 		set_bit(PORTB, PB7);
// 	}
// 	else if (select == 0){
// 		clear_bit(PORTB, PB7);
// 	}

	
}