#include <TimerOne.h>
#include <avr/sleep.h>

#include "game.h"
#include "Arduino.h"

static int fadeAmount = 5;
static int currIntensity = 0;

bool flagSleep = false;

int ledArray[4] = { l1, l2, l3, l4 };
int binaryArray[4] = {0, 0, 0, 0};

int generatedNumber = -1;

int current, level;
int score;
bool start, chooseLevel, levelSet, __welcome_printed, __round_started, b1Pressed;
long deltaF, roundTime, startTime;

void printBinaryArray() {
  for(int i=0; i<=3; i++) {
  	Serial.print(binaryArray[i]);
    Serial.print(" ");
  }
  
  Serial.print("\n");
}

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

void wakeUp() {
  if(flagSleep) flagSleep = false;
}

void deepSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();  
  
  sleep_disable();   
  
  Serial.println("WAKE UP");
}

// > Game
void ledSwitch(int __led) {
  digitalWrite(__led, !digitalRead(__led));
}

// > Game
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

// > Game
void b2Handler() {
  if(flagSleep) flagSleep = false;
  else if(!flagSleep && !start && !chooseLevel && levelSet) ledSwitch(l2);
}

// > Game
void b3Handler() {
  if(flagSleep) flagSleep = false;
  else if(!flagSleep && !start && !chooseLevel && levelSet) ledSwitch(l3);
}

// > Game
void b4Handler() {
  if(flagSleep) flagSleep = false;
  else if(!flagSleep && !start && !chooseLevel && levelSet) ledSwitch(l4);
}

// > Game
int writeLevel(int val) {
  return (val/256)+1;
}

// > Game
void updateRoundTimeAndScore() {
  long temp = roundTime-deltaF;
  roundTime = temp < 5000 ? 5000 : temp;
  score++;
}

// > Game
void gameOverLed() {
  digitalWrite(RED_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);
}

// > Game
void restartGame() {
  randomSeed(analogRead(0));

  current = -1;

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