/*
This driver sets up functions that makes it easier to convert the values from the joystick and the slider to digital values that can be used by the micocontroller
*/



#include <avr/io.h>
#include <stdio.h>
#include "adc.h"
#include "joystick.h"
#include "setup.h"

uint8_t mid_x, mid_y;

int joy_init(void){
	// let the ADC set itself up
	ADC_init();
	
	//Set Button pins to input
	DDRB &= ~(1<<PINB0) & ~(1<<PINB1) & ~(1<<PINB2);
	//set pull up resistors
	PORTB |= (1<<PINB0) | (1<<PINB1) | (1<<PINB2); 
	
	//Let the joystick calibrate itself
	JOY_calibrate();
	
	return 0;
}

//the calibrate function reads the initial values of the joystick and assumes these are the neutral positions.
int JOY_calibrate(void) {
	mid_x=ADC_read(0);
	mid_y=ADC_read(1);
	return 0;
}

// setting the inputs for the pins that the buttons are connected to
int joy_button(int button){
	switch (button) {
		case 0: // joystick button
			if (!test_bit(PINB,PINB0)) return 1;
			break;
		case 1: // left button
			if (!test_bit(PINB,PINB1)) return 1;
			break;	
		case 2: // right button
			if (!test_bit(PINB,PINB2)) return 1;
			break;
		default:
				break;
	}
	return 0;
}

// function that is used to get the position of the joystick
joy_position JOY_getPosition(void) {
	joy_position position;
	uint8_t x, y;
	
	//Read position x from channel 0
	x = ADC_read(1);
	//Read position y from channel 1
	y = ADC_read(0);
	
	//Calculate position x percentage
	if(x > mid_x) {
		position.x = 100 * (x - mid_x) / (0xFF - mid_x);
		} else if (x < mid_x) {
		position.x = 100 * (x - mid_x) / (mid_x - 0);
		} else {
		position.x = 0;
	}
	
	//Calculate position y percentage
	if(y > mid_y) {
		position.y = 100 * (y - mid_y) / (0xFF - mid_y);
		} else if (y < mid_y) {
		position.y = 100 * (y - mid_y) / (mid_y - 0);
		} else {
		position.y = 0;
	}
	
	return position;
}

//function to find the direction of the joystick, for use in the menu, represented both as a string and an interger
joy_position JOY_getDirection(void) {
	joy_position position;
	
	//Get actual position of joystick
	position = JOY_getPosition();
	
	if(position.x < -45) {
		position.direction = "LEFT";
		position.numdirection = 2;
		} 
	else if(position.x > 45) {
		position.direction = "RIGHT";
		position.numdirection = 1;
	}
	
	if(position.y < -45) {
		position.direction = "DOWN";
		position.numdirection = 4;
		} 
	else if(position.y > 45) {
		position.direction = "UP";
		position.numdirection = 3;
	}
	
	if((position.x >= -44 && position.x <= 44) && (position.y >= -44 && position.y <= 44)){
		position.direction = "NEUTRAL";
		position.numdirection = 0;
	}
	
	return position;
}
//find the slider position, for both sliders
slider_position JOY_getSliderPosition(void) {
	slider_position position;
	uint8_t l, r;
	
	//Read left slider from channel 2
	l = ADC_read(2);
	//Read right slider from channel 3
	r = ADC_read(3);
	
	//Calculate position percentage
	position.left = 100 * l / 0xFF;
	position.right = 100 * r / 0xFF;
	
	return position;
}
