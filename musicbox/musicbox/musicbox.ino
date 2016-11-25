#include "Button.h"

const int RED_LED_PIN = 13;
const int GREEN_LED_PIN = 12;

Button button(2);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  button.onChange(onChange);
  button.onClick(onClick);
}

void loop() {
  button.update();
}

void onChange(int btnPin, int state){
  digitalWrite(GREEN_LED_PIN, state);
}

int ledState = LOW;
void onClick(int btnPin, int state){
  if(ledState == LOW){
    ledState = HIGH;
  }else{
    ledState=  LOW;
  }
  digitalWrite(RED_LED_PIN, ledState);
}
