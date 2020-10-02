
#include <nsp.h>
// #define __a __auto_type
int main(void)
{
    printf("I>Hello world\n");
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("E>Failed to allocate socket");
        return E_F;
    }
    else
    {
        printf("I>Allocated socket %d\n");
    }

    //init structure
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr = {.s_addr = INADDR_ANY},
        .sin_port = htons(3000)};

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        printf("E>failed to bind");
        return E_F;
    }

    if (listen(sockfd, 2) < 0)
    {
        printf("E>Failed to set to listen mode");
        return E_F;
    }

    int newSock;
    int getLen = sizeof address;
    if ((newSock = accept(sockfd, (struct sockaddr *)&address, &getLen)) < 0)
    {
        printf("E>Failed to set to accept");
        return E_F;
    }

    char buffer[50];
    ssize_t readVal;
    
    while ((readVal = recv(newSock, buffer, 50,0)) > 0)
    {
        for (ssize_t i = 0; i < readVal; i++)
        {
            printf("%c ", buffer[i]);
        }
        fflush(NULL);
        printf("\n");
    }

    close(sockfd);

    return E_S;
}