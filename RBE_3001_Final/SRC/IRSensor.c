/*
 * IRSensor.c
 *
 *  Created on: Feb 22, 2017
 *      Author: meghanbroughton
 */

typedef struct {
	int filter;
	int calibration;
	unsigned short currVal;
	unsigned short prevVal;
	unsigned short distance;
}  IRSensor;

typedef const struct {
	float a;
	float b;
	float c;
} calibrate;

float calcIRSensor(calibrate sensor, unsigned short adc) {
	if(adc + sensor.b <= 0) {
		return 0;
	} else {
		return 10 * (sensor.a / (adc + sensor.b) - sensor.c);  //return distance
	}
}

IRSensor senseBlock(IRSensor sensor, calibrate IR, int ADCchannel, int setPoint, int calibration) {
	unsigned short distance = 0;
	sensor.calibration = calibration;  //max distance
	sensor.currVal = calcIRSensor(IR, getADC(ADCchannel));

	if(sensor.calibration > sensor.currVal) {
		sensor.filter++;
		if(sensor.filter > setPoint){
			distance = sensor.currVal;
		}
	} else {
		sensor.filter--;
		if(sensor.filter < 0){
			sensor.filter = 1;
			distance = 0;
		}
	}

	sensor.distance = distance;

	return distance;
}





