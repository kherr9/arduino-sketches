
const int RED_LED_PIN = 13;
const int BTN_PIN = 2;
int btnState = 0;

// declare type for button handler
// arg[0] - button pin
// arg[1] - button state
typedef void (*ButtonHandler)(int, int);

// declare array
ButtonHandler buttonHandlers[1];

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  buttonHandlers[0] = &updateLed;
}

void loop() {

  int tempBtnState = digitalRead(BTN_PIN);

  if(tempBtnState != btnState){
    // button state has changed

    for(int i = 0; i < 1; i++){
      ButtonHandler handler = buttonHandlers[i];
      handler(BTN_PIN, tempBtnState);
    }

    // update button state
    btnState = tempBtnState;
  }
}

void updateLed(int btnPin, int state){
  if(state == HIGH){
    digitalWrite(RED_LED_PIN, HIGH);  
  }else{
    digitalWrite(RED_LED_PIN, LOW);
  }
}
