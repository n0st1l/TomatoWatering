/*
 * WateringScreen.h
 *
 *  Created on: 28.03.2016
 *      Author: Administrator
 */

#ifndef WATERINGSCREEN_H_
#define WATERINGSCREEN_H_


#include "WString.h"
#include "LiquidCrystal.h"


class WateringScreen {
public:
	WateringScreen(LiquidCrystal* lcd);
	virtual ~WateringScreen();

	void updateStatus(String status);
	void updateQuantity(String quantity);
	void updateProgress(String progress);


private:
	LiquidCrystal* lcd;


};

#endif /* WATERINGSCREEN_H_ */
