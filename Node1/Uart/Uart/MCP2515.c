/*
 * MCP2515.c
 *
 * Created: 04.10.2018 15.30.13
 *  Author: Max-Pc
 */ 

#include "MCP2515.h"
#include "spi.h"
#include "UART.h"
#include "setup.h"

#include <util/delay.h>
#include <avr/sfr_defs.h>


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

void MCP_reset( void )
{
	// Lower the _CS pin
	SPI_set_ss(0);
	// Send reset instruction
	SPI_send(MCP_RESET);
	_delay_us(200);
	SPI_set_ss(1);
}

uint8_t MCP_read( uint8_t address )
{
	uint8_t received;
	// Lower the _CS pin
	SPI_set_ss(0);
	// Send read instruction
	SPI_send(MCP_READ);
	// Send 8-bit address
	SPI_send(address);
	// Send dummy data and receive data from MCP2515 because extra receive function is stupid
	received = SPI_send(0);
	SPI_set_ss(1);
	return received;
}

void MCP_write( uint8_t address, uint8_t data )
{
	SPI_set_ss(0);
	SPI_send(MCP_WRITE);
	SPI_send(address);
	SPI_send(data);
	SPI_set_ss(1);
}

// RTS command is either MCP_RTS_TX0, MCP_RTS_TX1, MCP_RTS_TX2 or MCP_RTS_ALL
void MCP_request_to_send( uint8_t RTS_command )
{
	SPI_set_ss(0);
	SPI_send(RTS_command);
	SPI_set_ss(1);
}

uint8_t MCP_read_status()
{
	SPI_set_ss(0);
	SPI_send(MCP_READ_STATUS);
	uint8_t status = SPI_send(0);
	SPI_set_ss(1);
	
	return status;
}

void MCP_bit_modify( uint8_t address, uint8_t mask, uint8_t data )
{
	SPI_set_ss(0);
	SPI_send(MCP_BITMOD);
	
	SPI_send(address);
	SPI_send(mask);
	SPI_send(data);
	
	SPI_set_ss(1);
}

