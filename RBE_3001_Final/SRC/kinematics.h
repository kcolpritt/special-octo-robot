#ifndef KINEMATICS_H_
#define KINEMATICS_H_

typedef struct {
	long theta_1;
	long theta_2;
} angles;

typedef struct {
	float X;
	float Y;
} coords;

angles inverseKinematics(double x, double y);
coords forKinematics(double theta1deg, double theta2deg);

#endif
