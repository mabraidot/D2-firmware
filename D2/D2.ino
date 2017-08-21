#include "Arduino.h"
#include "Configurations.h"

#include "Debug.h"
#include "Endstops.h"


void setup() {
  Serial.begin(250000);
  endstops.init();
}

void loop() {
  
}
