
#include <nsp.h>
#include<time.h>
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
        .sin_port = htons(PORT)};

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
    int i,j;
    while ((newSock = accept(sockfd, (struct sockaddr *)&address, &getLen))>=0)
    {
        if(newSock<1){
            printf("E>Failed to accept\n");continue;
        }
        time_t t = time(NULL);
        char* ptr = ctime(&t);
        if(!ptr){
            printf("E>Failed to get time");continue;
        }
        i=0,j=0;
        while((i=write(sockfd,ptr+j,TBS-j))>0){
            j+=i;
            if(j==TBS) break;
        }
    }

    
    ssize_t readVal;
    
    

    close(sockfd);

    return E_S;
}