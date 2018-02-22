#ifndef IO_H_
#define IO_H_

#include <avr/io.h>
#include <util/delay.h>

#include "../constants.h"

/** Number of possible short press events/handlers. */
#define N_PRESSEVENTS_SHORT	7

/** Number of possible long press events/handlers. */
#define N_PRESSEVENTS_LONG	2

/** Enumerates each push button. */
enum t_button {
    SET_ALARM,
    SET_CLOCK,
    STOP_ALARM,
    UP,
    DOWN,
    MODE,
    SNOOZE,
};

typedef void (*Handler) (void);

/**
 * I/O wrapper. Controls all peripherals except the display, that is managed by the Display class.
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
     * \param button button
     * \param handler handler function
     * \return void
     */
    void setPressHandler(t_button, Handler);

    /**
     * Sets an handler function for any button short press event. Used for events shared by all buttons.
     * \param handler handler function
     * \return void
     */
    void setPressHandler(Handler);

    /**
     * Sets an handler function for a given button long press event.
     * \param button Button
     * \param handler handler function
     * \return void
     */
    void setLongHandler(t_button, Handler);

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
    /** Stores each button known state. Used to detect transitions. */
    bool pressed[N_PRESSEVENTS_SHORT];

    /** Stores how many consecutive countCheckLong calls have detected a button pressed. */
    int  pressed_cnt[N_PRESSEVENTS_LONG];

    /** Short press handler array for each button. */
    Handler press_handler_array[N_PRESSEVENTS_SHORT];

    /** Short press handler array for a generic button. */
    Handler press_handler_generic;

    /** Long press handler array for each button. */
    Handler long_handler_array[N_PRESSEVENTS_SHORT];

    /**
     * Resets internal variables (pressed and pressed_cnt).
     * \return void
     */
    void _resetState();

    /**
     * Reads the button digital value and converts it to a boolean variable.
     * \param button Button ID
     * \return bool true if button is pressed
     */
    bool _getBtnValue(t_button);

};

#endif /* IO_H_ */