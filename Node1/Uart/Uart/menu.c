#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"
#include "menu.h"
#include "Joystick.h"

uint8_t menynummer = 0;	// Ved oppstart faar vi startskjerm
uint8_t vanskelighetsgrad = 0;

int init_menu(void) {
	joy_position joy_pos;
	joy_init();

switch(menynummer){
	case 0 : // Velkommen
				OLED_clear();
 				OLED_pos(7,1);
 				OLED_print("Press any key");
				for (int x = 0; x < 18; x++){
					OLED_print_startscr(x);
					_delay_ms(50);
				}
				_delay_ms(200);
				while(menynummer == 0){
					joy_pos = JOY_getDirection();
					_delay_ms(50);
					if (joy_pos.numdirection == 4){
						menynummer = 1;
					}
					else if (joy_pos.numdirection == 3){
						menynummer = 1;
					}
					else if (joy_pos.numdirection == 2){
						menynummer = 1;
					}
					else if (joy_pos.numdirection == 1){
						menynummer = 1;
					}
// 					else if (joy_button(0) == 0){
// 						menynummer='1';
// 					}
// 					else if (joy_button(1) == 0){
// 						menynummer='1';
// 					}
				}
				break;
	case 1 : // Start Game
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
		while(menynummer == 1){
		joy_pos = JOY_getDirection();
			_delay_ms(50);
			if (joy_pos.numdirection == 4){
				menynummer = 2;
			}
			else if (joy_pos.numdirection == 3){
				menynummer = 4;
			}
		}
		break;
	case 2 : // Difficulty
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
			while(menynummer == 2){
			joy_pos = JOY_getDirection();
			_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 3;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 1;
				}
				else if (joy_button(1) == 0 && vanskelighetsgrad == 1){
					menynummer = 5;
				}
				else if (joy_button(1) == 0 && vanskelighetsgrad == 2){
					menynummer = 9;
				}
				else if (joy_button(1) == 0 && vanskelighetsgrad == 3){
					menynummer = 13;
				} 
			}
			break;
	case 3 : // Highscores
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
			while(menynummer == 3){
			joy_pos = JOY_getDirection();
			_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 4;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 2;
				}
				else if (joy_button(1) == 0){
					menynummer = 9;
				}
			}
			break;
	case 4 :			//music
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
			while(menynummer == 4){
			joy_pos = JOY_getDirection();
			_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 1;
				}
				else if (joy_pos.numdirection== 3){
					menynummer = 3;
				}
			}
			break;
	case 5 : // Submeny EASY-EASY
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("* >Easy<");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 5){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 6;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 8;
				}
			}
			break;	
	case 6 : // Submeny EASY-MEDIUM
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  >Easy<");
			OLED_pos(3, 1);
			OLED_print("* Medium");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 6){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 7;
				}
				else if (joy_pos.numdirection== 3){
					menynummer = 5;
				}
				else if (joy_button(1) == 0){
					vanskelighetsgrad = 2;
					menynummer = 10;
				}
			}
			break;	
	case 7 : // Submeny EASY-HARD
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  >Easy<");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("* Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 7){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 8;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 6;
				}
				else if (joy_button(1) == 0){
					vanskelighetsgrad = 3;
					menynummer = 15;
				}
			}
			break;	
	case 8 : // Submeny EASY-RETURN
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  >Easy<");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer == 8){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 5;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 7;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
				}
			}
			break;	
	case 9 : // Submeny MEDIUM-EASY
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("* Easy");
			OLED_pos(3, 1);
			OLED_print(" >Medium<");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 9){
			joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 10;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 12;
				}
				else if (joy_button(1) == 0){
					menynummer = 5;
					vanskelighetsgrad = 1;
				}
			}
			break;	
	case 10 : // Submeny MEDIUM-MEDIUM
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  >Easy<");
			OLED_pos(3, 1);
			OLED_print("*>Medium<");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 10){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 11;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 9;
				}
			}
			break;
	case 11 : // Submeny MEDIUM-HARD
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("  >Medium<");
			OLED_pos(5, 1);
			OLED_print("* Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 11){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 12;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 10;
				}
				else if (joy_button(1) == 0){
					menynummer = 15;
					vanskelighetsgrad = 3;
				}
			}
			break;
	case 12 : // Submeny MEDIUM-RETURN
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print(" >Medium<");
			OLED_pos(5, 1);
			OLED_print("  Hard");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer == 12){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 9;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 11;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
				}
			}
			break;
	case 13 : // Submeny HARD-EASY
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("* Easy");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print(" >Hard<");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 13){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 14;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 16;
				}
				else if (joy_button(1) == 0){
					menynummer = 5;
					vanskelighetsgrad = 1;
				}
			}
			break;
	case 14 : // Submeny HARD-MEDIUM
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("* Medium");
			OLED_pos(5, 1);
			OLED_print("  >hard<");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 14){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 16;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 13;
				}
				else if (joy_button(1) == 0){
					menynummer = 10;
					vanskelighetsgrad = 2;
				}
			}
			break;			
	case 15 : // Submeny HARD-HARD
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print("* >Hard<");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 15){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 16;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 14;
				}
			}
			break;
	case 16 : // Submeny HARD-RETURN
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print("  Medium");
			OLED_pos(5, 1);
			OLED_print(" >Hard<");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer == 16){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.numdirection == 4){
					menynummer = 13;
				}
				else if (joy_pos.numdirection == 3){
					menynummer = 15;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
				}
			}
			break;
		}
}