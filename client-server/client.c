#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#define PORT 1111 

int main(){
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1){
		perror("Failure to create socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT);
	//sa.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int res = inet_pton(AF_INET, "127.0.1.1", &sa.sin_addr);

	if (res == -1){
		perror("conversion to binary failed");
		exit(EXIT_FAILURE);
	}	
	

	int connectCode = connect(clientSocket, (struct sockaddr *) &sa, sizeof(sa));
	if (connectCode == -1){
		perror("Connection failed");
		exit(EXIT_FAILURE);
	}
	
	/*recv and send*/
	char buffer[1024];
	char* hello = "---this is client's message---\n";
	send(clientSocket, hello, strlen(hello), 0);
	printf("Client has sent message\n");
	int valread = read(clientSocket, buffer, 1024);
	printf("%s\n", buffer);

	close(clientSocket);
	return EXIT_SUCCESS;

}
