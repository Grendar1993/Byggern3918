#ifndef JOYSTICK_H_
#define JOYSTICK_H_

//values used to calibrate the joystick, makes it possible to find the neutral position of the joystick
uint8_t mid_x, mid_y;

//struct for different readings from the joystick
//we can find the x-axis value, the y-axis value as well as the direction of the, both as a strong and a number 
typedef struct {
	int8_t x;
	int8_t y;
	int8_t dir;		// 1 = UP, 2 = DOWN
	int8_t sidedir; // 1 = RIGHT, 2 = LEFT
} joy_position;

//struct for the slider positions, we have two sliders, left and right slider
typedef struct {
	uint8_t left;
	uint8_t right;
} slider_position;

int joy_init(void);
int JOY_calibrate(void);
int joy_button(int button);
joy_position JOY_getPosition(void);
joy_position JOY_getDirection(void);
slider_position JOY_getSliderPosition(void);

#endif