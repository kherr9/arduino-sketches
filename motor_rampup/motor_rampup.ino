#include <SparkFun_TB6612.h>

// Basic sketch for trying out the Adafruit DRV8871 Breakout

#define AIN1 2
#define AIN2 4
#define PWMA 5
#define STBY 9

#define BIN1 3
#define BIN2 8
#define PWMB 6


// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = -1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
////Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
////Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

Motor motor1 = Motor(2, 4, 3, offsetA, STBY);
Motor motor2 = Motor(5, 10, 6, offsetB, STBY);

void setup() {
  Serial.begin(9600);
  Serial.println("DRV8871 test");

  delay(5000);
}

void loop() {
  
  int rpm = 100;//255;
  int sleep = 2000;

  // fwd
  motor1.drive(rpm);
  motor2.drive(rpm);
  delay(sleep);

  brake(motor1, motor2);
  delay(10);

  // bwd
  motor1.drive(rpm * -1);
  motor2.drive(rpm * -1);
  delay(sleep);

  brake(motor1, motor2);
  delay(10);

  // left
  motor1.drive(rpm);
  motor2.drive(rpm * -1);
  delay(sleep);
  
  brake(motor1, motor2);
  delay(10);

  // right
  motor1.drive(rpm * -1);
  motor2.drive(rpm);
  delay(sleep);
  
  brake(motor1, motor2);
  delay(10);

  delay(3000);
}
