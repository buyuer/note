#include <stdarg.h>
#include <stdio.h>

int print_(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    return vprintf(format, args);
}

int print(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    while (*format != '\0') {
        if (*format == 'd') {
            int v = va_arg(args, int);
            print_("%d", v);
        } else if (*format == 'f') {
            double v = va_arg(args, double);
            print_("%lf", v);
        } else {
            print_("%c", *format);
        }

        ++format;
    }
    va_end(args);
}

int main(int argc, const char* argv[])
{
    print("d f f d", 1, 2.2, 3.3, 4);
    print("f d f d", 1.1, 2, 3.3, 4);
}