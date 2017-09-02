#include "Kinematics.h";

#include "Configurations.h"
#include "Debug.h"

Kinematics::Kinematics(void)
{
  // private:
  
  /* Robot geometry */
  const float _e       = 115.0;  // end effector to wrist
  const float _f       = 457.3;  // base to shoulder
  const float _re      = 232.0;  // forearm
  const float _rf      = 112.0;  // arm

  /* Trigonometric constants */
  const float _sqrt3   = sqrt(3.0);
  const float _pi      = 3.141592653;
  const float _sin120  = _sqrt3/2.0;   
  const float _cos120  = -0.5;        
  const float _tan60   = _sqrt3;
  const float _sin30   = 0.5;
  const float _tan30   = 1/_sqrt3;

  // public:
  char status          = -1;
  float x              = 0;
  float y              = 0;
  float z              = 0;
  float theta1         = 0;
  float theta2         = 0;
  float theta3         = 0;
  
}



/**
 * Forward kinematics.
 * Receives theta1, theta2 and theta3; sets x, y and z.
 * Returns status: 0 = OK, -1 = non-existing position.
 */
int Kinematics::forwardKinematic(float theta1, float theta2, float theta3)
{
  float t = (_f-_e)*_tan30/2;
  float dtr = _pi/(float)180.0;
  
  theta1 *= dtr;
  theta2 *= dtr;
  theta3 *= dtr;
  
  float y1 = -(t + _rf*cos(theta1));
  float z1 = -_rf*sin(theta1);
  
  float y2 = (t + _rf*cos(theta2))*_sin30;
  float x2 = y2*_tan60;
  float z2 = -_rf*sin(theta2);
  
  float y3 = (t + _rf*cos(theta3))*_sin30;
  float x3 = -y3*_tan60;
  float z3 = -_rf*sin(theta3);
  
  float dnm = (y2-y1)*x3-(y3-y1)*x2;
  
  float w1 = y1*y1 + z1*z1;
  float w2 = x2*x2 + y2*y2 + z2*z2;
  float w3 = x3*x3 + y3*y3 + z3*z3;
  
  // x = (a1*z + b1)/dnm
  float a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
  float b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;
  
  // y = (a2*z + b2)/dnm;
  float a2 = -(z2-z1)*x3+(z3-z1)*x2;
  float b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;
  
  // a*z^2 + b*z + c = 0
  float a = a1*a1 + a2*a2 + dnm*dnm;
  float b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
  float c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - _re*_re);
  
  // discriminant
  float d = b*b - (float)4.0*a*c;
  if (d < 0) return -1; // non-existing point
  
  z = -(float)0.5*(b+sqrt(d))/a;
  x = (a1*z + b1)/dnm;
  y = (a2*z + b2)/dnm;
  return 0;
}



/**
 * Inverse kinematics.
 * Helper function, calculates angle theta (for YZ-pane).
 * Returns status: 0 = OK, -1 = non-existing position.
 */
char Kinematics::_delta_calcAngleYZ(float x0, float y0, float z0, float &theta)
{
  float y1 = -0.5 * 0.57735 * _f;  // f/2 * tg 30
  y0 -= 0.5 * 0.57735 * _e;        // shift center to edge
  
  // z = a + b*y
  float a = (x0*x0 + y0*y0 + z0*z0 +_rf*_rf - _re*_re - y1*y1)/(2*z0);
  float b = (y1-y0)/z0;
  
  // discriminant
  float d = -(a+b*y1)*(a+b*y1)+_rf*(b*b*_rf+_rf); 
  if (d < 0) return -1;           // non-existing point
  
  float yj = (y1 - a*b - sqrt(d))/(b*b + 1); // choosing outer point
  float zj = a + b*yj;
  theta = 180.0*atan(-zj/(y1 - yj))/_pi + ((yj>y1)?180.0:0.0);
  
  return 0;
}


/**
 * Inverse kinematics.
 * Receives x, y, z; sets theta1, theta2 and theta3;
 * Returns status: 0 = OK, -1 = non-existing position.
 */
int Kinematics::inverseKinematic(float x0, float y0, float z0)
{
  theta1 = theta2 = theta3 = 0;
  int status = _delta_calcAngleYZ(x0, y0, z0, theta1);
  if (status == 0) status = _delta_calcAngleYZ(x0*_cos120 + y0*_sin120, y0*_cos120-x0*_sin120, z0, theta2);  // rotate coords to +120 deg
  if (status == 0) status = _delta_calcAngleYZ(x0*_cos120 - y0*_sin120, y0*_cos120+x0*_sin120, z0, theta3);  // rotate coords to -120 deg
  
  return status;
}

