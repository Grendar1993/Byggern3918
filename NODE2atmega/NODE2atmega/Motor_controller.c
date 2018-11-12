/*
 * Motor_controller.c
 *
 * Created: 12.11.2018 10:51:37
 *  Author: Grend
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"
#include "setup.h"
#include "can.h"
#include "MOTOR_driver.h"
#include <math.h>
#include <util/delay.h>

float pos_min = 86;
float pos_max = 9200;
float current_pos = -86;
//float ref=-8000;
char rettning;
float possition;
int16_t prev_error = 0;
int16_t prev_padrag = 0;
int16_t padrag = 0;
// 
// ISR(TIMER2_OVF_vect){
// 	float possisjon = motor_read_rotation(0);
// 	error = ref - possisjon;
// 	if(ref>possisjon){
// 		rettning = "RIGHT";
// 	}
// 	else{
// 		rettning = "LEFT";
// 	}
// 	PID_alg(error,rettning);
// 	
// }

void PID_alg(ref){
double kp=0.05;
double Ti=100;
double h=1/F_CPU;
double possisjon = ((motor_read_rotation(0)*-1))/10;
int16_t error = (ref/10)-possisjon;
padrag=prev_padrag+kp*(error*(h/Ti)-prev_error);

if(padrag>255){
	padrag = 200;
}
else if(padrag<-255){
	padrag=-200;
}
if(signbit(padrag)==signbit(-1)){
	motor_set_direction(RIGHT);
}
else if(signbit(padrag)==signbit(1)){
	motor_set_direction(LEFT);
}
prev_padrag=padrag;
prev_error=error;

padrag = abs(padrag);
motor_set_speed(padrag);


// printf("Pådrag: %d \r\n",padrag);
// printf("Error: %d \r\n",error);
// _delay_ms(500);
}



void PID_init(void){
	
	
	
// skrur av global int
// cli();
// 
// TIMSK2=(1<<TOIE2);
// 
// sier at den må telle til 1024 før den teller en
// TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
// 
// skrur på global int
// sei();
}