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

