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

/*
* Коды кнопок. Соответствуют содержимому библиотеки <Keyboard.h> и <Mouse.h> 
* Используются только коды кнопок мыши и модификаторы клавиатуры.
* Все остальное вешать на кнопки с фиксацией не имеет смысла.
*/
#pragma once
#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

#define arraySize(_array) ( sizeof(_array) / sizeof(*(_array)) )
#define FF(val) ((const __FlashStringHelper*)val)

class Codes {
  private:
    inline static const PROGMEM uint8_t _codes[] { MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE, 
                                                   KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_ALT, KEY_LEFT_GUI,
                                                   KEY_RIGHT_CTRL, KEY_RIGHT_SHIFT, KEY_RIGHT_ALT, KEY_RIGHT_GUI };
  public:
    Codes();
    static const uint8_t codesSize = arraySize(_codes); // Размер списка кодов 
    static const uint8_t maxMouseCode = MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE; // Максимальное значение кода, когда речь все еще идет о мыше 0x07
    static uint8_t getCode(uint8_t index){index = min((uint8_t)index, (uint8_t)(codesSize - 1)); return pgm_read_byte(&_codes[index]);};
    static uint8_t checkCode(const uint8_t code); // Проверяет попадает ли код в список разрешенных (_codes)
    static const __FlashStringHelper* getCodeName(const uint8_t code);
    static void printCode(Print &p, const uint8_t code); // Напечатать код в поток
    static void printlnCode(Print &p, const uint8_t code);
    static void printCodeList(Print &p); // Выводит список всех доступных кодов 
};//class

