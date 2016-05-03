// Do not remove the include below
#include "TomatoWatering.h"

#include "AButton.h"

#include <stdio.h>
#include <string.h>

/* Create buffers */
char buf[50];
char day[10];


//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here

	/*IO*/
	liquidCrystal = new LiquidCrystal(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
	liquidCrystal->begin(20, 4);
	liquidCrystal->noAutoscroll();
	liquidCrystal->noBlink();
	liquidCrystal->noCursor();
	pinMode(LCD_A, OUTPUT);
	digitalWrite(LCD_A, HIGH);

	buttonTop = new AButton(BUTTON_TOP);
	buttonBottom = new AButton(BUTTON_BOTTOM);
	buttonLeft = new AButton(BUTTON_LEFT);
	buttonRight = new AButton(BUTTON_RIGHT);

	/*Timer*/
	lcdTimer = new ATimer(SECONDS_TO_MILLISECONDS((unsigned long) 20));

	/*Models*/
	wateringMode = WateringMode::Instance();
	operatingState = OperatingState::Instance();

	/*Screens*/
	mainScreen = new MainScreen(liquidCrystal);
	wateringScreen = new WateringScreen (liquidCrystal);

	/*Controls*/
	hardwareControl = HardwareControl::Instance();
	operatingControl = OperatingControl::Instance();
	operatingControl->setMainScreen(mainScreen);
	wateringControl = WateringControl::Instance();
	wateringControl->setWateringScreen(wateringScreen);

	/*Functions*/
	createPots();
	createWateringSettings();


}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here

	operatingControl->update();
	wateringControl->update();

	if(buttonTop->onPressed() ||
			buttonBottom->onPressed() ||
			buttonLeft->onPressed() ||
			buttonRight->onPressed())
	{
		digitalWrite(LCD_A, HIGH);
		liquidCrystal->display();
		lcdTimer->restart();
	}
	if(lcdTimer->onExpired())
	{
		liquidCrystal->noDisplay();
		digitalWrite(LCD_A, LOW);
	}
}

void createPots()
{
	PotModel tempPot;

	/* Create first pot
	 * 53.333 [ml/s] */
	tempPot.setPotIndex(0);
	tempPot.setPotName("PEPPERS");
	tempPot.setCorrectionFactor(53.333 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);

	/* Create second pot
	 * 51.282 [ml/s] */
	tempPot.setPotIndex(1);
	tempPot.setPotName("CHERRY");
	tempPot.setCorrectionFactor(51.282 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);

	/* Create third pot
	 * 55.556 [ml/s] */
	tempPot.setPotIndex(2);
	tempPot.setPotName("TOMATOES");
	tempPot.setCorrectionFactor(55.556 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);

	/* Create fourth pot
	 * 45.977 [ml/s] */
	tempPot.setPotIndex(3);
	tempPot.setPotName("DIVERSE");
	tempPot.setCorrectionFactor(45.977 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);
}

void createWateringSettings()
{
	Time tempTime;
	WateringSettings tempSettings;

	//	wateringMode->addWateringSettings(new WateringSettings(0, 0, 100, 1000, new Time(21, 0, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(1, 0, 200, 1100, new Time(21, 4, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(2, 0, 300, 1200, new Time(21, 8, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(3, 0, 400, 1300, new Time(21, 12, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(4, 0, 500, 1400, new Time(21, 16, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(5, 0, 600, 1500, new Time(21, 20, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(6, 0, 700, 1600, new Time(21, 24, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(7, 0, 800, 1700, new Time(21, 28, 0)));
	//
	//	wateringMode->addWateringSettings(new WateringSettings(8, 1, 100, 1000, new Time(21, 2, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(9, 1, 200, 1100, new Time(21, 6, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(10, 1, 300, 1200, new Time(21, 10, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(11, 1, 400, 1300, new Time(21, 14, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(12, 1, 500, 1400, new Time(21, 18, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(13, 1, 600, 1500, new Time(21, 22, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(14, 1, 700, 1600, new Time(21, 26, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(15, 1, 800, 1700, new Time(21, 30, 0)));
	//
	//	wateringMode->addWateringSettings(new WateringSettings(16, 2, 100, 1000, new Time(21, 0, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(17, 2, 200, 1100, new Time(21, 4, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(18, 2, 300, 1200, new Time(21, 8, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(19, 2, 400, 1300, new Time(21, 12, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(20, 2, 500, 1400, new Time(21, 16, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(21, 2, 600, 1500, new Time(21, 20, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(22, 2, 700, 1600, new Time(21, 24, 0)));
	//	wateringMode->addWateringSettings(new WateringSettings(23, 2, 800, 1700, new Time(21, 28, 0)));

	/* Create wateringSettings for fourth pot */
	tempTime.setTime(8, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setPotIndex(3);
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMinWaterQuantity(500);
	tempSettings.setMaxWaterQuantity(1000);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(22, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);
}
