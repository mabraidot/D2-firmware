#ifndef DEBUG_H
#define DEBUG_H

#include "Arduino.h"

class Debug {

  public:
    
    Debug() {};

    void print(String message, bool eol);


};

extern Debug debug;

#endif //DEBUG_H
