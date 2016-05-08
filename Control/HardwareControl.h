/*
 * HardwareControl.h
 *
 *  Created on: 03.11.2015
 *      Author: Administrator
 */

#ifndef CONTROL_HARDWARECONTROL_H_
#define CONTROL_HARDWARECONTROL_H_

#include "../Help/HelperClass.h"
#include <DHT.h>
#include <DS1302.h>
#include <LiquidCrystal.h>
#include <AButton.h>
#include <ALowPassFilter.h>
#include <ATimer.h>


class HardwareControl {
public:
	static HardwareControl *Instance();
	virtual ~HardwareControl();

	void update();

	Time* getTime();
	Date* getDate();
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
