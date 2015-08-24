// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _TomatoWatering_H_
#define _TomatoWatering_H_
#include "Arduino.h"
//add your includes for the project TomatoWatering here
#include "TimerOne.h"
#include "Model/WateringSettings.h"
#include "Model/PotModel.h"
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
PotModel* tomatoPot;


//Do not add code below this line
#endif /* _TomatoWatering_H_ */
