#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int ifd = inotify_init();
    if (ifd < 0)
    {
        perror("inotify init failed");
        goto err;
    }

    int ret = inotify_add_watch(ifd, "./", IN_ALL_EVENTS);
    if (ret < 0)
    {
        perror("inotify add failed");
        goto err;
    }

    char                  buf[4096] = {};
    struct inotify_event *event     = (struct inotify_event *)buf;
    ret                             = read(ifd, buf, sizeof(buf));
    if (ret < 0)
    {
        printf("read inotify failed %d: %d,%s\n", ret, errno, strerror(errno));
        goto err;
    }

    printf("%s", event->name);

err:
    close(ifd);
}
