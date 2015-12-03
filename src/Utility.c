#include <unp.h>
#include "Utility.h"
#include<stdio.h>

void echo(int connfd)
{
    ssize_t n;
    char buf[MAXLINE];

    while(1)
    {
        while((n = read(connfd, buf, MAXLINE)) >0)
        {
            Writen(connfd, buf, n);
        }
        // if is interrupted, read again.
        if(n < 0 && errno == EINTR) continue;
        else if (n < 0)
            err_sys("echo: read error");
    }
}
void sigchild_handler(int sig)
{
    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("child %d terminated\n", pid);
    }
    return;
}
void init_pool(int listenfd, pool *p)
{
    int i;
    p->maxi = -1;
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        p->clientfd[i] = -1;
    }
    p->maxfd = listenfd;
    FD_ZERO(&p->ready_set);
    FD_SET(listenfd, &p->read_set);
}
void add_client(int connfd, pool *p)
{
    int i ;
    p->nready --;
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        if(p->clientfd[i] < 0)
        {
            p->clientfd[i] = connfd;
            //p->clientbufs[i] =malloc(sizeof(char) * MAXLINE);
            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    if(i == FD_SETSIZE)
        err_quit("add_client error: To many clients");
}

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];

    for(i = 0; (i <= p->maxi) && (p->nready >0 ); ++i)
    {
        connfd = p->clientfd[i];
        if((connfd > 0) && ( FD_ISSET(connfd, &p->ready_set))){
            p->nready --;
            if((n = Read(connfd, buf,MAXLINE)) != 0)
            {
                Writen(connfd, buf, n);
            }
            else
            {
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}
    
    

