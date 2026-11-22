# include "uart_debug.h"
#include <stdint.h>

void UART_init()
{
    *UBRR0L = UBRR_val; //Fills UBBR0 with UBBR bit rate
    *UCSR0B |= RXEN0 | TXEN0; //Enabling receiver and transmitter bits

    *UCSR0A &= ~U2X0; // Using Asynchronous normal mode
    *UCSR0C |= UCSZ01 | UCSZ00; //Sets data frame size to 8 bits
    *UCSR0C &= ~UPM00 & ~UPM01; //Sets to no parity mode
    *UCSR0C |= USBS0; //Sets to use two stop bits
}

void UART_long_integer(unsigned long number)
{
    int multiple = 10;
    uint8_t digit;
    while(1)
    {
        if ((int)(number / multiple)<10)
            break;
        multiple*=10;
    }
    for(;multiple!=0;multiple/=10)
    {
        digit = (uint8_t)(number / multiple);
        number%=multiple;
        UART_transmit(digit+0x30);
    }
}

void UART_transmit(uint8_t data)
{

    // while(!(*UCSR0A & (UDRE0)));
    // *UDR0 = data;
    // Or we can use TXC0 as the indicator of sucessfull transmission instead of just checking if transmission buffer is empty or not
    *UCSR0A |=TXC0;
    *UDR0 = data;
    while (!(*UCSR0A & (TXC0)));
}

void UART_print_big(char *str, int length)
{
    for(int i=0;i<length; i++)
    {
        UART_transmit(str[i]);
    }
}