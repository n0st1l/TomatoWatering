/*
 * hwPins.h
 *
 *  Created on: 17.04.2015
 *      Author: Administrator
 */

#ifndef HELP_HWPINS_H_
#define HELP_HWPINS_H_

//LCD Pins
#define LCD_RS		25 //LCD Pin RS
#define LCD_E		24 //LCD powerOn: high, powerOff: low
#define LCD_A		27 //LCD backLightOn: high, backLightOff: low
#define LCD_D4		26 //LCD Data Pin 4
#define LCD_D5		29 //LCD Data Pin 5
#define LCD_D6		28 //LCD Data Pin 6
#define LCD_D7		31 //LCD Data Pin 7

//TimeModul Pins
#define DS1302_SCK	41 //TimeModul SCK
#define DS1302_IO	40 //TimeModul I/O
#define DS1302_RST	43 //TimeModul RST

//TemperatureModul Pins
#define DHT22_DATA	23 //TempModul Data Pin

//Button Pins
#define BUTTON_TOP		47
#define BUTTON_BOTTOM	46
#define BUTTON_LEFT		44
#define BUTTON_RIGHT	45
#define BUTTON_RESERVE1	49
#define BUTTON_RESERVE2	48

//Relay Pins
#define RELAY1	33
#define RELAY2	32
#define RELAY3	35
#define RELAY4	34
#define RELAY5	37
#define RELAY6	36
#define RELAY7	38
#define RELAY8	39

//Serial Pins
#define SERIAL_RX0	0
#define SERIAL_TX0	1
#define SERIAL_TX3	14
#define SERIAL_RX3	15
#define SERIAL_TX2	16
#define SERIAL_RX2	17
#define SERIAL_TX1	18
#define SERIAL_RX1	19
#define SERIAL_SDA	20
#define SERIAL_SDL	21

//Pump Data
#define PUMP_OUTPUT 100 // [ml/s] //TODO Change this value

#endif /* HELP_HWPINS_H_ */
