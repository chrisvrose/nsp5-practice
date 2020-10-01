#include <nsp.h>

int main(int argc, char **argv)
{
    printf("I>Hello world\n");
    if(argc<2){
        printf("GIB ADDRESS");
        return E_F;
    }
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
        .sin_port = htons(3000),
    };
    if (inet_pton(AF_INET, argv[1], &(address.sin_addr)) < 0)
    {
        printf("E>Could not get self addr");
        return E_F;
    };


    if ( connect(sockfd, (struct sockaddr *)&address, sizeof address) < 0)
    {
        printf("E>Failed connect, cri");
        return E_F;
    }
    char buffer[] = "Hello buddy how are you";int n;
    while((n = send(sockfd,buffer,sizeof buffer,0))>0){
        // buffer[n] = 0;
        printf("Wrote %d chars",n);
    }

    close(sockfd);

    return E_S;
}