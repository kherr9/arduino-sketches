#include "Arduino.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(int pin){
	pinMode(pin, OUTPUT);
	_pin = pin;
}

void MusicPlayer::play(Note notes[], int length){
	
	for(int i = 0; i < length; i++){
		
		Note note = notes[i];
		
		tone(_pin, note.getFrequency());
		delay(note.getDuration());
		noTone(_pin);
	}
}
