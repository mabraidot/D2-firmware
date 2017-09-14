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
#include <MultiStepper.h>
AccelStepper stepperA(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperB(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepperC(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);
MultiStepper steppers;

long positions[3]; // Array of desired stepper positions
//boolean running = false;

// @TODO: remove this!, it is only for demonstration purpose
void DeltaRobot::stepper_choreography(int mode = 0){
  plan.put(0, 0, -300);
  if(mode == 0){
    int i = 0;
    while(i<360){
      plan.put(80*cos(i), 80*sin(i), -300);
      i += 6;
    }
  }
  
  if(mode == 1){
    int j = 0;
    while(j<4){
      plan.put(0, 0, -280);
      plan.put(80, 80, -310);
      plan.put(0, 0, -280);
      plan.put(-80, -80, -310);
      j++;
    }
  }
  plan.put(0, 0, -300);
}






void DeltaRobot::homing(){
  
  for(int i = 0; i < 3; i++){
    arms[i].position = 0;
    arms[i].homed = 0;
  }
  
  boolean homed = false;
  float speed = 1000.0;
  float angle = -180.0;

	stepperA.setMaxSpeed(speed*2);
  stepperB.setMaxSpeed(speed*2);
  stepperC.setMaxSpeed(speed*2);
  stepperA.setAcceleration(speed);
  stepperB.setAcceleration(speed);
  stepperC.setAcceleration(speed);
  
  positions[0] = positions[1] = positions[2] = angle2steps(angle);
  stepperA.moveTo(positions[0]);
  stepperB.moveTo(positions[1]);
  stepperC.moveTo(positions[2]);
  
  while(!arms[0].homed || !arms[1].homed || !arms[2].homed){
  
    if(!arms[0].homed){
      if(endstops.is_A_hit()){
        stepperA.setSpeed(0);
        stepperA.moveTo(stepperA.currentPosition());
        arms[0].homed = 1;
      }else{
        stepperA.run();
      }
    }
    if(!arms[1].homed){
      if(endstops.is_B_hit()){
        stepperB.setSpeed(0);
        stepperB.moveTo(stepperB.currentPosition());
        arms[1].homed = 1;
      }else{
        stepperB.run();
      }
    }
    if(!arms[2].homed){
      if(endstops.is_C_hit()){
        stepperC.setSpeed(0);
        stepperC.moveTo(stepperC.currentPosition());
        arms[2].homed = 1;
      }else{
        stepperC.run();
      }
    }

  }

  // We set the new initial position. Horizontal arm is considered the zero angle.
  angle = -75.0;
  arms[0].position = angle2steps(angle - DELTA_X_OFFSET);
  arms[1].position = angle2steps(angle - DELTA_Y_OFFSET);
  arms[2].position = angle2steps(angle - DELTA_Z_OFFSET);
  stepperA.setCurrentPosition(arms[0].position);
  stepperB.setCurrentPosition(arms[1].position);
  stepperC.setCurrentPosition(arms[2].position);
  // After homing, go to angle zero
  plan.putAngle(0.0, 0.0, 0.0);
}

    
void DeltaRobot::init()
{
  
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);  
  pinMode(Z_DIR_PIN, OUTPUT); 
  pinMode(Z_ENABLE_PIN, OUTPUT);
  
  endstops.init();
  plan.init(true);
  homing();

  float speed = 800.0;
  stepperA.setMaxSpeed(speed*2);
  stepperB.setMaxSpeed(speed*2);
  stepperC.setMaxSpeed(speed*2);
  stepperA.setAcceleration(speed);
  stepperB.setAcceleration(speed);
  stepperC.setAcceleration(speed);
  
  steppers.addStepper(stepperA);
  steppers.addStepper(stepperB);
  steppers.addStepper(stepperC);

}

void DeltaRobot::run()
{
  if(!plan.isEmpty()){
    
    if(!plan.isBusy()){

      positions[0] = angle2steps(plan.getXTheta());
      positions[1] = angle2steps(plan.getYTheta());
      positions[2] = angle2steps(plan.getZTheta());
      
      /*debug.println("Prev Position ----------------------------> ");
      debug.println((String)arms[0].position);
      debug.println((String)arms[1].position);
      debug.println((String)arms[2].position);
      debug.println("New Theta ----------------------------> ");
      debug.println((String)plan.getXTheta());
      debug.println((String)plan.getYTheta());
      debug.println((String)plan.getZTheta());
      debug.println("Steps to move ----------------------------> ");
      debug.println((String)positions[0]);
      debug.println((String)positions[1]);
      debug.println((String)positions[2]);
      */
      
      steppers.moveTo(positions);
      

    }else{
			// Update arm positions while planner command is being executed
      arms[0].position = stepperA.currentPosition();
      arms[1].position = stepperB.currentPosition();
      arms[2].position = stepperC.currentPosition();
		}
    
  }
  
  // Run motors. Free up the planner if motors have finished, in order to take another command
  if(!steppers.run()){
    plan.next();
  }
}

/**
 * Calculates the number of steps it takes to get to an angle
 */
long DeltaRobot::angle2steps(float angle)
{
  return (long) round((angle / 360) * _stepsPerTurn * _gearRatio);
}

