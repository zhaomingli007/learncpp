#include <stdio.h>
#include <errno.h>
#include <unistd.h> // posix operating system API

#define MAXLINE 8192 /* Max text line length */
#define RIO_BUFFSIZE = 8192
typedef struct {
    int rio_fd;
    int rio_cnt; //unread bytes in internal buf
    char *rio_bufprt; //next unread byte in internal buffer
    char rio_buf[RIO_BUFFSIZE];
} rio_t;

void rio_readinitb(rio_t *rp, int rd);