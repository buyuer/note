#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int kfd = kqueue();

    struct kevent event[1] = {};
    EV_SET(event, 0, EVFILT_READ, EV_ADD, 0, 0, NULL);

    kevent(kfd, event, 1, NULL, 0, NULL);

    while (true)
    {
        struct kevent active_events[1];

        /* kevent is like epoll_ctl and epoll_wait */
        int retval = kevent(kfd, NULL, 0, active_events, 1, NULL);

        char    data_buf[1024] = {};
        ssize_t ret            = read(0, data_buf, sizeof(data_buf));
        if (ret > 0)
        {
            data_buf[ret - 1] = '\0';
            printf("    %s\n", data_buf);
            if (strcmp("exit", data_buf) == 0)
            {
                exit(EXIT_SUCCESS);
            }
        }
    }
}