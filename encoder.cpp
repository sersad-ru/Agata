#include "Arduino.h"
#include "encoder.h"


Encoder::Encoder(const uint8_t pinA, const uint8_t pinB, const uint8_t pinBTN, const int32_t withBtn, const int32_t withoutBtn){
  _pinA = pinA; // Пины
  _pinB = pinB;
  _pinBTN = pinBTN;
  
  _with_btn = withBtn; // Приращение при нажатой кнопке
  _without_btn = withoutBtn; // Приращение без нажатой кнопки
  _delta = 0; // Приращение энкодера ("+" - по часовой, "-" - против часовой)

  pinMode(_pinA, INPUT_PULLUP);
  pinMode(_pinB, INPUT_PULLUP);
  pinMode(_pinBTN, INPUT_PULLUP);
}// Encoder



// Обработчик прерывания по вращению
void Encoder::onRotate(){
  static uint8_t last_A = 0; // Предыдущее состояние выхода А
  static uint8_t flag = 0; // У нас два импульса на один шаг, кроме первого
  uint8_t enc_A = digitalRead(_pinA); // Читаем вход А
  if(enc_A == last_A) return; // Выход не менялся. Вращения не было
  flag = !flag; // Кроме первого шага нас интересует каждый второй импульс
  if(flag) {
     int8_t dir = (digitalRead(_pinB) == last_A) ? -1 : 1;//B == last_A, т.е B != A - значит по часовой, иначе против часовой 
     _delta += (!digitalRead(_pinBTN)) ? (dir * _with_btn) : (dir * _without_btn); // Считаем приращение учитываю состояние кнопки
  }//if   
  last_A = enc_A; // Сохраняем текущее значение А
}//onRotate

