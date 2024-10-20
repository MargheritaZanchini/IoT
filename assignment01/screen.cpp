#include "screen.h"
#include "game.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <LiquidCrystal_I2C.h>

static LiquidCrystal_I2C lcd(0x27, 20, 4);

void initLCD() {
  lcd.init();
  lcd.backlight();
}

// > Screen
void clearScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);

  __welcome_printed = false;
}

// > Screen
void welcomeScreen() {
  clearScreen();

  lcd.print("Welcome to GMB!");
  lcd.setCursor(0, 2);
  lcd.print("Press B1 to Start");

  __welcome_printed = true;
}

// > Screen
void updateLevelToBeChosen() {
  if(current == -1) {
    clearScreen();
    lcd.setCursor(0, 0);
    lcd.print("Choose Level: ");
    lcd.setCursor(0, 2);
    lcd.print("Press B1 to Select.");
    current = -2; // deve diventare FLAG
  }

  int newValue = analogRead(POT_PIN);
  if((newValue/256) != (current/256)) {
    current = newValue;
    lcd.setCursor(14, 0);
    lcd.print((current/256)+1);
  }

  lcd.setCursor(0, 2);
  lcd.print("Press B1 to Select.");
}

// > Screen
void chosenLevelScreen() {
  clearScreen();

  lcd.print("You Chose Level ");
  lcd.setCursor(16, 0);
  lcd.print(level);
  lcd.setCursor(0, 2);
  lcd.print("Go!");

  delay(3000);
}

// > Screen
void roundScreen() {
  clearScreen();
  lcd.print("To Convert: ");
  lcd.setCursor(12, 0);
  lcd.print(generatedNumber);

  __round_started = true;
}

// > Screen
void correctChoice() {
  clearScreen();
  turnOffLeds();
  lcd.print("GOOD!");
  lcd.setCursor(0, 2);
  lcd.print("Score:");

  lcd.setCursor(7, 2);
  lcd.print(score);

  delay(4000);
}

// > Screen
void gameOver() {
  clearScreen();
  turnOffLeds();

  lcd.print("Game Over!");
  lcd.setCursor(0, 2);
  lcd.print("Final Score:");
  lcd.setCursor(13, 2);
  lcd.print(score);

  gameOverLed();
  delay(9000);

  restartGame();
}