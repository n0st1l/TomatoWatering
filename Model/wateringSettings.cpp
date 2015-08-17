/*
 * wateringSettings.cpp
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#include "wateringsettings.h"

WateringSettings::WateringSettings() {
	this->waterQuantity = 0;
	this->wateringTime = new Time();
}

WateringSettings::WateringSettings(int waterQuantity, Time wateringTime) {
	this->waterQuantity = waterQuantity;
	this->wateringTime = new Time();
	this->wateringTime->setTime(wateringTime);
}

WateringSettings::~WateringSettings() {
	// TODO Auto-generated destructor stub
}

void WateringSettings::setWateringSettings(WateringSettings wateringSettings) {
	this->waterQuantity = wateringSettings.getWaterQuantity();
	this->wateringTime->setTime(*wateringSettings.getWateringTime());
}

void WateringSettings::setWaterQuantity(int waterQuantity) {
	this->waterQuantity = waterQuantity;
}

void WateringSettings::setWateringTime(Time wateringTime) {
	this->wateringTime->setTime(wateringTime);
}
