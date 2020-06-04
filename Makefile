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

all: AvrUart.o main.o
	$(CC) $(CFLAGS) $(OUTPUT)/AvrUart.o $(OUTPUT)/main.o -o $(OUTPUT)/main
	avr-objcopy -j .text -j .data -O ihex  $(OUTPUT)/main  $(OUTPUT)/main.hex
	minipro -p $(MMCU) -w $(OUTPUT)/main.hex -I
	minipro -p $(MMCU) -w fuse_bits/$(MMCU).conf -c config -e -I

AvrUart.o:
	$(CC) $(CFLAGS) -c HidBus/UART/AvrUart.cpp -o $(OUTPUT)/AvrUart.o

main.o:
	$(CC) $(CFLAGS) -c tests/main.cpp -o $(OUTPUT)/main.o

readFuseBits:
	minipro -p $(MMCU) -r fuse_bits/$(MMCU).conf -c config -e -I

git_push:
	git add *
	git commit -m 'Hid-K'
	git push