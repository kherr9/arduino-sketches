#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button {
	public:
		Button(int pin);
		void update();
		void onChange(void (*)(int, int));
		void onClick(void (*)(int, int));
	private:
		int _pin;
		int _state;
		void (*_onChange)(int, int);
		void (*_onClick)(int, int);
};

#endif
