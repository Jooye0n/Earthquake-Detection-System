#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXLINE 3
#define PORT 65021

int main(int argc, char* argv[]){
    int cli_sock;
    
    struct sockaddr_in serv_addr;


    char buf[MAXLINE +1];
    int nbytes;

    char* addrserv;
    int nport;

    pid_t pid;

    struct hostent *host_ent;
    

    if (argc == 1){
        nport = PORT;
    } else if (argc == 3) {
        addrserv =argv[1];
        nport = atoi(argv[2]);
    } else {
        printf("Usage: %s <server address>\n", argv[0]);
        printf("   or\nUsage: %s <server address <port>>\n", argv[0]);
        exit(0);
    }
    
    cli_sock = socket(PF_INET, SOCK_STREAM, 0);

    if (cli_sock == -1){
        perror("socket() error!\n");
        exit(0);
    }else{
        printf("socket success\n" );
    }

    //inet_ntoa(*(struct in_addr *)&ip->saddr

    //inet_aton("123.123.123.123", &inp); 
    //strcpy(buf, (char *)inet_ntoa(*(struct in_addr *)&inp)); 
    //printf("ip : %s", buf);





    // printf("3:%s", argv[1]);
    // addrserv = inet_ntoa(*(struct in_addr*)&host_ent->h_addr_list);

    struct in_addr inp;

    inet_aton("169.254.196.123", &inp); 
    addrserv = inet_ntoa(*(struct in_addr *)&inp);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(addrserv);
    serv_addr.sin_port = htons(nport);
    

    if (connect(cli_sock, (struct sockaddr*)&serv_addr,sizeof(struct sockaddr)) == -1){
        perror("connect() error\n");
        //exit(0);
        }

    
    if((pid = fork()) == -1){//error
        perror("fork() error\n");
        exit(0);
    } else if(pid ==0) {//child
        
        while(1){
            fgets(buf, sizeof(buf), stdin);
            nbytes = strlen(buf);
            write(cli_sock, buf, MAXLINE);
            if(strncmp(buf, "exit", 4) ==0) {
                puts("exit program");
                exit(0);
            }
        }
    } else if (pid > 0){//parent
        while(1){
            if((nbytes = read(cli_sock, buf, MAXLINE)) < 0){
                perror("read() error\n");
                exit(0);
            }
            if(strncmp(buf, "exit",4) == 0)
                exit(0);
        }
    }

	
    

    close(cli_sock);

    
    
    return 0;
}

