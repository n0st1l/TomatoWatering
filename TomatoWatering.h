// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _TomatoWatering_H_
#define _TomatoWatering_H_
#include "Arduino.h"

// NOTE add your includes for the project TomatoWatering here

/*Include Libraries*/
#include "TimerOne.h"
#include "date.h"
#include "DHT.h"
#include "DS1302.h"
#include "LiquidCrystal.h"
#include "time.h"

/*Include Helpers*/
#include "Help/HelperClass.h"
#include "Help/hwPins.h"
#include "Help/types.h"

/*Include Models*/
#include "Model/OperatingState.h"
#include "Model/PotModel.h"
#include "Model/WateringMode.h"
#include "Model/WateringModeState.h"
#include "Model/WateringSettings.h"

/*Include Controls*/
#include "Control/OperatingControl.h"

//end of add your includes here

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project TomatoWatering here
void print_time();
void printHelloWorld();


//Do not add code below this line
#endif /* _TomatoWatering_H_ */
