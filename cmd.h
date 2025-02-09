/*
* Command interface.
* Работает с UART-ом
*/
#pragma once
#include <Arduino.h>
#include "pinout.h"

#define CMD_BUF_SIZE 32 // Размер буфера для приема команд с аргументами

// Команды
typedef enum {
  CMD_NONE,  // Нет команды 
  CMD_ERROR, // Команда нераспознана
  CMD_HELP,  // ? - справка по командам (h - тоже подходит)
  CMD_INFO,  // i - информация о билде, название и конфигурация
  CMD_RESET, // & - сброс к настройкам по умолчанию (единственным аргументом должна быть "F" или "f". т.е. "&F")
  CMD_LEFT,  // l - левый энкодер l=1,10
  CMD_RIGHT, // r - правый энкодер r = -10, -100
  CMD_SWAP,  // s - поменять местами левый и правый энкодер
  CMD_KEY,   // k - кнопка k1=125
  CMD_DEBUG  // d - включить / выключить вывод событий в UART (не сохраняется в настройках)
} CMDCommands;

// Информация об энкодере
typedef struct {
  int32_t withBtn; // Шаг при нажатой кнопке (положительный - будет увеличиваться при CW, отрицательный - будет увеличиваться при CCW)
  int32_t withoutBtn; // Шаг при отпущенной кнопке
} CMDEnc;

// Информация о кнопке
typedef struct {
  uint8_t num; // Номер кнопки (1..6)
  uint8_t val; // Отправляемый код
}CMDKey;

class CMD {
  public:    
    CMD(Serial_ &ser);

    // Была ли получена (1) или нет (0) новая команда. После вызова флаг новой команды будет сброшен
    uint8_t hasNewCommand();

    // Вернуть последнюю команду
    CMDCommands getLastCommand(){return _last_command;};

    // Вернуть ссылку на строку аргументов
    char* getLastArgs(){return (char*)(_buf + 1);};

    // Попытаться разобрать конфигурацию энкодера. true - удалось. false - нет. l=1,10,cw или r = 10, 100, cww
    uint8_t parseEnc(CMDEnc &enc);

    // Попытаться разобрать конфигурацию кнопки. true - удалось. false - нет. k1=125 k2=0xFF
    uint8_t parseKey(CMDKey &key);
    
    // Опытаться определить, что была команда сброса ("F" или "f"). true - и правда была. false - нет
    uint8_t parseReset();

    // Выполнение переодических действий
    void run();

  private:
    Serial_ _ser;
    uint8_t _has_new_command = false; // Флаг наличия новой команды. Сбрасывается при вызове hasNewCommand()
    uint8_t _buf[CMD_BUF_SIZE]; // Буфер для приема команд
    CMDCommands _last_command = CMD_NONE; // Последняя полученная команда

    // Попытаться прочесть команду
    void _read_command();
};//class
