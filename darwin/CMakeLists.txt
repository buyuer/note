
add_executable(darwin_kqueue kqueue.c)

set_target_properties(
        darwin_kqueue
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)