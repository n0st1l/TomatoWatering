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
	mainScreen = NULL;

	twoSecondTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 2));
	oneMinuteTimer = new ATimer(MINUTES_TO_MILLISECONDS((unsigned long) 1));
	twoSecondTimer->restart();
	oneMinuteTimer->restart();

	firstStart = true;
}

OperatingControl::~OperatingControl() {
	this->hardwareControl = NULL;

	this->operatingState = NULL;

	this->mainScreen = NULL;

	delete this->twoSecondTimer;
	this->twoSecondTimer = NULL;

	delete this->oneMinuteTimer;
	this->oneMinuteTimer = NULL;

	if(operatingControl != 0)
	{
		delete this->operatingControl;
		this->operatingControl = NULL;
	}
}

void OperatingControl::setMainScreen(MainScreen* mainScreen) {
	this->mainScreen = mainScreen;
}

void OperatingControl::cycleTask() {
	if(this->firstStart == true)
	{
		LOG_DAEMON_DEBUG(eOperatingControl, "firstStart");
		this->onTwoSecondsTimerTimeout();
		this->onOneMinuteTimerTimeout();
		this->firstStart = false;
	}

	if(twoSecondTimer->onRestart())
	{
		this->onTwoSecondsTimerTimeout();
	}

	if(oneMinuteTimer->onRestart())
	{
		this->onOneMinuteTimerTimeout();
	}
}

void OperatingControl::onTwoSecondsTimerTimeout() {
	LOG_DAEMON_DEBUG(eOperatingControl, "onTwoSecondsTimerTimeout()");

	if(this->operatingState != NULL && this->hardwareControl != NULL)
	{
		operatingState->setActualTime(hardwareControl->getTime());
		operatingState->setActualDate(hardwareControl->getDate());

		if(this->mainScreen != NULL)
		{
			mainScreen->updateTime(operatingState->getActualTime()->getTimeString("hh:mm"));
		}
	}
}

void OperatingControl::onOneMinuteTimerTimeout() {
	LOG_DAEMON_DEBUG(eOperatingControl, "onOneMinuteTimerTimeout()");

	if(this->operatingState != NULL && this->hardwareControl != NULL)
	{
		operatingState->setActualHumidty(hardwareControl->getHumidity());
		operatingState->setActualTemperature(hardwareControl->getTemperature());

		if(this->mainScreen != NULL)
		{
			mainScreen->updateTemperature(String(operatingState->getActualTemperature()));
		}
	}
}
