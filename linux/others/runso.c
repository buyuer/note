#include <unistd.h>

char const __invoke_dynamic_linker__[] __attribute__ ((section (".interp")))
#ifdef __LP64__
= "/lib64/ld-linux-x86-64.so.2";
#else
= "/lib/ld-linux.so.2";
#endif

void _start(void)
{
    static char const msg[] = "Hello world!\n";

    write(STDOUT_FILENO, msg, sizeof msg - 1);
    _exit(0);
}