#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#include "TIMER.h"

static uint16_t pwm_timer_freq;
uint16_t pulse;




void PWM_init(float periode_sek, unsigned long klokkefrekvens){
	
	uint16_t prescaler = 256;
	
	// Hva gjøre egentlig disse? Table 17-2 mode 4
	// Disse må velges for å sette fast pwm
	 TCCR1A = (1<<WGM11) | (0<<WGM10);
	 TCCR1B = (1<<WGM12) | (1<<WGM13);
	 
	 // ok what now?
	 TCCR1A = (1<<COM1A1) | (0<<COM1A0);
	 
	 pwm_timer_freq=(uint32_t)klokkefrekvens/prescaler;
	 
}

void PWM_set_periode(float sec){
		// Bestemmer at vi skal sette periodetid uten prescaler. table 17-6
		TCCR1B = (1<<CS12) |(0<<CS11) | (0<<CS10);
		
		// Set period to 20 ms (prescaler 256)
		uint16_t period = pwm_timer_freq*sec - 0.5;
		ICR1 = period;
	
}

void PWM_pulse(float sec){
	
		pulse = pwm_timer_freq*sec - 0.5;
		OCR1A = pulse;
}