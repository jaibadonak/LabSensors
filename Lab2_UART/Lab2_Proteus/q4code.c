/*void usart_init(uint16_t ubrr) {  //Q4.3
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // async, 8N1
}
void usart_transmit(uint8_t data) { //Q4.4
    while ( !(UCSR0A & (1 << UDRE0)) );  // spin until UDRE0 == 1
    UDR0 = data;
}
*/
#define F_CPU 2000000UL     // Q4.5
#include <avr/io.h>
#include <util/delay.h>

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);

int main(void) {
    usart_init(12);                 // UBRR = 12 for 9600 baud @ 2 MHz

    uint16_t number = 345;
    while (1) {
        uint8_t hundreds = number / 100;         // 3
        uint8_t tens     = (number / 10) % 10;   // 4
        uint8_t ones     = number % 10;          // 5

        usart_transmit(hundreds + '0');     // '0' = 0x30, shifts digit to ASCII
        usart_transmit(tens     + '0');
        usart_transmit(ones     + '0');
        usart_transmit(' ');                // separator so repeats read as "345 345 345 ..."

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
