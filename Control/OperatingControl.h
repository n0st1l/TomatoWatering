/*
 * OperatingControl.h
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#ifndef CONTROL_OPERATINGCONTROL_H_
#define CONTROL_OPERATINGCONTROL_H_

#include "../Help/HelperClass.h"
#include "../Model/OperatingState.h"
#include <DS1302.h>
#include <DHT.h>


class OperatingControl {
public:
	static OperatingControl *Instance();
	virtual ~OperatingControl();

	void onTimerTimeout();


private:
	OperatingControl();
	static OperatingControl* operatingControl;

	OperatingState* operatingState;

	DS1302* realTimeClock;
	DHT* dht22;

	void setupRealTimeClock();


};

#endif /* CONTROL_OPERATINGCONTROL_H_ */
