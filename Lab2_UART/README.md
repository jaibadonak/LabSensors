<img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 3 Notes

Keep a digital log of your work using the readme file where appropriate.

# Pseudo Code for Pre-Lab

- You can use a simple algorithm that iterates through all the numbers up to 300, and checks if they can be exactly divided by numbers smaller than it using the modulo operator
- Here is an example algorithm you could use
> - Create an array that could store 62 numbers (note the variable type should allow storing integers up to 300)
> - Create a variable *i* to hold the position in the array where you will store next prime number and initialize this to 0
> - Create a variable *N* to hold the number we are going to check and see if it is a prime number (note the variable type should allow storing integers up to 300)
> - Create a counter variable *j* to iterate through numbers up to the number we want to check if it is a prime number (note the variable type should allow storing integers up to 300)
> - Create a variable *isPrime* that can be used as a flag to indicate its a prime number
> - In a 1st *for loop* increment *N* from 2 to 300 and within this loop
>   - Set the flag *isPrime*
>   - In a 2nd *for loop* increment *j* from 2 to N-1 and within this loop
>   - If *N % j* is 0 then *N* is not a prime number so clear *isPrime* and *break* the *for loop*
>   - If *isPrime* is set at the end of 2nd *for loop* then store *N* in the *i* position of the array and increment *i*
> - Continue with the 1st *for loop* until N reach 300 

QP.1:
293 or 0x0125
QP.2:
Hmm

Q1
i) Signals the beginning of a frame. The line idles high (1), and the start bit pulls it low (0) for one bit period. This falling edge tells the receiver “a frame is coming, start sampling now” and gives it a timing reference to align its clock with the incoming bits (since UART is asynchronous, there’s no shared clock line).

ii) A basic error-detection bit. It’s set so the total number of 1s in the data (plus the parity bit) is either even (even parity) or odd (odd parity), depending on which scheme is agreed. The receiver recomputes parity on the received bits, a mismatch means at least one bit flipped in transit. It only catches odd numbers of bit errors and can’t correct them, but it’s cheap. Can be disabled.

iii)Marks the end of the frame by returning the line to the idle-high state for one (or two) bit periods. This guarantees a known line state before the next start bit’s falling edge, so the receiver can reliably detect the next frame. It also gives the receiver a small buffer of time to finish processing the current byte.

iv)The signalling rate, bits per second. It defines how long each bit lasts (at 9600 baud, one bit = 1/9600 s is 104 µs). Both ends must use the same baud rate so the receiver samples each bit near its midpoint; even a few percent mismatch accumulates across the frame and causes the receiver to sample the wrong bit.
Q2.1

| Setting Name | Register and Bits | Purpose | Do we need it? | Initialisation/ Runtime |
|---|---|---|---|---|
| Receive Complete | UCSR0A RXC0 (Bit 7) | A flag indicating when the USART has received a complete packet that is ready to be read | No | - |
| Tx Data Register Empty | UCSR0A UDRE0 (Bit 5) | A flag indicating that the USART is ready to send another packet and it is safe to load data | Yes | Runtime |
| Transmit Complete | UCSR0A TXC0 (Bit 6) | A flag indicating that the entire frame in the transmit shift register has been shifted out and there is no new data in the transmit buffer | No | - |
| Mode Selection | UCSR0C UMSEL01:0 (Bits 7:6) | Selects the operating mode of the USART: asynchronous USART, synchronous USART, or master SPI | Yes | Initialisation |
| Character Size | UCSR0C UCSZ01:0 (Bits 2:1) and UCSR0B UCSZ02 (Bit 2) | Sets the number of data bits per frame (5, 6, 7, 8, or 9 bits) | Yes | Initialisation |
| Clock Polarity | UCSR0C UCPOL0 (Bit 0) | Sets the relationship between data output change and data input sample on the XCK clock; only used in synchronous mode | No | - |
| Baud Rate | UBRR0H (Bits 3:0) and UBRR0L (Bits 7:0) | 12-bit register that sets the USART baud rate by dividing the system clock | Yes | Initialisation |
| Receiver Enable | UCSR0B RXEN0 (Bit 4) | Enables the USART receiver and overrides the normal port operation of the RxD pin | Yes | Initialisation |
| Transmitter Enable | UCSR0B TXEN0 (Bit 3) | Enables the USART transmitter and overrides the normal port operation of the TxD pin | Yes | Initialisation |
| Parity Mode | UCSR0C UPM01:0 (Bits 5:4) | Enables and sets the type of parity generation and check: disabled, even parity, or odd parity | Yes | Initialisation |
| Parity Error | UCSR0A UPE0 (Bit 2) | A flag indicating that the next frame in the receive buffer had a parity error when received, valid only when parity checking is enabled | No | - |

Q2.2:
Using the asynchronous normal mode formula from the datasheet (U2X0 = 0):

UBRR = \frac{f_{osc}}{16 \times BAUD} - 1 = \frac{2,000,000}{16 \times 9600} - 1 = 13.02 - 1 \approx 12.02

So UBRR0 = 12.

Q2.3:
The UBRR is a 12-bit value (bits 11:0), but the ATmega328P is an 8-bit AVR — every I/O register is only 8 bits wide. A 12-bit value therefore can't fit in a single register, so it's split into a low byte (UBRR0L, bits 7:0) and a high nibble (UBRR0H, bits 3:0, with bits 7:4 reserved). This is the same pattern the AVR uses for other >8-bit peripheral values like the 16-bit timer counters (TCNT1H/L) and OCR/ICR registers.

Q2.4:
**UCSR0A**

| Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 |
|-------|-------|-------|-------|-------|-------|-------|-------|
| RXC0  | TXC0  | UDRE0 | FE0   | DOR0  | UPE0  | U2X0  | MPCM0 |
| 0     | 0     | 0     | 0     | 0     | 0     | 0     | 0     |

**UCSR0B**

| Bit 7  | Bit 6  | Bit 5  | Bit 4 | Bit 3 | Bit 2  | Bit 1 | Bit 0 |
|--------|--------|--------|-------|-------|--------|-------|-------|
| RXCIE0 | TXCIE0 | UDRIE0 | RXEN0 | TXEN0 | UCSZ02 | RXB80 | TXB80 |
| 0      | 0      | 0      | 1     | 1     | 0      | 0     | 0     |

**UCSR0C**

| Bit 7   | Bit 6   | Bit 5 | Bit 4 | Bit 3 | Bit 2  | Bit 1  | Bit 0  |
|---------|---------|-------|-------|-------|--------|--------|--------|
| UMSEL01 | UMSEL00 | UPM01 | UPM00 | USBS0 | UCSZ01 | UCSZ00 | UCPOL0 |
| 0       | 0       | 0     | 0     | 0     | 1      | 1      | 0      |

Q2.5:
i)
if( UCSR0A & (1 << UDRE0) ) {

ii)
UCSR0B |= (1 << TXEN0);

iii)
UCSR0C &= ~(1 << UCPOL0);

Q3:
char: 1 byte
int: 2 bytes
int_8t: 1 byte
uint_8t: 1 byte
uint_16t: 2 byte
float: 4 bytes
