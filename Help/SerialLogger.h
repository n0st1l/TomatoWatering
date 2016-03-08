/*
 * SerialLogger.h
 *
 *  Created on: 08.03.2016
 *      Author: Administrator
 */

#ifndef HELP_SERIALLOGGER_H_
#define HELP_SERIALLOGGER_H_

#include "Arduino.h"
#include "WString.h"

class SerialLogger {
public:
	static SerialLogger *Instance();
	virtual ~SerialLogger();

    /**
     * Write log message
     *
     * Write log message to database. If current log level is higher then @a p_Level, log is
     * supressed. Current log level is read from config table.
     *
     * @param   p_Source    Log source module
     * @param   p_Level     Log level
     * @param   p_LogId     Log number or id to identify the log message and know how to interpret log data.
     * @param   p_Data      Log data
     * @param   p_UserId    Id of current user (optional)
     */
    void Log(int p_Source, int p_Level, int p_LogId, String p_Data = String(""), int p_UserId = -1);


private:
	SerialLogger();
	static SerialLogger* serialLogger;


};

#endif /* HELP_SERIALLOGGER_H_ */
