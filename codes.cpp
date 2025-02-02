#include "codes.h"
#include <Keyboard.h>
#include <Mouse.h>

// Вернуть строковое представление по коду
const char* code2str(const uint8_t code){
  switch(code){
    case(MOUSE_LEFT):       return "MOUSE_LEFT";   // 0x01
    case(MOUSE_RIGHT):      return "MOUSE_RIGHT";  // 0x02
    case(MOUSE_MIDDLE):     return "MOUSE_MIDDLE"; // 0x04

    case(KEY_LEFT_CTRL):    return "KEY_LEFT_CTRL";
    case(KEY_LEFT_SHIFT):   return "KEY_LEFT_SHIFT";
    case(KEY_LEFT_ALT):     return "KEY_LEFT_ALT";
    case(KEY_LEFT_GUI):     return "KEY_LEFT_GUI";
    case(KEY_RIGHT_CTRL):   return "KEY_RIGHT_CTRL";
    case(KEY_RIGHT_SHIFT):  return "KEY_RIGHT_SHIFT";
    case(KEY_RIGHT_ALT):    return "KEY_RIGHT_ALT";
    case(KEY_RIGHT_GUI):    return "KEY_RIGHT_GUI";
    
    default: return "???";    
  }//switch
}//code2str


