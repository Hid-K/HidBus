// #ifdef HID_UART_BUS_H
// #define HID_UART_BUS_H

#include "UART/AvrUart.hpp"
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h> 
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <string.h>

namespace HidBus {

	#include "HID_UNIT_CONFIG.hpp"

	struct HidPkgHeader
	{
		unsigned int SRC_UID;
		unsigned int DEST_UID;
		unsigned int DATALen;
		unsigned char crc;
	};

	struct HidPackage
	{
		HidPkgHeader header;
		unsigned char DATA[128];
	};

	const unsigned char CRC7_POLY = 0x91;

	unsigned char getCRC(const unsigned char * message, unsigned char dataLen)
	{
	  unsigned char i, j, crc = 0;
	 
	  for (i = 0; i < dataLen; i++)
	  {
	    crc ^= message[i];
	    for (j = 0; j < 8; j++)
	    {
	      if (crc & 1)
	        crc ^= CRC7_POLY;
	      crc >>= 1;
	    }
	  }
	  return crc;
	};

	void HidSendData(const unsigned char * data, unsigned int dataLen, unsigned int dest_uid)
	{
		while ( (UCSRA & (1<<RXC)) ); //Waiting before uart data will be unavailable

		/*Interrupt ban*/
		asm("cli");

		/*Getting data crc checksumm*/
		unsigned char crc = getCRC(data, dataLen);
		
		/*Building package header*/
		HidPkgHeader header = {UID, dest_uid, dataLen, crc};

		// /*Memory allocation for package header and data*/
		// unsigned char * package = (unsigned char *)malloc(sizeof(HidPkgHeader)+dataLen);
		// /*Copying Header and data into single memory area to send them in one flow*/
		// memcpy(package, &header, sizeof(HidPkgHeader));
		// memcpy((package+sizeof(HidPkgHeader)), data, dataLen);

		UART::write((unsigned char *)&header, sizeof(HidPkgHeader));
		UART::write((unsigned char *)data, dataLen);
		UART::write((unsigned char *)data, sizeof(HidPackage::DATA) - dataLen);

		// free(package);
		sei();
	};

	HidPackage HidRecieveData()
	{
		asm("cli");

		HidPackage pkg;
		UART::read((unsigned char *)&pkg, sizeof(HidPackage));
		// HidPkgHeader header;
		// readUART((unsigned char *)&header, sizeof(HidPkgHeader));

		// unsigned char * package = (unsigned char *)malloc(header.DATALen);
		// readUART(package, header.DATALen);

		// HidPackage pkg {header, package};
		sei();
		return pkg;
	};

};
// #endif