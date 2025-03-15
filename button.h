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
* Кнопка. Просто кнопка. Читается опросом через run.
*/
#pragma once

#include <Arduino.h>


class Button{
  public:  
    Button(const uint8_t pin, uint8_t * is_inverted);
    void run(); // Выполнение переодических заданий
    
    // Получить состояние кнопки и сбросить флаг изменения
    uint8_t getPressed(){_was_changed = false; return _is_pressed;};

    // Получить состояние кнопки без сброса флага изменения
    uint8_t checkPressed(){return _is_pressed;};

    // Вернуть флаг измнения состояния
    uint8_t wasChanged(){return _was_changed;};

  private:
    uint8_t _pin = 0; // Пин
    uint8_t _is_pressed = false; // Флаг нажатия на кнопку
    uint8_t _was_changed = false; // Было ли изменено с последнего получения
    uint8_t *_is_inverted; // Нужно ли инвертировать состояние (указатель на элемент массива конфигуации, отвечающий за эту кнопку)
}; // class
