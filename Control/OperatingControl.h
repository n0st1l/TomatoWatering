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
#include "../Screen/MainScreen.h"
#include <ATimer.h>


class OperatingControl {
public:
	static OperatingControl *Instance();
	virtual ~OperatingControl();

	void setMainScreen(MainScreen* mainScreen);

	void cycleTask();


private:
	OperatingControl();
	static OperatingControl* operatingControl;

	HardwareControl* hardwareControl;
	OperatingState* operatingState;
	MainScreen* mainScreen;

	ATimer* twoSecondTimer;
	ATimer* oneMinuteTimer;

	bool firstStart;

	void onTwoSecondsTimerTimeout();
	void onOneMinuteTimerTimeout();

	void checkIfShouldResetDailyWaterQuantity();


};

#endif /* CONTROL_OPERATINGCONTROL_H_ */
