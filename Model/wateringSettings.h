/*
 * WateringSettings.h
 *
 *  Created on: 20.04.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGSETTINGS_H_
#define MODEL_WATERINGSETTINGS_H_

#include "../libraries/ATime/ATime.h"


const int Min_Temp			=	15;	//°C
const int Max_Temp			=	30;	//°C
const int Rain_Threshold	=	80;	//%


class WateringSettings {
public:
	WateringSettings();
	WateringSettings(int wateringSettingsIndex, int potIndex);
	WateringSettings(int wateringSettingsIndex, int potIndex, int minWaterQuantity, int maxWaterQuantity, ATime* wateringTime);
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

	inline ATime* getWateringTime() { return wateringTime; }
	void setWateringTime(ATime* wateringTime);

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
	ATime* wateringTime;


};

#endif /* MODEL_WATERINGSETTINGS_H_ */
