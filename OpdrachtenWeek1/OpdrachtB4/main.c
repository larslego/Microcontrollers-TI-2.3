/*
 * OpdrachtB4.c
 *
 * Created: 2/2/2022 12:40:26 PM
 * Author : berke
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for (int i=0; i<ms; i++) {
		_delay_ms(1);		// library function (max 30 ms at 8MHz)
	}
}

int main(void) {
	DDRD = 0b11111111;		// All pins PORTD are set to output

    while (1) {
		for (int i = 0; i < 8; i++) {
			wait(50);
			PORTD = 0x01 << i;
		}
		
		for (int i = 0; i < 8; i++) {
			wait(50);
			PORTD = 0x10 >> i;
		}
    }
	
	return 1;
}

