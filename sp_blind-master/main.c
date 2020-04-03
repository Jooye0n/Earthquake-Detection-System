#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <wiringPi.h>

#include "motor.h"
//header file


#define DEV_PATH1 "/dev/ledtest_dev"
#define DEV_PATH2 "/dev/button_dev"
#define DEV_PATH3 "/dev/buzzer_dev"
#define DEV_PATH4 "/dev/ultra_dev"
//device file



static int cycle;
//indicates the number of meal eaten



int main(int argc, char* argv[]){

 if(wiringPiSetup()==-1){
	printf("wiringPi Setup Error\n");
	return -1;
 }

  
 while(1){
 	
	int fdled=0,fdbutton=0,fdbuzzer=0,fdultra=0; // file descriptor
	int button_flag=0, ultra_flag=0, dist_count=0; 
 	int ret; //file function return variable
 	int lcd; //lcd variable
	float dist,s,e; s=0,e=0;// ultra sensor variable

	
	
	if((fdled=open(DEV_PATH1, O_RDWR | O_NONBLOCK)) <0){
		perror("led open()");
		exit(1);
	}// led file open(initiallized value "OFF")


	if((fdbutton=open(DEV_PATH2, O_RDWR | O_NONBLOCK))<0){
		perror("button open()");
		exit(1);
	}// button file open

	
	if((fdbuzzer=open(DEV_PATH3, O_RDWR | O_NONBLOCK))<0){
		perror("buzzer open()");
		exit(1);
	}// buzzer file open
	
	if((fdultra=open(DEV_PATH4, O_RDWR | O_NONBLOCK))<0){
		perror("ultra open()");
		exit(1);
	}// ultra sensor file open

		
 	delay(300);
	
	
 	while(1){
		ret=read(fdbutton,&button_flag,4);
		delay(10);
		if(button_flag==1)break;
	} /* button read (polling) -> BREAK if button senses pushed */

	
	printf("push!\n"); 
	button_flag=0;
	close(fdbutton); // button closed
 

	ret=write(fdled,NULL,NULL); // led ON
	
	delay(300);
	
	for(int i=0;i<1;i++) //counts time
	{
		for(int j=0;j<10;j++)
		{
			printf("time 00:00:%d%d\n",i,j);
			delay(1000);
		}
	}/*COUNT TIME*/	


	ret=write(fdbuzzer,NULL,NULL); // buzzer ON
	close(fdled); //LED closed
	
	delay(300);
	
	for(;;){ // ultra sensor cycle (polling)
		
		ret = write(fdultra,NULL,NULL);
		while(ultra_flag==0){
			ret=read(fdultra,&ultra_flag,4);
		}
	
		s=micros();

		while(ultra_flag==1){
			ret=read(fdultra,&ultra_flag,4);
		}

		e=micros();	

		dist=(e-s)/58;
		printf("distance(cm) : %f\n",dist);
		delay(1000);

		if(dist<10)dist_count++;
		if(dist_count>2)break;
	}
	

	close(fdultra);	//ultra sensor closed
	close(fdbuzzer);//buzzer closed


	
	motor(1,cycle+1);//operate servo motors
	
	
	
	cycle++;
	delay(300);

 }

 return 0;
}




