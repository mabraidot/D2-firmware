/**
 * A singleton object to manage endstops
 */

#include "Endstops.h"

// TEST_ENDSTOP: test the old and the current status of an endstop
#define TEST_ENDSTOP(ENDSTOP) (TEST(current_endstop_bits & old_endstop_bits, ENDSTOP))

Endstops endstops;

// public:

bool  Endstops::enabled = true,
      Endstops::enabled_globally = false;
      
volatile char Endstops::endstop_hit_bits; // use X_MIN, Y_MIN and Z_MIN as BIT value

byte Endstops::current_endstop_bits = 0,
     Endstops::old_endstop_bits = 0;


/**
 * Class and Instance Methods
 */
void Endstops::init() {

  #if HAS_X_MIN
    pinMode(X_MIN_PIN, INPUT);
  #endif

  #if HAS_Y_MIN
    pinMode(Y_MIN_PIN, INPUT);
  #endif

  #if HAS_Z_MIN
    pinMode(Z_MIN_PIN, INPUT);
  #endif

  #if HAS_X_MAX
    pinMode(X_MAX_PIN, INPUT);
  #endif

  #if HAS_Y_MAX
    pinMode(Y_MAX_PIN, INPUT);
  #endif

  #if HAS_Z_MAX
    pinMode(Z_MAX_PIN, INPUT);
  #endif

} // Endstops::init
