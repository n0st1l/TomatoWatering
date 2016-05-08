/*
 * SerialLogger.cpp
 *
 *  Created on: 08.03.2016
 *      Author: Administrator
 */

#include "SerialLogger.h"

#define LOGGER_ENABLE	false
SerialLogger* SerialLogger::serialLogger = 0;

SerialLogger* SerialLogger::Instance()
{
	if(serialLogger == 0)
	{
		serialLogger = new SerialLogger();
	}
	return serialLogger;
}

SerialLogger::SerialLogger() {
	if(LOGGER_ENABLE == true) {
		Serial.begin(57600);
	}

}

SerialLogger::~SerialLogger() {

	if(serialLogger != 0)
	{
		if(LOGGER_ENABLE == true) {
			Serial.end();
		}
		delete serialLogger;
	}
}

void SerialLogger::Log(int p_Source, int p_Level, int p_LogId, String p_Data, int p_UserId)
{
	if(LOGGER_ENABLE == true) {
		String output = String(millis()) +
				"_Level:" +
				String(p_Level) +
				"_LogId:" +
				String(p_LogId) +
				"_" +
				p_Data;

		Serial.println(output);
	}
}

