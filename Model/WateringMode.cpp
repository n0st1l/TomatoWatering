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

	for(int i = 0 ; i < NUMBEROFPOTS ; i++)
	{
		potArray[i] = new PotModel();
	}
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		wateringSettingsArray[i] = new WateringSettings();
	}
	wateringModeState = WateringModeState::Instance();
}

WateringMode::~WateringMode() {

	for(int i = 0 ; i < NUMBEROFPOTS ; i++)
	{
		delete potArray[i];
	}
	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		delete wateringSettingsArray[i];
	}
	delete wateringModeState;

	if(wateringMode != 0)
	{
		delete wateringMode;
	}
}

PotModel* WateringMode::getPot(int index) {

	if(HelperClass::Instance()->isIntInRange(index, 0, ARRAY_END(NUMBEROFPOTS) ) == true)
	{
		return potArray[index];
	}
	else
	{
		return new PotModel();
	}
}

WateringSettings* WateringMode::getWateringSettings(int index) {

	if(HelperClass::Instance()->isIntInRange(index, 0, ARRAY_END(NUMBEROFWATERINGSETTINGS) ) == true)
	{
		return wateringSettingsArray[index];
	}
	else
	{
		return new WateringSettings();
	}
}

bool WateringMode::addPot(PotModel* newPot) {

	if( potAlreadyExists(newPot) == false )
	{
		potArray[newPot->getPotIndex()] = newPot;
		return true;
	}

	return false;
}

bool WateringMode::removePot(int potIndexToRemove) {

	if(HelperClass::Instance()->isIntInRange(potIndexToRemove, 0, ARRAY_END(NUMBEROFPOTS) ) == true)
	{
		delete potArray[potIndexToRemove];
		potArray[potIndexToRemove] = new PotModel();

		for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
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

	if( wateringSettingsAlreadyExists(newWateringSettings) == false )
	{
		wateringSettingsArray[newWateringSettings->getWateringSettingsIndex()] = newWateringSettings;
		return true;
	}

	return false;
}

bool WateringMode::removeWateringSettings(int wateringSettingsIndexToRemove) {

	if(HelperClass::Instance()->isIntInRange(wateringSettingsIndexToRemove, 0, ARRAY_END(NUMBEROFWATERINGSETTINGS) ) == true)
	{
		delete wateringSettingsArray[wateringSettingsIndexToRemove];
		wateringSettingsArray[wateringSettingsIndexToRemove] = new WateringSettings();

		return true;
	}

	return false;
}

int WateringMode::getFreeWateringSettingsIndex() {

	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		if(wateringSettingsArray[i]->getWateringSettingsIndex() == -1)
		{
			return i;
		}
	}

	return NUMBEROFWATERINGSETTINGS;
}

bool WateringMode::potAlreadyExists(PotModel* potToCheck) {

	for(int i = 0 ; i < NUMBEROFPOTS ; i++)
	{
		if( (*potArray[i]) == (*potToCheck) )
		{
			return true;
		}
	}

	return false;
}

bool WateringMode::wateringSettingsAlreadyExists(
		WateringSettings* wateringSettingsToCheck) {

	for(int i = 0 ; i < NUMBEROFWATERINGSETTINGS ; i++)
	{
		if( (*wateringSettingsArray[i]) == (*wateringSettingsToCheck) )
		{
			return true;
		}
	}

	return false;
}
