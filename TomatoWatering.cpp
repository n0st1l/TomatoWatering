// Do not remove the include below
#include "TomatoWatering.h"


//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	Serial.begin(9600);
	waterSettings1 = new WateringSettings();
	waterSettings2 = new WateringSettings();
	waterSettings2->setWaterQuantity(1000);
	waterSettings2->setWateringTime(Time(20,10));
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	Timer1.initialize();
	Timer1.attachInterrupt(printHelloWorld);
}

void printHelloWorld(){
	//Serial.print(("HelloWorld\n"));
	Time* time1 = waterSettings1->getWateringTime();
	Serial.print(time1->getHour());
	Serial.print(":");
	Serial.print(time1->getMinutes());
	Serial.print("\n");
	Serial.print("Water Quantity: ");
	Serial.print(waterSettings1->getWaterQuantity());
	Serial.print("\n");
	Time* time2 = waterSettings2->getWateringTime();
	Serial.print(time2->getHour());
	Serial.print(":");
	Serial.print(time2->getMinutes());
	Serial.print("\n");
	Serial.print("Water Quantity: ");
	Serial.print(waterSettings2->getWaterQuantity());
	Serial.print("\n");
	waterSettings2->setWaterQuantity(waterSettings2->getWaterQuantity() + 10);
}
