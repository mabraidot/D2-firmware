#include "Arduino.h"
#include "Configurations.h"

class Planner
{
  public:
    typedef struct
    {
      bool busy;
      int XPosition;
      int YPosition;
			int ZPosition;
    } ringBuffer;
    
    Planner(void);

    void        init    (const bool clearBuffer);
    int         isEmpty (void);
    int         isFull  (void);
    ringBuffer  get     (void);
    void        next    (void);
    void        put     (int XPosition, int YPosition, int ZPosition);

  //private:
    ringBuffer bufferQueue[RING_BUFFER_SIZE];
    volatile unsigned char tail;
    volatile unsigned char head;
    volatile unsigned char count;
    unsigned char modulo_inc(int operand, int modulo);  
};


