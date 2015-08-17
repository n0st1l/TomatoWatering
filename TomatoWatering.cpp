// Do not remove the include below
#include "TomatoWatering.h"


//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	Serial.begin(9600);
	tomatoPot = new PotModel();
	tomatoPot->setPotNumber(1);
	tomatoPot->setPotName("Tomato");
	WateringSettings* tempWateringSettings = new WateringSettings(1000, Time(23, 59));
	tomatoPot->setWateringSettings(*tempWateringSettings, 0);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	Timer1.initialize();
	Timer1.attachInterrupt(printHelloWorld);
}

void printHelloWorld(){
	String tempString;
	tempString = "TomatoPot Number: " + String(tomatoPot->getPotNumber()) + "\n";
	Serial.print(tempString);
	tempString = "TomatoPot Name: " + tomatoPot->getPotName() + "\n";
	Serial.print(tempString);
	for(int i = 0 ; i < 2 ; i++)
	{
	tempString = String(tomatoPot->getWateringSettings(i)->getWaterQuantity()) + "\n";
	Serial.print(tempString);
	tempString = String(tomatoPot->getWateringSettings(i)->getWateringTime()->getTimeString()) + "\n";
	Serial.print(tempString);
	}
}
