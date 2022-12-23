list(APPEND c_targets
        restrict
        )

foreach (target ${c_targets})
    add_executable(c_${target} ${target}.c)
    set_target_properties(
            c_${target}
            PROPERTIES
            C_STANDARD 11
            C_EXTENSIONS OFF
            C_STANDARD_REQUIRED ON
    )
endforeach ()
