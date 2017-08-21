/**
 * A singleton object to manage endstops
 */

#include "Configurations.h"
#include "Debug.h"
#include "Endstops.h"
#include <TimerOne.h>

// Timer1 interrupt
void endstops_interrupt(void){
  endstops.update();
}



Endstops endstops;


// public:
/**
 * Class and Instance Methods
 */
void Endstops::init() {

  Timer1.initialize(50);
  Timer1.attachInterrupt( endstops_interrupt );
  
  pinMode(X_MIN_PIN, INPUT);
  digitalWrite(X_MIN_PIN, HIGH);

  pinMode(Y_MIN_PIN, INPUT);
  digitalWrite(Y_MIN_PIN, HIGH);
  
  pinMode(Z_MIN_PIN, INPUT);
  digitalWrite(Z_MIN_PIN, HIGH);
  
} // Endstops::init

/**
 * Update the endstops bits from the pins
 */
void Endstops::update(void) {
  
  static uint16_t stateA = 0; // current debounce status
  stateA = (stateA << 1) | !digitalRead(X_MIN_PIN) | 0xe000;
  if(stateA == 0xf000){
    _A_Hit = 1;   // endstop has hit
    debug.print("Endstop A has hit.", 1);
    
  }

  static uint16_t stateB = 0; // current debounce status
  stateB = (stateB << 1) | !digitalRead(Y_MIN_PIN) | 0xe000;
  if(stateB == 0xf000){
    _B_Hit = 1;   // endstop has hit
    debug.print("Endstop B has hit.", 1);
  }

  static uint16_t stateC = 0; // current debounce status
  stateC = (stateC << 1) | !digitalRead(Z_MIN_PIN) | 0xe000;
  if(stateC == 0xf000){
    _C_Hit = 1;   // endstop has hit
    debug.print("Endstop C has hit.", 1);
  }
}






// private:
static byte Endstops::_A_Hit = 0,
            Endstops::_B_Hit = 0,
            Endstops::_C_Hit = 0;



