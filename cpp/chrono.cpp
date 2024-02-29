#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
    auto point = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds{1234});
    auto cost = std::chrono::system_clock::now() - point;
    std::cout << cost.count() << std::endl;
    auto cost_ms =
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(
            cost);
    std::cout << cost_ms.count() << "ms" << std::endl;
}