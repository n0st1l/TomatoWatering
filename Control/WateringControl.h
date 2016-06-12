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

	void cycleTask();

//	void startAutoWatering(WateringSettings* wateringSettings);
//	void startManualWatering(int potIndex);
//	void stopWatering();


private:
	WateringControl();
	static WateringControl* wateringControl;

	HardwareControl* hardwareControl;

	OperatingState* operatingState;
	WateringMode* wateringMode;

	WateringScreen* wateringScreen;

	ATimer* oneSecondTimer;
	ATimer* wateringTimer;
	ATimer* waitTimer;

	static const int Pump_Wait_Time = 1;	//Unit: [s]

//	void startWatering(int potIndex);
	void setValve(int potIndex, DigitalOutputState_t digitalOutputState);
	void disableAllValves();
	void setPump(DigitalOutputState_t digitalOutputState);

	void processWateringControlState();

	float getWaterQuantity(float actTemp, float minTemp, float maxTemp, float minQuantity, float maxQuantity);

	void updateDisplayProgress();


};

#endif /* CONTROL_WATERINGCONTROL_H_ */
