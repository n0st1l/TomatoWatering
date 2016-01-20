/*
 * WateringSettings.cpp
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#include "Wateringsettings.h"

WateringSettings::WateringSettings() {
	this->wateringSettingsIndex = -1;
	this->potIndex = -1;
	this->minWaterQuantity = 0;
	this->maxWaterQuantity = 0;
	this->shouldWatering = false;
	this->wateringTime = new Time();
}

WateringSettings::WateringSettings(int wateringSettingsIndex, int potIndex) {
	this->wateringSettingsIndex = wateringSettingsIndex;
	this->potIndex = potIndex;
	this->minWaterQuantity = 0;
	this->maxWaterQuantity = 0;
	this->shouldWatering = false;
	this->wateringTime = new Time();
}

WateringSettings::WateringSettings(int wateringSettingsIndex, int potIndex, int minWaterQuantity,
		int maxWaterQuantity, Time* wateringTime) {
	this->wateringSettingsIndex = wateringSettingsIndex;
	this->potIndex = potIndex;
	this->minWaterQuantity = minWaterQuantity;
	this->maxWaterQuantity = maxWaterQuantity;
	this->shouldWatering = false;
	this->wateringTime = new Time();
	this->wateringTime->setValuesFrom(wateringTime);
}

WateringSettings::~WateringSettings() {
	// TODO Auto-generated destructor stub
}

void WateringSettings::setValuesFrom(WateringSettings* wateringSettings) {
	this->wateringSettingsIndex = wateringSettings->getWateringSettingsIndex();
	this->potIndex = wateringSettings->getPotIndex();
	this->minWaterQuantity = wateringSettings->getMinWaterQuantity();
	this->maxWaterQuantity = wateringSettings->getMaxWaterQuantity();
	this->shouldWatering = wateringSettings->getShouldWatering();
	this->wateringTime->setValuesFrom(wateringSettings->getWateringTime());
}

void WateringSettings::setPotIndex(int potIndex) {
	this->potIndex = potIndex;
}

void WateringSettings::setMinWaterQuantity(int waterQuantity) {
	this->minWaterQuantity = waterQuantity;
}

void WateringSettings::setMaxWaterQuantity(int waterQuantity) {
	this->maxWaterQuantity = waterQuantity;
}

void WateringSettings::setShouldWatering(bool shouldWatering) {
	this->shouldWatering = shouldWatering;
}

void WateringSettings::setWateringTime(Time* wateringTime) {
	this->wateringTime->setValuesFrom(wateringTime);
}

bool WateringSettings::isValid() {
	if((this->potIndex < 0) ||
			(this->wateringSettingsIndex < 0) ||
			(this->wateringTime->isValid() == false)) {
		return false;
	}
	else {
		return true;
	}
}
