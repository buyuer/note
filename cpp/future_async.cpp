#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

int main(int argc, char *argv[]) {
    std::future<bool> fut = std::async([](int x) -> bool {
        std::this_thread::sleep_for(5s);

        for (int i = 1; i < x; i++) {
            if (x % i == 0)
                return false;
        }
        return true;
    }, 700020007);

    std::cout << "please wait";

    while (fut.wait_for(100ms) != std::future_status::ready)
        std::cout << "." << std::flush;
    std::cout << std::endl;

    bool ret = fut.get();
    std::cout << "final result: " << ret << std::endl;
    return 0;
}