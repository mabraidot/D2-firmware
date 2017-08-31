#include "Planner.h";

Planner::Planner(void)
{

  typedef struct
  {
    bool busy;
    int XPosition;
    int YPosition;
		int ZPosition;
  } ringBuffer;

  ringBuffer bufferQueue[RING_BUFFER_SIZE];
  volatile unsigned char tail;
  volatile unsigned char head;
  volatile unsigned char count;
  
  init(true);
}

void Planner::init (const bool clearBuffer)
{
    if(clearBuffer){
      memset (bufferQueue, 0, sizeof (*bufferQueue));
    }
    tail = 0;
    head = 0;
    count = 0;
}

int Planner::isEmpty(void)
{
  return (0 == count);
}

int Planner::isFull(void)
{
  return (count >= RING_BUFFER_SIZE);
}

int Planner::isBusy()
{
	return bufferQueue[tail].busy;
}

void Planner::next(void)
{
  if(count > 0 && tail < head){
    bufferQueue[tail].busy = false;
    tail = modulo_inc(tail, RING_BUFFER_SIZE);
    --count;
  }
}

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

int Planner::getXPosition(void)
{
	if(count > 0 && tail < head && !bufferQueue[tail].busy){
		return bufferQueue[tail].XPosition;
	}else{
		return 0;
	}
}

int Planner::getYPosition(void)
{
	if(count > 0 && tail < head && !bufferQueue[tail].busy){
		return bufferQueue[tail].YPosition;
	}else{
		return 0;
	}
}

int Planner::getZPosition(void)
{
	if(count > 0 && tail < head && !bufferQueue[tail].busy){
		return bufferQueue[tail].ZPosition;
	}else{
		return 0;
	}
}

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

unsigned char Planner::modulo_inc(int operand, int modulo)
{
  operand++;
  if(operand < modulo){
    return operand;
  }else{
    return (operand % modulo);
  }
}

