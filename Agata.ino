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


Encoder encL = Encoder(ENC_L_A, ENC_L_B, ENC_L_BTN, 1, 10);
Encoder encR = Encoder(ENC_R_A, ENC_R_B, ENC_R_BTN, 1, 10);


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
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_L_BTN), [](){encL.onBtn();}, CHANGE);  

  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_R_A), [](){encR.onRotate();}, CHANGE);  
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(ENC_R_BTN), [](){encR.onBtn();}, CHANGE);  

}


void loop() {
  if(encL.checkDelta()){
    Serial.print("L: ");
    Serial.println(encL.getDelta());
  }//if 

  if(encR.checkDelta()){
    Serial.print("R: ");
    Serial.println(encR.getDelta());
  }//if 

  delay(500);
}
