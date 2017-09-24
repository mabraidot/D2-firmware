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


void magnet_choreography(){

  plan.put(0, 0, -330);

  /* 000 */
  //plan.put(0, 0, -342);

  /* CCC */
  //r1
  //plan.put(-25, -11, -342);
  //plan.put(-25, 11, -342);
  //r2
  //plan.put(-50, -23, -342);
  //plan.put(-50, 0, -342);
  //plan.put(-50, 23, -342);
  //r3
  //plan.put(-75, -23, -342);
  //plan.put(-75, 0, -342);
  //plan.put(-75, 23, -342);

  /* CCC bis */
  //r3
  //plan.put(80, -23, -342);
  //plan.put(80, 0, -342);
  //plan.put(80, 23, -342);

  float safe_height = -310;
  
  plan.put(-50, -23, safe_height);
  plan.put(-50, -23, -340);
  plan.put(-50, -23, safe_height, 1, 1);
  plan.put(80, -23, safe_height);
  plan.put(80, -23, -336);
  plan.put(80, -23, safe_height, 1, 0);

  plan.put(-50, 0, safe_height);
  plan.put(-50, 0, -340);
  plan.put(-50, 0, safe_height, 1, 1);
  plan.put(80, 0, safe_height);
  plan.put(80, 0, -336);
  plan.put(80, 0, safe_height, 1, 0);

  plan.put(-50, 23, safe_height);
  plan.put(-50, 23, -340);
  plan.put(-50, 23, safe_height, 1, 1);
  plan.put(80, 23, safe_height);
  plan.put(80, 23, -336);
  plan.put(80, 23, safe_height, 1, 0);
  

  ////////////////////
  plan.put(-75, -23, safe_height);
  plan.put(-75, -23, -338);
  plan.put(-75, -23, safe_height, 1, 1);
  plan.put(-50, -23, safe_height);
  plan.put(-50, -23, -340);
  plan.put(-50, -23, safe_height, 1, 0);

  plan.put(-75, 0, safe_height);
  plan.put(-75, 0, -338);
  plan.put(-75, 0, safe_height, 1, 1);
  plan.put(-50, 0, safe_height);
  plan.put(-50, 0, -340);
  plan.put(-50, 0, safe_height, 1, 0);

  plan.put(-75, 23, safe_height);
  plan.put(-75, 23, -338);
  plan.put(-75, 23, safe_height, 1, 1);
  plan.put(-50, 23, safe_height);
  plan.put(-50, 23, -340);
  plan.put(-50, 23, safe_height, 1, 0);

  ////////////////////
  plan.put(80, -23, safe_height);
  plan.put(80, -23, -336);
  plan.put(80, -23, safe_height, 1, 1);
  plan.put(-75, -23, safe_height);
  plan.put(-75, -23, -338);
  plan.put(-75, -23, safe_height, 1, 0);

  plan.put(80, 0, safe_height);
  plan.put(80, 0, -337);
  plan.put(80, 0, safe_height, 1, 1);
  plan.put(-75, 0, safe_height);
  plan.put(-75, 0, -338);
  plan.put(-75, 0, safe_height, 1, 0);

  plan.put(80, 23, safe_height);
  plan.put(80, 23, -337);
  plan.put(80, 23, safe_height, 1, 1);
  plan.put(-75, 23, safe_height);
  plan.put(-75, 23, -338);
  plan.put(-75, 23, safe_height, 1, 0);


  plan.put(0, 0, -330);

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
