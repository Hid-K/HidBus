#include "AvrUart.hpp"

#if defined(__AVR_ATmega8A__)
void UART::init(unsigned int speed)
{
	UBRRH = (unsigned char)(speed>>8);
	UBRRL = (unsigned char)speed;
	UCSRB=(1<<RXEN)|( 1<<TXEN); //Enabling UART recieve and transmitt
	UCSRB |= (1<<RXCIE); //Allowing interrupts, while transmitting
	UCSRA |= (1<<U2X); 
	UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
};

#elif defined(__AVR_ATmega16__)
void UART::init( unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB=(1<<RXEN)|( 1<<TXEN); //Enabling UART recieve and transmitt
	UCSRB |= (1<<RXCIE); //Allowing interrupts, while transmitting
	UCSRA |= (1<<U2X);
	UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
};
#else
	#error "AvrUart.hpp: device type not defined"
#endif

int UART::read(void * buf, unsigned int dataLength)
{
	for(unsigned int i = 0; i<dataLength; ++i)
	{
		while( !(UCSRA & (1<<RXC)) ); //Waiting for recieve buffer clear
		((unsigned char *)(buf))[i] = UDR;
	};
	return 0;
};

int UART::write(const void * buf, unsigned int dataLength)
{
	for (unsigned int i = 0; i < dataLength; ++i)
	{
		while ( !(UCSRA & (1<<UDRE)) ); //Waiting for recieve buffer clear
		UDR = ((const unsigned char *)(buf))[i];
	};
	return 0;
};