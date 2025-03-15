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

#include "app.h"
#include <ssBuildID.h>
#include <ssMultiPrint.h>
#include "codes.h"
#include "version.h"


const char KEY_VAL[] PROGMEM = "Key_";
#define KEY_NAME FF(KEY_VAL)

const char MOUSE_VAL[] PROGMEM = "Mouse";
#define MOUSE_NAME FF(MOUSE_VAL)

const char PRESS_VAL[] PROGMEM = " DOWN\t";
#define PRESS_NAME FF(PRESS_VAL)

const char RELEASE_VAL[] PROGMEM = " UP\t";
#define RELEASE_NAME FF(RELEASE_VAL)

const char CFG_SAVED_VAL[] PROGMEM = "Config saved.";
#define CFG_SAVED_NAME FF(CFG_SAVED_VAL)

const char ERROR_IN_CMD_VAL[] PROGMEM = "*** Error in command: \"";
#define ERROR_IN_CMD_NAME FF(ERROR_IN_CMD_VAL)


App::App(flashcfg* c, Encoder* encL, Encoder* encR, Button btn[], CMD* cmd){
  _cfg = c;
  _encL = encL;
  _encR = encR;
  _cmd = cmd;
  for(uint8_t i = 0; i < BTN_COUNT; i++) _buttons[i] = &btn[i];
}// App


// Выполнение переодических заданий
void App::run(){
  _processEncoders(); // Энкодеры
  _processButtons(); // Кнопки
  _processCommands(); // Команды
}// run


// Обработать энкодеры
void App::_processEncoders(){
  if(!_encL -> checkDelta() && !_encR -> checkDelta()) return; // На энкодерах событий не было
  int32_t x = (_cfg -> isRforX) ? _encR -> getDelta() : _encL -> getDelta(); // Кто отвечает за X
  int32_t y = (_cfg -> isRforX) ? _encL -> getDelta() : _encR -> getDelta(); // Кто отвечает за Y
  if(_dbg && Serial.availableForWrite()) ssMultiPrintln(Serial, F("x: "), x, F("\ty: "), y); // Выводить отладочные сообщения (если есть куда)
  while((abs(x) > 127) || (abs(y) > 127)){ // Максимальное приращение по осям 127
    int8_t stepX = (x > 0) ? min(x, 127) : max(x, -127); // Идем сразу на максимум или на x
    int8_t stepY = (y > 0) ? min(y, 127) : max(y, -127);
    Mouse.move(stepX, stepY);  // Делаем шаг
    x -= stepX; // Уменьшаем значения
    y -= stepY;
  }//while
  Mouse.move(x, y);
}//_processEncoders


// Обработать кнопки
void App::_processButtons(){
  for(uint8_t i = 0; i < BTN_COUNT; i++){
    _buttons[i] -> run();
    if(!_buttons[i] -> wasChanged()) continue; // С кнопкой ничего не происходило

    if((_cfg -> buttons[i]) <= Codes::maxMouseCode) _doMouse(i, _buttons[i] -> getPressed()); // Это мышь
      else _doKey(i, _buttons[i] -> getPressed()); // Это клавиатура
  }//for
}//processButtons


// Отработка мыши
void App::_doMouse(const uint8_t btn_ind, const uint8_t is_pressed){
  if(is_pressed) Mouse.press(_cfg -> buttons[btn_ind]);
    else Mouse.release(_cfg -> buttons[btn_ind]);
  if(!_dbg) return; // Не выводить отладочные сообщения 
  if(!Serial.availableForWrite()) return; // Некуда писать
  ssMultiPrint(Serial, MOUSE_NAME, (is_pressed) ? PRESS_NAME : RELEASE_NAME);
  Codes::printlnCode(Serial, _cfg -> buttons[btn_ind]);
}//_doMouse


