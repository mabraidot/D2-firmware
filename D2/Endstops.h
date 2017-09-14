#ifndef ENDSTOPS_H
#define ENDSTOPS_H

#include "Arduino.h"

class Endstops {

  public:
    
    Endstops() {};
    boolean a_hitten(void);
    boolean b_hitten(void);
    boolean c_hitten(void);
    /**
     * Initialize the endstop pins
     */
    void init();
    void update();
  private:
    boolean hit_A, hit_B, hit_C;
    
};

extern Endstops endstops;

#endif //ENDSTOPS_H
