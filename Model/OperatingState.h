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
	OperatingState();
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
	Time* actualTime;
	Date* actualDate;
	float actualHumidity;
	float actualTemperature;


};

#endif /* MODEL_OPERATINGSTATE_H_ */
