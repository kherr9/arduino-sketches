#include <usbhub.h>
#include <Wii.h>

const int BUZZER_PIN = 8;

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//WII Wii(&Btd, PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
WII Wii(&Btd); // After that you can simply create the instance like so and then press any button on the Wiimote

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

void loop() {
  Usb.Task();
  if (Wii.wiimoteConnected) {
    Wii.setLedOn(LED1);
    Wii.setLedOff(LED2);
    Wii.setLedOn(LED3);
    Wii.setLedOff(LED4);
    if(Wii.getButtonClick(LEFT)){
      tone(BUZZER_PIN, c4);  
    }
    if(Wii.getButtonClick(DOWN)){
      noTone(BUZZER_PIN);
    }
  }
}
