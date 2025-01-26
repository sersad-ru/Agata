#include <EEPROM.h>
#include "flashcfg.h"

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
//  cfg.tare = TARE_DEFAULT;

  cfg.noValue = 0;//Выставляем флаг, что данные установлены
  cfg_save(cfg); //сохраняем значения
}//cfg_reset


template <typename T>
void _print_val(Print &p, const __FlashStringHelper * name, T val){
  p.print(name);
  p.print(": \"");
  p.print(val);
  p.println("\" ");
}//_print_val


void cfg_print(Print &p, flashcfg &cfg){
//  _print_val(p, TARE_NAME, cfg.tare);
}//cfg_print
