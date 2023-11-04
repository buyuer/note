find_package(pybind11 QUIET)
if (NOT pybind11_FOUND)
    return()
endif ()