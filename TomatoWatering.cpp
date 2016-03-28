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
	wateringMode->addPot(new PotModel(0, "CHERRY"));
	wateringMode->addPot(new PotModel(1, "TOMATOES"));
	wateringMode->addPot(new PotModel(2, "CARROTS"));
	wateringMode->addPot(new PotModel(3, "SALAD"));
}

void createWateringSettings()
{
	wateringMode->addWateringSettings(new WateringSettings(0, 0, 100, 1000, new Time(6, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(1, 0, 200, 1100, new Time(7, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(2, 0, 300, 1200, new Time(8, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(3, 0, 400, 1300, new Time(9, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(4, 0, 500, 1400, new Time(10, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(5, 0, 600, 1500, new Time(11, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(6, 0, 700, 1600, new Time(12, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(7, 0, 800, 1700, new Time(13, 00, 0)));

	wateringMode->addWateringSettings(new WateringSettings(8, 1, 100, 1000, new Time(14, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(9, 1, 200, 1100, new Time(15, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(10, 1, 300, 1200, new Time(16, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(11, 1, 400, 1300, new Time(17, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(12, 1, 500, 1400, new Time(18, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(13, 1, 600, 1500, new Time(19, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(14, 1, 700, 1600, new Time(20, 00, 0)));
	wateringMode->addWateringSettings(new WateringSettings(15, 1, 800, 1700, new Time(21, 00, 0)));

	wateringMode->addWateringSettings(new WateringSettings(16, 2, 100, 1000, new Time(6, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(17, 2, 200, 1100, new Time(7, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(18, 2, 300, 1200, new Time(8, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(19, 2, 400, 1300, new Time(9, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(20, 2, 500, 1400, new Time(10, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(21, 2, 600, 1500, new Time(11, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(22, 2, 700, 1600, new Time(12, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(23, 2, 800, 1700, new Time(13, 30, 0)));

	wateringMode->addWateringSettings(new WateringSettings(24, 3, 100, 1000, new Time(14, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(25, 3, 200, 1100, new Time(15, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(26, 3, 300, 1200, new Time(16, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(27, 3, 400, 1300, new Time(17, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(28, 3, 500, 1400, new Time(18, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(29, 3, 600, 1500, new Time(19, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(30, 3, 700, 1600, new Time(20, 30, 0)));
	wateringMode->addWateringSettings(new WateringSettings(31, 3, 800, 1700, new Time(21, 30, 0)));
}
