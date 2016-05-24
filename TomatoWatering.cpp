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
	autoModeControl = AutoModeControl::Instance();
	manualModeControl = ManualModeControl::Instance();

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
	autoModeControl->cycleTask();
	manualModeControl->cycleTask();
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

	/* Create wateringSettings for manual mode */

	/* Create wateringSettings for first pot */
	tempTime.setTime(6, 30, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setPotIndex(0);
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMinWaterQuantity(200);
	tempSettings.setMaxWaterQuantity(500); // TODO Change this in summer
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(19, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(13, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMaxWaterQuantity(1000);
	wateringMode->addWateringSettings(&tempSettings);

	/* Create wateringSettings for second pot */
	tempTime.setTime(7, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setPotIndex(1);
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMinWaterQuantity(100);
	tempSettings.setMaxWaterQuantity(500);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(9, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(11, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(13, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMaxWaterQuantity(500); // TODO Change this in summer
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(15, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(17, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(19, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(21, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	/* Create wateringSettings for third pot */
	tempTime.setTime(7, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setPotIndex(2);
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMinWaterQuantity(100);
	tempSettings.setMaxWaterQuantity(500);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(9, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(11, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(13, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	tempSettings.setMaxWaterQuantity(500); // TODO Change this in summer
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(15, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(17, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(19, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

	tempTime.setTime(21, 0, 0);
	tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
	tempSettings.setWateringTime(&tempTime);
	wateringMode->addWateringSettings(&tempSettings);

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
