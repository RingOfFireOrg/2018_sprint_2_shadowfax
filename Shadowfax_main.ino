#include <time.h>
#include <Servo.h>
#include "ds_interface.h"
#include "Blinker.h"
#include "ServoDriveTrain.h"

#define RX_FROM_NMCU 2
#define TX_TO_NMCU 3

// ---------------------------------------------------------------------------
/* 
 * Create a Drive Station Interface "DS_Interface" object
 */
DS_Interface ds(RX_FROM_NMCU, TX_TO_NMCU);

// ---------------------------------------------------------------------------
/* Declarations to support having a remote control flashy flashyLight
 *
 * Create (instantiate) a Blinker object to blink the built in LED on pin 13
 * and a variable that let's tell the Blinker service routine how fast 
 * we want it to blink the LED.
 */
Blinker flashyLight(LED_BUILTIN);
Blinker::Speed_t speed_state = Blinker::HYPER;


// ---------------------------------------------------------------------------
/*
 * Section containing code to support driving with motors
 */

/*
 * Name the digital pins 5 & 6 for the motors/servos they represent, then create
 * an object of type ServoDriveTrain to control our servos as motors. If we use
 * the H-Bridge Shield for the gear boxes, we'll need to use a different type 
 * of drive train object.
 */
const int kPinServoLeft = 8;
const int kPinServoRight = 9;
const int kPinServoRaise = 10;
const int kPinServoArm = 11;

//Servo armRaise;
//Servo armOpen;

ServoDriveTrain drivetrain(kPinServoLeft, kPinServoRight);
// HbridgeDriveTrain drivetrain;

/*
 * Let’s start with the wheels still so it doesn’t run away
 */
ServoDriveTrain::Direction current_direction =  ServoDriveTrain::STOP;
// HbridgeDriveTrain::Direction current_direction =  HbridgeDriveTrain::STOP;

/* 
 * Arduino Setup where we initialize subsystems
 */
void setup() {
  Serial.begin(115200);
  Serial.println("Interfacing arduino with nodemcu");
  ds.init();     // setup drive station comms 
  flashyLight.init(); // setup the LED blinker
  drivetrain.init();  // setup the drive train to use the servos
  //armRaise.attach(kPinServoRaise);
  //armRaise.write(90);
  //armOpen.attach(kPinServoArm);
  //armOpen.write(90);
}

/* 
 * Arduino loop - where we get input and invoke our program’s
 * subsystems
 */
void loop() {

    char input = ds.readInputIfAvailable();
    // decide if this input should trigger a change our recorded
    // state:
    switch (input) {
      case 'f':
        speed_state = Blinker::FAST;
          //armRaise.write(45);
        break;
      case 'g':
        speed_state = Blinker::SLOW;
         //armOpen.write(150);
        break;
      case 'h':
        speed_state = Blinker::HYPER;
        break;
      case 'H': // NOTE: capital ‘H’ is different from lower ‘h’
        speed_state = Blinker::SUPERHYPER;
        break;
      case 's':
        current_direction = ServoDriveTrain::FORWARD; //BACKWARD!!
        break;
      case 'a':
        current_direction = ServoDriveTrain::RIGHT;//COUNTERCLOCKWISE
        break;
      case 'd':
        current_direction = ServoDriveTrain::LEFT;//CLOCKWISE
        break;
      case ' ':
        current_direction = ServoDriveTrain::STOP;
        break;
      case 'w':
        current_direction = ServoDriveTrain::REVERSE; //FORWARD!!
        break;
        
      default:
        /*
         * no reason to make changes to any state if there was
         * no keystroke or the keystroke was a letter we don’t
         * recognize in the list above
         */
        break;
    }

    flashyLight.service(speed_state);
    drivetrain.service(current_direction);
}