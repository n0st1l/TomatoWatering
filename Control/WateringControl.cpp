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
	this->waitTimer = new ATimer();
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
	delete this->waitTimer;
	this->waitTimer = NULL;

	if(wateringControl != 0)
	{
		delete this->wateringControl;
		this->wateringControl = NULL;
	}
}

void WateringControl::setWateringScreen(WateringScreen* wateringScreen) {
	this->wateringScreen = wateringScreen;
}

void WateringControl::cycleTask() {
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

void WateringControl::setValve(int potIndex,
		DigitalOutputState_t digitalOutputState) {

	String debugMsg = "setValve(int " + String(potIndex) + "DigitalOutputState_t " + String(digitalOutputState) + ")";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	switch(potIndex + 1)
	{
	case 1:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_1, digitalOutputState);
		break;
	case 2:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_2, digitalOutputState);
		break;
	case 3:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_3, digitalOutputState);
		break;
	case 4:
		this->hardwareControl->setDigitalOutput(eDigitalOutputTypeValve_4, digitalOutputState);
		break;
	default:
		break;
	}
}

void WateringControl::disableAllValves() {
	String debugMsg = "disableAllValves()";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	for(int i = 0 ; i < NUMBEROFPOTS ; i++)
	{
		this->setValve(i, eDigitalOutputStateDisabled);
	}
}

void WateringControl::setPump(DigitalOutputState_t digitalOutputState) {

	String debugMsg = "setPump(DigitalOutputState_t " + String(digitalOutputState) + ")";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	this->hardwareControl->setDigitalOutput(eDigitalOutputTypePump, digitalOutputState);
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

void WateringControl::processWateringControlState() {
	switch(this->wateringMode->getWateringModeState()->getActualWateringControlState())
	{
	case eWateringControlStateIdle:

		break;
	case eWateringControlStateCheckIfShouldStartWatering:

		break;
	case eWateringControlStateStartWatering:

		break;
	case eWateringControlStateEnableValve:
		this->setValve(this->wateringMode->getWateringModeState()->getActualPotIndex(), eDigitalOutputStateEnabled);

		this->waitTimer->setTimeout(SECONDS_TO_MILLISECONDS(1));
		this->waitTimer->restart();

		this->wateringMode->getWateringModeState()->setActualWateringControlState(eWateringControlStateWaitAfterEnableValve);
		break;
	case eWateringControlStateWaitAfterEnableValve:
		if(this->waitTimer->onExpired())
		{
			this->waitTimer->stop();

			this->wateringMode->getWateringModeState()->setActualWateringControlState(eWateringControlStateEnablePump);
		}
		break;
	case eWateringControlStateEnablePump:
		this->setPump(eDigitalOutputStateEnabled);

		this->wateringMode->getWateringModeState()->setActualWateringControlState(eWateringControlStateCheckIfShouldStopWatering);
		break;
	case eWateringControlStateCheckIfShouldStopWatering:

		break;
	case eWateringControlStateDisablePump:
		this->setPump(eDigitalOutputStateDisabled);

		this->waitTimer->setTimeout(SECONDS_TO_MILLISECONDS(1));
		this->waitTimer->restart();

		this->wateringMode->getWateringModeState()->setActualWateringControlState(eWateringControlStateWaitAfterDisablePump);
		break;
	case eWateringControlStateWaitAfterDisablePump:
		if(this->waitTimer->onExpired())
		{
			this->waitTimer->stop();

			this->wateringMode->getWateringModeState()->setActualWateringControlState(eWateringControlStateDisableValves);
		}
		break;
	case eWateringControlStateDisableValves:
		this->disableAllValves();
		break;
	default:

		break;
	}
}

float WateringControl::getWaterQuantity(float actTemp, float minTemp, float maxTemp, float minQuantity, float maxQuantity) {

	String debugMsg = "getWaterQuantity(float " + String(actTemp) +
			", float " + String(minTemp) +
			", float " + String(maxTemp) +
			", float " + String(minQuantity) +
			", float " + String(maxQuantity) + ")";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	float gain = 0;
	float offset = 0;
	float waterQuantity = 0;

	HelperClass::Instance()->getGainAndOffset(minTemp, maxTemp, minQuantity, maxQuantity, &gain, &offset);
	waterQuantity = gain * actTemp + offset;
	waterQuantity = constrain(waterQuantity, minQuantity, maxQuantity);

	debugMsg = "waterQuantity " + String(waterQuantity);
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

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
