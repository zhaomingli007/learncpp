#include "csprg.h"

void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufprt = rp->rio_buf;
}


static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;
    while (rp->rio_cnt <= 0)
    { /*Unread bytes*/
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0)
        {
            if (errno != EINTR)
            {
                return -1;
            }
        }
        else if (rp->rio_cnt == 0)
            return 0;
        else
            rp->rio_bufprt = rp->rio_buf;
    }
    /*copy from internal buffer to user buffer*/
    cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufprt, cnt);
    rp->rio_bufprt += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}
