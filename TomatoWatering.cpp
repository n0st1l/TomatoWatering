// Do not remove the include below
#include "TomatoWatering.h"

#include "Help/hwPins.h"
#include "DHT.h"
#include "LiquidCrystal.h"
#include <stdio.h>
#include <string.h>
#include <DS1302.h>

/* Create buffers */
char buf[50];
char day[10];


LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*Test Watering Mode*/
WateringMode* wateringMode = new WateringMode();
/*Test OperatingControl*/
OperatingControl* operatingControl = OperatingControl::Instance();
/*Test OperatingState*/
OperatingState* operatingState = OperatingState::Instance();
int count = 0;



//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	Serial.begin(9600);

	Serial.println("DHTxx test!");

	//dht.begin();

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 4);
	// Print a message to the LCD.
	lcd.print("hello, world!");
	pinMode(LCD_A, OUTPUT);
	digitalWrite(LCD_A, HIGH);
	pinMode(RELAY1, OUTPUT);
	pinMode(RELAY2, OUTPUT);
	pinMode(RELAY3, OUTPUT);
	pinMode(RELAY4, OUTPUT);
	pinMode(RELAY5, OUTPUT);
	pinMode(RELAY6, OUTPUT);
	pinMode(RELAY7, OUTPUT);
	pinMode(RELAY8, OUTPUT);


	//	/* Initialize a new chip by turning off write protection and clearing the
	//	     clock halt flag. These methods needn't always be called. See the DS1302
	//	     datasheet for details. */
	//	rtc.write_protect(false);
	//	rtc.halt(false);
	//
	//	/* Make a new time object to set the date and time */
	//	/*   Tuesday, May 19, 2009 at 21:16:37.            */
	//	Time t(23, 59, 30);
	//	Date d(2015, 8, 24);
	//
	//	/* Set the time and date on the chip */
	//	rtc.time(t);
	//	rtc.date(d);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here

	if(count%5 == 0)
	{
		print();
	}
	operatingControl->onTimerTimeout();
	count++;
	delay(1000);
}

void print()
{
	/* Get the current time and date from the chip */
	lcd.clear();
	lcd.print(operatingState->getActualTime()->getTimeString("hh:mm"));
	lcd.setCursor(0, 1);
	lcd.print(operatingState->getActualDate()->getDateString());
	lcd.setCursor(0, 2);
	lcd.print(operatingState->getActualTemperature());
	lcd.setCursor(0, 3);
	lcd.print(operatingState->getActualHumidity());
}
