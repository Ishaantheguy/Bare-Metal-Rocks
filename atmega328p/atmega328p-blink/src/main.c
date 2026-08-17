#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    //Setting Port B, Pin 5 mode as output
    DDRB |= (1<<DDB5);

    //Setting Port B, Pin 5 HIGH (Turns the LED ON)
    PORTB |= (1<<PORTB5);

    //Infinite loop for mcu
    while (1) {
        _delay_ms(3000);
        PORTB &=(0<<PORTB5);
        _delay_ms(3000);
        PORTB |=(1<<PORTB5);
    }

    return 0; 
}
