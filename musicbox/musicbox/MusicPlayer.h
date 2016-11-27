#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "Arduino.h"

enum NoteLength {
  Eigth,
  Quarter,
  Half,
  Whole
};

enum Notes {
  g3 = 196,
  a3 = 220,
  b3 = 247,
  c4 = 261,
  d4 = 294,
  e4 = 330,
  f4 = 349,
  g4 = 392 
};

struct Note {
	NoteLength length;
	Notes note;
	
	Note(Notes note, NoteLength length){
		this->note = note;
		this->length = length;
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

class MusicPlayer {
	public:
		MusicPlayer(int pin);
		void play(Note notes[], int length);
	private:
		int _pin;
};

#endif