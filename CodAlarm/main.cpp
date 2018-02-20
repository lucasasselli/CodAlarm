#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "core/Clock.h"
#include "core/CodAlarm.h"
#include "core/GUI.h"

#define BACKLIGHT_OFF -1
#define BUZZER_OFF -1

//////////////////////////////////////////////////////////////////////////
// PROTOTYPES
//////////////////////////////////////////////////////////////////////////

void pressButton();

void pressSetAlarm();
void longSetAlarm();
void pressSetClock();
void longSetClock();
void pressUp();
void pressDown();
void pressMode();
void pressSnooze();

void startBuzzer();
void stopBuzzer();

//////////////////////////////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////////////////////////////

// Objects
CodAlarm ca;
GUI gui(&ca);

// Other
int backlight_counter = BACKLIGHT_OFF;
int buzzer_counter = BUZZER_OFF;
bool buzzer_state = false;

int main(void) {
	
    // Initialize IO wrappers
    ca.io.init();
    ca.display.init();
	
	// Configure Timer 0: Fast counter
	TCNT0 = 0;					// Set timer to 0
	TIMSK0 |= (1 << TOIE0); 	// enable overflow interrupt
	TCCR0B |= (1 << CS01);		// Start timer at 1/8

    // Configure Timer 1: 1Hz
    TCNT1 = 0;								// Set timer to 0
    TCCR1B |= (1 << WGM12);					// Configure for CTC mode
    TIMSK1 |= (1 << OCIE1A);				// Enable CTC interrupt
    OCR1A  = TIMER1_CMP;					// Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
    TCCR1B |= (1 << CS10) | (1 << CS11);	// Start timer at 1/64
	
	// Configure Timer 2: Buzzer
	TCNT2 = 0;					// Set timer to 0
    TCCR2B |= (1 << WGM12);		// Configure for CTC mode
	OCR2A  = TIMER2_CMP;
	TCCR2B |= (1 << CS01);		// Start timer at 1/8

    // Configure button handlers
	ca.io.setPressHandler(pressButton);
	
    ca.io.setPressHandler(BTN_SET_ALARM, pressSetAlarm);
    ca.io.setPressHandler(BTN_SET_ALARM, pressSetClock);
    ca.io.setPressHandler(BTN_UP, pressUp);
    ca.io.setPressHandler(BTN_DOWN, pressDown);
    ca.io.setPressHandler(BTN_MODE, pressMode);
    ca.io.setPressHandler(BTN_SNOOZE, pressSnooze);
    ca.io.setLongHandler(BTN_SET_ALARM, longSetAlarm);
    ca.io.setLongHandler(BTN_SET_ALARM, longSetClock);

    sei();	// Turn on interrupts

    while (1) {

        // Switch off ringing alarm
        if(!ca.io.getSwitch()) {
            // Switch set on "Alarm off"
            if (ca.state = RING) {
                ca.state = IDLE;
                ca.snoozed = false;
				
				stopBuzzer(); // Stop buzzing
            }
        }
		
		// Check if any button was pressed
		ca.io.checkPress();		// Calls handler if so...

        // Draw display
        gui.draw();
    }
}


//////////////////////////////////////////////////////////////////////////
// ISRs
//////////////////////////////////////////////////////////////////////////

// TIMER0 overflow interrupt
ISR(TIMER0_OVF_vect)
{			
	// Check long press
	ca.io.countCheckLong();
		
	// Check display backlight
	if(backlight_counter != BACKLIGHT_OFF)
		if(backlight_counter > 0){
			// Decrease backlight counter
			backlight_counter--;
			}else{
			ca.io.setLight(false);
			backlight_counter = BACKLIGHT_OFF;
		}
		
	if(buzzer_counter != BUZZER_OFF)
		if(buzzer_counter > 0){
			// Decrease backlight counter
			buzzer_counter--;
		}else{
			if(ca.state == RING){
				// Start/Stop buzzer timer to create beeping
				if(buzzer_state){
					// Start buzzer timer
					startBuzzer();		// Also resets buzzer_counter
				}else {
					// Stop buzzer timer
					buzzer_counter = BUZZER_LONG_TIME;
					stopBuzzer();
				}
				buzzer_state != buzzer_state;
			}else{
				// Not ringing, stop here
				buzzer_counter = BUZZER_OFF;
				// Stop buzzer timer
				stopBuzzer();
			}
		}
}

