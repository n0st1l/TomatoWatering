// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _TomatoWatering_H_
#define _TomatoWatering_H_
#include "Arduino.h"

// NOTE add your includes for the project TomatoWatering here

/*Include Models*/
#include "Model/OperatingState.h"
#include "Model/PotModel.h"
#include "Model/WateringMode.h"
#include "Model/WateringModeState.h"
#include "Model/WateringSettings.h"

/*Include Controls*/
#include "Control/HardwareControl.h"
#include "Control/OperatingControl.h"
#include "Control/WateringControl.h"

/*Include Screens*/
#include "Screen/MainScreen.h"
#include "Screen/WateringScreen.h"

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

/*Models*/
WateringMode* wateringMode;
OperatingState* operatingState;

/*Controls*/
HardwareControl* hardwareControl;
OperatingControl* operatingControl;
WateringControl* wateringControl;

/*Screens*/
MainScreen* mainScreen;
WateringScreen* wateringScreen;

/*Functions*/
void createPots();
void createWateringSettings();


//Do not add code below this line
#endif /* _TomatoWatering_H_ */
