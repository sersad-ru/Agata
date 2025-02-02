/*
* Энкодер. Считает дельту ("+" - по часовой, "-" - против часовой).
* При вращении с нажатой кнопкой использует шаг withBtn [1], без кнопки withoutBtn [10]
* На прерывания надо вешать самостоятельно. 
* Вращение по часовой - положительное, против часовой - отрицательное
* Дельта считается в 32-битах (что б точно ничего не потеряло), так что вызовов Mouse.move может понадобиться много. 
*/
#pragma once
#include <Arduino.h>


class Encoder {
  public:    
    Encoder(const uint8_t pinA, const uint8_t pinB, const uint8_t pinBTN, const int32_t withBtn = 1, const int32_t withoutBtn = 10);

    // Установить конфигурацию энкодера. Сбрасывает текущую дельту. 
    // withBtn - шаг при нажатой кнопке (при вращении по часовой cw), т.е. против часовой будет -withBtn
    // withoutBtn - шаг при отпущенной (при вращении по часовой cw), т.е. против часовой будет -withoutBtn
    void setConfig(const int32_t withBtn, const int32_t withoutBtn);

    // Вернуть и сбросить изменение с момента последнего чтения
    int32_t getDelta(){int32_t res = _delta; _delta = 0; return res;};

    // Вернуть изменение, но не сбрасывать
    int32_t checkDelta(){return _delta;};

    // Обработчик прерывания по вращению энкодера. На прерывание ставится снаружи вручную. 
    void onRotate();

  private:
    volatile uint8_t _pinA = 0; // Пины
    volatile uint8_t _pinB = 0;
    volatile uint8_t _pinBTN = 0;

    volatile int32_t _with_btn = 0; // Приращение при нажатой кнопке
    volatile int32_t _without_btn = 0; // Приращение без нажатой кнопки

    volatile int32_t _delta = 0; // Приращение энкодера ("+" - по часовой, "-" - против часовой)
};//class
