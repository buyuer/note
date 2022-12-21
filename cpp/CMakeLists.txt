
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
add_executable(cpp_thread
        thread.cpp)
add_executable(cpp_mutex
        mutex.cpp)
add_executable(cpp_condition_variable
        condition_variable.cpp)
add_executable(cpp_iostream
        iostream.cpp)
add_executable(cpp_smart_pointer
        smart_pointer.cpp)

find_package(Threads)

target_link_libraries(cpp_thread Threads::Threads)
target_link_libraries(cpp_mutex Threads::Threads)
target_link_libraries(cpp_condition_variable Threads::Threads)

set_target_properties(
        cpp_semaphore
        cpp_future_async
        cpp_future_promise
        cpp_coroutine
        cpp_ranges
        cpp_thread
        cpp_iostream
        cpp_smart_pointer
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 23
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED OFF
)
