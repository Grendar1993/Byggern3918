/*
 * spi.h
 *
 * Created: 04.10.2018 14.19.34
 *  Author: Max-Pc
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_init( void );
uint8_t SPI_send(uint8_t data);
void SPI_set_ss( int select );
uint8_t SPI_read(void);

#endif /* SPI_H_ */