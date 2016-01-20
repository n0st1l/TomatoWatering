/*
 * WateringModeState.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGMODESTATE_H_
#define MODEL_WATERINGMODESTATE_H_

#include "WateringSettings.h"


class WateringModeState {
public:
	static WateringModeState *Instance();
	virtual ~WateringModeState();

	inline bool getIsWatering() { return isWatering; }
	void setIsWatering(bool isWatering);

	inline bool getIsAutomaticMode() { return isAutomaticMode; }
	void setIsAutomaticMode(bool isAutomaticMode);

	inline bool getIsManualMode() { return isManualMode; }
	void setIsManualMode(bool isManualMode);

	inline WateringSettings* getActualWateringSettings() { return actualWateringSettings; }
	void setActualWateringSettings(WateringSettings* actualWateringSettings);


private:
	WateringModeState();
	static WateringModeState* wateringModeState;

	bool isWatering;
	bool isAutomaticMode;
	bool isManualMode;
	WateringSettings* actualWateringSettings;


};

#endif /* MODEL_WATERINGMODESTATE_H_ */
