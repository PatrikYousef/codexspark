#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

typedef struct lista{
    

}lista;

void serverFunc(int connfd)
{
    int choice;

    // Server måste läsa valet från klienten
    read(connfd, &choice, sizeof(choice));

    switch (choice)
    {
    case 1:
    {
        int num1, num2, result;
        // Läs två tal från klienten
        read(connfd, &num1, sizeof(num1));
        read(connfd, &num2, sizeof(num2));

        result = num1 + num2;
        // Skicka tillbaka resultat
        write(connfd, &result, sizeof(result));
        printf("Server: num1 + num2 = %d\n", result);
    }
    break;

    case 2:
    {
        int length;
        char text[256];

        // Läs längd
        read(connfd, &length, sizeof(length));
        read(connfd, text, length);
        printf("Server text: %s\n", text);
        printf("Server length: %d\n", length);
    }
    break;
    
    default:
        printf("Server: okänt val.\n");
        break;
    }


}

// Driver function
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
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
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
        printf("server accept the client...\n");

    // Function for chatting between client and server
    serverFunc(connfd);

    // After chatting close the socket
    close(sockfd);
}