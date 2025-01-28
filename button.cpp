#include "Arduino.h"
#include "button.h"


Button::Button(const uint8_t pin){
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);  
}// Buttton


// Выполнение переодических заданий
void Button::run(){
  uint8_t new_val = !digitalRead(_pin);
  if(new_val == _is_pressed) return; // изменений небыло 
  _was_changed = true; // Состояние изменилось
  _is_pressed = new_val;
}// run