// Отработка кнопок
void App::_doKey(const uint8_t btn_ind, const uint8_t is_pressed){
  if(is_pressed) Keyboard.press(_cfg -> buttons[btn_ind]);
    else Keyboard.release(_cfg -> buttons[btn_ind]);
  if(!_dbg) return; // Не выводить отладочные сообщения 
  if(!Serial.availableForWrite()) return; // Некуда писать
  ssMultiPrint(Serial, KEY_NAME, btn_ind, (is_pressed) ? PRESS_NAME : RELEASE_NAME);
  Codes::printlnCode(Serial, _cfg -> buttons[btn_ind]);
}//_doKey


// Обработать команды
void App::_processCommands(){
  _cmd -> run();
  if(!_cmd -> hasNewCommand()) return; // Нету новых команд
  CMDKey key; // Настройки кнопки
  uint8_t key_num; // Номер кнопки для инверсии

  switch(_cmd -> getLastCommand()){
    case CMD_DEBUG:  // Переключение вывода в порт отладочных сообщений
      _dbg = !_dbg;
      ssMultiPrintln(Serial, F("Debug mode: "), (_dbg) ? F("ON") : F("OFF"));
    break;

    case CMD_INFO: // Информация о билде и текущих настройках
      ssMultiPrintln(Serial, "\n", APP_NAME, APP_LONG_NAME, APP_VER, APP_COPYRIGHT, APP_SERSAD);
      ssMultiPrintln(Serial, APP_BUILD_ID, BUILD_ID, "\n");
      cfg_print(Serial, *_cfg);
      ssMultiPrintln(Serial, F("Debug mode: "), (_dbg) ? F("ON") : F("OFF"));
      Serial.println(F("Use \"h\"\t- for help."));
      Serial.println();
    break;

    case CMD_HELP: // Вывести справку по командам
      Serial.println(F("--- HELP ---"));
      Serial.println(F("h\t- this help"));
      Serial.println(F("?\t- show version, build number and current config"));
      Serial.println(F("&F\t- reset to system defaults and save config"));
      Serial.println(F("s\t- swap left and right encoders and save config"));
      Serial.println(F("d\t- turn on / off debug mode"));
      Serial.println(F("l=A,B\t- left encoder settings:  A - fine increment, B - coarse increment. \"l=1,10\" - for CW rotation increment"));
      Serial.println(F("r=A,B\t- right encoder settings: A - fine increment, B - coarse increment. \"r=-5,-50\" - for CCW rotation increment"));
      ssMultiPrintln(Serial, F("iN\t- invert key status (pressed/released): N - key number [0.."), BTN_COUNT - 1, F("], \"i0\" - to invert key 0 (\""), KEY_INVERSE_NAME, F("\" in key status)"));      
      ssMultiPrintln(Serial, F("kN=C\t- key settings: N - key number [0.."), BTN_COUNT - 1, F("], C - key code. \"k0=0x02\" - for MOUSE_RIGHT on key 0"));
      Codes::printCodeList(Serial);
      Serial.println(F("--- --- ---"));
    break;

    case CMD_SWAP: // Поменять местами левый и правый энкодер
      _cfg -> isRforX = !_cfg -> isRforX;      
      ssMultiPrintln(Serial, (_cfg -> isRforX) ? ENC_R_NAME : ENC_L_NAME, ENC_NAME, ENC_USE_FOR_X_NAME);
      cfg_save(*_cfg); //сохраняем значения
      Serial.println(CFG_SAVED_NAME);
    break;

    case CMD_RESET: // Сброс настроек
      if(!_cmd -> parseReset()){
        ssMultiPrintln(Serial, ERROR_IN_CMD_NAME, (char*)(_cmd -> getLastArgs() - 1), "\""); 
        break;  
      }//if 
      cfg_reset(*_cfg); // сбрасываем настройки и сохраняем их
      _encL -> setConfig(_cfg -> encLwith, _cfg -> encLwithout); // Настраиваем энкодеры
      _encR -> setConfig(_cfg -> encRwith, _cfg -> encRwithout); // Настраиваем энкодеры
      Serial.println(F("Reset to defaults."));
    break;

    case CMD_KEY: // Настройка кнопки
      if(!_cmd -> parseKey(key)){ // Неудалось разобрать команду
        ssMultiPrintln(Serial, ERROR_IN_CMD_NAME, (char*)(_cmd -> getLastArgs() - 1), "\""); 
        break;  
      }//if 
      if(key.num > BTN_COUNT - 1){ // Тот ли номер кнопки
        _printIllegalKeyNum(key.num);      
        break;
      }//if
      if(!Codes::checkCode(key.val)){ // То ли значение кнопки
        ssMultiPrintln(Serial, F("*** Error: Illegal key code: "), key.val, F(" in command \""), (char*)(_cmd -> getLastArgs() - 1), "\"");
        Codes::printCodeList(Serial);
        break; 
      }//if
      _cfg -> buttons[key.num] = key.val;
      ssMultiPrint(Serial, _cfg -> inverse[key.num] ? KEY_INVERSE_NAME : KEY_NO_INVERSE_NAME, KEY_CODE_NAME, "_", key.num, ": ");
      Codes::printlnCode(Serial, key.val);
      cfg_save(*_cfg); //сохраняем значения
      Serial.println(CFG_SAVED_NAME);
    break;

    case CMD_INVERSE: // Инверсия состояния кнопки
      if(!_cmd -> parseInverse(key_num)){ // Неудалось разобрать команду
        ssMultiPrintln(Serial, ERROR_IN_CMD_NAME, (char*)(_cmd -> getLastArgs() - 1), "\""); 
        break;  
      }//if 
      if(key_num > BTN_COUNT - 1){ // Тот ли номер кнопки
        _printIllegalKeyNum(key_num);
        break;
      }//if
      _cfg -> inverse[key_num] = !_cfg -> inverse[key_num];
      ssMultiPrintln(Serial, KEY_CODE_NAME, "_", key.num, F(" is"), _cfg -> inverse[key_num] ? F(" ") : F(" not "), F("inverted."));
      cfg_save(*_cfg); //сохраняем значения
      Serial.println(CFG_SAVED_NAME);
    break;

    case CMD_LEFT: _doEnc(_encL, &(_cfg->encLwith), &(_cfg->encLwithout)); break; // Настройка левого энкодера
    case CMD_RIGHT: _doEnc(_encR, &(_cfg->encRwith), &(_cfg->encRwithout)); break; // Настройка правого энкодера
    
    default: // Ошибка
      ssMultiPrintln(Serial, ERROR_IN_CMD_NAME, (char*)(_cmd -> getLastArgs() - 1), "\""); break;
  }//switch
}//_processCommands


