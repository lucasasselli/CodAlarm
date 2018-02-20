#ifndef CLOCK_H_
#define CLOCK_H_

#define D_SEC 3600*24
#define H_SEC 3600
#define M_SEC 60

enum t_mode { H12, H24 };

class Clock
{
	private:
	
	long count;
	void _add(int val);
	
	public:

	Clock();
	
	void tick();
	long getValue();
	void sync(Clock);
	
	void setMin(int);
	void setHour(int);
	
	int getHour(t_mode);
	int getMin();
	bool isAm();
};

#endif /* CLOCK_H_ */