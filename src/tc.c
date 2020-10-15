#include <nsp.h>

int main(int argc, char **argv)
{
    printf("I>Hello world\n");
    if(argc<2){
        printf("E>No addr\n");
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
        .sin_port = htons(PORT),
    };
    if (inet_pton(AF_INET, argv[1], &(address.sin_addr)) < 0)
    {
        printf("E>Could not get self addr\n");
        return E_F;
    };


    if ( connect(sockfd, (struct sockaddr *)&address, sizeof address) < 0)
    {
        printf("E>Failed connect, cri\n");
        return E_F;
    }

    char buffer[TBS+1];int n,ts=0;
    int i=0,j=0;

    while((i=read(sockfd,buffer+j,28-j))>0){
        j+=i;
        if(j==TBS) break;
    }
    buffer[j+1]=0;

    printf("T>%s\n",buffer);

    close(sockfd);

    return E_S;
}