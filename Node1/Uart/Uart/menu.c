#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"
#include "menu.h"
#include "Joystick.h"

uint8_t menynummer = 0;	// Ved oppstart faar vi startskjerm
uint8_t vanskelighetsgrad = 1;
uint8_t musikknummer = 1;

char* highscorename1 = "PER";
char* highscorename2 = "PAAL";
char* highscorename3 = "ESPEN";
char* highscorescore1 = "0100";
char *highscorescore2 = "0098";
char *highscorescore3 = "0095";

int init_menu(void) {
	joy_position joy_pos;
	joy_init();

switch(menynummer){
	case 27 :	for (int x = 0; x < 15; x++){
					OLED_pos(x,3);
					OLED_print_animation('_');
				}
				break;
	case 0 : // Velkommen
				OLED_clear();
				double y = 2;
				float z = 1;
				float w = 1;
				int speed = 5;
				for (float x = 1; x < 20;){
					OLED_clear();
					OLED_pos(6,x);
					OLED_print("_");
 					OLED_pos(y,x);
 					OLED_print("~");
					OLED_pos(7,1);
					OLED_print("Press any key");
					x = x + z*1;
					y = y + w*0.25;
					_delay_ms(250/speed);
					if (y == 6){w = w*-1;}
					if (y == 2){w = w*-1;}
					if (x == 15){z = z*-1;}
					if (x == 0){z = z*-1;}
					while (menynummer == 0){
						joy_pos = JOY_getDirection();
						_delay_ms(50);
						if (joy_pos.sidedir > 1){
							menynummer = 1;
						}
						else if (joy_pos.dir > 1){
							menynummer = 1;
						}
 						else if (joy_button(1) == 0){
 							menynummer = 1;
 						}
						}
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
				_delay_ms(150);
				if (joy_pos.dir == 1){
					menynummer = 4;
				}
				else if (joy_pos.dir == 2){
					menynummer = 2;
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
				if (joy_pos.dir == 2){
					menynummer = 3;
				}
				else if (joy_pos.dir == 1){
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
				if (joy_pos.dir == 2){
					menynummer = 4;
				}
				else if (joy_pos.dir == 1){
					menynummer = 2;
				}
				else if (joy_button(1) == 0){
					menynummer = 23;
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
				if (joy_pos.dir == 2){
					menynummer = 1;
				}
				else if (joy_pos.dir == 1){
					menynummer = 3;
				}
				else if (joy_button(1) == 0 && musikknummer == 1){
					menynummer = 17;
				}
				else if (joy_button(1) == 0 && musikknummer == 2){
					menynummer = 19;
				}
				else if (joy_button(1) == 0 && musikknummer == 3){
					menynummer = 21;
				}
			}
			break;
	case 5 : // Submeny EASY-EASY
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("*>Easy<");
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
				if (joy_pos.dir == 2){
					menynummer = 6;
				}
				else if (joy_pos.dir == 1){
					menynummer = 8;
				}
			}
			break;	
	case 6 : // Submeny EASY-MEDIUM
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print(" >Easy<");
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
				if (joy_pos.dir == 2){
					menynummer = 7;
				}
				else if (joy_pos.dir == 1){
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
			OLED_print(" >Easy<");
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
				if (joy_pos.dir == 2){
					menynummer = 8;
				}
				else if (joy_pos.dir == 1){
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
			OLED_print(" >Easy<");
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
				if (joy_pos.dir == 2){
					menynummer = 5;
				}
				else if (joy_pos.dir == 1){
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
				if (joy_pos.dir == 2){
					menynummer = 10;
				}
				else if (joy_pos.dir == 1){
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
			OLED_print("  Easy");
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
				if (joy_pos.dir == 2){
					menynummer = 11;
				}
				else if (joy_pos.dir == 1){
					menynummer = 9;
				}
			}
			break;
	case 11 : // Submeny MEDIUM-HARD
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Easy");
			OLED_pos(3, 1);
			OLED_print(" >Medium<");
			OLED_pos(5, 1);
			OLED_print("* Hard");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 11){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.dir == 2){
					menynummer = 12;
				}
				else if (joy_pos.dir == 1){
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
				if (joy_pos.dir == 2){
					menynummer = 9;
				}
				else if (joy_pos.dir == 1){
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
				if (joy_pos.dir == 2){
					menynummer = 14;
				}
				else if (joy_pos.dir == 1){
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
			OLED_print(" >Hard<");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 14){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.dir == 2){
					menynummer = 15;
				}
				else if (joy_pos.dir == 1){
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
			OLED_print("*>Hard<");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 15){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.dir == 2){
					menynummer = 16;
				}
				else if (joy_pos.dir == 1){
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
				_delay_ms(150);
				if (joy_pos.dir == 2){
					menynummer = 13;
				}
				else if (joy_pos.dir == 1){
					menynummer = 15;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
				}
			}
			break;
	case 17 : // Submeny Music1 SONG
			OLED_clear();
			OLED_pos(2, 1);
			OLED_print(" > Sangnavn1 <");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 17){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.sidedir == 1){
					menynummer = 19;
					break;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 21;
					break;
				}
				else if (joy_pos.dir == 2){
					menynummer = 18;
					break;
				}
				else if (joy_button(1) == 0){
					musikknummer = 1;
					break;
				}
			}
			break;
	case 18 : // Submeny MUSIC1 - return
			OLED_clear();
			OLED_pos(2, 1);
			OLED_print("   Sangnavn1");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer == 18){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.dir == 2){
					menynummer = 17;
					break;
				}
				else if (joy_pos.dir == 1){
					menynummer = 17;
					break;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
					break;
				}
			}
			break;
	case 19 : // MUSIC2 - Song
			OLED_clear();
			OLED_pos(2, 1);
			OLED_print(" > Sangnavn2 <");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 19){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.sidedir == 1){
					menynummer = 21;
					break;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 17;
					break;
				}
				else if (joy_pos.dir == 2){
					menynummer = 20;
					break;
				}
				else if (joy_button(1) == 0){
					musikknummer = 2;
					break;
				}
			}
			break;
	case 20 : // MUSIC2 - return
			OLED_clear();
			OLED_pos(2, 1);
			OLED_print("   Sangnavn2");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer == 20){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.dir == 2){
					menynummer = 19;
					break;
				}
				else if (joy_pos.dir == 1){
					menynummer = 19;
					break;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
					break;
				}
			}
			break;
	case 21 : // MUSIC3 - SONG
			OLED_clear();
			OLED_pos(2, 1);
			OLED_print(" > Sangnavn3 <");
			OLED_pos(7, 1);
			OLED_print("  Back");
			_delay_ms(200);
			while(menynummer == 21){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.sidedir == 1){
					menynummer = 17;
					break;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 19;
					break;
				}
				else if (joy_pos.dir == 2){
					menynummer = 22;
					break;
				}
				else if (joy_button(1) == 0){
					musikknummer = 3;
					break;
				}
			}
			break;
	case 22 : // MUSIC3 - return
			OLED_clear();
			OLED_pos(2, 1);
			OLED_print("   Sangnavn3");
			OLED_pos(7, 1);
			OLED_print("* Back");
			_delay_ms(200);
			while(menynummer == 22){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.dir == 2){
					menynummer = 21;
					break;
				}
				else if (joy_pos.dir == 1){
					menynummer = 21;
					break;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
					break;
				}
			}
			break;
	case 23 : // HIGHSCORES - Return
			OLED_clear();
			OLED_pos(2, 3);
			OLED_print(highscorename1);
			OLED_pos(2,9);
			OLED_print(highscorescore1);
			OLED_pos(3, 3);
			OLED_print(highscorename2);
			OLED_pos(3,9);
			OLED_print(highscorescore2);
			OLED_pos(4, 3);
			OLED_print(highscorename3);
			OLED_pos(4,9);
			OLED_print(highscorescore3);
			OLED_pos(6,1);
			OLED_print("*Back    Reset");
			_delay_ms(200);
			while(menynummer == 23){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.sidedir == 1){
					menynummer = 24;
					break;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 24;
					break;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
				}
			}
			break;
	case 24 : // HIGHSCORES - Reset
			OLED_clear();
			OLED_pos(2, 3);
			OLED_print(highscorename1);
			OLED_pos(2,9);
			OLED_print(highscorescore1);
			OLED_pos(3, 3);
			OLED_print(highscorename2);
			OLED_pos(3,9);
			OLED_print(highscorescore2);
			OLED_pos(4,3);
			OLED_print(highscorename3);
			OLED_pos(4,9);
			OLED_print(highscorescore3);
			OLED_pos(6,1);
			OLED_print(" Back   *Reset");
			_delay_ms(200);
			while(menynummer == 24){
				joy_pos = JOY_getDirection();
				_delay_ms(150);
				if (joy_pos.sidedir == 1){
					menynummer = 23;
					break;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 23;
					break;
				}
				else if (joy_button(1) == 0){
					menynummer = 25;
				}
			}
			break;	
	case 25 : // Are you sure? No
			OLED_clear();
			OLED_pos(3,1);
			OLED_print("Are you sure?");
			OLED_pos(5, 1);
			OLED_print(" *No    Yes");
			_delay_ms(200);
			while(menynummer == 25){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.sidedir == 1){
					menynummer = 26;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 26;
				}
				else if (joy_button(1) == 0){
					menynummer = 23;
				}
			}
			break;
	case 26 : // Are you sure? Yes
			OLED_clear();
			OLED_pos(3,1);
			OLED_print("Are you sure?");
			OLED_pos(5, 1);
			OLED_print("  No   *Yes");
			_delay_ms(200);
			while(menynummer == 26){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.sidedir == 1){
					menynummer = 25;
				}
				else if (joy_pos.sidedir == 2){
					menynummer = 25;
				}
				else if (joy_button(1) == 0){
					menynummer = 1;
					highscorename1 = "...";
					highscorename2 = "...";
					highscorename3 = "...";
					highscorescore1 = "0000";
					highscorescore2 = "0000";
					highscorescore3 = "0000";					
				}
			}
			break;
		}
}