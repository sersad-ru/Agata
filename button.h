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
