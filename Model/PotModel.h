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
	PotModel(int potIndex, String potName, float correctionFactor);
	virtual ~PotModel();

	void setValuesFrom(PotModel* potModel);

	inline int getPotIndex() { return potIndex; }
	void setPotIndex(int potIndex);

	inline String getPotName() { return potName; }
	void setPotName(String potName);

	inline float getTotalWaterQuantity() { return totalWaterQuantity; }
	void setTotalWaterQuantity(float totalWaterQuantity);
	void addToTotalWaterQuantity(float waterQuantity);

	inline float getCorrectionFactor() { return correctionFactor; }
	void setCorrectionFactor(float correctionFactor);

	/*Operators*/
	inline bool operator == (const PotModel &otherPotModel) const
	{
		return this->potIndex == otherPotModel.potIndex;
	}


private:
	int potIndex;
	String potName;
	float totalWaterQuantity;	// [l]
	float correctionFactor;
};

#endif /* MODEL_POTMODEL_H_ */
