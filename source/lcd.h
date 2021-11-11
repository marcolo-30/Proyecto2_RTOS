/*
 * lcd.h
 *
 *  Created on: 10 nov. 2021
 *      Author: User
 */

#ifndef LCD_H_
#define LCD_H_

extern void init_LCD_display();
extern void enable_click_routine();
extern void write_character(char render_char);
extern void write_line(char *line);
extern void clear_and_home();
extern void write_second_line();
extern void home();

#endif /* LCD_H_ */
