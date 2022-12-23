#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
    auto id = std::this_thread::get_id();
    std::cout << id << std::endl;

    std::thread t1(
            [](int argc, char *argv[]) -> void {
                std::this_thread::sleep_for(std::chrono::seconds{1});

                for (int index = 0; index < argc; ++index) {
                    std::cout << argv[index] << std::endl;
                }
            },
            argc, argv);

    auto start = std::chrono::high_resolution_clock::now();
    t1.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Sleep " << elapsed.count() << " ms" << std::endl;

    return 0;
}
