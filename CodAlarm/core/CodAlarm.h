#ifndef CODALARM_H_
#define CODALARM_H_

#include "Clock.h"
#include "../hw/Display.h"
#include "../hw/IO.h"

/**
 * Alarm clock state type.
 */
enum t_state { 
	/** System is idling. */
	IDLE, 
	/** Setting clock minutes */
	SET_CLOCK1, 
	/** Setting clock hours */
	SET_CLOCK2, 
	/** Setting alarm hours */
	SET_ALARM1,
	/** Setting alarm minutes */ 
	SET_ALARM2, 
	/** Alarm ringing */
	RING 
};

/**
 * Wrapper class for the system configuration, state and time.
 */
class CodAlarm
{
	public:	
	
	CodAlarm(){
		// Set defaults
		state = IDLE;
		mode = H24;
		snoozed = false; 
	}
	
	//////////////////////////////////////////////////////////////////////////
	// HARDWARE
	//////////////////////////////////////////////////////////////////////////
	
	/** Display wrapper instance. */
	Display display;
	
	/** IO wapper instance. */
	IO io;
	
	//////////////////////////////////////////////////////////////////////////
	// CLOCKS
	//////////////////////////////////////////////////////////////////////////
	
	/** Current clock value. Set by user. */
	Clock clock;
	
	/** Current alarm value. Set by user. */
	Clock alarm;
	
	/** Current clock value. Set by system. */
	Clock snooze;
	
	//////////////////////////////////////////////////////////////////////////
	// STATE
	//////////////////////////////////////////////////////////////////////////
	
	/** Current system state. */
	t_state state;
	
	/** Format of the hour. */
	t_mode mode;
	
	/** True if the Alarm has been snoozed during last ring state. */
	bool snoozed;
};


#endif /* CODALARM_H_ */