#ifndef DELTAROBOT_H
#define DELTAROBOT_H

#include "Arduino.h"

class DeltaRobot {

  public:
    DeltaRobot(){};
    typedef struct 
    {
      long position;
      byte homed;
    } arm;
    
    void homing(void);
    void init(void);
    void run(void);
		long angle2steps(float angle);

    // delete. testing only
    void stepper_choreography(int mode);
    

  private:
    arm arms[3];
		float _gearRatio = DELTA_GEAR_RATIO;
		float _stepsPerTurn = 400 * MICROSTEPS; //(360/0.9)*microstepping
    
};

extern DeltaRobot delta;

#endif //DELTAROBOT_H
