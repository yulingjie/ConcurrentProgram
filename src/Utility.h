#ifndef __UTILITY_H__
#define __UTILITY_H__
/*
 * reads and echos text lines.
 */
void echo(int connfd);
/*
 * handle signal of child terminal
 * in case of zombie
 */
void sigchild_handler(int sig);
#endif
