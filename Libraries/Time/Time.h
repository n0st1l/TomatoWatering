/*
 * Time.h
 *
 *  Created on: 13.07.2015
 *      Author: Administrator
 */

#ifndef LIBRARIES_TIME_H_
#define LIBRARIES_TIME_H_

namespace Time {

class Time {
public:
	Time();
	Time(int p_hour, int p_minutes);
	virtual ~Time();

	inline int getHour() { return hour; }
	void setHour(int hour);

	inline int getMinutes() { return minutes; }
	void setMinutes(int minutes);

private:
	int hour;
	int minutes;
};

} /* namespace Time */

#endif /* LIBRARIES_TIME_H_ */
