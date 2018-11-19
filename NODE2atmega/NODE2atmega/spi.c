/*
 * spi.c
 *
 * Created: 04.10.2018 14.19.47
 *  Author: Max-Pc
 */ 

#define F_CPU 16000000

#include "spi.h"
#include "setup.h"
#include "UART.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#define SPI_SS PB7
#define SPI_MOSI PB2
#define SPI_MISO PB3
#define SPI_SCK PB1

/*
This driver enables the use of the SPI, so we can use it for communication between the micro controller and the MCP
*/


//function that sets up the SPI, defines PINs and clock speed, and chooses master and slave
void SPI_init( void )
{
	
// Set MOSI, SCK and SS output
DDRB |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS) | (1<<PB0);

//Set MISO as input pin
DDRB &= ~(1<<SPI_MISO);

//Enable SPI in master mode and set clock rate fosc/16
SPCR = (1<<SPE) | (1<<MSTR) | (0<<SPR1) | (1<<SPR0);		
	
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
	if (select == 1){
		set_bit(PORTB, SPI_SS);
	}
	else if (select == 0){
		clear_bit(PORTB, SPI_SS);
	}

	
}