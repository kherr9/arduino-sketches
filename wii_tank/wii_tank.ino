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

#define MOTOR_A 0
#define MOTOR_B 1

const int STBY = 9;

// Motor A
const int PWMA = 3; // speed control
const int AIN1 = 2; // direction
const int AIN2 = 4; // direction

// Motor B
const int PWMB = 6; // speed control
const int BIN1 = 5; // direction
const int BIN2 = 10; // direction

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
}

bool enabled = false;

void loop(){
  Usb.Task();

  Serial.println("start");
  move(1, 255, 1); //motor 1, full speed, left
  move(2, 255, 1); //motor 2, full speed, left
  Serial.println("end");
  delay(2000);
  
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
        stop();
        stop();
      }else{
        val = val * 2;
        if(val > 0){
          // forward
          move(MOTOR_A, CW, val);
          move(MOTOR_B, CW, val);
        }else{
          // backwards
          val = val * -1;
          Serial.println(val);
          move(MOTOR_A, CCW, val);
          move(MOTOR_B, CCW, val);
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
    stop();  
  }
}

void move(int motor, int direction, int speed)
{
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop()
{
  //enable standby  
  digitalWrite(STBY, LOW); 
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
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
