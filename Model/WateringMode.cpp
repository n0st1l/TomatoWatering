/*
 * WateringMode.cpp
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#include "WateringMode.h"


WateringMode* WateringMode::wateringMode = 0;

WateringMode* WateringMode::Instance()
{
	if(wateringMode == 0)
	{
		wateringMode = new WateringMode();
	}
	return wateringMode;
}

WateringMode::WateringMode() {

	for(int i = 0 ; i < NumberOfPots ; i++)
	{
		potArray[i] = new PotModel();
	}
	for(int i = 0 ; i < NumberOfWateringSettings ; i++)
	{
		wateringSettingsArray[i] = new WateringSettings();
	}
	wateringModeState = WateringModeState::Instance();
}

WateringMode::~WateringMode() {

	for(int i = 0 ; i < NumberOfPots ; i++)
	{
		delete potArray[i];
		potArray[i] = 0;
	}
	for(int i = 0 ; i < NumberOfWateringSettings ; i++)
	{
		delete wateringSettingsArray[i];
		wateringSettingsArray[i] = 0;
	}
	delete wateringModeState;
	wateringModeState = 0;

	if(wateringMode != 0)
	{
		delete wateringMode;
		wateringMode = 0;
	}
}

PotModel* WateringMode::getPot(int index) {

	if(HelperClass::Instance()->isIntInRange(index, 0, ARRAY_END(NumberOfPots) ) == true)
	{
		return potArray[index];
	}
	else
	{
		return 0;
	}
}

WateringSettings* WateringMode::getWateringSettings(int index) {

	if(HelperClass::Instance()->isIntInRange(index, 0, ARRAY_END(NumberOfWateringSettings) ) == true)
	{
		return wateringSettingsArray[index];
	}
	else
	{
		return 0;
	}
}

bool WateringMode::addPot(PotModel* newPot) {
	LOG_DAEMON_WARNING(eWateringMode, "addPot(PotModel* newPot)");

	if( potAlreadyExists(newPot) == false )
	{
		potArray[newPot->getPotIndex()]->setValuesFrom(newPot);

		String debugMsg = "potIndex " + String(newPot->getPotIndex()) +
				", potName " + newPot->getPotName() +
				", correctionFactor " + String(newPot->getCorrectionFactor(), 6);
		LOG_DAEMON_DEBUG(eWateringMode, debugMsg);
		return true;
	}

	return false;
}

bool WateringMode::removePot(int potIndexToRemove) {

	if(HelperClass::Instance()->isIntInRange(potIndexToRemove, 0, ARRAY_END(NumberOfPots) ) == true)
	{
		potArray[potIndexToRemove]->setPotIndex(-1);

		for(int i = 0 ; i < NumberOfWateringSettings ; i++)
		{
			if(wateringSettingsArray[i]->getPotIndex() == potIndexToRemove)
			{
				this->removeWateringSettings(i);
			}
		}

		return true;
	}

	return false;
}

bool WateringMode::addWateringSettings(WateringSettings* newWateringSettings) {
	LOG_DAEMON_WARNING(eWateringMode, "addWateringSettings(WateringSettings* newWateringSettings)");

	if( wateringSettingsAlreadyExists(newWateringSettings) == false )
	{
		wateringSettingsArray[newWateringSettings->getWateringSettingsIndex()]->setValuesFrom(newWateringSettings);

		String debugMsg = "wateringSettingsIndex " + String(newWateringSettings->getWateringSettingsIndex()) +
				", potIndex " + String(newWateringSettings->getPotIndex()) +
				", minWaterQuantity " + String(newWateringSettings->getMinWaterQuantity()) +
				", maxWaterQuantity " + String(newWateringSettings->getMaxWaterQuantity()) +
				", shouldWatering " + String(newWateringSettings->getShouldWatering()) +
				", wateringTime " + String(newWateringSettings->getWateringTime()->getTimeString("hh:mm"));
		LOG_DAEMON_DEBUG(eWateringMode, debugMsg);
		return true;
	}

	return false;
}

bool WateringMode::removeWateringSettings(int wateringSettingsIndexToRemove) {

	if(HelperClass::Instance()->isIntInRange(wateringSettingsIndexToRemove, 0, ARRAY_END(NumberOfWateringSettings) ) == true)
	{
		wateringSettingsArray[wateringSettingsIndexToRemove]->setWateringSettingsIndex(-1);
		wateringSettingsArray[wateringSettingsIndexToRemove]->setPotIndex(-1);

		return true;
	}

	return false;
}

int WateringMode::getFreeWateringSettingsIndex() {
	LOG_DAEMON_WARNING(eWateringMode, "getFreeWateringSettingsIndex()");

	for(int i = 0 ; i < NumberOfWateringSettings ; i++)
	{
		if(wateringSettingsArray[i]->getWateringSettingsIndex() == -1)
		{
			LOG_DAEMON_WARNING(eWateringMode, "return " + String(i));
			return i;
		}
	}

	LOG_DAEMON_WARNING(eWateringMode, "return " + String(NumberOfWateringSettings));
	return NumberOfWateringSettings;
}

bool WateringMode::potAlreadyExists(PotModel* potToCheck) {
	LOG_DAEMON_WARNING(eWateringMode, "potAlreadyExists(PotModel* potToCheck)");

	for(int i = 0 ; i < NumberOfPots ; i++)
	{
		if( (*potArray[i]) == (*potToCheck) )
		{
			LOG_DAEMON_WARNING(eWateringMode, "return true");
			return true;
		}
	}

	LOG_DAEMON_WARNING(eWateringMode, "return false");
	return false;
}

bool WateringMode::wateringSettingsAlreadyExists(
		WateringSettings* wateringSettingsToCheck) {
	LOG_DAEMON_WARNING(eWateringMode, "wateringSettingsAlreadyExists(WateringSettings* wateringSettingsToCheck)");

	for(int i = 0 ; i < NumberOfWateringSettings ; i++)
	{
		if( (*wateringSettingsArray[i]) == (*wateringSettingsToCheck) )
		{
			LOG_DAEMON_WARNING(eWateringMode, "return true");
			return true;
		}
	}

	LOG_DAEMON_WARNING(eWateringMode, "return false");
	return false;
}
