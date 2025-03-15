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

#include <EEPROM.h>
#include <ssMultiPrint.h>
#include "flashcfg.h"
#include "codes.h"

bool cfg_init(flashcfg &cfg) {
  return cfg_load(cfg); //Читаем
}//cfg_init


bool cfg_load(flashcfg &cfg) {
  EEPROM.get(0, cfg); //Читаем
  if(!cfg.noValue) return true; //Значение в памяти были
  cfg_reset(cfg); //Ставим по умолчанию
  return false; //не было значений в памяти
}//cfg_load


void cfg_save(flashcfg &cfg) {
  EEPROM.put(0, cfg); //Записываем значения
}//cfg_save


void cfg_reset(flashcfg &cfg) {
  //Ставим значения по умолчанию
  cfg.encLwith = ENC_L_WITH_DEFAULT;
  cfg.encLwithout = ENC_L_WITHOUT_DEFAULT;

  cfg.encRwith = ENC_R_WITH_DEFAULT;
  cfg.encRwithout = ENC_R_WITHOUT_DEFAULT;
  
  cfg.isRforX = IS_R_FOR_X_DEFAULT;

  cfg.buttons[0] = KEY_CODE_0_DEFAULT;
  cfg.buttons[1] = KEY_CODE_1_DEFAULT;
  cfg.buttons[2] = KEY_CODE_2_DEFAULT;
  cfg.buttons[3] = KEY_CODE_3_DEFAULT;  
  cfg.buttons[4] = KEY_CODE_4_DEFAULT;  
  cfg.buttons[5] = KEY_CODE_5_DEFAULT;  
  for(uint8_t i = 0; i < BTN_COUNT; i++) cfg.inverse[i] = KEY_INVERSE_DEFAULT;

  cfg.noValue = 0;//Выставляем флаг, что данные установлены
  cfg_save(cfg); //сохраняем значения
}//cfg_reset


void cfg_print(Print &p, flashcfg &cfg){
  ssMultiPrintln(p, (cfg.isRforX) ? ENC_R_NAME : ENC_L_NAME, ENC_NAME, ENC_USE_FOR_X_NAME);

  ssMultiPrintln(p, ENC_L_NAME, ENC_NAME, ENC_WITH_NAME, cfg.encLwith);
  ssMultiPrintln(p, ENC_L_NAME, ENC_NAME, ENC_WITHOUT_NAME, cfg.encLwithout);

  ssMultiPrintln(p, ENC_R_NAME, ENC_NAME, ENC_WITH_NAME, cfg.encRwith);
  ssMultiPrintln(p, ENC_R_NAME, ENC_NAME, ENC_WITHOUT_NAME, cfg.encRwithout);
  
  for(uint8_t i = 0; i < BTN_COUNT; i++){
    ssMultiPrint(p, cfg.inverse[i] ? KEY_INVERSE_NAME : KEY_NO_INVERSE_NAME, KEY_CODE_NAME, "_", i, ": "); 
    Codes::printlnCode(p, cfg.buttons[i]);
  }//for
}//cfg_print
