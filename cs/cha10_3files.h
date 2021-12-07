#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int open(char *filename, int flags, mode_t mode);
int close(int fd);
