/*
 * Kinematics_.c
 *
 *  Created on: Feb 27, 2017
 *      Author: meghanbroughton
 */

typedef struct {
	long theta_1;
	long theta_2;
} angles;

typedef struct {
	float X;
	float Y;
} coords;

const double length0;
const double length1;
const double length2;

coords position;
float theta1, theta2, theta1_1, theta1_2, theta2_1, theta2_2, invTheta1Rad, invTheta1Deg, invTheta2Rad, invTheta2Deg;


coords forKinematics(double theta1deg, double theta2deg) {
	theta1 = (theta1deg * M_PI) / 180; //convert to radian
	theta2 = (theat2deg * M_PI) / 180; //convert to radian

	position.X = length1 * cos(theta1) + length2 * cos(theta1) * cos(theta2) - length2 * sin(theta1) * sin(theta2);  //forward kinematics for x
	position.Y = length0 + length1 * sin(theta1) + length2 * cos(theta1) * sin(theta2) + length2 * sin(theta1) * cos(theta2); //forward kinematics for y

	return position;
}

angles inverseKinematics(double x, double y) {
	theta1_2 = (x * (length1 + length2 * cos(theta2)) + (y * length2 * sin(theta2)))/ (pow(x, 2) + pow(y, 2));
	theta1_1 = sqrt(1-pow(theta1_2, 2));

	angles invAngles;

	invTheta1Rad = atan2(-theta1_1, theta1_2);
	invTheta1Deg = (invTheta1Rad * 180) / M_PI;
	invAngles.theta_1 = invTheta1Deg;

	theta2_2 = (pow(x,2) + pow(y,2) - pow(length1, 2) - pow(length2, 2)) / (2 * length1 * length2);
	theta2_1 = sqrt(1 - pow(theta2_2,2));

	invTheta2Rad = atan2(-theta2_1, theta2_2);
	invTheta2deg = (invTheta2Rad * 180) / M_PI;
	invAngles.theta_2 = invTheta2Deg;

	return invAngles;
}




