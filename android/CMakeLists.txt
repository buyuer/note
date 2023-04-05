if (NOT ANDROID)
    return()
endif ()

add_library(note SHARED)

target_sources(note PRIVATE note.cpp)

set_target_properties(
        note
        PROPERTIES
        C_STANDARD 11
        C_EXTENSIONS OFF
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 23
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED OFF
)
