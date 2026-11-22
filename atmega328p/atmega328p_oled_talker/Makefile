MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -std=c99 -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

PORT = /dev/ttyACM0
PROGRAMMER = arduino
BAUD = 115200

all: main.hex

main.elf: main.c uart_debug.c i2c.c
	$(CC) $(CFLAGS) -o main.elf main.c uart_debug.c i2c.c

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

flash: main.hex
	avrdude -F -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:main.hex:i

clean:
	rm -f main.elf main.hex
