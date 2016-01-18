/*
 * HardwareControl.cpp
 *
 *  Created on: 03.11.2015
 *      Author: Administrator
 */

#include "HardwareControl.h"

HardwareControl* HardwareControl::hardwareControl = 0;

HardwareControl* HardwareControl::Instance()
{
	if(hardwareControl == 0)
	{
		hardwareControl = new HardwareControl();
	}
	return hardwareControl;
}

HardwareControl::HardwareControl() {
	this->realTimeClock = new DS1302(DS1302_RST, DS1302_IO, DS1302_SCK);
	//this->setupRealTimeClock();

	this->dht22 = new DHT(DHT22_DATA, DHT22);
	this->dht22->begin();

	this->setupRelayModule();
}

HardwareControl::~HardwareControl() {
	delete this->realTimeClock;
	delete this->dht22;
}

void HardwareControl::update() {

}

Time* HardwareControl::getTime() {
	return realTimeClock->time();
}

Date* HardwareControl::getDate() {
	return realTimeClock->date();
}

float HardwareControl::getHumidity() {
	return dht22->readHumidity();
}

float HardwareControl::getTemperature() {
	return dht22->readTemperature();
}

void HardwareControl::setDigitalOutput(
		DigitalOutputType_t digitalOutputType,
		DigitalOutputState_t digitalOutputState) {
	switch(digitalOutputType)
	{
	case eDigitalOutputTypeValve_1:
		digitalWrite(RELAY1, digitalOutputState);
		break;
	case eDigitalOutputTypeValve_2:
		digitalWrite(RELAY2, digitalOutputState);
		break;
	case eDigitalOutputTypeValve_3:
		digitalWrite(RELAY3, digitalOutputState);
		break;
	case eDigitalOutputTypeValve_4:
		digitalWrite(RELAY4, digitalOutputState);
		break;
	case eDigitalOutputTypePump:
		digitalWrite(RELAY5, digitalOutputState);
		break;
	case eDigitalOutputTypeReserve_1:
	case eDigitalOutputTypeReserve_2:
	case eDigitalOutputTypeReserve_3:
	case eDigitalOutputTypeUndefined:
	default:
		break;
	}
}

void HardwareControl::setupRealTimeClock() {
	/* Initialize a new chip by turning off write protection and clearing the
	     clock halt flag. These methods needn't always be called. See the DS1302
	     datasheet for details. */
	realTimeClock->write_protect(false);
	realTimeClock->halt(false);

	/* Make a new time object to set the date and time */
	Time* t = new Time(0, 8, 0);
	Date* d = new Date(2015, 11, 27);

	/* Set the time and date on the chip */
	realTimeClock->time(t);
	realTimeClock->date(d);
}

void HardwareControl::setupRelayModule() {
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	pinMode(RELAY5, OUTPUT);
	pinMode(RELAY6, OUTPUT);
	pinMode(RELAY7, OUTPUT);
	pinMode(RELAY8, OUTPUT);
}
