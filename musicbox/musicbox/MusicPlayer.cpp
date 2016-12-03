#include "Arduino.h"
#include "MusicPlayer.h"

int calcLengthDuration(NoteLength length, int tempoMs){
	switch(length){
	  case Eigth:
		return tempoMs/2;
	  case Quarter:
		return tempoMs;
	  case Half:
		return tempoMs * 2;
	  case Whole:
		return tempoMs * 4;
	  default:
		return 0;
	}
}

MusicPlayer::MusicPlayer(int pin){
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void MusicPlayer::play(Note notes[], int length, int bpm){
	
	// convert bpm to ms
	int tempoMs = 60000 / bpm;
	
	for(int i = 0; i < length; i++){
		
		Note note = notes[i];
		
		tone(_pin, note.note);
		delay(calcLengthDuration(note.length, tempoMs));
		noTone(_pin);
	}
}

void MusicPlayer::update(){
	// do nothing
}
