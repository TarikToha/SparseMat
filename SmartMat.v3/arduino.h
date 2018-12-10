#ifndef ARDUINO_H
#define ARDUINO_H

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "adc.h"

uint16_t count_in, count_out;
char buffer[10];


void setup() {
	count_in = count_out = 0;

	DDRC = 0x01;
	DDRD = 0x80;
	PORTC= PORTD = 0;

	adc_init();
	lcd_init(LCD_DISP_ON);

	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_puts("In=");
	lcd_gotoxy(8,0);
	lcd_puts("Out=");
	lcd_gotoxy(0,1);
	lcd_puts("Total=");

}


void printInLCD(uint8_t x, uint8_t y, const char *s) {
	lcd_gotoxy(x,y);
	lcd_puts("    ");
	lcd_gotoxy(x,y);
	lcd_puts(s);
}


void printOutput(int direction){
		
	if (!direction) {
		PORTC = 0x01;
		count_in++;
		itoa(count_in, buffer, 10);
		printInLCD(4,0,buffer);
		itoa(count_in-count_out, buffer,10);
		printInLCD(7,1,buffer);

	} else if (direction == 1) {
		PORTD = 0x80;
		count_out++;
		itoa(count_out, buffer, 10);
		printInLCD(13,0,buffer);
		itoa(count_in-count_out, buffer,10);
		printInLCD(7,1,buffer);

	} else {
		PORTC = PORTD = 0;
	}

}



#endif