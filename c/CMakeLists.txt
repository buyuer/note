note_generate_target(./ c TARGETS)

find_package(Threads)

foreach(TARGET ${TARGETS})
    target_link_libraries(${TARGET} Threads::Threads)
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
    )
endforeach()
