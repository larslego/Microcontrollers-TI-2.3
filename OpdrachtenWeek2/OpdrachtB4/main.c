/*
 * OpdrachtB4.c
 *
 * Created: 2/9/2022 11:46:40 AM
 * Author : berke
 */ 



#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>




typedef struct {
	unsigned char data;
	unsigned int delay ;
} ANIMATION_STRUCT;

ANIMATION_STRUCT pattern[3][2] = {
	{{0x01, 1000}, {0x08, 1000}},
	{{0x02, 1000}, {0x10, 1000}},
	{{0x04, 1000}, {0x20, 1000}}
};

/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void)
{
		DDRC = 0b11111111;					// PORTD all output
		
		while (1) {
			// Set index to begin of pattern array
			int index = 0;
			// as long as delay has meaningful content
			while( index < (sizeof pattern / sizeof pattern[0]) ) {
				// Write data to PORTD
				PORTC = pattern[index][0].data | pattern[index][1].data;
				// wait
				wait(pattern[index][0].delay);
				// increment for next round
				index++;
			}
		}

		return 1;
}

