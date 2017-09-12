#include "Arduino.h"
#include "Configurations.h"
#include "Debug.h"
#include "DeltaRobot.h"
#include "Planner.h"



void setup() {
  Serial.begin(250000);
  delta.init();
}

void loop() {
  if (Serial.available()) process_serial();
  delta.run();
  
  /*
  static int serial_interval = 1000;
  static unsigned long serial_timeout = millis() + serial_interval;
  if(serial_timeout < millis()){

    //Serial.println("Empty------------------------------->");
    //Serial.println(plan.isEmpty());
    //Serial.println("Busy------------------------------->");
    //Serial.println(plan.isBusy());
    
    serial_timeout = millis() + serial_interval;
  }*/
  
}


void process_serial(){
  char cmd = Serial.read();
  if (cmd > 'Z') cmd -= 32;
  switch (cmd) {
    case 'H': help(); break;
    case 'C': delta.stepper_choreography(0); break;
    case 'P': delta.stepper_choreography(1); break;

    case 'K': 
      float pos1 = Serial.parseFloat(); 
      float pos2 = Serial.parseFloat(); 
      float pos3 = Serial.parseFloat(); 
      plan.put(pos1, pos2, pos3); 
      break;
    
  }
  
  while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
  
}

void help() {
  Serial.println(F("\nStepper motor interface emulator"));
  Serial.println(F("Available serial commands: (lines end with CRLF or LF)"));
  Serial.println(F(""));
  Serial.println(F("H: will print this help message again"));
  Serial.println(F("C: Little choreography"));
  Serial.println(F("P: P&P choreography"));
  Serial.println(F("K1,2,-3: Inverse Kinematics (X,Y,Z) -> (1,2,-3)"));
}
