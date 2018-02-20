#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>
#include <util/delay.h>

#include "../constants.h"

class Display
{
	public:
	void init();
	
	void setPixel(int, int, int);
	void update();
	void clear();
	void reset();
	
	private:
	
	char display_data[16][64]; 	// Don't judge me.
	
	void _send(char c);
	
	void _sendCommand(char c);
	void _sendData(char c);
	void _reset();
};

#endif /* DISPLAY_H_ */