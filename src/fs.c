#include <nsp.h>

//handle all children that are returning and collect their returns
void child_handler(int sig)
{
    pid_t pid;
    int status;
    /* EEEEXTEERMINAAATE! */
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("G>Child(%d) has exit\n", pid);
    }
}

int respond(int connectfd)
{

    char buf1[500], buf2[1500];
    pid_t pid = getpid();
    int i = 0, j = 0, k = 0, l = 0;
    printf("%d>Attempting to get input\n", pid);
    //get client req
    while ((i = read(connectfd, buf1 + j, 500)) > 0)
    {
        j += i;
        printf("%d>Read %d,=%d,(%d)\n", pid, i, buf1[j], j);
        if (j >= 500)
        {
            printf("%d> Breaking input on j=%d with content (%d)\n", pid, j, buf1[j]);
            break;
        }
    }
    printf("%d>Processed input\n", pid);
    printf("%d>Fin Read string length %d, string:%s\n", pid, strlen(buf1),buf1);
    //buf1 now has a file name

    int fd = open(buf1, O_RDONLY);
    if(fd<0){
        printf("%d>Failed to open file\n", pid);
        close(connectfd);
    }
    //respond back with j chars
    j = 0;
    while (k < 500)
    {
        j = read(fd, buf2 + l, 1500 - l);
        l += j;
        
        buf2[l+1]=0;
        i = write(connectfd, buf2 + k, 1500 - k);
        if (i == 0)
            break;
        k += i;
    }
    printf("%d>Wrote back data\n", pid);
    close(connectfd);
}

int main()
{
    signal(SIGCHLD, child_handler);
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

    int newSock, pid;
    socklen_t len;
    int t;
    while ((newSock = accept(sockfd, (struct sockaddr *)&address, &len)) >= 0)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("%d>Created to respond\n", getpid());
            respond(newSock);
            close(newSock);
            return 0;
        }
        else if (pid == -1)
        {
            printf("E>Could not respond\n");
            close(newSock);

            break;
        }
        else
        {
            waitpid(-1, &t, WNOHANG);
        }
    }
    close(sockfd);
}