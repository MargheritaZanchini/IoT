#ifndef __GAME_H__
#define __GAME_H__

#define __MILLISECONDS 1000 // Milliseconds Value Converter
#define __MICROSECONDS 1000000 // Microseconds Value Converter

#define WAITING_TIME 10 * __MICROSECONDS // Waiting Time Before Deep Sleep (10seconds)
#define INITIAL_ROUND_TIME 15 * __MILLISECONDS // Initial Round Time (15seconds)
#define MINIMUM_ROUND_TIME 5 * __MILLISECONDS // Minimum Round Time (5seconds)

#define b1 5 // Most Significant Binary - Button Pin
#define b2 4
#define b3 3
#define b4 2 // Least Significant Binary - Button Pin

#define l1 13 // Most Significant Binary - LED Pin
#define l2 12
#define l3 11
#define l4 10 // Least Significant Binary - LED Pin

#define RED_LED_PIN 6 // Red LED Pin

#define POT_PIN A0 // Potentiometer Pin

// Game States Enumeration
enum GameState { STATE_SETUP_GAME, STATE_CHOOSING_LEVEL, STATE_SETUP_LEVEL, STATE_PLAYING, STATE_SLEEPING };

extern int ledArray[4]; // LED Array
extern int binaryArray[4]; // Binary Array used in Checks and Convertions

extern int
  generatedNumber, // Random Generated Number
  current, // Current Value of the Potentiometer
  level, // Current Selected Level
  score; // Current Player Score

extern bool
  flagSleep, // Deep Sleep Status - Flag
  start, // If Game Started - Flag
  chooseLevel, // If Player Choosing Level - Flag
  levelSet, // If Level is Set - Flag
  __welcome_printed, // If Welcome Screen was Printed - Flag
  __round_started, // If Round has Started - Flag
  b1Pressed; // If Button 1 was Pressed - Flag

extern long
  deltaF, // Reducing Factor of Round Time (level-based calculated)
  roundTime, // Round Time
  startTime; // Starting Round Time

// Makes the Red LED Fade
void fade();

// Invert the Sleep Flag
void setFlagSleep();

// Set Arduino in Deep Sleep
void deepSleep();

// Checks the Player Binary LEDs Input
bool checkPlayerBinaryInput();

// Turn off all the Binary LEDs
void turnOffLeds();

// Resets the Binary Array (used to check player input)
void resetBinaryArray();

// Convert Decimal to Binary Array
bool cd2ba(int __dec);

// Switchs the Array
void ledSwitch(int __led);

// Button 1 Handler
void b1Handler();

// Button 2 Handler
void b2Handler();

// Button 3 Handler
void b3Handler();

// Button 4 Handler
void b4Handler();

// Transform Potentiometer Value into Readable Level
int writeLevel(int val);

// Updates Round Time and Player Score
void updateRoundTimeAndScore();

// Activates the Game Over Red LED
void gameOverLed();

// Restart the Game (initializes the variables)
void restartGame();

// Returns the Game State for the Game Loop
int getGameState();

#endif