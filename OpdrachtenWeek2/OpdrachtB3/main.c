/*
 * OpdrachtB3.c
 *
 * Created: 9-2-2022 11:07:26
 * Author : Larsl
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

int number = 0;

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

const unsigned char Numbers[16] = {
  // dPgfedcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b11111100, // B
	0b00111001, // C
	0b01111100, // D
	0b01111001, // E
	0b01110001 // F
};

void writeDigit(int digit) {
	if (digit > 15) {
		PORTC = Numbers[15];
	} else {
		PORTC = Numbers[digit];
	}
}

int main(void)
{
	// Init I/O
	DDRD = 0b11111100;		// PORTD(7:3) output, PORTD(2:0) input
	
	// Init I/O
	DDRC = 0xFF;
	
	while (1) {
		wait(500);
		
		if (PIND == 0x01) {
			number++;
		} else if (PIND == 0x02) {
			number--;
		} else if (PIND == 0x03) {
			number = 0;
		}
		if (number < 0) number = 15;
		if (number > 15) number = 0;
		writeDigit(number);
	}
}

