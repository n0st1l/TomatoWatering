/*
 * MainScreen.cpp
 *
 *  Created on: 28.03.2016
 *      Author: Administrator
 */

#include "MainScreen.h"

MainScreen::MainScreen(LiquidCrystal* lcd) {
	// TODO Auto-generated constructor stub
	this->lcd = lcd;
}

MainScreen::~MainScreen() {
	// TODO Auto-generated destructor stub
}

void MainScreen::updateTime(String time) {
	lcd->setCursor(0,0);
	lcd->print(time);
}

void MainScreen::updateTemperature(String temperature) {
	lcd->setCursor(15,0);
	lcd->print(temperature);
}
