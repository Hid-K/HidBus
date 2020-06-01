all:
	avr-g++ -mmcu=atmega16 main.cpp -o main -O1 -Wall -Wextra 
	avr-objcopy -j .text -j .data -O ihex  main  main.hex
	minipro -p ATMEGA16L -w main.hex -I
	minipro -p ATMEGA16L -w fuse_bits/ATMEGA16L.fuses.conf -c config -e -I

git_push:
	git add *
	git commit -m 'Hid-K'
	git push