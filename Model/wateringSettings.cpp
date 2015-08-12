/*
 * wateringSettings.cpp
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#include "WateringSettings.h"

WateringSettings::WateringSettings() {
	waterQuantity = 0;
	wateringTime = new Time();
}

WateringSettings::~WateringSettings() {
	// TODO Auto-generated destructor stub
}

void WateringSettings::setWaterQuantity(int waterQuantity) {
	this->waterQuantity = waterQuantity;
}

void WateringSettings::setWateringTime(Time wateringTime) {
	this->wateringTime->setHour( wateringTime.getHour() );
	this->wateringTime->setMinutes( wateringTime.getMinutes() );
}
