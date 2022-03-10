#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <iso646.h>



#define MAX 80
#define PORT 8080
#define SA struct sockaddr

FILE *fp;


void recup_pid() {
FILE *fp;
int pid = getpid();
char * mypid = malloc(6);   // ex. 34567
sprintf(mypid, "%d", pid);
fp = fopen("pid_serveur1.txt", "w");
fprintf(fp, "%s\n", mypid);
fclose(fp);

}


int read_PID() {
FILE *fp;
char *buff= malloc(6);
fp = fopen("pid_fd.txt", "r");
fscanf(fp, "%s", buff);
fclose(fp);
return atoi(buff);

}




// Function designed for chat between client and server.
void func(int connfd)
{
    char buff[MAX];
    int n;
    float lastvalue[10] ={0};
    int k=0;
    static float som1=0;
    static float som2=0;
    static float som3=0;
    static float moy1=0;
    static float moy2=0;
    static float moy3=0;
    static float moy=0;


    recup_pid();
     
	
    // infinite loop for chat
    for (;;) {
	

	

	
	kill(read_PID(), SIGUSR1);	
	
	fp = fopen("capteur_valeur.txt", "a");
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(connfd, buff, MAX);
	//printf("valeur con_check= %d", con_check);
	lastvalue[k]= atof(buff);
	for (int j=0; j< 10; j++) {
		som1 += lastvalue[j];
		som2 += lastvalue[j];
		moy1 = som1/10;
		moy2 = som2/10;
	}
	
	if (moy1!=moy2) {
			for (int k; k< 10; k++) {
			som3 += lastvalue[k];
			}
		moy3= som3/10;
		if (moy3 == moy1) {
		moy = moy3;
		}
		else if( moy3 == moy2) {
		moy = moy2;
		}
		else {
		// suicide
		}
	}
	else {
	moy = moy1;			
	}
	
	k++;
	if (k==9) {
	k=0;
	}	
	
        // print buffer which contains the client contents
        printf("Valeur du capteur : %s\n", buff);
	printf("moyenne: %f\n  ",moy);
	fprintf(fp, "%f\n", moy);
	fflush(stdout);
        bzero(buff, MAX);	
        // copy server message in the buffer
        //while ((buff[n++] = getchar()) != '\n')
   
        // and send that buffer to client
        //write(connfd, buff, sizeof(buff));
  	 fclose(fp);
	
	
	 
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
	    

            break;
        }

    }
}
   
// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");
   
    // lire la valeur
    func(connfd);
   


   
    // After chatting close the socket
    close(sockfd);
}
