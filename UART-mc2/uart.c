 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Ahmed Dwidar
 *
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

void UART_init(uint32 baud_rate)
{
	uint16 ubrr_value;

	SET_BIT(UCSRA,U2X);  //UCSRA (double transmition speed)

	SET_BIT(UCSRB,RXEN); //UCSRB (enable reciever and transmitter)
	SET_BIT(UCSRB,TXEN);

	SET_BIT(UCSRC,URSEL); // UCSRC(enable the register,8-bit char,1-bit stop,disable parity)
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);

	ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);

	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}
void UART_sendByte(const uint8 data)
{
	/*
	 * UDR = data;
	 * while(BIT_IS_CLEAR(UCSRA,TXC)){}
	 * SET_BIT(UCSRA,TXC);
	 */

	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/*
	 * (when UDR register not empty the flag iscleared)
	 is better  i will send the data and immediately det out when i call it again i would have finiched some codes
	 */
	UDR = data;
}
uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

		return UDR; //(once UDR register is filled the flag will be cleared)
}
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}
void UART_receiveString(uint8 *Str)
{

	uint8 i = 0;

	//Receive the first byte
	Str[i] = UART_recieveByte();

	// Receive the whole string until the '#'
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	// After receiving the whole string plus the '#', replace the '#' with '\0'
	Str[i] = '\0';
}

	/*
	 * uint8 i = 0;
	do
	{
		Str[i] = UART_recieveByte();
		i++;

	}while(Str[i] != '#');

	Str[i] = '\0';

*/
