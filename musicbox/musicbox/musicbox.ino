
const int RED_LED_PIN = 13;
const int BTN_PIN = 2;
int btnState = 0;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
}

void loop() {

  int tempBtnState = digitalRead(BTN_PIN);

  if(tempBtnState != btnState){
    // button state has changed

    // delcare function pointer
    void (*functionPtr)(int);

    // assign function pointer
    functionPtr = &updateLed;

    // invoke function pointer
    (*functionPtr)(btnState);

    // update button state
    btnState = tempBtnState;
  }
}

void updateLed(int state){
  if(state == LOW){
    digitalWrite(RED_LED_PIN, HIGH);  
  }else{
    digitalWrite(RED_LED_PIN, LOW);
  }
}
