#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>

// Initialise Timer0
void timer0_init();

// Check if Timer0 has reached comparison value.
// Clear compare flag and return 1 if reached.
// Otherwise, return 0.
uint8_t timer0_check_clear_compare();

#endif