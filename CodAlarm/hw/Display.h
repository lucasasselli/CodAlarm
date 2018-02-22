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
	
	/** Display pixel buffer. */
	char display_data[16][64]; 	// Don't judge me.
	
	/**
	 * Sends a single character trough the SPI interface.
	 * \param c Character to be sent
	 * \return void
	 */
	void _send(char);
	
	/**
	 * Sends a command to the ST7565 controller. DISPLAY_A0 is set to high.
	 * \param c Command to be sent
	 * \return void
	 */
	void _sendCommand(char c);
	
	/**
	 * Sends a byte of data to the ST7565 controller. DISPLAY_A0 is set to low.
	 * \param c Data to be sent
	 * \return void
	 */
	void _sendData(char c);
	
	/**
	 * Hard resets the ST7565 controller. DISPLAY_RESET set to high and then low.
	 * \return void
	 */
	void _reset();
};

#endif /* DISPLAY_H_ */