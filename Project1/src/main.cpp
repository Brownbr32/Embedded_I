#include <Arduino.h>
#include <commands.h>
using namespace std;


int i;


    char warnString[80] = "\nwarning: You're on a timer! Options:\n  getVal\n  setVal\n  helpMe";
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  for (i = 0; i < numLeds; i++)
    pinMode(leds[i], OUTPUT);
    delay(1000);
    Serial.println(warnString);
}

// the loop routine runs over and over again forever:
void loop() {
  if (onVal[3]) colorShift();
  if (Serial.peek() > 0) {
    readSerial();
    Serial.println(warnString);
   }
}