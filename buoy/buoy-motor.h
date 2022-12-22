#ifndef BUOY_MOTOR_H_
#define BUOY_MOTOR_H_

// initialize the motor
void init_motor();
// resets the current position of the motor to 0
void motor_resetPosition();
// command motor to rotate clockwise
void motor_clockwise();
// command motor to rotate counter-clockwise
void motor_counterclockwise();

#endif /* BUOY_MOTOR_H_ */
