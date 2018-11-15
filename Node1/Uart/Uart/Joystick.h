#ifndef JOYSTICK_H_
#define JOYSTICK_H_

uint8_t mid_x, mid_y;

typedef struct {
	int8_t x;
	int8_t y;
	int8_t sidedir; // 1 = Right, 2 = Left
	int8_t dir;		// 1 = Up, 2 = Down
} joy_position;

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