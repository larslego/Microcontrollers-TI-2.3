/*
 * LCD.c
 *
 * Created: 9-2-2022 12:49:44
 *  Author: Larsl
 */ 
#include "LCD.h"

void switch_E() {
	PORTC |= (1<<E);
	_delay_ms(1);
	PORTC &= ~(1<<E);
}

void init() {
	// See table 13 from the HD44780U datasheet.
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// Step 2 Function set
	PORTC = D5;
	switch_E();

	// Step 3 (table 12)
	PORTC = D5;   // function set
	switch_E();
	PORTC = D7;
	switch_E();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	switch_E();
	PORTC = 0xF0;
	switch_E();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	switch_E();
	PORTC = 0x60;
	switch_E();
}

void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<RS);
	switch_E();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<RS);
	switch_E();
}

void lcd_write_string(char *str) {
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void display_text(char *str) {
	
}



void set_cursor(int position) {
	
}