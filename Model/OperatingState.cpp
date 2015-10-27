/*
 * OperatingState.cpp
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#include "OperatingState.h"


OperatingState::OperatingState() {
	this->actualTime = new Time();
	this->actualDate = new Date();
	this->actualHumidity = 0.0f;
	this->actualTemperature = 0.0f;
}

OperatingState::~OperatingState() {
	// TODO Auto-generated destructor stub
}

void OperatingState::setActualTime(Time* p_actualTime) {
	this->actualTime->setValuesFrom(p_actualTime);
}

void OperatingState::setActualDate(Date* p_actualDate) {
	this->actualDate->setValuesFrom(p_actualDate);
}

void OperatingState::setActualHumidty(float p_actualHumidity) {
	this->actualHumidity = p_actualHumidity;
}

void OperatingState::setActualTemperature(float p_actualTemperature) {
	this->actualTemperature = p_actualTemperature;
}