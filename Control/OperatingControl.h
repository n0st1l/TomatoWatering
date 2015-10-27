/*
 * OperatingControl.h
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#ifndef CONTROL_OPERATINGCONTROL_H_
#define CONTROL_OPERATINGCONTROL_H_

#include "..\Help\HelperClass.h"
#include <TimerOne.h>
#include <DS1302.h>
#include <DHT.h>


class OperatingControl {
public:
	OperatingControl();
	virtual ~OperatingControl();


private:
	DS1302* realTimeClock;
	DHT* dht22;

	void onOneSecondTimerTimeout();
};

#endif /* CONTROL_OPERATINGCONTROL_H_ */
