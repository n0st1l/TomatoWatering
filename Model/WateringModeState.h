/*
 * WateringModeState.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGMODESTATE_H_
#define MODEL_WATERINGMODESTATE_H_

#include "WateringSettings.h"

typedef enum e_WateringControlState
{
    eWateringControlStateIdle								= 0,
	eWateringControlStateCheckIfShouldStartWatering,
	eWateringControlStateStartWatering,
	eWateringControlStateStartTimer,
	eWateringControlStateEnableValve,
	eWateringControlStateWaitAfterEnableValve,
	eWateringControlStateEnablePump,
	eWateringControlStateCheckIfShouldStopWatering,
	eWateringControlStateStopWatering,
	eWateringControlStateDisablePump,
	eWateringControlStateWaitAfterDisablePump,
	eWateringControlStateDisableValves,
	eWateringControlStatePostProcessing,
	eWateringControlStateResetModel
} WateringControlState_t;


class WateringModeState {
public:
	static WateringModeState *Instance();
	virtual ~WateringModeState();

	inline bool getIsWatering() { return isWatering; }
	void setIsWatering(bool isWatering);

	inline bool getIsAutomaticMode() { return isAutomaticMode; }
	void setIsAutomaticMode(bool isAutomaticMode);

	inline WateringSettings* getActualWateringSettings() { return actualWateringSettings; }
	void setActualWateringSettings(WateringSettings* actualWateringSettings);

	inline WateringControlState_t getActualWateringControlState() { return actualWateringControlState; }
	void setActualWateringControlState(WateringControlState_t actualWateringControlState);


private:
	WateringModeState();
	static WateringModeState* wateringModeState;

	bool isWatering;
	bool isAutomaticMode;
	WateringSettings* actualWateringSettings;
	WateringControlState_t actualWateringControlState;


};

#endif /* MODEL_WATERINGMODESTATE_H_ */
