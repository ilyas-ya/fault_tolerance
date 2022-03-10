#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void recup_pid() {


	FILE *fp;
	int pid = getpid();
	char * mypid = malloc(6);   // ex. 34567
	sprintf(mypid, "%d", pid);
	fp = fopen("pid_fd.txt", "w");
	fprintf(fp, "%s\n", mypid);
	fclose(fp);
}



char* read_PID() {
	FILE *fp;
	char *buff= malloc(6);
	fp = fopen("pid_serveur1.txt", "r");
	fscanf(fp, "%s", buff);
	fclose(fp);

	return buff;

}

void my_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("Received SIGUSR1!\n");
    }
}




void func(int sockfd)
{
	


   
    char* buff;

    char* msg_start= "s" ;
    int n;
    int compteur=0;
    int check=0;
    int cm=0;

    while(1) {



	



	signal(SIGUSR1, my_handler);
	/*
	fflush(stdout);
        printf("From Server : %s", buff);
	fflush(stdout);
	
	
	if(buff == "a") {
	compteur++;
	}
	if (check == compteur) {
	cm++;
	}
	else {
	check = compteur;
	}

	if( cm == 10) {
	//write(sockfd, buff, sizeof(char));
	}


        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }

	*/

	
    }
}
   
int main()
{
     recup_pid();


   /*
    int sockfd, connfd;
    struct sockaddr_in server, cli;
   
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( PORT );

    //Connect to remote server
    if (connect(sockfd , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    
    puts("Connected\n");
    
    // Function for chatting between client and server
    func(sockfd);
   
    // After chatting close the socket
    close(sockfd);
	*/
	    while(1) {

	signal(SIGUSR1, my_handler);

	}
}
