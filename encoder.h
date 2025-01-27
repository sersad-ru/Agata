/*
* Энкодер. 
* На прерывания вешается сам. Одно для вращения и одно для кнопки.
* Вращение по часовой - положительное, против часовой - отрицательное
*/
#pragma once
#include <Arduino.h>


class Encoder {
  public:    
    Encoder(const uint8_t pinA, const uint8_t pinB, const uint8_t pinBTN, const int32_t withBtn = 1, const int32_t withoutBtn = 10);

    // Вернуть изменение с момента последнего чтения
    int32_t getDelta(){int32_t res = _delta; _delta = 0; return res;};

  private:
    static inline volatile uint8_t _pinA = 0; // Пины
    static inline volatile uint8_t _pinB = 0;
    static inline volatile uint8_t _pinBTN = 0;

    static inline volatile int32_t _with_btn = 0; // Приращение при нажатой кнопке
    static inline volatile int32_t _without_btn = 0; // Приращение без нажатой кнопки

    static inline volatile uint8_t _is_btn_pressed = 0; // Флаг нажатой кнопки энкодера
    static inline volatile int32_t _delta = 0; // Приращение энкодера ("+" - по часовой, "-" - против часовой)

    // Обработчик прерывания по врещению энкодера
    static void _on_rotate();

    // Обработчик прерывания по нажатию кнопки
    static void _on_btn();
};//class
