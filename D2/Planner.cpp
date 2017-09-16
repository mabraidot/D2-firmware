#include "Configurations.h"
#include "Debug.h"
#include "Planner.h"
#include "Kinematics.h"

Planner plan;
Kinematics kinematics = Kinematics();

/*Planner::Planner(void)
{

  // Structure to store the intended movement position.
  typedef struct
  {
    bool    busy;
    float   XPosition;
    float   YPosition;
		float   ZPosition;
    float   getXTheta  (void);
    float   getYTheta  (void);
    float   getZTheta  (void);
  } ringBuffer;

  // Array of ringBuffer structures. Ring buffer design pattern.
  ringBuffer bufferQueue[RING_BUFFER_SIZE];
  volatile unsigned char tail;
  volatile unsigned char head;
  volatile unsigned char count;
  
  init(true);
}*/

/**
 * Initializes the buffer variables with zeros.
 */
void Planner::init (const bool clearBuffer)
{
    if(clearBuffer){
      memset (bufferQueue, 0.00, sizeof (*bufferQueue));
    }
    tail = 0;
    head = 0;
    count = 0;
}

/**
 * Checks whether is there are more movements or not.
 */
int Planner::isEmpty(void)
{
  return (0 == count);
}

/**
 * Checks if planner can store more movements or not.
 */
int Planner::isFull(void)
{
  return (count >= RING_BUFFER_SIZE);
}

/**
 * Is the tail movement being processed right now?.
 */
int Planner::isBusy()
{
	return bufferQueue[tail].busy;
}

/**
 * Moves the tail one step further, if there is more movements to step into.
 */
void Planner::next(void)
{
  if(count > 0){
    bufferQueue[tail].busy = false;
    tail = modulo_inc(tail, RING_BUFFER_SIZE);
    --count;
  }
}

/**
 * Returns a ringBuffer object with all set positions.
 */
Planner::ringBuffer Planner::get()
{
  ringBuffer c;
  //if(count > 0 && tail < head && !bufferQueue[tail].busy){
  if(count > 0){

    //bufferQueue[tail].busy = true;
    c = bufferQueue[tail];
    
  }else{
    c.XPosition = 0.00;
    c.YPosition = 0.00;
    c.ZPosition = 0.00;
    c.XTheta    = 0.00;
    c.YTheta    = 0.00;
    c.ZTheta    = 0.00;
    c.busy      = false;
  }
  return c;
}

/**
 * Return the intended X position.
 */
float Planner::getXPosition(void)
{
	if(count > 0){
		return bufferQueue[tail].XPosition;
	}else{
		return 0.00;
	}
}

/**
 * Return the intended Y position.
 */
float Planner::getYPosition(void)
{
	if(count > 0){
		return bufferQueue[tail].YPosition;
	}else{
		return 0.00;
	}
}

/**
 * Return the intended Z position.
 */
float Planner::getZPosition(void)
{
	if(count > 0){
		return bufferQueue[tail].ZPosition;
	}else{
		return 0.00;
	}
}

/**
 * Return the intended X theta angle.
 */
float Planner::getXTheta(void)
{
  if(count > 0){
    bufferQueue[tail].busy = true;
    return bufferQueue[tail].XTheta;
  }else{
    return 0.00;
  }
}

/**
 * Return the intended Y theta angle.
 */
float Planner::getYTheta(void)
{
  if(count > 0){
    bufferQueue[tail].busy = true;
    return bufferQueue[tail].YTheta;
  }else{
    return 0.00;
  }
}


/**
 * Return the intended Z theta angle.
 */
float Planner::getZTheta(void)
{
  if(count > 0){
    bufferQueue[tail].busy = true;
    return bufferQueue[tail].ZTheta;
  }else{
    return 0.00;
  }
}


/**
 * Stores a new movement into the buffer. Uses forward kinematics to calculate XYZ positions
 */
void Planner::putAngle(float XTheta, float YTheta, float ZTheta)
{
  kinematics.forwardKinematic(XTheta, YTheta, ZTheta);
  if(kinematics.status == 0){
    put(kinematics.x, kinematics.y, kinematics.z);
  }
}

/**
 * Stores a new movement into the buffer. Uses inverse kinematics to calculate angles
 */
void Planner::put(float XPosition, float YPosition, float ZPosition)
{
  if(count < RING_BUFFER_SIZE){
  
    kinematics.inverseKinematic(XPosition, YPosition, ZPosition);
    
    /*debug.println("");
    debug.println("Positions ----------------------------> ");
    debug.println((String)XPosition);
    debug.println((String)YPosition);
    debug.println((String)ZPosition);
    debug.println("IK Theta ----------------------------> ");
    debug.println((String)kinematics.theta1);
    debug.println((String)kinematics.theta2);
    debug.println((String)kinematics.theta3);
    */
    // If intended movement is possible
    if(kinematics.status == 0){
      
      bufferQueue[head].XPosition = XPosition;
      bufferQueue[head].YPosition = YPosition;
      bufferQueue[head].ZPosition = ZPosition;
      //bufferQueue[head].busy = (head == tail) ? true : false;
      bufferQueue[head].busy = false;
    
      bufferQueue[head].XTheta = kinematics.theta1;
      bufferQueue[head].YTheta = kinematics.theta2;
      bufferQueue[head].ZTheta = kinematics.theta3;

      head = modulo_inc(head, RING_BUFFER_SIZE);
      ++count;
    }
  }
}

/**
 * Helper function to increase a number by a given module.
 */
unsigned char Planner::modulo_inc(int operand, int modulo)
{
  operand++;
  if(operand < modulo){
    return operand;
  }else{
    return (operand % modulo);
  }
}

