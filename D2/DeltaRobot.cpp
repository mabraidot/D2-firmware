/**
 * A singleton object to manage the robot's arms
 */
#include "Configurations.h"
#include "Debug.h"
#include "Endstops.h"
#include "DeltaRobot.h"
#include "Planner.h"

DeltaRobot delta;
Planner plan = Planner();

void DeltaRobot::init()
{
  // @TODO: make a homing routine
  endstops.init();
  
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
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
      // restar de la posicion actual y mover los motores a los angulos calculados
      /*plan.getXTheta();
      plan.getYTheta();
      plan.getZTheta();*/
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

