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
        PORTB |= (1 << PB5);
        _delay_ms(500);
        PORTB &= ~(1 << PB5);
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

## Part 2

### 2.1 0- Reference-voltage options

| REFS1:REFS0 | Reference |
|---|---|
| 00 | External voltage applied to AREF |
| 01 | AVCC, with a capacitor at AREF |
| 10 | Reserved |
| 11 | Internal nominal 1.1 V reference |

AVCC is appropriate for the 0–5 V signals. The internal 1.1 V reference would cause readings above 1.1 V to saturate.

### 2.2 - Initial register values

Configuration: ADC2, AVCC reference, right-adjusted result, polling, single conversions, prescaler 16.

| Register | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|---|---|---|---|---|---|---|---|---|
| ADMUX names | REFS1 | REFS0 | ADLAR | Reserved | MUX3 | MUX2 | MUX1 | MUX0 |
| Values | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 |
| ADCSRA names | ADEN | ADSC | ADATE | ADIF | ADIE | ADPS2 | ADPS1 | ADPS0 |
| Values | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 0 |
| ADCSRB names | Reserved | ACME | Reserved | Reserved | Reserved | ADTS2 | ADTS1 | ADTS0 |
| Values | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

```c
ADMUX  = 0x42;
ADCSRA = 0x84;
ADCSRB = 0x00;
```

These are initial values following reset. ADIF is a flag cleared by writing one, not zero.

### 2.3- adc_init()

Included with the complete ADC module under 3.5 below.

## Part 3: Reading da ADC

### 3.1 - Select ADC1 without changing other settings

```c
ADMUX = (ADMUX & 0xF0) | 0x01;
```

This replaces only MUX3:0.

### 3.2 - Start conversion

Set ADSC in ADCSRA.

```c
ADCSRA |= (1 << ADSC);
```

### 3.3 - Detect completion

For single-conversion mode:

- ADSC == 0: conversion finished.
- ADIF == 1: a conversion-complete event occurred.

When polling ADIF, clear any previous completion flag before starting the next conversion.

### 3.4 - Y two data registers?

The result is 10 bits, but each register holds 8 bits.

With ADLAR = 0:

- ADCL contains result bits 7–0.
- ADCH contains result bits 9–8.

U should read ADCL first, then ADCH, to obtain a consistent result.

### 3.5 - ADC module, including 2.3 and 4.1

adc.h:

```c
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);
uint16_t adc_read(uint8_t channel);
uint16_t adc_convert_mv(uint16_t value);

#endif
```

adc.c:

```c
#include <avr/io.h>
#include "adc.h"

void adc_init(void)
{
    // ADC0, ADC1 and ADC2: inputs, with pull-ups disabled.
    DDRC  &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));
    PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));

    ADMUX  = (1 << REFS0) | (1 << MUX1);  // AVCC, ADC2
    ADCSRB = 0;
    ADCSRA = (1 << ADEN) | (1 << ADPS2);  // Enable, divide by 16

    DIDR0 |= (1 << ADC0D) | (1 << ADC1D) | (1 << ADC2D);
}

uint16_t adc_read(uint8_t channel)
{
    // Caller supplies an available external channel, 0–7.
    ADMUX = (ADMUX & 0xF0) | (channel & 0x07);

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC)) {
    }

    uint8_t low  = ADCL;
    uint8_t high = ADCH;

    return ((uint16_t)high << 8) | low;
}

uint16_t adc_convert_mv(uint16_t value)
{
    // Use a 32-bit intermediate and round to nearest millivolt.
    return (uint16_t)(((uint32_t)value * 5000UL + 512UL) / 1024UL);
}
```

## Part 4: Processing dataa

### 4.1 - Conversion to millivolts

Pseudocode:

1. Receive the raw ADC count.
2. Convert it to a 32-bit value before multiplication.
3. Multiply by the reference voltage in millivolts.
4. Divide by 1024, rounding if required.
5. Return the result in millivolts.

```text
V_mV ≈ N × 5000 / 1024
```

Example: N = 512 gives 2500 mV.

For the initial ADC2 test:

```c
while (1) {
    measured_mv = adc_convert_mv(adc_read(2));
    _delay_ms(1);
}
```

This has around 1.104 ms between samples, plus software overhead. A 1 ms delay after conversion does not produce an exact 1 ms sampling period.

