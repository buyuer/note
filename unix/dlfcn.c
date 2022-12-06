#include <dlfcn.h>
#include <stdio.h>

typedef int (*printf_t)(const char *, ...);

int main(int argc, char *argv[])
{
    void *handler = dlopen("/lib/x86_64-linux-gnu/libc.so.6", RTLD_NOW);

    if (!handler)
    {
        printf("open lib failed: %s\n", dlerror());
    }

    printf_t dl_printf = dlsym(handler, "printf");

    dl_printf("this is dl_printf\n");

    dlclose(handler);
}