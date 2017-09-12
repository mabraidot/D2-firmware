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
#include <AccelStepper.h>
AccelStepper stepperA(AccelStepper::FULL2WIRE, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperB(AccelStepper::FULL2WIRE, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperC(AccelStepper::FULL2WIRE, Z_STEP_PIN, Z_DIR_PIN);
float xtheta,  ytheta,  ztheta = 0;
long xsteps,  ysteps,  zsteps = 0;

/*#include <A4988.h>
#include <SyncDriver.h>
A4988 stepperA(400*6.2, X_DIR_PIN, X_STEP_PIN, X_ENABLE_PIN);
A4988 stepperB(400*6.2, Y_DIR_PIN, Y_STEP_PIN, Y_ENABLE_PIN);
A4988 stepperC(400*6.2, Z_DIR_PIN, Z_STEP_PIN, Z_ENABLE_PIN);
SyncDriver motors(stepperA, stepperB, stepperC);
*/
void DeltaRobot::stepper_choreography(int mode = 0){
  if(mode == 0){
    static int i = 0;
    while(i<360){
      plan.put(80*cos(i), 80*sin(i), -300);
      i += 6;
    }
    plan.put(0, 0, -300);
  }
  
  if(mode == 1){
    static int j = 0;
    while(j<4){
      plan.put(0, 0, -250);
      plan.put(80, 80, -330);
      plan.put(0, 0, -250);
      plan.put(-80, -80, -330);
      j++;
    }
    plan.put(0, 0, -300);
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
    arms[i].position = 0.00;
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
  //stepperA.setEnablePin(X_ENABLE_PIN);
  stepperA.setMaxSpeed(500.0);
  stepperA.setAcceleration(100.0);

  //stepperB.setEnablePin(Y_ENABLE_PIN);
  stepperB.setMaxSpeed(500.0);
  stepperB.setAcceleration(100.0);

  //stepperC.setEnablePin(Z_ENABLE_PIN);
  stepperC.setMaxSpeed(500.0);
  stepperC.setAcceleration(100.0);
  /*
  char rpm = 1400;
  stepperA.begin(rpm,2);
  stepperA.setSpeedProfile(LINEAR_SPEED, 3000, 2000);
  stepperB.begin(rpm,2);
  stepperB.setSpeedProfile(LINEAR_SPEED, 3000, 2000);
  stepperC.begin(rpm,2);
  stepperC.setSpeedProfile(LINEAR_SPEED, 3000, 2000);
  */
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
    
    if(!plan.isBusy()){
      xtheta = plan.getXTheta() - arms[0].position;
      ytheta = plan.getYTheta() - arms[1].position;
      ztheta = plan.getZTheta() - arms[2].position;

      xsteps = (long) round( ( xtheta * 800 * 6.8 ) / 360 );
      ysteps = (long) round( ( ytheta * 800 * 6.8 ) / 360 );
      zsteps = (long) round( ( ztheta * 800 * 6.8 ) / 360 );
 
      /*debug.println("Prev Position ----------------------------> ");
      debug.println((String)arms[0].position);
      debug.println((String)arms[1].position);
      debug.println((String)arms[2].position);
      debug.println("New Theta ----------------------------> ");
      debug.println((String)xtheta);
      debug.println((String)ytheta);
      debug.println((String)ztheta);
      debug.println("Steps to move ----------------------------> ");
      debug.println((String)xsteps);
      debug.println((String)ysteps);
      debug.println((String)zsteps);
      */
      
      stepperA.moveTo(xsteps);
      stepperB.moveTo(ysteps);
      stepperC.moveTo(zsteps);
      

      /*motors.rotate(xtheta, ytheta, ztheta);
      plan.next();
      */

      // Update arm positions after motors have finished rotating
      arms[0].position += xtheta;
      arms[1].position += ytheta;
      arms[2].position += ztheta;

    }
    
  }
  // iniciar o parar los motores
  if(stepperA.distanceToGo() == 0){
    //stepperA.stop();
  }else{
    stepperA.run();
  }
  if(stepperB.distanceToGo() == 0){
    //stepperB.stop();
  }else{
    stepperB.run();
  }
  if(stepperC.distanceToGo() == 0){
    //stepperC.stop();
  }else{
    stepperC.run();
  }


  // Si los motores terminaron el comando, liberar el planner 
  // para poder tomar otro comando
  if (stepperA.distanceToGo() == 0 && stepperB.distanceToGo() == 0 && stepperC.distanceToGo() == 0) {
    plan.next();
    
  }
}

