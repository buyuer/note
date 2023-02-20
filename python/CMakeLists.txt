
find_package(Python3 COMPONENTS Development)
if (NOT Python3_FOUND)
    return()
endif ()

note_generate_target(./ python TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE Python3::Python)
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
endforeach ()
