#define F_CPU 2000000UL

#include <avr/io.h>
#include <stdint.h>

#include "timer0.h"
#include "led.h"

int main(void)
{
    // Set LED pin PB5 as OUTPUT
    DDRB |= (1 << PB5);

    // Set PORTC and PORTD as INPUTS
    DDRC = 0x00;
    DDRD = 0x00;

    // Initialise Timer0
    timer0_init();

    while (1)
    {
        if (timer0_check_clear_compare())
        {
            led_toggle();
        }
    }
}