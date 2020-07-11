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

	this->liquidCrystal = new LiquidCrystal(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
	this->liquidCrystal->begin(20, 4);
	this->setupLiquidCrystal();

	this->buttonTop = new AButton(BUTTON_TOP);
	this->buttonBottom = new AButton(BUTTON_BOTTOM);
	this->buttonLeft = new AButton(BUTTON_LEFT);
	this->buttonRight = new AButton(BUTTON_RIGHT);

	this->humidityLowPass = new ALowPassFilter(0.5);
	this->temperatureLowPass = new ALowPassFilter(0.5);

	this->lcdTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 20));

	this->setupRelayModule();
}

HardwareControl::~HardwareControl() {
	delete this->realTimeClock;
	delete this->dht22;

	delete this->liquidCrystal;

	delete this->buttonTop;
	delete this->buttonBottom;
	delete this->buttonLeft;
	delete this->buttonRight;

	delete this->humidityLowPass;
	delete this->temperatureLowPass;

	delete this->lcdTimer;
}

void HardwareControl::cycleTask() {
	if(buttonTop->onPressed() ||
			buttonBottom->onPressed() ||
			buttonLeft->onPressed() ||
			buttonRight->onPressed())
	{
		digitalWrite(LCD_A, HIGH);
		liquidCrystal->display();
		lcdTimer->restart();
	}
	if(lcdTimer->onExpired())
	{
		liquidCrystal->noDisplay();
		digitalWrite(LCD_A, LOW);
	}
}

ATime* HardwareControl::getTime() {
	return this->realTimeClock->time();
}

ADate* HardwareControl::getDate() {
	return this->realTimeClock->date();
}

float HardwareControl::getHumidity() {
	this->humidityLowPass->addNewData(this->dht22->readHumidity());
	return this->humidityLowPass->getProcessedData();
}

float HardwareControl::getTemperature() {
	this->temperatureLowPass->addNewData(this->dht22->readTemperature());
	return this->temperatureLowPass->getProcessedData();
}

void HardwareControl::setDigitalOutput(
		DigitalOutputType_t digitalOutputType,
		DigitalOutputState_t digitalOutputState) {

	String debugMsg = "setDigitalOutput(DigitalOutputType_t " + String(digitalOutputType) + ", DigitalOutputState_t " + String(digitalOutputState) + ")";
	LOG_DAEMON_DEBUG(eHardwareControl, debugMsg);

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
	ATime t (21, 24, 0);
	ADate d (2018, 6, 7);

	/* Set the time and date on the chip */
	realTimeClock->time(t);
	realTimeClock->date(d);
}

void HardwareControl::setupLiquidCrystal() {
	this->liquidCrystal->noAutoscroll();
	this->liquidCrystal->noBlink();
	this->liquidCrystal->noCursor();
	/*Set backlight*/
	pinMode(LCD_A, OUTPUT);
	digitalWrite(LCD_A, HIGH);
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
