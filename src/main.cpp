#include <Arduino.h>
#include "M5Cardputer.h"
#include <M5GFX.h>

int mainState = 0;
int timerMinutes = 0;
int workMinute = 0;
int breakMinute = 0;
int minute = 59;
int savedMinute;
int savedBreak;
int soundState = 1;
int masterVolume = 50;
int volumeLevel = 0;

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
void beepTone(int toneVal, int volume);
void resetParams();
void postSesh();
void postTimer();

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


  case 7:
    postSesh();
    break;


  case 8:
    postTimer();
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

    M5Cardputer.Display.setFont(&fonts::FreeSansBold9pt7b);
    M5Cardputer.Display.setTextColor(RED, BLACK);
    M5Cardputer.Display.drawString("^/v  = 1            +/- = 5", M5Cardputer.Display.width()/2, 15+20+25+25+35);

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
        workMinute = workMinute > 0 ? workMinute - 1 : workMinute;
        savedMinute = workMinute;
        mainState = 5;
        
      }else{
      }
    }
}

void breakSetState(){

    M5Cardputer.Display.setTextColor(GREEN, BLACK);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.drawString("POMO MODE", M5Cardputer.Display.width() / 2, 15);
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("Set break time (Minutes):", M5Cardputer.Display.width() / 2, 15+30);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawNumber(breakMinute, M5Cardputer.Display.width() / 2, 15+15+60);

    M5Cardputer.Display.setFont(&fonts::FreeSansBold9pt7b);
    M5Cardputer.Display.setTextColor(RED, BLACK);
    M5Cardputer.Display.drawString("^/v  = 1            +/- = 5", M5Cardputer.Display.width()/2, 15+20+25+25+35);
    
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
        breakMinute = breakMinute > 0 ? breakMinute - 1 : breakMinute;
        savedBreak = breakMinute;
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

    M5Cardputer.Display.setFont(&fonts::FreeSansBold9pt7b);
    M5Cardputer.Display.setTextColor(RED, BLACK);
    M5Cardputer.Display.drawString("^/v  = 1            +/- = 5", M5Cardputer.Display.width()/2, 15+20+25+25+35);

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
        timerMinutes = timerMinutes > 0 ? timerMinutes - 1 : timerMinutes;
        mainState = 3;
        
      }else{
      }
    }
}

void defState(){

    M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
    M5Cardputer.Display.setTextColor(BLUE, BLACK);
    M5Cardputer.Display.drawString("Select Mode:", M5Cardputer.Display.width()/2, 15+20);
    M5Cardputer.Display.drawString("1 Pomodoro Mode", M5Cardputer.Display.width()/2,15+20+25);
    M5Cardputer.Display.drawString("2 Timer Mode", M5Cardputer.Display.width()/2, 15+20+25+25);

    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.setTextColor(RED, BLACK);
    M5Cardputer.Display.drawString("Volume(^/v):", 80, 15+20+25+25+35);
    M5Cardputer.Display.drawNumber(volumeLevel, 160, 15+20+25+25+35);

    volumeLevel = (volumeLevel > 5 || volumeLevel < 1) ? volumeLevel = 1 : volumeLevel;

    if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed('1')){
        M5Cardputer.Display.clear();
        beepTone(3,volumeLevel);
        mainState = 1;
      }else if(M5Cardputer.Keyboard.isKeyPressed('2')){
        M5Cardputer.Display.clear();
        beepTone(3,volumeLevel);
        mainState = 2;
      }else if(M5Cardputer.Keyboard.isKeyPressed(';')){
        volumeLevel+=1;
        beepTone(3,volumeLevel);
      }else if(M5Cardputer.Keyboard.isKeyPressed('.')){
        volumeLevel-=1;
        beepTone(3,volumeLevel);
      }
    }
}

void runTimer() {
  unsigned long cMills = millis();
  if (cMills - prevMills >= timeInt) {
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("Timer running...", M5Cardputer.Display.width() / 2,20);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawString(":", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    M5Cardputer.Display.drawNumber(timerMinutes, (M5Cardputer.Display.width() / 2) - 40, M5Cardputer.Display.height() / 2);
    M5Cardputer.Display.setTextPadding(50);
    M5Cardputer.Display.drawNumber(minute, (M5Cardputer.Display.width() / 2) + 40, M5Cardputer.Display.height() / 2);
    prevMills = cMills;
    minute--;

    if ((minute < 0 && timerMinutes > 0) || minute == 60){
        minute = 59;
        timerMinutes--;
        Serial.println(timerMinutes);
    }else if(minute < 0 && timerMinutes == 0) {
      M5Cardputer.Display.clear();
      mainState = 8;
    }

    if(M5Cardputer.Keyboard.isChange()){
        if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
              M5Cardputer.Display.clear();
              resetParams();
              mainState = 0;
        }
    }
  }
}

