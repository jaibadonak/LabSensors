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

### 1.3 - Simultaneous channels

One. The channels share one ADC, so voltage and current are sampled sequentially.

### 1.4 - Conversion time

A normal conversion takes 13 ADC clock cycles:

```
t_conversion = 13 / 125000 = 104 us
```

The first conversion after enabling the ADC takes 25 cycles, or 200 us, excluding the wait for a clock edge.

### 1.5 - Slowest stage

Successive approximation. The ADC must settle and compare successive trial voltages to determine all ten bits.

### 1.6 -Expected ADC count

```
N ≈ 1024 × V_analog / 5
```

The result is quantised to an integer and limited to 0–1023.

The lab's example uses 1023 for endpoint scaling; the datasheet uses 1024 for the ADC transfer relationship. At 3.35 V:

```
N ≈ 1024 × 3.35 / 5 = 686.08 ≈ 686
```

### 1.7 - Voltage resolution

```
Delta V = 5 / 1024 = 0.0048828125 V ≈ 4.883 mV/count
```

### 1.8 - Recommended ADC clock

50–200 kHz is the recommended range for maximum 10-bit resolution.

### 1.9 - Prescaler

```text
Prescaler = 2,000,000 / 125,000 = 16
```

Therefore, ADPS2:ADPS0 = 100.
