#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int main(int argc, char* argv[])
{
    std::mutex m;

    std::thread t1(
        [](std::mutex* m) -> void {
            std::unique_lock<std::mutex> ul(*m);

            std::cout << "t1 done" << std::endl;
        },
        &m);
    t1.detach();

    m.lock();
    std::cout << "main thread done" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds { 1 });
    m.unlock();

    return 0;
}