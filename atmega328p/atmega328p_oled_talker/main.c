# include "i2c.h"
# include "uart_debug.h"
#include <stdint.h>

static uint8_t image_buffer[1024] = {0};

void TWSR_debug_msg()
{
    if(STATUS_CODE)
    {
        UART_print_big("TWSR status code:", 18);
        UART_long_integer((unsigned long)STATUS_CODE);
    }
}

void sending_i2c_data_byte(uint8_t data)
{
    TWDR = data; //
    TWCR = _BV(TWINT) | _BV(TWEN);
    while(!(TWCR & _BV(TWINT)));
    TWSR_debug_msg();
}

void set_pixel(uint8_t row, uint8_t column)
{
    image_buffer[row + (column/8)*128] |= (1<< (column & 7));
}

void creating_icon()
{
    for(int i=0;i<1024;i++)
    {
        image_buffer[i] = 0;
    }

    
    for (int y=3;y<=10;y++)
    {
        for (int x=32;x<=95;x++)
        {
            set_pixel(x,y);
        }
    }
    
    for(int y=11; y<=52; y++)
    {
        for(int x=56;x<=71;x++)
        {
            set_pixel(x, y);
        }
    }

    for(int y=53;y<=60;y++)
    {
        for(int x=32;x<=95;x++)
        {
            set_pixel(x, y);
        }
    }
}

void send_image()
{
    twi_init();
    while(!(TWCR & _BV(TWINT)));
    TWSR_debug_msg();

    sending_i2c_data_byte(slarw(0x3c, 1));//Write mode
    sending_i2c_data_byte(0x0 | (1<<6)); // This tells that all the incoming bytes are command bytes

    creating_icon();

    for(int i=0;i<1024;i++)
    {
        sending_i2c_data_byte(image_buffer[i]);
    }
    twi_finish();
}



void oled_init()
{
    twi_init();
    while(!(TWCR & _BV(TWINT)));
    TWSR_debug_msg();
    
    sending_i2c_data_byte(slarw(0x3c, 1));//Write mode
    sending_i2c_data_byte(0x0); // This tells that all the incoming bytes are command bytes

    uint8_t command_list[26] = {0};
    uint8_t cnt = 0;
    command_list[cnt++] = 0xAE ;// Switching display off
    command_list[cnt++] = 0xD5; // Setting display clock ratio frequency
    command_list[cnt++] = 0x80; // This is the value of clock ratio frequency
    command_list[cnt++] = 0xA8; // Setting multiplex
    command_list[cnt++] = 63; // This is multiplex of height-1
    command_list[cnt++] = 0xD3; // Setting display offset
    command_list[cnt++] = 0x0; // Display offset is 0
    command_list[cnt++] = 0x40 | 0x0; //Set display start line
    command_list[cnt++] = 0x8D; // Charge pump setting
    command_list[cnt++] = 0x14; // Enable charge pump during display on
    command_list[cnt++] = 0x20; // Setting addressing mode
    command_list[cnt++] = 0x0; // Horizontal Memory addressing mode
    command_list[cnt++] = 0xA1; // Set segment-remap
    command_list[cnt++] = 0xC8; // Set COMSCAN direction in descending order
    command_list[cnt++] = 0xDA; // Set COM pins
    command_list[cnt++] = 0x12; // Alternative COM pin configuration and disable COM left right remap
    command_list[cnt++] = 0x81; // Set Contrast
    command_list[cnt++] = 0xCF; // Contrast value
    command_list[cnt++] = 0xD9; // Set pre-charge period
    command_list[cnt++] = 0xF1; // Pre-charge period of total of about 1CLK in phase 1 and 15DCLK in phase 2
    command_list[cnt++] = 0xDB; // Sets Vcomh , will understand what this does in the future
    command_list[cnt++] = 0x40; // Sets its value which isnt mentioned in the documentation table
    command_list[cnt++] = 0xA4; // Sets entire display on with output following RAM content
    command_list[cnt++] = 0xA6; // Sets normal display where 1 in RAM means ON in display and vice versa
    command_list[cnt++] = 0x2E; // Deactivates scrolling
    command_list[cnt++] = 0XAF; // Display ON in normal mode

    for(int i=0;i<cnt;i++)
        sending_i2c_data_byte(command_list[i]);

    twi_finish();
}

void main()
{
    UART_init();
    send_image();
    oled_init();
}