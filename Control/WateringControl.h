/*
 * WateringControl.h
 *
 *  Created on: 03.11.2015
 *      Author: Administrator
 */

#ifndef CONTROL_WATERINGCONTROL_H_
#define CONTROL_WATERINGCONTROL_H_


#include "HardwareControl.h"
#include "../Help/HelperClass.h"
#include "../Model/OperatingState.h"
#include "../Model/WateringMode.h"


class WateringControl {
public:
	static WateringControl *Instance();
	virtual ~WateringControl();

	void checkIfShouldSetWateringFlag();
	void checkIfShouldWatering();


private:
	WateringControl();
	static WateringControl* wateringControl;

	HardwareControl* hardwareControl;

	OperatingState* operatingState;
	WateringMode* wateringMode;


};

#endif /* CONTROL_WATERINGCONTROL_H_ */