void workTimer() {
  
  unsigned long cMills = millis();
  if (cMills - prevMills >= timeInt) {
    M5Cardputer.Display.setTextColor(YELLOW,BLACK);
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("WORK TIME!", M5Cardputer.Display.width() / 2,20);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawString(":", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    M5Cardputer.Display.drawNumber(workMinute, (M5Cardputer.Display.width() / 2) - 40, M5Cardputer.Display.height() / 2);
    M5Cardputer.Display.setTextPadding(50);
    M5Cardputer.Display.drawNumber(minute, (M5Cardputer.Display.width() / 2) + 40, M5Cardputer.Display.height() / 2);
    prevMills = cMills;
    minute--;
    if ((minute < 0 && workMinute > 0) || minute == 60) {
      minute = 59;
      workMinute--;
    } else if (minute < 0 && workMinute == 0) {
      minute = 59;
      beepTone(2,volumeLevel);
      M5Cardputer.Display.clear();
      mainState = 6;
    }
  }

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
            resetParams();
             M5Cardputer.Display.clear();
             mainState = 0;
      }
  }
}



void breakTimer() {

  unsigned long cMills = millis();
  if (cMills - prevMills >= timeInt) {
    M5Cardputer.Display.setTextColor(GREEN,BLACK);
    M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
    M5Cardputer.Display.drawString("Break time!", M5Cardputer.Display.width() / 2,20);
    M5Cardputer.Display.setFont(&fonts::FreeSansBold24pt7b);
    M5Cardputer.Display.drawString(":", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    M5Cardputer.Display.drawNumber(breakMinute, (M5Cardputer.Display.width() / 2) - 40, M5Cardputer.Display.height() / 2);
    M5Cardputer.Display.setTextPadding(50);
    M5Cardputer.Display.drawNumber(minute, (M5Cardputer.Display.width() / 2) + 40, M5Cardputer.Display.height() / 2);
    prevMills = cMills;
    minute--;
    if ((minute < 0 && breakMinute > 0) || minute == 60) {

      minute = 59;
      breakMinute--;
    } else if (minute < 0 && breakMinute == 0) {
      minute = 59;
      M5Cardputer.Display.clear();
      mainState = 7;
    }
  }

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
             M5Cardputer.Display.clear();
             resetParams();
             mainState = 0;
      }
  }
}

void postSesh(){

  M5Cardputer.Display.setTextColor(YELLOW,BLACK);
  M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
  M5Cardputer.Display.drawString("Session Finished!", M5Cardputer.Display.width() / 2,20);
  M5Cardputer.Display.drawString("Press Space to Continue", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);

  beepTone(1,volumeLevel);

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
             M5Cardputer.Display.clear();
             resetParams();
             mainState = 0;
      }else if(M5Cardputer.Keyboard.isKeyPressed(' ')){
             M5Cardputer.Display.clear();
             workMinute = savedMinute;
             breakMinute = savedBreak;
             mainState = 4;
      }
  }
}

void postTimer(){

  M5Cardputer.Display.setTextColor(YELLOW,BLACK);
  M5Cardputer.Display.setFont(&fonts::FreeSans9pt7b);
  M5Cardputer.Display.drawString("Timer Finished!", M5Cardputer.Display.width() / 2,20);
  M5Cardputer.Display.drawString("Press del to exit", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);

  beepTone(1,volumeLevel);

  if(M5Cardputer.Keyboard.isChange()){
      if(M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)){
             M5Cardputer.Display.clear();
             resetParams();
             mainState = 0;
      } 
    }
}

void beepTone(int toneVal, int volume){

  switch (volume)
  {

  case 1:
    M5Cardputer.Speaker.setVolume(0);
    break;
  
  case 2:
    M5Cardputer.Speaker.setVolume(50);
    break;
  
  case 3:
    M5Cardputer.Speaker.setVolume(100);
    break;
  
  case 4:
    M5Cardputer.Speaker.setVolume(150);
    break;
  
  case 5:
    M5Cardputer.Speaker.setVolume(250);
    break;
  
  default:
    break;
  }
  switch (toneVal)
  {
  case 1:
    M5Cardputer.Speaker.tone(4000, 100);
    delay(300);
    M5Cardputer.Speaker.tone(4000, 100);
    delay(500);
    M5Cardputer.Speaker.tone(4000, 100);
    delay(300);
    M5Cardputer.Speaker.tone(4000, 100);
    delay(500);
    break;

  case 2:
    M5Cardputer.Speaker.tone(4000, 100);
    delay(300);
    M5Cardputer.Speaker.tone(4000, 100);
    delay(500);
    break;

  case 3:
    M5Cardputer.Speaker.tone(4000, 100);
    delay(300);
    break;

  default:
    break;
  }
}

void resetParams(){

  mainState = 0;
  timerMinutes = 0;
  workMinute = 0;
  breakMinute = 0;
  minute = 59;

}
