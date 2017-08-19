#ifndef ENDSTOPS_H
#define ENDSTOPS_H

#include "Arduino.h"

class Endstops {

  public:

    static bool enabled, enabled_globally;
    static volatile char endstop_hit_bits; // use X_MIN, Y_MIN and Z_MIN as BIT value

    static byte current_endstop_bits, old_endstop_bits;

    Endstops() {};

    /**
     * Initialize the endstop pins
     */
    void init();

    /**
     * Update the endstops bits from the pins
     */
    static void update();

    /**
     * Print an error message reporting the position when the endstops were last hit.
     */
    static void report_state(); //call from somewhere to create an serial error message with the locations the endstops where hit, in case they were triggered

    // Enable / disable endstop checking globally
    static void enable_globally(bool onoff=true) { enabled_globally = enabled = onoff; }

    // Enable / disable endstop checking
    static void enable(bool onoff=true) { enabled = onoff; }

    // Disable / Enable endstops based on ENSTOPS_ONLY_FOR_HOMING and global enable
    static void not_homing() { enabled = enabled_globally; }

    // Clear endstops (i.e., they were hit intentionally) to suppress the report
    static void hit_on_purpose() { endstop_hit_bits = 0; }

};

extern Endstops endstops;

#define ENDSTOPS_ENABLED  endstops.enabled


#endif //ENDSTOPS_H
