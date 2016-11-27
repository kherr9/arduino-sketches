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
  g3,a3,b3,c4,d4,e4,f4,g4  
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

class MusicPlayer {
	public:
		MusicPlayer(int pin);
		void play(Note notes[], int length);
	private:
		int _pin;
};

#endif