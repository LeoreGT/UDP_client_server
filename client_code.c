#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
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

/* Function creates the clientside socket with loopback ip address and port number
 * User inputs question to be sent to the serverside, sent with the sendto function
 * Once server responds, is read with recvfrom and printed
 */

void Run()
{
  struct sockaddr_in serverSide;
  char message[1024];
  int clientSide, portNum, sizeMessage;
  socklen_t addr_size;

  clientSide = socket(PF_INET, SOCK_DGRAM, 0);

  serverSide.sin_family = AF_INET;   //create the socket
  serverSide.sin_port = htons(1024); //port number
  serverSide.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP address (loopback)
  memset(serverSide.sin_zero, 0, sizeof(serverSide.sin_zero)); //set to 0 for no junk

  addr_size = sizeof(serverSide);

  while(1)
  {
    printf("Type a question to send to server:");
    fgets(message,1024, stdin); //gets response input
    printf("You typed: %s",message);

    sizeMessage = strlen(message) + 1;

    sendto(clientSide,message,sizeMessage,0,(struct sockaddr *)&serverSide,addr_size);

    sizeMessage = recvfrom(clientSide,message,1024,0,NULL, NULL); //check size of incoming message

    printf("Answer from server: %s\n",message);

  }

}
