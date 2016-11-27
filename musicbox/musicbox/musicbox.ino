#include "Button.h"
#include "MusicPlayer.h"

const int RED_LED_PIN = 13;
const int GREEN_LED_PIN = 12;
const int BUZZER_PIN = 7;

Button button(2);
MusicPlayer musicPlayer(7);

Note arpeggio[] = {
  {c4, Quarter},
  {e4, Quarter},
  {g4, Quarter},
  {e4, Quarter},
  {c4, Half}  
};

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
  //int length = sizeof arpeggio / sizeof arpeggio[0];
  //play(arpeggio, length);  
  musicPlayer.play(arpeggio);
}

