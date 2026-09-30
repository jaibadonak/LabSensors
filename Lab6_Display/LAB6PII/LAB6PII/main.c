#include "display.h"
#include <avr/io.h>

/*
 * Q2.2
 *
 * Since PB0/PB1 are now reserved for Ds1/Ds2, the shift-register control
 * lines are assigned here to spare pins and should be changed if the
 * Proteus schematic uses different connections.
 *
 * 74HC595:
 *   PD0 = SH_DS
 *   PD1 = SH_CP
 *   PD2 = SH_ST
 *
 * Digit cathodes:
 *   PB0 = Ds1
 *   PB1 = Ds2
 *   PB2 = Ds3
 *   PB3 = Ds4
 *
 * Digit enable is active-low.
 */

#define SH_DS_PIN PD0
#define SH_CP_PIN PD1
#define SH_ST_PIN PD2

#define DS1_PIN PB0
#define DS2_PIN PB1
#define DS3_PIN PB2
#define DS4_PIN PB3

static void pulse_pin(volatile uint8_t *port, uint8_t pin)
{
    *port |= (1 << pin);
    *port &= ~(1 << pin);
}

void init_display(void)
{
    DDRD |= (1 << SH_DS_PIN) | (1 << SH_CP_PIN) | (1 << SH_ST_PIN);
    DDRB |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN) | (1 << DS4_PIN);

    PORTD &= ~((1 << SH_DS_PIN) | (1 << SH_CP_PIN) | (1 << SH_ST_PIN));

    PORTB |= (1 << DS1_PIN) | (1 << DS2_PIN) | (1 << DS3_PIN);
    PORTB &= ~(1 << DS4_PIN);
}

void send_next_character_to_display(void)
{
    uint8_t character = 0x07; // display "7"

    PORTD &= ~((1 << SH_CP_PIN) | (1 << SH_ST_PIN));

    for (int8_t bit = 7; bit >= 0; bit--)
    {
        if (character & (1 << bit))
            PORTD |= (1 << SH_DS_PIN);
        else
            PORTD &= ~(1 << SH_DS_PIN);

        pulse_pin(&PORTD, SH_CP_PIN);
    }

    pulse_pin(&PORTD, SH_ST_PIN);
}
