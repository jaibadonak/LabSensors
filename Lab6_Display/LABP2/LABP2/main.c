
#define F_CPU 2000000UL    
#include <avr/io.h>
#include <util/delay.h>
#include "display.h"
#include <avr/interrupt.h>


#define SH_CP PC3
#define DS    PC4
#define SH_ST PC5
#define DS1   PD4
#define DS2   PD5
#define DS3   PD6
#define DS4   PD7

//global variable
volatile uint16_t number = 0;

void I0config() {
	DDRB = 0x00;
	DDRB |= (1 << PINB0 );
}


int main(void) {


	//WITH DECIMAL POINT
	timer0Config();
	I0config();
	init_display();
	init_display_digits();


    sei();
    while (1)
    {
			seperate_and_load_characters(number,4);
			number++;
			_delay_ms(250);
			if(number>9999){
			 number = 0;
			}

    }
}