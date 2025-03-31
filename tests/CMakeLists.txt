find_package(libcpptest
    NAMES
        cpptest
        libcpptest
    REQUIRED
)

get_target_property(libcpptest_INCLUDE_DIR CPPTEST::libcpptest INTERFACE_INCLUDE_DIRECTORIES)

add_subdirectory(ftp)
add_subdirectory(storage)