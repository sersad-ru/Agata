/*
 * Хранение в EEPROM
*/
#pragma once
#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>

#define FF(val) ((const __FlashStringHelper*)val)

#define BTN_COUNT 6 // Количество обслуживаемых кнопок

// Параметры по-умолчанию
// Код кнопки
const char KEY_CODE_VAL[] PROGMEM = "Key";
#define KEY_CODE_NAME FF(KEY_CODE_VAL)
#define KEY_CODE_0_DEFAULT KEY_LEFT_SHIFT // Слева направо, сверху вних
#define KEY_CODE_1_DEFAULT KEY_LEFT_ALT
#define KEY_CODE_2_DEFAULT KEY_LEFT_CTRL
#define KEY_CODE_3_DEFAULT MOUSE_LEFT // Второй ряд, ближе к энкодерам
#define KEY_CODE_4_DEFAULT MOUSE_MIDDLE
#define KEY_CODE_5_DEFAULT MOUSE_RIGHT

// Энкодер
const char ENC_VAL[] PROGMEM = "encoder ";
#define ENC_NAME FF(ENC_VAL)

const char ENC_WITH_VAL[] PROGMEM = "with:\t = ";
#define ENC_WITH_NAME FF(ENC_WITH_VAL)

const char ENC_WITHOUT_VAL[] PROGMEM = "without:\t = ";
#define ENC_WITHOUT_NAME FF(ENC_WITHOUT_VAL)

const char ENC_USE_FOR_X_VAL[] PROGMEM = "for X axis";
#define ENC_USE_FOR_X_NAME FF(ENC_USE_FOR_X_VAL)


// Левый энкодер
const char ENC_L_VAL[] PROGMEM = "Left ";
#define ENC_L_NAME FF(ENC_L_VAL)
// Правый энкодер
const char ENC_R_VAL[] PROGMEM = "Right ";
#define ENC_R_NAME FF(ENC_R_VAL)

#define ENC_L_WITH_DEFAULT 1 // Левый энкодер при нажатой кнопке
#define ENC_L_WITHOUT_DEFAULT 10 // Левый энкодер при отпущенной кнопке

#define ENC_R_WITH_DEFAULT 1 // Правый энкодер при нажатой кнопке
#define ENC_R_WITHOUT_DEFAULT 10 // Парвый энкодер при отпущенной кнопке

// Управляет ли праый X
#define IS_R_FOR_X_DEFAULT true // Правый энкодер управляет осью X

// Параметры конфигурации
typedef struct {
  uint8_t  noValue; // Флаг того (==1), что не было сохраненных значений 
  
  uint8_t buttons[BTN_COUNT]; // Список кодов кнопок

  int32_t encLwith; // Приращение левого энкодера при нажатой кнопке
  int32_t encLwithout; // Приращение левого энкодера при отпущенной кнопке

  int32_t encRwith; // Приращение правого энкодера при нажатой кнопке
  int32_t encRwithout; // Приращение правого энкодера при отпущенной кнопке

  uint8_t isRforX; // Если true - то правый энкодер управляет X иначе Y
} flashcfg;

bool cfg_init(flashcfg &cfg); //Подготовиться к работе с конфигом и загрузить его, а если надо и прописать по умолчанию (вернет false - если по умолчанию)
bool cfg_load(flashcfg &cfg); //Загрузить конфиг из флеша (false - если по умолчанию)
void cfg_save(flashcfg &cfg); //Сохранить конфиг во флеш
void cfg_reset(flashcfg &cfg); //Сбросить конфиг на значения по умолчанию
void cfg_print(Print &p, flashcfg &cfg); // Вывести настройки
