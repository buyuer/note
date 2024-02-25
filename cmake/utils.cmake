
function(note_generate_target _PATH _PREFIX _TARGETS)
    file(GLOB FILE_PATHS "${_PATH}/*.cpp" "${_PATH}/*.cxx" "${_PATH}/*.c" "${_PATH}/*.cu")
    foreach (FILE_PATH ${FILE_PATHS})
        string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
        set(TARGET_NAME ${_PREFIX}_${FILE_NAME})
        add_executable(${TARGET_NAME} ${FILE_PATH})
        message("   -> add target: ${TARGET_NAME}")
        list(APPEND TARGETS_NAME ${TARGET_NAME})
        install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/output)
    endforeach ()
    set(${_TARGETS} ${TARGETS_NAME} PARENT_SCOPE)
endfunction()
