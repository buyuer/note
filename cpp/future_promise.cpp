#include <future>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::literals::chrono_literals;

int main(int argc, char *argv[]) {
    std::promise<int> pro;

    auto fut = pro.get_future();

    std::thread t1([](std::promise<int> *pro) -> void {
        std::this_thread::sleep_for(3s);

        pro->set_value(10);
    }, &pro);
    t1.detach();

    while (fut.wait_for(100ms) != std::future_status::ready)
        std::cout << "." << std::flush;
    std::cout << std::endl;

    std::cout << "final result: " << fut.get() << std::endl;

    return 0;
}