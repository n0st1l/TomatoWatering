/*
 * Log.h
 *
 *  Created on: 08.03.2016
 *      Author: Administrator
 */

#ifndef HELP_LOG_H_
#define HELP_LOG_H_

#include "SerialLogger.h"

	/** Define available log levels */
	typedef enum {
	    eLogDebug,  ///< Debug log level. For debugging only.
	    eLogInfo,   ///< Information output
	    eLogWarn,   ///< Warning
	    eLogError   ///< Error or fatal condition
	} eLogLevel_t;

	/** Define available log sources */
	typedef enum {
	    eSrcHardware,       ///< Log from hardware module
	    eSrcDaemon,         ///< Log from daemon application
	    eSrcApplication     ///< Log from GUI application
	} eLogSource_t;

	/** Define available log Ids */
	typedef enum {
	    eTomatoWatering = 0x100,
		eHelperClass = 0x101,
	    eHardwareControl = 0x201,
	    eOperatingControl = 0x202,
	    eWateringControl = 0x203
	} eDaemonLogIdTypes_t;


	/** Defines all log levels with Daemon as log source */
	#define LOG_DAEMON_DEBUG(id, data) \
		SerialLogger::Instance()->Log(eSrcDaemon, eLogDebug, id, data);

	#define LOG_DAEMON_INFO(id, data) \
		SerialLogger::Instance()->Log(eSrcDaemon, eLogInfo, id, data);

	#define LOG_DAEMON_WARNING(id, data) \
		SerialLogger::Instance()->Log(eSrcDaemon, eLogWarn, id, data);

	#define LOG_DAEMON_ERROR(id, data) \
		SerialLogger::Instance()->Log(eSrcDaemon, eLogError, id, data);

	/** Defines all log levels with Hardware module as log source */
	#define LOG_HW_DEBUG(id, data) \
		SerialLogger::Instance()->Log(eSrcHardware, eLogDebug, id, data);

	#define LOG_HW_INFO(id, data) \
		SerialLogger::Instance()->Log(eSrcHardware, eLogInfo, id, data);

	#define LOG_HW_WARNING(id, data) \
		SerialLogger::Instance()->Log(eSrcHardware, eLogWarn, id, data);

	#define LOG_HW_ERROR(id, data) \
		SerialLogger::Instance()->Log(eSrcHardware, eLogError, id, data);


#endif /* HELP_LOG_H_ */
