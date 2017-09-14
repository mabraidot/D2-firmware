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

#define MICROSTEPS   			 2	//1, 2, 8, 16

/** ROBOT GEOMETRY  **/
#define DELTA_E                 33.00  // end effector to wrist radius
#define DELTA_F                 70.00  // base to shoulder radius
#define DELTA_RE                331.30 // forearm length
#define DELTA_RF                121.20  // arm length
#define DELTA_GEAR_RATIO        6.82    // 150 theet big pulley / 22 theet small pulley
#define DELTA_X_OFFSET          0.0     // angle compensation for axis after homing
#define DELTA_Y_OFFSET          0.0     // angle compensation for axis after homing
#define DELTA_Z_OFFSET          0.0     // angle compensation for axis after homing

/** GENERAL CONFIGURATIONS  **/
#define DEBUG              true
#define RING_BUFFER_SIZE   256

