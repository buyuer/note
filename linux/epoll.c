#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int efd = epoll_create1(EPOLL_CLOEXEC);

    struct epoll_event event = {
        .events = EPOLLIN,
        .data.fd = 0,
    };

    epoll_ctl(efd, EPOLL_CTL_ADD, 0, &event);

    struct epoll_event events[10] = {};
    while (true) {
        int retval = epoll_wait(
            efd, events, sizeof(events) / sizeof(struct epoll_event), -1);

        for (int index = 0; index < retval; ++index) {

            if (events[index].events & EPOLLIN) {
                char data_buf[1024] = {};
                ssize_t ret
                    = read(events[index].data.fd, data_buf, sizeof(data_buf));
                if (ret > 0) {
                    data_buf[ret - 1] = '\0';
                    printf("    %s\n", data_buf);
                    if (strcmp("exit", data_buf) == 0) {
                        exit(EXIT_SUCCESS);
                    }
                }
            }
        }
    }
}