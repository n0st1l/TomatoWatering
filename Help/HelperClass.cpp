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


