/*
 * WateringMode.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGMODE_H_
#define MODEL_WATERINGMODE_H_

#include "../Help/HelperClass.h"
#include "PotModel.h"
#include "WateringSettings.h"
#include "WateringModeState.h"

const int NumberOfPots = 4;
const int NumberOfWateringSettings = 32;

class WateringMode {
public:
	static WateringMode *Instance();
	virtual ~WateringMode();

	PotModel* getPot(int index);

	WateringSettings* getWateringSettings(int index);

	bool addPot(PotModel* newPot);
	bool removePot(int potIndexToRemove);

	bool addWateringSettings(WateringSettings* newWateringSettings);
	bool removeWateringSettings(int wateringSettingsIndexToRemove);

	int getFreeWateringSettingsIndex();

	inline WateringModeState* getWateringModeState() { return wateringModeState; }


private:
	WateringMode();
	static WateringMode* wateringMode;

	PotModel* potArray[NumberOfPots];
	WateringSettings* wateringSettingsArray[NumberOfWateringSettings];
	WateringModeState* wateringModeState;

	bool potAlreadyExists(PotModel* potToCheck);
	bool wateringSettingsAlreadyExists(WateringSettings* wateringSettingsToCheck);


};

#endif /* MODEL_WATERINGMODE_H_ */
