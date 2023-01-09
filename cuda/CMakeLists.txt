find_package(CUDAToolkit QUIET)
if (NOT CUDAToolkit_FOUND)
    return()
endif ()

note_generate_target(./ boost TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE CUDA::cudart)
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
    )
endforeach ()
