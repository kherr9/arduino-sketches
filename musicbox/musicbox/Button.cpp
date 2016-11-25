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
	onClick(doNothing);
	onChange(doNothing);
}

void Button::update(){
	int currentState = digitalRead(_pin);
	
	// if state has changed...
	if(currentState != _state){
		
		_onChange(_pin, currentState);
		
		// click event
		if(currentState == HIGH){
			_onClick(_pin, currentState);
		}
		
		_state = currentState;
	}
	
};

void Button::onChange(void(*onChange)(int, int)){
	_onChange = onChange;
}

void Button::onClick(void(*onClick)(int, int)){
	_onClick = onClick;
}

