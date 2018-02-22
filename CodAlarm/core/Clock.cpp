#include "Clock.h"

Clock::Clock(){
	
	// Reset count
	count = 0;
}

void Clock::_add(int val){
	
	// Increment count by val
	count += val;
	
	// count is circular from 0 to DAY_SEC
	if(count < 0){
		count = D_SEC - count;
	}else if(count > D_SEC){
		count = count - D_SEC;
	}		
}

void Clock::tick(){
	_add(1);
}

long Clock::getValue(){
	return count;
}

void Clock::sync(Clock source){
	count = source.getValue();
}

void Clock::setMin(int x){
	_add(x*M_SEC);
}

void Clock::setHour(int x){
	_add(x*H_SEC);
}

int Clock::getHour(t_mode mode){
	int x = count/H_SEC;
	
	if(mode == H12)
		return x > 12 ? x-11 : x;
	else
		return x;
}

int Clock::getMin(){
	return count%H_SEC;
}

bool Clock::isAm(){
	int x = count/H_SEC;
	
	return x > 12 ? true : false;
}