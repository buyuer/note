#include <iostream>
#include <concepts>

template<typename T>
concept HasPlusOperator = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template<typename T>
requires HasPlusOperator<T>
T add1(const T &x, const T &y) {
    return x + y;
}

template<HasPlusOperator T>
T add2(const T &x, const T &y) {
    return x + y;
}

int main() {
    auto num1 = add1(1, 2);

    std::cout << num1 << std::endl;

    HasPlusOperator auto num2 = add2(3, 4);

    std::cout << num2 << std::endl;

    return 0;
}
