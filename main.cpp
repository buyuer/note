#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> get_args(int argc, char *argv[])
{
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i)
    {
        args.emplace_back(argv[i]);
    }

    return std::move(args);
}

int main(int argc, char *argv[])
{
    auto args = get_args(argc, argv);

    for (auto &arg : args)
    {
        std::cout << arg << std::endl;
    }
}
