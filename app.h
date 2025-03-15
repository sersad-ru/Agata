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
    void _printIllegalKeyNum(const uint8_t num); // Вывести ошибку номера кнопки
}; // class
