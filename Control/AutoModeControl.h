/*
 * AutoModeControl.h
 *
 *  Created on: 17.05.2016
 *      Author: Administrator
 */

#ifndef AUTOMODECONTROL_H_
#define AUTOMODECONTROL_H_


#include "../Help/HelperClass.h"
#include "../Model/OperatingState.h"
#include "../Model/WateringMode.h"
#include <ATimer.h>


class AutoModeControl {
public:
	static AutoModeControl *Instance();
	virtual ~AutoModeControl();

	void cycleTask();

	bool startWatering(WateringSettings* wateringSettings);


private:
	AutoModeControl();
	static AutoModeControl* autoModeControl;

	OperatingState* operatingState;
	WateringMode* wateringMode;

	ATimer* oneSecondTimer;

	void checkIfShouldSetWateringFlag();
	void checkIfShouldWatering();


};

#endif /* AUTOMODECONTROL_H_ */
