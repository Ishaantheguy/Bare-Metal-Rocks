# include "i2c.h"
#include <stdint.h>


void twi_init()
{
    PORTC |= _BV(4) | _BV(5); //Turning on internal pull up resistors so that the SDA and SCL
    // Lines are set high , which is a requirement for TWI state machine.
    TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTA);
}

void twi_finish()
{
    TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO);
}

void clear_TWINT()
{
    TWCR |= _BV(TWINT);
}


uint8_t slarw(uint8_t addr, uint8_t mode)
{
    uint8_t temp_addr = (addr << 1);
    if(mode == 1)
        temp_addr &= ~_BV(0);
    else
        temp_addr |= _BV(1);
    return temp_addr;
}
