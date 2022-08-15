
add_executable(unix_select select.c)
add_executable(unix_poll poll.c)

set_target_properties(
        unix_select
        unix_poll
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)