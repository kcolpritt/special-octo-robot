#include <math.h>
#include "kinematics.h"

float map(float x, float min1, float max1, float min2, float max2){
	return (x - min1) * (max2-min2) / (max1 - min1) + min2;
}

coords linearizing(signed short xdist){
	coordinates pos;
	if(xdist < 215){
		pos.x = 235;
		pos.y = -27;
	} else if(xdist < 220){
		pos.x = 242;
		pos.y = -23;
	} else if(xdist < 225){
		pos.x = 245;
		pos.y = -20;
	} else if(xdist < 230){
		pos.x = 252;
		pos.y = -20;
	} else if(xdist < 235){
		pos.x = 260;
		pos.y = -16+10;
	} else if(xdist < 240){
		pos.x = 265;
		pos.y = -12+10;
	} else if (xdist < 245){
		pos.x = 265;
		pos.y = -10+10;
	} else if (xdist < 250){
		pos.x = 275;
		pos.y = -6;
	} else {
		pos.x = 285;
		pos.y = -10;
	}
	return pos;
