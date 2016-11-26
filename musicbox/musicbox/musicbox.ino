#include "Button.h"

const int RED_LED_PIN = 13;
const int GREEN_LED_PIN = 12;

Button button(2);

enum NoteLength {
  Eigth,
  Quarter,
  Half,
  Whole
};

enum Notes {
  A,B,C,D,E,F,G  
};

struct Note {
  NoteLength length;
  Notes note;
  
  Note(Notes note, NoteLength length){
    this->note = note;
    this->length = length;
  }
};

Note marryHadALittleLamb[] = {
  {B, Quarter},
  {A, Quarter},
  {G, Quarter},
  {A, Quarter},
  {B, Quarter},
  {B, Quarter},
  {B, Quarter},
  {A, Quarter},
  {A, Quarter},
  {A, Quarter},
  {B, Quarter},
  {D, Quarter},
  {D, Quarter},
  {B, Quarter},
  {A, Quarter},
  {G, Quarter},
  {A, Quarter},
  {B, Quarter},
  {B, Quarter},
  {B, Quarter},
  {B, Quarter},
  {A, Quarter},
  {A, Quarter},
  {B, Quarter},
  {A, Quarter},
  {G, Quarter}
};

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
