#include "csprg.h"
//only return short count if it encounters EOF
ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
                nread = 0; /* Interrupted by sig handler return */
            else
                return -1; /* Error set by read()*/
        }
        else if (nread == 0)
            break; /* EOF */
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrittern;
    char *bufp = usrbuf;
    while (nleft > 0)
    {
        if ((nwrittern = write(fd, bufp, nleft)) <= 0)
        {
            if (errno == EINTR)
                nwrittern = 0;
            else
                return -1;
        }
        nleft -= nwrittern;
        bufp -= nwrittern;
    }
    return n;
}

//Copy a text file from standard input to stardard output
int main(int argc, char ** argv){
    int n;
    rio_t rio;
    char buf[MAXLINE];

    rio_readinitb(&rio, STDIN_FILENO);
    while((n= rio_readlineb(&rio, buf, MAXLINE)) != 0)
        rio_writen(STDOUT_FILENO, buf, n);

}

