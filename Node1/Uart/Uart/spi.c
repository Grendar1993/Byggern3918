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

/*
This driver enables the use of the SPI, so we can use it for communication between the micro controller and the MCP
*/


//function that sets up the SPI, defines PINs and clock speed, and chooses master and slave
void SPI_init( void )
{
	// Set MOSI, SCK and SS output
	DDRB |= (1 << DDB5)|(1 << DDB7)|(1 << DDB4);
	DDRB &= ~(1<<DDB6);
	
	// Enable SPI, Master, set clock rate
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
}

//function that makes it easier to send data via the SPI
uint8_t SPI_send(uint8_t data)
{
	// Start transmission (write to data register)
	SPDR = data;
	// Wait for transmission complete
	while(!(SPSR & (1 << SPIF)));
	
	return SPDR;
	
}

//function that makes it possible to read data by sending dummy data, as SPI can only read and write at the same time
//not really needed
uint8_t SPI_read(void) {
	//Send dummy data to read for slave
	SPI_send(0);
	
	//Wait for data to be received
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

// Defines chip-select, is done manually
void SPI_set_ss( int select )
{
	//use Port B4 as SS
	if (select == 1){
		set_bit(PORTB, PB4);
	}
	else if (select == 0){
		clear_bit(PORTB, PB4);
	}
	

	
}