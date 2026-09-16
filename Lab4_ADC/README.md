<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 4 Notes

Keep a digital log of your work using the readme file where appropriate.

## Pre-lab: Digital I/O

### P.1 — Purpose of DDRn

The Data Direction Register configures each pin of port n:

- 1: output.
- 0: input.

```c
DDRB = 0xFF;
DDRC = 0x00;
DDRD = 0x00;
```

### P.2 — LED pin
For 1 Hz flashing with 50% duty cycle:

```c
#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0xFF;
    DDRC = 0x00;
    DDRD = 0x00;

    while (1) {
        PORTB |= _BV(PB5);
        _delay_ms(500);
        PORTB &= ~_BV(PB5);
        _delay_ms(500);
    }
}
```
