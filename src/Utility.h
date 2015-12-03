#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <unp.h>
/*
 * reads and echos text lines.
 */
void echo(int connfd);
/*
 * handle signal of child terminal
 * in case of zombie
 */
void sigchild_handler(int sig);

typedef struct {
    int maxfd;       // largest descriptor in read_set
    fd_set read_set; // set of all active descriptors
    fd_set ready_set;// subset of sescriptors ready for reading
    int nready;      // number of ready descriptors from select
    int maxi;       // highwater index into client array
    int clientfd[FD_SETSIZE];   // set of active descriptors
//    char* clientbufs[FD_SETSIZE]; // set of active read buffers
} pool;

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);
#endif
