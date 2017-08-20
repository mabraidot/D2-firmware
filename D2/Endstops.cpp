/**
 * A singleton object to manage endstops
 */

#include "Configurations.h"
#include "Endstops.h"

Endstops endstops;

// public:


/**
 * Class and Instance Methods
 */
void Endstops::init() {

  pinMode(X_MIN_PIN, INPUT);
  digitalWrite(X_MIN_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(X_MIN_PIN), Endstops::update, CHANGE);

  pinMode(Y_MIN_PIN, INPUT);
  digitalWrite(Y_MIN_PIN, HIGH);
  attachInterrupt(digitalPinToPCICR(Y_MIN_PIN), Endstops::update, CHANGE);
  
  pinMode(Z_MIN_PIN, INPUT);
  digitalWrite(Z_MIN_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(Z_MIN_PIN), Endstops::update, CHANGE);
  
} // Endstops::init

/**
 * Update the endstops bits from the pins
 */
void Endstops::update(void) {

  
  
}

