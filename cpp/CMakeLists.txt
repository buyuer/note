list(APPEND cpp_targets
        semaphore
        future_async
        future_promise
        coroutine
        ranges
        thread
        mutex
        condition_variable
        iostream
        smart_pointer
        )

foreach (target ${cpp_targets})
    add_executable(cpp_${target} ${target}.cpp)
    set_target_properties(
            cpp_${target}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 23
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
    )
endforeach ()

find_package(Threads)

target_link_libraries(cpp_thread Threads::Threads)
target_link_libraries(cpp_mutex Threads::Threads)
target_link_libraries(cpp_condition_variable Threads::Threads)
