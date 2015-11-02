/*
 * WateringMode.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGMODE_H_
#define MODEL_WATERINGMODE_H_

#include "..\Help\HelperClass.h"
#include "PotModel.h"
#include "WateringSettings.h"
#include "WateringModeState.h"

#define NUMBEROFPOTS				4
#define NUMBEROFWATERINGSETTINGS	32

class WateringMode {
public:
	WateringMode();
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
	PotModel* potArray[NUMBEROFPOTS];
	WateringSettings* wateringSettingsArray[NUMBEROFWATERINGSETTINGS];
	WateringModeState* wateringModeState;

	bool potAlreadyExists(PotModel* potToCheck);
	bool wateringSettingsAlreadyExists(WateringSettings* wateringSettingsToCheck);


};

#endif /* MODEL_WATERINGMODE_H_ */
