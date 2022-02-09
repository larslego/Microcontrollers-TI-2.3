/*
 * OpdrachtB2.c
 *
 * Created: 2/9/2022 10:33:51 AM
 * Author : berke
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int i = 0;

ISR( INT0_vect ) {
	i--;
	i = (i < 0 ? 7 : i);
	PORTC = (1<<i);
}


ISR( INT1_vect ) {
	i++;
	i = (i > 7 ? 0 : i);
	PORTC = (1<<i);
}


int main(void)
{
	DDRC = 0xFF; //Setting row to output
	DDRD = 0x00;
	
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0	

	sei();	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

