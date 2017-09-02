/** RAMPS 1.4 PINOUT CONFIGURATION **/
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
//#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
//#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
//#define Z_MAX_PIN          19


/** ROBOT GEOMETRY  **/
#define DELTA_E             115.0  // end effector to wrist
#define DELTA_F             457.3  // base to shoulder
#define DELTA_RE            232.0  // forearm
#define DELTA_RF            112.0  // arm

/** GENERAL CONFIGURATIONS  **/
#define DEBUG              true
#define RING_BUFFER_SIZE   256
