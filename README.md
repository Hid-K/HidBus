# HidBus
## C library for AVR microcontrollers to use HidBus

This library using UART to send and recieve packages.

All __HidBus__ library members are isolated by namespace "HidBus::".
* HidBus unit making recomendations:
    Add __HIDBUS_UNIT_CONFIG.hpp__ into library folder and define there unit commands and it's adress.

HidBus members defined in __HidBus.hpp__ header file.
First is the package header structure:
```C
struct HidPkgHeader
{
	unsigned int SRC_UID;
	unsigned int DEST_UID;
	unsigned int DATALen;
	unsigned char crc;
};
```

__HidPkgHeader::SRC_UID__ is the sender unit adress (16 bits).
__HidPkgHeader::DEST_UID__ is the destination unit adress (16 bits).
__HidPkgHeader::DATALen__ is the length of package data.
`For usaly units this number must not be higher, than 128`
__HidPkgHeader::crc__ is the package payload crc checksumm to check package data integriti.

Next is the package structure to return recieved data from __HidBus::RecieveData()__:
```C
struct HidPackage
{
	HidPkgHeader header;
	unsigned char DATA[128];
};
```
__HidPackage::HidPkgHeader__ is just __HidBus::HidPkgHeader__ structure.
__HidPackage::DATA__ is package payload.

Crc checksumm calculating function:
```C
HidBus::getCRC(const unsigned char * data, unsigned char dataLen);
```
Function, that building your data into package and sending it to HidBus:
```C
HidBus::SendData(const void * data, unsigned int dataLen, unsigned int dest_uid);
```

This function recieves package header and check it's destination adress, if this package sended to this unit, function recieving it and writing data into package:
```C
signed char HidBus::RecieveData(HidBus::HidPackage & packageBuf)
```
If package are sended to this unit, returns __0__, else __-1__