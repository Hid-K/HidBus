#Developer makefile
#Building demo project and doing something more


#Controller:
MMCU = atmega16

#Chip freq
FREQ = 16000000UL

#Compiler:
CC = avr-g++

#Compiler flags:
CFLAGS = -Wall -O1 -mmcu=$(MMCU) -D F_CPU=$(FREQ)

#Output file way:
OUTPUT = build

all: AvrUart.o main.o HidBus.o
	$(CC) $(CFLAGS) $(OUTPUT)/AvrUart.o $(OUTPUT)/HidBus.o $(OUTPUT)/main.o -o $(OUTPUT)/main
	avr-objcopy -j .text -j .data -O ihex  $(OUTPUT)/main  $(OUTPUT)/main.hex
	minipro -p $(MMCU) -w $(OUTPUT)/main.hex
	minipro -p $(MMCU) -w fuse_bits/$(MMCU).conf -c config -e

AvrUart.o:
	$(CC) $(CFLAGS) -c ../HidBus/UART/AvrUart.cpp -o $(OUTPUT)/AvrUart.o

main.o:
	$(CC) $(CFLAGS) -c main.cpp -o $(OUTPUT)/main.o

HidBus.o:
	$(CC) $(CFLAGS) -c ../HidBus/HidBus.cpp -o $(OUTPUT)/HidBus.o

readFuseBits:
	minipro -p $(MMCU) -r fuse_bits/$(MMCU).conf -c config -e -I

git_push:
	git add *
	git commit -m 'Hid-K'
	git push