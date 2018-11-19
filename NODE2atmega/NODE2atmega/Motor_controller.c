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
#include "Motor_controller.h"
#include "math.h"
#include <util/delay.h>

float pos_min = 86;
float pos_max = 9200;
float current_pos = -86;
static int16_t ref;
static double  prev_error = 0;
static double  prev_prev_error = 0;
static double prev_padrag = 0;
int16_t prev_ref_update;
int16_t terskel = 150;



ISR(TIMER2_OVF_vect){
	PID_alg(ref);
}

void PID_init(){
		 //-------------INITIALIZE TIMER INPUT-----------------
		 
		 // Disable global interrupts
		 cli();
		 
		 // enable timer overflow interrupt for Timer2 denne er 8 bit
		 TIMSK2=(1<<TOIE2);
		 
		 // start timer2 with /1024 prescaler
		 
		 TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
		 
		 // Enable global interrupts
		 sei();
		 
		 //---------------------------------------------------
}

int16_t update_ref(int16_t oppdatert_ref){
	ref=oppdatert_ref;
	return ref;
}

void PID_alg(int16_t ref){
int16_t padrag;
int16_t error;
double kp=1.5;
double Ti=0.5;
double h=0.016;
//double Td= 0.02;
int16_t possisjon;

//beregning av possisjon gjør om 0-9200 til 0-255
possisjon = (motor_read_rotation(0)*-1);
possisjon = possisjon * 0.027;

// beregner error
error = ref - possisjon;

// regulator algoritme (Regtekboka)
padrag = prev_padrag + kp*((1 + h/Ti)*error-prev_error);
// prøve en PID
//padrag = prev_padrag + kp*((1 + h/Ti + Td/h)*error+(-1-((2*Td)/h) )*prev_error + (Td/h)*prev_prev_error);
//printf("Padrag: %d \r\n",padrag);

//legger limit på hastighet
if(padrag>terskel){
	padrag = terskel;}
else if(padrag<-terskel){
	padrag=-terskel;}	

//velger rettning
if(padrag<0){
	motor_set_direction(LEFT);}
else{
	motor_set_direction(RIGHT);}
	
//oppdaterer variabler
prev_prev_error=prev_error;
prev_error=error;
prev_padrag=padrag;

// setter ut padraget
padrag=abs(padrag);
motor_set_speed(padrag);
}

void PID_diff(vanskelighetsgrad_t vanskelighetsgrad){
	switch (vanskelighetsgrad){
		case EASY:
				terskel=150;
				break;
		case MEDIUM:
				terskel=200;
				break;
		case HARD:
				terskel=255;
				break;	
	}
}
