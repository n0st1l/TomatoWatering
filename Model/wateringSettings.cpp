/*
 * wateringSettings.cpp
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#include "wateringSettings.h"

wateringSettings::wateringSettings() {
	waterQuantity = 0;
	wateringTime1 = Time();
	wateringTime2 = Time();
}

wateringSettings::~wateringSettings() {
	// TODO Auto-generated destructor stub
}

void wateringSettings::setWaterQuantity(int waterQuantity) {
	this->waterQuantity = waterQuantity;
}

void wateringSettings::setWateringTime1(Time wateringTime1) {
	this->wateringTime1 = wateringTime1;
}

void wateringSettings::setWateringTime2(Time wateringTime2) {
	this->wateringTime2 = wateringTime2;
}
