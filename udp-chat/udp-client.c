#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 
#include <string.h>

#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main()
{

    char message[1000];
   
    char buffer[100];
    int sockfd, n;
    struct sockaddr_in servaddr;

    // clear servaddr 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("25.51.174.23");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // create datagram socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // connect to server 
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }
    char* hi = "Violetta connected"; 
    sendto(sockfd, hi, MAXLINE, 0, (struct sockaddr*) NULL, sizeof(servaddr));
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) NULL, NULL);
    puts(buffer);

    while (1) {
        fgets(message, 1000, stdin);

        // request to send datagram 
        // no need to specify server address in sendto 
        // connect stores the peers IP and port 
        sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr));

        // waiting for response 
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
        puts(buffer);

        // close the descriptor 
        
    }
    close(sockfd);
    
}
