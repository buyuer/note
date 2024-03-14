#include <iostream>

struct Operator {
    template <typename T> T operator+(const T& a) { return T {} + a; }

    explicit operator bool() { return true; }
    operator int() { return 2; }
};

int main(int argc, char* argv[])
{
    Operator o1, o2;

    if (o1) {
        int x = o1;
    }
}