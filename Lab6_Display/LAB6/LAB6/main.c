#define F_CPU 2000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

/*
 *  Part 1: Multiplexing
 *
 * Segment mapping:
 *   PC0..PC5 = a..f
 *   PB4 = g
 *   PB5 = LED
 *
 * Digit enables:
 *   PB0 = Ds1
 *   PB1 = Ds2
 *   0 = enabled, 1 = disabled
 *
 */

#define DS1_PIN PB0
#define DS2_PIN PB1
#define SEG_G_PIN PB4
#define LED_PIN PB5

static const uint8_t seg_pattern[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66,
    0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

volatile uint8_t counter = 0;
static volatile uint8_t next_digit = 0;

static void output_digit(uint8_t pattern)
{
    PORTC = (PORTC & 0xC0) | (pattern & 0x3F);

    if (pattern & 0x40)
        PORTB |= (1 << SEG_G_PIN);
    else
        PORTB &= ~(1 << SEG_G_PIN);
}

static void init_display(void)
{
    DDRC |= 0x3F;
    DDRB |= (1 << DS1_PIN) | (1 << DS2_PIN) |
            (1 << SEG_G_PIN) | (1 << LED_PIN);

    PORTB |= (1 << DS1_PIN) | (1 << DS2_PIN);
    output_digit(0x00);
}

static void init_timer0_10ms(void)
{
    TCCR0A = (1 << WGM01);
    OCR0A = 77;
    TCCR0B = (1 << CS02);
    TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
    uint8_t digit_value;

    // Blank both digits before changing segment data.
    PORTB |= (1 << DS1_PIN) | (1 << DS2_PIN);

    if (next_digit == 0)
    {
        digit_value = counter / 10;
        output_digit(seg_pattern[digit_value]);
        PORTB &= ~(1 << DS1_PIN);
        next_digit = 1;
    }
    else
    {
        digit_value = counter % 10;
        output_digit(seg_pattern[digit_value]);
        PORTB &= ~(1 << DS2_PIN);
        next_digit = 0;
    }
}

int main(void)
{
    init_display();
    init_timer0_10ms();
    sei();

    while (1)
    {
        _delay_ms(1000);

        counter++;
        if (counter > 99)
            counter = 0;
    }
}
