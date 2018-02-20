#include "Display.h"

void Display::init() {

    // Configure SPI
    DDRB = (1<<DDB3)|(1<<DDB3)|(1<<DDB5); 	// Set SS, MOSI and SCK output, all others input
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); 	// Enable SPI, Master, set clock rate fclk/16

    // Configure direction
    DDR(PORT_DISPLAY_A0)	= SET_BIT(DDR(PORT_DISPLAY_A0), LINE_DISPLAY_A0);
    DDR(PORT_DISPLAY_RESET)	= SET_BIT(DDR(PORT_DISPLAY_RESET), LINE_DISPLAY_RESET);

    reset();
}

void Display::_send(char c) {

    SPDR = c;

    // Wait completion
    while(!(SPSR & (1<<SPIF)));
}

void Display::_sendCommand(char data) {
    PORT(PORT_DISPLAY_A0) = SET_BIT(PORT(PORT_DISPLAY_A0), LINE_DISPLAY_A0);
    _delay_us(15);
    _send(data);
}

void Display::_sendData(char data) {
    PORT(PORT_DISPLAY_A0) = UNSET_BIT(PORT(PORT_DISPLAY_A0), LINE_DISPLAY_A0);
    _delay_us(15);
    _send(data);
}

void Display::_reset() {
    PORT(PORT_DISPLAY_RESET) = SET_BIT(PORT(PORT_DISPLAY_RESET), LINE_DISPLAY_RESET);
    _delay_us(30);
    PORT(PORT_DISPLAY_RESET) = UNSET_BIT(PORT(PORT_DISPLAY_RESET), LINE_DISPLAY_RESET);
    _delay_us(30);		// Just to be safe...
}

void Display::reset() {

    _reset();

	// Configure display
    _sendCommand(0b00110000);   // 8-bit mode.
    _delay_us(100);
    _sendCommand(0b00110000);	// 8-bit mode again.
    _delay_us(110);
    _sendCommand(0b00001100);   // Display on
    _delay_us(100);
    _sendCommand(0b00000001);   // Clears screen.
    _delay_ms(2);
    _sendCommand(0b00000110);   // Cursor moves right, no display shift.
    _delay_us(80);
    _sendCommand(0b00110100);   // Extended instruction set, 8bit
    _delay_us(100);
    _sendCommand(0b00110110);   // Repeat instruction with bit1 set
    _delay_us(100);
}

void Display::update() {
    for(char y = 0; y < 64; y++) {
        if(y < 32) {
            _sendCommand(0x80 | y);
            _sendCommand(0x80);
        } else {
            _sendCommand(0x80 | (y-32));
            _sendCommand(0x88);
        }
        for(char x = 0; x < 16; x++) {
            _sendData(display_data[x][y]);
        }
    }
}

void Display::clear() {
    unsigned int x, y;
    for(y=0; y<64; y++)
        for(x=0; x<17; x++)
            display_data[x][y]=0x00;
}

void Display::setPixel(int x, int y, int value) {
    int x_char = x/8;
    int index = (7-x)%8;
    char buf = display_data[x_char][y];

    if(value==0) {
        buf=UNSET_BIT(buf,index);
    } else {
        buf=SET_BIT(buf,index);
    }

    display_data[x_char][y]=buf;
}