#include <unp.h>
#include "Utility.h"

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
