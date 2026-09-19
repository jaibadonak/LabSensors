#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Set PORTB as outputs
    DDRB = 0xFF;

    // Set PORTC and PORTD as inputs
    DDRC = 0x00;
    DDRD = 0x00;

    while (1)
    {
        // Turn LED ON (PB5 = 1)
        PORTB |= (1 << PB5);
        _delay_ms(375);

        // Turn LED OFF (PB5 = 0)
        PORTB &= ~(1 << PB5);
        _delay_ms(125);
    }
}