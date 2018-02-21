#ifndef IO_H_
#define IO_H_

#include <avr/io.h>
#include <util/delay.h>

#include "../constants.h"

#define BTN_PRESS_CNT 6
#define BTN_LONG_CNT 6

#define BTN_SET_ALARM	0
#define BTN_SET_CLOCK	1
#define BTN_UP			2
#define BTN_DOWN		3
#define BTN_MODE		4
#define BTN_SNOOZE		5

typedef void (*Handler) (void);

/**
 *  I/O wrapper. Controls all peripherals except the display, that is managed by the Display class.
 */

class IO {
	
public:
	/**
	 * \brief Initializes the Atmega328p I/O
	 * \return void
	 */
    void init();

    /**
     * Returns the status of the alarm switch.
     * \return bool true if alarm is enabled.
     */
    bool getSwitch();


    /**
     * Turns ON/OFF the display backlight.
	 * \param state true if backlight is ON.
     * \return void
     */
    void setLight(bool);
	
	/**
	 * Commutes the value of the buzzer digital port. Must be called periodically to produce sound.
	 * \return void
	 */
	void buzz();
	
	/**
	 * Sets an handler function for a given button short press event.
	 * \param btn Button ID
	 * \param handler handler function
	 * \return void
	 */
	void setPressHandler(int, Handler);
	
	/**
	 * Sets an handler function for any button short press event. Used for events shared by all buttons.
	 * \param btn Button ID
	 * \param handler handler function
	 * \return void
	 */
	void setPressHandler(Handler);
	
	/**
	 * Sets an handler function for a given button long press event.
	 * \param btn Button ID
	 * \param handler handler function
	 * \return void
	 */
	void setLongHandler(int, Handler);
	
   /**
	* When called, it compares the button state with the one from a previous call to detect a button press-down event. If no 
	* previous record is available, all buttons are assumed as not pressed. If a press-down is detected the short press event 
	* handler for that button is called as well as the generic one. Debounce is synchronous and has a delay of 
	* \return void
	*/
	void checkPress();
	
	/**
	* When called, if a button is pressed, a counter is incremented for that button, or reset otherwise. If a button remains pressed
	* for LONG_PRESS_N separate calls, the long press event handler is generated for that button and counting is suspended.
	* \return void
	*/
	void countCheckLong();
	
private:
	bool pressed[BTN_PRESS_CNT];
	int  pressed_cnt[BTN_PRESS_CNT];
	
	Handler press_handler_array[BTN_PRESS_CNT];
	Handler press_handler_generic;
	Handler long_handler_array[BTN_PRESS_CNT];
	
	void _resetState();
	bool _getBtnValue(int);
	
};

#endif /* IO_H_ */