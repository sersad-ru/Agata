#include "cmd.h"

CMD::CMD(Serial_ &ser) {
  _ser = ser;
  _last_command = CMD_NONE;
  _has_new_command = false;
}// CMD


// Была ли получена (1) или нет (0) новая команда. После вызова флаг новой команды будет сброшен
uint8_t CMD::hasNewCommand(){
  uint8_t res = _has_new_command;
  _has_new_command = false;
  return res;
}//hasNewCommand


// Попытаться разобрать конфигурацию кнопки. true - удалось. false - нет
uint8_t CMD::parseKey(CMDKey &key){
  if(sscanf((char*)(_buf + 1), "%hhu = %hhi", &key.num, &key.val) == 2) return true;
  key.num = 0;
  key.val = 0;
  return false;
}//parseKey


// Попытаться разобрать конфигурацию энкодера. true - удалось. false - нет
uint8_t CMD::parseEnc(CMDEnc &enc){
  if(sscanf((char*)(_buf + 1), " = %li , %li", &enc.withBtn, &enc.withoutBtn) == 2) return true;
  enc.withBtn = 0;
  enc.withoutBtn = 0;
  return false;
}//parseEnc


// Опытаться определить, что была команда сброса ("F" или "f"). true - и правда была. false - нет
uint8_t CMD::parseReset(){
  return (char)tolower(_buf[1]) == 'f';
}//parseReset


// Попытаться разобрать инвертирования кнопки. true - удалось, false - нет.
uint8_t CMD::parseInverse(uint8_t &key_num){
  if(sscanf((char*)(_buf + 1), "%hhu", &key_num) == 1) return true;
  return false;
}//parseInverse


// Выполнение переодических действий
void CMD::run(){
  _read_command();
}//run
    

// Попытаться прочесть команду
void CMD::_read_command(){
  // Читаем (копим) строку
  static uint8_t i = 0;
  while(_ser.available()){
    _buf[i++] = _ser.read();
    if((_buf[i - 1] == 0x0D) || (_buf[i - 1] == 0x0A) || (i > (CMD_BUF_SIZE - 1))){
      _buf[i - 1] = 0; // ставим 0 вместо \r или \n или последним символом буфера
      if(i < 2) i = 0; // Если сразу прилетело окончание строки, то начинать сначала
      while(_ser.available())_ser.read(); // подчищаем буфер
      break;
    }//if
  }//while
  
  // К этому моменту i указывает на позицию, куда попадет СЛЕДУЮЩИЙ символ. На следующей итерации!
  if((i < 2) || (_buf[i - 1] != 0)) return; // Минимальный индекс  = 2 ([0]: символ, [1]: \0). Последний записанный (i - 1) символ должен быть \0

  // Считаем, что строку собрали. В следующий раз будем начинать с начала
  i = 0;

  // Анализируем, что начитали
  char cmd = (char)_buf[0]; // Команда

  _has_new_command = true; // Надеемся, что нашли 
  switch(tolower(cmd)){    
    case 'h': _last_command = CMD_HELP; break;    
    case '?': _last_command = CMD_INFO; break;    
    case '&': _last_command = CMD_RESET; break;    
    case 'l': _last_command = CMD_LEFT; break;    
    case 'r': _last_command = CMD_RIGHT; break;    
    case 'k': _last_command = CMD_KEY; break;    
    case 's': _last_command = CMD_SWAP; break;    
    case 'd': _last_command = CMD_DEBUG; break;    
    case 'i': _last_command = CMD_INVERSE; break;    
    default: // не нашли
      _last_command = CMD_ERROR;
  }//switch    
}//_read_command


