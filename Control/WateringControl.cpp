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

	this->oneSecondTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 1));
	this->oneSecondTimer->restart();
	this->wateringTimer = new ATimer();
}

WateringControl::~WateringControl() {
	delete this->hardwareControl;

	delete this->operatingState;
	delete this->wateringMode;

	delete this->oneSecondTimer;
	delete this->wateringTimer;

	if(wateringControl != 0)
	{
		delete this->wateringControl;
	}
}

void WateringControl::update() {
	if(this->oneSecondTimer->onRestart())
	{
		this->checkIfShouldSetWateringFlag();
		this->checkIfShouldWatering();
	}

	if(this->wateringTimer->onExpired())
	{
		this->stopWatering();
	}
}

void WateringControl::startAutoWatering(WateringSettings* settings) {
	if( (settings->isValid() == false) ||
			(this->wateringMode->getWateringModeState()->getIsWatering() == true) ||
			(this->wateringMode->getWateringModeState()->getIsAutomaticMode() == false) )
	{
		//Invalid settings, is already started or not in automatic mode
		return;
	}
	this->wateringMode->getWateringModeState()->setIsWatering(true);
	this->wateringMode->getWateringModeState()->setActualWateringSettings(settings);

	this->startWatering(settings->getPotIndex());

	float waterQuantity = this->getWaterQuantity(operatingState->getActualTemperature(), MIN_TEMP, MAX_TEMP, settings->getMinWaterQuantity(), settings->getMaxWaterQuantity());
	float pumpWorkTime = waterQuantity / PUMP_OUTPUT;

	this->wateringTimer->setTimeout(SECONDS_TO_MILLISECONDS(pumpWorkTime));
	this->wateringTimer->restart();
}

void WateringControl::startManualWatering(int potIndex) {
	if( (this->wateringMode->getWateringModeState()->getIsWatering() == true) ||
			(this->wateringMode->getWateringModeState()->getIsManualMode() == false) )
	{
		//Is already started or not in manual mode
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

	if(this->wateringMode->getWateringModeState()->getActualWateringSettings()->isValid() == true) {
		this->wateringMode->getWateringModeState()->getActualWateringSettings()->setShouldWatering(false);
	}
	this->wateringMode->getWateringModeState()->setActualWateringSettings(new WateringSettings());
	this->wateringMode->getWateringModeState()->setIsWatering(false);

	this->wateringTimer->stop();
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
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypePump, eDigitalOutputStateEnabled);
}

void WateringControl::checkIfShouldSetWateringFlag() {
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if(actSettings->isValid() == true) {
			if( (actSettings->getShouldWatering() == false) &&
					(this->operatingState->getActualTime()->secsTo(actSettings->getWateringTime()) < 0) &&
					(this->operatingState->getActualTime()->secsTo(actSettings->getWateringTime()) > -10))
			{
				actSettings->setShouldWatering(true);
			}
		}
	}
}

void WateringControl::checkIfShouldWatering() {
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if(actSettings->isValid() == true) {
			if( (actSettings->getShouldWatering() == true) &&
					(this->wateringMode->getWateringModeState()->getIsWatering() == false) )
			{
				this->startAutoWatering(actSettings);
				return;
			}
		}
	}
}

float WateringControl::getWaterQuantity(float actTemp, float minTemp, float maxTemp, float minQuantity, float maxQuantity) {
	float gain = 0;
	float offset = 0;
	float waterQuantity = 0;

	HelperClass::Instance()->getGainAndOffset(minTemp, maxTemp, minQuantity, maxQuantity, &gain, & offset);
	waterQuantity = gain * actTemp + offset;
	waterQuantity = constrain(waterQuantity, minQuantity, maxQuantity);

	return waterQuantity;
}
