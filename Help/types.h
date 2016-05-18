/*
 * types.h
 *
 *  Created on: 17.08.2015
 *      Author: Administrator
 */

#ifndef HELP_TYPES_H_
#define HELP_TYPES_H_


typedef enum DigitalOutputType
{
	eDigitalOutputTypeUndefined	= 0,
    eDigitalOutputTypeValve_1   = 1,
	eDigitalOutputTypeValve_2   = 2,
	eDigitalOutputTypeValve_3   = 3,
	eDigitalOutputTypeValve_4   = 4,
    eDigitalOutputTypePump		= 5,
	eDigitalOutputTypeReserve_1 = 6,
	eDigitalOutputTypeReserve_2 = 7,
	eDigitalOutputTypeReserve_3 = 8
} DigitalOutputType_t;

typedef enum DigitalOutputState
{
	eDigitalOutputStateDisabled	= 0,
    eDigitalOutputStateEnabled	= 1
} DigitalOutputState_t;


#endif /* HELP_TYPES_H_ */
