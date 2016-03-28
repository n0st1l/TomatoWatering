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
#include "../Screen/WateringScreen.h"
#include <ATimer.h>


class WateringControl {
public:
	static WateringControl *Instance();
	virtual ~WateringControl();

	void setWateringScreen(WateringScreen* wateringScreen);

	void update();

	void startAutoWatering(WateringSettings* wateringSettings);
	void startManualWatering(int potIndex);
	void stopWatering();


private:
	WateringControl();
	static WateringControl* wateringControl;

	HardwareControl* hardwareControl;

	OperatingState* operatingState;
	WateringMode* wateringMode;

	WateringScreen* wateringScreen;

	ATimer* oneSecondTimer;
	ATimer* wateringTimer;

	void startWatering(int potIndex);

	void checkIfShouldSetWateringFlag();
	void checkIfShouldWatering();

	float getWaterQuantity(float actTemp, float minTemp, float maxTemp, float minQuantity, float maxQuantity);

	void updateDisplayProgress();


};

#endif /* CONTROL_WATERINGCONTROL_H_ */
