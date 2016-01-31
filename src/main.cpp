#include "Arduino.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int zeroPin = 6;
const int onePin = 7;

int prevZeroState = 0;
int prevOneState = 0;

String binary = "";
int calculated = 0;

void updateWith(int zeroOrOne) {
  lcd.clear();
  binary.concat(zeroOrOne);
  lcd.setCursor(0, 0);
  lcd.print(binary);
  calculated = calculated << 1;
  calculated |= (zeroOrOne << 0);
  lcd.setCursor(0, 1);
  lcd.print(calculated);
}

bool buttonPressed(int &previousState, int state) {
  if(previousState != state) {
    previousState = state;
    return state == LOW ? true : false;
  }
  return false;
}

void setup() {
  lcd.begin(16, 2);
  pinMode(zeroPin, INPUT);
  pinMode(onePin, INPUT);
  lcd.print("Enter Number");
}

void loop() {
  if(buttonPressed(prevZeroState, digitalRead(zeroPin))) {
    updateWith(0);
  }

  if(buttonPressed(prevOneState, digitalRead(onePin))) {
    updateWith(1);
  }
}
