/*
 * OpdrachtB7.c
 *
 * Created: 2/8/2022 1:13:57 PM
 * Author : berke
 */ 
#define F_CPU 68e6
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

//Possible states..
typedef enum {START, STATE_1, STATE_2, STATE_3, END} ENUM_STATES;
typedef enum {PORT_D7, PORT_D6, PORT_D5, NONE} ENUM_SWITCHES;

//Active state..	
ENUM_STATES active = START;

//Holds possible state change
typedef struct  
{
	ENUM_STATES begin;
	ENUM_SWITCHES key;
	ENUM_STATES target;
} STATE_CHANGE;

//Holds the state changes
STATE_CHANGE all_states[] = {
	//Start possibles
	{START, PORT_D6, STATE_1}, {START, PORT_D5, STATE_2}, 
		
	//State 1 possibles
	{STATE_1, PORT_D7, START}, {STATE_1, PORT_D5, STATE_2}, 
	
	//State 2 possibles	
	{STATE_2, PORT_D7, START}, {STATE_2, PORT_D6, STATE_1}, {STATE_2, PORT_D5, STATE_3},

	//State 3 possibles
	{STATE_3, PORT_D7, START}, {STATE_3, PORT_D5, END}, {STATE_3, PORT_D6, END}, 
		
	//End possibles
	{END, PORT_D7, START}
};

//Waiting function
void wait( int ms ){
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//Changes the active state
void change_active(ENUM_SWITCHES change){
	for (int i = 0; i < (sizeof all_states / sizeof all_states[0]); i++)
	{
		if (all_states[i].begin == active && all_states[i].key == change){
			active =  all_states[i].target;
			return;
		}	
	}
}

//Prints out active state
void print_active(){
	PORTC = 0x00;
	if (active == START){
		printf("start\n");
		PORTC = 0b00000001;
	} else if (active == END){
		printf("END\n");
		PORTC = 0b00010000;
	} else {
		printf("state_%d", (active == STATE_1 ? 1 : (active == STATE_2 ? 2 : 3)));
		PORTC = 1 << (active == STATE_1 ? 1 : (active == STATE_2 ? 2 : 3));
	}
}

ENUM_SWITCHES read_port(){
	if (PIND == (1 << 7)){;
		return PORT_D7;
	} else if (PIND == (1 << 6)){
		return PORT_D6;
	} else if (PIND == (1 << 5)){
		return PORT_D5;
	}
	return NONE;
}

int main(void)
{
	//Setup
	DDRD = 0b00000000;
	DDRC = 0b00011111;					// All pins PORTD are set to input 
	print_active();
			
	//Running
    while (1) 
    {
		wait(100);
		ENUM_SWITCHES pressed = read_port();
		if (pressed != NONE){
			change_active(pressed);
			print_active();
		}
    }
}

