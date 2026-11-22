# include <stdint.h>

# define PORTC *(volatile uint8_t *)(0x28)

# define TWDR *(volatile uint8_t *)(0xBB)

# define TWCR *(volatile uint8_t *)(0xBC)
# define TWIE 0x0
# define TWEN 0x2
# define TWINT 0X7
# define TWSTA 0x5
# define TWSTO 0x4  

# define TWBR *(volatile uint8_t *)(0xB8)

# define TWSR *(volatile uint8_t *)(0xB9)
# define TWPS1 0x1
# define TWPS0 0x0

# define STATUS_CODE (uint8_t)(TWSR & 248) // From TWS3 to TWS7

# define _BV(bit) (1<<bit)

void twi_init();
void twi_finish();
void clear_TWINT();
uint8_t slarw(uint8_t , uint8_t);
