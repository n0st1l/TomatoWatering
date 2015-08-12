/*
 * Time.cpp
 *
 *  Created on: 13.07.2015
 *      Author: Administrator
 */

#include "Time.h"

namespace Time {

Time::Time() {
	this->hour = 0;
	this->minutes = 0;
}

Time::Time(int hour, int minutes) {
	this->hour = hour;
	this->minutes = minutes;
}

Time::~Time() {
	// TODO Auto-generated destructor stub
}

void Time::setHour(int hour)
{
	this->hour = hour;
}

void Time::setMinutes(int minutes)
{
	this->minutes = minutes;
}

} /* namespace Time */
