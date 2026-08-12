#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);

int main(void) {
    /* --- Prime number generation --- */
    uint16_t primes[62];    // store up to 62 numbers (values up to 300)
    uint8_t  i = 0;         // position for next prime
    uint16_t N;             // number to check (up to 300)
    uint16_t j;             // divisor counter (up to 300)
    uint8_t  isPrime;       // flag

    for (N = 2; N <= 300; N++) {
        isPrime = 1;                    // set the flag

        for (j = 2; j < N; j++) {       // test divisors 2 through N-1
            if (N % j == 0) {           // evenly divisible -> not prime
                isPrime = 0;            // clear the flag
                break;
            }
        }

        if (isPrime) {                  // still set -> N is prime
            primes[i] = N;
            i++;
        }
    }

  

    while (1) {
        

        /* --- Q4.7: Transmit prime list (3-digit, comma+space separated) --- */
        for (uint8_t k = 0; k < i; k++) {
            hundreds = primes[k] / 100;
            tens     = (primes[k] / 10) % 10;
            ones     = primes[k] % 10;

            usart_transmit(hundreds + '0');
            usart_transmit(tens     + '0');
            usart_transmit(ones     + '0');
            usart_transmit(',');
            usart_transmit(' ');
        }

        _delay_ms(500);
    }
}

void usart_init(uint16_t ubrr) {
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_transmit(uint8_t data) {
    while ( !(UCSR0A & (1 << UDRE0)) );
    UDR0 = data;
}