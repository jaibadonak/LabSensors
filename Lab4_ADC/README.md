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
