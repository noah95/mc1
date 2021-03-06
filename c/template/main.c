/**
 *	filename: main.c
 *	Author: Noah Huetter
 *	Email:	noahhuetter@gmail.com 
 */

//================================================================================
// Includes
//================================================================================
#include "header.h"

//================================================================================
// Defines
//================================================================================
#define LEDS PORTC

#define BAUD (57600)
#define UBR_VAL ((F_CPU/16/BAUD)-1)


//================================================================================
// Funtion declarations
//================================================================================
void inti_send_buf();
int serial_putchar(char ch, FILE *unused);
void initIO ();


//================================================================================
// Main routine
//================================================================================
//
int main()
{	
	static FILE fd_stdout= FDEV_SETUP_STREAM(serial_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &fd_stdout;
	static FILE fd_lcdout= FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);
	FILE *LCD = &fd_lcdout;
	
	inti_send_buf();
	initIO();

	init_lcd();

	fprintf(LCD, "42 is the answer");

	LEDS=0x55;
//	sei();

	while(1){

		printf("Hello World\r\n");
		_delay_ms(1000);
		LEDS^=0xff;
 	}
}



//================================================================================
// Functions
//================================================================================

/**
 * @brief      Inits the serial send buffer
 */
void inti_send_buf()
{
		UBRR0L=UBR_VAL&0xFF;
		UBRR0H=(UBR_VAL>>8)&0xFF;
		UCSR0B=(1<<RXEN0)|(1<<TXEN0);
		UCSR0C=(3<<UCSZ00);
}

/**
 * @brief      Puts char on serial port
 *
 * @param[in]  ch      char
 * @param      unused  FILE stream
 *
 * @return     always 0
 */
int serial_putchar(char ch, FILE *unused)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=ch;
	return 0;
}

/**
 * @brief      Inits IO Ports
 */
void initIO () 
{
	DDRC = 0xff;
}
