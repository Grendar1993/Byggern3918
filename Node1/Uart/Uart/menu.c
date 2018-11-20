#include "setup.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "oled.h"
#include "menu.h"
#include "Joystick.h"

extern int menynummer;	// Ved oppstart faar vi startskjerm
extern uint8_t vanskelighetsgrad = 1;
extern uint8_t musikknummer = 1;
extern int highscorescore1 = 0;
extern int highscorescore2 = 0;
extern int highscorescore3 = 0;
extern int gamestep;
extern int score;
extern menuactive;
extern hp;

extern char* highscorename1[4] = {".", ".", ".", "."};
extern char* highscorename2[4] = {".", ".", ".", "."};
extern char* highscorename3[4] = {".", ".", ".", "."};
char buffer[8];
char* name[4];
joy_position joy_pos;

int init_menu(void) {
	switch(menynummer){
		case 0 : // Welcome-screen
				OLED_clear();
				float y = 2;
				float z = 1;
				float w = 1;
				float x = 1;
				int counter = 0;
				while (menynummer == 0){
					OLED_clear();
					OLED_pos(7,x-2);
					OLED_print("]_`");
					OLED_pos(1,6);
					if (counter < 10){
						OLED_print("00");
					}
					else if (counter < 100){
						OLED_print("0");
					}
					OLED_print(itoa(counter, buffer, 10));
					OLED_pos(y,x-1);
					OLED_print("~");
					OLED_pos(8,1);
					OLED_print("Press any key");
					x = x + z*1;
					y = y + w*0.5;
					if (y == 6){w = w*-1; counter = counter + 1;}
					if (y == 2){w = w*-1;}
					if (x == 15){z = z*-1;}
					if (x == 0){z = z*-1;}
					joy_pos = JOY_getDirection();
					_delay_ms(125);
					if (joy_pos.sidedir == 1){
						menynummer = 28;
					}
					else if (joy_pos.sidedir == 2){
						menynummer = 28;
					}
					else if (joy_pos.dir == 1){
						menynummer = 1;
					}
					else if (joy_pos.dir == 2){
						menynummer = 1;
					}
					else if (joy_button(1) == 0){
						menynummer = 1;
					}
			}
			break;
		case 1 : // Main menu - Start Game
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("* Start game");
			OLED_pos(3, 1);
			OLED_print("  Difficulty");
			OLED_pos(5, 1);
			OLED_print("  Highscores");
			OLED_pos(7, 1);
			OLED_print("  Mini-Pong");
			_delay_ms(200);
			while(menynummer == 1){
				joy_pos = JOY_getDirection();
				_delay_ms(50);
				if (joy_pos.dir == 1){
					menynummer = 4;
				}
				else if (joy_pos.dir == 2){
					menynummer = 2;
				}
				else if (joy_button(1) == 0){
					menuactive = 2;
					menynummer = 27;
					gamestep = 1;
					hp = 3;
					score = 0;
					break;
				}
			}
			break;
		case 2 : // Main menu - Difficulty
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Start game");
			OLED_pos(3, 1);
			OLED_print("* Difficulty");
			OLED_pos(5, 1);
			OLED_print("  Highscores");
			OLED_pos(7, 1);
			OLED_print("  Mini-Pong");
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
		case 3 : // Main menu - Highscores
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Start game");
			OLED_pos(3, 1);
			OLED_print("  Difficulty");
			OLED_pos(5, 1);
			OLED_print("* Highscores");
			OLED_pos(7, 1);
			OLED_print("  Mini-Pong");
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
		case 4 : // Main menu - Mini-Pong
			OLED_clear();
			OLED_pos(1, 1);
			OLED_print("  Start game");
			OLED_pos(3, 1);
			OLED_print("  Difficulty");
			OLED_pos(5, 1);
			OLED_print("  Highscores");
			OLED_pos(7, 1);
			OLED_print("* Mini-Pong");
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
				else if (joy_button(1) == 0){
					menynummer = 28;
					_delay_ms(150);
				}
			}
			break;
		case 5 : // Submenu difficulty - EASY-EASY
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
		case 6 : // Submeny difficulty - EASY-MEDIUM
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
		case 7 : // Submeny difficulty - EASY-HARD
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
		case 8 : // Submeny difficulty - EASY-RETURN
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
		case 9 : // Submeny difficulty - MEDIUM-EASY
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
		case 10 : // Submeny difficulty - MEDIUM-MEDIUM
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
		case 11 : // Submeny difficulty - MEDIUM-HARD
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
		case 12 : // Submeny difficulty - MEDIUM-RETURN
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
		case 13 : // Submeny difficulty - HARD-EASY
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
		case 14 : // Submeny difficulty - HARD-MEDIUM
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
		case 15 : // Submeny difficulty - HARD-HARD
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
		case 16 : // Submeny difficulty - HARD-RETURN
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
		case 23 : // HIGHSCORES - Return
			OLED_clear();
			OLED_pos(2, 3);
			for (int i = 0; i < 4; i++){
				OLED_print(highscorename1[i]);
			}
			OLED_pos(2,9);
			OLED_print(itoa(highscorescore1, buffer, 10));
			OLED_pos(3, 3);
			for (int i = 0; i < 4; i++){
				OLED_print(highscorename2[i]);
			}
			OLED_pos(3,9);
			OLED_print(itoa(highscorescore2, buffer, 10));
			OLED_pos(4, 3);
			for (int i = 0; i < 4; i++){
				OLED_print(highscorename3[i]);
			}
			OLED_pos(4,9);
			OLED_print(itoa(highscorescore3, buffer, 10));
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
			for (int i = 0; i < 4; i++){
				OLED_print(highscorename1[i]);
			}
			OLED_pos(2,9);
			OLED_print(itoa(highscorescore1, buffer, 10));
			OLED_pos(3, 3);
			for (int i = 0; i < 4; i++){
				OLED_print(highscorename2[i]);
			}
			OLED_pos(3,9);
			OLED_print(itoa(highscorescore2, buffer, 10));
			OLED_pos(4, 3);
			for (int i = 0; i < 4; i++){
				OLED_print(highscorename3[i]);
			}
			OLED_pos(4,9);
			OLED_print(itoa(highscorescore3, buffer, 10));
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
		case 25 : // Clear highscores - Are you sure? No
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
		case 26 : // Clear highscores - Are you sure? Yes
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
					for (int i = 0; i < 4; i++){
						highscorename1[i] = ".";
						highscorename2[i] = ".";
						highscorename3[i] = ".";
					}
					highscorescore1 = 0;
					highscorescore2 = 0;
					highscorescore3 = 0;
				}
			}
			break;
		case 27 :	// Highscore sorting logic. Called when player finishes the game and jumps to case 1 ("Main menu - Start game") when it is done sorting
			OLED_clear();
			if (score >= highscorescore1){
				char** endstr = OLED_nameprompt();
				for (int i = 0; i < 4; i++){							// If score >= highest score, move everything down 1 rank and replace highest score with the achieved score
					highscorename3[i] = highscorename2[i];
					highscorename2[i] = highscorename1[i];
					highscorename1[i] = endstr[i];
					}
				highscorescore3 = highscorescore2;
				highscorescore2 = highscorescore1;
				highscorescore1 = score;
			}
			else if (score >= highscorescore2){							// Same as previous, but with the second highest score
				char** endstr = OLED_nameprompt();
				for (int i = 1; i < 4; i++){
					highscorename3[i] = highscorename2[i];
					highscorename2[i] = endstr[i];
				}
				highscorescore3 = highscorescore2;
				highscorescore2 = score;
			}
			else if (score >= highscorescore3){							// Same as previous, but with the third highest score
				char** endstr = OLED_nameprompt();
				for (int i = 1; i < 4; i++){
					highscorename3[i] = endstr[i];
				}
				highscorescore3 = score;
			}
			menynummer = 1;
			break;
		case 28 :	// Mini-Pong. Ping-pong game played on the OLED-screen.
			OLED_clear();
			float v = 2;																// Position of slider
			y = 2;																		// Position of ball on screen (y-axis)
			x = 1;																		// Position of ball on screen (x-axis)
			z = 1;																		// Inverter
			w = 1;																		// Inverter
			counter = 0;																// Score counter
			while (menynummer == 28){
				OLED_clear();
				OLED_pos(7,v-2);														// Placement and print of the slider
				OLED_print("]_`");
				OLED_pos(y,x);															// Placement and print of the ball
				OLED_print("~");
				OLED_pos(8,7);
				if ((y == 6)&&((round(x) == v)||(round(x) == v-1)||round(x) == v-2)){	// If the ball hits the slider, add 1 to the score.
					counter = counter + 1;
				}
				else if (y == 6){														// If the ball is on the bottom of the screen, but miss the slider, reset score
					counter = 0;
				}
				if (counter < 10){														// Cosmetic, add "00" in front of the score if it is a single digit number
					OLED_print("00");
				}
				else if (counter < 100){												// Cosmetic, add "0" in front of the score if it is a double digit number
					OLED_print("0");
				}
				OLED_print(itoa(counter, buffer, 10));									// Print counter. itoa() converts from number to string (10 sets the decimal number system)
				
				x = x + z*0.25;															// Speed of ball in x-axis, z is a positive or negative number, depending on ball direction
				y = y + w*0.5;															// Speed of ball in y-axis, w is a positive or negative number, depending on ball direction
				
				if (y == 6){w = w*-1;}													// If the ball hits the bottom or top side of the screen, invert our speed-increment (*-1)
				if (y == 2){w = w*-1;}													
				if (x == 15){z = z*-1;}													// If the ball hits one of the sides of the screen, invert our speed increment (*-1)
				if (x == 0){z = z*-1;}
				joy_pos = JOY_getDirection();
				int timer = 250/vanskelighetsgrad;
				my_delay_ms(timer);														// Game speed
				if (joy_pos.sidedir == 1){												// Moving the joystick to the right moves the slider to the left
					v = v + 1;
					if (v > 15){														// Make sure joystick doesent move out of the screen
						v = 15;
					}				}
				else if (joy_pos.sidedir == 2){
					v = v - 1;
					if (v < 1){
						v = 1;
					}
				}
				else if (joy_button(1) == 0){											// If button is pressed, exit game and return to main menu
					menynummer = 1;
				}
			}
			break;
	}
return gamestep;
}