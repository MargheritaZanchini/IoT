#ifndef __GAME_H__
#define __GAME_H__

#define l1 13
#define l2 12
#define l3 11
#define l4 10

#define RED_LED_PIN 6

#define POT_PIN A0

extern int ledArray[4];
extern int binaryArray[4];

extern int generatedNumber;

extern bool flagSleep;

extern int current, level;

extern int score;

extern bool start, chooseLevel, levelSet, __welcome_printed, __round_started, b1Pressed;

extern long deltaF, roundTime, startTime;

void fade();

void setFlagSleep();

void wakeUp();

void deepSleep();

void printBinaryArray();

bool checkPlayerBinaryInput();

void turnOffLeds();

void resetBinaryArray();

// Convert Decimal to Binary Array
bool cd2ba(int __dec);

void ledSwitch(int __led);

void b1Handler();

void b2Handler();

void b3Handler();

void b4Handler();

int writeLevel(int val);

void updateRoundTimeAndScore();

void gameOverLed();

void restartGame();

#endif