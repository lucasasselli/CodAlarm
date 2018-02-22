#include "IO.h"

void IO::init() {

    // Set directions
    DDR(PORT_BACKLIGHT)		= SET_BIT(DDR(PORT_BACKLIGHT), LINE_BACKLIGHT);
    DDR(PORT_BUZZER)		= SET_BIT(DDR(PORT_BUZZER), LINE_BUZZER);

    DDR(PORT_BTN_SET_ALARM) = UNSET_BIT(DDR(PORT_BTN_SET_ALARM), LINE_BTN_SET_ALARM);
    DDR(PORT_BTN_SET_CLOCK) = UNSET_BIT(DDR(PORT_BTN_SET_CLOCK), LINE_BTN_SET_CLOCK);
    DDR(PORT_BTN_UP)		= UNSET_BIT(DDR(PORT_BTN_UP), LINE_BTN_UP);
    DDR(PORT_BTN_DOWN)		= UNSET_BIT(DDR(PORT_BTN_DOWN), LINE_BTN_DOWN);
    DDR(PORT_BTN_MODE)		= UNSET_BIT(DDR(PORT_BTN_MODE), LINE_BTN_MODE);
    DDR(PORT_BTN_SNOOZE)	= UNSET_BIT(DDR(PORT_BTN_SNOOZE), LINE_BTN_SNOOZE);

    // Reset pressed status
    _resetState();
}

void IO::_resetState() {
    for(int i=0; i<N_PRESSEVENTS_SHORT; i++) {
        // Reset button pressed state
        pressed[i] = false;
    }
    for(int i=0; i<N_PRESSEVENTS_LONG; i++) {
        // Reset button long press count
        pressed_cnt[i] = 0;
    }
}

bool IO::getSwitch() {
    // TODO: Check if high/low
    return CHECK_BIT(PIN(PORT_SWITCH), LINE_SWITCH);
}

void IO::setLight(bool state) {
    if(state) {
        PORT(PORT_BACKLIGHT) = SET_BIT(PORT(PORT_BACKLIGHT), LINE_BACKLIGHT);
    } else {
        PORT(PORT_BACKLIGHT) = UNSET_BIT(PORT(PORT_BACKLIGHT), LINE_BACKLIGHT);
    }
}

void IO::buzz() {
    if(CHECK_BIT(PIN(PORT_BUZZER), LINE_BUZZER)) {
        PORT(PORT_BUZZER) = UNSET_BIT(PORT(PORT_BUZZER), LINE_BUZZER);
    } else {
        PORT(PORT_BUZZER) = SET_BIT(PORT(PORT_BUZZER), LINE_BUZZER);
    }
}

void IO::setPressHandler(t_button button, Handler handler) {
    press_handler_array[button] = handler;
}

void IO::setPressHandler(Handler handler) {
    press_handler_generic = handler;
}


void IO::setLongHandler(t_button button, Handler handler) {
    long_handler_array[button] = handler;
}

void IO::checkPress() {
    for(int i=0; i<N_PRESSEVENTS_SHORT; i++) {
        bool value = _getBtnValue((t_button) i);

        // Released -> Pressed
        if(value && !pressed[i]) {
            // Button appears to be pressed... debounce!
            _delay_ms(DELAY_DEBOUNCE);	// Software debounce
            if(value) {
                pressed[i] = true;		// Change state for button
                press_handler_generic();
                press_handler_array[i]();	// Call the button handler
            }
        }

        // Pressed -> Released
        if(!value && pressed[i]) {
            // Button appears to be released... debounce!
            _delay_ms(DELAY_DEBOUNCE);	// Software debounce
            if(!value) {
                pressed[i] = false;		// Change state for button
            }
        }
    }
}

void IO::countCheckLong() {
    for(int i=0; i<N_PRESSEVENTS_LONG; i++) {
        if(pressed[i]) {
            // If button is pressed
            if(pressed_cnt[i] < N_LONG_PRESS) {
                // Time not elapsed
                pressed_cnt[i]++;
            } else {
                if(pressed_cnt[i] < N_LONG_PRESS) {
                    // Time just elapsed
                    pressed_cnt[i]++;
                    long_handler_array[i]();
                }
            }
        } else {
            // If not pressed, keep count to 0!
            pressed_cnt[i] = 0;
        }
    }
}

bool IO::_getBtnValue(t_button button) {
    bool value;

    switch(button) {
    case SET_ALARM:
        value = CHECK_BIT(PIN(PORT_BTN_SET_ALARM), LINE_BTN_SET_ALARM);

    case SET_CLOCK:
        value = CHECK_BIT(PIN(PORT_BTN_SET_CLOCK), LINE_BTN_SET_CLOCK);

    case STOP_ALARM:
        value = CHECK_BIT(PIN(PORT_BTN_STOP_ALARM), LINE_BTN_STOP_ALARM);

    case UP:
        value = CHECK_BIT(PIN(PORT_BTN_UP), LINE_BTN_UP);

    case DOWN:
        value = CHECK_BIT(PIN(PORT_BTN_DOWN), LINE_BTN_DOWN);

    case MODE:
        value = CHECK_BIT(PIN(PORT_BTN_MODE), LINE_BTN_MODE);

    case SNOOZE:
        value = CHECK_BIT(PIN(PORT_BTN_SNOOZE), LINE_BTN_SNOOZE);
    }

    // Buttons are active low!
    return !value;
}