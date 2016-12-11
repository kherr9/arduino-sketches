#include <usbhub.h>
#include <Wii.h>

const int BUZZER_PIN = 4;
const int ON_LED_PIN = 6;
const int CONNECTED_LED_PIN = 5;

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd, PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
//WII Wii(&Btd); // After that you can simply create the instance like so and then press any button on the Wiimote

void setup() {
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ON_LED_PIN, OUTPUT);  
  pinMode(CONNECTED_LED_PIN, OUTPUT);

  digitalWrite(ON_LED_PIN, HIGH);
  digitalWrite(CONNECTED_LED_PIN, LOW);
}

bool toneEnabled = false;

void loop() {
  Usb.Task();
  if (Wii.wiimoteConnected) {
    //Wii.setLedOn(LED1);
    //Wii.setLedOff(LED2);
    //Wii.setLedOn(LED3);
    //Wii.setLedOff(LED4);
    //if(Wii.getButtonClick(LEFT)){
    //  tone(BUZZER_PIN, c4);  
    //}
    //if(Wii.getButtonClick(DOWN)){
    //  noTone(BUZZER_PIN);
    //}

    if(Wii.getButtonClick(B)){
      toneEnabled = !toneEnabled;
      if(toneEnabled == false){
        noTone(BUZZER_PIN);
      }
    }

    if(toneEnabled){
      // read gyro
      int pitch = Wii.getPitch();
      //Serial.println(pitch);
      // convert gyro to pitch
      // set tone
      int frequency = getFrequency(pitch);
      
      tone(BUZZER_PIN, frequency); 
    }
  }

  updateBluetoothConnectedState();
}

enum Notes {
  g3 = 196,
  a3 = 220,
  b3 = 247,
  c4 = 261,
  d4 = 294,
  e4 = 330,
  f4 = 349,
  g4 = 392 
};

// pitch will range from 0 - 360 where the apex is 180
int getFrequency(int pitch){

  /*
  Serial.print("pitch: ");
  Serial.print(pitch);
  */
  
  // shift pitch by 90
  // so that 180 is apex
  if((pitch+= 90) > 360){
    pitch-=360;
  }
  
  // 190 -> 170
  // 55 -> 55
  if(pitch > 180){
    pitch = 360 - pitch;  
  }

  /*
  Serial.print("\tval: ");
  Serial.print(pitch);
  Serial.println();
  */

  return (pitch + 100) * 3;// + 300;
  
  if(pitch > 180)
    return c4;
  else if (pitch > 90)
    return e4;
  else if (pitch > 0)
    return g4;
}

bool hasConnected = false;
void updateBluetoothConnectedState(){
  bool isConnected = Wii.wiimoteConnected;
  if(isConnected != hasConnected){
    digitalWrite(CONNECTED_LED_PIN, isConnected ? HIGH : LOW);
    hasConnected = isConnected;
    Serial.println("Bluetooth has connected");
  }  
};
