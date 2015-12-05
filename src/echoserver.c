#include "Utility.h"
#include<unp.h>
void * thread(void *vargp);

int main(int argc, char** argv)
{
    int listenfd;
    int *pConnfd;
    socklen_t clilen; 
    struct sockaddr_in cliaddr, servaddr;
    pthread_t tid; 

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for(;;)
    {
      pConnfd = Malloc(sizeof(int)); 
      *pConnfd = Accept(listenfd, (SA*) &cliaddr, &clilen);
      pthread_create(&tid, NULL, thread, pConnfd);
    }
}

void * thread(void *vargp)
{
    int connfd = *((int*)vargp);
    pthread_detach(pthread_self());
    free(vargp);
    echo(connfd);
    Close(connfd);
    return NULL;
}
