/*
 * wateringSettings.h
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGSETTINGS_H_
#define MODEL_WATERINGSETTINGS_H_

#include <DS1302.h>


class wateringSettings {
public:
	wateringSettings();
	virtual ~wateringSettings();

	inline int getWaterQuantity() { return waterQuantity; }
	void setWaterQuantity(int waterQuantity);

	inline Time getWateringTime1() { return wateringTime1; }
	void setWateringTime1(Time wateringTime1);

	inline Time getWateringTime2() { return wateringTime2; }
	void setWateringTime2(Time wateringTime2);

private:
	int waterQuantity; //Water Quantity in [ml]
	Time wateringTime1; //Stores the watering time 1
	Time wateringTime2; //Stores the watering time 2
};

#endif /* MODEL_WATERINGSETTINGS_H_ */
