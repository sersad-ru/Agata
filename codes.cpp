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

#include "codes.h"
#include <ssMultiPrint.h>

Codes::Codes(){

}//Codes

static const __FlashStringHelper* Codes::getCodeName(const uint8_t code){
  switch(code){
    case(MOUSE_LEFT):       return F("MOUSE_LEFT");   // 0x01
    case(MOUSE_RIGHT):      return F("MOUSE_RIGHT");  // 0x02
    case(MOUSE_MIDDLE):     return F("MOUSE_MIDDLE"); // 0x04

    case(KEY_LEFT_CTRL):    return F("KEY_LEFT_CTRL");
    case(KEY_LEFT_SHIFT):   return F("KEY_LEFT_SHIFT");
    case(KEY_LEFT_ALT):     return F("KEY_LEFT_ALT");
    case(KEY_LEFT_GUI):     return F("KEY_LEFT_GUI");
    case(KEY_RIGHT_CTRL):   return F("KEY_RIGHT_CTRL");
    case(KEY_RIGHT_SHIFT):  return F("KEY_RIGHT_SHIFT");
    case(KEY_RIGHT_ALT):    return F("KEY_RIGHT_ALT");
    case(KEY_RIGHT_GUI):    return F("KEY_RIGHT_GUI");

    default: return F("???");
  }//switch
}//getCodeName


// Напечатать код в поток
static void Codes::printCode(Print &p, const uint8_t code){
  ssMultiPrint(p, getCodeName(code), F("\t = "), code, F("\t (0x"));
  if(code < 16) p.print('0');
  p.print(code, HEX);
  p.print(')');
}//printCode


static void Codes::printlnCode(Print &p, const uint8_t code){
  printCode(p, code);
  p.println();
}//printlnCode


// Проверяет попадает ли код в список разрешенных (_codes)
static uint8_t Codes::checkCode(const uint8_t code){
  for(uint8_t i = 0; i < codesSize; i++) if(code == getCode(i)) return true;
  return false;
}//checkCode 


// Выводит список всех доступных кодов 
static void Codes::printCodeList(Print &p){
  p.println(F("Available key codes:"));
  for(uint8_t i = 0; i < codesSize; i++) printlnCode(p, getCode(i));
}//printCodeList