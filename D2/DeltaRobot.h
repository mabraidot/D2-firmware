#ifndef DELTAROBOT_H
#define DELTAROBOT_H

#include "Arduino.h"

class DeltaRobot {

  public:
    DeltaRobot(){};
    typedef struct 
    {
      float position;
      byte homed;
    } arm;
    
    void init(void);
    void run(void);

    // delete. testing only
    void stepper_rotate(int deg);
    void stepper_choreography(int mode);
    

  private:
    arm arms[3];
    
};

extern DeltaRobot delta;

#endif; //DELTAROBOT_H
