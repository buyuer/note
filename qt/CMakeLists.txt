find_package(Qt5 COMPONENTS Core Gui QUIET)

if (NOT Qt5_FOUND)
    return()
endif ()
