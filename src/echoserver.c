#include "Utility.h"
#include<unp.h>


int main(int argc, char** argv)
{
    int listenfd, connfd;
    socklen_t clilen; 
    struct sockaddr_in cliaddr, servaddr;
    static pool pool;
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);
    init_pool(listenfd, &pool);

    for(;;)
    {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1,&pool.ready_set, NULL, NULL, NULL);

        // if listenfd is selected
        if(FD_ISSET(listenfd, &pool.ready_set)){
           clilen = sizeof(cliaddr); 
           connfd = Accept(listenfd, (SA*) &cliaddr, &clilen);

           add_client(connfd, &pool);
        }

       check_clients(&pool); 
    }
}

