#include "RBELib/RBELib.h"


int main(void) {
	IRSensor sensor1;
	IRSensor sensor2;
	sensor1.distance = 0;
	sensor2.distance = 0;
	int flag1;
	int flag2;
	signed short dist = 0;
	signed short dist1 = 0;
	signed short dist2 = 0;


	while(1){

		sensor1 = senseBlock(sensor1, IR, /*ADCChannel*/, 20, 220);
		sensor2 = senseBlock(sensor2, IR, /*ADCChannel*/, 20, 220);

		if((sensor1.distance != 0) && (flag1 == 0)) {
			flag1 = 1;
			dist1 = sensor1.distance;
		}
		if((sensor2.distance != 0) && (flag2 == 0)) {
			flag2 = 1;
			dist2 = sensor2.distance;
		}
		if((dist1 != 0) && (dist2 != 0)){
			dist = (dist1 + dist2) / 2;
		}

		return dist;
	}
}
