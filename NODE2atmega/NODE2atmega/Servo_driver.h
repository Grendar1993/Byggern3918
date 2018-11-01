/*
 * Servo_driver.h
 *
 * Created: 01.11.2018 15:52:26
 *  Author: Grend
 */ 


#ifndef SERVO_DRIVER_H_
#define SERVO_DRIVER_H_

void servo_init(unsigned long clock_speed);

void set_servo(int servo_rettning);



#endif /* SERVO_DRIVER_H_ */