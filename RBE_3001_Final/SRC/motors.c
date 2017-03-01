/*
 * motors.c
 *
 * Created on: Feb 28, 2017
 *     Author: mebroughton
 *
 */

#include "RBELib/RBELib.h"
#include "motors.h"

/**
 * @brief Drive motors
 *
 * @param speed value between -1023 and 1023 represented by how fast the motor should be
 * @param motor value of 0 or 1
 *
 */

void driveMotor(int motor, int speed){
	if(speed > 1023){
		speed = 1023;
	}
	if(speed < -1023){
		speed = -1023;
	}
	if(speed > -30 && speed < 30){
		speed = 0;
	}
	if((speed >= 0) && (motor == uppermotor)){  //forward
		setDAC(0, speed);
		setDAC(1,0);
	}
	if((speed < 0) && (motor == uppermotor)){   //Backward
		setDAC(0,0);
		setDAC(1, -1*speed);
	}
	if((speed >= 0) & (motor == lowermotor)){
		setDAC(3, speed);
		setDAC(2, -1*speed);
	}
}




