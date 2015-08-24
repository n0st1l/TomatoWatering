/*
 * PotModel.cpp
 *
 *  Created on: 13.08.2015
 *      Author: Administrator
 */

#include "PotModel.h"

PotModel::PotModel() {
	this->potNumber = 0;
	this->potName = "undefined";

	for(int i = 0 ; i < SIZE_WATERINGSETTINGSARRAY ; i++)
	{
		wateringSettingsArray[i] = new WateringSettings();
	}
}

PotModel::~PotModel() {
	// TODO Auto-generated destructor stub
}

void PotModel::setPotNumber(int potNumber) {
	this->potNumber = potNumber;
}

void PotModel::setPotName(String potName) {
	this->potName = potName;
}

WateringSettings* PotModel::getWateringSettings(int index) {
	return wateringSettingsArray[index];
}
