/*
Light It Up Sketch
*/


const int ledPin1=7;
const int ledPin2=8;
const int ledPin3=9;
const int sensorPin=A0;

const int variance=100;
const int dim=625;
const int lessdim= dim+variance;
const int leastdim = lessdim+variance;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(sensorPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
    
    // read the amount of light in the room
    // returns value from 0 - 1023
    int sensorValue= analogRead(sensorPin);
    Serial.println(sensorValue);
    
    // If the room is really dark, turn on all three LEDS
    if (sensorValue<dim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
    }
    // if the room is a medium amount of dark, turn on two LEDs
    else if(sensorValue <lessdim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, LOW);
    }
    // if the room is slightly dark, just turn on one LED
     else if(sensorValue <leastdim){
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

