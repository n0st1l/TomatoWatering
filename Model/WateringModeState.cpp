/*
 * WateringModeState.cpp
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#include "WateringModeState.h"

WateringModeState::WateringModeState() {
	this->isWatering = false;
	this->isAutomaticMode = false;
	this->isManualMode = false;
	this->actualWateringSettingsIndex = -1;
}

WateringModeState::~WateringModeState() {
	// TODO Auto-generated destructor stub
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

void WateringModeState::setActualWateringSettingsIndex(
		int actualWateringSettingsIndex) {
	this->actualWateringSettingsIndex = actualWateringSettingsIndex;
}
