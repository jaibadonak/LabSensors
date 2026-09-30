#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/*
 * Stage 1 - Pre-Lab
 *
 * Common-cathode two-digit display.
 *
 * Segment mapping:
 *   PC0 = Sa
 *   PC1 = Sb
 *   PC2 = Sc
 *   PC3 = Sd
 *   PC4 = Se
 *   PC5 = Sf
 *   PB4 = Sg
 *   PB5 = LED
 *
 * Digit enables:
 *   PB0 = Ds1, PB1 = Ds2
 *   0 = enabled, 1 = disabled
 *
 * Push button:
 *   PB7, active-low with internal pull-up
 */

#define DS1_PIN PB0
#define DS2_PIN PB1
#define BUTTON_PIN PB7

#define SEG_A PC0
#define SEG_B PC1
#define SEG_C PC2
#define SEG_D PC3
#define SEG_E PC4
#define SEG_F PC5
#define SEG_G PB4
#define LED_PIN PB5

static const uint8_t seg_pattern[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

static void output_digit(uint8_t pattern)
{
    // a..f are on PC0..PC5.
    PORTC = (PORTC & 0xC0) | (pattern & 0x3F);

    // g is bit 6 of the segment pattern, but physically on PB4.
    if (pattern & 0x40)
        PORTB |= (1 << SEG_G);
    else
        PORTB &= ~(1 << SEG_G);
}

static void init_io(void)
{
    // PC0..PC5 as outputs for segments a..f.
    DDRC |= 0x3F;

    // PB0/PB1 = digit enables, PB4 = segment g, PB5 = LED.
    DDRB |= (1 << DS1_PIN) | (1 << DS2_PIN) |
            (1 << SEG_G) | (1 << LED_PIN);

    // PB7 as input with pull-up.
    DDRB &= ~(1 << BUTTON_PIN);
    PORTB |= (1 << BUTTON_PIN);

    // Disable Ds1, enable Ds2.
    PORTB |= (1 << DS1_PIN);
    PORTB &= ~(1 << DS2_PIN);

    output_digit(seg_pattern[0]);
}

static uint8_t button_pressed(void)
{
    return !(PINB & (1 << BUTTON_PIN));
}

int main(void)
{
    init_io();

    uint8_t count = 0;

    while (1)
    {
        output_digit(seg_pattern[count]);

        for (uint8_t i = 0; i < 10; i++)
        {
            _delay_ms(100);

            if (button_pressed())
            {
                count = 0;
                output_digit(seg_pattern[0]);

                while (button_pressed())
                    _delay_ms(10);

                break;
            }

            if (i == 9)
            {
                count++;
                if (count > 9)
                    count = 0;
            }
        }
    }
}
