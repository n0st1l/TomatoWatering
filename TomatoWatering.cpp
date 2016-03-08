// Do not remove the include below
#include "TomatoWatering.h"

#include "Help/hwPins.h"
#include "LiquidCrystal.h"
#include <stdio.h>
#include <string.h>

/* Create buffers */
char buf[50];
char day[10];


LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*Test Watering Mode*/
WateringMode* wateringMode = WateringMode::Instance();
/*Test OperatingControl*/
OperatingControl* operatingControl = OperatingControl::Instance();
/*Test OperatingState*/
OperatingState* operatingState = OperatingState::Instance();
/*Test HardwareControl*/
HardwareControl* hardwareControl = HardwareControl::Instance();
/*Test WateringControl*/
WateringControl* wateringControl = WateringControl::Instance();
/*Test ATimer*/
ATimer* oneSecondTimer = new ATimer(SECONDS_TO_MILLISECONDS(1));



//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
//	Serial.begin(9600);
//	Serial.print("hello, world!\n");
	LOG_DAEMON_DEBUG(1, "Hello");

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 4);
	// Print a message to the LCD.
	lcd.print("hello, world!");
	pinMode(LCD_A, OUTPUT);
	digitalWrite(LCD_A, HIGH);

	oneSecondTimer->restart();

	PotModel* tempPot = new PotModel();
	tempPot->setPotIndex(1);
	tempPot->setPotName("Tomaten");
	wateringMode->addPot(tempPot);
	tempPot = new PotModel();
	tempPot->setPotIndex(2);
	tempPot->setPotName("Karotten");
	wateringMode->addPot(tempPot);

	WateringSettings* tempSettings = new WateringSettings(1, 1, 500, 1000, &Time(23, 31, 0));
	wateringMode->addWateringSettings(tempSettings);
	tempSettings = new WateringSettings(2, 1, 100, 200, &Time(23, 30, 0));
	wateringMode->addWateringSettings(tempSettings);
	tempSettings = new WateringSettings(3, 2, 100, 200, &Time(23, 31, 0));
	wateringMode->addWateringSettings(tempSettings);
	tempSettings = new WateringSettings(4, 2, 500, 1000, &Time(23, 30, 0));
	wateringMode->addWateringSettings(tempSettings);

	wateringMode->getWateringModeState()->setIsAutomaticMode(true);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here

	operatingControl->update();
	wateringControl->update();

	if(oneSecondTimer->onRestart())
	{
		print();
	}
}

void print()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(operatingState->getActualTime()->getTimeString("hh:mm"));
	lcd.setCursor(10, 0);
	lcd.print(operatingState->getActualTemperature());
}
