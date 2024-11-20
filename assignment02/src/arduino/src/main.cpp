#include <Arduino.h>

#define LED_PIN 9 //selecting the pin we want to work with, in this case, where is the led

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT); //we say it's an outup
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Acceso");
  digitalWrite(LED_PIN, HIGH); //we turn on the led at the pin 13, we put 5 volt into that pin
  delay(1000);
  digitalWrite(LED_PIN, LOW); //turn off the pin
  Serial.println("Spento");
  delay(1000);
  

  //the led will blick every second

}
