/*
* Agata
* v 1.0
* (c)25.01.2025 by sersad
*/

/*
* Board: Arduino AVR Boards / Arduino Micro (Leonardo)
*/
#include <ssBuildID.h>
#include "version.h"
#include "flashcfg.h"
#include "pinout.h"
#include "encoder.h"
#include "button.h"
#include "app.h"


Encoder encL = Encoder(ENC_L_A, ENC_L_B, ENC_L_BTN);

void setup() {
  Serial.begin(9600);
  while(!Serial);
   // Порт должен очухаться 
  for(uint8_t i = 0; i < 20; i++){
   delay(100);
   Serial.print('*');
   Serial.flush();
  }//for

  Serial.print(APP_NAME);
  Serial.print(APP_VER);
  Serial.print(APP_COPYRIGHT);
  Serial.println(APP_SERSAD);

  Serial.print(APP_BUILD_ID);
  Serial.println(BUILD_ID);

}

void loop() {
  Serial.println(encL.getDelta());
  delay(1000);
}
