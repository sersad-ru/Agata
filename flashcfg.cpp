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
       ssMultiPrint(p, KEY_CODE_NAME, "[", i, "]: ");
       Codes::printlnCode(p, cfg.buttons[i]);
  }//for
}//cfg_print
