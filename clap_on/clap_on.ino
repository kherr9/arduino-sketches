/*
Light It Up Sketch
*/

// 0 false; 1 true
#define debug 1

#define ledPin1 7
#define ledPin2 8
#define ledPin3 9
#define sensorPin 2

const int DialSensitivity = 150;
const int variance=100;
const int dim=600;
const int lessdim= dim+variance;
const int leastdim = lessdim+variance;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(sensorPin, INPUT);

  if(debug){
    Serial.begin(9600);
  }
}

void loop() {

    int sound = digitalRead(sensorPin);
    
    //if a sound is heard, and the LEDs are off, turn them on,
    if(sound == HIGH){
      // sound is heard
      int light = digitalRead(ledPin1);

      if(light == LOW){
        delay(250);
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
      }else{
        delay(250);
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
      }
    }
}

