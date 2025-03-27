/*
 * OperatingState.h
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#ifndef MODEL_OPERATINGSTATE_H_
#define MODEL_OPERATINGSTATE_H_

#include "../Help/HelperClass.h"
#include <../libraries/ATime/ATime.h>
#include <../libraries/ADate/ADate.h>


class OperatingState {
public:
	static OperatingState *Instance();
	virtual ~OperatingState();

	inline ATime* getActualTime() { return actualTime; }
	void setActualTime(ATime* p_actualTime);

	inline ADate* getActualDate() { return actualDate; }
	void setActualDate(ADate* p_actualDate);

	inline float getActualHumidity() { return actualHumidity; }
	void setActualHumidty(float p_actualHumidity);

	inline float getActualTemperature() { return actualTemperature; }
	void setActualTemperature(float p_actualTemperature);

	inline float getTotalWaterQuantity() { return totalWaterQuantity; }
	void setTotalWaterQuantity(float p_totalWaterQuantity);
	void addToTotalWaterQuantity(float p_waterQuantity);

	inline float getDailyWaterQuantity() { return dailyWaterQuantity; }
	void setDailyWaterQuantity(float p_dailyWaterQuantity);
	void addToDailyWaterQuantity(float p_waterQuantity);

	inline DigitalOutputState_t getLedBoardState() { return ledBoardState; }
	void setLedBoardState(DigitalOutputState_t p_ledBoardState);


private:
	OperatingState();
	static OperatingState* operatingState;

	ATime* actualTime;
	ADate* actualDate;
	float actualHumidity;		// [%]
	float actualTemperature;	// [°C]
	float totalWaterQuantity;	// [l]
	float dailyWaterQuantity;	// [l]
	DigitalOutputState_t ledBoardState;


};

#endif /* MODEL_OPERATINGSTATE_H_ */
