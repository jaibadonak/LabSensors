/*
 * LABP2.c
 *
 * Created: 30/09/2026 4:09:53 pm
 * Author : jnie221
 */ 

#define F_CPU 2000000UL

#include "display.h"

int main(void)
{
	init_display();
	send_next_character_to_display();

	while (1)
	{
	}
}
