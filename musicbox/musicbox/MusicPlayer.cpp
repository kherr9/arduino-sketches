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
	_notes = notes;
	_notesLength = length;
	_bpm = bpm;
	_tempoMs = 60000 / bpm;
	_noteIndex = -1;
	_isPlaying = true;
}

void MusicPlayer::update(){
	if(_isPlaying && millis() > _nextTime){
		nextNote();
	}
}

void MusicPlayer::nextNote(){
	_noteIndex++;
	
	if(_noteIndex < _notesLength){
		// play note
		Note note = _notes[_noteIndex];
		tone(_pin, note.note);
		
		// save note length
		int noteLength = calcLengthDuration(note.length, _tempoMs);
		_nextTime = millis() + noteLength;
	}else{
		// end of song
		noTone(_pin);
		_isPlaying = false;
	}
}
