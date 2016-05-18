/*
 * ManualModeControl.cpp
 *
 *  Created on: 17.05.2016
 *      Author: Administrator
 */

#include "ManualModeControl.h"


ManualModeControl* ManualModeControl::manualModeControl = 0;

ManualModeControl* ManualModeControl::Instance() {
	if(manualModeControl == 0)
	{
		manualModeControl = new ManualModeControl();
	}
	return manualModeControl;
}

ManualModeControl::ManualModeControl() {

}

ManualModeControl::~ManualModeControl() {
	if(manualModeControl != 0)
	{
		delete this->manualModeControl;
		this->manualModeControl = NULL;
	}
}

void ManualModeControl::cycleTask() {
}



