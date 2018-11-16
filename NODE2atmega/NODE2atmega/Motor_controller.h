/*
 * Motor_controller.h
 *
 * Created: 12.11.2018 10:51:19
 *  Author: Grend
 */ 


#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_
typedef enum{
	EASY,
	MEDIUM,
	HARD
} vanskelighetsgrad_t;

	
void PID_alg(int16_t);
void PID_init(void);
int16_t update_ref(int16_t);
void PID_diff(vanskelighetsgrad_t);

#endif /* MOTOR_CONTROLLER_H_ */