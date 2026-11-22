# include <stdint.h>

# define UBRR0H (volatile uint8_t *)(0xC5)
# define UBRR0L (volatile uint8_t *)(0xC4)
# define BAUD_RATE 9600
# define UBRR_val (volatile uint32_t)(F_CPU/((uint32_t)BAUD_RATE<<4)-1)

# define UCSR0A (volatile uint8_t *)(0XC0)
# define UCSR0B (volatile uint8_t *)(0XC1)
# define UCSR0C (volatile uint8_t *)(0XC2)
# define UDR0 (volatile uint8_t *)(0xC6)

# define UDRE0 (volatile uint8_t)(1<<5)
# define U2X0 (volatile uint8_t)(1<<2)
# define RXEN0 (volatile uint8_t)(1<<4)
# define TXEN0 (volatile uint8_t)(1<<3)
# define TXC0 (volatile uint8_t)(1<<6)

# define UCSZ00 (volatile uint8_t)(1<<1)
# define UCSZ01 (volatile uint8_t)(1<<2)

# define UPM00 (volatile uint8_t)(1<<4)
# define UPM01 (volatile uint8_t)(1<<5)

# define USBS0 (volatile uint8_t)(1<<3)
// # define

void UART_init();
void UART_transmit(uint8_t);
void UART_print_big(char *, int);
void UART_long_integer(unsigned long);