/*
  Assignment 01 - Give me the Binary Code!

  Margherita Zanchini: margherita.zanchini@studio.unibo.it
  Sofia Caberletti: sofia.caberletti@studio.unibo.it
  Marco Marrelli: marco.marrelli@studio.unibo.it
*/

#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <avr/sleep.h>

#include "game.h"
#include "screen.h"

#define __MILLISECONDS 1000
#define __MICROSECONDS 1000000

#define WAITING_TIME 10 * __MICROSECONDS
#define INITIAL_ROUND_TIME 15 * __MILLISECONDS
#define MINIMUM_ROUND_TIME 5 * __MILLISECONDS

#define b1 5
#define b2 4
#define b3 3
#define b4 2

void setup(){  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(b1,INPUT);
  enableInterrupt(b1, b1Handler, FALLING);

  pinMode(b2, INPUT);
  enableInterrupt(b2, b2Handler, FALLING);
  
  pinMode(b3, INPUT);
  enableInterrupt(b3, b3Handler, FALLING);
  
  pinMode(b4, INPUT);
  enableInterrupt(b4, b4Handler, FALLING);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);

  pinMode(RED_LED_PIN, OUTPUT); 

  turnOffLeds();

  initLCD();

  Timer1.initialize(WAITING_TIME);
  restartGame();
}

void loop(){
  if(start) {
    if(!__welcome_printed) {
      welcomeScreen();
    }

    fade();

    if(flagSleep) {
      clearScreen();
      deepSleep();
    }
  }
  if(chooseLevel) {
    if (!b1Pressed) {
      if(digitalRead(RED_LED_PIN) == HIGH) digitalWrite(RED_LED_PIN, LOW);
      updateLevelToBeChosen();
    }
    if (b1Pressed && !levelSet) {
      level = writeLevel(analogRead(POT_PIN));
      deltaF = level*500;
      chosenLevelScreen();

      levelSet = true;
      chooseLevel = false;
    }
  }
  else if(!chooseLevel && levelSet) {
    if(!__round_started) {
      generatedNumber = random(0, 16);
      roundScreen();
      startTime = millis();
    }
    if(millis() - startTime > roundTime) {
      if(!cd2ba(generatedNumber)) return;

      if(checkPlayerBinaryInput()) {
        updateRoundTimeAndScore();
        correctChoice();
        
        __round_started = false;
      }
      else gameOver();
    }
  }
}
