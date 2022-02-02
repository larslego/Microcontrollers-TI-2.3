/*
 * OpdrachtB5.c
 *
 * Created: 2-2-2022 13:45:48
 * Author : Larsl
 */ 


#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms(1);		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
	DDRD = 0b11111111;		// All pins PORTD are set to output

	while (1) {
		for (int i = 0; i < 8; i++) {
			// Enable new leading LED
			wait(50);
			PORTD |= 0x01 << i;
		}
		for (int i = 0; i < 8; i++) {
			// Disable trailing LED
			wait(50);
			PORTD &= ~(0x01 << i);
		}
	}
	
	return 1;
}

