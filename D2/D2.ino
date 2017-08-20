#include "Arduino.h"
#include "Configurations.h"
#include "Endstops.h"


void setup() {
  Serial.begin(115200);
}

void loop() {
  
}


void debug(String message, bool eol=false){
  if(eol){
    Serial.println(message);
  }else{
    Serial.print(message);
  }
}

