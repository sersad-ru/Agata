/*
* Энкодер. 
* На прерывания НЕ вешается сам. Одно для вращения и одно для кнопки.
* Вращение по часовой - положительное, против часовой - отрицательное
*/
#pragma once
#include <Arduino.h>


class Encoder {
  public:    
    Encoder(const uint8_t pinA, const uint8_t pinB, const uint8_t pinBTN, const int32_t withBtn = 1, const int32_t withoutBtn = 10);

    // Вернуть и сбросить изменение с момента последнего чтения
    int32_t getDelta(){int32_t res = _delta; _delta = 0; return res;};

    // Вернуть изменение, но не сбрасывать
    int32_t checkDelta(){return _delta;};

    // Обработчик прерывания по вращению энкодера 
    void onRotate();

  private:
    volatile uint8_t _pinA = 0; // Пины
    volatile uint8_t _pinB = 0;
    volatile uint8_t _pinBTN = 0;

    volatile int32_t _with_btn = 0; // Приращение при нажатой кнопке
    volatile int32_t _without_btn = 0; // Приращение без нажатой кнопки

    volatile int32_t _delta = 0; // Приращение энкодера ("+" - по часовой, "-" - против часовой)
};//class
