/**
 * A singleton object to manage endstops
 */

#include "Configurations.h"
#include "Debug.h"
#include "Endstops.h"
#include <TimerOne.h>

Endstops endstops;

// Timer1 interrupt
void endstops_interrupt(void){
  endstops.update();
}




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

boolean Endstops::a_hitten(void){
  boolean temp = hit_A;
  hit_A = false;
  return temp;
}
boolean Endstops::b_hitten(void){
  boolean temp = hit_B;
  hit_B = false;
  return temp;
}
boolean Endstops::c_hitten(void){
  boolean temp = hit_C;
  hit_C = false;
  return temp;
}

/**
 * Update the endstops bits from the pins.
 * This function is called from the timer interrupt.
 */
void Endstops::update(void) {

  static uint16_t stateA = 0; // current debounce status
  stateA = (stateA << 1) | !digitalRead(X_MIN_PIN) | 0xe000;
  if(stateA == 0xf000){
    hit_A = true;
    debug.println("Endstop A has hit.");
  }

  static uint16_t stateB = 0; // current debounce status
  stateB = (stateB << 1) | !digitalRead(Y_MIN_PIN) | 0xe000;
  if(stateB == 0xf000){
    hit_B = true;
    debug.println("Endstop B has hit.");
  }

  static uint16_t stateC = 0; // current debounce status
  stateC = (stateC << 1) | !digitalRead(Z_MIN_PIN) | 0xe000;
  if(stateC == 0xf000){
    hit_C = true;
    debug.println("Endstop C has hit.");
  }
}
