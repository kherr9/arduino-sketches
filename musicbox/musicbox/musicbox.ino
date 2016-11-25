
const int RED_LED_PIN = 13;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED_LED_PIN, HIGH);

  delay(1000);

  digitalWrite(RED_LED_PIN, LOW);

  delay(1000);
}
