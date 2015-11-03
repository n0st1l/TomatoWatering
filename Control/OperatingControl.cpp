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
	hardwareControl = HardwareControl::Instance();
	operatingState = OperatingState::Instance();
}

OperatingControl::~OperatingControl() {
	delete this->hardwareControl;
	delete this->operatingState;

	if(operatingControl != 0)
	{
		delete this->operatingControl;
	}
}

void OperatingControl::onTimerTimeout() {
	operatingState->setActualTime(hardwareControl->getTime());
	operatingState->setActualDate(hardwareControl->getDate());

	operatingState->setActualHumidty(hardwareControl->getHumidity());
	operatingState->setActualTemperature(hardwareControl->getTemperature());
}
