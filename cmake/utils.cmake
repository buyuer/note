# Date      2022.02.01
# Author    dingddding@163.com
# Bref      The CMakeLists.txt

function(note_generate_target _PATH _PREFIX _TARGETS)
    file(GLOB FILE_PATHS "${_PATH}/*.cpp" "${_PATH}/*.cxx" "${_PATH}/*.c" "${_PATH}/*.cu")
    foreach (FILE_PATH ${FILE_PATHS})
        string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
        set(TARGET_NAME ${_PREFIX}_${FILE_NAME})
        add_executable(${TARGET_NAME} ${FILE_PATH})
        message(STATUS "   -> add target: ${TARGET_NAME}")
        list(APPEND TARGETS_NAME ${TARGET_NAME})
        install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/output)
    endforeach ()
    set(${_TARGETS} ${TARGETS_NAME} PARENT_SCOPE)
endfunction()

function(get_build_info _BUILD_INFO)
    set(BUILD_SHA "N/A")
    set(BUILD_BRANCH "N/A")
    set(BUILD_COMMIT_DATE "N/A")
    set(BUILD_DIRTY "")
    find_package(Git)
    if (GIT_FOUND)
        execute_process(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
                OUTPUT_VARIABLE BUILD_SHA
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
                OUTPUT_VARIABLE BUILD_BRANCH
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${GIT_EXECUTABLE} show -s --format=%cd --date=short HEAD
                OUTPUT_VARIABLE BUILD_COMMIT_DATE
                OUTPUT_STRIP_TRAILING_WHITESPACE)
        string(REPLACE "-" "." BUILD_COMMIT_DATE ${BUILD_COMMIT_DATE})

        execute_process(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND bash -c "${GIT_EXECUTABLE} diff --quiet --exit-code || echo dirty."
                OUTPUT_VARIABLE BUILD_DIRTY
                OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif ()
    string(TIMESTAMP BUILD_TIME "%Y.%m.%d.%H.%M.%S")
    set(${_BUILD_INFO} "hash(${BUILD_SHA}).branch(${BUILD_DIRTY}${BUILD_BRANCH}).date(${BUILD_COMMIT_DATE}).buildtime(${BUILD_TIME})" PARENT_SCOPE)

    # message(STATUS "Build Time              ${BUILD_TIME}")
    # message(STATUS "Build SHA               ${BUILD_SHA}")
    # message(STATUS "Build Branch            ${BUILD_BRANCH}")
    # message(STATUS "Build Commit Data       ${BUILD_COMMIT_DATE}")
    # message(STATUS "Build dirty             ${BUILD_DIRTY}")
endfunction()

function(get_subdir _SUBDIRS _DIR)
    file(GLOB children RELATIVE ${_DIR} ${_DIR}/*)
    set(DIRS "")
    foreach (child ${children})
        if (IS_DIRECTORY ${_DIR}/${child} AND EXISTS ${_DIR}/${child}/CMakeLists.txt)
            list(APPEND DIRS ${child})
        endif ()
    endforeach ()
    set(${_SUBDIRS} ${DIRS} PARENT_SCOPE)
endfunction()
