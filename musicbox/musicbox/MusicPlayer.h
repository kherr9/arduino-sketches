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
};

class MusicPlayer {
	public:
		MusicPlayer(int pin);
		void play(Note notes[], int length, int bpm);
		void update();/*
		bool isPlaying();
		void stop();*/
	private:
		int _pin;
		Note* _notes;
		int _notesLength;
		int _bpm;
		int _tempoMs;
		int _noteIndex;
		unsigned long _nextTime;
		bool _isPlaying;
		void nextNote();
};

#endif