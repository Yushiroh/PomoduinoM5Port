#include <Arduino.h>
#include "M5Cardputer.h"

int mainState = 0;
int timerMinutes = 0;
int workMinute = 0;
int breakMinute = 0;
int breakMinutes = 1;
int minute = 60;
int savedMinute;
int savedBreak;
int soundState = 1;

unsigned long prevMills = 0;
unsigned long timeInt = 1000;

void stateLoad( int state);
void pomoState();
void timerState();
void defState();
void runTimer();
void workTimer();
void breakSetState();
void breakTimer();

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(WHITE);
    M5Cardputer.Display.setTextDatum(middle_center);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.drawString("YushidoroM5", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    delay(1000);
    M5Cardputer.Display.clear();
    
    M5Cardputer.Speaker.setVolume(255);
    M5Cardputer.Speaker.tone(10000, 100);
    delay(1000);
    M5Cardputer.Speaker.tone(4000, 20);
    delay(1000);
    M5Cardputer.Speaker.tone(10000, 100);
    delay(1000);
    M5Cardputer.Speaker.tone(4000, 20);
    delay(1000);
    M5Cardputer.Speaker.tone(10000, 100);
    delay(1000);
    M5Cardputer.Speaker.tone(4000, 20);
    delay(1000);
}

void loop() {
    M5Cardputer.update();
    stateLoad(mainState);

}

void stateLoad(int state){
  switch (state)
  {
  case 0:
    defState();
    break;
  case 1:
    pomoState();
    break;
  
  case 2:
    timerState();
    break;

  case 3:
    runTimer();
    break;

  case 4:
    workTimer();
    break;


  case 5:
    breakSetState();
    break;


  case 6:
    breakTimer();
    break;

  default:
    break;
  }
}

void pomoState(){

    M5Cardputer.Display.setTextColor(BLUE, BLACK);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.drawString("POMO MODE", M5Cardputer.Display.width() / 2, 15);
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("Set work time (Minutes):", M5Cardputer.Display.width() / 2, 15+30);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawNumber(workMinute, M5Cardputer.Display.width() / 2, 15+15+60);

      if(workMinute >= 61 ||  workMinute < 0){
        workMinute = 0;
        M5Cardputer.Display.clear();
      }else{
      }

    if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
        M5Cardputer.Display.clear();
        mainState = 0;
      }else if(M5Cardputer.Keyboard.isKeyPressed('=')){

        M5Cardputer.Display.clear();
        workMinute += 5;

      }else if(M5Cardputer.Keyboard.isKeyPressed('-')){

        M5Cardputer.Display.clear();
        workMinute-= 5;

      }else if(M5Cardputer.Keyboard.isKeyPressed(';')){

        M5Cardputer.Display.clear();
        workMinute += 1;

      }else if(M5Cardputer.Keyboard.isKeyPressed('.')){

        M5Cardputer.Display.clear();
        workMinute -= 1;

      }else if(M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)){

        M5Cardputer.Display.clear();
        mainState = 5;
        
      }else{
      }
    }
}

void breakSetState(){

    M5Cardputer.Display.setTextColor(BLUE, BLACK);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.drawString("POMO MODE", M5Cardputer.Display.width() / 2, 15);
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("Set break time (Minutes):", M5Cardputer.Display.width() / 2, 15+30);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawNumber(breakMinute, M5Cardputer.Display.width() / 2, 15+15+60);

      if(breakMinute >= 61 ||  breakMinute < 0){
        breakMinute = 0;
        M5Cardputer.Display.clear();
      }else{
      }

    if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
        M5Cardputer.Display.clear();
        mainState = 0;
      }else if(M5Cardputer.Keyboard.isKeyPressed('=')){

        M5Cardputer.Display.clear();
        breakMinute += 5;

      }else if(M5Cardputer.Keyboard.isKeyPressed('-')){

        M5Cardputer.Display.clear();
        breakMinute-= 5;

      }else if(M5Cardputer.Keyboard.isKeyPressed(';')){

        M5Cardputer.Display.clear();
        breakMinute += 1;

      }else if(M5Cardputer.Keyboard.isKeyPressed('.')){

        M5Cardputer.Display.clear();
        breakMinute -= 1;

      }else if(M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)){

        M5Cardputer.Display.clear();
        mainState = 4;
        
      }else{
      }
    }
}

