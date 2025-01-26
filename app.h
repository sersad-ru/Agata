/*
* Основная логика приложения
*/
#pragma once

#include <Arduino.h>
#include "pinout.h"
#include "flashcfg.h"

#define FF(val) ((const __FlashStringHelper*)val)

// Название приложения
const char APP_NAME[] PROGMEM = "The WaterScales v1.0 (c)2024 by sersad.ru";


// Состояния приложения
typedef enum {
  APP_NORMAL,   // Обычное состояние
  APP_LOADING,  // Идет постепенный набор веса
  APP_NEGATIVE  // Отрицательный вес. Сняли бутыль
} appState;

class App{
  public:  
    App(flashcfg* c);
    void run(); // Выполнение переодических заданий
    
  private:
    flashcfg * _cfg;
}; // class
