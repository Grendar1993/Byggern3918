/*
 * MCP2515.c
 *
 * Created: 04.10.2018 15.30.13
 *  Author: Max-Pc
 */ 

//this driver defines functions that makes it faster and easier to use the MCP-IC to send messegaes between the microcontroller and the MCP via SPI

#include "MCP2515.h"
#include "spi.h"
#include "UART.h"
#include "setup.h"

#include <util/delay.h>
#include <avr/sfr_defs.h>

//function to set up the MCP for use
uint8_t MCP_init( void )
{
	SPI_init();
	MCP_reset();
	
	uint8_t value = MCP_read(MCP_CANSTAT);
	
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("ERROR..ERROR...CONFIG NOT WORKING");
		return 1;
	}
	return 0;
}

//function to reset the MCP
void MCP_reset( void )
{
	// Lower the _CS pin
	SPI_set_ss(0);
	// Send reset instruction
	SPI_send(MCP_RESET);
	_delay_us(200);
	SPI_set_ss(1);
}

//function that lets us read register in the MCP
uint8_t MCP_read( uint8_t address )
{
	uint8_t received;
	// Lower the _CS pin
	SPI_set_ss(0);
	// Send read instruction
	SPI_send(MCP_READ);
	// Send 8-bit address
	SPI_send(address);
	// Send dummy data and receive data from MCP
	received = SPI_send(0);
	SPI_set_ss(1);
	return received;
}

//function that lets us write to registers in the MCP
void MCP_write( uint8_t address, uint8_t data )
{
	SPI_set_ss(0);
	SPI_send(MCP_WRITE);
	SPI_send(address);
	SPI_send(data);
	SPI_set_ss(1);
}

//Asking to send message via a transmission channel, only use TX0 in this project.
// RTS command is either MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2 or MCP_RTS_ALL.
void MCP_request_to_send( uint8_t RTS_command )
{
	SPI_set_ss(0);
	SPI_send(RTS_command);
	SPI_set_ss(1);
}

//function that lets us read the status of the MCP, is useful for debugging
uint8_t MCP_read_status()
{
	SPI_set_ss(0);
	SPI_send(MCP_READ_STATUS);
	uint8_t status = SPI_send(0);
	SPI_set_ss(1);
	
	return status;
}

//function that lets us change the settings of the MCP
void MCP_bit_modify( uint8_t address, uint8_t mask, uint8_t data )
{
	SPI_set_ss(0);
	SPI_send(MCP_BITMOD);
	
	SPI_send(address);
	SPI_send(mask);
	SPI_send(data);
	
	SPI_set_ss(1);
}

