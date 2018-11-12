/*
 * MOTOR_driver.h
 *
 * Created: 12.11.2018 08:56:05
 *  Author: Grend
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_


typedef enum {LEFT, RIGHT} motor_direction_t;

void motor_init();
void motor_set_direction(motor_direction_t);
void motor_set_speed(uint8_t);
int16_t motor_read_rotation(uint8_t);
void motor_reset_encoder();
void motor_calibrate();
void motor_move(int16_t rot_diff, uint8_t power);
#endif /* MOTOR_DRIVER_H_ */