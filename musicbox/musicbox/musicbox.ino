
const int RED_LED_PIN = 13;
const int GREEN_LED_PIN = 12;
const int BTN_PIN = 2;

// inititlize array with all 0s.
int ButtonStates[10] = { 0 };

// declare type for button handler
// arg[0] - button pin
// arg[1] - button state
typedef void (*ButtonEventHandler)(int, int);

// declare array
const int ButtonHandlersLength = 1;
ButtonEventHandler buttonHandlers[ButtonHandlersLength];

// declare array
const int ButtonClickHandlersLength = 1;
ButtonEventHandler buttonClickHandlers[ButtonClickHandlersLength];

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  buttonHandlers[0] = &updateGreenLedOnChange;
  buttonClickHandlers[0] = &updateLedOnClick;
}

void loop() {
  checkButtonState(BTN_PIN);
}

void checkButtonState(int btnPin){

  // get current button state
  int currentBtnState = digitalRead(btnPin);

  // get previous button state
  int previousBtnState = ButtonStates[btnPin];

  // if the btn state has changed...
  if(currentBtnState != previousBtnState){

    // raise state change event
    for(int i = 0; i < ButtonHandlersLength; i++){
      buttonHandlers[i](btnPin, currentBtnState);
    }

    // if button pressed...
    if(currentBtnState == HIGH){      

      // raise click event
      for(int i = 0; i < ButtonClickHandlersLength; i++){
        buttonClickHandlers[i](btnPin, currentBtnState);
      }
    }

    // update button state
    ButtonStates[btnPin] = currentBtnState;
  }
}

void updateGreenLedOnChange(int btnPin, int state){
    digitalWrite(GREEN_LED_PIN, state);
}

int ledState = LOW;
void updateLedOnClick(int btnPin, int state){
    if(ledState == LOW){
      ledState = HIGH;
    }else{
      ledState = LOW;
    }

    digitalWrite(RED_LED_PIN, ledState);
}
