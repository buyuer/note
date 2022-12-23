list(APPEND unix_targets
        dlfcn
        select
        poll
        pthread
        pthread_mutex
        pthread_cond
        )

foreach (target ${unix_targets})
    add_executable(unix_${target} ${target}.c)
    set_target_properties(
            unix_${target}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
    )
endforeach ()

find_package(Threads)

target_link_libraries(unix_dlfcn -ldl)
target_link_libraries(unix_pthread Threads::Threads)
target_link_libraries(unix_pthread_mutex Threads::Threads)
target_link_libraries(unix_pthread_cond Threads::Threads)
