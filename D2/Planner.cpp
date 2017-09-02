#include "Planner.h";

Planner::Planner(void)
{

  // Structure to store the intended movement position.
  typedef struct
  {
    bool busy;
    int XPosition;
    int YPosition;
		int ZPosition;
  } ringBuffer;

  // Array of ringBuffer structures. Ring buffer design pattern.
  ringBuffer bufferQueue[RING_BUFFER_SIZE];
  volatile unsigned char tail;
  volatile unsigned char head;
  volatile unsigned char count;
  
  init(true);
}

/**
 * Initializes the buffer variables with zeros.
 */
void Planner::init (const bool clearBuffer)
{
    if(clearBuffer){
      memset (bufferQueue, 0, sizeof (*bufferQueue));
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
  if(count > 0 && tail < head){
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
  if(count > 0 && tail < head && !bufferQueue[tail].busy){

    bufferQueue[tail].busy = true;
    c = bufferQueue[tail];
    
  }else{
    c.XPosition = 0;
    c.YPosition = 0;
    c.ZPosition = 0;
    c.busy = false;
  }
  return c;
}

/**
 * Return the intended X position.
 */
int Planner::getXPosition(void)
{
	if(count > 0 && tail < head && !bufferQueue[tail].busy){
		return bufferQueue[tail].XPosition;
	}else{
		return 0;
	}
}

/**
 * Return the intended Y position.
 */
int Planner::getYPosition(void)
{
	if(count > 0 && tail < head && !bufferQueue[tail].busy){
		return bufferQueue[tail].YPosition;
	}else{
		return 0;
	}
}

/**
 * Return the intended Z position.
 */
int Planner::getZPosition(void)
{
	if(count > 0 && tail < head && !bufferQueue[tail].busy){
		return bufferQueue[tail].ZPosition;
	}else{
		return 0;
	}
}

/**
 * Stores a new movement into the buffer.
 */
void Planner::put(int XPosition, int YPosition, int ZPosition)
{
  if(count < RING_BUFFER_SIZE){
    bufferQueue[head].XPosition = XPosition;
    bufferQueue[head].YPosition = YPosition;
    bufferQueue[head].ZPosition = ZPosition;
    bufferQueue[head].busy = false;
    
    head = modulo_inc(head, RING_BUFFER_SIZE);
    ++count;
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

