#include "Arduino.h"
#include "Configurations.h"
#include "Debug.h"
#include "DeltaRobot.h"

//#include <AccelStepper.h>
#include <A4988.h>
#include <SyncDriver.h>


/*
AccelStepper stepperA(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperB(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperC(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
*/
A4988 stepperA(400*6.2, X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN);
A4988 stepperB(400*6.2, Y_DIR_PIN, Y_STEP_PIN, Y_ENABLE_PIN);
A4988 stepperC(400*6.2, Z_DIR_PIN, Z_STEP_PIN, Z_ENABLE_PIN);
SyncDriver motors(stepperA, stepperB, stepperC);

void setup() {
  Serial.begin(250000);
  
  delta.init();
  
  /*
  stepperA.setMaxSpeed(200.0);
  stepperA.setAcceleration(100.0);
  stepperB.setMaxSpeed(200.0);
  stepperB.setAcceleration(100.0);
  stepperC.setMaxSpeed(200.0);
  stepperC.setAcceleration(100.0);
  */
  
  char rpm = 1400;
  stepperA.begin(rpm,2);
  stepperA.setSpeedProfile(LINEAR_SPEED, 3000, 2000);
  stepperB.begin(rpm,2);
  stepperB.setSpeedProfile(LINEAR_SPEED, 3000, 2000);
  stepperC.begin(rpm,2);
  stepperC.setSpeedProfile(LINEAR_SPEED, 3000, 2000);
  
}

void loop() {
  /*stepperA.run();
  stepperB.run();
  stepperC.run();
  */
  
  if (Serial.available()) process_serial();
}

void stepper_rotate(int deg){

  /*stepperA.moveTo(deg);
  stepperB.moveTo(deg);
  stepperC.moveTo(deg);
  */
  if(deg > 0 && deg > 90){deg = 90;}
  if(deg < 0 && deg < -90){deg = -90;}
  motors.rotate(deg, deg, deg);
}
void stepper_choreography(int mode = 0){
  if(mode == 0){
    motors.rotate(-20, -20, -20);
    motors.rotate(0, 0, 40);
    motors.rotate(40, 0, -40);
    motors.rotate(-40, 40, 0);
    motors.rotate(0, -40, 40);
    motors.rotate(0, 0, -40);
  
    motors.rotate(-40, -40, -40);
    motors.rotate(0, 0, 20);
    motors.rotate(20, 0, -20);
    motors.rotate(-20, 20, 0);
    motors.rotate(0, -20, 20);
    motors.rotate(0, 0, -20);
  
    motors.rotate(60, 60, 60);
  }
  
  if(mode == 1){
    motors.rotate(-30, -30, -30);
    
    motors.rotate(10, 10, 30);
    motors.rotate(-10, -10, -30);

    motors.rotate(10, 30, 10);
    motors.rotate(-10, -30, -10);

    motors.rotate(30, 10, 10);
    motors.rotate(-30, -10, -10);

    motors.rotate(30, 30, 30);
  }
}


void process_serial(){
  char cmd = Serial.read();
  if (cmd > 'Z') cmd -= 32;
  switch (cmd) {
    case 'H': help(); break;
    case 'F': stepper_rotate(Serial.parseInt()); break;
    case 'B': stepper_rotate(-1*Serial.parseInt()); break;
    case 'C': stepper_choreography(0); break;
    case 'P': stepper_choreography(1); break;
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
