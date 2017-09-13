#ifndef ENDSTOPS_H
#define ENDSTOPS_H

#include "Arduino.h"

class Endstops {

  public:
    
    Endstops() {};
    boolean hit_A, hit_B, hit_C;
    /**
     * Initialize the endstop pins
     */
    void init();
    static void update();

};

extern Endstops endstops;

#endif //ENDSTOPS_H
