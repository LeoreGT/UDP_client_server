#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>

void Run();

/* ---------------------------------- */

int main()
{
  Run();
  return 0;
}

/* ---------------------------------- */

/* Function creates the serverside socket with loopback ip address and port number (same as client)
 * Prints questions from clientside with recvfrom
 * User inputs answer to be sent to the serverside, sent with the sendto function
 * Once there is another question from clientside, is read with recvfrom and printed
 */

void Run()
{
  struct sockaddr_in serverSide, clientAddr;
  struct sockaddr_storage serverStorage;
  char question[1024];
  char response[1024];
  int newSocket, sizeMessage;
  socklen_t addr_size, client_addr_size;
  int i;

  newSocket = socket(PF_INET, SOCK_DGRAM, 0); //create the socket

  serverSide.sin_family = AF_INET;
  serverSide.sin_port = htons(1024); //port number
  serverSide.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP address (loopback)
  memset(serverSide.sin_zero, 0, sizeof(serverSide.sin_zero)); //set to 0 for not junk

  bind(newSocket, (struct sockaddr *) &serverSide, sizeof(serverSide));

  addr_size = sizeof(serverStorage);

  while(1)
  {
    sizeMessage = recvfrom(newSocket,question,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

    printf("Received: %s",question);

    printf("Please respond: ");
    fgets(response,1024, stdin);
    sizeMessage = strlen(response) + 1;

    sendto(newSocket,response,sizeMessage,0,(struct sockaddr *)&serverStorage,addr_size);
  }
}
