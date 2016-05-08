/*
 * HelperClass.cpp
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#include "HelperClass.h"


HelperClass* HelperClass::helperClass = 0;

HelperClass* HelperClass::Instance()
{
	if(helperClass == 0)
	{
		helperClass = new HelperClass();
	}
	return helperClass;
}

HelperClass::HelperClass() {

}

HelperClass::~HelperClass() {

	if(helperClass != 0)
	{
		delete helperClass;
	}
}

bool HelperClass::isIntInRange(int value, int min, int max) {

	if( ((value) >= (min)) && ((value) <= (max)) )
		return true;
	else
		return false;
}

bool HelperClass::isFloatInRange(float value, float min, float max) {

	if( ((value) >= (min)) && ((value) <= (max)) )
		return true;
	else
		return false;
}

bool HelperClass::getGainAndOffset(float x1, float x2, float y1, float y2,
		float* gain, float* offset) {

	String debugMsg = "getGainAndOffset(float " + String(x1) +
			", float " + String(x2) +
			", float " + String(y1) +
			", float " + String(y2) + ")";
	LOG_DAEMON_DEBUG(eHelperClass, debugMsg);

	if( (x1 >= x2) || (y1 >= y2) ) {

		debugMsg = "min and max mismatch";
		LOG_DAEMON_DEBUG(eHelperClass, debugMsg);

		return false;
	}
	*gain = (y2 - y1) / (x2 - x1);
	*offset = y1 - (*gain * x1);

	debugMsg = "gain " + String(*gain) + ", offset " + String(*offset);
	LOG_DAEMON_DEBUG(eHelperClass, debugMsg);

	return true;
}
