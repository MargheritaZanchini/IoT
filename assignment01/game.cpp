#include <TimerOne.h>
#include <avr/sleep.h>

#include "Arduino.h"

#include "game.h"

static int fadeAmount = 5; // Fade Step Amount 
static int currIntensity = 0; // Current Red LED Intensity

bool flagSleep = false;

int ledArray[4] = { l1, l2, l3, l4 };
int binaryArray[4] = { 0, 0, 0, 0 };

int generatedNumber = -1;

int current, level;
int score;
bool start, chooseLevel, levelSet, __welcome_printed, __round_started, b1Pressed;
long deltaF, roundTime, startTime;

bool checkPlayerBinaryInput() {
  for(int i=0; i<=3; i++) {
    if(digitalRead(ledArray[i]) != binaryArray[i])
      return false;
  }
  return true;
}

void turnOffLeds() {
  for(int i=0; i<=3; i++) {
  	digitalWrite(ledArray[i], LOW);
  }
}

void resetBinaryArray() {
  for(int i=3; i>=0; i--) {
  	binaryArray[i] = 0;
  }
}

// Convert Decimal to Binary Array
bool cd2ba(int __dec) {
  resetBinaryArray();
  
  if(__dec < 0 || __dec > 15) return false;
  
  int remainder = 0;
  for(int i=3; i>=0; i--) {
  	remainder = __dec%2;
  	__dec = __dec/2;
  	binaryArray[i] = remainder;
  }
  
  return true;
}

void fade() {
  analogWrite(RED_LED_PIN, currIntensity);
  currIntensity = currIntensity + fadeAmount;
  if (currIntensity == 0 || currIntensity == 255) {
    fadeAmount = -fadeAmount;
  }
  delay(15);
}

void setFlagSleep() {
  flagSleep = !flagSleep;
  
  if(flagSleep) digitalWrite(RED_LED_PIN, LOW);
}

void deepSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();  
  
  sleep_disable();   
  
  Serial.println("WAKE UP");
}

void ledSwitch(int __led) {
  digitalWrite(__led, !digitalRead(__led));
}

void b1Handler() {
  if(chooseLevel) b1Pressed = true;
  else if(start) {
    if(flagSleep) flagSleep = false;
    else {
      Timer1.detachInterrupt();
      Timer1.stop();
      chooseLevel = true;
      start = false;
    }
  }
  else if(!chooseLevel && levelSet) {
    ledSwitch(l1);
  }
}

void b2Handler() {
  if(flagSleep) flagSleep = false;
  else if(!flagSleep && !start && !chooseLevel && levelSet) ledSwitch(l2);
}

void b3Handler() {
  if(flagSleep) flagSleep = false;
  else if(!flagSleep && !start && !chooseLevel && levelSet) ledSwitch(l3);
}

void b4Handler() {
  if(flagSleep) flagSleep = false;
  else if(!flagSleep && !start && !chooseLevel && levelSet) ledSwitch(l4);
}

int writeLevel(int val) {
  return (val/256)+1;
}

void updateRoundTimeAndScore() {
  long temp = roundTime-deltaF;
  roundTime = temp < 5000 ? 5000 : temp;
  score++;
}

void gameOverLed() {
  digitalWrite(RED_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);
}

void restartGame() {
  randomSeed(analogRead(0));

  current = -256; // Initialized as -1 for First Use

  __welcome_printed = false;
  __round_started = false;

  chooseLevel = false;
  levelSet = false;

  level = 0;
  deltaF = 0;

  score = 0;
  startTime = 0;
  roundTime = 15000;
  b1Pressed = false;
  
  start = true;

  Timer1.attachInterrupt(setFlagSleep);
  Timer1.start();

  Serial.println("[GMTBC] Game Restarted");

  flagSleep = false;
}

int getGameState() {
  if(start) {
    return flagSleep ? STATE_SLEEPING : STATE_SETUP_GAME;
  }
  if(chooseLevel) {
    if (!b1Pressed) {
      return STATE_CHOOSING_LEVEL;
    }
    if (b1Pressed && !levelSet) {
      return STATE_SETUP_LEVEL;
    }
  }
  else if(!chooseLevel && levelSet) {
    return STATE_PLAYING;
  }
}