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

	this->wateringScreen = NULL;

	this->oneSecondTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 1));
	this->oneSecondTimer->restart();
	this->wateringTimer = new ATimer();
}

WateringControl::~WateringControl() {
	this->hardwareControl = NULL;

	this->operatingState = NULL;
	this->wateringMode = NULL;

	this->wateringScreen = NULL;

	delete this->oneSecondTimer;
	this->oneSecondTimer = NULL;
	delete this->wateringTimer;
	this->wateringTimer = NULL;

	if(wateringControl != 0)
	{
		delete this->wateringControl;
		this->wateringControl = NULL;
	}
}

void WateringControl::setWateringScreen(WateringScreen* wateringScreen) {
	this->wateringScreen = wateringScreen;
}

void WateringControl::update() {
	if(this->oneSecondTimer->onRestart())
	{
		this->checkIfShouldSetWateringFlag();
		this->checkIfShouldWatering();

		if(this->wateringTimer->isActive())
		{
			this->updateDisplayProgress();
		}
	}

	if(this->wateringTimer->onExpired())
	{
		this->stopWatering();
	}
}

void WateringControl::startAutoWatering(WateringSettings* settings) {

	String debugMsg = "startAutoWatering(WateringSettings* settings)";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	if( (settings->isValid() == false) ||
			(this->wateringMode->getWateringModeState()->getIsWatering() == true) ||
			(this->wateringMode->getWateringModeState()->getIsAutomaticMode() == false) )
	{
		//Invalid settings, is already started or not in automatic mode
		debugMsg = "Invalid settings, is already started or not in automatic mode";
		LOG_DAEMON_WARNING(eWateringControl, debugMsg);
		return;
	}
	this->wateringMode->getWateringModeState()->setIsWatering(true);
	this->wateringMode->getWateringModeState()->setActualWateringSettingsIndex(settings->getWateringSettingsIndex());

	debugMsg = "settings->getWateringSettingsIndex() = " + String(settings->getWateringSettingsIndex());
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);
	this->startWatering(settings->getPotIndex());

	float waterQuantity = this->getWaterQuantity(operatingState->getActualTemperature(), MIN_TEMP, MAX_TEMP, settings->getMinWaterQuantity(), settings->getMaxWaterQuantity());
	this->operatingState->setTotalWaterQuantity(this->operatingState->getTotalWaterQuantity() + (waterQuantity / 1000));
	float pumpWorkTime = waterQuantity / (PUMP_OUTPUT * wateringMode->getPot(settings->getPotIndex())->getCorrectionFactor());

	this->wateringTimer->setTimeout(SECONDS_TO_MILLISECONDS(pumpWorkTime));
	this->wateringTimer->restart();

	/*Update the display*/
	if(this->wateringScreen != NULL)
	{
		this->wateringScreen->updateStatus("WATERING " + this->wateringMode->getPot(settings->getPotIndex())->getPotName());
		this->wateringScreen->updateQuantity("QUANTITY " + String((int)waterQuantity) + " ML");
	}
}

void WateringControl::startManualWatering(int potIndex) {

	String debugMsg = "startManualWatering(int " + String(potIndex) + ")";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	if( (this->wateringMode->getWateringModeState()->getIsWatering() == true) ||
			(this->wateringMode->getWateringModeState()->getIsAutomaticMode() == true) )
	{
		//Is already started or not in manual mode
		debugMsg = "Is already started or not in manual mode";
		LOG_DAEMON_WARNING(eWateringControl, debugMsg);
		return;
	}
	this->wateringMode->getWateringModeState()->setIsWatering(true);

	this->startWatering(potIndex);

	/*Update the display*/
	if(this->wateringScreen != NULL)
	{
		this->wateringScreen->updateStatus("WATERING " + this->wateringMode->getPot(potIndex)->getPotName());
		this->wateringScreen->updateQuantity("");
		this->wateringScreen->updateProgress("");
	}
}

void WateringControl::stopWatering() {

	String debugMsg = "stopWatering()";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	this->hardwareControl->setDigitalOutput(eDigitalOutputTypePump, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_1, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_2, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_3, eDigitalOutputStateDisabled);
	this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_4, eDigitalOutputStateDisabled);

	if(this->wateringMode->getWateringSettings(this->wateringMode->getWateringModeState()->getActualWateringSettingsIndex())->isValid() == true) {
		this->wateringMode->getWateringSettings(this->wateringMode->getWateringModeState()->getActualWateringSettingsIndex())->setShouldWatering(false);
	}
	this->wateringMode->getWateringModeState()->setActualWateringSettingsIndex(-1);
	this->wateringMode->getWateringModeState()->setIsWatering(false);

	this->wateringTimer->stop();

	/*Update the display*/
	if(this->wateringScreen != NULL)
	{
		this->wateringScreen->updateStatus("READY");
		this->wateringScreen->updateQuantity("TOTAL " + String(this->operatingState->getTotalWaterQuantity()) + " L");
		this->wateringScreen->updateProgress("");
	}
}

void WateringControl::startWatering(int potIndex) {

	String debugMsg = "startWatering(int " + String(potIndex) + ")";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	switch(potIndex + 1)
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

		if(actSettings != 0)
		{
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
}

void WateringControl::checkIfShouldWatering() {
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		WateringSettings* actSettings = this->wateringMode->getWateringSettings(i);

		if(actSettings != 0)
		{
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
}

float WateringControl::getWaterQuantity(float actTemp, float minTemp, float maxTemp, float minQuantity, float maxQuantity) {

	//	String debugMsg = "getWaterQuantity(float " + String(actTemp) +
	//			", float " + String(minTemp) +
	//			", float " + String(maxTemp) +
	//			", float " + String(minQuantity) +
	//			", float " + String(maxQuantity) + ")";
	//	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	float gain = 0;
	float offset = 0;
	float waterQuantity = 0;

	HelperClass::Instance()->getGainAndOffset(minTemp, maxTemp, minQuantity, maxQuantity, &gain, &offset);
	waterQuantity = gain * actTemp + offset;
	waterQuantity = constrain(waterQuantity, minQuantity, maxQuantity);

	//	debugMsg = "waterQuantity " + String(waterQuantity);
	//	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	return waterQuantity;
}

void WateringControl::updateDisplayProgress() {
	if(this->wateringScreen != NULL)
	{
		String progress = "";
		int percent = this->wateringTimer->getPercentValue();
		for(int i = 0 ; i < 20 ; i++)
		{
			if(percent > 5)
			{
				progress = progress + "=";
				percent -= 5;
			}
		}
		this->wateringScreen->updateProgress(progress);
	}
}
