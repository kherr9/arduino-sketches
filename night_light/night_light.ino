/*
Light It Up Sketch
*/

// 0 false; 1 true
#define debug 1

#define ledPin1 7
#define ledPin2 8
#define ledPin3 9
#define sensorPin A0
#define dialPin A1

const int DialSensitivity = 150;
const int variance=100;
const int dim=625;
const int lessdim= dim+variance;
const int leastdim = lessdim+variance;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(dialPin, INPUT);

  if(debug){
    Serial.begin(9600);
  }
}

void loop() {
    
    // read the amount of light in the room
    // returns value from 0 - 1023
    unsigned int sensorValue= analogRead(sensorPin);
    unsigned int dialValue = analogRead(dialPin);
    int offset = ((long)dialValue * DialSensitivity / 1023) - (DialSensitivity / 2);
    unsigned int adjustedSensorValue = sensorValue + offset;

    if(debug){
      Serial.print(sensorValue);
      Serial.print("\t");
      Serial.print(adjustedSensorValue);
      Serial.print("\t");
      Serial.print(dialValue);
      Serial.print("\t");
      Serial.println(offset);
    }
    
    // If the room is really dark, turn on all three LEDS
    if (adjustedSensorValue<dim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
    }
    // if the room is a medium amount of dark, turn on two LEDs
    else if(adjustedSensorValue <lessdim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, LOW);
    }
    // if the room is slightly dark, just turn on one LED
     else if(adjustedSensorValue <leastdim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
    }
    // if the room is light (or in any other case), turn all the LEDs off
    else{
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW); 
    }
}

// 0 <= value <= 1023
int getOffset(int value){
  
}

