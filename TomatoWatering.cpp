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
unsigned long count = 0;



//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	Serial.begin(9600);

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 4);
	// Print a message to the LCD.
	lcd.print("hello, world!");
	pinMode(LCD_A, OUTPUT);
	digitalWrite(LCD_A, HIGH);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here

//	if(count%5 == 0)
//	{
//		wateringMode->getWateringModeState()->setIsManualMode(true);
//	    wateringControl->startManualWatering(3);
//	}
//	if(count%6 == 0)
//	{
//		print();
//	    wateringControl->startManualWatering(1);
//	}
//	if(count%7 == 0)
//	{
//		wateringControl->stopWatering();
//	}

	if(count%100 == 0)
	{
		//every one second
	}
	if(count%(10 * 100) == 0)
	{
		//every ten seconds
		operatingControl->onTenSecondsTimerTimeout();
		print();
	}
	if(count%(60 * 100) == 0)
	{
		//every minute
		operatingControl->onOneMinuteTimerTimeout();
	}

	count++;
	delay(10);
}

void print()
{
	/* Get the current time and date from the chip */
	lcd.setCursor(0, 0);
	lcd.print("                    ");
	lcd.setCursor(0, 0);
	lcd.print(operatingState->getActualTime()->getTimeString("hh:mm"));
	lcd.setCursor(0, 1);
	lcd.print("                    ");
	lcd.setCursor(0, 1);
	lcd.print(operatingState->getActualDate()->getDateString());
	lcd.setCursor(0, 2);
	lcd.print("                    ");
	lcd.setCursor(0, 2);
	lcd.print(operatingState->getActualTemperature());
	lcd.setCursor(0, 3);
	lcd.print("                    ");
	lcd.setCursor(0, 3);
	Time *t1 = new Time(24, 00, 00);
	lcd.print(operatingState->getActualTime()->secsTo(t1));
}
