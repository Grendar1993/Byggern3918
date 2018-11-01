#include <stdint.h>
#include <stdio.h>


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

void PWM_init(float periode_sek, unsigned long klokkefrekvens);

void PWM_set_periode(float sec);

void PWM_pulse(float sec);


#endif /* TIMER_H_ */