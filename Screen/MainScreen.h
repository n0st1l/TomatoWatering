/*
 * MainScreen.h
 *
 *  Created on: 28.03.2016
 *      Author: Administrator
 */

#ifndef MAINSCREEN_H_
#define MAINSCREEN_H_


#include "WString.h"
#include "LiquidCrystal.h"


class MainScreen {
public:
	MainScreen(LiquidCrystal* lcd);
	virtual ~MainScreen();

	void updateTime(String time);
	void updateTemperature(String temperature);


private:
	LiquidCrystal* lcd;
};

#endif /* MAINSCREEN_H_ */
