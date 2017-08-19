
#ifndef _ENDSTOP_INTERRUPTS_H_
#define _ENDSTOP_INTERRUPTS_H_

volatile uint8_t e_hit = 0; // Different from 0 when the endstops should be tested in detail.
                            // Must be reset to 0 by the test function when finished.

// This is what is really done inside the interrupts.
inline void endstop_ISR_worker( void ) {
  e_hit = 2; // Because the detection of a e-stop hit has a 1 step debouncer it has to be called at least twice.
}

// Use one Routine to handle each group
// One ISR for all EXT-Interrupts
void endstop_ISR(void) { endstop_ISR_worker(); }

// Handlers for pin change interrupts
#ifdef PCINT0_vect
  ISR(PCINT0_vect) { endstop_ISR_worker(); }
#endif

#ifdef PCINT1_vect
  ISR(PCINT1_vect) { endstop_ISR_worker(); }
#endif

#ifdef PCINT2_vect
  ISR(PCINT2_vect) { endstop_ISR_worker(); }
#endif

#ifdef PCINT3_vect
  ISR(PCINT3_vect) { endstop_ISR_worker(); }
#endif


// Install Pin change interrupt for a pin, can be called multiple times
void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

void setup_endstop_interrupts( void ) {

  #if HAS_X_MAX
    pciSetup(X_MAX_PIN);
  #endif

  #if HAS_X_MIN
    pciSetup(X_MIN_PIN);
  #endif

  #if HAS_Y_MAX
    pciSetup(Y_MAX_PIN);
  #endif

  #if HAS_Y_MIN
    pciSetup(Y_MIN_PIN);
  #endif

  #if HAS_Z_MAX
    pciSetup(Z_MAX_PIN);
  #endif

  #if HAS_Z_MIN
    pciSetup(Z_MIN_PIN);
  #endif
  
}

#endif //_ENDSTOP_INTERRUPTS_H_
