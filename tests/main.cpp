#include<avr/io.h>

// #define F_CPU 16000000UL
#include<util/delay.h>

#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h> 
#include <avr/pgmspace.h>

#include "../HidBus/UART/AvrUart.hpp"
#include "../HidBus/HidBus.hpp"
// #include "../HidBus/HID_UNIT_CONFIG.hpp"

int main()
{
	UART::init(203);
	DDRD |= (1<<5);

	/*Allow interrupts*/
	asm("sei");

	PORTD |= (1<<5);
	_delay_ms(1000);
	PORTD &= ~(1<<5);

	while(true);
	return 0;
};

ISR(USART_RXC_vect)
{
	HidBus::HidPackage package = {0,0,0,0};
	switch(HidBus::RecieveData(package))
	{
		case 0:
			switch(package.DATA[0])
			{
				case LED_ON:
					PORTD |= (1<<5);
					/* 00 00 01 00 01 00 30 03 -- package to call this command*/
				break;

				case LED_OFF:
					PORTD &= ~(1<<5);
					/* 00 00 01 00 01 00 30 02 -- package to call this command*/
				break;
			};
		break;
	};
};