
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
    if(btnState == LOW){
      // button down
      // turn on led
      digitalWrite(RED_LED_PIN, HIGH);
    }else{
      // button up
      // turn off led
      digitalWrite(RED_LED_PIN, LOW);
    }
    
    btnState = tempBtnState;
  }
}
