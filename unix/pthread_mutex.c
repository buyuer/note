#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void *thread_entry(void *arg) {
    pthread_mutex_t *mutex = (pthread_mutex_t *) arg;

    pthread_mutex_lock(mutex);
    printf("thread\n");
    pthread_mutex_unlock(mutex);

    return 0;
}

int main(int argc, char *argv[]) {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_mutex_lock(&mutex);

    pthread_t thread;
    pthread_create(&thread, NULL, thread_entry, &mutex);
    pthread_detach(thread);

    sleep(2);
    printf("main thread\n");
    pthread_mutex_unlock(&mutex);

    sleep(1);
    pthread_mutex_destroy(&mutex);
}
