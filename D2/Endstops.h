#ifndef ENDSTOPS_H
#define ENDSTOPS_H

#include "Arduino.h"

class Endstops {

  public:
    
    Endstops() {};

    /**
     * Initialize the endstop pins
     */
    void init();
    static void update();

};

extern Endstops endstops;

#endif //ENDSTOPS_H
