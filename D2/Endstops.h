#ifndef ENDSTOPS_H
#define ENDSTOPS_H

#include "Arduino.h"

class Endstops {

  public:
    
    Endstops() {};
    boolean is_A_hit(void);
    boolean is_B_hit(void);
    boolean is_C_hit(void);
    /**
     * Initialize the endstop pins
     */
    void init();
    void update();
  private:
    boolean _hit_A, _hit_B, _hit_C;
    
};

extern Endstops endstops;

#endif //ENDSTOPS_H
