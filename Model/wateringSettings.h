/*
 * WateringSettings.h
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGSETTINGS_H_
#define MODEL_WATERINGSETTINGS_H_

#include <Time.h>


#define MIN_TEMP	15 //�C
#define MAX_TEMP	25 //�C


class WateringSettings {
public:
	WateringSettings();
	WateringSettings(int wateringSettingsIndex, int potIndex);
	WateringSettings(int wateringSettingsIndex, int potIndex, int minWaterQuantity, int maxWaterQuantity, Time* wateringTime);
	virtual ~WateringSettings();

	void setValuesFrom(WateringSettings* wateringSettings);

	inline int getWateringSettingsIndex() { return wateringSettingsIndex; }
	void setWateringSettingsIndex(int wateringSettingsIndex);

	inline int getPotIndex() { return potIndex; }
	void setPotIndex(int potIndex);

	inline int getMinWaterQuantity() { return minWaterQuantity; }
	void setMinWaterQuantity(int waterQuantity);

	inline int getMaxWaterQuantity() { return maxWaterQuantity; }
	void setMaxWaterQuantity(int waterQuantity);

	inline bool getShouldWatering() { return shouldWatering; }
	void setShouldWatering(bool shouldWatering);

	inline Time* getWateringTime() { return wateringTime; }
	void setWateringTime(Time* wateringTime);

	bool isValid();

	/*Operators*/
	inline bool operator == (const WateringSettings &otherWateringSettings) const
	{
		return this->wateringSettingsIndex == otherWateringSettings.wateringSettingsIndex;
	}


private:
	int wateringSettingsIndex; //This index is to identify the wateringSettings
	int potIndex; //This wateringSetting appertains to the potIndex
	int minWaterQuantity; //Minimum Water Quantity in [ml]
	int maxWaterQuantity; //Maximum Water Quantity in [ml]
	bool shouldWatering; //Defines if this wateringSetting should watered
	Time* wateringTime;


};

#endif /* MODEL_WATERINGSETTINGS_H_ */
