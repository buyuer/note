
note_generate_target(./ darwin DARWIN_TARGETS)

find_package(Threads)

foreach(TARGET ${DARWIN_TARGETS})
    target_link_libraries(${TARGET} Threads::Threads)
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 23
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
    )
endforeach()
