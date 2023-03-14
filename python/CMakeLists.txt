
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
    # windows平台的路径是 '\'，添加宏的时候，要把路径里的 ’\’，替换为 '\\'
    # 如果是c++，可使用 R“”，不转义字符串，如：-DPYTHONHOME=R"${PYTHONHOME}"
    string(REGEX REPLACE "[\\]" "\\\\\\\\" PYTHONHOME ${Python3_ROOT})
    target_compile_definitions(${TARGET} PRIVATE -DPYTHONHOME="${PYTHONHOME}")
endforeach ()
