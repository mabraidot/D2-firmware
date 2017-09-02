#ifndef KINEMATICS_H
#define KINEMATICS_H

#include "Arduino.h"

class Kinematics
{
  public:
    Kinematics(void);
  
    float x, y, z, theta1, theta2, theta3;
    char status;
    int forwardKinematic(float theta1, float theta2, float theta3);
    int inverseKinematic(float x0, float y0, float z0);
    
  private:
    const float _e, _f, _re, _rf;
    const float _sqrt3, _pi, _sin120, _cos120, _tan60, _sin30, _tan30;
    char _delta_calcAngleYZ(float x0, float y0, float z0, float &theta);
};

#endif //KINEMATICS_H
