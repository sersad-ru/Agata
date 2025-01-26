#include "app.h"
#include <ssBuildID.h>

#define APP_DELAY_MS 100 // Задержка отработки основной логики

App::App(flashcfg* c){
  _cfg = c;
}// App


// Выполнение переодических заданий
void App::run(){
}// run


