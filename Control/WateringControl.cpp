/*
 * WateringControl.cpp
 *
 *  Created on: 03.11.2015
 *      Author: Administrator
 */

#include "WateringControl.h"


WateringControl* WateringControl::wateringControl = 0;

WateringControl* WateringControl::Instance()
{
	if(wateringControl == 0)
	{
		wateringControl = new WateringControl();
	}
	return wateringControl;
}

WateringControl::WateringControl() {
	this->hardwareControl = HardwareControl::Instance();

	this->operatingState = OperatingState::Instance();
	this->wateringMode = WateringMode::Instance();
}

WateringControl::~WateringControl() {
	delete this->hardwareControl;

	delete this->operatingState;
	delete this->wateringMode;

	if(wateringControl != 0)
	{
		delete this->wateringControl;
	}
}

void WateringControl::checkIfShouldSetWateringFlag() {
}

void WateringControl::checkIfShouldWatering() {
}

