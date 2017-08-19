
#ifndef MACROS_H
#define MACROS_H

#define PIN_EXISTS(PN) (defined(PN ##_PIN) && PN ##_PIN >= 0)

#define HAS_X_MAX (PIN_EXISTS(X_MAX))
#define HAS_Y_MAX (PIN_EXISTS(Y_MAX))
#define HAS_Z_MAX (PIN_EXISTS(Z_MAX))
#define HAS_X_MIN (PIN_EXISTS(X_MIN))
#define HAS_Y_MIN (PIN_EXISTS(Y_MIN))
#define HAS_Z_MIN (PIN_EXISTS(Z_MIN))



void DEBUG(String message, bool eol=false){
  if(eol){
    Serial.println(message);
  }else{
    Serial.print(message);
  }
}


#endif //MACROS_H
