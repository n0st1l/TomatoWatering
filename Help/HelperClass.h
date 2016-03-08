/*
 * HelperClass.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef HELP_HELPERCLASS_H_
#define HELP_HELPERCLASS_H_

#include "Log.h"
#include "hwPins.h"
#include "types.h"

#define ARRAY_END(x)	(x) - 1

#define HOURS_TO_MINUTES(x)			((x) * 60)
#define HOURS_TO_SECONDS(x)			((x) * 60 * 60)
#define MINUTES_TO_SECONDS(x)		((x) * 60)
#define MINUTES_TO_MILLISECONDS(x)	((x) * 60 * 1000)
#define SECONDS_TO_MILLISECONDS(x)	((x) * 1000)
#define SECONDS_TO_MICROSECONDS(x)	((x) * 1000 * 1000)

class HelperClass {
public:
	static HelperClass *Instance();
	virtual ~HelperClass();

	bool isIntInRange(int value, int min, int max);
	bool isFloatInRange(float value, float min, float max);

	bool getGainAndOffset(float x1, float x2, float y1, float y2, float* gain, float* offset);


private:
	HelperClass();
	static HelperClass* helperClass;


};

#endif /* HELP_HELPERCLASS_H_ */
