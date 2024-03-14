#include <map>
#include <vector>

#include <iostream>
#include <string_view>

auto get_args(int argc, char* argv[]) -> std::vector<std::string_view>
{
    std::vector<std::string_view> args;

    for (int index = 0; index < argc; ++index) {
        args.emplace_back(argv[index]);
    }
    return std::move(args);
}

auto get_envs(char* envp[])
{
    std::map<std::string_view, std::string_view> envs;
    for (; *(envp) != nullptr; ++envp) {
        std::string_view env_str { *envp };

        auto pos = env_str.find(std::string_view { "=" });
        auto ret
            = envs.insert({ env_str.substr(0, pos),
                            env_str.substr(pos + 1, env_str.size() - pos) });
        if (!ret.second) {
            std::cerr << "insert envp failed: " << env_str << std::endl;
            break;
        }
    }

    return std::move(envs);
}

int main(int argc, char* argv[], char* envp[])
{
    auto args { get_args(argc, argv) };
    auto envs { get_envs(envp) };

    auto it = envs.find(std::string_view { "Path" });
    if (it != envs.end()) {
        std::cout << "Path set in envs: " << it->second << std::endl;
    } else {
        std::cout << "Path is not set in envs: " << std::endl;
    }

    for (auto& [key, value] : envs) {
        std::cout << key << ": " << value << std::endl;
    }
}
