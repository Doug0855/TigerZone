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
	// Init message and buffer
	std::string message;
	char buffer[256];
	int n;
	
	// Start Authentication protocol process
	std::cout << "Authentication starting..." << std::endl;
	message = "THIS IS SPARTA!\r\n";
	bzero(buffer,256);								// Zero buffer
	message.copy(buffer, 255, 0);					// Copy buffer into string
	n = write(newsockfd, buffer, strlen(buffer));	// Send message to server
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
// Was used to test challenge protocol, no longer used
void challenge(int newsockfd)
{
	// Init message and buffer
	std::string message;
	char buffer[256];
	int n;
	
	// Start challenge protocol simulation
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
std::string getMsg(int newsockfd)
{
	// Create buffer to read message
	char buffer[256];
	bzero(buffer, 256);

	// Get message from server
	int n = read(newsockfd, buffer, 255);
	if (n < 0){
		error("Error occured");
	}

	return std::string(buffer);

}
void exchangeMessages(int newsockfd) { //get a single message from the client
	int count = 0;
	int n;
	int waitSecond = 3;
	std::string message;
	char buffer[256];
	std::string response;
	std::cout<<"Client connected. Start sending messages."<<std::endl;

	authentication(newsockfd);
	// Loop to continuously get messages
	while(true) 
	{
		std::cout<<"Get response? (y/n)"<< std::endl;
		std::getline(std::cin, response);

		// Check if no response
		if (response.compare("") == 0)
			break;
		// Check if yes
		if (response[0] == 'y')
		{
			// Get message from client
			std::cout <<"Message from client: " << getMsg(newsockfd) << std::endl;
		} else if (response[0] == 'n'){
			// Message to send
			std::cout<<"Enter Message >>";
			std::getline(std::cin, message);
			// Add delimiter and verify message
			message.append("\r\n");
			std::cout <<"Verification: " << message << std::endl;
			if (message.compare("THANK YOU FOR PLAYING! GOODBYE\r\n") == 0){
				// Send message as usual and then break
				bzero(buffer, 256);
				message.copy(buffer, 255, 0);
				n = write(newsockfd, buffer, strlen(buffer));
				if (n < 0) error("Error occurred.");
				else std::cout<<"Message sent successfully."<<std::endl;
				break;
			}

			// Clear buffer and send message
			bzero(buffer, 256);
			message.copy(buffer, 255, 0);
			n = write(newsockfd, buffer, strlen(buffer));
			
			// Check for error
			if (n < 0) error("Error occurred.");
			else std::cout<<"Message sent successfully."<<std::endl;
		} else {
			std::cout << "ERR: input y/n" << std::endl;
		}
		if(message.compare("") == 0){
			//exit(1);
		}
		message = "";
	}
}

int main(int argc, char *argv[])
{
	// Stores info for socket connection
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	
	// Check for arguments from terminal
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	// Assign sockfd and error check
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	
	// Set serv_addr attributes and portno
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0)
			  error("ERROR on binding");
	
	// Assign newsockfd
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
	if (newsockfd < 0)
		error("ERROR on accept");

	// Send messages between server and client
	exchangeMessages(newsockfd);

	close(newsockfd);
	close(sockfd);
	return 0;
}
