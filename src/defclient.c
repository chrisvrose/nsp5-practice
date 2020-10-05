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

    char buffer[3276700];int n,ts=0;
    fgets(buffer,3276700,stdin);
    printf("I>READ(%d)\n",strlen(buffer));
    while((n = send(sockfd,buffer+ts,strlen(buffer),0))>0){
        // buffer[n] = 0;
        printf("I>Wrote %d chars\n",n);
        ts+=n;
        if(ts>=strlen(buffer)){
            break;
        }
    }

    close(sockfd);

    return E_S;
}