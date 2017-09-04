/**
 * A singleton object to manage the robot's arms
 */
#include "Configurations.h"
#include "Debug.h"
#include "Endstops.h"
#include "DeltaRobot.h"
#include "Planner.h"

DeltaRobot delta;




/**
 * CAMBIAR POR NUEVA LIBRERIA STEPPER
 */
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
void DeltaRobot::stepper_rotate(int deg){
  /*stepperA.moveTo(deg);
  stepperB.moveTo(deg);
  stepperC.moveTo(deg);
  */
  if(deg > 0 && deg > 90){deg = 90;}
  if(deg < 0 && deg < -90){deg = -90;}
  motors.rotate(deg, deg, deg);
}
void DeltaRobot::stepper_choreography(int mode = 0){
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
/**
 * FIN CAMBIAR POR NUEVA LIBRERIA STEPPER
 */









    
void DeltaRobot::init()
{
  // @TODO: make a homing routine
  endstops.init();
  plan.init(true);
  for(int i = 0; i < 3; i++){
    arms[i].position = 90.0;
    arms[i].homed = 1;
  }
  
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT); 
  pinMode(Z_ENABLE_PIN, OUTPUT);


  /**
   * CAMBIAR POR NUEVA LIBRERIA STEPPER
   */
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
  /**
   * FIN CAMBIAR POR NUEVA LIBRERIA STEPPER
   */

}

void DeltaRobot::run()
{
  /** 
   * si hay comandos en la queue (plan.count > 0) 
   * leer el comando de la tail
   * si no esta ocupado (plan.busy = true)
   * setear el movimiento del motor
   * fin si
   * resto del bloque de control del motor stop/run
   * si el motor termino
   * mover la tail del buffer al siguiente comando
   * fin si
   * fin si hay comandos en la queue
   */
  if(!plan.isEmpty()){
    
    if(plan.isBusy()){
      float xtheta = plan.getXTheta() - arms[0].position;
      float ytheta = plan.getYTheta() - arms[1].position;
      float ztheta = plan.getZTheta() - arms[2].position;
      
      motors.rotate(xtheta, ytheta, ztheta);
      
      plan.next();

      // Update arm positions after motors have finished rotating
      arms[0].position += xtheta;
      arms[1].position += xtheta;
      arms[2].position += xtheta;
    }
    
    // Si los motores terminaron el comando, liberar el planner 
    // para poder tomar otro comando
    /*if (leftMotor.finished() && rightMotor.finished()) {
      //delay(1000);
      plan.next();
    }*/
  }
  // iniciar o parar los motores
  /*if (leftMotor.finished()) {
    leftMotor.stop();
  }else{
    leftMotor.run();
  }
  if (rightMotor.finished()) {
    rightMotor.stop();
  }else{
    rightMotor.run();
  }*/
}

