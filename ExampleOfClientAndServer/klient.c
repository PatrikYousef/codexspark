#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void clientFunc(int sockfd)
{
    int choice;

    printf("Vad vill du göra (1 = addera två tal)? ");
    scanf("%d", &choice);

    // Skicka val till servern
    write(sockfd, &choice, sizeof(choice));

    switch (choice)
    {
    case 1:
    {
        int num1 = 4;
        int num2 = 7;
        int result;

        // Skicka tal till servern
        write(sockfd, &num1, sizeof(num1));
        write(sockfd, &num2, sizeof(num2));

        // Läs resultat från servern och printa ut den
        read(sockfd, &result, sizeof(result));
        printf("Resultat från server: %d\n", result);
    }
    break;

    case 2:
    {
        char text[] = "HelloWorld";
        int length = strlen(text) + 1; // include '\0'

        // Skicka längden
        write(sockfd, &length, sizeof(length));

        // Skicka själva texten (utan &)
        write(sockfd, text, length);

        printf("Skickade text till servern.\n");
        printf("Server text: %s\n", text);
        printf("Server length: %d\n", length);
    }
    break;

    case 3:
    {
    }
    break;

    default:
        printf("Ogiltigt val.\n");
        break;
    }
}

int main()
{
    int sockfd, connfd;
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    clientFunc(sockfd);

    // close the socket
    close(sockfd);
}