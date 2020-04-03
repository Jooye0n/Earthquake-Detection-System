#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <pthread.h>


#define MAXLINE 3
#define PORT 65021

#define PIN 2 //speaker
#define SERVO1 1 //motor90
#define SERVO2 23 //motor180
#define DEV_PATH "/dev/ultra_dev"

#define IOCTL_MAGIC_NUMBER	'H'
#define IOCTL_LED_20	_IO(IOCTL_MAGIC_NUMBER, 0) //white
#define IOCTL_LED_23	_IO(IOCTL_MAGIC_NUMBER, 1) //yellow
#define IOCTL_LED_24	_IO(IOCTL_MAGIC_NUMBER, 2) //red
#define IOCTL_LED_25	_IO(IOCTL_MAGIC_NUMBER, 3) //green

int k=24;
//int check[4] = {0, 0, 0, 0};

void *t_fun1(void*data){
	
	char* thread_name = (char*)data;
	//printf("[%s]\n", thread_name);

	
	while(1){
		
	softPwmWrite(PIN, 5);
    delay(250);
	softPwmWrite(PIN, 0);
	delay(250);
	
	}
}

void *t_fun2(void*data){
	
	char* thread_name = (char*)data;
	//printf("[%s]\n", thread_name);

	
	while(1){
		
	softPwmWrite(PIN, 10);
    delay(150);
	softPwmWrite(PIN, 0);
	delay(150);
	
	}
}

void *t_fun3(void*data){
	
	char* thread_name = (char*)data;
	//printf("[%s]\n", thread_name);

	
	while(1) {
	softPwmWrite(PIN, 30);
    delay(80);
	softPwmWrite(PIN, 0);
	delay(80);
	}
}



