#include <coroutine>
#include <iostream>
#include <string_view>

struct HelloCoroutine {
    struct HelloPromise {
        std::string_view value_;

        HelloCoroutine get_return_object() {
            return std::coroutine_handle<HelloPromise>::from_promise(*this);
        }

        std::suspend_never initial_suspend() noexcept { return {}; }

        std::suspend_always final_suspend() noexcept { return {}; }

        void unhandled_exception() {}

        std::suspend_always yield_value(std::string_view value) {
            value_ = value;
            std::cout << value << std::endl;
            return {};
        }

        std::suspend_never return_value(std::string_view value) {
            value_ = value;
            std::cout << value << std::endl;
            return {};
        }
    };

    using promise_type = HelloPromise;

    HelloCoroutine(std::coroutine_handle<HelloPromise> h) : handle(h) {}

    std::coroutine_handle<HelloPromise> handle;
};

HelloCoroutine hello_yield() {
    std::string_view s = "Hello ";
    co_yield s;
    std::cout << "world" << std::endl;
}

HelloCoroutine hello_await() {
    std::cout << "Hello" << std::endl;
    co_await std::suspend_always{};
    std::cout << "world" << std::endl;
}

HelloCoroutine hello_return() {
    std::cout << "hello" << std::endl;
    co_await std::suspend_always{};
    std::string_view s = "world ";
    co_return s;
}

int main() {
    HelloCoroutine coro = hello_return();

    std::cout << "calling resume" << std::endl;
    coro.handle.resume();

    std::cout << "destroy" << std::endl;
    coro.handle.destroy();

    return 0;
}