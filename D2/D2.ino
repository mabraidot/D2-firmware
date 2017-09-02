#include "Arduino.h"
#include "Configurations.h"
#include "Debug.h"
#include "DeltaRobot.h"

void setup() {
  Serial.begin(250000);
  delta.init();
}

void loop() {
  if (Serial.available()) process_serial();
  delta.run();
}


void process_serial(){
  char cmd = Serial.read();
  if (cmd > 'Z') cmd -= 32;
  switch (cmd) {
    case 'H': help(); break;
    case 'F': delta.stepper_rotate(Serial.parseInt()); break;
    case 'B': delta.stepper_rotate(-1*Serial.parseInt()); break;
    case 'C': delta.stepper_choreography(0); break;
    case 'P': delta.stepper_choreography(1); break;
  }
  
  while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
  
}

void help() {
  Serial.println(F("\nStepper motor interface emulator"));
  Serial.println(F("Available serial commands: (lines end with CRLF or LF)"));
  Serial.println(F(""));
  Serial.println(F("H: will print this help message again"));
  Serial.println(F("F123: sets the target rotation for the motor to 123 degrees, Forward"));
  Serial.println(F("B123: sets the target rotation for the motor to 123 degrees, Backward"));
  Serial.println(F("C: Little choreography"));
  Serial.println(F("P: P&P choreography"));
  
}
