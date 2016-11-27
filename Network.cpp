#include "Network.h"

Client::Client(std::string hostname, std::string port)
{
    portno = stoi(port);
    server = gethostbyname(hostname.c_str());
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
}
Client::~Client()
{

}

void Client::connectToServer()
{
  int tmp = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
  if (tmp < 0)
      error("ERROR connecting");
  else
      fprintf(stdout, "Connected to Server successfully!\n");
}
void Client::sendMessage(std::string message)
{
  bzero(buffer,256);
  message.copy(buffer, 255, 0);
  //fgets(buffer,255,stdin);
  n = write(sockfd,buffer,strlen(buffer));
  if (n < 0)
       error("ERROR writing to socket");
}
std::string Client::receiveMessage()
{
  std::string message;
  bzero(buffer,256);
  n = read(sockfd,buffer,255);
  if (n < 0)
       error("ERROR reading from socket");
  else
        message = buffer;
  return message;
}
void Client::closeConnection()
{
  close(sockfd);
  fprintf(stdout, "Connection to Server terminated by the Client!\n");
}
void Client::error(const char *msg)
{
    perror(msg);
    exit(0);
}
