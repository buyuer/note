#include <any>
#include <iostream>

#include <any>
#include <iostream>

int main()
{
    std::cout << std::boolalpha;

    std::any v = 1;
    std::cout << v.type().name() << ": " << std::any_cast<int>(v) << '\n';
    v = 3.14;
    std::cout << v.type().name() << ": " << std::any_cast<double>(v) << '\n';
    v = true;
    std::cout << v.type().name() << ": " << std::any_cast<bool>(v) << '\n';

    try {
        v = 1;
        std::cout << std::any_cast<float>(v) << '\n';
    } catch (const std::bad_any_cast& e) {
        std::cout << e.what() << '\n';
    }

    v = 2;
    if (v.has_value())
        std::cout << v.type().name() << ": " << std::any_cast<int>(v) << '\n';

    v.reset();
    if (!v.has_value())
        std::cout << "没有值\n";

    v = 3;
    int* p = std::any_cast<int>(&v);
    std::cout << *p << '\n';
}
