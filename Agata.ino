/*
* Agata
* v 1.0
* (c)25.01.2025 by sersad
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

#include "cmd.h"

#define arraySize(_array) ( sizeof(_array) / sizeof(*(_array)) )

// Энкодеры
Encoder encL = Encoder(ENC_L_A, ENC_L_B, ENC_L_BTN, 1, 10);
Encoder encR = Encoder(ENC_R_A, ENC_R_B, ENC_R_BTN, 1, 10);

// Кнопки
Button buttons[] = {Button(KEY_1), Button(KEY_2), Button(KEY_3), Button(KEY_4), Button(KEY_5), Button(KEY_6)};


CMD cmd = CMD(Serial);

void setup() {
  Serial.begin(9600);
  while(!Serial);

   // Порт должен очухаться 
  for(uint8_t i = 0; i < 20; i++){
   delay(100);
   Serial.print('*');
   Serial.flush();
  }//for
  ssMultiPrintln(Serial, "\n", APP_NAME, APP_VER, APP_COPYRIGHT, APP_SERSAD);
  ssMultiPrintln(Serial, APP_BUILD_ID, BUILD_ID);

  // Развешивать обработчики прерываний приходится тут и через лямбду :(
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_L_A), [](){encL.onRotate();}, CHANGE);  
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_R_A), [](){encR.onRotate();}, CHANGE);  

}

CMDKey key;
CMDEnc enc;

void loop() {
  for(uint8_t i = 0; i < arraySize(buttons); i++){
    buttons[i].run();
    if(buttons[i].wasChanged()){
      ssMultiPrintln(Serial, F("Key["), i, F("]: "), buttons[i].getPressed());
    }//if
  }//for

  if(encL.checkDelta()){
    Serial.print("L: ");
    Serial.println(encL.getDelta());
  }//if 

  if(encR.checkDelta()){
    Serial.print("R: ");
    Serial.println(encR.getDelta());
  }//if 

  cmd.run();
  if(cmd.hasNewCommand()){
    ssMultiPrintln(Serial, F("New command: "), cmd.getLastCommand(), F(" args: \""), cmd.getLastArgs(), "\"");
    if(cmd.getLastCommand() == CMD_ERROR){
      ssMultiPrintln(Serial, F("Error in command: \""), (char*)(cmd.getLastArgs() - 1), "\"");
    }//if

    if(cmd.getLastCommand() == CMD_KEY){
      ssMultiPrintln(Serial, F("Key -> "), cmd.parseKey(key));
      ssMultiPrintln(Serial, F("Key num: "), key.num, F(" Key value: "), key.val);
    }//if

    if((cmd.getLastCommand() == CMD_LEFT) || (cmd.getLastCommand() == CMD_RIGHT)){
      ssMultiPrintln(Serial, F("Enc -> "), cmd.parseEnc(enc));
      ssMultiPrintln(Serial, F(" With: "), enc.withBtn, F(" Without: "), enc.withoutBtn);
    }//if

  }//if
  //delay(500);
}
