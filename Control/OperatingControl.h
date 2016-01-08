/*
 * OperatingControl.h
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#ifndef CONTROL_OPERATINGCONTROL_H_
#define CONTROL_OPERATINGCONTROL_H_


#include "HardwareControl.h"
#include "../Help/HelperClass.h"
#include "../Model/OperatingState.h"


class OperatingControl {
public:
	static OperatingControl *Instance();
	virtual ~OperatingControl();

	void onTenSecondsTimerTimeout();
	void onOneMinuteTimerTimeout();


private:
	OperatingControl();
	static OperatingControl* operatingControl;

	HardwareControl* hardwareControl;
	OperatingState* operatingState;


};

#endif /* CONTROL_OPERATINGCONTROL_H_ */
