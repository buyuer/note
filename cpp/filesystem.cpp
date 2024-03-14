#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::string get_permissions(const fs::path& path)
{
    const fs::perms p = std::filesystem::status(path).permissions();
    std::string result {};
    auto show = [&](char op, fs::perms perm) {
        result += (fs::perms::none == (perm & p) ? '-' : op);
    };
    show('r', fs::perms::owner_read);
    show('w', fs::perms::owner_write);
    show('x', fs::perms::owner_exec);
    show('r', fs::perms::group_read);
    show('w', fs::perms::group_write);
    show('x', fs::perms::group_exec);
    show('r', fs::perms::others_read);
    show('w', fs::perms::others_write);
    show('x', fs::perms::others_exec);
    return result;
}

int main(int argc, char* argv[])
{
    std::vector<fs::path> paths;
    paths.reserve(argc);

    for (decltype(argc) it = 1; it < argc; ++it) {
        auto path = fs::path { argv[it] };
        if (fs::exists(path)) {
            paths.emplace_back(std::move(path));
        }
    }

    for (auto& path : paths) {
        std::cout << path << ": " << std::endl;
        fs::directory_iterator dir_it { path };
        for (auto& entry : dir_it) {
            auto status = fs::status(path);
            std::cout << "\t" << entry << "\t\t" << get_permissions(path)
                      << std::endl;
        }
    }
}