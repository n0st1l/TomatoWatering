/*
 * OperatingState.cpp
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#include "OperatingState.h"


OperatingState* OperatingState::operatingState = 0;

OperatingState* OperatingState::Instance()
{
	if(operatingState == 0)
	{
		operatingState = new OperatingState();
	}
	return operatingState;
}

OperatingState::OperatingState() {
	this->actualTime = new ATime();
	this->actualDate = new ADate();
	this->actualHumidity = 40.0f;
	this->actualTemperature = 20.0f;
	this->totalWaterQuantity = 0.0f;
	this->dailyWaterQuantity = 0.0f;
}

OperatingState::~OperatingState() {
	delete this->actualTime;
	this->actualTime = NULL;

	delete this->actualDate;
	this->actualDate = NULL;

	if(operatingState != 0)
	{
		delete this->operatingState;
		this->operatingState = NULL;
	}
}

void OperatingState::setActualTime(ATime* p_actualTime) {
	this->actualTime->setValuesFrom(p_actualTime);
}

void OperatingState::setActualDate(ADate* p_actualDate) {
	this->actualDate->setValuesFrom(p_actualDate);
}

void OperatingState::setActualHumidty(float p_actualHumidity) {
	this->actualHumidity = p_actualHumidity;
}

void OperatingState::setActualTemperature(float p_actualTemperature) {
	this->actualTemperature = p_actualTemperature;
}

void OperatingState::setTotalWaterQuantity(float p_totalWaterQuantity) {
	this->totalWaterQuantity = p_totalWaterQuantity;
}

void OperatingState::addToTotalWaterQuantity(float p_waterQuantity) {
	this->totalWaterQuantity = this->totalWaterQuantity + p_waterQuantity;
}

void OperatingState::setDailyWaterQuantity(float p_dailyWaterQuantity) {
	this->dailyWaterQuantity = p_dailyWaterQuantity;
}

void OperatingState::addToDailyWaterQuantity(float p_waterQuantity) {
	this->dailyWaterQuantity = this->dailyWaterQuantity + p_waterQuantity;
}
