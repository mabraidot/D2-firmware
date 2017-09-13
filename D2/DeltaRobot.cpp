/**
 * A singleton object to manage the robot's arms
 */
#include "Configurations.h"
#include "Debug.h"
#include "Endstops.h"
#include "DeltaRobot.h"
#include "Planner.h"

DeltaRobot delta;




#include <AccelStepper.h>
AccelStepper stepperA(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperB(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperC(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

long xsteps,  ysteps,  zsteps = 0;


// @TODO: remove this!, it is only for demonstration purpose
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








    
void DeltaRobot::init()
{
  // @TODO: make a homing routine
  endstops.init();
  plan.init(true);
  for(int i = 0; i < 3; i++){
    arms[i].position = 0;
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
  

  //stepperA.setEnablePin(X_ENABLE_PIN);
  stepperA.setMaxSpeed(5000.0);
  stepperA.setAcceleration(2000);
  stepperA.setSpeed(3000.0);

  stepperB.setMaxSpeed(5000.0);
  stepperB.setAcceleration(2000);
  stepperB.setSpeed(3000.0);

  stepperC.setMaxSpeed(5000.0);
  stepperC.setAcceleration(1000);
  stepperC.setSpeed(2500.0);
  

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

      xsteps = angle2steps(plan.getXTheta());
      ysteps = angle2steps(plan.getYTheta());
      zsteps = angle2steps(plan.getZTheta());
 
      debug.println("Prev Position ----------------------------> ");
      debug.println((String)arms[0].position);
      debug.println((String)arms[1].position);
      debug.println((String)arms[2].position);
      debug.println("New Theta ----------------------------> ");
      debug.println((String)plan.getXTheta());
      debug.println((String)plan.getYTheta());
      debug.println((String)plan.getZTheta());
      debug.println("Steps to move ----------------------------> ");
      debug.println((String)xsteps);
      debug.println((String)ysteps);
      debug.println((String)zsteps);
      
      
      stepperA.moveTo(xsteps);
      stepperB.moveTo(ysteps);
      stepperC.moveTo(zsteps);
      

    }else{
			// Update arm positions while planner command is being executed
      arms[0].position = stepperA.currentPosition();
      arms[1].position = stepperB.currentPosition();
      arms[2].position = stepperC.currentPosition();
		}
    
  }
  // Start motors
  stepperA.run();
  stepperB.run();
  stepperC.run();

  // Free up the planner if motors have finished, in order to take another command
  if (!stepperA.isRunning() && !stepperB.isRunning() && !stepperC.isRunning()) {
    plan.next();
  }
}

/**
 * Calculates the number of steps it takes to get to an angle
 */
long DeltaRobot::angle2steps(float angle)
{
	return (long) round((angle / 0.9) * _microsteps * _gearRatio);
}

