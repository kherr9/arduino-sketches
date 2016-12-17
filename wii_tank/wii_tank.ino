    /* Ardumoto Example Sketch
  by: Jim Lindblom
  date: November 8, 2013
  license: Public domain. Please use, reuse, and modify this 
  sketch!

  Three useful functions are defined:
    setupArdumoto() -- Setup the Ardumoto Shield pins
    driveArdumoto([motor], [direction], [speed]) -- Drive [motor] 
      (0 for A, 1 for B) in [direction] (0 or 1) at a [speed]
      between 0 and 255. It will spin until told to stop.
    stopArdumoto([motor]) -- Stop driving [motor] (0 or 1).

  setupArdumoto() is called in the setup().
  The loop() demonstrates use of the motor driving functions.
*/

#include <usbhub.h>
#include <Wii.h>

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
// Don't change these! These pins are statically defined by shield layout
//const byte PWMA = 3;  // PWM control (speed) for motor A
//const byte PWMB = 11; // PWM control (speed) for motor B
//const byte DIRA = 12; // Direction control for motor A
//const byte DIRB = 13; // Direction control for motor B

// when hit wired with usb shield
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 5; // PWM control (speed) for motor B
const byte DIRA = 2; // Direction control for motor A
const byte DIRB = 4; // Direction control for motor B

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd, PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
//WII Wii(&Btd); // After that you can simply create the instance like so and then press any button on the Wiimote

void setup()
{
  
  Serial.begin(9600);

  setupWiimote();
  setupArdumoto(); // Set all pins as outputs
  delay(5000);
}

bool enabled = false;

void loop(){
  Usb.Task();

  if (Wii.wiimoteConnected) {

    if(enabled){
    
      int val = Wii.getRoll();
  
      // clamp val 90 <= x <= 270
      if(val > 270){
        val = 270;
      }else if(val < 90){
        val = 90;
      }
  
      // -90 <= x <= 90
      val = val - 180;
  
      // -100 <= x <= 100
      val = val * 100 / 90; 
  
      // make bigger stable state
      if(val < 15 && val > -15){
        val = 0;  
      }
  
      Serial.print("speed: ");
      Serial.print(val);
      Serial.println();
  
      if(val == 0){
        stopArdumoto(MOTOR_A);
        stopArdumoto(MOTOR_B);
      }else{
        val = val * 2;
        if(val > 0){
          // forward
          driveArdumoto(MOTOR_A, CW, val);
          driveArdumoto(MOTOR_B, CW, val);
        }else{
          // backwards
          val = val * -1;
          Serial.println(val);
          driveArdumoto(MOTOR_A, CCW, val);
          driveArdumoto(MOTOR_B, CCW, val);
        }
      }
          
    }else{
      
    }

    if (Wii.getButtonClick(A)) {
      enabled = !enabled;
      Serial.print("Enabled: ");
      Serial.print(enabled);
      Serial.println();  
    }
    
  }else{
    stopArdumoto(MOTOR_A);
    stopArdumoto(MOTOR_B);  
  }
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

void setupWiimote(){
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  
  //pinMode(BUZZER_PIN, OUTPUT);
  //pinMode(ON_LED_PIN, OUTPUT);  
  //pinMode(CONNECTED_LED_PIN, OUTPUT);

  //digitalWrite(ON_LED_PIN, HIGH);
  //digitalWrite(CONNECTED_LED_PIN, LOW);
}  