int main(int argc, char* argv[]){
	
	int fd = open("/dev/led_dev", O_RDWR);


	//socket
	int serv_sock;
	int conn_sock;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in conn_addr;
	
	int addrlen, datalen;
	char buf[MAXLINE +1];
	
	int nbytes;
	int nport;

	char * str0 = "0";
	char * str1 = "1";
	char * str2 = "2";
	char * str3 = "3";
	
	
	
	//thread
	pthread_t p_thread[2];
	int thr_id;
	int status;
	
	char p1[] = "thread_1"; 
	char p2[] = "thread_2";
	char pM[] = "thread_m";



	//motor
	int ultra_flag =0;
	int fdultra=0;
	int ret; // return value
	float dist,s,e;
	s=0;
	e=0;

	
	wiringPiSetup();
	softPwmCreate(PIN, 0, 200);
	softPwmCreate(SERVO1, 0, 200);
	softPwmCreate(SERVO2, 0, 200);
	
		

	if((fdultra=open(DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("ultraopen");
		exit(1);
	}
	
	
	pid_t pid;
	
	if(argc == 1){
		nport = PORT;
	}else if (argc == 2){
		nport = atoi(argv[1]);
	}else{
		printf("Usage: %s <port>\n",argv[0]);
		exit(0);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(serv_sock ==-1){
		perror("socket() error!\n");
		exit(0);
	}else{
		printf("socket success\n");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(nport);
	
	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1){
		perror("bind() error\n");
		exit(0);
	}
	
	if(listen(serv_sock, 1) == -1){
		perror("listen() error\n");
		exit(0);
	}
	
	addrlen = sizeof(conn_sock);
	conn_sock = accept(serv_sock, (struct sockaddr *)&conn_addr, &addrlen);
	
	if(conn_sock == -1){
		perror("accept() error\n");
		exit(0);
	}
	
	if((pid = fork()) == -1){
		close(conn_sock);
		perror("fork() error\n");
	}else if(pid==0){
		while(1){
			fgets(buf, sizeof(buf), stdin);
			nbytes = strlen(buf);
			write(conn_sock, buf, MAXLINE);
			if(strncmp(buf,"exit",4)==0) {
				puts("exit program");
				exit(0);
			}
		}
    }else if(pid > 0){
		while(1){
			
			if((nbytes = read(conn_sock, buf, MAXLINE)) < 0){
				perror("read() error\n");
				exit(0);
			}
			
			
			//
			if(strcmp(str3, buf) == 0){ //first 3														//3
				//check[3] = 1;
				printf("level : 3\n");
				
				/*
				thr_id = pthread_create(&p_thread[2], NULL, t_fun3, (void *)pM);
				if (thr_id < 0)
				{
					perror("thread create error : ");
					return 0;
				}
				*/
				ioctl(fd, IOCTL_LED_25, 0);
				
				softPwmWrite(PIN, 80);
				delay(80);	
				
				softPwmWrite(SERVO1, 15);
				delay(300);
				
				for(;;){
					ret = write(fdultra, NULL,0);
					while(ultra_flag==0){
						ret = read(fdultra, &ultra_flag,4);
					}
					s = micros();

					while(ultra_flag == 1){
						ret = read(fdultra, &ultra_flag, 4);
					}
					e = micros();
					dist = (e-s)/58;

					
					softPwmWrite(SERVO2,k);
					
					if(dist<4.5){
						printf("distance : %f\n", dist);
						break;
					}
					delay(200);
					k--;
				}
				
				//check[3] = 0;
				//pthread_join(p_thread[2], (void **)&status);
				//softPwmWrite(PIN, 80);
				//delay(80);
				
				
				
			}
			else if(strcmp(str2, buf) == 0){ //&& check[3] == 0 ){											//2
				//check[2] = 1;	
				printf("level : 2\n");
				/*
				thr_id = pthread_create(&p_thread[1], NULL, t_fun2, (void *)p2);
				if (thr_id < 0)
				{
					perror("thread create error : ");
					return 0;
				}
				*/
				ioctl(fd, IOCTL_LED_24, 0);
				
				softPwmWrite(PIN, 40);
				delay(15);
				
				softPwmWrite(SERVO1, 15);
				delay(300);
	
				
				for(;;){
					ret = write(fdultra, NULL,0);
					while(ultra_flag==0){
						ret = read(fdultra, &ultra_flag,4);
					}
					s = micros();

					while(ultra_flag == 1){
						ret = read(fdultra, &ultra_flag, 4);
					}
					e = micros();
					dist = (e-s)/58;

					softPwmWrite(SERVO2,k);
					if(dist<4.5){
						printf("distance : %f\n",dist);
						break;
					}
					delay(200);
					k--;
				}
				
				//pthread_join(p_thread[1], (void **)&status);
				//softPwmWrite(PIN, 40);
				//delay(150);
				
				//check[2] = 0;
						
			}
			/*
			 
			  else if(strcmp(str2, buf) == 0 && check[2] == 1){
					
				printf("until 2\n");		
			}
			 */
			 
			 
			 
			 
			else if(strcmp(str1, buf) == 0 ){//&& check[2] == 0 && check[3] == 0){								///1
				//check[1] = 1;	
				printf("level : 1\n");
				
				/*
				thr_id = pthread_create(&p_thread[0], NULL, t_fun1, (void *)p1);
				if (thr_id < 0)
				{
					perror("thread create error : ");
					return 0;
				}	
				*/
				
				ioctl(fd, IOCTL_LED_23, 0);
	
	
				softPwmWrite(PIN, 5);
				delay(5);
				
				
				softPwmWrite(SERVO1, 15);
				delay(300);
				
				
				//check[1] = 0;	
				//pthread_join(p_thread[2], (void **)&status);
				//softPwmWrite(PIN, 5);
				//delay(250);
				
			}
			/*
			 * else if(strcmp(str1, buf) == 0 && check[2] == 0 && check[3] == 0 && check[1] == 1){
				printf("until 1\n");		}
			 * 
			 * 
			 */
			else if(strcmp(str0, buf) == 0){ //&& check[2] == 0 && check[3] == 0 && check[1] == 0){
				//check[0] = 1;
				printf("level : 0\n");
				ioctl(fd, IOCTL_LED_20, 0);
				softPwmWrite(PIN, 0);
				delay(10);	
				
				//check[0] = 0;
			}else{
				
				
				//printf("sdflsidjflsdijf\n");
				//printf("%s\n", buf);
			}
			
			if(strncmp(buf, "exit",4) == 0)
				exit(0);
			}
		}
	close(conn_sock);
	close(serv_sock);
	return 0;
}
