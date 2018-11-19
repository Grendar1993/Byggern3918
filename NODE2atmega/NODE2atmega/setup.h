/*
 * setup.h
 *
 * Created: 20.09.2018 15.36.14
 *  Author: Max-Pc
 */ 


#ifndef SETUP_H_
#define SETUP_H_

// #define F_CPU 4912500 /*4912500UL*/
// #define BAUD 9600
// #define UBRREG F_CPU/16/BAUD-1


#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))



#endif /* SETUP_H_ */