/*
	Button.cpp - Library for handling button events.
	Created by Kevin Herr.
	Released into the public domain.
*/

#include "Arduino.h"
#include "Button.h"

void doNothing(int, int){
}

Button::Button(int pin){
	pinMode(pin, INPUT);
	_pin = pin;
	_state = LOW;
	_previousState = _state;
	_previousDebounceTime = 0;
	_debounceDelay = 50;
	onClick(doNothing);
	onChange(doNothing);
}

void Button::update(){
	
	// read the state of the switch into local variable
	int reading = digitalRead(_pin);
	unsigned long time = millis();
	
	// check to see if you pressed the button
	// (i.e. the input went from LOW to HIGH), and you've waited
	// long enough since the last press to ignore any noise:
	
	// if the switch changed, due to noise or pressing:
	if(reading != _previousState){
		// reset the debouncing timer
		_previousDebounceTime = time;
	}
	
	// if the delay is greater than debounce delay...
	// interpret as press, NOT noise
	if((millis() - _previousDebounceTime) > _debounceDelay){
		
		// if button state has changed...
		if(reading != _state){
			
			// update button state
			_state = reading;
			
			// todo: invoke methods
			onStateChange(_pin, reading);
		}
	}
	
	// save the reading. Next time through the loop,
	// it'll be the lastButtonState
	_previousState = reading;
};

void Button::onStateChange(int pin, int state){
	
	// change
	_onChange(pin, state);
	
	// click (press down)
	if(state == HIGH){
		_onClick(pin, state);
	}
}

void Button::onChange(void(*onChange)(int, int)){
	_onChange = onChange;
}

void Button::onClick(void(*onClick)(int, int)){
	_onClick = onClick;
}

