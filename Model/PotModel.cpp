/*
 * PotModel.cpp
 *
 *  Created on: 13.08.2015
 *      Author: Administrator
 */

#include "PotModel.h"

PotModel::PotModel() {
	this->potIndex = 0;
	this->potName = "undefined";
}

PotModel::~PotModel() {
	// TODO Auto-generated destructor stub
}

void PotModel::setPotIndex(int potIndex) {
	this->potIndex = potIndex;
}

void PotModel::setPotName(String potName) {
	this->potName = potName;
}
