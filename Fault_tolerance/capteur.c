#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <math.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    float sinus;
    int n;

    
    for (;;) {

	
	static int i =0; //STATIC POUR NE PAS REMETTRE A 1 A CHAQUE ITERATION
        bzero(buff, sizeof(buff));
        n = 0;
	sinus = sin(2*3.14*i/50);
	//printf("%f",&sinus);
	sprintf(buff, "%f", sinus); //valeur de sinus sur le buffer
        write(sockfd, buff, sizeof(buff)); // envoyer
	
	i++;	
	
        bzero(buff, sizeof(buff));
	
        printf("From Server : %s", buff);
	fflush(stdout);
	sleep(1);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
	
    }
}
   
int main()
{
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
}
