#ifndef OLED_H_
#define OLED_H_

uint8_t page, col;

int OLED_init(void);
int OLED_home(void);

int OLED_goto_line(uint8_t line);
int OLED_pos(uint8_t line, uint8_t column);

int OLED_clear_line(uint8_t line);
int OLED_clear(void);
int OLED_print_char(char c);
int OLED_print(char *data);
int OLED_draw_circle(uint8_t x, uint8_t y, uint8_t r);

int OLED_nameprompt(void);
int OLED_game(int diff);
void my_delay_ms(int n);

void OLED_refresh(void);

#endif