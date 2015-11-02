/*
 * OperatingControl.cpp
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#include "OperatingControl.h"


OperatingControl* OperatingControl::operatingControl = 0;

OperatingControl* OperatingControl::Instance()
{
	if(operatingControl == 0)
	{
		operatingControl = new OperatingControl();
	}
	return operatingControl;
}

OperatingControl::OperatingControl() {
	operatingState = OperatingState::Instance();

	this->realTimeClock = new DS1302(DS1302_RST, DS1302_IO, DS1302_SCK);
	this->setupRealTimeClock();

	this->dht22 = new DHT(DHT22_DATA, DHT22);
	this->dht22->begin();
}

OperatingControl::~OperatingControl() {
	delete this->operatingState;
	delete this->realTimeClock;
	delete this->dht22;
}

void OperatingControl::onTimerTimeout() {
	operatingState->setActualTime(realTimeClock->time());
	operatingState->setActualDate(realTimeClock->date());

	operatingState->setActualHumidty(dht22->readHumidity());
	operatingState->setActualTemperature(dht22->readTemperature());
}

void OperatingControl::setupRealTimeClock() {
	/* Initialize a new chip by turning off write protection and clearing the
	     clock halt flag. These methods needn't always be called. See the DS1302
	     datasheet for details. */
	realTimeClock->write_protect(false);
	realTimeClock->halt(false);

	/* Make a new time object to set the date and time */
	Time t(23, 59, 30);
	Date d(2015, 11, 2);

	/* Set the time and date on the chip */
	realTimeClock->time(t);
	realTimeClock->date(d);
}
