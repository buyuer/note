#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct pollfd fds[1] = {};
    fds[0].fd            = 0;
    fds[0].events        = POLLIN;

    while (true)
    {
        int retval = poll(fds, 1, -1);

        /* Check all fds after poll return */
        if (retval == -1)
        {
            perror("poll()");
        }
        else if (retval && (fds[0].revents & POLLIN))
        {
            printf("fd is coming data:\n");

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
        else
        {
            printf("no data\n");
        }
    }
}