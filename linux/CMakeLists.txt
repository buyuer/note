
add_executable(linux_epoll epoll.c)
add_executable(linux_inotify inotify.c)

set_target_properties(
        linux_epoll
        linux_inotify
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)