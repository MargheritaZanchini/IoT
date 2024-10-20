#ifndef __SCREEN_H__
#define __SCREEN_H__

// Initialize the LCD I2C Screen
void initLCD();

// Clears the Screen
void clearScreen();

// Prints the Welcome Message to Screen
void welcomeScreen();

// Prints the new Chosen Level to Screen
void updateLevelToBeChosen();

// Prints the Chosen Level Message to Screen after Setup
void chosenLevelScreen();

// Prints the Generated Random Number to Screen
void roundScreen();

// Prints the Correct Message and Player New Score
void correctChoice();

// Prints the Game Over Message and the Player Final Score
void gameOver();

#endif