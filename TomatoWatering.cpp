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
	tempPot.setPotName("TOMATOES");
	tempPot.setCorrectionFactor(51.282 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);

	/* Create third pot
	 * 55.556 [ml/s] */
	tempPot.setPotIndex(2);
	tempPot.setPotName("CHERRY");
	tempPot.setCorrectionFactor(55.556 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);

	/* Create fourth pot
	 * 45.977 [ml/s] */
	tempPot.setPotIndex(3);
	tempPot.setPotName("STRAWBERRY");
	tempPot.setCorrectionFactor(45.977 / PUMP_OUTPUT);

	wateringMode->addPot(&tempPot);
}

void createWateringSettings()
{
	Time tempTime;
	WateringSettings tempSettings;

	/* Create wateringSettings for manual mode */

	/* Create wateringSettings for first pot */
	tempSettings.setPotIndex(0);
	tempSettings.setMinWaterQuantity(200);
	tempSettings.setMaxWaterQuantity(1500); // TODO Change this in summer

	//Watering forth pot every five hour from 5:15 to 20:15
	for(int i = 5 ; i <= 20 ; i += 5)
	{
		tempTime.setTime(i, 15, 0);
		tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
		tempSettings.setWateringTime(&tempTime);
		wateringMode->addWateringSettings(&tempSettings);
	}

	/* Create wateringSettings for second pot */
	tempSettings.setPotIndex(1);
	tempSettings.setMinWaterQuantity(200);
	tempSettings.setMaxWaterQuantity(1000); // TODO Change this in summer

	//Watering second pot every hour from 7 to 20
	for(int i = 7 ; i <= 20 ; i++)
	{
		tempTime.setTime(i, 0, 0);
		tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
		tempSettings.setWateringTime(&tempTime);
		wateringMode->addWateringSettings(&tempSettings);
	}

	/* Create wateringSettings for third pot */
	tempSettings.setPotIndex(2);
	tempSettings.setMinWaterQuantity(200);
	tempSettings.setMaxWaterQuantity(1000); // TODO Change this in summer

	//Watering third pot every hour from 7:30 to 20:30
	for(int i = 7 ; i <= 20 ; i++)
	{
		tempTime.setTime(i, 30, 0);
		tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
		tempSettings.setWateringTime(&tempTime);
		wateringMode->addWateringSettings(&tempSettings);
	}

	/* Create wateringSettings for fourth pot */
	tempSettings.setPotIndex(3);
	tempSettings.setMinWaterQuantity(200);
	tempSettings.setMaxWaterQuantity(800); // TODO Change this in summer

	//Watering fourth pot every five hour from 5:45 to 20:45
	for(int i = 5 ; i <= 20 ; i += 5)
	{
		tempTime.setTime(i, 45, 0);
		tempSettings.setWateringSettingsIndex(wateringMode->getFreeWateringSettingsIndex());
		tempSettings.setWateringTime(&tempTime);
		wateringMode->addWateringSettings(&tempSettings);
	}
}
