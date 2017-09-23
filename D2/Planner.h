#include "Arduino.h"
#include "Configurations.h"

class Planner
{
  public:
    typedef struct
    {
      bool    busy;
      float   XPosition;
      float   YPosition;
      float   ZPosition;
      float   XTheta;
      float   YTheta;
      float   ZTheta;
    } ringBuffer;
    
    Planner(){};

    void        init    (const bool clearBuffer);
		int         isBusy	(void);    
		int         isEmpty (void);
    int         isFull  (void);
    int         getToolState  (void);
    void        setToolState  (const bool state);
    float       getXPosition  (void);
    float       getYPosition  (void);
    float       getZPosition  (void);
    float       getXTheta  (void);
    float       getYTheta  (void);
    float       getZTheta  (void);
    ringBuffer  get     (void);
    void        next    (void);
    boolean     put     (float XPosition, float YPosition, float ZPosition);
    boolean     put     (float XPosition, float YPosition, float ZPosition, const bool setTool, const bool toolState);
    boolean     putAngle(float XTheta, float YTheta, float ZTheta);
    boolean     putAngle(float XTheta, float YTheta, float ZTheta, const bool setTool, const bool toolState);
    ringBuffer  bufferQueue[RING_BUFFER_SIZE];
    
  private:
    volatile bool tool;
    volatile unsigned char tail;
    volatile unsigned char head;
    volatile unsigned char count;
    unsigned char modulo_inc(int operand, int modulo);  
};

extern Planner plan;