void timerState(){

    M5Cardputer.Display.setTextColor(BLUE, BLACK);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.drawString("TIMER MODE", M5Cardputer.Display.width() / 2, 15);
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("Set Timer (Minutes):", M5Cardputer.Display.width() / 2, 15+30);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawNumber(timerMinutes, M5Cardputer.Display.width() / 2, 15+15+60);

      if(timerMinutes >= 61 || timerMinutes < 0){
        timerMinutes = 0;
        M5Cardputer.Display.clear();
      }else{
      }

    if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
        M5Cardputer.Display.clear();
        mainState = 0;
      }else if(M5Cardputer.Keyboard.isKeyPressed('=')){

        M5Cardputer.Display.clear();
        timerMinutes += 5;

      }else if(M5Cardputer.Keyboard.isKeyPressed('-')){

        M5Cardputer.Display.clear();
        timerMinutes -= 5;

      }else if(M5Cardputer.Keyboard.isKeyPressed(';')){

        M5Cardputer.Display.clear();
        timerMinutes += 1;

      }else if(M5Cardputer.Keyboard.isKeyPressed('.')){

        M5Cardputer.Display.clear();
        timerMinutes -= 1;

      }else if(M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)){

        M5Cardputer.Display.clear();
        mainState = 3;
        
      }else{
      }
    }
}

void defState(){

    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.setTextColor(BLUE, BLACK);
    M5Cardputer.Display.drawString("Select Mode:", M5Cardputer.Display.width() / 2, 15 + 30);
    M5Cardputer.Display.drawString("1 Pomodoro Mode", M5Cardputer.Display.width() / 2, 45 + 30);
    M5Cardputer.Display.drawString("2 Timer Mode", M5Cardputer.Display.width() / 2, 45 + 25 + 30 );

    if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed('1')){
        M5Cardputer.Display.clear();
        mainState = 1;
      }else if(M5Cardputer.Keyboard.isKeyPressed('2')){
        M5Cardputer.Display.clear();
        mainState = 2;
      }
    }
}

void runTimer() {

  unsigned long cMills = millis();

  if (cMills - prevMills >= timeInt) {
    M5Cardputer.Display.drawNumber(timerMinutes, M5Cardputer.Display.width() / 2, 30);
    M5Cardputer.Display.drawNumber(minute, M5Cardputer.Display.width() / 2, 80);
    prevMills = cMills;
    minute--;

    if ((minute < 0 && timerMinutes > 0) || minute == 60) {

      minute = 59;
      timerMinutes--;
      Serial.println(timerMinutes);
    } else if (minute < 0 && timerMinutes == 0) {

      M5Cardputer.Speaker.tone(10000, 100);
      delay(1000);
      M5Cardputer.Speaker.tone(4000, 20);
      delay(1000);
      M5Cardputer.Speaker.tone(10000, 100);
      delay(1000);
      M5Cardputer.Speaker.tone(4000, 20);
      delay(1000);

      minute = 60;

      M5Cardputer.Display.clear();
      mainState = 0;


      Serial.println("TIMER_DONE!");
    }
  }

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
             M5Cardputer.Display.clear();
             mainState = 0;
      }
  }

}


void workTimer() {

  unsigned long cMills = millis();

  if (cMills - prevMills >= timeInt) {
    M5Cardputer.Display.setTextColor(YELLOW,BLACK);
    M5Cardputer.Display.drawNumber(workMinute, M5Cardputer.Display.width() / 2, 30);
    M5Cardputer.Display.drawNumber(minute, M5Cardputer.Display.width() / 2, 80);
    prevMills = cMills;
    minute--;

    if ((minute < 0 && workMinute > 0) || minute == 60) {

      minute = 59;
      workMinute--;
    } else if (minute < 0 && workMinute == 0) {


      minute = 60;

      M5Cardputer.Display.clear();
      mainState = 6;


      Serial.println("TIMER_DONE!");
    }
  }

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
             M5Cardputer.Display.clear();
             mainState = 0;
      }
  }
}


void breakTimer() {

  unsigned long cMills = millis();

  if (cMills - prevMills >= timeInt) {
    M5Cardputer.Display.setTextColor(YELLOW,BLACK);
    M5Cardputer.Display.drawNumber(breakMinute, M5Cardputer.Display.width() / 2, 30);
    M5Cardputer.Display.drawNumber(minute, M5Cardputer.Display.width() / 2, 80);
    prevMills = cMills;
    minute--;

    if ((minute < 0 && breakMinute > 0) || minute == 60) {

      minute = 59;
      breakMinutes--;
    } else if (minute < 0 && breakMinute == 0) {


      minute = 60;

      M5Cardputer.Display.clear();
      mainState = 0;


      Serial.println("TIMER_DONE!");
    }
  }

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
             M5Cardputer.Display.clear();
             mainState = 0;
      }
  }
}