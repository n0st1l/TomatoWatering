/*
 * OperatingControl.cpp
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#include "OperatingControl.h"


OperatingControl::OperatingControl() {
	this->realTimeClock = new DS1302(DS1302_RST, DS1302_IO, DS1302_SCK);
	this->dht22 = new DHT(DHT22_DATA, DHT22);
}

OperatingControl::~OperatingControl() {
	// TODO Auto-generated destructor stub
}

void OperatingControl::onOneSecondTimerTimeout() {
}
