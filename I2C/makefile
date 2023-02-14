MAIN   = main
I2C_LIB = i2c_lib
PORT       = /dev/ttyUSB0
DEVICE     = atmega328p
PROGRAMMER = arduino

#Se utlizar o Atmega328p na placa Arduino UNO o baud rate deve ser 115200
#Se utilizar o Atmega328p nano o baud rate deve ser 57600
#Se utilizar o Atmega168 no nano o baud rate deve ser 19200
BAUD       = 57600
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)


default: compile upload clean

compile:
	$(COMPILE) -c $(MAIN).c -o $(MAIN).o
	$(COMPILE) -c $(I2C_LIB).c -o $(I2C_LIB).o
	$(COMPILE) -o $(MAIN).elf $(MAIN).o $(I2C_LIB).o
	avr-objcopy -j .text -j .data -O ihex $(MAIN).elf $(MAIN).hex 
	avr-size --format=avr --mcu=$(DEVICE) $(MAIN).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(MAIN).hex:i

size:
	avr-size --format=avr --mcu=$(DEVICE) $(MAIN).elf

clean:
	@rm *.o
	@rm *.elf
	@rm *.hex
