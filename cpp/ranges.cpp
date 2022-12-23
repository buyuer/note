#include <iostream>
#include <ranges>
#include <vector>

int main(int argc, char *argv[], char *env[])
{
    auto v1 = std::views::iota.operator()(1, 100);

    auto is_multiple_3 = [](int i) -> bool { return i % 3 == 0; };

    auto result = v1 | std::views::filter(is_multiple_3);

    for (auto i : result)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
