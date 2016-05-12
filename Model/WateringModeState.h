/*
 * WateringModeState.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef MODEL_WATERINGMODESTATE_H_
#define MODEL_WATERINGMODESTATE_H_

typedef enum e_WateringControlState
{
    eWateringControlStateIdle								= 0,
	eWateringControlStateCheckIfShouldStartWatering			= 1,
	eWateringControlStateStartWatering						= 2,
	eWateringControlStateEnableValve						= 3,
	eWateringControlStateWaitAfterEnableValve				= 4,
	eWateringControlStateEnablePump							= 5,
	eWateringControlStateCheckIfShouldStopWatering			= 6,
	eWateringControlStateDisablePump						= 7,
	eWateringControlStateWaitAfterDisablePump				= 8,
	eWateringControlStateDisableValves						= 9
} WateringControlState_t;


class WateringModeState {
public:
	static WateringModeState *Instance();
	virtual ~WateringModeState();

	inline bool getIsWatering() { return isWatering; }
	void setIsWatering(bool isWatering);

	inline bool getIsAutomaticMode() { return isAutomaticMode; }
	void setIsAutomaticMode(bool isAutomaticMode);

	inline int getActualWateringSettingsIndex() { return actualWateringSettingsIndex; }
	void setActualWateringSettingsIndex(int actualWateringSettingsIndex);

	inline int getActualPotIndex() { return actualPotIndex; }
	void setActualPotIndex(int actualPotIndex);

	inline WateringControlState_t getActualWateringControlState() { return actualWateringControlState; }
	void setActualWateringControlState(WateringControlState_t actualWateringControlState);


private:
	WateringModeState();
	static WateringModeState* wateringModeState;

	bool isWatering;
	bool isAutomaticMode;
	int actualWateringSettingsIndex;
	int actualPotIndex;
	WateringControlState_t actualWateringControlState;


};

#endif /* MODEL_WATERINGMODESTATE_H_ */
