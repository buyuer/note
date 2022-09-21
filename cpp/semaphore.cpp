#include <iostream>
#include <semaphore>
#include <thread>

using namespace std::literals::chrono_literals;

int main(int argc, char *argv[])
{
    std::counting_semaphore<10> sem(0);

    std::thread t1(
        [](std::counting_semaphore<10> *sem) -> void {
            while (true)
            {
                sem->acquire();
                std::cout << "." << std::flush;
            }
        },
        &sem);

    t1.detach();

    for (size_t index = 0; index < 5; ++index)
    {
        sem.release();
        std::this_thread::sleep_for(1s);
    };
}