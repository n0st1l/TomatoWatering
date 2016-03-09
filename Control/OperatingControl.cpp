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

	tenSecondTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 10));
	oneMinuteTimer = new ATimer(MINUTES_TO_MILLISECONDS((unsigned long) 1));
	tenSecondTimer->restart();
	oneMinuteTimer->restart();
}

OperatingControl::~OperatingControl() {
	delete this->hardwareControl;
	delete this->operatingState;

	delete this->tenSecondTimer;
	delete this->oneMinuteTimer;

	if(operatingControl != 0)
	{
		delete this->operatingControl;
	}
}

void OperatingControl::update() {
	if(tenSecondTimer->onRestart())
	{
		this->onTenSecondsTimerTimeout();
	}

	if(oneMinuteTimer->onRestart())
	{
		this->onOneMinuteTimerTimeout();
	}
}

void OperatingControl::onTenSecondsTimerTimeout() {
	//LOG_DAEMON_DEBUG(eOperatingControl, "onTenSecondsTimerTimeout()");

	operatingState->setActualTime(hardwareControl->getTime());
	operatingState->setActualDate(hardwareControl->getDate());
}

void OperatingControl::onOneMinuteTimerTimeout() {
	//LOG_DAEMON_DEBUG(eOperatingControl, "onOneMinuteTimerTimeout()");

	operatingState->setActualHumidty(hardwareControl->getHumidity());
	operatingState->setActualTemperature(hardwareControl->getTemperature());
}
