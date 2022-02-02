/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** knipper.c
**
** Beschrijving:	Toggle even en oneven leds PORTD  
** -------------------------------------------------------------------------*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>


/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
*******************************************************************/
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void ) {
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
*******************************************************************/

	DDRD = 0b11111111;			// All pins PORTD are set to output 
	DDRC = 0b00000000;			// All pins PORTC are set to input 
	
	int speed = 1;
	int count = 0;
	
	while (1) {
		//Button logic
		if (PINC == 0x01){
			if (speed == 1){
				speed = 4;
			} else {
				speed = 1;
			}
			wait(200);
		}
		
		//Speed logic
		if (count > speed * 1000){
			PORTD  =0x80;
			count = 0;
		} else if (count > speed * 500){
			PORTD =0x00;

		}
		
		//Delay logic
		count = count +  10;
		wait(10);
	}

	return 1;
}

