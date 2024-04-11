#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    const char* str = "hello world\n";
    const size_t str_len = strlen(str);
    const ssize_t ret = write(1, str, strlen(str));
    if (str_len != ret) {
        perror("write failed");
    }
#if defined(__unix__) || defined(__unix)
    printf("posix here");
#else
    perror("do not support unix");
#endif
}