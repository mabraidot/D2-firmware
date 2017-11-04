/**
 * A singleton object to manage magnet choreography
 */

#include "Configurations.h"
#include "Debug.h"
#include "Magnet.h"
#include "Planner.h"

Magnet magnet;


// public:
void Magnet::init() {
    
    /****************
    
    8 9 10

     0 1
    2 3 4
    5 6 7

    ****************/

    float rads = 3.1415/180.0;
    float angle = 0.0;
    
    for(int i = 0; i<3; i++){
        angle = rads * ((120*i) + 60);

        //r1
        ballsPlatform[i][0].x = 20 * cos(angle)      + -8 * sin(angle);
        ballsPlatform[i][0].y = 20 * -1*sin(angle)   + -8 * cos(angle);
        ballsPlatform[i][0].filled = 0;
        
        ballsPlatform[i][1].x = 20 * cos(angle)      + 8 * sin(angle);
        ballsPlatform[i][1].y = 20 * -1*sin(angle)   + 8 * cos(angle);
        ballsPlatform[i][1].filled = 0;

        //r2
        ballsPlatform[i][2].x = 40 * cos(angle)      + -17 * sin(angle);
        ballsPlatform[i][2].y = 40 * -1*sin(angle)   + -17 * cos(angle);
        ballsPlatform[i][2].filled = 1;

        ballsPlatform[i][3].x = 40 * cos(angle)      + 0 * sin(angle);
        ballsPlatform[i][3].y = 40 * -1*sin(angle)   + 0 * cos(angle);
        ballsPlatform[i][3].filled = 1;

        ballsPlatform[i][4].x = 40 * cos(angle)      + 17 * sin(angle);
        ballsPlatform[i][4].y = 40 * -1*sin(angle)   + 17 * cos(angle);
        ballsPlatform[i][4].filled = 1;

        //r3
        ballsPlatform[i][5].x = 60 * cos(angle)      + -17 * sin(angle);
        ballsPlatform[i][5].y = 60 * -1*sin(angle)   + -17 * cos(angle);
        ballsPlatform[i][5].filled = 1;

        ballsPlatform[i][6].x = 60 * cos(angle)      + 0 * sin(angle);
        ballsPlatform[i][6].y = 60 * -1*sin(angle)   + 0 * cos(angle);
        ballsPlatform[i][6].filled = 1;

        ballsPlatform[i][7].x = 60 * cos(angle)      + 17 * sin(angle);
        ballsPlatform[i][7].y = 60 * -1*sin(angle)   + 17 * cos(angle);
        ballsPlatform[i][7].filled = 1;

        // bis 
        ballsPlatform[i][8].x = -60 * cos(angle)      + -17 * sin(angle);
        ballsPlatform[i][8].y = -60 * -1*sin(angle)   + -17 * cos(angle);
        ballsPlatform[i][8].filled = 0;

        ballsPlatform[i][9].x = -60 * cos(angle)      + 0 * sin(angle);
        ballsPlatform[i][9].y = -60 * -1*sin(angle)   + 0 * cos(angle);
        ballsPlatform[i][9].filled = 0;

        ballsPlatform[i][10].x = -60 * cos(angle)      + 17 * sin(angle);
        ballsPlatform[i][10].y = -60 * -1*sin(angle)   + 17 * cos(angle);
        ballsPlatform[i][10].filled = 0;
    }
  
} // Magnet::init

void Magnet::move(int oGroup, int oId, int dGroup, int dId){

    if(ballsPlatform[oGroup][oId].filled && !ballsPlatform[dGroup][dId].filled){
        
        plan.put(ballsPlatform[oGroup][oId].x, ballsPlatform[oGroup][oId].y, safe_height);
        plan.put(ballsPlatform[oGroup][oId].x, ballsPlatform[oGroup][oId].y, height);
        plan.put(ballsPlatform[oGroup][oId].x, ballsPlatform[oGroup][oId].y, safe_height, 1, 1);
        ballsPlatform[oGroup][oId].filled = 0;

        plan.put(ballsPlatform[dGroup][dId].x, ballsPlatform[dGroup][dId].y, safe_height);
        plan.put(ballsPlatform[dGroup][dId].x, ballsPlatform[dGroup][dId].y, height);
        plan.put(ballsPlatform[dGroup][dId].x, ballsPlatform[dGroup][dId].y, safe_height, 1, 0);
        ballsPlatform[dGroup][dId].filled = 1;

    }else{
        
        if(!ballsPlatform[oGroup][oId].filled){
            debug.println(F("La posición de origen no tiene una bola"));
            debug.println(String(oGroup) + " - " + String(oId));
        }else if(ballsPlatform[dGroup][dId].filled){
            debug.println(F("La posición de destino no está libre."));
            debug.println(String(dGroup) + " - " + String(dId));
        }
    }

}