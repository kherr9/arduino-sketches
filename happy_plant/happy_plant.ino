#include <LedControl.h>

LedControl lc = LedControl(12, 10, 11, 1);

// delay between sensor measurements and 
// frame delay
unsigned long delayTime = 200;

int moistureSensor = A0;
int moisture;
// change this value depending on plant type
// or sensitivity needed
int okay_soil_moisture = 650;
int happy_soil_moisture = 500;

// put LED displays in arrays
byte happy[]={
    B00001000,
    B11000100,
    B11000010,
    B00010010,
    B00010010,
    B11000010,
    B11000100,
    B00001000
};

byte okay[]={
    B00000010,
    B11000010,
    B11000010,
    B00010010,
    B00010010,
    B11000010,
    B11000010,
    B00000010
};

byte sad[]={
    B00000001,
    B11000010,
    B11000100,
    B00010100,
    B00010100,
    B11000100,
    B11000010,
    B00000001
};

void setup() {
  lc.shutdown(0, false); // wakup display
  lc.setIntensity(0, 5); // display brightness
  lc.clearDisplay(0); // clear display

  Serial.begin(9600);
}

void loop() {
  // read the soil moisture level
  // if the soil has enough moisture, make a happy face
  // otherwise, make a sad face

  moisture = analogRead(moistureSensor);

  Serial.println(moisture);

  if(moisture <= happy_soil_moisture){
    writeLedControl(happy);
  }else if(moisture <= okay_soil_moisture){
    writeLedControl(okay);
  }else{
    writeLedControl(sad);
  }

  delay(delayTime);
}

void writeLedControl(byte matrix[]){
  for(int i = 0; i < 8; i++){
    lc.setRow(0, i, matrix[i]);
  }
}

