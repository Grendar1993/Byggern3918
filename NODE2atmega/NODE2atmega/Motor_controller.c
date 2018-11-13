/*
 * Motor_controller.c
 *
 * Created: 12.11.2018 10:51:37
 *  Author: Grend
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

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
int16_t ref;
double  prev_error;



ISR(TIMER2_OVF_vect){
	PID_alg(ref);
	
}

void PID_init(){
		 //-------------INITIALIZE TIMER INPUT-----------------
		 
		 // Disable global interrupts
		 cli();
		 
		 // enable timer overflow interrupt for Timer2
		 TIMSK2=(1<<TOIE2);
		 
		 // start timer2 with /1024 prescaler
		 
		 TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
		 
		 // Enable global interrupts
		 sei();
		 
		 //---------------------------------------------------
}

int16_t update_ref(int16_t oppdatert_ref){
	ref=oppdatert_ref;
}

void PID_alg(int16_t ref){
float kp=0.5;
float Ti=1;
float h=0.00016;
float k= 255;
float k_1 = 9200;
int32_t possisjon = (motor_read_rotation(0)*-1);
possisjon = possisjon * k;
possisjon = possisjon / k_1;
double error = ref - possisjon;
prev_error = prev_error + error;
int32_t padrag = kp*error + h*Ti*prev_error;

//hindrer at integratoren bygger seg for mye op
if(possisjon==error){
	prev_error=0;
}

//printf("padrag = %li, possisjon = %li \r\n", padrag, possisjon);

if(padrag>255){
	padrag = 100;
}
else if(padrag<-255){
	padrag=-100;
}	
if(signbit(padrag)==signbit(-1)){
	motor_set_direction(LEFT);
}
else if(signbit(padrag)==signbit(1)){
	motor_set_direction(RIGHT);
}
padrag = abs(padrag);
//if(padrag<50){
//	padrag=50;
//}
motor_set_speed(padrag);
}
