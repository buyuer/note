# Date      2024.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

find_package(CUDAToolkit QUIET)
if (NOT CUDAToolkit_FOUND)
    return()
endif ()

set(CMAKE_CUDA_ARCHITECTURES 75)
set(CMAKE_CUDA_COMPILER ${CUDAToolkit_NVCC_EXECUTABLE})

project(note-cuda LANGUAGES CUDA)

note_generate_target(./ cuda TARGETS)

foreach (TARGET ${TARGETS})
    target_link_libraries(${TARGET} PRIVATE CUDA::cudart)
    set_target_properties(
            ${TARGET}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
            CXX_STANDARD 23
            CXX_EXTENSIONS OFF
            CXX_STANDARD_REQUIRED OFF
            CUDA_STANDARD 23
            CUDA_EXTENSIONS OFF
            CUDA_STANDARD_REQUIRED OFF
    )
endforeach ()
