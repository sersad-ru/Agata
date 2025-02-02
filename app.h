/*
* Основная логика приложения
*/
#pragma once

#include <Arduino.h>
#include "pinout.h"
#include "flashcfg.h"

class App{
  public:  
    App(flashcfg* c);
    void run(); // Выполнение переодических заданий
    
  private:
    flashcfg * _cfg;
}; // class
