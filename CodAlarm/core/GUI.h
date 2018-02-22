#ifndef GUI_H_
#define GUI_H_

#include <avr/io.h>

#include "../constants.h"
#include "CodAlarm.h"

/** Returns the units digit for a decimal value */
#define L_DDIG(x) x%10

/** Returns the tens digit for a decimal value */
#define H_DDIG(x) x/10

/** Symbol width in pixel  */
#define SIZE_BASE_W		4

/** Symbol height in pixel */
#define SIZE_BASE_H		8

#define SCALE_SMALL		1
#define SCALE_NORMAL	2
#define SCALE_BIG		4

/** Symbol type */
enum t_symbol {
	SYM_0,
	SYM_1,
	SYM_2,
	SYM_3,
	SYM_4,
	SYM_5,
	SYM_6,
	SYM_7,
	SYM_8,
	SYM_9,
	SYM_P,
	SYM_A,
	SYM_M,
	SYM_COLUMN,
	SYM_BELL_R,	
	SYM_BELL_L,	
};

// Numbers
static const char number_0[4]   = {0xF9, 0x99, 0x99, 0xF0}; // Number 0
static const char number_1[4]   = {0x11, 0x11, 0x11, 0x10}; // Number 1, Hey!
static const char number_2[4]   = {0xF1, 0x1F, 0x88, 0xF0}; // Number 2
static const char number_3[4]   = {0xF1, 0x1F, 0x11, 0xF0}; // Number 3
static const char number_4[4]   = {0x99, 0x9F, 0x11, 0x10}; // Number 4
static const char number_5[4]   = {0xF8, 0x8F, 0x11, 0xF0}; // Number 5
static const char number_6[4]   = {0xF8, 0x8F, 0x99, 0xF0}; // Number 6
static const char number_7[4]   = {0xF1, 0x11, 0x11, 0x10}; // Number 7
static const char number_8[4]   = {0xF9, 0x9F, 0x99, 0xF0}; // Number 8
static const char number_9[4]   = {0xF9, 0x9F, 0x11, 0xF0}; // Number 9

// Letters
static const char letter_p[4]   = {0xF9, 0x9F, 0x88, 0x88}; // Letter P
static const char letter_a[4]   = {0xF9, 0x9F, 0x99, 0x99}; // Letter A
static const char letter_m[4]   = {0x9F, 0x99, 0x99, 0x99}; // Letter M

// Symbols
static const char column[4]     = {0x06, 0x60, 0x06, 0x60};	// Symbol ':'

// Graphic
static const char bell_left[4]  = {0x11, 0x33, 0x37, 0xF1}; // Left half of bell icon
static const char bell_right[4] = {0x88, 0xCC, 0xCE, 0xF8}; // Right half of bell icon

/**
 * Handles the graphical user interface on the display by controlling the Display instance in CodAlarm.
 */
class GUI {

public:
    /**
     * Class constructor. Used to pass a pointer to an instance of CodAlarm.
     * \param Pointer to CodAlarm Object instance.
     * \return 
     */
    GUI(CodAlarm*);

    /**
     * Draws the interface on the screen.
     * \return void
     */
    void draw();

private:
	/** Pointer the instance of CodAlarm passed in the constructor */
    CodAlarm* ca;
	
	
    /**
	 * Draws a symbol on the screen at the specified coordinate (upper left corner of the symbol), with
	 * a given upscale. Each symbol has an aspect ratio of 1:2 and is a 4x8 pixel matrix stored in an array
	 * of 4 byes. Upscaling allows to have multiple symbol sizes without without encoding multiple symbols; upscaling is
	 * performed by drawing the same symbol with bigger pixels. Three upscales values are used:
	 * - SCALE_SMALL  : No upscaling, 4x8 pixels
	 * - SCALE_NORMAL : 2x upscaling, 8x16 pixels
	 * - SCALE_BIG	  : 4x upscaling, 16x32 pixels
     * \param pos_x Horizontal position
     * \param pos_y Vertical position
     * \param c Character to be drawn
     * \param scale Upscale value
     * \return void
     */
    void _drawSymbol(int, int, t_symbol, int);
	
    /**
     * Provides the blinking animation by reading Timer1.
     * \return bool Commutes periodically.
     */
    bool _blinkState();
};



#endif /* GUI_H_ */