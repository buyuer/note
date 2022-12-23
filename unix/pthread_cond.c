#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct CondMutex {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

static void *thread_entry(void *arg) {
    struct CondMutex *pair = (struct CondMutex *) arg;

    pthread_cond_wait(&pair->cond, &pair->mutex);
    printf("thread\n");

    return 0;
}

int main(int argc, char *argv[]) {
    struct CondMutex pair = {};
    pthread_cond_init(&pair.cond, NULL);
    pthread_mutex_init(&pair.mutex, NULL);

    pthread_t thread;
    pthread_create(&thread, NULL, thread_entry, &pair);
    pthread_detach(thread);

    sleep(2);

    printf("main thread\n");
    pthread_cond_signal(&pair.cond);

    sleep(1);

    pthread_cond_destroy(&pair.cond);
    pthread_mutex_destroy(&pair.mutex);
}