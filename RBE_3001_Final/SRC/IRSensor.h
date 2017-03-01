#ifndef IRSENSOR_H_
#define IRSENSOR_H_

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

float calcIRSensor(calibrate sensor, unsigned short adc);
IRSensor senseBlock(IRSensor sensor, calibrate maxDist, int ADCchannel, int maxCount, int calibration);

#endif
