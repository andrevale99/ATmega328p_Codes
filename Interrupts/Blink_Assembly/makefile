FILENAME   = main
PORT       = /dev/ttyUSB0
DEVICE     = atmega328p
PROGRAMMER = arduino

#Se for usar o arduino nano usar o BAUD a 57600
#BAUD       = 115200
BAUD       = 57600
COMPILE    = avra


default: compile upload clean

compile:
	$(COMPILE) $(FILENAME).S

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).S.hex:i

clean:
	rm $(FILENAME).S.*
