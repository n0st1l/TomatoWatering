/*
 * HardwareControl.h
 *
 *  Created on: 03.11.2015
 *      Author: Administrator
 */

#ifndef CONTROL_HARDWARECONTROL_H_
#define CONTROL_HARDWARECONTROL_H_

#include "../Help/HelperClass.h"
#include <DS1302.h>
#include <DHT.h>


class HardwareControl {
public:
	static HardwareControl *Instance();
	virtual ~HardwareControl();

	void update();

	Time* getTime();
	Date* getDate();
	float getHumidity();
	float getTemperature();

	void setDigitalOutput(DigitalOutputType_t digitalOutputType, DigitalOutputState_t digitalOutputState);


private:
	HardwareControl();
	static HardwareControl* hardwareControl;

	DS1302* realTimeClock;
	DHT* dht22;

	void setupRealTimeClock();
	void setupRelayModule();


};

#endif /* CONTROL_HARDWARECONTROL_H_ */
