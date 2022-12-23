#ifndef BUOY_MOTOR_H_
#define BUOY_MOTOR_H_

// initialize the motor
void init_motor();
// run motor with acceleration to a target
void motor_run();
// command motor to rotate clockwise
bool motor_clockwise();
// command motor to rotate counter-clockwise
bool motor_counterclockwise();

#endif /* BUOY_MOTOR_H_ */
