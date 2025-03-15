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
* Описание подключения периферии
*/

#pragma once
#include "micro_pins.h"

// Энкодеры
// Левый
#define ENC_L_A D15 
#define ENC_L_B D14 
#define ENC_L_BTN D16

// Правый
#define ENC_R_A D9 
#define ENC_R_B D8 
#define ENC_R_BTN D10

// Кнопки (Слева направо. Сверху вниз)
#define KEY_1 D5 // Первый ряд (дальше от энкодеров). Левая.
#define KEY_2 D6 // Первый ряд. Средняя.
#define KEY_3 D7 // Первый ряд. Правая.

#define KEY_4 D2 // Второй ряд (ближе к энкодерам). Левая.
#define KEY_5 D3 // Второй ряд. Средняя.
#define KEY_6 D4 // Второй ряд. Правая.

