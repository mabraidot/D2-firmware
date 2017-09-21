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
boolean running = false;

// @TODO: remove this!, it is only for demonstration purpose
void DeltaRobot::add_choreography(int mode){
  if(!plan.isFull() && choreography == 0 && mode > 0){
    choreography = mode;
  }else{
    debug.println("Planner is busy. You cannot add any new movement.");
  }
}
void DeltaRobot::stepper_choreography(){

  static boolean delta_start_centered = false;
  static boolean delta_end_centered = false;
  static boolean delta_choreo_finished = false;
  static int i, j = 0; // circle and pick and place vars
  
  if(!plan.isFull() && choreography > 0){
    // do the opening movement
    if(!delta_start_centered){
      delta_start_centered = plan.put(0, 0, -300);
    }

    if(!delta_choreo_finished){
      
      // CIRCLE
      if(choreography == 1){

          static float rads = 0.0;
          if(i <= 360){
            rads = i*3.1415/180.0;
            plan.put(110*cos(rads), 110*sin(rads), -300);
            i += 1;
          }
          if(i > 360 && j <= 360){
            rads = j*3.1415/180.0;
            plan.put(50*cos(rads), 50*sin(rads), -240);
            j += 1;
          }
          if(i > 360 && j > 360){
            //delta_mode1_finished = true;
            delta_choreo_finished = true;
            i = j = 0;
            rads = 0.0;
          }

      // PICK AND PLACE
      }else if(choreography == 2){
        
        static int y = 20; // How high in the z coordinate rise the arm
        static int yy = 0; // y position
        static bool yyy = false; // does y coordinate went through negative position already
        if(j < 240){

          y = -y;
          yy = y/2-abs(y)/2;
          if(yy < 0){
            if(yyy){
              yy *= -1;
              yyy = false;
            }else{
              yyy = true;
            }

          }
          plan.put((float) j-(110.0-(y/2)), (float) yy, (float) -(300.0-(y/2)));
          
          j = j + (10+(y/2));

        }else{
          delta_choreo_finished = true;
          y = 20;
          yy = 0;
          yyy = false;
          j = 0;
        }

      // SIGMOID CURVE
      }else if(choreography == 3){

        static int s = -100;
        if(s<100){
          float sigmoid = 200.0 / (1.0 + exp(-0.05 * s));
          plan.put(s, sigmoid-100, -300);
          s++;
        }else{
          delta_choreo_finished = true;
          s = -100;
        }

      }

    }else if(!delta_end_centered){
      delta_end_centered = plan.put(0, 0, -300);
    }


    //if(delta_end_centered && delta_mode1_finished){
    if(delta_end_centered && delta_choreo_finished){

      debug.println("<--------- End of choreography ---------> ");
      
      choreography = 0;

      delta_start_centered = false;
      delta_choreo_finished = false;
      delta_end_centered = false;
    }

  }

}




void DeltaRobot::setVelocity(float speed, float acceleration){
  stepperA.setMaxSpeed(speed);
  stepperB.setMaxSpeed(speed);
  stepperC.setMaxSpeed(speed);
  stepperA.setAcceleration(acceleration);
  stepperB.setAcceleration(acceleration);
  stepperC.setAcceleration(acceleration);
}


void DeltaRobot::homing(){
  
  for(int i = 0; i < 3; i++){
    arms[i].homed = 0;
  }
  
  boolean homed = false;
  float angle = -180.0;

	setVelocity(2000.0, 1000.0);
  
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
  choreography = 0;

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);  
  pinMode(Z_DIR_PIN, OUTPUT); 
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(MAGNET, OUTPUT); 

  endstops.init();
  plan.init(true);
  homing();

  setVelocity(5000.0, 20000.0);

  steppers.addStepper(stepperA);
  steppers.addStepper(stepperB);
  steppers.addStepper(stepperC);

}

void DeltaRobot::run()
{
  if(!plan.isEmpty()){
    
    if(!plan.isBusy()){

      setVelocity(5000.0, 7000.0);
      //setVelocity(2000.0, 0.0);

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
      
      //steppers.moveTo(positions);
      stepperA.moveTo(positions[0]);
      stepperB.moveTo(positions[1]);
      stepperC.moveTo(positions[2]);
      

    }else{
			// Update arm positions while planner command is being executed
      arms[0].position = stepperA.currentPosition();
      arms[1].position = stepperB.currentPosition();
      arms[2].position = stepperC.currentPosition();
		}
    
    stepperA.run();
    stepperB.run();
    stepperC.run();
    
    // Run motors. Free up the planner if motors have finished, in order to take another command
    //if(!steppers.run()){
    if(!stepperA.isRunning() && !stepperB.isRunning() && !stepperC.isRunning()){
      plan.next();
    }

  }

  stepper_choreography();

}

/**
 * Calculates the number of steps it takes to get to an angle
 */
long DeltaRobot::angle2steps(float angle)
{
  return (long) round((angle / 360) * _stepsPerTurn * _gearRatio);
}

