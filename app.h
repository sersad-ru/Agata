/*
* Основная логика приложения
*/
#pragma once

#include <Arduino.h>
#include "pinout.h"
#include "flashcfg.h"

#define FF(val) ((const __FlashStringHelper*)val)

// Название приложения
const char APP_NAME_VAL[] PROGMEM = "Agata. The splitted mouse. ";
#define APP_NAME FF(APP_NAME_VAL)
const char APP_SERSAD_VAL[] PROGMEM = " by sersad.ru";
#define APP_SERSAD FF(APP_SERSAD_VAL)
const char APP_BUILD_ID_VAL[] PROGMEM = "BuildID: ";
#define APP_BUILD_ID FF(APP_BUILD_ID_VAL)


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
