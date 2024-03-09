#include <aio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define BUFFER_SIZE 10240

int main(int argc, char *argv[])
{
    int          fd;
    struct aiocb rd;

    if (argc != 2)
    {
        perror("Please give the path of file");
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    bzero(&rd, sizeof(rd));
    rd.aio_buf = (char *)malloc(BUFFER_SIZE);
    if (rd.aio_buf == NULL)
    {
        perror("Error allocating buffer");
        return 1;
    }
    rd.aio_fildes     = fd;
    rd.aio_nbytes     = BUFFER_SIZE;
    rd.aio_offset     = 0;
    rd.aio_lio_opcode = LIO_READ;

    if (aio_read(&rd) < 0)
    {
        perror("Error adding aio_read request");
        return 1;
    }

    while (aio_error(&rd) == EINPROGRESS)
    {
        printf("wait to doing\n");
    }

    ssize_t readLen = aio_return(&rd);
    if (readLen >= 0)
    {
        printf("Read %zd bytes: %s\n", readLen, (char *)rd.aio_buf);
    }
    else
    {
        perror("Error reading file");
    }

    free((void *)rd.aio_buf);
    close(fd);

    return 0;
}