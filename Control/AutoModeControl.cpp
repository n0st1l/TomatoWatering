/*
 * AutoModeControl.cpp
 *
 *  Created on: 17.05.2016
 *      Author: Administrator
 */

#include "AutoModeControl.h"


AutoModeControl* AutoModeControl::autoModeControl = 0;

AutoModeControl* AutoModeControl::Instance() {
	if(autoModeControl == 0)
	{
		autoModeControl = new AutoModeControl();
	}
	return autoModeControl;
}

AutoModeControl::AutoModeControl() {
	this->operatingState = OperatingState::Instance();
	this->wateringMode = WateringMode::Instance();

	this->oneSecondTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 1));
	this->oneSecondTimer->restart();
}

AutoModeControl::~AutoModeControl() {
	this->operatingState = NULL;
	this->wateringMode = NULL;

	delete this->oneSecondTimer;
	this->oneSecondTimer = NULL;

	if(autoModeControl != 0)
	{
		delete this->autoModeControl;
		this->autoModeControl = NULL;
	}
}

void AutoModeControl::cycleTask() {
	if(this->oneSecondTimer->onRestart())
	{
		// Only process if is in automatic mode
		if(this->wateringMode->getWateringModeState()->getIsAutomaticMode() == true)
		{
			this->checkIfShouldSetWateringFlag();
			this->checkIfShouldWatering();
		}
	}
}

bool AutoModeControl::startWatering(WateringSettings* wateringSettings) {
		String debugMsg = "startWatering(WateringSettings* wateringSettings)";
		LOG_DAEMON_DEBUG(eAutoModeControl, debugMsg);

	if(wateringSettings != 0)
	{
		if(wateringSettings->isValid() == true) {
			this->wateringMode->getWateringModeState()->setActualWateringSettings(wateringSettings);
			this->wateringMode->getWateringModeState()->setIsWatering(true);

			debugMsg = "valid wateringSettings, prepared model to start";
			LOG_DAEMON_DEBUG(eAutoModeControl, debugMsg);
			return true;
		}
	}

	debugMsg = "invalid wateringSettings";
	LOG_DAEMON_DEBUG(eAutoModeControl, debugMsg);
	return false;
}

/*!
 * Sets the watering flag if it's not already set, the time is equal to the actual time and it's not raining
 */
void AutoModeControl::checkIfShouldSetWateringFlag() {
	for(int i = 0 ; i < NumberOfWateringSettings ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if(actSettings != 0)
		{
			if(actSettings->isValid() == true) {
				if( (actSettings->getShouldWatering() == false) &&
						(this->operatingState->getActualTime()->secsTo(actSettings->getWateringTime()) < 0) &&
						(this->operatingState->getActualTime()->secsTo(actSettings->getWateringTime()) > -4) &&
						(this->operatingState->getActualHumidity() < Rain_Threshold) )
				{
					actSettings->setShouldWatering(true);
				}
			}
		}
	}
}

void AutoModeControl::checkIfShouldWatering() {
	for(int i = 0 ; i < NumberOfWateringSettings ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if(actSettings != 0)
		{
			if(actSettings->isValid() == true) {
				if( (actSettings->getShouldWatering() == true) &&
						(this->wateringMode->getWateringModeState()->getIsWatering() == false) )
				{
					this->startWatering(actSettings);
					return;
				}
			}
		}
	}
}
