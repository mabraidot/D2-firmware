#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "Arduino.h"
#include "Configurations.h"

class Kinematics
{
  public:
    Kinematics(void);
  
    float x, y, z, theta1, theta2, theta3;
    int status;
    int forwardKinematic(float theta1, float theta2, float theta3);
    int inverseKinematic(float x0, float y0, float z0);
    
  private:
    int _delta_calcAngleYZ(float x0, float y0, float z0, float &theta);

    /* Delta Robot geometry */
    const float _e       = DELTA_E;  // end effector to wrist
    const float _f       = DELTA_F;  // base to shoulder
    const float _re      = DELTA_RE; // forearm
    const float _rf      = DELTA_RF; // arm

    /* Trigonometric constants */
    const float _sqrt3   = sqrt(3.0);
    const float _pi      = 3.141592653;
    const float _sin120  = _sqrt3/2.0;   
    const float _cos120  = -0.5;        
    const float _tan60   = _sqrt3;
    const float _sin30   = 0.5;
    const float _tan30   = 1/_sqrt3;
};

#endif //KINEMATICS_H
