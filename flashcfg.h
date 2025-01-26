/*
 * Хранение в EEPROM
*/
#pragma once
#include <Arduino.h>

#define FF(val) ((const __FlashStringHelper*)val)

// Параметры по-умолчанию
// Нулевой уровень взвешивания
const char TARE_NAME_VAL[] PROGMEM = "tare";
#define TARE_NAME FF(TARE_NAME_VAL)
#define TARE_DEFAULT 0


// Параметры конфигурации
typedef struct {
  uint8_t  noValue; // Флаг того (==1), что не было сохраненных значений 
  
} flashcfg;

bool cfg_init(flashcfg &cfg); //Подготовиться к работе с конфигом и загрузить его, а если надо и прописать по умолчанию (вернет false - если по умолчанию)
bool cfg_load(flashcfg &cfg); //Загрузить конфиг из флеша (false - если по умолчанию)
void cfg_save(flashcfg &cfg); //Сохранить конфиг во флеш
void cfg_reset(flashcfg &cfg); //Сбросить конфиг на значения по умолчанию
void cfg_print(Print &p, flashcfg &cfg); // Вывести настройки
