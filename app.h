/*
* Основная логика приложения
*/
#pragma once

#include <Arduino.h>
#include "pinout.h"
#include "flashcfg.h"
#include "encoder.h"
#include "button.h"
#include "cmd.h"

class App{
  public:  
    App(flashcfg* c, Encoder* encL, Encoder* encR, Button btn[], CMD* cmd);
    void run(); // Выполнение переодических заданий
  private:
    flashcfg * _cfg;
    Encoder* _encL; // Левый энкодер
    Encoder* _encR; // Правый энкодер
    Button *_buttons[BTN_COUNT]; // Кнопки
    CMD* _cmd; // Коммандный интерфейс

    uint8_t _dbg = false; // Включить (временно, интерактивно) отладочный вывод событий в UART

    void _processEncoders(); // Обработать энкодеры
    void _processButtons(); // Обработать кнопки
    void _processCommands(); // Обработать команды
    void _doMouse(const uint8_t btn_ind, const uint8_t is_pressed); // Отработка мыши
    void _doKey(const uint8_t btn_ind, const uint8_t is_pressed); // Отработка кнопок
    void _doEnc(Encoder*_enc, int32_t* with, int32_t* without); // Поменять настройки энкодера 
}; // class
