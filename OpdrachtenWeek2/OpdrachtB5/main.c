/*
 * OpdrachtB5.c
 *
 * Created: 9-2-2022 12:48:36
 * Author : Larsl
 */ 

#include "LCD/LCD.h"

int main(void)
{
	init();
	display_text("Joe Mama");
	
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(10);
    }
}

