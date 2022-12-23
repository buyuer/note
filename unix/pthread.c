#include <pthread.h>
#include <unistd.h>

#include <stdio.h>

static void *thread_entry(void *arg) {
    printf("data addr: %p(after)\n", arg);

    return 0;
}

int main(int argc, char *argv[]) {
    static unsigned char data = 0xaa;
    printf("data addr: %p(before)\n", &data);
    pthread_t thread;
    pthread_create(&thread, NULL, thread_entry, &data);
    pthread_detach(thread);

    sleep(1);

    return 0;
}
