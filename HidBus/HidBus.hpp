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

	#include "HIDBUS_UNIT_CONFIG.hpp"

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
	unsigned char getCRC(const unsigned char * data, unsigned char dataLen);
	void SendData(const void * data, unsigned int dataLen, unsigned int dest_uid);
	signed char RecieveData(HidPackage & packageBuf);

};
#endif