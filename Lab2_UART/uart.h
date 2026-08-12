#ifndef UART_H_
#define UART_H_

void usart_init(uint16_t ubrr);

void usart_transmit(uint8_t data);

#endif