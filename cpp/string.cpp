#include <iostream>
#include <string>
#include <string_view>

int main(int argc, char* argv[])
{
    std::string str { "你好" };
    std::cout << str.find("好") << std::endl;

    std::cout << str << std::endl;
}