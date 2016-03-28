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
#include "AButton.h"
#include "ATimer.h"
#include "date.h"
#include "DHT.h"
#include "DS1302.h"
#include "LiquidCrystal.h"
#include "time.h"

/*Include Helpers*/
#include "Help/HelperClass.h"

/*Include Models*/
#include "Model/OperatingState.h"
#include "Model/PotModel.h"
#include "Model/WateringMode.h"
#include "Model/WateringModeState.h"
#include "Model/WateringSettings.h"

/*Include Screens*/
#include "Screen/MainScreen.h"
#include "Screen/WateringScreen.h"

/*Include Controls*/
#include "Control/HardwareControl.h"
#include "Control/OperatingControl.h"
#include "Control/WateringControl.h"

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

/*IO*/
LiquidCrystal* liquidCrystal;
AButton* buttonTop;
AButton* buttonBottom;
AButton* buttonLeft;
AButton* buttonRight;

/*Timer*/
ATimer* lcdTimer;

/*Models*/
WateringMode* wateringMode;
OperatingState* operatingState;

/*Screens*/
MainScreen* mainScreen;
WateringScreen* wateringScreen;

/*Controls*/
HardwareControl* hardwareControl;
OperatingControl* operatingControl;
WateringControl* wateringControl;

/*Functions*/
void createPots();
void createWateringSettings();


//Do not add code below this line
#endif /* _TomatoWatering_H_ */
