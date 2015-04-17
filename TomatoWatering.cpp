// Do not remove the include below
#include "TomatoWatering.h"


//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
// Add your initialization code here
}

// The loop function is called in an endless loop
void loop()
{
	Timer1.initialize();
	Timer1.attachInterrupt(printHelloWorld);

//Add your repeated code here
}

void printHelloWorld(){
	Serial.print(("HelloWorld\n"));
}
