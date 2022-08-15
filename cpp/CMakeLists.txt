
add_executable(cpp_semaphore
        semaphore.cpp)
add_executable(cpp_future_async
        future_async.cpp)
add_executable(cpp_future_promise
        future_promise.cpp)
add_executable(cpp_coroutine
        coroutine.cpp)
add_executable(cpp_ranges
        ranges.cpp)

set_target_properties(
        cpp_semaphore
        cpp_future_async
        cpp_future_promise
        cpp_coroutine
        cpp_ranges
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 23
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED OFF
)
