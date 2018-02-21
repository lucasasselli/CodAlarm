#ifndef CLOCK_H_
#define CLOCK_H_

#define D_SEC 3600*24
#define H_SEC 3600
#define M_SEC 60

enum t_mode { H12, H24 };

/**
 *  Implements most clock functions.
 */
class Clock
{
	private:
	/**
	 * Current clock value in seconds.
	 */
	long count;
	
	/**
	 * \brief Increments the clock value by a certain value in seconds.
	 * If the clock value overflows the number of seconds in a day, the value restarts from 0 plus the difference.
	 * \param val seconds
	 * 
	 * \return void
	 */
	void _add(int);
	
	public:

	/**
	 * Clock constructor.
	 * \return 
	 */
	Clock();
	
	
	/**
	 * \brief Increments the clock value by 1 second.
	 * If the clock value overflows the number of seconds in a day, the value restarts from 0.
	 * \return void
	 */
	void tick();
	
	/**
	 * Returns the clock value in seconds.
	 * \return seconds
	 */
	long getValue();
	
	
	/**
	 * Sets time to the value of another clock.
	 * \param c source clock
	 * \return void
	 */
	void sync(Clock);
	
	/**
	 * \brief Increases the current number of minutes by a value.
	 * If the clock value overflows the number of seconds in a day, the value restarts from 0 plus the difference.
	 * \param x minutes
	 * \return void
	 */
	void setMin(int);
	
	/**
	 * \brief Increases the current number of hours by a value.
	 * If the clock value overflows the number of seconds in a day, the value restarts from 0 plus the difference.
	 * \param x hours
	 * \return void
	 */
	void setHour(int);
	
	/**
	 * Returns the clock value in hours according to the specified format.
	 * \param mode 12/24 hour format
	 * \return Clock value in hours
	 */
	int getHour(t_mode);
	
	
	/**
	 * Returns the clock value in minutes.
	 * \return Clock value in minutes
	 */
	int getMin();
	
	/**
	 * Returns if the hour is either an AM or PM one.
	 * \return true if Am
	 */
	bool isAm();
};

#endif /* CLOCK_H_ */