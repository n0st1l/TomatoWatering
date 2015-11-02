/*
 * PotModel.h
 *
 *  Created on: 13.08.2015
 *      Author: Administrator
 */

#ifndef MODEL_POTMODEL_H_
#define MODEL_POTMODEL_H_

#include "WString.h"


class PotModel {
public:
	PotModel();
	virtual ~PotModel();

	inline int getPotIndex() { return potIndex; }
	void setPotIndex(int potIndex);

	inline String getPotName() { return potName; }
	void setPotName(String potName);

	/*Operators*/
	inline bool operator == (const PotModel &otherPotModel) const
	{
		return this->potIndex == otherPotModel.potIndex;
	}


private:
	int potIndex;
	String potName;
};

#endif /* MODEL_POTMODEL_H_ */
