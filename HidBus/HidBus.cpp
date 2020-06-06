#include "HidBus.hpp"

unsigned char HidBus::getCRC(const unsigned char * data, unsigned char dataLen)
{
  unsigned char i, j, crc = 0;
 
  for (i = 0; i < dataLen; i++)
  {
    crc ^= data[i];
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
        crc ^= CRC7_POLY;
      crc >>= 1;
    }
  }
  return crc;
};

void HidBus::SendData(const void * data, unsigned int dataLen, unsigned int dest_uid)
{
	while ( (UCSRA & (1<<RXC)) ); //Waiting before uart data will be unavailable
	
	/*Building package header*/
	HidPkgHeader header = {
						   .SRC_UID  =  UID,
						   .DEST_UID =  dest_uid,
						   .DATALen  =  dataLen,
						   .crc      =  getCRC((const unsigned char*)data, dataLen)
						  };

	/*Interrupt ban*/
	asm("cli");

	UART::write(&header, sizeof(HidPkgHeader));
	UART::write(data, dataLen);

	/*Interrupt unban*/
	asm("sei");
	return;
};

signed char HidBus::RecieveData(HidBus::HidPackage & packageBuf)
{
	/*Interrupt ban*/
	asm("cli");

	UART::read(&packageBuf, sizeof(HidBus::HidPackage::header));
	UART::read(packageBuf.DATA, packageBuf.header.DATALen);

	/*Interrupt unban*/
		asm("sei");

	if (packageBuf.header.DEST_UID == UID &&
		packageBuf.header.DATALen <= sizeof(HidPackage::DATA))
	{
		return 0;
	}
	else 
	{
		return -1;
	};
};