/*
 * Константы версии 
*/

#pragma once
#include <Arduino.h>

#define FF(val) ((const __FlashStringHelper*)val)

const char APP_VER_VAL[] PROGMEM = "v1.0"; // Базовая версия
#define APP_VER FF(APP_VER_VAL)

const char APP_CPY_VAL[] PROGMEM = " (c)2025"; // Годы копирайта
#define APP_COPYRIGHT FF(APP_CPY_VAL)
