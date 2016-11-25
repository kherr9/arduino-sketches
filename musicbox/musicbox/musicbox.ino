
const int RED_LED_PIN = 13;
const int BTN_PIN = 2;
int btnState = 0;

// declare type for button handler
// arg[0] - button pin
// arg[1] - button state
typedef void (*ButtonHandler)(int, int);
// arg[0] - button pin
typedef void (*ButtonClickHandler)(int);

// declare array
const int ButtonHandlersLength = 0;
ButtonHandler buttonHandlers[1];

// declare array
const int ButtonClickHandlersLength = 1;
ButtonClickHandler buttonClickHandlers[ButtonClickHandlersLength];

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  buttonClickHandlers[0] = &updateLedOnClick;
}

void loop() {

  int tempBtnState = digitalRead(BTN_PIN);

  // button down event or up event
  if(tempBtnState != btnState){
    // button state has changed

    // state change
    for(int i = 0; i < ButtonHandlersLength; i++){
      ButtonHandler handler = buttonHandlers[i];
      handler(BTN_PIN, tempBtnState);
    }

    // click
    if(tempBtnState == HIGH){      
      // button clicked
      for(int i = 0; i < ButtonClickHandlersLength; i++){
        buttonClickHandlers[i](BTN_PIN);
      }
    }

    // update button state
    btnState = tempBtnState;
  }
}

int ledState = LOW;
void updateLedOnClick(int btnPin){
    if(ledState == LOW){
      ledState = HIGH;
    }else{
      ledState = LOW;
    }

    digitalWrite(RED_LED_PIN, ledState);
}
