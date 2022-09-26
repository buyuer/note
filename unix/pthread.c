#include <pthread.h>
#include <unistd.h>

#include <stdio.h>

static void *thread_entry(void *arg)
{
    printf("%p\n", arg);

    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    pthread_create(&thread, NULL, thread_entry, argv);
    pthread_detach(thread);

    sleep(1);
}