// Timer1 compare interrupt
ISR(TIMER1_COMPA_vect) {
    // Count seconds
    ca.clock.tick();

    // Check alarm/snooze
    if(ca.io.getSwitch()) {
        // Switch set on "Alarm on"
        if (ca.state = IDLE) {
            if(ca.snoozed) {
                // Snoozed once
                if(ca.snooze.getValue() == ca.clock.getValue()) {
                    ca.state = RING;
					startBuzzer();
                }
            } else {
                // Never pressed snooze
                if(ca.alarm.getValue() == ca.clock.getValue()) {
                    ca.state = RING;
					startBuzzer();
                }
            }
        }
    }
}

ISR(TIMER2_COMPA_vect) {
	// Bzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz!!!!!
	ca.io.buzz();
}

//////////////////////////////////////////////////////////////////////////
// BUTTON HANDLERS
//////////////////////////////////////////////////////////////////////////

void pressButton() {
	// Generic short press
	ca.io.setLight(true);
	backlight_counter = BACKLIGHT_TIME;
	
	startBuzzer();
}

void pressSetAlarm() {
    // Short press
    if(ca.state == SET_ALARM1) {
        ca.state = SET_ALARM2;
    } else {
        ca.state = IDLE;
    }
}

void longSetAlarm() {
    // Long press
    if(ca.state == IDLE) {
        ca.state = SET_ALARM1;
    }
}

void pressSetClock() {
    // Short press
    if(ca.state == SET_CLOCK1) {
        ca.state = SET_CLOCK2;
    } else {
        ca.state = IDLE;
    }

}

void longSetClock() {
    // Long press
    if(ca.state == IDLE) {
        ca.state = SET_CLOCK1;
    }
}

void pressUp() {
    switch (ca.state) {
    case SET_ALARM1:
        ca.alarm.setHour(1);
        break;

    case SET_ALARM2:
        ca.alarm.setMin(1);
        break;

    case SET_CLOCK1:
        ca.clock.setHour(1);
        break;

    case SET_CLOCK2:
        ca.clock.setMin(1);
        break;

    default:
        // Nothing!
        break;
    }
}

void pressDown() {
    switch (ca.state) {
    case SET_ALARM1:
        ca.alarm.setHour(-1);
        break;

    case SET_ALARM2:
        ca.alarm.setMin(-1);
        break;

    case SET_CLOCK1:
        ca.clock.setHour(-1);
        break;

    case SET_CLOCK2:
        ca.clock.setMin(-1);
        break;

    default:
        // Nothing!
        break;
    }
}

void pressMode() {
    if(ca.mode == H12) {
        ca.mode = H24;
    } else {
        ca.mode = H12;
    }
}

void pressSnooze() {
    if(ca.state == RING) {
        // Only if ringing
        if (!ca.snoozed) {
            // First snooze
            ca.snoozed = true;			// No longer first snooze
            ca.snooze.sync(ca.alarm);	// Start from alarm value...
            ca.snooze.setMin(5);		// ... 5 more minutes Mom
        } else {
            // More than 1 snooze
            ca.snooze.setMin(5);
        }

        // Stop ringing
        ca.state = IDLE;
    }
}

//////////////////////////////////////////////////////////////////////////
// FUNCTIONS
//////////////////////////////////////////////////////////////////////////

void startBuzzer(){
	if(ca.state == RING){
		// Ringing...
		if(buzzer_counter <= 0 ){
			// Avoid resetting counter: could be a button pressed while ringing!
			buzzer_counter = BUZZER_LONG_TIME;
		}
	}else{
		// Not ringing...
		buzzer_counter = BUZZER_LONG_TIME;
	}
	// Activate interrupt
	TIMSK2 = SET_BIT(TIMSK2, OCIE1A);	// Enable Timer2 CTC interrupt
}
	
void stopBuzzer(){
	// Disable interrupt
	TIMSK2 = UNSET_BIT(TIMSK2, OCIE1A);	// Enable Timer2 CTC interrupt
}