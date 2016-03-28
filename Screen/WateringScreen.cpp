/*
 * WateringScreen.cpp
 *
 *  Created on: 28.03.2016
 *      Author: Administrator
 */

#include "WateringScreen.h"

WateringScreen::WateringScreen(LiquidCrystal* lcd) {
	// TODO Auto-generated constructor stub
	this->lcd = lcd;
}

WateringScreen::~WateringScreen() {
	// TODO Auto-generated destructor stub
}

void WateringScreen::updateStatus(String status) {
	lcd->setCursor(0,1);
	lcd->print("                    ");
	lcd->setCursor(0,1);
	lcd->print(status);
}

void WateringScreen::updateQuantity(String quantity) {
	lcd->setCursor(0,2);
	lcd->print("                    ");
	lcd->setCursor(0,2);
	lcd->print(quantity);
}

void WateringScreen::updateProgress(String progress) {
	lcd->setCursor(0,3);
	lcd->print("                    ");
	lcd->setCursor(0,3);
	lcd->print(progress);
}
