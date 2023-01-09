find_package(OpenCV QUIET)
if (NOT OpenCV_FOUND)
    return()
endif ()

note_generate_target(./ cv TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET}         PRIVATE ${OpenCV_LIBS})
    target_include_directories(${TARGET}    PRIVATE ${OpenCV_INCLUDE_DIRS})
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