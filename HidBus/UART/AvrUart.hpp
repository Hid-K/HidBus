#ifndef AVR_UART_H
#define AVR_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h> 

// #ifndef F_CPU
// 	#error "No F_CPU defined for AvrUart.hpp"
// #endif
namespace UART {
	#if defined(__AVR_ATmega8A__)
	void init(unsigned int speed);

	#elif defined(__AVR_ATmega16__)
	void init( unsigned int ubrr);
	#else
		#error "AvrUart.hpp: device type not defined"
	#endif

	int read(void * buf, unsigned int dataLength);

	int write(const void * buf, unsigned int dataLength);
};
#endif