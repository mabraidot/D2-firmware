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


  private:

    static byte _A_Hit, _B_Hit, _C_Hit;

};

extern Endstops endstops;

#endif //ENDSTOPS_H
