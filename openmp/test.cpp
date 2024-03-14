#include <omp.h>

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    auto thread_num = omp_get_num_procs();

    std::vector<int> nums(thread_num, 0);

    int summary { 0 };

#pragma omp parallel for default(none) shared(nums, summary, std::cout)
    for (auto& num : nums) {
        num += 1;
        std::cout << "thread: " << omp_get_thread_num() << std::endl;
#pragma omp critical
        summary += num;
    }

    std::cout << "summary: " << summary << std::endl;
}