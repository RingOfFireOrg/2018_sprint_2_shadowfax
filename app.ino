#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoArm;
Servo servoRaise;

const int kPinServoLeft = 7;
const int kPinServoRight = 2;
const int kPinServoArm = 3;
const int kPinServoRaise = 4;

void setup()
{
    servoLeft.attach(kPinServoLeft);
    servoRight.attach(kPinServoRight);
    servoArm.attach(kPinServoArm);
    servoRaise.attach(kPinServoRaise);
}

void loop()
{

    //if(input*){
    //}
  servoLeft.write(180);
        delay(2000);
        servoLeft.write(0);
        delay(2000);
}