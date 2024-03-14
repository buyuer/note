#include <assert.h>
#include <stdio.h>
#include <threads.h>
#include <time.h>

int thread_func(void* arg)
{
    printf("%lu, %s\n", thrd_current(), __func__);
    struct timespec sleep_time = { .tv_sec = 1, .tv_nsec = 0 };
    thrd_yield();
    thrd_sleep(&sleep_time, NULL);
}

int main()
{
    thrd_t th;
    int status = thrd_create(&th, thread_func, NULL);
    assert(("thrd_create create error!!\n", status == thrd_success));

    thrd_join(th, NULL);
    printf("%lu, %s\n", thrd_current(), __func__);
}