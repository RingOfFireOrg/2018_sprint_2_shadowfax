#include <Servo.h>

Servo servoLeft;
Servo servoRight;
Servo servoArm;
Servo servoRaise;

const int kPinServoLeft = 8;
const int kPinServoRight = 9;
const int kPinServoRaise = 10;
const int kPinServoArm = 11;

// pin 8 is left wheel 
// pin 9 is right wheel
// pin 10 is winch
// pin 11 is arm

buttonPressed = LOW;
buttonNotPressed = HIGH;

bool grabberClosed = false;
bool grabberRaised = true;

void setup()
{
    servoLeft.attach(kPinServoLeft);
    servoRight.attach(kPinServoRight);
    servoArm.attach(kPinServoArm);
    servoRaise.attach(kPinServoRaise);
}

void loop()
{
    //input: WASD, f = hinge and g = grabber
    //if(input*){
    //}
 /* servoLeft.write(180);
        delay(2000);
        servoLeft.write(0);
        delay(2000);
*/

/*
if(digitalRead(kPinServoArm) == buttonPressed){

    if grabberClosed = false{

        grabberClosed = true;

        servoArm.write(180);

    }


    else if grabberClosed = true{

        grabberClosed = false;

            servoArm.write(0);

    }
}

if(digitalRead(kPinServoRaise) == buttonPressed){

    if grabberRaised = false{

        grabberRaised = true;

        servoRaise.write(180);

    }


    else if grabberRaised = true{

        grabberRaised = false;

            servoRaise.write(0);

    }
}
*/





}