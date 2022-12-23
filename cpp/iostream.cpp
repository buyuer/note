#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<int> nums;

    for (int num{}; std::cin >> num;) {
        nums.emplace_back(num);
        if (std::cin.get() == '\n')
            break;
    }

    for (auto num: nums) {
        std::cout << num << std::endl;
    }

    return 0;
}
