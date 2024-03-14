#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

void print() { std::cout << std::endl; }

template <typename T, typename... ARGS> void print(const T& a, ARGS&&... args)
{
    std::cout << a;
    if (sizeof...(args) > 0) {
        std::cout << ", ";
    }
    print(std::forward<ARGS>(args)...);
}

template <typename... ARGS> void print2(ARGS... args)
{
    std::initializer_list<int> { (std::cout << "[" << args << "]", 0)... };
    std::cout << std::endl;
}

template <typename... ARGS> void print3(ARGS&&... args)
{
    (std::cout << ... << args) << std::endl;
}

template <typename... Types> void func1(std::vector<Types...> v1) { }
template <typename... Types> void func2(std::vector<Types>... v1) { }

int main(int argc, char* argv[])
{
    print(1, 3, 4, "Hello", 1.0);
    std::vector<int> v1;
    func1(v1);
    func2(v1, v1);
}