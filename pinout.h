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

