/*
 * OperatingState.h
 *
 *  Created on: 08.09.2015
 *      Author: Administrator
 */

#ifndef MODEL_OPERATINGSTATE_H_
#define MODEL_OPERATINGSTATE_H_

#include <Time.h>
#include <Date.h>


class OperatingState {
public:
	static OperatingState *Instance();
	virtual ~OperatingState();

	inline Time* getActualTime() { return actualTime; }
	void setActualTime(Time* p_actualTime);

	inline Date* getActualDate() { return actualDate; }
	void setActualDate(Date* p_actualDate);

	inline float getActualHumidity() { return actualHumidity; }
	void setActualHumidty(float p_actualHumidity);

	inline float getActualTemperature() { return actualTemperature; }
	void setActualTemperature(float p_actualTemperature);


private:
	OperatingState();
	static OperatingState* operatingState;

	Time* actualTime;
	Date* actualDate;
	float actualHumidity;
	float actualTemperature;


};

#endif /* MODEL_OPERATINGSTATE_H_ */
