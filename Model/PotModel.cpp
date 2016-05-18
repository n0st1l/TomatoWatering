/*
 * PotModel.cpp
 *
 *  Created on: 13.08.2015
 *      Author: Administrator
 */

#include "PotModel.h"

PotModel::PotModel() {
	this->potIndex = -1;
	this->potName = "undefined";
	this->totalWaterQuantity = 0;
	this->correctionFactor = 1;
}

PotModel::PotModel(int potIndex, String potName, float correctionFactor) {
	this->potIndex = potIndex;
	this->potName = potName;
	this->totalWaterQuantity = 0;
	this->correctionFactor = correctionFactor;
}

PotModel::~PotModel() {
	// TODO Auto-generated destructor stub
}

void PotModel::setValuesFrom(PotModel* potModel) {
	this->potIndex = potModel->getPotIndex();
	this->potName = potModel->getPotName();
	this->totalWaterQuantity = potModel->getTotalWaterQuantity();
	this->correctionFactor = potModel->getCorrectionFactor();
}

void PotModel::setPotIndex(int potIndex) {
	this->potIndex = potIndex;
}

void PotModel::setPotName(String potName) {
	this->potName = potName;
}

void PotModel::setTotalWaterQuantity(float totalWaterQuantity) {
	this->totalWaterQuantity = totalWaterQuantity;
}

void PotModel::setCorrectionFactor(float correctionFactor) {
	this->correctionFactor = correctionFactor;
}
