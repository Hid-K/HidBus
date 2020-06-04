#Controller:
MMCU = atmega16

#Chip freq
FREQ = 16000000UL

#Compiler:
CC = avr-g++

#Compiler flags:
CFLAGS = -Wall -O1 -mmcu=$(MMCU) -D F_CPU=$(FREQ)

#Output file way:
OUTPUT = build/

all:
	$(CC) $(CFLAGS) tests/main.cpp -o $(OUTPUT)/main
	avr-objcopy -j .text -j .data -O ihex  $(OUTPUT)/main  $(OUTPUT)/main.hex
	minipro -p $(MMCU) -w $(OUTPUT)/main.hex -I
	minipro -p $(MMCU) -w fuse_bits/$(MMCU).conf -c config -e -I

readFuseBits:
	minipro -p $(MMCU) -r fuse_bits/$(MMCU).conf -c config -e -I

git_push:
	git add *
	git commit -m 'Hid-K'
	git push