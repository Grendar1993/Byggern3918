#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"
#include "menu.h"
#include "Joystick.h"

//#include "buzzer.h"
//#include "eeprom.h"

char menynummer='0';

int init_menu(void) {
	joy_position joy_pos;
	joy_init();
	joy_pos = JOY_getDirection();


switch(menynummer){
	case '1' :
			OLED_clear();
			OLED_pos(1, 4);
			OLED_print("* Start game");
			OLED_pos(3, 4);
			OLED_print("  Difficulty");
			OLED_pos(5, 4);
			OLED_print("  Options");
			OLED_pos(7, 4);
			OLED_print("  Music");
			_delay_ms(300);
		while(menynummer=='1'){
			joy_pos = JOY_getDirection();
// 			OLED_pos(radvelger, 1);
// 			OLED_print("*");
			if (joy_pos.direction=="DOWN"){
				menynummer='2' ;
				break;
			}
			else if (joy_pos.direction=="UP"){
				menynummer='1' ;
				break;
			}
			// definere peker
		}
	case '2' :
			OLED_clear();
			OLED_pos(1, 4);
			OLED_print("  Start game");
			OLED_pos(3, 4);
			OLED_print("* Difficulty");
			OLED_pos(5, 4);
			OLED_print("  Options");
			OLED_pos(7, 4);
			OLED_print("  Music");
			_delay_ms(300);
			while(menynummer=='2'){
			joy_pos = JOY_getDirection();
				// 			OLED_pos(radvelger, 1);
				// 			OLED_print("*");
				if (joy_pos.direction=="DOWN"){
					menynummer='3' ;
					break;
				}
				else if (joy_pos.direction=="UP"){
					menynummer='1' ;
					break;
				}
				// definere peker
			}

	case '3' :
			OLED_clear();
			OLED_pos(1, 4);
			OLED_print("  Start game");
			OLED_pos(3, 4);
			OLED_print("  Difficulty");
			OLED_pos(5, 4);
			OLED_print("* Options");
			OLED_pos(7, 4);
			OLED_print("  Music");
			_delay_ms(300);
			while(menynummer=='3'){
			joy_pos = JOY_getDirection();
				// 			OLED_pos(radvelger, 1);
				// 			OLED_print("*");
				if (joy_pos.direction=="DOWN"){
					menynummer='4' ;
					break;
				}
				else if (joy_pos.direction=="UP"){
					menynummer='2' ;
					break;
				}
				// definere peker
			}
	case '4' :			
			OLED_clear();
			OLED_pos(1, 4);
			OLED_print("  Start game");
			OLED_pos(3, 4);
			OLED_print("  Difficulty");
			OLED_pos(5, 4);
			OLED_print("  Options");
			OLED_pos(7, 4);
			OLED_print("* Music");
			_delay_ms(300);
			while(menynummer=='4'){
			joy_pos = JOY_getDirection();
			// 			OLED_pos(radvelger, 1);
			// 			OLED_print("*");
				if (joy_pos.direction=="DOWN"){
					menynummer='4' ;
					break;
				}
				else if (joy_pos.direction=="UP"){
					menynummer='3' ;
					break;
				}
		// definere peker
			}
    
	default:
 		if (joy_pos.direction == "DOWN") {
	 		OLED_clear();
	 		menynummer = '1';
 		}
}}