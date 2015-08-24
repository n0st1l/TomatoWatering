/*
 * PotModel.h
 *
 *  Created on: 13.08.2015
 *      Author: Administrator
 */

#ifndef MODEL_POTMODEL_H_
#define MODEL_POTMODEL_H_

#include "WString.h"
#include "wateringsettings.h"

#define SIZE_WATERINGSETTINGSARRAY	5

class PotModel {
public:
	PotModel();
	virtual ~PotModel();

	inline int getPotNumber() { return potNumber; }
	void setPotNumber(int potNumber);

	inline String getPotName() { return potName; }
	void setPotName(String potName);

	WateringSettings* getWateringSettings(int index);


private:
	int potNumber;
	String potName;
	WateringSettings* wateringSettingsArray[SIZE_WATERINGSETTINGSARRAY];
};

#endif /* MODEL_POTMODEL_H_ */
