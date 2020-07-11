/*
 * HardwareControl.h
 *
 *  Created on: 03.11.2015
 *      Author: Administrator
 */

#ifndef CONTROL_HARDWARECONTROL_H_
#define CONTROL_HARDWARECONTROL_H_

#include "../Help/HelperClass.h"
#include <../libraries/DHT22/DHT.h>
#include <../libraries/DS1302/DS1302.h>
#include <LiquidCrystal.h>
#include <../libraries/AButton/AButton.h>
#include <../libraries/ALowPassFilter/ALowPassFilter.h>
#include <../libraries/ATimer/ATimer.h>


class HardwareControl {
public:
	static HardwareControl *Instance();
	virtual ~HardwareControl();

	void cycleTask();

	ATime* getTime();
	ADate* getDate();
	float getHumidity();
	float getTemperature();
	inline LiquidCrystal* getLiquidCrystal() { return liquidCrystal; }

	void setDigitalOutput(DigitalOutputType_t digitalOutputType, DigitalOutputState_t digitalOutputState);


private:
	HardwareControl();
	static HardwareControl* hardwareControl;

	/*Real time clock*/
	DS1302* realTimeClock;

	/*Temperature & humidity sensor*/
	DHT* dht22;

	/*LCD display*/
	LiquidCrystal* liquidCrystal;

	/*Buttons*/
	AButton* buttonTop;
	AButton* buttonBottom;
	AButton* buttonLeft;
	AButton* buttonRight;

	/*Filter*/
	ALowPassFilter* humidityLowPass;
	ALowPassFilter* temperatureLowPass;

	/*Timer*/
	ATimer* lcdTimer;

	/*Functions*/
	void setupRealTimeClock();
	void setupLiquidCrystal();
	void setupRelayModule();


};

#endif /* CONTROL_HARDWARECONTROL_H_ */
