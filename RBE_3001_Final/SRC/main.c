
/* main.c
 *
 *  Created on: August 20, 2016
 *      Author: Joe st. Germain
 */


#include "RBELib/RBELib.h"
//For use of abs()
#include <stdlib.h>


//character for receiving serial data
char inchar;
unsigned long lowADC = 0;
unsigned long highADC = 0;
unsigned long pot1Ang=0;
unsigned long potAngInt;
unsigned long mV=0;
volatile unsigned long systemTime = 0;
volatile unsigned long timerCounter;
volatile unsigned long intTime;
volatile double timerCountVal = 9; //9 for ms system time
volatile long highLinkErr;
volatile long lowLinkErr;

volatile int highSetP;
volatile int lowSetP;

volatile int offSetlow = 250;
volatile double adctoanglelow = 3.66;

volatile int offSethigh = 250;
volatile double adctoanglehigh = 4.16;
/*
 * Timer 0 ISR triggered on overflow
 */

// Takes in angle and returns adc value for lower link 0-180
int angleToADCLow(int angle)
{
	//double offsetadclow = angle + offSetlow ;
	double adclow =  ( angle * adctoanglelow)+ offSetlow;

	return adclow;
}

// Takes in angle and returns adc value for higher link 0-180
int angleToADCHigh(int angle)
{
	//double offsetadclow = angle + offSetlow ;
	double adchigh =  ( angle * adctoanglehigh)+ offSethigh;

	return adchigh;
}


void updatePIDLink(char link,int setPoint)
{
switch(link){
case 'H':
	//1000 to 250
	if (FALSE){
		setDAC(2, 0);
		setDAC(3, 0);
	}
	else{
		long pidNum = calcPID('H', setPoint, getADC(3));
		//printf("H \n\r");
		//printf(" ADC: %d,Set: %d",getADC(3),setPoint);
		//printf(" PId: %ld, \n\r",pidNum);
		if (pidNum >= 0){
			setDAC(2, pidNum);
			setDAC(3, 0);
		}
		else{
			setDAC(2,0);
			setDAC(3, -pidNum);
		}
	}
	break;
case 'L':
	//1000 to 250
	if (FALSE){
		setDAC(0, 0);
		setDAC(1, 0);
	}
	else{
		long pidNum = calcPID('L', setPoint, getADC(2));
		//printf("L \n\r");
		//printf(" ADC: %d,Set: %d",getADC(2),setPoint);
		//printf(" PId: %ld, \n\r",pidNum);
		if (pidNum >= 0)		{
			setDAC(0, 0);
			setDAC(1, pidNum);
		}
		else{
			setDAC(0,-pidNum);
			setDAC(1, 0);
		}
	}
	break;
	}
}


ISR(TIMER0_OVF_vect)
{
	timerCounter++;
	//counts to make 1ms timer
	if (timerCounter >=timerCountVal)
	{
	//Port C pin 0 flip for prelab part 8
	//PORTC ^= (1 << 0);
	timerCounter=0;
	systemTime++;
	intTime++;
	// sets 100 hz
	if (intTime>=10)
	{
		 // updatePIDLink('H',calcPID('H',90,getADC(2)));
		 // updatePIDLink('L',calcPID('L',90,getADC(3)));
		updatePIDLink('H',highSetP);
		updatePIDLink('L',lowSetP);
		  printf("Accel X 0: %d\n\r",GetAccelerationH48C(0));
		  printf("Accel Y 1: %d\n\r",GetAccelerationH48C(1));
		  printf("Accel Z 2: %d\n\r",GetAccelerationH48C(2));
	}
	}

}

int main(void)
{
	  //Enable printf() and setServo()
	  initRBELib();
	  /*
	  // Write the USARTDebug.c file using the function prototypes in the H file to enable the usart
	  //Set the baud rate of the UART
	  debugUSARTInit(115200);
	  initADC(0);
	  initSPI();
	  // printf uses a fair amount of memory to be included but makes serial printing much easier
	  printf("PutCharDebug is complete \n\r");

	  // Runs once per ms
	  //Also runs PID once per 100 ms
	  initTimer(0, 0, 0);
	  //Set PID constants
	  setConst('H',20.0,0.01,0.1);
	  setConst('L',20.0,0.01,0.1);
	  */

	  Link upper_link
	  Link lower_link
	  IRSensor sensor1;
	  IRSensor sensor2;
	  sensor1.distance = 0;
	  sensor2.distance = 0;

	  signed short distance1 = 0,

	  const int theta1Start = 90;
	  const int theta2Start = 90;
	  int flag1;
	  int flag2;


	  typedef enum {
		  Start, Sense, MoveArm, Grab, LiftBlock, Weigh;
	  } sort_blocks;

	  while(1)
	  {


/*
		  //PID run in interupt
		  lowSetP=angleToADCLow(0);
		  highSetP=angleToADCHigh(90);

		  printf("adcL: %d\n\r",lowSetP);
		  printf("adcH: %d \n\r",highSetP);
		  _delay_ms(2000);




		  lowSetP=angleToADCLow(90);
		  highSetP=angleToADCHigh(0);
		  printf("adcL: %d\n\r",lowSetP);
		  printf("adcH: %d\n\r",highSetP);

		  _delay_ms(2000);
*/
		  while(flag) {

			  flag = 0;

			  switch(sort_blocks) {

			  case Start:
				  setServo(/*pin, value*/); //run conveyor
				  //set links to start positions
				  sort_blocks = Sense;
				  break;
			  }

			  case Sense:
				  sensor1 = senseBlock(sensor1, IR, /*ADCChannel, setPoint, calibration*/);
				  sensor2 = senseBlock(sensor2, IR, /*ADCChannel, setPoint, calibration*/);

				  if((sensor1.distance != 0) && (flag1 == 0)) {
					  flag1 = 1;
					  dist1 = sensor1.distance;
				  }
				  if((sensor2.distance != 0) && (flag2 == 0)) {
					  flag2 = 1;
					  dist2 = sensor2.distance;
				  }
				  if((dist1 != 0) && (dist2 != 0)){
					  distance = (dist1 + dist2) / 2;
					  sort_blocks = /*next case*/;
				  } else {
					  sort_blocks = Sense;
				  }
				  break;

			  case MoveArm:
				  //use inverse kinematics to find angles
				  //move arm to this position
				  //determine error
				  sort_blocks = Grab;
				  break;

			  case Grab:
				  setServo(/*pin, speed*/); //Close the Gripper
				  move_blocks = LiftBlock;
				  break;

			  case LiftBlock:
				  setServo(/*pin, speed*/); //close gripper
				  //move arm to specified position
				  //determine error
				 sort_blocks = Weigh;
				 break;

			  case Weigh:
				  for(i=0, i<1000, i++){
					  //apply torque large enough to move small block but too small to move large block
					  //find position of upper link (getADC())
					  // if(arm doesn't move) block = heavy
					  //if(arm does move) block = light
				  }
				  sort_blocks = Sort;
				  break;

			  case Sort:
				  //if(block == heavy) move to heavy spot
				  //if(block == light) move to light spot



		  }

	  }
}




