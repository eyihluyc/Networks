#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#define PORT 1111 

int main(){
	
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1){
		perror("Failure to create socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int bindCode = bind(serverSocket, (struct sockaddr *) &sa, sizeof(sa));
	if (bindCode == -1){
		perror("Failure to bind socket to port");
		exit(EXIT_FAILURE);
	}
	
	int listenCode = listen(serverSocket, 10);
	if (listenCode == -1){
		perror("Failure to start to listen on port");
		exit(EXIT_FAILURE);
	}

	for ( ; ; ){

		int connectionSocket = accept(serverSocket, NULL, NULL);
		if (connectionSocket == -1){
			perror("failure to accept connection socket");
			exit(EXIT_FAILURE);
		}

		
		char buffer[1024];
		int valread = read(connectionSocket, buffer, 1024);
		printf("%s\n", buffer);
		char* hello = "---this is server's message---\n";
		send(connectionSocket, hello, strlen(hello), 0);
		printf("Server has sent message\n");

		int shutdownCode = shutdown(connectionSocket, SHUT_RDWR);

		if (shutdownCode == -1){
			perror("shutdown failed");
			close(connectionSocket);
			close(serverSocket);
			exit(EXIT_FAILURE);
		}
		close(connectionSocket);
	}

	close(serverSocket);
	return EXIT_SUCCESS;

}
