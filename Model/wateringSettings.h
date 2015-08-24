/*
 * wateringSettings.h
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGSETTINGS_H_
#define MODEL_WATERINGSETTINGS_H_

#include <Time.h>

#define NUMOFWATERINGTIME 5


class WateringSettings {
public:
	WateringSettings();
	WateringSettings(int waterQuantity, Time* wateringTime);
	virtual ~WateringSettings();

	void setValuesFrom(WateringSettings* wateringSettings);

	inline int getWaterQuantity() { return waterQuantity; }
	void setWaterQuantity(int waterQuantity);

	inline Time* getWateringTime() { return wateringTime; }
	void setWateringTime(Time* wateringTime);


private:
	int waterQuantity; //Water Quantity in [ml]
	Time* wateringTime;


};

#endif /* MODEL_WATERINGSETTINGS_H_ */
