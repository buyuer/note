#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main(int argc, char* argv[])
{
    std::mutex m;
    std::condition_variable cv;

    std::thread t1(
        [](std::mutex* m, std::condition_variable* cv) -> void {
            std::unique_lock<std::mutex> ul(*m);
            cv->wait(ul);

            std::cout << "t1 done" << std::endl;
        },
        &m, &cv);
    t1.detach();

    std::cout << "main thread done" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds { 1 });
    cv.notify_one();

    return 0;
}