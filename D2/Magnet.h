#ifndef MAGNET_H
#define MAGNET_H

#include "Arduino.h"

class Magnet {

  public:
    
    Magnet() {};
    
    float safe_height = -338;//-325;
    float height = -348;//-347.5;
    
    typedef struct
    {
        bool    filled;
        float   x;
        float   y;
    } balls;
    balls ballsPlatform[3][11];

    void init();
    void move(int oGroup, int oId, int dGroup, int dId);
    
};

extern Magnet magnet;

#endif //MAGNET_H
