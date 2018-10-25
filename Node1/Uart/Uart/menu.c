#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"
#include "menu.h"
#include "Joystick.h"

char menynummer='0';	// Ved oppstart faar vi startskjerm
int init_menu(void) {
	joy_position joy_pos;
	joy_init();

switch(menynummer){
	case '0' : // Velkommen
				OLED_clear();
 				OLED_pos(7,1);
 				OLED_print("Press any key");
				for (int x = 0; x < 18; x++){
					OLED_print_startscr(x);
					_delay_ms(50);
				}
				_delay_ms(200);
				while(menynummer=='0'){
					joy_pos = JOY_getDirection();
					_delay_ms(50);
					if (joy_pos.direction=="DOWN"){
						menynummer='1';
					}
					else if (joy_pos.direction=="UP"){
						menynummer='1';
					}
					else if (joy_pos.direction=="LEFT"){
						menynummer='1';
					}
					else if (joy_pos.direction=="RIGHT"){
						menynummer=='1';
					}
// 					else if (joy_button(0) == 0){
// 						menynummer='1';
// 					}
// 					else if (joy_button(1) == 0){
// 						menynummer='1';
// 					}
				}
				break;
	case '1' : // Start Game
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("* Start game");
			OLED_pos(3, 1);
			OLED_print("  Difficulty");
			OLED_pos(5, 1);
			OLED_print("  Highscores");
			OLED_pos(7, 1);
			OLED_print("  Music");
			_delay_ms(200);
		while(menynummer=='1'){
		joy_pos = JOY_getDirection();
			_delay_ms(50);
			if (joy_pos.direction=="DOWN"){
				menynummer='2';
			}
			else if (joy_pos.direction=="UP"){
				menynummer='4';
			}
		}
		break;
	case '2' : // Difficulty
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Start game");
			OLED_pos(3, 1);
			OLED_print("* Difficulty");
			OLED_pos(5, 1);
			OLED_print("  Highscores");
			OLED_pos(7, 1);
			OLED_print("  Music");
			_delay_ms(200);
			while(menynummer=='2'){
			joy_pos = JOY_getDirection();
			_delay_ms(50);
				if (joy_pos.direction == "DOWN"){
					menynummer='3' ;
				}
				else if (joy_pos.direction == "UP"){
					menynummer='1' ;
				}
				else if (joy_button(1) == 0){
					menynummer='5';
				}
			}
			break;
	case '3' : // Highscores
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Start game");
			OLED_pos(3, 1);
			OLED_print("  Difficulty");
			OLED_pos(5, 1);
			OLED_print("* Highscores");
			OLED_pos(7, 1);
			OLED_print("  Music");
			_delay_ms(200);
			while(menynummer=='3'){
			joy_pos = JOY_getDirection();
			_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='4';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='2';
				}
				else if (joy_button(1) == 0){
					menynummer='9';
				}
			}
			break;
	case '4' :			//music
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Start game");
			OLED_pos(3, 1);
			OLED_print("  Difficulty");
			OLED_pos(5, 1);
			OLED_print("  Highscores");
			OLED_pos(7, 1);
			OLED_print("* Music");
			_delay_ms(200);
			while(menynummer=='4'){
			joy_pos = JOY_getDirection();
			_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='1';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='3';
				}
			}
			break;
	case '5' : // Submeny difficulty easy
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("* Easy");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer=='5'){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='6';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='8';
				}
			}
			break;	
	case '6' : // Submeny difficulty medium
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("* Medium");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer=='6'){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='7';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='5';
				}
			}
			break;	
	case '7' : // Submeny difficulty hard
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("* Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer=='7'){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='8';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='6';
				}
			}
			break;	
	case '8' : // Submeny difficulty return
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer=='8'){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='5';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='7';
				}
				else if (joy_button(1) == 0){
					menynummer='1';
				}
			}
			break;	
	case '9' : // Test
			OLED_clear();
			OLED_pos(8,1);
			OLED_print("Press any key");
			for (int x = 0; x < 18; x++){
				OLED_print_startscr(x);
				_delay_ms(50);
			}
			_delay_ms(200);
			while(menynummer=='9'){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.direction=="DOWN"){
					menynummer='1';
				}
				else if (joy_pos.direction=="UP"){
					menynummer='1';
				}
			}
			break;
		}
	}