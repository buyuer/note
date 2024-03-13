#include <functional>
#include <iostream>

template <typename T> T plus(T x1, T x2, T x3)
{
    std::cout << "x1: " << x1 << ", x2: " << x2 << ", x3: " << x3 << std::endl;
    return x1 + x2 + x3;
}
template <typename T> T mult(T x1, T x2, T x3)
{
    std::cout << "x1: " << x1 << ", x2: " << x2 << ", x3: " << x3 << std::endl;
    return x1 * x2 * x3;
}

struct Functions
{
    std::string name{"Functions: "};

    int plus(int x1, int x2, int x3)
    {
        auto x = ::plus(x1, x2, x3);
        std::cout << name << x << std::endl;
        return x;
    }
};

int main(int argc, char *argv[])
{
    using namespace std::placeholders;

    Functions funcs;

    auto p1 = std::bind(plus<int>, _3, _2, _1);
    auto p2 = std::bind(&Functions::plus, &funcs, _3, _2, _1);

    std::cout << p1(1, 2, 3) << std::endl;
    std::cout << p2(4, 5, 6) << std::endl;

    std::function<int(int, int, int)> f1{};
    f1 = plus<int>;
    f1(1, 2, 3);
    f1 = mult<int>;
    f1(1, 2, 3);
}