#ifndef ENDSTOPS_H
#define ENDSTOPS_H

#include "Arduino.h"


/**
 * Patch for pins_arduino.h (...\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h)
 *
 * These macros for the Arduino MEGA do not include the two connected pins on Port J (D13, D14).
 * So we extend them here because these are the normal pins for Y_MIN and Y_MAX on RAMPS.
 * There are more PCI-enabled processor pins on Port J, but they are not connected to Arduino MEGA.
 */

#if defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_MEGA)
    #undef  digitalPinToPCICR
    #define digitalPinToPCICR(p)    ( ((p) >= 10 && (p) <= 15) || \
                                      ((p) >= 50 && (p) <= 53) || \
                                      ((p) >= 62 && (p) <= 69) ? &PCICR : (uint8_t *)0)
#endif

								
								
								
class Endstops {

  public:

    Endstops() {};

    /**
     * Initialize the endstop pins
     */
    void init();
    static void update();

};

extern Endstops endstops;

#endif //ENDSTOPS_H
