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
 * Константы версии 
*/

#pragma once
#include <Arduino.h>

#define FF(val) ((const __FlashStringHelper*)val)

const char APP_VER_VAL[] PROGMEM = "v1.0"; // Базовая версия
#define APP_VER FF(APP_VER_VAL)

const char APP_CPY_VAL[] PROGMEM = " (c)2025"; // Годы копирайта
#define APP_COPYRIGHT FF(APP_CPY_VAL)

const char APP_NAME_VAL[] PROGMEM = "Agata"; // Название приложения
#define APP_NAME FF(APP_NAME_VAL)

const char APP_LONG_NAME_VAL[] PROGMEM = ". The splitted mouse. "; // Длинная часть названия приложения
#define APP_LONG_NAME FF(APP_LONG_NAME_VAL)


const char APP_SERSAD_VAL[] PROGMEM = " by sersad.ru"; // Копирайт
#define APP_SERSAD FF(APP_SERSAD_VAL)

const char APP_BUILD_ID_VAL[] PROGMEM = "BuildID: "; // Идентификатор сборки
#define APP_BUILD_ID FF(APP_BUILD_ID_VAL)
