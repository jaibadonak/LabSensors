#include "display.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define SH_CP PC3
#define DS    PC4
#define SH_ST PC5
#define DS1   PD4
#define DS2   PD5
#define DS3   PD6
#define DS4   PD7

//WITHOUT DECIMAL POINT
const uint8_t seg_val[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //0,1,2,3,4,5,6,7,8,9

//4 characters to be displayed on Ds1 to Ds4
static volatile uint8_t disp_characters[4]={0,0,0,0};

//The current digit (e.g the 1's, the 10's) of the 4-digit number we're displaying
static volatile uint8_t disp_pos = 0;


ISR (TIMER0_COMPA_vect) {

	PORTD |= (1<<DS1) | (1<<DS2) |(1<<DS3) | (1<<DS4);
	send_next_character_to_display();
	PORTD &= ~(1 << (DS4 - disp_pos)); //since consecutive, it will cycle

	disp_pos++; //since static, it remembers it's value.
	if(disp_pos > 3) disp_pos = 0; //reset per number.
}



void timer0Config() {
	TCCR0A |= (1<<WGM01); //CTC MODE
	TCCR0B |= (1<<CS02); //prescaler to 256
	OCR0A = 77;
	TIMSK0 |= (1<<OCIE0A);
}

void init_display() {
	DDRC |= (1<<SH_CP) | (1<<DS) | (1<<SH_ST);
}


void init_display_digits() {
	DDRD = 0x00;
	DDRD |= (1<<DS1) | (1<<DS2) | (1<<DS3) | (1<<DS4);
}

//It gets a singular number's segment pattern, breaks into on and off's and logs those changes loading them into the D-flip flops,
//essentially pre-loading the number and confirms it with the latch
void send_next_character_to_display(void) {
	uint8_t oneOrZero;
	PORTC &= ~(1<<SH_CP) & ~(1<<SH_ST); //turn of both bits
	for (int8_t i = 7; i >= 0; i--) {
		oneOrZero = (disp_characters[disp_pos]>>i) & 0x01; // Isolating each bit of value from the MSB to the LSB.
		if (oneOrZero) PORTC |= (1<<DS); //if bit one, then log one
		else      PORTC &= ~(1<<DS); //else log 0.
		PINC = (1<<SH_CP);//toggles clock pulse to "confirm changes"
		PINC = (1<<SH_CP);//toggles clock pulse back to off for rising edge(for next character)
	}
	PINC = (1<<SH_ST);//toggle latch to latch the output
	PINC = (1<<SH_ST);//needs to be off for next time to have rising edge
}


//for grabbing number and seperating into an array, then into its seg_value, for e.g 1234 = {0xff,0xff,0xff,0xff}
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos) {
	uint16_t currentValue = number;
	int8_t i = 0; //needs to bne int so it get go negative
	uint8_t disp_characters_temp = 0;

	//stores each digit, thousands on the left
	while (i < 4)  {
		disp_characters_temp = currentValue % 10;
		currentValue /= 10;
		disp_characters[i] = seg_val[disp_characters_temp];
		i++;

	}



}