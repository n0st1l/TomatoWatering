/*
 * HelperClass.h
 *
 *  Created on: 27.10.2015
 *      Author: Administrator
 */

#ifndef HELP_HELPERCLASS_H_
#define HELP_HELPERCLASS_H_

#include "hwPins.h"
#include "types.h"

#define ARRAY_END(x)	(x) - 1

class HelperClass {
public:
	static HelperClass *Instance();
	virtual ~HelperClass();

	bool isIntInRange(int value, int min, int max);
	bool isFloatInRange(float value, float min, float max);


private:
	HelperClass();
	static HelperClass* helperClass;


};

#endif /* HELP_HELPERCLASS_H_ */
