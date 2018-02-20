#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Useful stuff
#define CHECK_BIT(var, pos) ((var) & ( 1 << pos ))
#define SET_BIT(var, pos) ((var) | (1 << pos))
#define UNSET_BIT(var, pos) ((var) & ~(1 << pos))

#define CONCAT(x,y)			x ## y

#define DDR(x)				CONCAT(DDR,x)
#define PORT(x)				CONCAT(PORT,x)
#define PIN(x)				CONCAT(PIN,x)


//////////////////////////////////////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////////////////////////////////////

# define F_CPU 1000000UL

#define TIMER1_CMP			15624	// Timer1 = 1 sec
#define TIMER2_CMP			11		// Timer2 = 3Khz
#define DELAY_DEBOUNCE		10		// Millisec.
#define LONG_PRESS_TIME		976	    // Timer0 = 2 sec
#define BACKLIGHT_TIME		2441 	// Timer0 = 5 sec
#define BUZZER_LONG_TIME	448 	// Timer0 = 1 sec
#define BUZZER_SHORT_TIME	112 	// Timer0 = 25 msec

//////////////////////////////////////////////////////////////////////////
// PINOUT
//////////////////////////////////////////////////////////////////////////

#define PORT_BACKLIGHT		B
#define LINE_BACKLIGHT		0
#define PORT_BUZZER			B
#define LINE_BUZZER			0

#define PORT_BTN_SET_CLOCK	D
#define LINE_BTN_SET_CLOCK	0
#define PORT_BTN_SET_ALARM	D
#define LINE_BTN_SET_ALARM	0
#define PORT_BTN_UP			D
#define LINE_BTN_UP			0
#define PORT_BTN_DOWN		D
#define LINE_BTN_DOWN		0
#define PORT_BTN_MODE		D
#define LINE_BTN_MODE		0
#define PORT_BTN_SNOOZE		D
#define LINE_BTN_SNOOZE		0
#define PORT_SWITCH			D
#define LINE_SWITCH			0

#define PORT_DISPLAY_A0		D
#define LINE_DISPLAY_A0		0
#define PORT_DISPLAY_RESET	D
#define LINE_DISPLAY_RESET	0

#endif /* CONSTANTS_H_ */