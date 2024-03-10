#include <errno.h>
#include <fcntl.h>
#include <libaio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FILE_PATH  "./TEST"
#define MAX_EVENTS 2
#define IOCB_NUM   2

// TODO 怎么设置回调

int main()
{
    io_context_t ctx               = {};
    struct iocb  iocbs[IOCB_NUM]   = {};
    struct iocb *iocbs_p[IOCB_NUM] = {};
    for (int index = 0; index < IOCB_NUM; ++index)
    {
        iocbs_p[index]    = &iocbs[index];
        iocbs[index].data = (void *)1;
    }
    struct io_event events[MAX_EVENTS] = {};
    char            buff_write[]       = "Hello libaio";
    char            buff_read[32]      = {};
    struct timespec timeout;

    int fd = open(FILE_PATH, O_RDWR | O_CREAT);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }

    int ret = io_setup(MAX_EVENTS, &ctx);
    if (ret < 0)
    {
        printf("io_setup error: %d, %s", ret, strerror(ret));
        return -1;
    }

    io_prep_pwrite(&iocbs[0], fd, buff_write, sizeof(buff_write), 0);
    io_prep_pread(&iocbs[1], fd, buff_read, sizeof(buff_read), 0);
    ret = io_submit(ctx, IOCB_NUM, iocbs_p);
    if (ret != IOCB_NUM)
    {
        io_destroy(ctx);
        printf("io_setup error: %d, %s", ret, strerror(ret));
        return -1;
    }

    while (1)
    {
        timeout.tv_sec  = 0;
        timeout.tv_nsec = 500000000;

        ret = io_getevents(ctx, 1, MAX_EVENTS, events, &timeout);
        if (ret < 0)
        {
            perror("io_getevents error");
            break;
        }
        else if (ret == 0)
        {
            printf("No buff_write in 0.5 seconds.\n");
            continue;
        }
        for (int index = 0; index < ret; ++index)
        {
            // TODO 弄明白每个成员都是干嘛的？怎么传递data
            printf("%p: \n", events[index].obj->data);
        }

        printf("%s\n", buff_write);
        printf("%s\n", buff_read);

        break;
    }

    io_destroy(ctx);
    close(fd);
    return 0;
}
