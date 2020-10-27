#include <Arduino.h>
#include <string>
using namespace std;

            // R, G, B
int leds[3] = {30,39,40};
int numLeds  = 3;
int onVal[4] = {0,0,0,1};

void printVals() {
    Serial.print("r: ");
    Serial.print(onVal[0]);
    Serial.print(",\tg: ");
    Serial.print(onVal[1]);
    Serial.print(",\tb: ");
    Serial.println(onVal[2]);
    onVal[3] = 1;
}

void setVals() {
    Serial.println();
    Serial.println("What color would you like to change?");
    Serial.println("  r, g, b");
    String color = "";
    Serial.flush();
    while (!color.length())
        color = Serial.readString();
    Serial.print("You chose: ");
    Serial.println(color);
    Serial.flush();

    Serial.println("What intensity would you like? (0-100)");
    int ensity = -2;
    String myInt = "";
    while(!myInt.length())
        myInt = Serial.readString();
    ensity = myInt.toInt();
    Serial.print("You chose: ");
    Serial.println(ensity);
    int idx = 0;
    switch(color[0]) {
        case 'b' :
            idx++;
        case 'g' :
            idx++;
    }
    onVal[idx] = ensity;
    analogWrite(leds[0],onVal[0]);
    analogWrite(leds[1],onVal[1]);
    analogWrite(leds[2],onVal[2]);
    onVal[3] = 0;
}

void help() {
    Serial.println("\nsee values written to LEDs: getVal");
    Serial.println("  note that this command begins color changes.");
    Serial.println("write values to LEDs: setVal color(r,g,b) intensity(0-100)");
    Serial.println("  example: setVal r 20");
    Serial.println("  note that this command terminates color changes.");
    Serial.println("see this help menu: helpMe");
}
void readSerial() {

    String cmd = Serial.readString();
    cmd.replace('\n','\0');
    cmd.replace('\r','\0');

    if      (cmd == "getVal") printVals();
    else if (cmd == "setVal") setVals();
    else if (cmd == "helpMe") help();
    else Serial.println("\nOops! Looks like you missed it!");
    Serial.flush();
}

int inc[3] = {1,1,1};
void colorShift() {
    int i = 0;
  if (millis()%500 == 0) {
   for (i = 0; i<3; i++) {
    if (onVal[i] < 2) inc[i] = 1;
    if (onVal[i] > 50) inc[i] = -1;
    onVal[i] += (i + 1)*inc[i];
    analogWrite(leds[i],onVal[i]);
   }
   delay(1);
  }
}