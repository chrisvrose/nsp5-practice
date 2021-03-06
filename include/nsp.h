#ifndef __NSP_H
#define __NSP_H 1

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/resource.h>

#include<sys/wait.h>
#include<unistd.h>
#define E_S EXIT_SUCCESS
#define E_F EXIT_FAILURE

#define PORT 3000
//time buffer size
#define TBS 28

#endif