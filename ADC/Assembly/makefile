FILENAME   = main
PORT       = /dev/ttyACM0
DEVICE     = atmega328p
PROGRAMMER = arduino

#Se for usar o arduino nano usar o BAUD a 57600
BAUD       = 115200
#BAUD       = 57600
COMPILE    = avra


default: compile upload clean

compile:
	$(COMPILE) $(FILENAME).asm m328Pdef.inc -I ./

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	@rm $(FILENAME).hex
	@rm $(FILENAME).eep.*
	@rm $(FILENAME).obj
