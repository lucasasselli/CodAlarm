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

class IO {
	
public:
    void init();

    bool getSwitch();

    void setLight(bool);
	
	void buzz();
	
	void setPressHandler(int, Handler);
	void setPressHandler(Handler);
	void setLongHandler(int, Handler);
	
	void checkPress();
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