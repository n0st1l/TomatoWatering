/*
 * wateringSettings.cpp
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#include "wateringsettings.h"

WateringSettings::WateringSettings() {
	this->potIndex = 0;
	this->minWaterQuantity = 0;
	this->maxWaterQuantity = 0;
	this->shouldWatering = false;
	this->watered = false;
	this->wateringTime = new Time();
}

WateringSettings::WateringSettings(int potIndex) {
	this->potIndex = potIndex;
	this->minWaterQuantity = 0;
	this->maxWaterQuantity = 0;
	this->shouldWatering = false;
	this->watered = false;
	this->wateringTime = new Time();
}

WateringSettings::WateringSettings(int potIndex, int minWaterQuantity,
		int maxWaterQuantity, Time* wateringTime) {
	this->potIndex = potIndex;
	this->minWaterQuantity = minWaterQuantity;
	this->maxWaterQuantity = maxWaterQuantity;
	this->shouldWatering = false;
	this->watered = false;
	this->wateringTime = new Time();
	this->wateringTime->setValuesFrom(wateringTime);
}

WateringSettings::~WateringSettings() {
	// TODO Auto-generated destructor stub
}

void WateringSettings::setValuesFrom(WateringSettings* wateringSettings) {
	this->minWaterQuantity = wateringSettings->getMinWaterQuantity();
	this->maxWaterQuantity = wateringSettings->getMaxWaterQuantity();
	this->wateringTime->setValuesFrom(wateringSettings->getWateringTime());
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

void WateringSettings::setWatered(bool watered) {
	this->watered = watered;
}

void WateringSettings::setWateringTime(Time* wateringTime) {
	this->wateringTime->setValuesFrom(wateringTime);
}
