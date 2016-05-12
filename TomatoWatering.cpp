// Do not remove the include below
#include "TomatoWatering.h"

#include <stdio.h>
#include <string.h>

/* Create buffers */
char buf[50];
char day[10];


//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here

	/*Models*/
	wateringMode = WateringMode::Instance();
	operatingState = OperatingState::Instance();

	/*Controls*/
	hardwareControl = HardwareControl::Instance();
	operatingControl = OperatingControl::Instance();
	wateringControl = WateringControl::Instance();

	/*Screens*/
	mainScreen = new MainScreen(hardwareControl->getLiquidCrystal());
	operatingControl->setMainScreen(mainScreen);
	wateringScreen = new WateringScreen (hardwareControl->getLiquidCrystal());
	wateringControl->setWateringScreen(wateringScreen);

	/*Functions*/
	createPots();
	createWateringSettings();


}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here

	operatingControl->cycleTask();
	wateringControl->cycleTask();
	hardwareControl->cycleTask();


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
	tempTime.setTime(6, 45, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setPotIndex(3);
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMinWaterQuantity(500);
	tempSettings.setMaxWaterQuantity(2000);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(13, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(21, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMaxWaterQuantity(3000);
	wateringMode->addWateringSettings(&tempSettings);
}
