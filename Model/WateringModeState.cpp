/*
 * WateringModeState.cpp
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#include "WateringModeState.h"


WateringModeState* WateringModeState::wateringModeState = 0;

WateringModeState* WateringModeState::Instance()
{
	if(wateringModeState == 0)
	{
		wateringModeState = new WateringModeState();
	}
	return wateringModeState;
}

WateringModeState::WateringModeState() {
	this->isWatering = false;
	this->isAutomaticMode = false;
	this->isManualMode = false;
	this->actualWateringSettings = new WateringSettings();
}

WateringModeState::~WateringModeState() {
	if(wateringModeState != 0)
	{
		delete this->wateringModeState;
	}
}

void WateringModeState::setIsWatering(bool isWatering) {
	this->isWatering = isWatering;
}

void WateringModeState::setIsAutomaticMode(bool isAutomaticMode) {
	this->isAutomaticMode = isAutomaticMode;
}

void WateringModeState::setIsManualMode(bool isManualMode) {
	this->isManualMode = isManualMode;
}

void WateringModeState::setActualWateringSettings(
		WateringSettings* actualWateringSettings) {
	this->actualWateringSettings = actualWateringSettings;
}
