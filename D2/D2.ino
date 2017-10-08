#include "Arduino.h"
#include "Configurations.h"
#include "Debug.h"
#include "DeltaRobot.h"
#include "Planner.h"



void setup() {
  Serial.begin(250000);
  delta.init();
}

void loop() {
  if (Serial.available()) process_serial();
  delta.run();
  
  /*
  static int serial_interval = 1000;
  static unsigned long serial_timeout = millis() + serial_interval;
  if(serial_timeout < millis()){

    //Serial.println("Empty------------------------------->");
    //Serial.println(plan.isEmpty());
    //Serial.println("Busy------------------------------->");
    //Serial.println(plan.isBusy());
    
    serial_timeout = millis() + serial_interval;
  }*/
  
}


void pen_choreography(){
  plan.put(0, 0, -300);

  plan.put(-40, 0, -318);
  plan.put(-40, 40, -318);
  plan.put(40, 40, -318);
  plan.put(40, -40, -318);
  plan.put(-40, -40, -318);
  plan.put(-40, 0, -318);

  plan.put(0, 0, -300);
}


void magnet_choreography(){

  
  float rads = 3.1415/180.0;
  float angle = 0.0;
  float cos60 = cos(rads*60.0);
  float sin60 = sin(rads*60.0);
  float cos180 = cos(rads*180.0);
  float sin180 = sin(rads*180.0);
  float cos300 = cos(rads*300.0);
  float sin300 = sin(rads*300.0);
  float x = 0.0;
  float y = 0.0;

  float safe_height = -325;
  float height = -346;
  
  plan.put(0, 0, safe_height);

  
  /*for(int i = 0; i<3; i++){
    angle = rads * ((120*i) + 60);

    //r1
    x = 20 * cos(angle)      + -8 * sin(angle);
    y = 20 * -1*sin(angle)   + -8 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = 20 * cos(angle)      + 8 * sin(angle);
    y = 20 * -1*sin(angle)   + 8 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);

    //r2
    x = 40 * cos(angle)      + -17 * sin(angle);
    y = 40 * -1*sin(angle)   + -17 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = 40 * cos(angle)      + 0 * sin(angle);
    y = 40 * -1*sin(angle)   + 0 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = 40 * cos(angle)      + 17 * sin(angle);
    y = 40 * -1*sin(angle)   + 17 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);

    //r3
    x = 60 * cos(angle)      + -17 * sin(angle);
    y = 60 * -1*sin(angle)   + -17 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = 60 * cos(angle)      + 0 * sin(angle);
    y = 60 * -1*sin(angle)   + 0 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = 60 * cos(angle)      + 17 * sin(angle);
    y = 60 * -1*sin(angle)   + 17 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);

    // bis 
    //r3
    x = -60 * cos(angle)      + -17 * sin(angle);
    y = -60 * -1*sin(angle)   + -17 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = -60 * cos(angle)      + 0 * sin(angle);
    y = -60 * -1*sin(angle)   + 0 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
    x = -60 * cos(angle)      + 17 * sin(angle);
    y = -60 * -1*sin(angle)   + 17 * cos(angle);
    plan.put(x, y, safe_height);
    plan.put(x, y, height);
  }*/

  

  
  plan.put(-40, -17, safe_height);
  plan.put(-40, -17, height);
  plan.put(-40, -17, safe_height, 1, 1);
  plan.put(60, -17, safe_height);
  plan.put(60, -17, height);
  plan.put(60, -17, safe_height, 1, 0);

  plan.put(-40, 0, safe_height);
  plan.put(-40, 0, height);
  plan.put(-40, 0, safe_height, 1, 1);
  plan.put(60, 0, safe_height);
  plan.put(60, 0, height);
  plan.put(60, 0, safe_height, 1, 0);

  plan.put(-40, 17, safe_height);
  plan.put(-40, 17, height);
  plan.put(-40, 17, safe_height, 1, 1);
  plan.put(60, 17, safe_height);
  plan.put(60, 17, height);
  plan.put(60, 17, safe_height, 1, 0);
  

  ////////////////////
  plan.put(-60, -17, safe_height);
  plan.put(-60, -17, height);
  plan.put(-60, -17, safe_height, 1, 1);
  plan.put(-40, -17, safe_height);
  plan.put(-40, -17, height);
  plan.put(-40, -17, safe_height, 1, 0);

  plan.put(-60, 0, safe_height);
  plan.put(-60, 0, height);
  plan.put(-60, 0, safe_height, 1, 1);
  plan.put(-40, 0, safe_height);
  plan.put(-40, 0, height);
  plan.put(-40, 0, safe_height, 1, 0);

  plan.put(-60, 17, safe_height);
  plan.put(-60, 17, height);
  plan.put(-60, 17, safe_height, 1, 1);
  plan.put(-40, 17, safe_height);
  plan.put(-40, 17, height);
  plan.put(-40, 17, safe_height, 1, 0);

  ////////////////////
  plan.put(60, -17, safe_height);
  plan.put(60, -17, height);
  plan.put(60, -17, safe_height, 1, 1);
  plan.put(-60, -17, safe_height);
  plan.put(-60, -17, height);
  plan.put(-60, -17, safe_height, 1, 0);

  plan.put(60, 0, safe_height);
  plan.put(60, 0, height);
  plan.put(60, 0, safe_height, 1, 1);
  plan.put(-60, 0, safe_height);
  plan.put(-60, 0, height);
  plan.put(-60, 0, safe_height, 1, 0);

  plan.put(60, 17, safe_height);
  plan.put(60, 17, height);
  plan.put(60, 17, safe_height, 1, 1);
  plan.put(-60, 17, safe_height);
  plan.put(-60, 17, height);
  plan.put(-60, 17, safe_height, 1, 0);
  

  plan.put(0, 0, safe_height);

}


void process_serial(){
  char cmd = Serial.read();
  if (cmd > 'Z') cmd -= 32;
  switch (cmd) {
    case '?': help(); break;
    case 'H': delta.homing(); break;
    case 'C': delta.add_choreography(1); break;
    case 'P': delta.add_choreography(2); break;
    case 'S': delta.add_choreography(3); break;
    case 'M': magnet_choreography(); break;
    case 'B': pen_choreography(); break;
    
    case 'K': 
      float pos1 = Serial.parseFloat(); 
      float pos2 = Serial.parseFloat(); 
      float pos3 = Serial.parseFloat(); 
      int pos4 = Serial.parseInt(); 
      if(pos4){
        int pos5 = Serial.parseInt(); 
        plan.put(pos1, pos2, pos3, true, pos5);
      }else{
        plan.put(pos1, pos2, pos3); 
      }
      break;
    
  }
  
  while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
  
}

void help() {
  Serial.println(F("\nStepper motor interface emulator"));
  Serial.println(F("Available serial commands: (lines end with CRLF or LF)"));
  Serial.println(F(""));
  Serial.println(F("?: will print this help message again"));
  Serial.println(F("H: perform a homing action"));
  Serial.println(F("C: Little choreography"));
  Serial.println(F("P: P&P choreography"));
  Serial.println(F("S: Sigmoid choreography"));
  Serial.println(F("K1,2,-3: Inverse Kinematics (X,Y,Z) -> (1,2,-3)"));
}
