# ATmega328P Bare-Metal Examples

This repository contains simple **bare-metal programming examples for the ATmega328P**. The projects demonstrate direct interaction with the microcontroller's hardware registers without relying on the Arduino framework.

Refer [Blog](https://ishaantheguy.in/blog/bare-metal-atmega328p/) for better understanding on how to approach and understand such programs

## Projects

### 1. Blinky

A minimal GPIO example that periodically toggles the onboard LED.

The program directly configures the GPIO registers of the ATmega328P rather than using Arduino functions such as `pinMode()` or `digitalWrite()`.

The onboard LED on an Arduino Uno is connected to **PB5 (digital pin 13)**.

---

### 2. Echo Service (USART)

A simple UART-based echo service.

Characters received through the serial interface are transmitted back to the host, allowing the ATmega328P to communicate with a computer through the Arduino's USB-to-serial interface.

The echo service can be tested using a serial terminal or PlatformIO's serial monitor.

---

### 3. Oled Communication (TWI)

All of us here with an OLED , at some point of time, must have heard about the Adafruit_GFX and Adafruit_SSD1306 libraries to tell our oled display what to show. Whether it be a Robot face (Yes they have supported showing some symbols on the screen), Geometrical shapes or just some random pixels, Adafruit has quite nicely put them all together. But how does that happen? All through the Two-Wire Interface (Wanted to call it I2C but Philips might come after me ;) ).

Here ATmega328p acts as the master device communicating with the oled slave, giving it appropriate commands and data to display my image.

Have also added a UART debugger which prints to the serial monitor the values of the TWINT flag after each communication.

For this one, I didn't want to rely on pio so I used a Makefile. Just follow the following commands:-

To build the firmware:

```bash
make
```

To remove the previous build files before a fresh build:
```bash
make clean
```

To upload the firmware:
```
make flash
``` 

## Hardware

The examples require:

* Arduino Uno / ATmega328P board
* USB cable
* Computer
* OLED screen (Only for the 3rd project)

No external components are necessarily required since we can also simulate their behavior on Wokwi's board.

## Building and Uploading

The projects can be built and uploaded using **PlatformIO**.

From the project directory:

```bash
pio run
```

To upload the firmware:

```bash
pio run --target upload
```

To identify the connected serial device:

```bash
pio device list
```

To open the serial monitor for the Echo Service:

```bash
pio device monitor
```

## Bare-Metal Approach

These examples intentionally avoid the Arduino API. Instead of using:

```cpp
pinMode();
digitalWrite();
Serial.begin();
Serial.println();
```

the programs interact directly with the ATmega328P's memory-mapped peripheral registers.


## Repository Structure

```text
.
├── blinky/
│   ├── platformio.ini
│   └── src/
│       └── main.c
│
├── echo-service/
│   ├── platformio.ini
│   └── src/
│       └── main.c
│
├── oled-talker/
│   ├── Makefile
│   ├── main.c
│   ├── i2c.c
│   ├── i2c.h
│   ├── uart_debug.c
│   └── uart_debug.h
│ 
└── README.md
```

## Future Extensions

I am thinking of extending it into larger bare-metal projects, including:

-  Timer-based delays
-  Interrupt-driven UART
-  Timer interrupts
-  PWM
-  ADC
-  SPI drivers
✔  I2C drivers
-  EEPROM access
✔  UART command shell
-  Bootloader development
-  Logic analyzer implementation
✔  Custom startup code and linker configuration