// Поменять настройки энкодера 
void App::_doEnc(Encoder* _enc, int32_t* with, int32_t* without){
  CMDEnc enc;
  if(!_cmd -> parseEnc(enc)){ // Неудалось разобрать команду
    ssMultiPrintln(Serial, ERROR_IN_CMD_NAME, (char*)(_cmd -> getLastArgs() - 1), "\""); 
    return;
  }//if
  
  // Запоминаем настройки
  *with = enc.withBtn;
  *without = enc.withoutBtn;

  // Выводим новые настройки
  ssMultiPrintln(Serial, (_enc == _encL) ? ENC_L_NAME : ENC_R_NAME, ENC_NAME, ENC_WITH_NAME, enc.withBtn);
  ssMultiPrintln(Serial, (_enc == _encL) ? ENC_L_NAME : ENC_R_NAME, ENC_NAME, ENC_WITHOUT_NAME, enc.withoutBtn);

  // Ставим их в энкодер
  _enc -> setConfig(enc.withBtn, enc.withoutBtn);

  cfg_save(*_cfg); //сохраняем значения
  Serial.println(CFG_SAVED_NAME);
}//_doEnc


// Вывести ошибку номера кнопки
void App::_printIllegalKeyNum(const uint8_t num){
  ssMultiPrintln(Serial, F("*** Error: Illegal key number: "), num, F(" (not in [1.."), BTN_COUNT - 1, F("]) in command \""), (char*)(_cmd -> getLastArgs() - 1), "\""); 
}//_printIllegalKeyNumb