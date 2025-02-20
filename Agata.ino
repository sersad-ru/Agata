/*
* Agata
* v 1.0
* (c)25.01.2025 by sersad
* 20.02.2025
*/

/*
* Board: Arduino AVR Boards / Arduino Micro (Leonardo)
*/
#include <PinChangeInterrupt.h>
#include <ssBuildID.h>
#include <ssMultiPrint.h>
#include "version.h"
#include "flashcfg.h"
#include "pinout.h"
#include "encoder.h"
#include "button.h"
#include "app.h"

//#define RESET_FLASH_CFG //Сбросить конфигурацию

#define arraySize(_array) ( sizeof(_array) / sizeof(*(_array)) )

// Конфиг
flashcfg cfg;

// Энкодеры
Encoder encL = Encoder(ENC_L_A, ENC_L_B, ENC_L_BTN, ENC_L_WITH_DEFAULT, ENC_L_WITHOUT_DEFAULT);
Encoder encR = Encoder(ENC_R_A, ENC_R_B, ENC_R_BTN, ENC_R_WITH_DEFAULT, ENC_R_WITHOUT_DEFAULT);

// Кнопки
Button buttons[BTN_COUNT] = { Button(KEY_1, &cfg.inverse[0]), 
                              Button(KEY_2, &cfg.inverse[1]), 
                              Button(KEY_3, &cfg.inverse[2]), 
                              Button(KEY_4, &cfg.inverse[3]), 
                              Button(KEY_5, &cfg.inverse[4]), 
                              Button(KEY_6, &cfg.inverse[5])};

// Командный интерфейс
CMD cmd = CMD(Serial);

// Приложение
App app = App(&cfg, &encL, &encR, buttons, &cmd);


void setup() {
  Serial.begin(9600);

   // Порт должен очухаться 
  for(uint8_t i = 0; i < 20; i++){
   delay(100);
   if(Serial.availableForWrite()) Serial.print('*');
   Serial.flush();
  }//for
  ssMultiPrintln(Serial, "\n", APP_NAME, APP_LONG_NAME, APP_VER, APP_COPYRIGHT, APP_SERSAD);
  ssMultiPrintln(Serial, APP_BUILD_ID, BUILD_ID);

  cfg_init(cfg); // Инициализируем конфиг (значения по умолчанию ставятся там же - в flashcfg.cpp
  Serial.println(F("\nConfig loaded."));
#ifdef RESET_FLASH_CFG
  cfg_reset(cfg); //Принудительно сбрасываем значения
  Serial.println(F("\nConfig reseted."));
#endif
  if(Serial.availableForWrite()) cfg_print(Serial, cfg);
  Serial.println();

  // Настраиваем энкодеры
  encL.setConfig(cfg.encLwith, cfg.encLwithout);
  encR.setConfig(cfg.encRwith, cfg.encRwithout); 

  // Развешивать обработчики прерываний приходится тут и через лямбду :(
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_L_A), [](){encL.onRotate();}, CHANGE);  
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_R_A), [](){encR.onRotate();}, CHANGE);  

  ssMultiPrintln(Serial, APP_NAME, F(" is ready."));  
}// setup


void loop() {
  app.run();
}
