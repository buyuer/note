#include <concepts>
#include <format>
#include <iostream>
#include <iterator>

int main(int argc, char* argv[])
{
    std::cout << std::format("{}", 123) << std::endl;
    std::cout << std::format("{:6}", 134) << std::endl;
    std::cout << std::format("{:<2}", 100) << std::endl;

    std::string str;
    std::format_to(std::back_inserter(str), "{}", 10);
    std::cout << str << std::endl;
}