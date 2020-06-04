#ifndef HID_UART_BUS_H
#define HID_UART_BUS_H

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

	void SendData(const void * data, unsigned int dataLen, unsigned int dest_uid)
	{
		// while ( (UCSRA & (1<<RXC)) ); //Waiting before uart data will be unavailable

		/*Interrupt ban*/
		asm("cli");
		
		/*Building package header*/
		HidPkgHeader header = {
							   .SRC_UID  =  UID,
							   .DEST_UID =  dest_uid,
							   .DATALen  =  dataLen,
							   .crc      =  getCRC((const unsigned char*)data, dataLen)
							  };

		UART::write(&header, sizeof(HidPkgHeader));
		UART::write(data, dataLen);

		/*Interrupt unban*/
		asm("sei");
		return;
	};

	HidPackage RecieveData()
	{
		/*Interrupt ban*/
		asm("cli");

		HidPackage pkg;
		if (pkg.header.DEST_UID == UID &&
			pkg.header.DATALen <= sizeof(HidPackage::DATA))
		{
			UART::read(pkg.DATA, pkg.header.DATALen);
		};

		/*Interrupt unban*/
		asm("sei");
		return pkg;
	};

};
#endif