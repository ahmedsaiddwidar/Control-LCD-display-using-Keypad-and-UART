/*
 * mc1_main.c
 *
 *  Created on: Jul 9, 2023
 *      Author: Ahmed Dwidar
 */
#include "keypad.h"
#include "uart.h"
#include <util/delay.h>

int main(void)
{
	uint8 key;

	UART_init(9600);

	while(1)
	{
		key = KEYPAD_getPressedKey();

		UART_sendByte(key);

		_delay_ms(500);
	}
}

