#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    fd_set read_fds = {};
    int retval = 0;

    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);

    printf("select wailing\n");

    /* Let the last log can be output */
    fflush(stdout);

    while (true) {
        struct timeval tv = {
                .tv_sec  = 5,
                .tv_usec = 0
        };

        retval = select(1, &read_fds, NULL, NULL, &tv);

        if (retval == -1) {
            perror("select()");
        } else if (retval) {
            /* select will modify timeout to reflect the amount of time not
             * slept, but pselect will not
             * */
            printf("fd is available now and tv: %lf\n",
                   (double) tv.tv_sec + (double) tv.tv_usec / 1000000);

            /* After select() has returned, readfds will be cleared of
             * all file descriptors except for those that are ready for reading.
             * */
            if (FD_ISSET(0, &read_fds)) {
                char data_buf[1024] = {};
                ssize_t ret = read(0, data_buf, sizeof(data_buf));
                if (ret > 0) {
                    data_buf[ret - 1] = '\0';
                    printf("    %s\n", data_buf);
                    if (strcmp("exit", data_buf) == 0) {
                        exit(EXIT_SUCCESS);
                    }
                }
            }
        } else if (retval == 0) {
            printf("select timeout ......\n");
            continue;
        } else {
            printf("there is no fd available\n");
        }
    }
}
