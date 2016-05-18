/*
 * ManualModeControl.h
 *
 *  Created on: 17.05.2016
 *      Author: Administrator
 */

#ifndef MANUALMODECONTROL_H_
#define MANUALMODECONTROL_H_


#include "../Help/HelperClass.h"


class ManualModeControl {
public:
	static ManualModeControl *Instance();
	virtual ~ManualModeControl();

	void cycleTask();


private:
	ManualModeControl();
	static ManualModeControl* manualModeControl;


};

#endif /* MANUALMODECONTROL_H_ */
