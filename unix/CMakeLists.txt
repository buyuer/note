
add_executable(unix_select select.c)
add_executable(unix_poll poll.c)
add_executable(unix_pthread pthread.c)
add_executable(unix_pthread_mutex pthread_mutex.c)

find_package(Threads)

target_link_libraries(unix_pthread Threads::Threads)
target_link_libraries(unix_pthread_mutex Threads::Threads)

set_target_properties(
        unix_select
        unix_poll
        unix_pthread
        unix_pthread_mutex
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)