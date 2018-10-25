#include <avr/pgmspace.h>

#ifndef FONT_DRAWINGS_H_
#define FONT_DRAWINGS_H_

const unsigned char PROGMEM ntnu[7][128] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,
0xF8,0xF8,0xF0,0xE0,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xF8,0xF8,
0xF8,0xF8,0xF8,0x70,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,
0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,
0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xE0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,
0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xE1,0xE1,
0xF3,0xFF,0xFF,0xFF,0xFF,0x7F,0x1E,0x00,0x00,0x00,0x00,0xC0,0xF1,0xF9,0xF9,0xF9,
0xF9,0xF1,0xF0,0xE0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x7F,0xFF,0xFF,0xFE,0xFE,0xF8,0xF0,0xE0,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x03,0x01,0x01,0x01,0xE1,
0xE1,0xF1,0xF1,0xF1,0xF3,0xF3,0xF3,0xF1,0xF1,0xF0,0xF0,0xF0,0xF0,0xE0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x07,0x07,0x07,0x07,
0x07,0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x78,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,
0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,
0x00,0x00,0x00,0x01,0x07,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFE,0xF8,0xF8,0xF8,0xF8,
0xF9,0xF9,0xF9,0xF9,0xFD,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x0F,0x07,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF8,0xF8,
0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF9,0xF1,0xF1,0xE1,0xE0,0xC0,0xC0,0x80,0x00,0x00,
0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFC,0xF0,0xF0,0xE0,0xC1,0x81,0x01,0x00,0x00,0x00,
0xE0,0xF0,0xF0,0xF8,0xF8,0xF0,0xF0,0xE0,0xC0,0xC0,0x01,0x01,0x01,0x00,0x00,0x00,
0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0xC1,0xC1,
0xE1,0xE1,0xF1,0xF1,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,
0xE0,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xC1,0xC1,0xC1,0xC1,0xC1,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x00,
0x00,0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0x81,0x81,0x81,
0x81,0x81,0xC3,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,
0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFE,0xFC,0xFC,0xF8,0xF0,0xE0,
0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,
0xFF,0xFF,0x0F,0x07,0x03,0x03,0x01,0x01,0x01,0xE1,0xF1,0xF1,0xF1,0xF3,0xF3,0xF3,
0xF3,0xF1,0xF1,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x3F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,
0x00,0x00,0x00,0x0F,0x1F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x01,0x00,0x00,0x00,
0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x01,0x03,0x07,0x07,0x0F,0x1F,
0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0x78,0x00,0x00,0x00,0x07,0x0F,0x3F,0x3F,
0x7F,0x7F,0xFF,0xFE,0xFC,0xF8,0xF8,0xF8,0xF8,0xF9,0xFB,0xFB,0xFB,0xFF,0xFF,0xFF,
0x7F,0x7F,0x3F,0x1F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

const unsigned char PROGMEM mushroom[4][32] = {
	//Line 0
	{0b00000000,0b00000000,0b11000000,0b11000000,0b11110000,0b11110000,0b00111100,0b00111100,
		0b11111111,0b11111111,0b11111111,0b11111111,0b00111111,0b00111111,0b00000011,0b00000011,
		0b00000011,0b00000011,0b00111111,0b00111111,0b11111111,0b11111111,0b11111111,0b11111111,
	0b00111100,0b00111100,0b11110000,0b11110000,0b11000000,0b11000000,0b00000000,0b00000000},
	//Line 1
	{0b11111100,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,0b11111100,0b11111100,
		0b00000000,0b00000000,0b11110000,0b11110000,0b11111100,0b11111100,0b11111100,0b11111100,
		0b11111100,0b11111100,0b11111100,0b11111100,0b11110000,0b11110000,0b00000000,0b00000000,
	0b11111100,0b11111100,0b11111111,0b11111111,0b11111111,0b11111111,0b11111100,0b11111100},
	//Line 2
	{0b11111111,0b11111111,0b11000011,0b11000011,0b11000011,0b11000011,0b11110000,0b11110000,
		0b00110000,0b00110000,0b00110011,0b00110011,0b11111111,0b11111111,0b00111111,0b00111111,
		0b00111111,0b00111111,0b11111111,0b11111111,0b00110011,0b00110011,0b00110000,0b00110000,
	0b11110000,0b11110000,0b11000011,0b11000011,0b11000011,0b11000011,0b11111111,0b11111111},
	//Line 3
	{0b00000000,0b00000000,0b00000011,0b00000011,0b00111100,0b00111100,0b11000000,0b11000000,
		0b11000000,0b11000000,0b11000000,0b11000000,0b11000011,0b11000011,0b11000000,0b11000000,
		0b11000000,0b11000000,0b11000011,0b11000011,0b11000000,0b11000000,0b11000000,0b11000000,
	0b11000000,0b11000000,0b00111100,0b00111100,0b00000011,0b00000011,0b00000000,0b00000000}
};

const unsigned char PROGMEM circles[7][32] = {
	//clear
	{0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=2
	{0b00000110,0b00001001,0b00001001,0b00000110,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=3
	{0b00001100,0b00010010,0b00100001,0b00100001,0b00010010,0b00001100,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=4
	{0b00111100,0b01000010,0b10000001,0b10000001,0b10000001,0b10000001,0b01000010,0b00111100,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
	0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=5
	{0b01111000,0b10000100,0b00000010,0b00000001,0b00000001,0b00000001,0b00000001,0b00000010,
		0b10000100,0b01111000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000000,0b00000000,0b00000001,0b00000010,0b00000010,0b00000010,0b00000010,0b00000001,
	0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=6
	{0b11111000,0b00000100,0b00000010,0b00000001,0b00000001,0b00000001,0b00000001,0b00000001,
		0b00000001,0b00000010,0b00000100,0b11111000,0b00000000,0b00000000,0b00000000,0b00000000,
		0b00000001,0b00000010,0b00000100,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,
	0b00001000,0b00000100,0b00000010,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000},
	//r=7
	{0b11110000,0b00001000,0b00000100,0b00000010,0b00000001,0b00000001,0b00000001,0b00000001,
		0b00000001,0b00000001,0b00000010,0b00000100,0b00001000,0b11110000,0b00000000,0b00000000,
		0b00000011,0b00000100,0b00001000,0b00010000,0b00100000,0b00100000,0b00100000,0b00100000,
	0b00100000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000011,0b00000000,0b00000000}
};

#endif