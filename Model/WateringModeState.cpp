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
	this->isAutomaticMode = true;
	this->actualWateringSettingsIndex = -1;
	this->actualPotIndex = -1;
	this->actualWateringControlState = eWateringControlStateIdle;
}

WateringModeState::~WateringModeState() {
	if(wateringModeState != 0)
	{
		delete this->wateringModeState;
		this->wateringModeState = 0;
	}
}

void WateringModeState::setIsWatering(bool isWatering) {
	this->isWatering = isWatering;
}

void WateringModeState::setIsAutomaticMode(bool isAutomaticMode) {
	this->isAutomaticMode = isAutomaticMode;
}

void WateringModeState::setActualWateringSettingsIndex(
		int actualWateringSettingsIndex) {
	this->actualWateringSettingsIndex = actualWateringSettingsIndex;
}

void WateringModeState::setActualPotIndex(int actualPotIndex) {
	this->actualPotIndex = actualPotIndex;
}

void WateringModeState::setActualWateringControlState(
		WateringControlState_t actualWateringControlState) {
	this->actualWateringControlState = actualWateringControlState;
}
