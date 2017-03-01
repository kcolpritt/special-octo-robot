/*
 * IRSensor.c
 *
 *  Created on: Feb 22, 2017
 *      Author: meghanbroughton
 */


float calcIRSensor(calibrate sensor, unsigned short adc) {
	if(adc + sensor.b <= 0) {
		return 0;
	} else {
		return 10 * (sensor.a / (adc + sensor.b) - sensor.c);  //return distance
	}
}

IRSensor senseBlock(IRSensor sensor, calibrate maxDist, int ADCchannel, int maxCount, int calibration) {
	unsigned short distance = 0;
	sensor.calibration = calibration;  //max distance
	sensor.currVal = calcIRSensor(maxDist, getADC(ADCchannel));

	if(sensor.calibration > sensor.currVal) {
		sensor.filter++;
		if(sensor.filter > maxCount){
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

	return sensor;
}





