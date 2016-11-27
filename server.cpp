/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}
void authentication(int newsockfd)
{
	std::string message;
	char buffer[256];
	int n;
	std::cout << "Authentication starting..." << std::endl;
	message = "THIS IS SPARTA!\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd, buffer, strlen(buffer));
	if (n < 0) error("ERROR writing to socket");

	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);

	message = "HELLO!\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) error("ERROR writing to socket");

	bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);

	message = "WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) error("ERROR writing to socket");
}
void challenge(int newsockfd)
{
	std::string message;
	char buffer[256];
	int n;
	std::cout << "challenge protocol:" << std::endl;
	message = "NEW CHALLENGE 1 YOU WILL PLAY 2 MATCHES\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) error("ERROR writing to socket");
	std::cout << "buffer written to socket is:" << buffer << std::endl;

	message = "NEW CHALLENGE 1 YOU WILL PLAY 1 MATCH\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) error("ERROR writing to socket");

	message = "PLEASE WAIT FOR THE NEXT CHALLENGE TO BEGIN\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) error("ERROR writing to socket");

	message = "END OF CHALLENGES\r\n";
	bzero(buffer,256);
	message.copy(buffer, 255, 0);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) error("ERROR writing to socket");
	/*bzero(buffer,256);
	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);*/
}

void exchangeMessages(int newsockfd) {
	int count = 0;
	int n;
	std::string message;
	char buffer[256];
	std::cout<<"Client connected. Start sending messages."<<std::endl;

	authentication(newsockfd);
	// Loop to continuously get messages
	while(true) {
		// Get message
		std::cout<<"Enter Message >>";
		std::getline(std::cin, message);
		message.append("\r\n");
		std::cout<<"Verification: " <<message<<std::endl;

		// Clear buffer and insert message
		bzero(buffer, 256);
		message.copy(buffer, 255, 0);
		n = write(newsockfd, buffer, strlen(buffer));
		if (n < 0) error("Error occurred.");
		else std::cout<<"Message sent successfully. Waiting for response"<<std::endl;

		// Get message from client
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		std::cout<<"Message from client: ";
		printf("%s\n", buffer);
		if (n < 0) error("Error occurred.");
	}		
}
int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0)
			  error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
	if (newsockfd < 0)
		error("ERROR on accept");

	// Send messages betwen server and client
	exchangeMessages(newsockfd);
	
	close(newsockfd);
	close(sockfd);
	return 0;
}
