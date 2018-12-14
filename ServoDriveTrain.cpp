#include "ServoDriveTrain.h"

#include <math.h>

/*
 * Name the servo speeds for full speed forward and REVERSE
 * Remember that the Left servo is reversed because it mounted
 * mirror image to the right servo, so needs to spin in the opposite 
 * direction for the same effect. It might be smarter to wrap the 
 * servos in a "motor" class that has an "invert()" function, 
 * but this will do for now. Just allways use a constant ending
 * in "_R" for the right servo and one ending in "_L" for the left
 * servo.
 */ 
// right servo:
#define SERVO_FWD_R 180
#define SERVO_REV_R 0
// left servo:
#define SERVO_FWD_L 0 
#define SERVO_REV_L 180
// they  both "stop" in the same direction. :-)
#define SERVO_STOP 90


/*
 * Constructor to create a new drivetrain object
 * leftPin - the index of the DIO pin delivering PWM signal to the left servo
 * rightPin - the index of the DIO pin delivering PWM signal to the right servo
 */
ServoDriveTrain::ServoDriveTrain(int leftPin, int rightPin) {
    left_motor_pin = leftPin;
    right_motor_pin = rightPin;
}

/*
 * A destructor so the compiler has instructions for how to clean up
 * when a ServoDriveTrain object is destroyed. Program should never
 * invoke in directly.
 */
ServoDriveTrain::~ServoDriveTrain() {
    left_motor_pin = 0;
    right_motor_pin = 0;
    current_direction = STOP;
}

/*
 * init()
 * This function should be called from the arduino "setup()" function
 */
void ServoDriveTrain::init() {
    left_motor.attach(left_motor_pin);
    right_motor.attach(right_motor_pin);
    current_direction = STOP;
    service(current_direction);
}

/*
 * service()
 * Call this function to change the state of the servos. Pass in a Direction
 * wayToGo - is the direction you'd like the robot to go, inlcuding "ServoDriveTrain::STOP"
 */
void ServoDriveTrain::service(ServoDriveTrain::Direction wayToGo) {
    switch(wayToGo) {
        case FORWARD:
            left_motor.write(SERVO_FWD_L);
            right_motor.write(SERVO_FWD_R);
            current_direction = wayToGo;
            break;
        case REVERSE:
            left_motor.write(SERVO_REV_L);
            right_motor.write(SERVO_REV_R);
            current_direction = wayToGo;
            break;
        case LEFT:
            left_motor.write(SERVO_REV_L);
            right_motor.write(SERVO_FWD_R);
            current_direction = wayToGo;
            break;
        case RIGHT:
            left_motor.write(SERVO_FWD_L);
            right_motor.write(SERVO_REV_R);
            current_direction = wayToGo;
            break;
        case STOP:
            left_motor.write(SERVO_STOP);
            right_motor.write(SERVO_STOP);
            current_direction = wayToGo;
            break;
    }
}

#define MAX_SPEED_OFFSET 90 // max speed is either 180 or 0 both 90 away from "stop"

int compute_servo_angle(float input) {
    if (fabs(input) > 1) {
        input = (input > 0 ? 1.0 : -1.0);
    }
    /* how to think about this
     * the input is a number between -1.0 and 1.0. 
     * i.e. the input is a fraction with an absolute value lower than 1.
     * The offset from 90 (stopped) we need must be some fraction of 
     * 90 (since we can only go 90 away from stopped max speeds are 0 and 180).
     * If we multiply a fraction of 1 times 90, we'll get a number between
     * 0 and 90 with a sign that means if we add it to 90, it'll be that much
     * below or above 90, which makes it the number we need.
     */
    int speed = input * MAX_SPEED_OFFSET + SERVO_STOP;
    return (speed);
}

/*
 * setMotorsDirectly is a way to have direct control of each motor's speed
 */
void ServoDriveTrain::setMotorsDirectly(float left_speed, float right_speed) {
    // computer angle value between 0 and 180 for each servo
    /*
     * we invert the left result because we invert the left wheel everywhere
     */
    int left_angle = compute_servo_angle(left_speed);
    left_angle = left_angle * (-1);

    int right_angle = compute_servo_angle(right_speed);

    if (left_speed > right_speed) {
        current_direction = ServoDriveTrain::RIGHT;
    } else if (right_speed > left_speed) {
        current_direction = ServoDriveTrain::LEFT;
    } if (left_speed > 0.0) {
        current_direction = ServoDriveTrain::FORWARD;
    } if (left_speed < 0.0) {
        current_direction = ServoDriveTrain::REVERSE;
    } else {
        current_direction = ServoDriveTrain::STOP;
    }
    left_motor.write(-1 * left_angle); 
    right_motor.write(right_angle);
}

ServoDriveTrain::Direction ServoDriveTrain::getCurrentDirection() {
    return (current_direction);
}