#include <avr/sleep.h>
#include <LiquidCrystal_I2C.h>

#include "Arduino.h"

#include "screen.h"
#include "game.h"

// The Liquid Crystal I2C Screen
static LiquidCrystal_I2C lcd(0x27, 20, 4);

void initLCD() {
  lcd.init();
  lcd.backlight();
}

void clearScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
}

void welcomeScreen() {
  clearScreen();

  lcd.print("Welcome to GMB!");
  lcd.setCursor(0, 2);
  lcd.print("Press B1 to Start");

  __welcome_printed = true;
}

void updateLevelToBeChosen() {
  if(current == -256) {
    clearScreen();
    lcd.setCursor(0, 0);
    lcd.print("Choose Level: ");
    lcd.setCursor(0, 2);
    lcd.print("Press B1 to Select.");
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

void chosenLevelScreen() {
  clearScreen();

  lcd.print("You Chose Level ");
  lcd.setCursor(16, 0);
  lcd.print(level);
  lcd.setCursor(0, 2);
  lcd.print("Go!");

  delay(3000);
}

void roundScreen() {
  clearScreen();
  lcd.print("To Convert: ");
  lcd.setCursor(12, 0);
  lcd.print(generatedNumber);

  __round_started = true;
}

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