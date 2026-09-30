/*
 * display.h
 
 */


#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>      // for uint8_t / uint16_t

void init_display(void);
void init_display_digits(void);
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos);
void send_next_character_to_display(void);
void timer0Config(void);

#endif