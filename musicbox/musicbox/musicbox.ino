#include "Button.h"

const int RED_LED_PIN = 13;
const int GREEN_LED_PIN = 12;
const int BUZZER_PIN = 7;

Button button(2);

enum NoteLength {
  Eigth,
  Quarter,
  Half,
  Whole
};

enum Notes {
  g3,a3,b3,c4,d4,e4,f4,g4 // middle C  
};

struct Note {
  NoteLength length;
  Notes note;
  
  Note(Notes note, NoteLength length){
    this->note = note;
    this->length = length;
  }
  
  unsigned int getFrequency(){
    switch(note){
      case g3:
        return 196;
      case a3:
        return 220;
      case b3:
        return 247;
      case c4:
        return 261;
      case d4:
        return 294;
      case e4:
        return 330;
      case f4:
        return 349;
      case g4:
        return 392;
      default:
        return 0;
    }
  }

  unsigned long getDuration(){
    long tempo = 300;
    switch(length){
      case Eigth:
        return tempo/2;
      case Quarter:
        return tempo;
      case Half:
        return tempo * 2;
      case Whole:
        return tempo * 4;
      default:
        return 0;
    }
  }
};

void play(Note notes[], int length){
  Serial.println(length);
  for(int i = 0; i < length; i++){
    play(notes[i]);
  }  
}

void play(Note note){ 
  tone(BUZZER_PIN, note.getFrequency());
  delay(note.getDuration());
  noTone(BUZZER_PIN);
}

Note maryHadALittleLamb[] = {
  {b3, Quarter},
  {a3, Quarter},
  {g3, Quarter},
  {a3, Quarter},
  {b3, Quarter},
  {b3, Quarter},
  {b3, Half},
  {a3, Quarter},
  {a3, Quarter},
  {a3, Half},
  {b3, Quarter},
  {d4, Quarter},
  {d4, Half},
  {b3, Quarter},
  {a3, Quarter},
  {g3, Quarter},
  {a3, Quarter},
  {b3, Quarter},
  {b3, Quarter},
  {b3, Quarter},
  {b3, Quarter},
  {a3, Quarter},
  {a3, Quarter},
  {b3, Quarter},
  {a3, Quarter},
  {g3, Whole}
};

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  button.onChange(onChange);
  button.onClick(onClick);
}

void loop() {
  button.update();
}

void onChange(int btnPin, int state){
  digitalWrite(GREEN_LED_PIN, state);
}

void onClick(int btnPin, int state){
  int length = sizeof maryHadALittleLamb / sizeof maryHadALittleLamb[0];
  play(maryHadALittleLamb, length);  
}

/*
int ledState = LOW;
void onClick(int btnPin, int state){
  if(ledState == LOW){
    ledState = HIGH;
  }else{
    ledState=  LOW;
  }
  digitalWrite(RED_LED_PIN, ledState);
}
*/
