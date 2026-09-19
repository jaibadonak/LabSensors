#include "led.h"

#include <avr/io.h>

void led_toggle()
{
    // Toggle LED connected to PB5
    PORTB ^= (1 << PB5);
}