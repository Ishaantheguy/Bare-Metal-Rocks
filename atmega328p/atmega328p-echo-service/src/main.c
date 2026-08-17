#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>


#define maxLength 20

void USART_init(unsigned int ubrr);
void USART_transmit_5_to_8(unsigned char content);
unsigned char USART_receive_5_to_8(void);
void USART_printf(const char *str);

int main(void)
{
    DDRB |= 1<<DDB5; // Setting pin to output mode
    PORTB |= 0<<PORTB5; //Setting led to low
    while(1)
    {
        // Calculating the ubrr for the 16MHz which is standard Arduino speed
        unsigned int ubrr =(F_CPU/(16UL*9600UL))-1;
        USART_init(ubrr);

        USART_printf("\r\nEnter content (up to 20 characters):\r\n");
        
        char buf[maxLength]={0};
        int len=0;
        
        while (len<(maxLength - 1)) { 
            unsigned char t=USART_receive_5_to_8();
            if (t=='\b' || t==0x7F) {
                if (len>0) {
                    len--;
                    USART_transmit_5_to_8('\b');
                    USART_transmit_5_to_8(' ');
                    USART_transmit_5_to_8('\b');
                }
                continue;
            }
            
            
            if (t=='\n' || t=='\r')
                break;
            
            USART_transmit_5_to_8(t);
            buf[len++]=t;
        }
        
        buf[len]='\0'; 
        USART_printf("\r\nContent is: ");
        USART_printf(buf);
        USART_printf("\r\n");
    }
}

void USART_init(unsigned int ubrr)
{
    //Setting the USART baude rate register high and low
    UBRR0H=(unsigned char)(ubrr>>8);
    UBRR0L=(unsigned char)ubrr;

    //Enable receiver and transmitter
    UCSR0B=(1<<TXEN0)|(1<<RXEN0);
    
    //Set size of data frame to 8 bits
    UCSR0C=(3<<UCSZ00); 
}

void USART_printf(const char *str)
{
    while (*str) {
        USART_transmit_5_to_8(*str++);}
}

void USART_transmit_5_to_8(unsigned char content)
{
    while (!(UCSR0A & (1<<UDRE0)))
    {}
    UDR0=content;
}

unsigned char USART_receive_5_to_8()
{
    while(!(UCSR0A & (1<<RXC0)))
    {}
    return UDR0;
}
