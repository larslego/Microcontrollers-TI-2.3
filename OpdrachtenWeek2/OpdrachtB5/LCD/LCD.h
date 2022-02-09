/*
 * LCD.h
 *
 * Created: 9-2-2022 12:49:54
 *  Author: Larsl
 */ 

#define RS 0x04 // Select registers 0: Instruction, 1: Data
#define E 0x08 // Starts data and read/write
#define D4 0x10 
#define D5 0x20
#define D6 0x40
#define D7 0x80

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init();
void display_text(char *str);
void set_cursor(int position);
void lcd_write_string(char *str);
