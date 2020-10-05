#include <nsp.h>

int main(int argc, char **argv)
{
    char buffer[500], resp[500];
    int i, j, k;
    printf("I>Hello world\n");
    if (argc < 2)
    {
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

    if (connect(sockfd, (struct sockaddr *)&address, sizeof address) < 0)
    {
        printf("E>Failed connect, cri\n");
        return E_F;
    }

    //send req
    printf("Enter data\n:");
    // scanf("%s",buffer);
    fgets(buffer, 500, stdin);
    i = 0;
    j = 0;
    k = strlen(buffer);
    printf("I>Got data \"%s\"\n", buffer);
    while ((i = write(sockfd, buffer, 500)) > 0)
    {
        j += i;
        printf("I>Wrote %d/%d chars\n", j, k);
        if (j == 500)
        {
            printf("I>Done, wrote %d/%d\n",j,k);
            break;
        }
    }

    //recv resp
    printf("I>Response:\n");
    fflush(stdout);
    j=0;
    while ((i = read(sockfd, resp+j, 500)) > 0)
    {
        j+=i;
        fflush(stdout);
        if(j==500) break;
    }
    printf("%s", resp);
    printf("\nI>Done\n");

    close(sockfd);
}