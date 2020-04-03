#include "motor.h"

const int pin = 24;
const int pin2 = 18;
static int RUN_BIT = FALSE;

int motor(int angle, int cycle){		// cycle starts from 1 to n

	if(wiringPiSetupGpio() == -1)
		return 1;

	
	softPwmCreate(pin, 0, 100);
	softPwmCreate(pin2, 0, 100);

	if((cycle%3) == 2)	//is it lunch?
		RUN_BIT = FALSE;
	else
		RUN_BIT = TRUE;

	if(angle==1){ // angle = 1, 45 degree 
		if(RUN_BIT){ // after breakfast and dinner
			softPwmWrite(pin, 24);	
			softPwmWrite(pin2, 24);	
			usleep(80000);
			softPwmWrite(pin2,0); 
			usleep(3000);		// Motor A and motor B were not perfectly synched. Motor B had to stop 3000usec prior to motor A.
			softPwmWrite(pin,0);	
		}
		else{ // after lunch
			softPwmWrite(pin, 24);
			usleep(83000);
			softPwmWrite(pin, 0);
		}
	}
	else if(angle==2){		// angle = 2, flushing the container
		softPwmWrite(pin, 24);
		softPwmWrite(pin2, 24);
		usleep(470000);
		softPwmWrite(pin, 0);
		softPwmWrite(pin2, 0);
	}
	else{
		printf("invalid input\n");
	}
	
	
	return 0;
}
