#ifndef DELTAROBOT_H
#define DELTAROBOT_H

#include "Arduino.h"

class DeltaRobot {

  public:
    DeltaRobot() {};
    void init(void);
    void run(void);
    
    typedef struct 
    {
      float position;
      byte homed;
    } arm;

  private:
    arm arms[3];
    
};

extern DeltaRobot delta;

#endif; //DELTAROBOT_H
