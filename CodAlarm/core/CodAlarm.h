#ifndef CODALARM_H_
#define CODALARM_H_

#include "Clock.h"
#include "../hw/Display.h"
#include "../hw/IO.h"

enum t_state { IDLE, SET_CLOCK1, SET_CLOCK2, SET_ALARM1, SET_ALARM2, RING };

/**
 *  Wrapper class for the alarm configuration, state and time.
 */
class CodAlarm
{
	public:	
	
	CodAlarm(){
		state = IDLE;
		mode = H12;
		snoozed = false;
	}
	
	// Hardware
	Display display;
	IO io;
	
	// Time
	Clock clock;
	Clock alarm;
	Clock snooze;
	
	// State
	t_state state;
	t_mode mode;
	bool snoozed;
};


#endif /* CODALARM_H_ */