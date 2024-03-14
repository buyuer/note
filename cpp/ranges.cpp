#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

int main(int argc, char* argv[], char* env[])
{
    {
        auto v1 = std::views::iota.operator()(1, 100);
        auto is_multiple_3 = [](int i) -> bool { return i % 3 == 0; };
        auto result = v1 | std::views::filter(is_multiple_3);
        for (auto i : result) {
            std::cout << i << std::endl;
        }
    }
    {
        std::string str { "hello world i am ding" };
        auto result = std::views::all(str) | std::views::split(' ')
            | std::views::transform([](auto word) {
                          return std::string_view(word.begin(), word.end());
                      });
        for (auto s : result) {
            std::cout << s << std::endl;
        }
    }

    return 0;
}
