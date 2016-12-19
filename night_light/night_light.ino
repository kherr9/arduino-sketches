/*
Light It Up Sketch
*/


int ledPin1=7;
int ledPin2=8;
int ledPin3=9;
int sensorPin=A0;

int variance=100;
int dim=625;
int lessdim= dim+variance;
int leastdim = lessdim+variance;

void setup() {
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(sensorPin, INPUT);

Serial.begin(9600);
    
}

void loop() {
    
    //read the amount of light in the room
    int sensorValue= analogRead(sensorPin);
    Serial.println(sensorValue);
    
    //If the room is really dark, turn on all three LEDS
    if (sensorValue<dim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
    }
    
    //if the room is a medium amount of dark, turn on two LEDs
    else if(sensorValue <lessdim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, LOW);
    }
    
    //if the room is slightly dark, just turn on one LED
     else if(sensorValue <leastdim){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
    }
    
    
    //if the room is light (or in any other case), turn all the LEDs off
    
    else{
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        
    }
    
}

