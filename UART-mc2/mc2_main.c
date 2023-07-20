/*
 * mc2_main.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Ahmed Dwidar
 */
#include "LCD_DRIVER1.h"
#include "uart.h"

int main(void)
{
	uint8 received_key;

	LCD_init();
	UART_init(9600);

	while(1)
	{
		received_key = UART_recieveByte();

		if((received_key <= 9) && (received_key >= 0))
		{
			LCD_intgerToString(received_key);
		}
		else
		{
			LCD_displayCharacter(received_key);
		}
	}
}

