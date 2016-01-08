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
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if( (actSettings->getWatered() == false) &&
				(this->operatingState->getActualTime()->secsTo(actSettings->getWateringTime()) < 0) )
		{
			actSettings->setShouldWatering(true);
		}
	}
}

void WateringControl::checkIfShouldWatering() {
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if( (actSettings->getWatered() == false) &&
				(actSettings->getShouldWatering() == true) &&
				(this->wateringMode->getWateringModeState()->getIsWatering() == false) )
		{
			this->startAutoWatering(i);
			return;
		}
	}
}

void WateringControl::startAutoWatering(int wateringSettingsIndex) {
	if( (this->wateringMode->getWateringModeState()->getIsWatering() == true) ||
			(this->wateringMode->getWateringModeState()->getIsAutomaticMode() == false) )
	{
		//Is already started
		return;
	}
	this->wateringMode->getWateringModeState()->setIsWatering(true);
	this->wateringMode->getWateringModeState()->setActualWateringSettingsIndex(wateringSettingsIndex);

	this->startWatering(this->wateringMode->getWateringSettings(wateringSettingsIndex)->getPotIndex());

	//TODO start timer
}

void WateringControl::startManualWatering(int potIndex) {
	if( (this->wateringMode->getWateringModeState()->getIsWatering() == true) ||
			(this->wateringMode->getWateringModeState()->getIsManualMode() == false) )
	{
		//Is already started
		return;
	}
	this->wateringMode->getWateringModeState()->setIsWatering(true);

	this->startWatering(potIndex);
}

void WateringControl::stopWatering() {
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypePump, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_1, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_2, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_3, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_4, eDigitalOutputStateDisabled);

	this->wateringMode->getWateringSettings(this->wateringMode->getWateringModeState()->getActualWateringSettingsIndex())->setWatered(true);
	this->wateringMode->getWateringModeState()->setActualWateringSettingsIndex(-1);
	//TODO stop timer
	this->wateringMode->getWateringModeState()->setIsWatering(false);
}

void WateringControl::startWatering(int potIndex) {
	switch(potIndex)
	{
	case 1:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_1, eDigitalOutputStateEnabled);
		break;
	case 2:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_2, eDigitalOutputStateEnabled);
		break;
	case 3:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_3, eDigitalOutputStateEnabled);
		break;
	case 4:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_4, eDigitalOutputStateEnabled);
		break;
	default:
		break;
	}
	delay(500);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypePump, eDigitalOutputStateEnabled);
}
