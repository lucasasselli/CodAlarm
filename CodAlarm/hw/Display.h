#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>
#include <util/delay.h>

#include "../constants.h"

/**
 *  Display control wrapper.
 */

class Display
{
	public:
	/**
	 * \brief Initializes the display
	 * by setting the I/O and configuring the ST7565 controller.
	 * \return void
	 */
	void init();
	
	
	/**
	 * \brief Changes pixel color
	 * in the display buffer.
	 * \param x horizontal position
	 * \param y vertical position
	 * \param value either BlACK or WHITE
	 * 
	 * \return void
	 */
	void setPixel(int, int, int);
	
	
	/**
	 * Updates display.
	 * \return void
	 */
	void update();
	
	
	/**
	 * Clears display buffer.
	 * \return void
	 */
	void clear();
	
	/**
	 * \brief Resets the display.
	 * It performs an hardware reset and reinitializes the ST7565 controller.
	 * \return void
	 */
	void reset();
	
	private:
	
	char display_data[16][64]; 	// Don't judge me.
	
	void _send(char c);
	
	void _sendCommand(char c);
	void _sendData(char c);
	void _reset();
};

#endif /* DISPLAY_H_ */