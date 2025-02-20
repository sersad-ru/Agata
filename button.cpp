#include "Arduino.h"
#include "button.h"


Button::Button(const uint8_t pin, uint8_t * is_inverted){
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);  
  _is_inverted = is_inverted;
}// Buttton


// Выполнение переодических заданий
void Button::run(){
  uint8_t new_val = (*_is_inverted) ? digitalRead(_pin) : !digitalRead(_pin);
  if(new_val == _is_pressed) return; // изменений небыло 
  _was_changed = true; // Состояние изменилось
  _is_pressed = new_val;
}// run


