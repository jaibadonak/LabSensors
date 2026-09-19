#include timer0.h
#include led.h

#include avrio.h
#include stdint.h

void timer0_init()
{
     Set Timer0 to CTC mode (WGM020 = 010)
    TCCR0A = (1  WGM01);

     Set compare value for approximately 10 ms
    OCR0A = 77;

     Clear Timer0 counter
    TCNT0 = 0;

     Clear any existing compare match flag
    TIFR0 = (1  OCF0A);

     Start Timer0 with prescaler of 256
    TCCR0B = (1  CS02);
}

uint8_t timer0_check_clear_compare()
{
     Check if compare match A flag is set
    if (TIFR0 & (1  OCF0A))
    {
         Clear compare match flag by writing 1
        TIFR0 = (1  OCF0A);

        return 1;
    }

    return 0;
}