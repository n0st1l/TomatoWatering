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
		if(this->wateringTimer->isActive())
		{
			this->updateDisplayProgress();
		}
	}

	// State Machine
	this->processWateringControlState();
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

	for(int i = 0 ; i < NumberOfPots ; i++)
	{
		this->setValve(i, eDigitalOutputStateDisabled);
	}
}

void WateringControl::setPump(DigitalOutputState_t digitalOutputState) {

	String debugMsg = "setPump(DigitalOutputState_t " + String(digitalOutputState) + ")";
	LOG_DAEMON_DEBUG(eWateringControl, debugMsg);

	this->hardwareControl->setDigitalOutput(eDigitalOutputTypePump, digitalOutputState);
}

void WateringControl::processWateringControlState() {
	WateringModeState* modeState = wateringMode->getWateringModeState();
	WateringSettings* actWateringSettings = modeState->getActualWateringSettings();
	bool actWateringSettingsIsValid = false;

	// Check if actual watering settings is valid
	if(actWateringSettings != NULL)
	{
		if(actWateringSettings->isValid() == true)
		{
			actWateringSettingsIsValid = true;
		}
	}

	switch(modeState->getActualWateringControlState())
	{
	case eWateringControlStateIdle:
		/*Update the display*/
		if(this->wateringScreen != NULL)
		{
			this->wateringScreen->updateStatus("IDLE");
			this->wateringScreen->updateTotalQuantity("TOTAL " + String(this->operatingState->getTotalWaterQuantity()) + " L");
			this->wateringScreen->updateDailyQuantity("DAILY " + String(this->operatingState->getDailyWaterQuantity()) + " L");
		}

		modeState->setActualWateringControlState(eWateringControlStateCheckIfShouldStartWatering);
		break;
	case eWateringControlStateCheckIfShouldStartWatering:
		if(modeState->getIsWatering() == true)
		{
			if(actWateringSettingsIsValid == true)
			{
				modeState->setActualWateringControlState(eWateringControlStateStartWatering);
			}
			else
			{
				// TODO Implement this
			}
		}

		break;
	case eWateringControlStateStartWatering:
		/*Update the display*/
		if( (this->wateringScreen != NULL) && (actWateringSettingsIsValid == true))
		{
			this->wateringScreen->updateStatus("WATERING " + this->wateringMode->getPot(actWateringSettings->getPotIndex())->getPotName());
		}

		modeState->setActualWateringControlState(eWateringControlStateStartTimer);
		break;
	case eWateringControlStateStartTimer:
		if(actWateringSettingsIsValid == true)
		{
			float waterQuantity = this->getWaterQuantity(operatingState->getActualTemperature(), Min_Temp, Max_Temp, modeState->getActualWateringSettings()->getMinWaterQuantity(), modeState->getActualWateringSettings()->getMaxWaterQuantity());

			//Save new totalWaterQuantity
			this->operatingState->addToTotalWaterQuantity((waterQuantity / 1000));
			//Save new dailyWaterQuantity
			this->operatingState->addToDailyWaterQuantity((waterQuantity / 1000));
			//Save new totalWaterQuantity for the pot
			this->wateringMode->getPot(actWateringSettings->getPotIndex())->addToTotalWaterQuantity((waterQuantity / 1000));

			float pumpWorkTime = waterQuantity / (PUMP_OUTPUT * wateringMode->getPot(modeState->getActualWateringSettings()->getPotIndex())->getCorrectionFactor());
			this->wateringTimer->setTimeout(SECONDS_TO_MILLISECONDS(pumpWorkTime + Pump_Wait_Time));
			this->wateringTimer->restart();

			/*Update the display*/
			if(this->wateringScreen != NULL)
			{
				this->wateringScreen->updateTotalQuantity("QUANTITY " + String((int)waterQuantity) + " ML");
			}

			modeState->setActualWateringControlState(eWateringControlStateEnableValve);
		}
		else
		{
			modeState->setActualWateringControlState(eWateringControlStateStopWatering);
		}
		break;
	case eWateringControlStateEnableValve:
		if(actWateringSettingsIsValid == true)
		{
			this->setValve(actWateringSettings->getPotIndex(), eDigitalOutputStateEnabled);

			this->waitTimer->setTimeout(SECONDS_TO_MILLISECONDS(Pump_Wait_Time));
			this->waitTimer->restart();

			modeState->setActualWateringControlState(eWateringControlStateWaitAfterEnableValve);
		}
		else
		{
			modeState->setActualWateringControlState(eWateringControlStateStopWatering);
		}
		break;
	case eWateringControlStateWaitAfterEnableValve:
		if(this->waitTimer->onExpired())
		{
			this->waitTimer->stop();

			modeState->setActualWateringControlState(eWateringControlStateEnablePump);
		}
		break;
	case eWateringControlStateEnablePump:
		this->setPump(eDigitalOutputStateEnabled);

		modeState->setActualWateringControlState(eWateringControlStateCheckIfShouldStopWatering);
		break;
	case eWateringControlStateCheckIfShouldStopWatering:
		if( (modeState->getIsWatering() == false) ||
				(this->wateringTimer->onExpired()) )
		{
			modeState->setActualWateringControlState(eWateringControlStateStopWatering);
		}
		break;
	case eWateringControlStateStopWatering:
		this->wateringTimer->stop();

		modeState->setActualWateringControlState(eWateringControlStateDisablePump);
		break;
	case eWateringControlStateDisablePump:
		this->setPump(eDigitalOutputStateDisabled);

		this->waitTimer->setTimeout(SECONDS_TO_MILLISECONDS(Pump_Wait_Time));
		this->waitTimer->restart();

		modeState->setActualWateringControlState(eWateringControlStateWaitAfterDisablePump);
		break;
	case eWateringControlStateWaitAfterDisablePump:
		if(this->waitTimer->onExpired())
		{
			this->waitTimer->stop();

			modeState->setActualWateringControlState(eWateringControlStateDisableValves);
		}
		break;
	case eWateringControlStateDisableValves:
		this->disableAllValves();

		modeState->setActualWateringControlState(eWateringControlStatePostProcessing);
		break;
	case eWateringControlStatePostProcessing:
		if(actWateringSettingsIsValid == true)
		{
			modeState->getActualWateringSettings()->setShouldWatering(false);
		}

		modeState->setActualWateringControlState(eWateringControlStateResetModel);
		break;
	case eWateringControlStateResetModel:
		modeState->setIsWatering(false);
		modeState->setActualWateringSettings(NULL);
		modeState->setActualWateringControlState(eWateringControlStateIdle);
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
