#ifndef CONSTANTS_H_
#define CONSTANTS_H_

//////////////////////////////////////////////////////////////////////////
// MACROS
//////////////////////////////////////////////////////////////////////////

/** Returns the value of a single bit at a given position. */
#define CHECK_BIT(var, pos) ((var) & ( 1 << pos ))

/** Sets to 1 the value of a single bit at a given position. */
#define SET_BIT(var, pos) ((var) | (1 << pos))

/** Sets to 1 the value of a single bit at a given position. */
#define UNSET_BIT(var, pos) ((var) & ~(1 << pos))

/** Concatenates two names. */
#define CONCAT(x,y)			x ## y

/** DDRx register. */
#define DDR(x)				CONCAT(DDR,x)

/** PORTx register. */
#define PORT(x)				CONCAT(PORT,x)

/** PINx register. */
#define PIN(x)				CONCAT(PIN,x)


//////////////////////////////////////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////////////////////////////////////

/** Clock frequency in Hz. Used by the Delay.h AVR library. */
# define F_CPU 1000000UL

/** Timer1 compare interrupt value. Used to create an interrupt every second. */
#define TIMER1_CMP			15624	// Timer1 = 1 sec

/** Timer2 compare interrupt value. Used to create an 3kHz buzz. */
#define TIMER2_CMP			11		// Timer2 = 3Khz

/** Debounce check delay in milliseconds. */
#define DELAY_DEBOUNCE		10		// ms

/** Number of Timer0 interrupts that amounts to a long press event. */
#define N_LONG_PRESS		976	    // Timer0 = 2 sec

/** Number of Timer0 interrupts that amounts to the backlight timeout. */
#define N_BACKLIGHT			2441 	// Timer0 = 5 sec

/** Number of Timer0 interrupts that amounts to a single ringing "beep". */
#define N_BUZZER_LONG		448 	// Timer0 = 1 sec

/** Number of Timer0 interrupts that amounts to a single button "beep". */
#define N_BUZZER_SHORT		112 	// Timer0 = 25 msec

//////////////////////////////////////////////////////////////////////////
// PINOUT
//////////////////////////////////////////////////////////////////////////

#define PORT_BACKLIGHT		C
#define LINE_BACKLIGHT		5
#define PORT_BUZZER			B
#define LINE_BUZZER			1

#define PORT_BTN_SET_CLOCK	D
#define LINE_BTN_SET_CLOCK	1
#define PORT_BTN_SET_ALARM	D
#define LINE_BTN_SET_ALARM	2
#define PORT_BTN_STOP_ALARM	D
#define LINE_BTN_STOP_ALARM	3
#define PORT_BTN_UP			D
#define LINE_BTN_UP			4
#define PORT_BTN_DOWN		D
#define LINE_BTN_DOWN		5
#define PORT_BTN_MODE		D
#define LINE_BTN_MODE		6
#define PORT_BTN_SNOOZE		D
#define LINE_BTN_SNOOZE		7
#define PORT_SWITCH			D	
#define LINE_SWITCH			0

#define PORT_DISPLAY_A0		B
#define LINE_DISPLAY_A0		0
#define PORT_DISPLAY_RESET	D
#define LINE_DISPLAY_RESET	0

#endif /* CONSTANTS_H_ */