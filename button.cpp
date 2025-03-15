/*
Agata. The Splitted Mouse.
(c)2025 by Sergey Sadovnikov (sersad@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <www.gnu.org/licenses/>.
*/

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


