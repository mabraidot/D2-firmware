#include "Debug.h"

Debug debug;

void Debug::print(String message, bool eol=false){

  if(eol){
    Serial.println(message);
  }else{
    Serial.print(message);
  }
  
}

