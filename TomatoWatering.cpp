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


DHT dht(DHT22_DATA, DHT22);
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
/* Create a DS1302 object */
DS1302 rtc(DS1302_RST, DS1302_IO, DS1302_SCK);

/*Test Watering Mode*/
WateringMode* wateringMode = new WateringMode();


//The setup function is called once at startup of the sketch
void setup()
{
	// Add your initialization code here
	Serial.begin(9600);
	Time* tempTime = new Time(23, 59);

	Serial.println("DHTxx test!");

	dht.begin();

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


	/* Initialize a new chip by turning off write protection and clearing the
	     clock halt flag. These methods needn't always be called. See the DS1302
	     datasheet for details. */
	rtc.write_protect(false);
	rtc.halt(false);

	/* Make a new time object to set the date and time */
	/*   Tuesday, May 19, 2009 at 21:16:37.            */
	Time t(23, 59, 30);
	Date d(2015, 8, 24);

	/* Set the time and date on the chip */
	rtc.time(t);
	rtc.date(d);
}

// The loop function is called in an endless loop
void loop()
{
	//Add your repeated code here
	//	Timer1.initialize();
	//	Timer1.attachInterrupt(printHelloWorld);

	print_time();
	delay(5000);
}

void printHelloWorld(){
	//	String tempString;
	//	tempString = "TomatoPot Number: " + String(tomatoPot->getPotNumber()) + "\n";
	//	Serial.print(tempString);
	//	tempString = "TomatoPot Name: " + tomatoPot->getPotName() + "\n";
	//	Serial.print(tempString);
	//	for(int i = 0 ; i < 2 ; i++)
	//	{
	//	tempString = String(tomatoPot->getWateringSettings(i)->getWaterQuantity()) + "\n";
	//	Serial.print(tempString);
	//	tempString = String(tomatoPot->getWateringSettings(i)->getWateringTime()->getTimeString()) + "\n";
	//	Serial.print(tempString);
	//	}

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	float t = dht.readTemperature();

	// check if returns are valid, if they are NaN (not a number) then something went wrong!
	if (isnan(t) || isnan(h)) {
		Serial.println("Failed to read from DHT");
	} else {
		Serial.print("Humidity: ");
		Serial.print(h);
		Serial.print(" %\t");
		Serial.print("Temperature: ");
		Serial.print(t);
		Serial.println(" *C");
	}
}

void print_time()
{
	/* Get the current time and date from the chip */
	Time t = rtc.time();
	Date d = rtc.date();
	lcd.clear();
	lcd.print(t.getTimeString("hh:mm:ss"));
	lcd.setCursor(0, 1);
	lcd.print(d.getDateString());
	lcd.setCursor(0, 2);
	WateringSettings* wateringSettings = new WateringSettings(0, 1);
	lcd.print(wateringMode->addWateringSettings(wateringSettings));
	lcd.print(wateringMode->getFreeWateringSettingsIndex());
	//lcd.print(wateringMode->getFreeWateringSettingsIndex());
}
