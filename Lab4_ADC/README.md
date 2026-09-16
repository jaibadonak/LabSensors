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
## Part 1

### 1.1 - Definitions

| Term | Answer |
|---|---|
| Channel selection | A multiplexer connects one selected analogue input to the shared ADC. |
| Sample and hold | Captures the input voltage at a particular instant and holds it steady during conversion. |
| Successive approximation | Tests the result one bit at a time, from most significant to least significant, using a DAC and comparator. |
| Reference voltage | The voltage that sets the ADC's conversion scale and upper input range. |
| Sampling rate | The number of samples acquired per second. |
| Resolution | The number of distinguishable output levels, or the voltage represented by one count. A 10-bit ADC has 2^10 = 1024 levels. |

### 1.2 - Number of input channels

Eight external channels, ADC0–ADC7, on the ATmega328PB and 32-pin ATmega328P. The 28-pin ATmega328P exposes only six external channels. Internal sources can also be selected.
