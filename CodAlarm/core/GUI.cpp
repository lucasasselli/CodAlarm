#include "GUI.h"


GUI::GUI(CodAlarm* _ca){
	ca = _ca;
}

void GUI::_drawSymbol(int pos_x, int pos_y, t_symbol c, int scale){
	
	int width = SIZE_BASE_W;
	int height = SIZE_BASE_H;
	
	// Upscaling
	width *= scale;
	height *= scale;
	
	// Draw loop
	for(int y=pos_y; y<pos_y+height; y++){
		for(int x=pos_x; x<pos_x+width; x++)
		{
			int block = ((y-pos_y)/2)/scale;
			int pos = (7-(((y-pos_y)%2)*4+(x-pos_x)))/scale;
			
			char buf;

			switch(c){
				case SYM_0:
				buf=number_0[block];
				break;

				case SYM_1:
				buf=number_1[block];
				break;

				case SYM_2:
				buf=number_2[block];
				break;

				case SYM_3:
				buf=number_3[block];
				break;

				case SYM_4:
				buf=number_4[block];
				break;

				case SYM_5:
				buf=number_5[block];
				break;

				case SYM_6:
				buf=number_6[block];
				break;

				case SYM_7:
				buf=number_7[block];
				break;

				case SYM_8:
				buf=number_8[block];
				break;

				case SYM_9:
				buf=number_9[block];
				break;
				
				case SYM_P:
				buf=letter_p[block];
				break;
				
				case SYM_A:
				buf=letter_a[block];
				break;
				
				case SYM_M:
				buf=letter_m[block];
				break;

				case SYM_COLUMN:
				buf=column[block];
				break;
				
				case SYM_BELL_L:
				buf=bell_left[block];
				break;
				
				case SYM_BELL_R:
				buf=bell_right[block];
				break;
			}

			int value = CHECK_BIT(buf,pos);
			
			ca->display.setPixel(x,y, value);
		}
	}
}

bool GUI::_blinkState(){
	// This is only cosmetic, no precise timing is required!
	return TCNT1 > 7812 ? true : false;
}

void GUI::draw(){
	
	// Clear screen buffer
	ca->display.clear();
	
	// Draw clock digits
	int clock_hour = ca->clock.getHour(ca->mode);
	int clock_min = ca->clock.getMin();
	
	if((ca->state != SET_CLOCK1) | (ca->state != SET_CLOCK1 && _blinkState())){
		t_symbol hour_h = (t_symbol) (H_DDIG(clock_hour));
		t_symbol hour_l = (t_symbol) (L_DDIG(clock_hour));
		_drawSymbol(17,5, hour_h, SCALE_BIG);	// 1st hour digit
		_drawSymbol(37,5, hour_l, SCALE_BIG);	// 2nd hour digit
	}
	
	_drawSymbol(55,5, SYM_COLUMN, SCALE_BIG);				// Clock column
	
	if((ca->state != SET_CLOCK2) | (ca->state != SET_CLOCK2 && _blinkState())){
		t_symbol min_h = (t_symbol) (H_DDIG(clock_min));
		t_symbol min_l = (t_symbol) (L_DDIG(clock_min));
		_drawSymbol(73,5, min_h, SCALE_BIG);	// 1st min digit
		_drawSymbol(93,5, min_l, SCALE_BIG);	// 2nd min digit
	}
	
	if(ca->mode == H12){
		if (ca->clock.isAm()){
			_drawSymbol(111, 5, SYM_A, SCALE_SMALL);
		}else{
			_drawSymbol(111, 5, SYM_A, SCALE_SMALL);
		}
		_drawSymbol(116, 5, SYM_M, SCALE_SMALL);
	}
	
	// Draw alarm digits
	int alarm_hour = ca->alarm.getHour(ca->mode);
	int alarm_min = ca->alarm.getMin();
		
	if((ca->state != SET_ALARM1) | (ca->state != SET_ALARM1 && _blinkState())){
		t_symbol hour_h = (t_symbol) (H_DDIG(alarm_hour));
		t_symbol hour_l = (t_symbol) (L_DDIG(alarm_hour));
		_drawSymbol(17,43, hour_h, SCALE_BIG);	// 1st hour digit
		_drawSymbol(27,43, hour_l, SCALE_BIG);	// 2nd hour digit
	}
		
	_drawSymbol(35,43, SYM_COLUMN, SCALE_BIG);				// Alarm column
		
	if((ca->state != SET_ALARM2) | (ca->state != SET_ALARM2 && _blinkState())){
		t_symbol min_h = (t_symbol) (H_DDIG(alarm_min));
		t_symbol min_l = (t_symbol) (L_DDIG(alarm_min));
		_drawSymbol(43,43, min_h, SCALE_BIG);	// 1st min digit
		_drawSymbol(53,43, min_l, SCALE_BIG);	// 2nd min digit
	}
		
	if(ca->mode == H12){
		if (ca->alarm.isAm()){
			_drawSymbol(63, 43, SYM_A, SCALE_SMALL);
			}else{
			_drawSymbol(63, 43, SYM_A, SCALE_SMALL);
		}
		_drawSymbol(68, 43, SYM_M, SCALE_SMALL);
	}
	
	// Draw alarm symbol
	if(ca->io.getSwitch()){
		_drawSymbol(77, 53, SYM_BELL_L, SCALE_SMALL);
		_drawSymbol(78, 53, SYM_BELL_R, SCALE_SMALL);
	}
	
	// Send screen update
	ca->display.update();
}