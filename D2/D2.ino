#include "Arduino.h"
#include "Configurations.h"
#include "Debug.h"
#include "DeltaRobot.h"
#include "Planner.h"
#include "Magnet.h"

void setup() {
  Serial.begin(250000);
  delta.init();
  magnet.init();
}

void loop() {
  if (Serial.available()) process_serial();
  delta.run();
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

  /****************
  
  8 9 10

   0 1
  2 3 4
  5 6 7

  ****************/
  plan.put(0, 0, -300);


  magnet.move(0, 8, 1, 4);
  magnet.move(0, 9, 1, 3);
  magnet.move(0, 10, 1, 2);

  magnet.move(1, 8, 2, 4);
  magnet.move(1, 9, 2, 3);
  magnet.move(1, 10, 2, 2);
  
  magnet.move(2, 8, 0, 4);
  magnet.move(2, 9, 0, 3);
  magnet.move(2, 10, 0, 2);

  ///////////////////
  magnet.move(0, 2, 0, 8);
  magnet.move(0, 3, 0, 9);
  magnet.move(0, 4, 0, 10);

  magnet.move(0, 5, 0, 2);
  magnet.move(0, 6, 0, 3);
  magnet.move(0, 7, 0, 4);

  magnet.move(0, 8, 0, 5);
  magnet.move(0, 9, 0, 6);
  magnet.move(0, 10, 0, 7);

  ///////////////////
  magnet.move(1, 2, 0, 10);
  magnet.move(1, 3, 0, 9);
  magnet.move(1, 4, 0, 8);

  magnet.move(2, 2, 1, 10);
  magnet.move(2, 3, 1, 9);
  magnet.move(2, 4, 1, 8);

  magnet.move(0, 2, 2, 10);
  magnet.move(0, 3, 2, 9);
  magnet.move(0, 4, 2, 8);


  plan.put(0, 0, -300);


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
    //case 'B': pen_choreography(); break;
    
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
  Serial.println(F("\nInterfaz Delta Robot"));
  Serial.println(F("Comandos disponibles:"));
  Serial.println(F(""));
  Serial.println(F("?: Esta ayuda"));
  Serial.println(F("H: Realizar una acción de home en cada brazo"));
  Serial.println(F("C: Coreografía de círculo"));
  Serial.println(F("P: Coreografía de Pick and Place"));
  Serial.println(F("S: Coreografía Sigmoide"));
  Serial.println(F("M: Coreografía Magneto"));
  Serial.println(F("K1,2,-3,4,5: Cinemática inversa (X,Y,Z) -> (1,2,-3)"));
  Serial.println(F("             4:(0|1) Seleccionar imán"));
  Serial.println(F("             5:(0|1) Encender / Apagar imán"));
}
